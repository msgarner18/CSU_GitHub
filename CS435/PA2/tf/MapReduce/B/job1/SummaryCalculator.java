package tf.MapReduce.B.job1;

import java.util.StringTokenizer;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.Text;

import java.util.TreeMap;
import java.util.Map;
import java.util.ArrayList;
import java.util.Set;

public class SummaryCalculator {
    private Map<Text, DoubleWritable> TF_IDFs; 
    private Map<IntWritable, ArrayList<String>> sentences;

    public SummaryCalculator(Map<Text, DoubleWritable> TF_IDFs, Map<IntWritable, ArrayList<String>> sentences) {
        this.TF_IDFs = TF_IDFs;
        this.sentences = sentences;
    }

    public Set<String> getBestSentences(IntWritable docId) {
        ArrayList<String> sentenceList = sentences.get(docId);
        
        Map<String, Double> best_sentence_TF_IDFs = new TreeMap<String, Double>();
        for( String sentence : sentenceList) {
            String sentenceCopy = new String(sentence);
            double[] best_unigram_TF_IDFs = getBestUnigramTF_IDFs(docId, sentenceCopy);
            double sentenceScore = calculateSentenceScore(best_unigram_TF_IDFs);
            addSentence(new String(sentenceCopy), sentenceScore, best_sentence_TF_IDFs);
            // best_sentence_TF_IDFs.put(sentenceCopy, 1.0);
        }

        return best_sentence_TF_IDFs.keySet();
    }

    public double[] getBestUnigramTF_IDFs(IntWritable docId, String sentence) {
        double[] best_unigram_TF_IDFs = {0.0, 0.0, 0.0, 0.0, 0.0};
       
        String rawText = new String(sentence);
        StringTokenizer itr = new StringTokenizer(rawText);
        while(itr.hasMoreTokens()) {
            String unigram = itr.nextToken();
            Text key = new Text(docId.get()+unigram);
            DoubleWritable cur_TF_IDF_Writable = TF_IDFs.get(key);
            if(cur_TF_IDF_Writable != null) {
                double cur_TF_IDF = cur_TF_IDF_Writable.get();
                addUnigram(cur_TF_IDF, best_unigram_TF_IDFs);
            }
            
        }

        return best_unigram_TF_IDFs;
    }

    private void addUnigram(double cur_TF_IDF, double[] best_unigram_TF_IDFs) {
        for(int i = 0; i < 5; i++) {
            double TF_IDF = best_unigram_TF_IDFs[i];
            if(cur_TF_IDF > TF_IDF) {
                if(i > 0) {
                    best_unigram_TF_IDFs[i-1] = best_unigram_TF_IDFs[i];
                }
                best_unigram_TF_IDFs[i] = cur_TF_IDF;
                continue;
            }
            break;
        }
    }

    public double calculateSentenceScore(double[] best_unigram_TF_IDFs) {
        double sentenceScore = 0;
        for(double TF_IDF : best_unigram_TF_IDFs) {
            sentenceScore += TF_IDF;
        }

        return sentenceScore;
    }

    private void addSentence(String sentence, double sentenceScore, Map<String, Double> best_sentence_TF_IDFs) {
         // add sentence to best_sentence_TF_IDFs list in the proper place
         best_sentence_TF_IDFs.put(sentence, sentenceScore);
         if(best_sentence_TF_IDFs.size() > 5) {
             double min_TF_IDF = 0.0;
             String min_sentence = sentence;
             for(String s : best_sentence_TF_IDFs.keySet()) {
                 if(best_sentence_TF_IDFs.get(s).doubleValue() < min_TF_IDF) {
                     min_TF_IDF = best_sentence_TF_IDFs.get(s).doubleValue();
                     min_sentence = s;
                 }
             }
             best_sentence_TF_IDFs.remove(min_sentence);
         }
    }
}
