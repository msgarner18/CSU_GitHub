package tf;

import tf.MapReduce.A.job1.JobOneA;
import tf.MapReduce.A.job2.JobTwoA;
import tf.MapReduce.A.job3.JobThreeA;

import org.apache.hadoop.conf.Configuration;

import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;
import org.apache.hadoop.conf.Configured;

import org.apache.hadoop.mapreduce.Counter;

public class DriverA extends Configured implements Tool{
    public static enum DocumentsCount {
        NUMDOCS
    }

	public static int runJob(String inputDir, String TF_IDFDir) throws Exception {
		String freqDir = "/PA2/IOFolders/outputs/freq";
		String TFDir = "/PA2/IOFolders/outputs/TF";

		Counter docCounter = JobOneA.run(inputDir, freqDir);
        JobTwoA.run(freqDir, TFDir);
        return JobThreeA.run(docCounter, TFDir, TF_IDFDir);
		// return 0;

	}

	public static void main(String[] args) throws Exception {
		//ToolRunner allows for command line configuration parameters - suitable for shifting between local job and yarn
		// example command: hadoop jar <path_to_jar.jar> <main_class> -D param=value <input_path> <output_path>
		//We use -D mapreduce.framework.name=<value> where <value>=local means the job is run locally and <value>=yarn means using YARN
		int res = ToolRunner.run(new Configuration(), new DriverA(), args);
        System.exit(res); //res will be 0 if all tasks are executed succesfully and 1 otherwise
	}

	@Override
   	public int run(String[] args) throws Exception {
		
        if(runJob(args[0], args[1]) != 0)
            return 1; //error
		return 0;	 //success
   	}
}
