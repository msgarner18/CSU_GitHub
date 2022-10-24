package tf.CustomWritables;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.DoubleWritable;

public class UnigramTF_IDFWritable implements Writable {
    private Text unigram;
    private DoubleWritable TF_IDF_value;
   
    public UnigramTF_IDFWritable() {
        this.unigram = new Text();
        this.TF_IDF_value = new DoubleWritable();
    }

    public UnigramTF_IDFWritable(Text unigram, DoubleWritable TF_IDF_value) {
        this.unigram = unigram;
        this.TF_IDF_value = TF_IDF_value;
    }

    public Text getDocId() {
        return unigram;
    }

    public DoubleWritable getTF_IDF() {
        return TF_IDF_value;
    }

    @Override
	public void readFields(DataInput arg0) throws IOException {
        unigram.readFields(arg0);
		TF_IDF_value.readFields(arg0);
	}

	@Override
	public void write(DataOutput arg0) throws IOException {
		unigram.write(arg0);
		TF_IDF_value.write(arg0);
	}

	@Override
	public String toString() {
        return unigram.toString() + "\t" + TF_IDF_value.get();
	}

    @Override
    public int hashCode() {
      return unigram.hashCode();
    }
}
