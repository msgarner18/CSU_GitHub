// package ngram;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

//IMPORTANT: make sure you understand ALL code and can EXPLAIN it
//IMPORTANT: make sure you understand the role of EACH class
public class Book {
	private String headerText, bodyText, author, year;
	private int ngramCount;

	public Book(String rawText, int ngramCount) {
		this.ngramCount = ngramCount;
		
		//split rawText
		String[] splitString = rawText.split("\\*\\*\\* START OF THIS PROJECT GUTENBERG EBOOK .* \\*\\*\\*\\R", 2);

		bodyText = splitString[1];
		headerText = splitString[0];

		//format
		bodyText = formatBook(bodyText);
		author = parseAuthor(headerText);
		year = parseYear(headerText);
	}

	private String parseAuthor(String headerText) {
		Pattern authorPattern = Pattern.compile("Author: *(.*)\\R");
		Matcher authorMatcher = authorPattern.matcher(headerText);
		
		if(authorMatcher.find()){
			String authorMatch = authorMatcher.group(1);
			return authorMatch;
		}

		return "";
	}

	private String parseYear(String headerText) {
		Pattern yearPattern = Pattern.compile("Release Date:.*([0-9][0-9][0-9][0-9])");
		Matcher yearMatcher = yearPattern.matcher(headerText);
		
		if(yearMatcher.find()){
			String yearMatch = yearMatcher.group(1);
			return yearMatch;
		}

		return "";
	}

	public String getBookAuthor() {
		return author;
	}

	public String getBookYear() {
		return year;
	}

	public String getBookHeader() {
		return headerText;
	}

	public String getBookBody() {
		return bodyText;
	}

	private String formatHyphens(String s) {
		// replace multiple hyphens with a single hyphen
		s = s.replaceAll("--+", "-");
		
		// "-" is not an allowable word on its own
		s = s.replaceAll(" - ", " ");

		// "-word" and "word-"" -> word
		s = s.replaceAll("- ", " ");
		s = s.replaceAll(" -", " ");

		return s;
	}

	private String formatSentenceBreaks(String s) {
		if(ngramCount >= 2) {
			
			s = s.replaceAll("@", " _END_ _START_ ");
			if(s.substring(s.length() - 8).compareTo("_START_ ") == 0)
				s = "_START_ " + s.substring(0, s.lastIndexOf(" _START_ "));
			else
				s = "_START_ " + s + " _END_";
		}
		else {
			s = s.replaceAll("@", " ");
		}

		return s;
	}

	private String formatBook(String bookText) {
		// Ensure that every word can be identified by "[space]word[space]"
		bookText = " " + bookText + " ";
		
		// convert to lower case
		bookText = bookText.toLowerCase();

		//remove @ characters so I can use @ as my sentence break character
		bookText = bookText.replaceAll("@", "");

		// replace all whitespace type characters with space characters
		bookText = bookText.replaceAll("\\s+", " ");
		
		// replace end of sentence with sentence break character @
		bookText = bookText.replaceAll("[.!?] ", "@");
		
		// remove all characters except for lower-case-letter, space, hyphen, and sentence break characters(@)
		bookText = bookText.replaceAll("[^@a-z -]", ""); // remove unallowed characters

		// replace all @ with _START_ and _END_ flags or " " for unigrams
		bookText = this.formatSentenceBreaks(bookText);
		
		// correct invalidly hyphenated words
		bookText = this.formatHyphens(bookText);

		// cleanup leftover space from deleted words
		bookText = bookText.replaceAll("\\s+", " ");

		return bookText;
	}
}

