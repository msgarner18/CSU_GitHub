package tf;

import tf.MapReduce.B.job1.JobOneB;
// import java.io.IOException;
// import java.util.ArrayList;
// import java.util.HashMap;
// import java.util.Map;
// import java.util.StringTokenizer;
// import java.util.regex.Matcher;
// import java.util.regex.Pattern;

import org.apache.hadoop.conf.Configuration;
// import org.apache.hadoop.fs.Path;
// import org.apache.hadoop.io.BytesWritable;
// import org.apache.hadoop.io.IntWritable;
// import org.apache.hadoop.io.Writable;
// import org.apache.hadoop.io.MapWritable;
// import org.apache.hadoop.io.Text;
// import org.apache.hadoop.mapreduce.Job;
// import org.apache.hadoop.mapreduce.Mapper;
// import org.apache.hadoop.mapreduce.Reducer;
// import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
// import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;
import org.apache.hadoop.conf.Configured;

public class DriverB extends Configured implements Tool{

	public static int runJob(String TF_IDF_Dir, String inputDir, String outputDir) throws Exception {
        return JobOneB.run(TF_IDF_Dir, inputDir, outputDir);

		// return 0;
	}

	public static void main(String[] args) throws Exception {
		//ToolRunner allows for command line configuration parameters - suitable for shifting between local job and yarn
		// example command: hadoop jar <path_to_jar.jar> <main_class> -D param=value <input_path> <output_path>
		//We use -D mapreduce.framework.name=<value> where <value>=local means the job is run locally and <value>=yarn means using YARN
		int res = ToolRunner.run(new Configuration(), new DriverB(), args);
        System.exit(res); //res will be 0 if all tasks are executed succesfully and 1 otherwise
	}

	@Override
   	public int run(String[] args) throws Exception {
        if(runJob(args[0], args[1], args[2]) != 0)
            return 1; //error
		return 0;	 //success
   	}
}
