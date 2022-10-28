// package tf;
package tf.InputClasses;

// import java.util.regex.Matcher;
// import java.util.regex.Pattern;

public class SentenceParser {
    private int index;
    private String[] sentences;
    
    // rawText is the line id \t body
    public SentenceParser(String rawText) {
        index = 0;
        String article = removeId(rawText);
        sentences = tokenizeArticle(article);

    }

    private String removeId(String rawText) {
        String[] splitString = rawText.split("<====>[0-9]+<====>\\s*", 2);
        if(splitString.length == 2)
            return splitString[1];
        return "";
    }

    private String preProcessSentence(String sentence) {
        sentence = sentence.toLowerCase();
        // sentence = sentence.replaceAll("/", " ");
        // sentence = sentence.replaceAll("\\s+", " ");
        // sentence = sentence.replaceAll("[^a-z ]", "");
		sentence = sentence.replaceAll("[^a-z\\s]", "");
		sentence = sentence.replaceAll("\\s+", " ");
        if(sentence.length() > 0 && sentence.charAt(0) == ' ')
            sentence = sentence.substring(1);
        
        return sentence;
    }

    private String[] tokenizeArticle(String article) {
        return article.split("\\. ", -1);
    }

    public boolean hasMoreSentences() {
        return index < sentences.length;
    }

    public String next() {
        return preProcessSentence(sentences[index++]);
    }
}
