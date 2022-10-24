// package ngram;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.BytesWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.MapWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;
import org.apache.hadoop.conf.Configured;

public class NgramMapReduce extends Configured implements Tool{
	private static int CurrentVolume = 1;

	public static enum Profiles {
		A1 ('a', 1),
		B1 ('b', 1),
		A2 ('a', 2),
		B2 ('b', 2);

	    private final char profileChar;
	    private final int ngramNum;

	    private Profiles(char c, int n) {
			profileChar = c;
			ngramNum = n;
	    }

	    public boolean equals(Profiles p) {
				boolean charsAreEqual = (profileChar == p.profileChar);
				boolean gramsAreEqual = (ngramNum == p.ngramNum);
				
				return charsAreEqual && gramsAreEqual;
	    }
	}

	// unique to each mapper
	public static class TokenizerMapper extends Mapper<Object, BytesWritable, Text, VolumeWriteable> {
			// private VolumeWriteable volume = new VolumeWriteable(NgramMapReduce.CurrentVolume, new IntWritable(1));
			// private static int CurrentVolume = 1;
			private Text node;//contains either "ngram \t year" or "ngram \t author"

		// called for all mappers
	    public void map(Object key, BytesWritable bWriteable, Context context) throws IOException, InterruptedException {
	    	Profiles profile = context.getConfiguration().getEnum("profile", Profiles.A1); //get profile
			
			//code to get a book
	    	String rawText = new String(bWriteable.getBytes());
	    	Book book = new Book(rawText, profile.ngramNum);
			String year = book.getBookYear();
			String author = book.getBookAuthor();

			// initialize looping through tokens
			VolumeWriteable volume = new VolumeWriteable();
			volume.insertMapValue(new Text(rawText), new IntWritable(1));

			StringTokenizer itr = new StringTokenizer(book.getBookBody());
			StringTokenizer itr2 = new StringTokenizer(book.getBookBody());
			String s;
			if(profile.ngramNum == 2 && itr.hasMoreTokens())
				s = itr.nextToken();//offset itr and itr2 by 1
	    	
			// loop through tokens
			while (itr.hasMoreTokens()) {
				s = itr.nextToken();

				if(profile.ngramNum == 2)
					s = itr2.nextToken() + " " + s;

				if(profile.profileChar == 'a')
					node = new Text(s+"\t"+year);
				if(profile.profileChar == 'b')
					node = new Text(s+"\t"+author);

				// System.err.println("node: "+node+", volume: "+volume);
				System.err.println("test");
				context.write(node, volume);
	    	}
			// volume = new VolumeWriteable(++NgramMapReduce.CurrentVolume, new IntWritable(1));
	    }
	}

	public static class IntSumReducer extends Reducer<Text, VolumeWriteable, Text, VolumeWriteable> {
		private VolumeWriteable volResult;
		private MapWritable newMap;
		private IntWritable countWritable;

		 @Override
		 public void reduce(Text key, Iterable<VolumeWriteable> values, Context context) throws IOException, InterruptedException {
			newMap = new MapWritable();
			//combine volumes
			int total_count = 0;
			for(VolumeWriteable val : values) {
				total_count += val.getCount().get();
				// val.insertMapValue(new IntWritable(2), new IntWritable(1));
				newMap.putAll(val.getVolumeIds());
			}
			countWritable = new IntWritable(total_count);
			volResult = new VolumeWriteable();
			volResult.set(newMap, countWritable);
			context.write(key, volResult);
		}
	}

	public static int runJob(Configuration conf, String inputDir, String outputDir) throws Exception {
		Job job = Job.getInstance(conf, "ngram");

		job.setInputFormatClass(WholeFileInputFormat.class);
		job.setJarByClass(NgramMapReduce.class);

		job.setMapperClass(TokenizerMapper.class);
		// job.setCombinerClass(IntSumReducer.class);
		job.setReducerClass(IntSumReducer.class);

		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(VolumeWriteable.class);

		FileInputFormat.addInputPath(job, new Path(inputDir));
		FileOutputFormat.setOutputPath(job, new Path(outputDir));
		return job.waitForCompletion(true) ? 0 : 1;
	}

	public static void main(String[] args) throws Exception {
		//ToolRunner allows for command line configuration parameters - suitable for shifting between local job and yarn
		// example command: hadoop jar <path_to_jar.jar> <main_class> -D param=value <input_path> <output_path>
		//We use -D mapreduce.framework.name=<value> where <value>=local means the job is run locally and <value>=yarn means using YARN
		int res = ToolRunner.run(new Configuration(), new NgramMapReduce(), args);
    System.exit(res); //res will be 0 if all tasks are executed succesfully and 1 otherwise
	}

	@Override
   	public int run(String[] args) throws Exception {
		//#TODO#: update few things
		Configuration conf = this.getConf();
		Profiles profiles[] = {Profiles.A1};//, Profiles.A2, Profiles.B1, Profiles.B2};
		for(Profiles p : profiles) {
			conf.setEnum("profile", p);
			System.out.println("For profile: " + p.toString());
			if(runJob(conf, args[0], args[1]+p.toString()) != 0)
				return 1; //error
		}
		return 0;	 //success
   	}
}
