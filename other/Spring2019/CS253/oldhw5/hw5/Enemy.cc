/*
why is gallery = g not declared in this scope?
*/
#include "Enemy.h"
#include "Gallery.h"
#include <cstring>
//#include <iostream>
//#include <vector>
//#include <stdio.h>
//#include <sys/types.h>
//#include <pwd.h>
//#include <fstream>
//#include <unistd.h>
//#include <stdlib.h>
//#include <stdio.h>

#include <string>
//#include <cassert>
//#include <stdexcept>
//#include <sstream>


using namespace std;

Enemy::Enemy(){k = false;}
Enemy::Enemy(const string &keyName)
{
	k = true;
	pushKeys(keys, keyName);
}
bool Enemy::read(istream &in)
{
	eraseVector(s);
	bool returnVal = pushParagraph(s, in);
	if(returnVal)
	{	
		maxSpacing = condenseVector(s);
		checkForKeyErrors(s, keys);
	}
	return returnVal;
}
void Enemy::write(ostream &out)
{
	maxSpacing = condenseVector(s);
	organizeVector(s, n, l, o);
	reallignParagraph(s, maxSpacing,/* keys,*/ out);
	//print(s);
	
	out<< "";
}

string Enemy::field(string key) const
{
	for(auto val:s)
	{
		if(val.find(key) != string::npos)
		{
			string word = val;
			size_t i;
			for(i = 0; i < val.length() && (val[i] != ' ' && val[i] != '\n' && val[i] != '\t' && val[i] != '\v' && val[i] != '\f'); i++)
			{
			}
			for(i = i; i < val.length() && (val[i] == ' ' || val[i] == '\n' || val[i] == '\t' || val[i] == '\v' || val[i] == '\f'); i++)
			{
			}
			word.erase(0, i);
			for(i = 0; i < word.length() && (word[i] != ' ' && word[i] != '\n' && word[i] != '\t' && word[i] != '\v' && val[i] != '\f'); i++)
			{
			}
			word.erase(i, word.length()-i);
			return word;
			
		}
	}
	throw range_error("key " + key + " not found");
	return "";
}
void Enemy::show_name(bool n_)
{
	n = n_;
}
void Enemy::show_name()
{
	n = true;
}

void Enemy::show_other(bool o_)
{
	o = o_;
}
void Enemy::show_other()
{
	o = true;
}

void Enemy::show_link(bool l_)
{
	l = l_;
}
void Enemy::show_link()
{
	l = true;
}

void Enemy::clear()
{
	eraseVector(s);
}

size_t Enemy::size()const
{
	return s.size();
}

bool Enemy::empty()const
{
	if(s.size() == 0)
		return true;
	return false;
}

void Enemy::linkWithGal(Gallery* g)
{
	gallery =g;
}

Enemy* Enemy::link(string relation)const
{
	string desiredKey = "Link"+relation;
	string line;
	if(gallery == nullptr)
	{
		throw runtime_error(relation+ " is not part of a Gallery");
		return nullptr;
	}
	size_t j;
	size_t i;
	for(j = 0; j < gallery->size() && gallery->get(j)->s[0].find(desiredKey) == string::npos; j++)
	{
		for(i = 0; i < gallery->get(j)->s.size() && gallery->get(j)->s[i].find(desiredKey) == string::npos; i++)
		{
			
			/*cout << "line = " << line << '\n';
			cout << "i = " << i << '\n';
			cout << "s[i] = " << s[i] << '\n';
			cout << "desiredKey = " << desiredKey << '\n';*/
			//cout << "s[i].find(desiredKey) = " << s[i].find(desiredKey) << '\n';
		}
		i = 0;
	}
	if(j >= gallery->size())
	{
		throw range_error("this Enemy has no corresponding Link… field, or no enemy with this Name is found in the associated Gallery");
		return nullptr;
	}
		
	line = gallery->get(j)->s[i];
	//line should be equal to the line with "Link"+relation

	line = line.substr(desiredKey.length()+1, line.length()-desiredKey.length());
	//line should be equal to the word after Link key

	Enemy* enp;

	for(j = 0; j < gallery->size() && gallery->get(j)->s[0].find("Name " + line) == string::npos; j++)
	{
		for(i = 0; i < gallery->get(j)->s.size() && gallery->get(j)->s[i].find("Name " + line) == string::npos; i++)
		{
		}
		i = 0;
	}
	enp = gallery->get(i);
	//enp should point to the enemy containing the line "Name " + word after link

	return enp;
}

//private

//Tools

///////////////////
//prints vector s//
///////////////////
void Enemy::print(vector<string> &s_)
{
	for(auto val:s_)
	{
		cout << val << '\n';
	}
}
void Enemy::print(vector<size_t> &s_)
{
	for(auto val:s_)
	{
		cout << val << '\n';
	}
}

////////////////////////////////////
//erase the contents of the vector//
////////////////////////////////////

void Enemy::eraseVector(vector<string> &s_)
{
	while(s_.size() > 0)
	{
		s_.pop_back();
	}
}


//End of Tools//


//main code//

////////////////////////////////
//fills a vector full of keys //
//complain if any errors occur//
////////////////////////////////
void Enemy::pushKeys(vector<string> &keys_, const string &key)
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
void Enemy::openInFile(const string &file, ifstream &in)
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
bool Enemy::getProperLine(const int &input_Index, istream &in, string &input_, bool &endOfCurrentIn_)
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
		endOfCurrentIn_ = false;
		return 0;
	}
}

///////////////////////////////////////////////////////////////////
//reads a paragraph from cin into vector s and returns maxSpacing//
///////////////////////////////////////////////////////////////////
bool Enemy::pushParagraph(vector<string> &s_, istream &in)
{
	string input_;
	bool returnVal = true;
	//getline until you hit end of paragraph
	for(int j = 0; getProperLine(1, in, input_, returnVal) && !((input_ == ""  || input_ == "\n") && s_.size() > 1); j++)
	{
		//cout << input_ << '\n';
		s_.push_back(input_);//add line to s vector
		if(input_ == "" || input_ == "\n" || input_ == "\v" || input_ == "\f" )
			s_.pop_back();
	}
	if(returnVal == false && s_.size() == 0)
		returnVal = false;
	else
		returnVal = true;
	return returnVal;
}

/////////////////////////////////////////////
//reorganizes vector s to be in this order://
//1. Name                                  //
//2. everything other than name and link   //
//3. link                                  //
/////////////////////////////////////////////
size_t Enemy::condenseVector(vector<string> &s_)
{
	size_t maxSpacing_ = 0;
	vector<string> nVector;
	for(size_t j = 0; j < s_.size(); j++)
	{
		if(s_[j][0] == ' ' || s_[j][0] == '\t' || s_[j][0] == '\v' || s_[j][0] == '\f')
		{
			nVector[nVector.size()-1] = nVector[nVector.size()-1].append(s_[j]);
		}
		else if(s[j] == "")
		{
		}
		else
		{
			nVector.push_back(s_[j]);

			//if second word is farther than the others in paragraph, maxSpacing becomes that position
			for(size_t i = 0; i < nVector[nVector.size()-1].length() && nVector[nVector.size()-1][i] != ' '; i++)
			{
				if(i > maxSpacing_)
					maxSpacing_ = i;
			}
		}
	}
	//clear old vector
	while(s_.size() > 0)
		s_.pop_back();
	
	//copy new vector to old vector
	for(size_t i = 0; i < nVector.size(); i++)
		s_.push_back(nVector[i]);
	return maxSpacing_;
}

void Enemy::organizeVector(vector<string> &s_, const bool &n_, const bool &l_, const bool &o_)
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
void Enemy::findSpaces(string &word, const char &char1, vector<size_t> &spacesFound)
{
	char prevChar = word[0];
	for(size_t i = 0; i < word.length(); i++)
	{
		if(word[i] == char1 && prevChar == char1)
			spacesFound.push_back(i);
		prevChar = word[i];
	}
	if(word[word.length()-1] == char1)
		 spacesFound.push_back(word.length()-1);
}

void Enemy::findSpaces(string &word, const char &char1, const char &char2, vector<size_t> &spacesFound)
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

void Enemy::findSpaces(string &word, vector<size_t> &spacesFound)
{
	for(size_t i = 0; i < word.length(); i+=1)
	{
		if(word[i] ==  '\t' || word[i] ==  '\v' || word[i] ==  '\f' || word[i] ==  '\r')
		{
			word[i] = ' ';
		}
	}
	findSpaces(word, ' ', spacesFound);
}

void Enemy::findSpaces(vector<string> &s_, vector<size_t> &spacesFound)
{
	for(size_t i = 0; i+1 <= s_.size(); i++)
	{
		findSpaces(s_[i], spacesFound);
	}
}

////////////////////////////////////////////////////////////////////////////
//check if there are any errors in the keys and complain and set bad if so//
////////////////////////////////////////////////////////////////////////////

void Enemy::checkForKeyErrors(vector<string> &s_, vector<string> &keys_)
{
	if(k)
	{
		//bool keysIsIns_ = false;
		bool nameIsPresent = false;
		string name = "Name";
		string compareWord = "Name Blofeld";
		
		//If the Enemy doesn’t appear in the keyfile, throw a runtime_error, mentioning the bad key. 
		for(size_t i = 0; i+1 <= keys_.size(); i++)
		{
			string word = keys_[i];
			
			for(size_t j = 0; j < s_.size(); j++)
			{
				/*if(word.find(" " + s_[j] + " ")!= string::npos || word.find(s_[j] + " ") == 0)
				{
					keysIsIns_ = true;
				}*/
				
				if(s[j].find(" " + name + " ")!= string::npos || s[j].find(name + " ") == 0)
				{
					nameIsPresent = true;
				}
			}
			/*//no longer need to ensure that an enemy contains each of the keys
			if(keysIsIns_)
			{
				cerr << "key in the Enemy doesn’t appear in the keyfile" << '\n';
				cerr << "word = " << word << '\n';
				throw runtime_error(word);
			}
			*/
		}
		if(nameIsPresent == false)
		{
			cerr << "Name isn't present!" << '\n';
			throw runtime_error("Name");
		}	


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
				throw runtime_error(word);
			}
			else if(found.size() == 0)
			{
				throw runtime_error(word);
			}

			if(!isAlpha(s_[i][0]))
			{
				throw runtime_error(s_[i]);
				//cerr << "Key is not alphabetic in " << programName << "! input_ is " << s_[i] << '\n';	
			}
			if(s_[i].find_last_of(" ") == string::npos || s_[i].find_last_of(" ") == s_[i].length())
			{
				throw runtime_error(s[i]);
				//cerr << "Value is missing in " << programName << '\n';
				//cerr << "SpacesFound.size() = " << spacesFound.size() << '\n';
				//cerr << "spacesFound[1] + 1 = " << spacesFound[1] + 1 << '\n';
				//cerr << "s[i].length() =  " << s_[i].length() << '\n';
			}
		}
	}

}

///////////////////////////////////////////
//returns true if character is alphabetic//
///////////////////////////////////////////
bool Enemy::isAlpha(char c)
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
void Enemy::printRealignedWord(string &word, vector<size_t> &spacesFound, const size_t &maxSpacing_, ostream &out)
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
	
	out << word << '\n';
}

///////////////////////////////////////
//reallign each word in the paragraph//
///////////////////////////////////////
void Enemy::reallignParagraph(vector<string> &s_, const size_t &maxSpacing_, /*vector<string> &keys_,*/ ostream &out)
{
	//checkForKeyErrors(s_, keys_);
	vector<size_t> spacesFound;
	findSpaces(s_, spacesFound);
	for(size_t i = 0; i+1 <= s_.size(); i++)
	{
		//output data if no errors are present
		printRealignedWord(s_[i], spacesFound, maxSpacing_, out);//only prints if bad == false
	}
}

ostream &operator<<(ostream &out, Enemy &rhs)
{
	rhs.write(out);
	return out << "";
}
