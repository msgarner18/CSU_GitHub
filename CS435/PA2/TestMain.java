// package tf.Testing;

// for testing
import java.util.Scanner;
import java.io.File;
// import tf.InputClasses.Document;

public class TestMain {
    public static void main(String[] args) throws Exception {
        Scanner myScanner = new Scanner(new File("IOFolders/input/test.txt"));
        String rawText = myScanner.useDelimiter("\\Z").next();
        Document doc = new Document(rawText);
        int docId = doc.getDocId();
        String article = doc.getArticle();
        System.out.println("docId:");
        System.out.println(docId);
        System.out.println("article:");
        System.out.println(article);
    }
}
