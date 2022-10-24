// package ngram;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.MapWritable;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.Text;

public class VolumeWriteable implements Writable {
	private IntWritable count;
	private MapWritable volumeIds;
	
	public VolumeWriteable(String key, IntWritable count){
		this.count = count;
		volumeIds = new MapWritable();
		this.insertMapValue(new Text(key), new IntWritable());
	}

	public VolumeWriteable() {
		volumeIds = new MapWritable();
		count = new IntWritable(1);
	}

	public IntWritable getCount() {
		return count;
	}

	public MapWritable getVolumeIds() {
		return volumeIds;
	}

	public void set(MapWritable volumeIds, IntWritable count){
		this.volumeIds = volumeIds;
		this.count = count;
	}

	public void insertMapValue(Text key, IntWritable value){
		this.volumeIds.put(key, value);
	}

	@Override
	public void readFields(DataInput arg0) throws IOException {
		count.readFields(arg0);
		volumeIds.readFields(arg0);
	}

	@Override
	public void write(DataOutput arg0) throws IOException {
		count.write(arg0);
		volumeIds.write(arg0);
	}

	@Override
	public String toString(){
		return count.get() + "\t" + volumeIds.size();
	}

    @Override
    public int hashCode() {
      return volumeIds.hashCode();
    }
}
