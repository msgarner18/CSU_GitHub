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

import java.util.HashMap;
import java.util.Map;
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
                context.write(docId, new Text("A "+docId.get()+unigram.toString()));
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
                context.write(docId, new Text("B "+new String(sentence)));
            }
        }

		@Override
		protected void setup(Context context) {
            TF_IDFs = new HashMap<Text, DoubleWritable>(); 
            sentences = new HashMap<IntWritable, ArrayList<String>>();
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
            // SummaryCalculator calc = new SummaryCalculator(TF_IDFs, sentences);
            
            // for(IntWritable docId : sentences.keySet()){
            //     for(String sentence : calc.getBestSentences(docId)) {
            //         context.write(new IntWritable(docId.get()), new Text(sentence));
            //     }  
            // }
            // for(Text key : TF_IDFs.keySet()) {
            //     context.write(new IntWritable(1), new Text(TF_IDFs.get(key).get()+""));
            // }
            // for(IntWritable docId : sentences.keySet()){
            //     for(String sentence : sentences.get(docId)) {
            //         context.write(new IntWritable(docId.get()), new Text(sentence));
            //     }  
            // }
        }
            //     // retrieve list of sentences associated with this docId
            //     ArrayList<String> list = sentences.get(docId);

            //     // Store top 5 sentence TF_IDFs for this docId
            //     Map<String, Double> best_sentence_TF_IDFs= new HashMap<String, Double>();
            //     for(String sentence : list) {
            //         // calc sentence TF_IDF
            //         String rawText = new String(sentence);
            //         StringTokenizer itr = new StringTokenizer(rawText);

            //         double[] best_TF_IDFs = {0.0, 0.0, 0.0, 0.0, 0.0};
            //         while(itr.hasMoreTokens()) {
            //             String unigram = itr.nextToken();
            //             Text key = new Text(docId.get()+unigram);
            //             double cur_TF_IDF = TF_IDFs.get(key).get();
            //             // add TF_IDF to best_TF_IDFs list in the proper place
            //             for(int i = 0; i < 5; i++) {
            //                 double TF_IDF = best_TF_IDFs[i];
            //                 if(cur_TF_IDF > TF_IDF) {
            //                     if(i > 0) {
            //                         best_TF_IDFs[i-1] = best_TF_IDFs[i];
            //                     }
            //                     best_TF_IDFs[i] = cur_TF_IDF;
            //                     continue;
            //                 }
            //                 break;
            //             }
            //         }
            //         // sum top 5 TF_IDFs to make a sentence score
            //         double sentenceScore = 0;
            //         for(double TF_IDF : best_TF_IDFs) {
            //             sentenceScore += TF_IDF;
            //         }

            //         // add sentence to best_sentence_TF_IDFs list in the proper place
            //         best_sentence_TF_IDFs.put(sentence, sentenceScore);
            //         if(best_sentence_TF_IDFs.size() > 5) {
            //             double min_TF_IDF = 0.0;
            //             String min_sentence = sentence;
            //             for(String s : best_sentence_TF_IDFs.keySet()) {
            //                 if(best_sentence_TF_IDFs.get(s).doubleValue() < min_TF_IDF) {
            //                     min_TF_IDF = best_sentence_TF_IDFs.get(s).doubleValue();
            //                     min_sentence = s;
            //                 }
            //             }
            //             best_sentence_TF_IDFs.remove(min_sentence);
            //         }
            //     }
            //     for(String sentence : best_sentence_TF_IDFs.keySet()) {
            //         context.write(new IntWritable(docId.get()), new Text(sentence));
            //     }       
            // }
		// }
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