package tf.CustomWritables;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.Text;

public class UnigramTF_IDFWritable implements Writable {
	private Text unigram;
	private DoubleWritable TF_IDF;

	public UnigramTF_IDFWritable(Text unigram, DoubleWritable TF_IDF){
		this.unigram = new Text(unigram.toString());
        this.TF_IDF = new DoubleWritable(TF_IDF.get());
	}

	public UnigramTF_IDFWritable() {
		this.unigram = new Text();
        this.TF_IDF = new DoubleWritable();
	}

	public Text getUnigram() {
		return unigram;
	}

	public DoubleWritable getTF_IDF() {
		return TF_IDF;
	}

	@Override
	public void readFields(DataInput arg0) throws IOException {
		unigram.readFields(arg0);
		TF_IDF.readFields(arg0);
	}

	@Override
	public void write(DataOutput arg0) throws IOException {
		unigram.write(arg0);
		TF_IDF.write(arg0);
	}

	@Override
	public String toString(){
		return unigram.toString() + "\t" + TF_IDF.get();
	}

    @Override
    public int hashCode() {
      return unigram.hashCode();
    }
}
