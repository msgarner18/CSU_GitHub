// package tf.MapReduce.B.job1;

// import java.util.StringTokenizer;
// import org.apache.hadoop.io.IntWritable;
// import org.apache.hadoop.io.DoubleWritable;
// import org.apache.hadoop.io.Text;

// import java.util.HashMap;
// import java.util.Map;
// import java.util.ArrayList;

// public class Filler {
//     private static void addTF_IDF(Map<Text, DoubleWritable> TF_IDFs, IntWritable docId) {
//         String rawText = new String(content.toString().substring(2));
//         StringTokenizer itr = new StringTokenizer(rawText);

//         Text unigram = new Text(itr.nextToken());
//         double TF_IDF = Double.parseDouble(itr.nextToken());

//         TF_IDFS.put(new Text(docId.get()+unigram.toString()), new DoubleWritable(TF_IDF));
//     }

//     private static void addSentence(Map<IntWritable, ArrayList<String>> sentences, IntWritable docId) {
//         String sentence = content.toString().substring(2);
//         ArrayList<String> list = sentences.get(docId);
//         if(list == null)
//             list = new ArrayList<String>();
//         list.add(new String(sentence));

//         sentences.put(docId, list);
//     }
// }
