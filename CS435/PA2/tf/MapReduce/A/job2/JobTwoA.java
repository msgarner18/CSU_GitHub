package tf.MapReduce.A.job2;

import tf.CustomWritables.UnigramFreqWritable;
import tf.CustomWritables.UnigramTFWritable;
import tf.DriverA;

import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.mapreduce.lib.input.NLineInputFormat;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.Counter;

import java.util.ArrayList;

public class JobTwoA {
     // unique to each mapper
	public static class TFMapper extends Mapper<LongWritable, Text, IntWritable, UnigramFreqWritable> {

        // called for all mappers
        public void map(LongWritable key, Text input, Context context) throws IOException, InterruptedException {
            String rawText = new String(input.toString());
            StringTokenizer itr = new StringTokenizer(rawText);
           
            int docId = Integer.parseInt(itr.nextToken());
            String unigram = itr.nextToken();
            int freq = Integer.parseInt(itr.nextToken());

            context.write(new IntWritable(docId), new UnigramFreqWritable(new Text(unigram), new IntWritable(freq)));
        }
    }

    // public static class TFCombiner extends Reducer<Text, IntWritable, Text, IntWritable> {

    //     @Override
    //     public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
    //         int total_freq = 0;
    //         for(IntWritable val : values) {
    //             total_freq += val.get();
    //         }

    //         context.write(new Text(key.toString()), new IntWritable(total_freq));
    //     }
    // }

    public static class TFReducer extends Reducer<IntWritable, UnigramFreqWritable, IntWritable, UnigramTFWritable> {

        @Override
        public void reduce(IntWritable docIdKey, Iterable<UnigramFreqWritable> unigram_freq_itr, Context context) throws IOException, InterruptedException {
            ArrayList<UnigramFreqWritable> list = new ArrayList<UnigramFreqWritable>();
            
            // calc maxFreq
            double maxFreq = 0.0;
            for(UnigramFreqWritable unigram_freq : unigram_freq_itr) {
                String unigram = unigram_freq.getUnigram().toString();
                int freq = unigram_freq.getFreq().get();
                list.add(new UnigramFreqWritable(new Text(unigram), new IntWritable(freq)));
                if(freq > maxFreq)
                    maxFreq = freq;
            }

            // calc TF
            for(UnigramFreqWritable unigram_freq : list) {
                String unigram = unigram_freq.getUnigram().toString();
                int freq = unigram_freq.getFreq().get();
                double TF = 0.5 + 0.5 * (freq/maxFreq);
                context.write(docIdKey, new UnigramTFWritable(new Text(unigram), new DoubleWritable(TF)));
            }
        }
    }

    public static void run(String inputDir, String outputDir) throws Exception {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "Job 2A");

		job.setInputFormatClass(NLineInputFormat.class);
		job.setJarByClass(DriverA.class);

		job.setMapperClass(JobTwoA.TFMapper.class);
        job.setMapOutputKeyClass(IntWritable.class);
		job.setMapOutputValueClass(UnigramFreqWritable.class);

		// job.setCombinerClass(JobTwoA.TFCombiner.class);

		job.setReducerClass(JobTwoA.TFReducer.class);
        job.setOutputKeyClass(IntWritable.class);
		job.setOutputValueClass(UnigramTFWritable.class);

		FileInputFormat.addInputPath(job, new Path(inputDir));
		FileOutputFormat.setOutputPath(job, new Path(outputDir));

        job.waitForCompletion(true);
    }
}
