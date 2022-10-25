package tf.MapReduce.A.job1;

import tf.DriverA;
import tf.CustomWritables.UnigramFreqWritable;
import tf.InputClasses.Document;

import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.mapreduce.lib.input.NLineInputFormat;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.Counter;

public class JobOneA {
    // unique to each mapper
	public static class FreqMapper extends Mapper<LongWritable, Text, Text, IntWritable> {

        // called for all mappers
        public void map(LongWritable key, Text input, Context context) throws IOException, InterruptedException {
            String rawText = new String(input.toString());
            Document doc = new Document(rawText);
            int docId = doc.getDocId();
            if(docId != -1) {
                context.getCounter(DriverA.DocumentsCount.NUMDOCS).increment(1);
                String article = doc.getArticle();
                StringTokenizer itr = new StringTokenizer(article);
                while(itr.hasMoreTokens()) {
                    String unigram = itr.nextToken();
                    Text docId_unigram = new Text(docId+"\t"+unigram);
                    context.write(new Text(docId_unigram), new IntWritable(1));
                }
            }
        }
    }

    public static class FreqCombiner extends Reducer<Text, IntWritable, Text, IntWritable> {

        @Override
        public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            int total_freq = 0;
            for(IntWritable val : values) {
                total_freq += val.get();
            }

            context.write(new Text(key.toString()), new IntWritable(total_freq));
        }
    }

    public static class FreqReducer extends Reducer<Text, IntWritable, IntWritable, UnigramFreqWritable> {

        @Override
        public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            // for(IntWritable)
            StringTokenizer itr = new StringTokenizer(key.toString());
            int docId = Integer.parseInt(itr.nextToken());
            String unigram = itr.nextToken();

            int total_freq = 0;
            for(IntWritable val : values) {
                total_freq += val.get();
            }
            context.write(new IntWritable(docId), new UnigramFreqWritable(new Text(unigram), new IntWritable(total_freq)));
        }
    }

    public static Counter run(String inputDir, String outputDir) throws Exception {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "Job 1A");

		job.setInputFormatClass(NLineInputFormat.class);
		job.setJarByClass(DriverA.class);

		job.setMapperClass(JobOneA.FreqMapper.class);
        job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(IntWritable.class);

		// job.setCombinerClass(JobOneA.FreqCombiner.class);

		job.setReducerClass(JobOneA.FreqReducer.class);
        job.setOutputKeyClass(IntWritable.class);
		job.setOutputValueClass(UnigramFreqWritable.class);

		FileInputFormat.addInputPath(job, new Path(inputDir));
		FileOutputFormat.setOutputPath(job, new Path(outputDir));

        job.waitForCompletion(true);

        Counter counter = job.getCounters().findCounter(DriverA.DocumentsCount.NUMDOCS);
        return counter;
    }
}
