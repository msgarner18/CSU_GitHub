/*
how do I make .c, .h, and library files?
how do I allow for "const-corectness"
how do I write a copy constructor, assignment operator, and destructor
why is my string comparison not working?
*/
#include <cstring>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <cassert>
#include <stdexcept>
#include <sstream>

using namespace std;
string programName;

class Enemy
{
	public:
		Enemy(){k = false;}
		Enemy(const string &keyName)
		{
			k = true;
			pushKeys(keys, keyName);
		}
		//copy constructor-what is automatic copy constructor?
		/*Enemy(const Enemy &e)
		{
			maxSpacing = e.maxSpacing;
		}*/
		//assignment operator- below output operator
		//destructor
		~Enemy()
		{
			//do I need to put anything here if I don't need to delete anything?
		}
		bool read(istream &in)
		{
			eraseVector(s);
			maxSpacing = pushParagraph(s, 1, in, endOfCurrentIn);
			return !endOfCurrentIn;
		}
		void write()
		{
			organizeVector(s, n, l, o);
			reallignParagraph(s, maxSpacing, keys);
		}
		string field(string key)
		{
			for(auto val:s)
			{
				if(val.find(key) != string::npos)
				{
					string word = val;
					size_t i;
					for(i = 0; i < val.length()&& val[i] != ' '; i++)
					{
					}
					for(i = i; i < val.length()&& val[i] == ' '; i++)
					{
					}
					i+=1;
					word.erase(0, i);
					word.erase(i, word.length()-i);
					cout << word <<  "-" << '\n';
					if(word == "Chimera")
						cout << "good" << '\n';
					return word;
					
				}
			}
			return "";
		}
		void show_name(bool n_)
		{
			n = n_;
		}
		void show_name()
		{
			n = true;
		}

		void show_other(bool o_)
		{
			o = o_;
		}
		void show_other()
		{
			o = true;
		}
		
		void show_link(bool l_)
		{
			l = l_;
		}
		void show_link()
		{
			l = true;
		}

		void clear()
		{
			eraseVector(s);
		}

		size_t size()
		{
			return s.size();
		}

		bool empty()
		{
			if(s.size() == 0)
				return true;
			return false;
		}

		void print()
		{
			for(auto val:s)
			{
				cout << val << '\n';
			}
		}
	private:
		vector<string> s;
		vector<string> keys;
		string input;
		size_t maxSpacing = 0;//position in which second word should be located
		bool n = false;
		bool l = false;
		bool o = false;
		bool k = true;
		bool endOfCurrentIn = false;

		//Tools

		///////////////////
		//prints vector s//
		///////////////////
		void print(vector<string> &s_)
		{
			for(auto val:s_)
			{
				cout << val << '\n';
			}
		}
		void print(vector<size_t> &s_)
		{
			for(auto val:s_)
			{
				cout << val << '\n';
			}
		}

		////////////////////////////////////
		//erase the contents of the vector//
		////////////////////////////////////

		void eraseVector(vector<string> &s_)
		{
			while(s_.size() > 0)
			{
				s_.pop_back();
			}
		}


		//End of Tools//


		//main code//
		//returns argv index of where to find key
		string findk(char* index)
		{
			string word = "";
			word.append(index);
			
			return word;
		}

		void collectOpts(bool &k_, bool &n_, bool &l_, bool &o_, string &key, int &input_Index, int argc, char *argv[])
		{
			char c;
			do
			{
				c = getopt(argc, argv, "-nlok:");
				if(c == 'k')
				{
					k_ = true;
					key = findk(optarg);
					//input_Index = optind;
					cout << key << '\n';
				}
				if(c == 'n')
					n_ = true;
				if(c == 'l')
					l_ = true;
				if(c== 'o')
					o_ = true;
				if(c == 'n'|| c == 'l'||c== 'o' || c == 'k')
					input_Index = optind;
			}while(c != -1 && c != '?');

			if(argc <= input_Index)
				input_Index = 0;
		}

		////////////////////////////////
		//fills a vector full of keys //
		//complain if any errors occur//
		////////////////////////////////
		void pushKeys(vector<string> &keys_, const string &key)
		{
			string input_;
			ifstream keyIn(key);
			
			if(!keyIn.is_open())
			{
				//If it doesn’t, or if any other problem with the file or its contents is encountered, throw a runtime_error, mentioning the filename. 
				throw runtime_error(key);//cerr << "failed to open file " << key << " in pushKeys in program " << programName << '\n';
			}

			while(getline(keyIn, input_))
			{
				keys_.push_back(input_);
				//The keyfile should contain one alphanumeric key per line
				if(input_ == "" || input_ == " ")
					throw runtime_error(input_);
			}
		}

		//////////////////////////////////////////////////
		//open specified file                           //
		//complain and set bad if something bad happened//
		//////////////////////////////////////////////////
		void openInFile(const string &file, ifstream &in)
		{
			if(in.is_open())	
				in.close();

			in.open(file);//change back to i

			if(!in.is_open())
			{
				//Throw a runtime_error, mentioning the filename, upon failure. Don’t add any extra blank lines. 
				throw runtime_error(file);//cerr << "failed to open file " << file << " in openInFile " << programName << '\n';
			}
		}

		////////////////////////////////////////////////////////////////////////
		//calls get line for either cin or in depending on number of arguments//
		////////////////////////////////////////////////////////////////////////
		bool getProperLine(const int &input_Index, istream &in, string &input_, bool &endOfCurrentIn_)
		{
			if(input_Index == 0)
			{
				if(getline(cin, input_))
					return 1;		
				return 0;
			}
			else
			{
				if(getline(in, input_))
					return 1;
				endOfCurrentIn_ = true;
				return 0;
			}
		}

		///////////////////////////////////////////////////////////////////
		//reads a paragraph from cin into vector s and returns maxSpacing//
		///////////////////////////////////////////////////////////////////
		size_t pushParagraph(vector<string> &s_, const int &input_Index, istream &in, bool &endOfCurrentIn_)
		{
			size_t maxSpacing_ = 0;//position in which second word should be located
			string input_;

			//getline until you hit end of paragraph
			for(int j = 0; getProperLine(input_Index, in, input_, endOfCurrentIn_); j++)
			{
				s_.push_back(input_);//add line to s vector
				
				if(input_[0] == '	' || input_[0] == ' ')
				{
					if(j >= 1)
					{
						s_[j-1] = s_[j-1].append(input_);
						s_.pop_back();
						j--;
					}
				}
				else if(input_ == "")
				{
					s_.pop_back();
					j--;
					if(s_.size() >= 1)
					{
						return maxSpacing_;
					}
				}
				else
				{
					//if second word is farther than the others in paragraph, maxSpacing becomes that position
					for(size_t i = 0; i < s_[s_.size()-1].length() && s_[s_.size()-1][i] != ' '; i++)
					{
						if(i > maxSpacing_)
							maxSpacing_ = i;
					}
				}
			}
			return maxSpacing_;
		}

		/////////////////////////////////////////////
		//reorganizes vector s to be in this order://
		//1. Name                                  //
		//2. everything other than name and link   //
		//3. link                                  //
		/////////////////////////////////////////////
		void organizeVector(vector<string> &s_, const bool &n_, const bool &l_, const bool &o_)
		{
			vector<string> newVector;
			bool defaultOpts = (!n_ && !l_ && !o_);	

			//push Names
			if(n_ || defaultOpts)
			{
				for(size_t i = 0; i < s_.size(); i++)
				{
					if(s_[i].find("Name ") == 0 && s_[i].find("Name ") != string::npos)
						newVector.push_back(s_[i]);
				}
			}

			//push others
			if(o_ || defaultOpts)
			{
				for(size_t i = 0; i < s_.size(); i++)
				{
					if(s_[i].find("Link") == 0 && s_[i].find("Link") != string::npos){}
					else if(s_[i].find("Name ") == 0 && s_[i].find("Name ") != string::npos){}
					else
						newVector.push_back(s_[i]);
				}
			}

			//push Links
			if(l_ || defaultOpts)
			{
				for(size_t i = 0; i < s_.size(); i++)
				{
					if(s_[i].find("Link") == 0 && s_[i].find("Link") != string::npos)
						newVector.push_back(s_[i]);
				}
			}	

			//clear old vector
			while(s_.size() > 0)
				s_.pop_back();
			
			//copy new vector to old vector
			for(size_t i = 0; i < newVector.size(); i++)
				s_.push_back(newVector[i]);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//takes a word and fills a vector full of the locations of all the spaces in the word//
		///////////////////////////////////////////////////////////////////////////////////////
		void findSpaces(string &word, const char &char1, vector<size_t> &spacesFound)
		{
			char prevChar = word[0];
			for(size_t i = 0; i < word.length(); i++)
			{
				if(word[i] == char1 && prevChar == char1)
					spacesFound.push_back(i);
				prevChar = word[i];
			}
		}

		void findSpaces(string &word, const char &char1, const char &char2, vector<size_t> &spacesFound)
		{
			for(size_t i = 0; i < word.length(); i+=1)
			{
				if(word[i] == char1)
				{
					word[i] = char2;
				}
			}
			findSpaces(word, char2, spacesFound);
		}

		void findSpaces(string &word, vector<size_t> &spacesFound)
		{
			for(size_t i = 0; i < word.length(); i+=1)
			{
				if(word[i] ==  '	')
				{
					word[i] = ' ';
				}
			}
			findSpaces(word, ' ', spacesFound);
		}

		////////////////////////////////////////////////////////////////////////////
		//check if there are any errors in the keys and complain and set bad if so//
		////////////////////////////////////////////////////////////////////////////

		void checkForKeyErrors(vector<string> &s_, vector<string> &keys_)
		{
			if(k)
			{
				/*
				//If the Enemy doesn’t appear in the keyfile, throw a runtime_error, mentioning the bad key. 
				for(size_t i = 0; i+1 <= keys_.size(); i++)
				{
					string word = keys_[i];
					bool keysIsIns_ = false;
					for(size_t j = 0; j < s_.size(); j++)
					{
						if(word.find(" " + s_[j] + " ")!= string::npos || word.find(s_[j] + " ") == 0)
						{
							keyIsIns_ = true;
						}
					}
		
				}
				*/
				//If duplicate keys are encountered, throw a runtime_error, mentioning the bad key.
				//If no Name key is read, throw a runtime_error.
				for(size_t i = 0; i+1 <= s_.size(); i++)
				{
					vector<string> found;
					string word = s_[i];
					//bool keyIsIns_ = false;
					for(size_t j = 0; j < keys_.size(); j++)
					{
						if(word.find(" " + keys_[j] + " ")!= string::npos || word.find(keys_[j] + " ") == 0)//checks if it's an individual word, or starts the line
						{
							found.push_back(keys_[j]);
						}
						if(word.find(keys_[j] + " ") != word.rfind(keys_[j] + " "))
						{
							found.push_back(keys_[j]);
						}
					}
					
					if(found.size() > 1)
					{
						cerr << programName << ": " << word << " has too many keys! \n";
					}
					else if(found.size() == 0)
					{
						cerr << programName << ": " << "Key is missing in " << word << "! \n";
					}
				}
			}

		}

		///////////////////////////////////////////
		//returns true if character is alphabetic//
		///////////////////////////////////////////
		bool isAlpha(char c)
		{
			bool solution;
			if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			{
				solution = true;
			}
			else
			{
				solution = false;
			}
			return solution;
		}


		//////////////////////////////////////////////////////////////////
		//returns a word that is lined up with the rest of the paragraph//
		//////////////////////////////////////////////////////////////////
		void printRealignedWord(string &word, vector<size_t> &spacesFound, const size_t &maxSpacing_)
		{	
			int firstSpace = word.find_first_of(" ");
			int max = maxSpacing_;
			if(spacesFound.size() > 0)
			{
				for(size_t j = 0; j < spacesFound.size(); j+=1)
				{
					word.erase(spacesFound[j]-j, 1);
				}
			}

			for(int i = 0; i <= max-firstSpace; i++)
			{
				word.insert(firstSpace, " ");//maxSpacing-firstSpaceFound times
			}
			cout << word << '\n';
		}

		///////////////////////////////////////
		//reallign each word in the paragraph//
		///////////////////////////////////////
		void reallignParagraph(vector<string> &s_, const size_t &maxSpacing_, vector<string> &keys_)
		{
			checkForKeyErrors(s_/*[i]*/, keys_);
			for(size_t i = 0; i+1 <= s_.size(); i++)
			{
				vector<size_t> spacesFound;
				findSpaces(s_[i], spacesFound);
				
				//check for errors in data
				
				

				if(!isAlpha(s_[i][0]))
				{
					cerr << "Key is not alphabetic in " << programName << "! input_ is " << s_[i] << '\n';	
				}
				if(s_[i].find_last_of(" ") == string::npos || s_[i].find_last_of(" ") == s_[i].length())
				{
					cerr << "Value is missing in " << programName << '\n';
					cerr << "SpacesFound.size() = " << spacesFound.size() << '\n';
					cerr << "spacesFound[1] + 1 = " << spacesFound[1] + 1 << '\n';
					cerr << "s[i].length() =  " << s_[i].length() << '\n';
				}
				//output data if no errors are present
				printRealignedWord(s_[i], spacesFound, maxSpacing_);//only prints if bad == false
			}
		}
};

ostream &operator<<(ostream &os, Enemy &rhs)
{
	rhs.write();
	return os << "";
}

//assignment operator
/*ostream &operator=(const Enemy &e1, const Enemy &e2)
{
	
}*/
/*
int main()
{

    const Enemy a;
    assert(a.empty());
    assert(a.size() == 0);
	cout << "1" << '\n';
    ifstream lair("pony-villains");
    assert(lair);
    Enemy b("keys"), c, d;


    bool got_b = b.read(lair);

    bool got_c = c.read(lair);
    bool got_d = d.read(lair);
cout << "2" << '\n';
    assert(got_b);
	cout << "test 1" << '\n';
    assert(b.size() == 5);
	cout << "test 2" << '\n';
    assert(!b.empty());
cout << "3" << '\n';
    assert(got_c);
    assert(c.size() == 4);
    assert(!c.empty());
cout << "4" << '\n';
    assert(!got_d);
cout << "5" << '\n';
    cout << b << "———–—––—–——–———–\n" << c;
cout << "6" << '\n';
    b = c;
    assert(b.size() == 4);
cout << "7" << '\n';
    assert(b.field("BodyType"s) == "Chimera");
cout << "8" << '\n';
    c.show_other(false);
    cout << "::::::::\n" << c;
    c.show_other();
    c.show_link(false);
    cout << "********\n" << c;
cout << "9" << '\n';
    stringstream iss("\n\n\nName \t\v\f xyz  \n\n\n");
    assert(c.read(iss));
    assert(c.size() == 1);
    assert(c.field("Name") == "xyz");
    ostringstream oss;
    assert(oss << c);
    assert(oss.str() == "Name xyz\n");
cout << "10" << '\n';
    // Try a field that’s not there:
    try {
        string s = b.field("foobar");
        cerr << "ERROR: .field() worked?\n";
    }
    catch (const range_error &err) {
        cout << "Good, range_error = " << err.what() << '\n';
    }
    catch (const exception &err) {
        cerr << "ERROR: exception = " << err.what() << '\n';
    }
    catch (...) {
        cerr << "ERROR: What the ☆⚡🔪☠§❢💣 did you throw?\n";
    }

    return 0;
}
*/
/*
class Foo
{
	public:
		Foo() : c(1), d(2) {}
		void zip() {cout << c << '\n';}
	private:
		int c, d;
};

int main()
{
	Foo f;
	f.zip();
}
*/

/*
class Ratio
{
	public:
		Ratio(int a, int b) : top(a), bottom(b) {}
		double get_real() const
		{
			return top / double(bottom);
		}
	private:
		int top, bottom;
};

void show_ratio(const Ratio &r)
{
	cout << r.get_real() << '\n';
}

int main()
{
	Ratio f(355,113);
	cout << f.get_real() << '\n';
	//show_ratio(f);
}
*/

/*
class Foo
{
	public:
		Foo() { counter++; }
		~Foo() { counter--; }
		int get_count() const { return counter; }
	private:
		static int counter;
};
int Foo::counter = 0;

int main()
{
	Foo a, b, c, d, e;
	cout << e.get_count() << '\n';
}
*/

/*
class Quoted
{
	string s;
	public:
		Quoted(const string &word) : s(word) { }//accessor
		string get() const; // declaration only
};
string Quoted::get() const
{
	return "“" + s + "”";
}
ostream &operator<<(ostream &os, const Quoted &rhs)
{
	return os << rhs.get();
}

int main()
{
	Quoted name("Slartibartfast");
	cout << name.Quoted("hi") << '\n';
	cout << "I am " << name << ".\n";
}
*/


/*class Point
{
	public:
		Point(int a, int b) {x = a; y = b;}// ctor
		int get_x() const { return x; }    // accessor
		int get_y() const { return y; }
		void go_right() { x++; }           // mutator
	private:
		int x, y;
};

ostream &operator<<(ostream &out, const Point &p)
{
	return out << p.get_x() << ',' << p.get_y();
}

int main()
{
	Point p(12, 34);
	cout << p << '\n';  // invoke operator<<
	p.go_right();
	cout << p << '\n';  // invoke operator<<
}*/
