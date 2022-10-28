package tf.CustomWritables;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.DoubleWritable;

public class DocIdTFWritable implements Writable {
    private IntWritable docId;
    private DoubleWritable TF_value;
   
    public DocIdTFWritable() {
        this.docId = new IntWritable();
        this.TF_value = new DoubleWritable();
    }

    public DocIdTFWritable(IntWritable docId, DoubleWritable TF_value) {
        this.docId = docId;
        this.TF_value = TF_value;
    }

    public IntWritable getDocId() {
        return docId;
    }

    public DoubleWritable getTF() {
        return TF_value;
    }

    @Override
	public void readFields(DataInput arg0) throws IOException {
        docId.readFields(arg0);
		TF_value.readFields(arg0);
	}

	@Override
	public void write(DataOutput arg0) throws IOException {
		docId.write(arg0);
		TF_value.write(arg0);
	}

	@Override
	public String toString(){
        return docId.toString() + "\t" + TF_value.get();
	}

    @Override
    public int hashCode() {
      return docId.hashCode();
    }
}
