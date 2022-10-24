package tf.MapReduce.A.job2;

import tf.CustomWritables.UnigramFreqWritable;
import tf.DriverA;

import java.io.IOException;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.mapreduce.lib.input.NLineInputFormat;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.io.BytesWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.Counter;

public class JobTwoA {
    // unique to each mapper
	public static class FreqMapper extends Mapper<Object, BytesWritable, Text, IntWritable> {

        // called for all mappers
        public void map(Object key, BytesWritable bWriteable, Context context) throws IOException, InterruptedException {
            
        }
    }

    public static class FreqCombiner extends Reducer<Text, IntWritable, Text, IntWritable> {

        @Override
        public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            
        }
    }

    public static class FreqReducer extends Reducer<Text, IntWritable, IntWritable, UnigramFreqWritable> {

        @Override
        public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            
        }
    }

    public static void run(Counter docCounter, String inputDir, String outputDir) {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "Job 2A");

		job.setInputFormatClass(NLineInputFormat.class);
		job.setJarByClass(DriverA.class);

		job.setMapperClass(JobTwoA.FreqMapper.class);
        job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(IntWritable.class);

		job.setCombinerClass(JobTwoA.FreqCombiner.class);

		job.setReducerClass(JobTwoA.FreqReducer.class);
        job.setOutputKeyClass(IntWritable.class);
		job.setOutputValueClass(UnigramFreqWritable.class);

		FileInputFormat.addInputPath(job, new Path(inputDir));
		FileOutputFormat.setOutputPath(job, new Path(outputDir));

        job.waitForCompletion(true);
    }
}
