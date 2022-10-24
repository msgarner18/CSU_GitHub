// package tf;
package tf.CustomWritables;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.MapWritable;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.Text;

public class UnigramTFWritable implements Writable {
    private Text unigram;
    private DoubleWritable TF_value;
   
    public UnigramTFWritable() {
        this.unigram = new Text();
        this.TF_value = new DoubleWritable();
    }

    public UnigramTFWritable(Text unigram, DoubleWritable TF_value) {
        this.unigram = unigram;
        this.TF_value = TF_value;
    }

    public Text getUnigram() {
        return unigram;
    }

    public DoubleWritable getTF() {
        return TF_value;
    }

    @Override
	public void readFields(DataInput arg0) throws IOException {
		unigram.readFields(arg0);
		TF_value.readFields(arg0);
	}

	@Override
	public void write(DataOutput arg0) throws IOException {
		unigram.write(arg0);
		TF_value.write(arg0);
	}

	@Override
	public String toString(){
		return unigram.toString() + "\t" + TF_value.get();
	}

    @Override
    public int hashCode() {
      return unigram.hashCode();
    }
}

