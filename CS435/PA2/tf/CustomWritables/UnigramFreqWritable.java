package tf.CustomWritables;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.MapWritable;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.Text;

public class UnigramFreqWritable implements Writable {
	private Text unigram;
	private IntWritable freq;
	
	public UnigramFreqWritable(Text unigram, IntWritable freq){
		this.unigram = new Text(unigram.toString());
        this.freq = new IntWritable(freq.get());
	}

	public UnigramFreqWritable() {
		this.unigram = new Text();
        this.freq = new IntWritable();
	}

	public Text getUnigram() {
		return unigram;
	}

	public IntWritable getFreq() {
		return freq;
	}

	@Override
	public void readFields(DataInput arg0) throws IOException {
		unigram.readFields(arg0);
		freq.readFields(arg0);
	}

	@Override
	public void write(DataOutput arg0) throws IOException {
		unigram.write(arg0);
		freq.write(arg0);
	}

	@Override
	public String toString(){
		return unigram.toString() + "\t" + freq.get();
	}

    @Override
    public int hashCode() {
      return unigram.hashCode();
    }
}
