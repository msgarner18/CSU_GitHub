package tf.MapReduce.B.job1;

import tf.DriverB;
import tf.InputClasses.Document;
import tf.InputClasses.SentenceParser;
import tf.CustomWritables.UnigramFreqWritable;
import tf.CustomWritables.UnigramTFWritable;
// import tf.MapReduce.B.job1.Filler;
import tf.MapReduce.B.job1.SummaryCalculator;

import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;

import org.apache.hadoop.io.BytesWritable;
import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.MapWritable;
import org.apache.hadoop.io.Text;

import java.util.TreeMap;
import java.util.Map;
import java.util.Set;
import java.util.ArrayList;

import java.util.StringTokenizer;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.NLineInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.input.MultipleInputs;
import org.apache.hadoop.mapreduce.Counter;
import org.apache.hadoop.fs.Path;

// outputs docId longest_sentence
public class JobOneB {
    public static class TF_IDFMapper extends Mapper<Object, Text, IntWritable, Text> {
        public void map(Object key, Text input, Context context) throws IOException, InterruptedException {
            String rawText = new String(input.toString());
            StringTokenizer itr = new StringTokenizer(rawText);

            int docId = Integer.parseInt(itr.nextToken());
            Text unigram = new Text(itr.nextToken());
            double TF_IDF = Double.parseDouble(itr.nextToken());

            context.write(new IntWritable(docId), new Text("A\t"+unigram+ "\t"+ TF_IDF));
        }
    }
    public static class SentenceMapper extends Mapper<Object, Text, IntWritable, Text> {

	    public void map(Object key, Text input, Context context) throws IOException, InterruptedException {
	    	String rawText = new String(input.toString());
            Document doc = new Document(rawText);
			int docId = doc.getDocId();
			if(docId != -1) {
                SentenceParser itr = new SentenceParser(rawText);
                while(itr.hasMoreSentences()) {
                    String sentence = itr.next();
                    if(sentence.length() > 0)
                        context.write(new IntWritable(docId), new Text("B\t"+sentence));
                }
            }
		}
	}

	public static class SentenceReducer extends Reducer<IntWritable, Text, IntWritable, Text> {
        private Map<Text, DoubleWritable> TF_IDFs; 
        private Map<IntWritable, ArrayList<String>> sentences;

        private void addTF_IDF(IntWritable docId, Text content) {
            if(content.toString().charAt(0) == 'A') {
                String rawText = new String(content.toString().substring(2));
                StringTokenizer itr = new StringTokenizer(rawText);

                Text unigram = new Text(itr.nextToken());
                double TF_IDF = Double.parseDouble(itr.nextToken());

                TF_IDFs.put(new Text(docId.get()+unigram.toString()), new DoubleWritable(TF_IDF));
            }
        }

        private void addSentence(IntWritable docId, Text content) {
            if(content.toString().charAt(0) == 'B') {
                String sentence = content.toString().substring(2);
                ArrayList<String> list = sentences.get(docId);
                if(list == null)
                    list = new ArrayList<String>();
                list.add(new String(sentence));

                sentences.put(docId, list);
            }
        }

		@Override
		protected void setup(Context context) {
            TF_IDFs = new TreeMap<Text, DoubleWritable>(); 
            sentences = new TreeMap<IntWritable, ArrayList<String>>();
		}

        @Override
		public void reduce(IntWritable docIdKey, Iterable<Text> contentItr, Context context) throws IOException, InterruptedException {
			for(Text content : contentItr) {
                IntWritable docId = new IntWritable(docIdKey.get());
                addTF_IDF(docId, content);
                addSentence(docId, content);
			}
		}

        @Override
		protected void cleanup(Context context) throws IOException, InterruptedException {
            // loop through each docId
            SummaryCalculator calc = new SummaryCalculator(TF_IDFs, sentences);
            
            for(IntWritable docId : sentences.keySet()){
                Set<String> best_sentences = calc.getBestSentences(docId);
                for(String sentence : sentences.get(docId)) {
                    if( best_sentences.contains(sentence) )
                        context.write(new IntWritable(docId.get()), new Text(sentence));
                }  
            }
        }
	}

	public static int run(String TF_IDFInput, String docInput, String outputDir) throws Exception {
		Configuration conf = new Configuration();
		Job job = Job.getInstance(conf, "Job 1B");

        MultipleInputs.addInputPath(job, new Path(TF_IDFInput),
            NLineInputFormat.class, JobOneB.TF_IDFMapper.class);
        MultipleInputs.addInputPath(job, new Path(docInput),
            NLineInputFormat.class, JobOneB.SentenceMapper.class);
		// job.setInputFormatClass(NLineInputFormat.class);
		job.setJarByClass(DriverB.class);

		job.setMapOutputKeyClass(IntWritable.class);
		job.setMapOutputValueClass(Text.class);


		job.setReducerClass(JobOneB.SentenceReducer.class);
		job.setOutputKeyClass(IntWritable.class);
		job.setOutputValueClass(Text.class);

		// FileInputFormat.addInputPath(job, new Path(inputDir));
		FileOutputFormat.setOutputPath(job, new Path(outputDir));
		
		return job.waitForCompletion(true) ? 0 : 1;
	}
}