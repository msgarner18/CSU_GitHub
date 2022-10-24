package tf.CustomWritables;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.Text;

public class DocIdTFWritable implements Writable {
	private Text unigram;
	private DoubleWritable TF;
	
	public DocIdTFWritable(Text unigram, DoubleWritable TF){
		this.unigram = new Text(unigram.toString());
        this.TF = new DoubleWritable(TF.get());
	}

	public DocIdTFWritable() {
		this.unigram = new Text();
        this.TF = new DoubleWritable();
	}

	public Text getUnigram() {
		return unigram;
	}

	public DoubleWritable getTF() {
		return TF;
	}

	@Override
	public void readFields(DataInput arg0) throws IOException {
		unigram.readFields(arg0);
		TF.readFields(arg0);
	}

	@Override
	public void write(DataOutput arg0) throws IOException {
		unigram.write(arg0);
		TF.write(arg0);
	}

	@Override
	public String toString(){
		return unigram.toString() + "\t" + TF.get();
	}

    @Override
    public int hashCode() {
      return unigram.hashCode();
    }
}
