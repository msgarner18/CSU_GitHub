package tf.InputClasses;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

//IMPORTANT: make sure you understand ALL code and can EXPLAIN it
//IMPORTANT: make sure you understand the role of EACH class
public class Document {
	private int id;
	private String article;

	public Document(String rawText) {
		
		//split rawText
		String[] splitString = rawText.split("<====>", 3);

		this.id = Integer.parseInt(splitString[1]);
		article = splitString[2];
	}

	public int getDocId() {
		return id;
	}

	public String getArticle() {
		return article;
	}

	private String formatArticle(String articleText) {
		articleText = articleText.toLowerCase();
		articleText = articleText.replaceAll("\\s+", " ");
		articleText = articleText.replaceAll("[^a-z ] ", "");

		return articleText;
	}
}


