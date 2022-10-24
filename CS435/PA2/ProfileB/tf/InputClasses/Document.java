// package tf;
package tf.InputClasses;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Document {
    private int id;
    private String article;
    // private static final String docFreqPattern = ".+<====>[0-9]+<====>.+";
    
    // rawText is the line id \t body
    public Document(String rawText) {
        id = parseId(rawText);
        
        article = parseArticle(rawText);
        article = formatArticle(article);
    }

    private int parseId(String rawText) {
        Pattern idPattern = Pattern.compile("<====>([0-9]+)<====>");
        Matcher idMatcher = idPattern.matcher(rawText);
        
        if(idMatcher.find()){
            String idMatch = idMatcher.group(1);
            return Integer.parseInt(idMatch);
        }

        return -1;
    }

    private String parseArticle(String rawText) {
        String[] splitString = rawText.split(".+<====>[0-9]+<====>", 2);
        if(splitString.length == 2)
            return splitString[1];
        return "";
    }

    public int getId() {
        return this.id;
    }

    public String getArticle() {
        return this.article;
    }

    private String formatArticle(String article) {
        article = article.toLowerCase();
        article = article.replaceAll("/", " ");
        article = article.replaceAll("\\s+", " ");
        article = article.replaceAll("[^a-z ]", "");

        return article;
    }
}
