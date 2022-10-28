package tf.Test;

import tf.MapReduce.B.job1.SummaryCalculator;

import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;

import java.util.TreeMap;
import java.util.Map;
import java.util.ArrayList;

public class TestMain {
    public static void main(String[] args) throws Exception {
        Map<Text, DoubleWritable> TF_IDFs = new TreeMap<Text, DoubleWritable>() {{
            put(new Text("1234a"), new DoubleWritable(1.0));
            put(new Text("1234b"), new DoubleWritable(0.9));
            put(new Text("1234c"), new DoubleWritable(0.8));
            put(new Text("1234d"), new DoubleWritable(0.7));
            put(new Text("1234e"), new DoubleWritable(0.6));
            put(new Text("1234f"), new DoubleWritable(0.5));
            put(new Text("1234g"), new DoubleWritable(0.4));
        }}; 
        Map<IntWritable, ArrayList<String>> sentences = new TreeMap<IntWritable, ArrayList<String>>() {{
            put(new IntWritable(1234), new ArrayList<String>() {{
                add("g g g g g a");
                add("g g g g g b");
                add("g g g g g c");
                add("g g g g g d");
                add("g g g g g e");
                add("g g g g g f");
                add("g g g g g g");
            }});
        }}; 

        SummaryCalculator calc = new SummaryCalculator(TF_IDFs, sentences);
        // String sentence = "a b c d e f g";
        // sentences.get(new IntWritable(1234)) ) {
        for( String sentence : calc.getBestSentences(new IntWritable(1234)) ) {
            double[] best_unigram_TF_IDFs = calc.getBestUnigramTF_IDFs(new IntWritable(1234), sentence);
            System.out.println("sentence: "+sentence);
            System.out.println("best_unigram_TF_IDFs: ");
            for(double TF_IDF : best_unigram_TF_IDFs) {
                System.out.println("\t"+TF_IDF);
            }
            System.out.println("sentenceScore: " + calc.calculateSentenceScore(best_unigram_TF_IDFs));
        }
            
        // for( String sentence : calc.getBestSentences(new IntWritable(1234)) ) {
        //     System.out.println(sentence);
        // }
    }
}
