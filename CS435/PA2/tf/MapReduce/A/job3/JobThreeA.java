// package tf.MapReduce.A.job3;

// import tf.CustomWritables.UnigramFreqWritable;
// import tf.CustomWritables.UnigramTF_IDFWritable;
// import tf.DriverA;

// import java.io.IOException;

// import org.apache.hadoop.fs.Path;
// import org.apache.hadoop.mapreduce.lib.input.NLineInputFormat;
// import org.apache.hadoop.conf.Configuration;
// import org.apache.hadoop.io.BytesWritable;
// import org.apache.hadoop.io.IntWritable;
// import org.apache.hadoop.io.Writable;
// import org.apache.hadoop.io.Text;
// import org.apache.hadoop.mapreduce.Job;
// import org.apache.hadoop.mapreduce.Mapper;
// import org.apache.hadoop.mapreduce.Reducer;
// import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
// import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
// import org.apache.hadoop.mapreduce.Counter;

// public class JobThreeA {
//     // unique to each mapper
// 	public static class TF_IDFMapper extends Mapper<Object, BytesWritable, Text, IntWritable> {

//         // called for all mappers
//         public void map(Object key, BytesWritable bWriteable, Context context) throws IOException, InterruptedException {
            
//         }
//     }

//     public static class TF_IDFCombiner extends Reducer<Text, IntWritable, Text, IntWritable> {

//         @Override
//         public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            
//         }
//     }

//     public static class TF_IDFReducer extends Reducer<Text, IntWritable, IntWritable, UnigramFreqWritable> {

//         @Override
//         public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            
//         }
//     }

//     public static void run(Counter counter, String inputDir, String outputDir) throws Exception {
//         Configuration conf = new Configuration();
//         Job job = Job.getInstance(conf, "Job 3A");

//         job.getConfiguration().setLong(counter.getDisplayName(), counter.getValue());

// 		job.setInputFormatClass(NLineInputFormat.class);
// 		job.setJarByClass(DriverA.class);

// 		job.setMapperClass(JobThreeA.TF_IDFMapper.class);
//         job.setMapOutputKeyClass(IntWritable.class);
// 		job.setMapOutputValueClass(UnigramFreqWritable.class);

// 		// job.setCombinerClass(JobThreeA.FreqCombiner.class);

// 		job.setReducerClass(JobThreeA.TF_IDFReducer.class);
//         job.setOutputKeyClass(IntWritable.class);
// 		job.setOutputValueClass(UnigramTF_IDFWritable.class);

// 		FileInputFormat.addInputPath(job, new Path(inputDir));
// 		FileOutputFormat.setOutputPath(job, new Path(outputDir));

//         job.waitForCompletion(true);
//     }
// }


package tf.MapReduce.A.job3;

import tf.DriverA;
import tf.CustomWritables.DocIdTFWritable;
import tf.CustomWritables.UnigramTF_IDFWritable;

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

import java.lang.Math;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.NLineInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.Counter;
import org.apache.hadoop.fs.Path;

public class JobThreeA {
    public static class TFMapper extends Mapper<Object, Text, Text, DocIdTFWritable> {

	    public void map(Object key, Text input, Context context) throws IOException, InterruptedException {
	    	String rawText = new String(input.toString());
			StringTokenizer itr = new StringTokenizer(rawText);
			int docId = Integer.parseInt(itr.nextToken());
			String unigram = itr.nextToken();
			double TF_value = Double.parseDouble(itr.nextToken());

			context.write(new Text(unigram), new DocIdTFWritable(new IntWritable(docId), new DoubleWritable(TF_value)));
		}
	}

	public static class TF_IDFReducer extends Reducer<Text, DocIdTFWritable, IntWritable, UnigramTF_IDFWritable> {
        private int N;

        @Override
		protected void setup(Context context) {
			N = (int) context.getConfiguration().getLong(DriverA.DocumentsCount.NUMDOCS.name(), 0);
		}

		@Override
		public void reduce(Text unigramKey, Iterable<DocIdTFWritable> docIdTFItr, Context context) throws IOException, InterruptedException {
			ArrayList<DocIdTFWritable> docIdTF_list = new ArrayList<DocIdTFWritable>();

            // calc ni
            double ni = 0;
			for(DocIdTFWritable docIdTF : docIdTFItr) {
                int docId = docIdTF.getDocId().get();
                double TF = docIdTF.getTF().get();
                docIdTF_list.add(new DocIdTFWritable(new IntWritable(docId), new DoubleWritable(TF)));

                ni += 1;
			}

            // IDF
            double IDF = Math.log10(N/ni);

            // TF_IDF
            for(DocIdTFWritable docIdTF : docIdTF_list) {
                double TF = docIdTF.getTF().get();
                double TF_IDF = TF * IDF;

                int docId = docIdTF.getDocId().get();
                UnigramTF_IDFWritable unigramTF_IDF = new UnigramTF_IDFWritable(new Text(unigramKey), new DoubleWritable(TF_IDF));
                context.write(new IntWritable(docId), unigramTF_IDF);
            }
		}
	}

	public static int run(Counter docNumCounter, String inputDir, String outputDir) throws Exception {
		Configuration conf = new Configuration();
		Job job = Job.getInstance(conf, "Job 3A");

		job.getConfiguration().setLong(docNumCounter.getDisplayName(), docNumCounter.getValue());

		job.setInputFormatClass(NLineInputFormat.class);
		job.setJarByClass(DriverA.class);

		job.setMapperClass(JobThreeA.TFMapper.class);
		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(DocIdTFWritable.class);

		// job.setCombinerClass(MyCombiner.class);

		job.setReducerClass(JobThreeA.TF_IDFReducer.class);
		job.setOutputKeyClass(IntWritable.class);
		job.setOutputValueClass(UnigramTF_IDFWritable.class);

		FileInputFormat.addInputPath(job, new Path(inputDir));
		FileOutputFormat.setOutputPath(job, new Path(outputDir));
		
		return job.waitForCompletion(true) ? 0 : 1;
	}
}

