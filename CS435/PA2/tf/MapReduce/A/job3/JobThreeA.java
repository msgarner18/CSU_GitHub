package tf.MapReduce.A.job3;

import tf.CustomWritables.UnigramFreqWritable;
import tf.CustomWritables.UnigramTF_IDFWritable;
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

public class JobThreeA {
    // unique to each mapper
	public static class TF_IDFMapper extends Mapper<Object, BytesWritable, Text, IntWritable> {

        // called for all mappers
        public void map(Object key, BytesWritable bWriteable, Context context) throws IOException, InterruptedException {
            
        }
    }

    public static class TF_IDFCombiner extends Reducer<Text, IntWritable, Text, IntWritable> {

        @Override
        public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            
        }
    }

    public static class TF_IDFReducer extends Reducer<Text, IntWritable, IntWritable, UnigramFreqWritable> {

        @Override
        public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            
        }
    }

    public static void run(Counter counter, String inputDir, String outputDir) throws Exception {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "Job 3A");

        job.getConfiguration().setLong(counter.getDisplayName(), counter.getValue());

		job.setInputFormatClass(NLineInputFormat.class);
		job.setJarByClass(DriverA.class);

		job.setMapperClass(JobThreeA.TF_IDFMapper.class);
        job.setMapOutputKeyClass(IntWritable.class);
		job.setMapOutputValueClass(UnigramFreqWritable.class);

		// job.setCombinerClass(JobThreeA.FreqCombiner.class);

		job.setReducerClass(JobThreeA.TF_IDFReducer.class);
        job.setOutputKeyClass(IntWritable.class);
		job.setOutputValueClass(UnigramTF_IDFWritable.class);

		FileInputFormat.addInputPath(job, new Path(inputDir));
		FileOutputFormat.setOutputPath(job, new Path(outputDir));

        job.waitForCompletion(true);
    }
}
