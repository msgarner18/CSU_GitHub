import java.util.Scanner; // for testing
import java.io.File; // for testing

import java.util.ArrayList;
import java.util.StringTokenizer;

// import org.apache.hadoop.io.MapWritable;
// import org.apache.hadoop.io.IntWritable;
// import org.apache.hadoop.io.Text;

// import org.apache.hadoop.io.Writable;


public class Main {
    public static void main(String[] args) throws Exception {
		TestClass test = new TestClass();
		test.map();
		test.map();
		test.map();
		// System.out.println(CurrentVolume++);
		// System.out.println(CurrentVolume);
		// VolumeWriteable volInput = new VolumeWriteable();
		// VolumeWriteable volInput2 = new VolumeWriteable();
		// volInput.insertMapValue(new IntWritable(1), new IntWritable(1));
		// volInput2.insertMapValue(new IntWritable(2), new IntWritable(1));
		// MapWritable newMap = new MapWritable();
		// newMap.putAll(volInput.getVolumeIds());
		// newMap.putAll(volInput2.getVolumeIds());
		// System.out.println(newMap.size());
		//map
		// ArrayList<VolumeWriteable> volumes = new ArrayList<VolumeWriteable>();

		// IntWritable one = new IntWritable(1);
		// IntWritable two = new IntWritable(2);
		// IntWritable [] nums = {one, one, one, two, two, two};
		// for(IntWritable num : nums) {
		// 	VolumeWriteable vol = new VolumeWriteable();
		// 	vol.insertMapValue(num, one);
		// 	volumes.add(vol);
		// }
		// System.out.println("Old Volumes");
		// for(VolumeWriteable vol : volumes) {
		// 	System.out.println(vol);
		// }
		
		// //reduce
		// VolumeWriteable resultVolume = new VolumeWriteable(new MapWritable(), new IntWritable(0));

		// for(VolumeWriteable vol : volumes) {
		// 	resultVolume.incrementCount(vol.getCount().get());

	
		// 	resultVolume.getVolumeIds().putAll(vol.getVolumeIds());
		// }

		// System.out.println("Reduced Volume");
		// System.out.println(resultVolume);

		// Scanner myScanner = new Scanner(new File("book.txt"));
		// String myRawText = myScanner.useDelimiter("\\Z").next();
		// // System.out.println(myRawText);
		// int profileNum = 2;
		// Book myBook = new Book(myRawText, profileNum);
		
		
		// System.out.println("Author:");
		// System.out.println(myBook.getBookAuthor());
		// System.out.println();

		// System.out.println("Year:");
		// System.out.println(myBook.getBookYear());
		// System.out.println();

		// System.out.println("HeaderText:");
		// System.out.println(myBook.getBookHeader());
		// System.out.println();
		
		// System.out.println("Body:");
		// System.out.println(myBook.getBookBody());
		// System.out.println();


		// System.out.println("Mapping...");

		// StringTokenizer itr = new StringTokenizer(myBook.getBookBody());
		// StringTokenizer itr2 = new StringTokenizer(myBook.getBookBody());
		// String s;
		// if(profileNum == 2 && itr.hasMoreTokens())
		// 	s = itr.nextToken();
		// while (itr.hasMoreTokens()) {
		// 	s = itr.nextToken();
			
		// 	if(profileNum == 2)
		// 		s = itr2.nextToken() + " " + s;
				
		// 	System.out.println(s);

		// }

		// myScanner.close();
	}
}
