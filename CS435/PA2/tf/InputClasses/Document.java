package tf.InputClasses;

public class Document {
	private int id;
	private String article;

	public Document(String rawText) {
		//split rawText
		String[] splitString = rawText.split("<====>", 3);
		if(splitString.length >= 3) {
			this.id = Integer.parseInt(splitString[1]);
			String articleText = splitString[2];
			article = formatArticle(articleText);
		}
		else {
			this.id = -1;
		}
	}

	public int getDocId() {
		return id;
	}

	public String getArticle() {
		return article;
	}

	private String formatArticle(String articleText) {
		articleText = articleText.toLowerCase();
		articleText = articleText.replaceAll("[^a-z\\s]", "");
		articleText = articleText.replaceAll("\\s+", " ");

		return articleText;
	}
}


