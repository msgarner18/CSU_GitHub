#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cassert>
#include <stdexcept>
#include <sstream>

class Enemy
{
	public:
		//Enemy();
		Enemy(const std::string &keyName);
		//copy constructor-what is automatic copy constructor?
		/*Enemy(const Enemy &e)
		{
			maxSpacing = e.maxSpacing;
		}*/
		//assignment operator- below output operator
		//destructor
		//~Enemy();
		bool read(std::istream &in);
		void write(std::ostream &out);
		std::string field(std::string key) const;
		void show_name(bool n_);
		void show_name();
		void show_other(bool o_);
		void show_other();
		void show_link(bool l_);
		void show_link();
		void clear();
		size_t size()const;
		bool empty()const;
		//*Enemy link(std::string relation);

	private:
		std::vector<std::string> s;
		std::vector<std::string> keys;
		std::string input;
		size_t maxSpacing = 0;//position in which second word should be located
		bool n = true;
		bool l = true;
		bool o = true;
		bool k = true;
		bool endOfCurrentIn = false;

		//Tools

		///////////////////
		//prints vector s//
		///////////////////
		void print(std::vector<std::string> &s_);
		void print(std::vector<size_t> &s_);

		////////////////////////////////////
		//erase the contents of the vector//
		////////////////////////////////////

		void eraseVector(std::vector<std::string> &s_);


		//End of Tools//


		//main code//
		

		////////////////////////////////
		//fills a vector full of keys //
		//complain if any errors occur//
		////////////////////////////////
		void pushKeys(std::vector<std::string> &keys_, const std::string &key);

		//////////////////////////////////////////////////
		//open specified file                           //
		//complain and set bad if something bad happened//
		//////////////////////////////////////////////////
		void openInFile(const std::string &file, std::ifstream &in);

		////////////////////////////////////////////////////////////////////////
		//calls get line for either cin or in depending on number of arguments//
		////////////////////////////////////////////////////////////////////////
		bool getProperLine(const int &input_Index, std::istream &in, std::string &input_, bool &endOfCurrentIn_);

		///////////////////////////////////////////////////////////////////
		//reads a paragraph from cin into vector s and returns maxSpacing//
		///////////////////////////////////////////////////////////////////
		bool pushParagraph(std::vector<std::string> &s_, std::istream &in);

		/////////////////////////////////////////////
		//reorganizes vector s to be in this order://
		//1. Name                                  //
		//2. everything other than name and link   //
		//3. link                                  //
		/////////////////////////////////////////////
		size_t condenseVector(std::vector<std::string> &s_);
		void organizeVector(std::vector<std::string> &s_, const bool &n_, const bool &l_, const bool &o_);
		///////////////////////////////////////////////////////////////////////////////////////
		//takes a word and fills a vector full of the locations of all the spaces in the word//
		///////////////////////////////////////////////////////////////////////////////////////
		void findSpaces(std::string &word, const char &char1, std::vector<size_t> &spacesFound);

		void findSpaces(std::string &word, const char &char1, const char &char2, std::vector<size_t> &spacesFound);

		void findSpaces(std::string &word, std::vector<size_t> &spacesFound);

		void findSpaces(std::vector<std::string> &s_, std::vector<size_t> &spacesFound);

		////////////////////////////////////////////////////////////////////////////
		//check if there are any errors in the keys and complain and set bad if so//
		////////////////////////////////////////////////////////////////////////////

		void checkForKeyErrors(std::vector<std::string> &s_, std::vector<std::string> &keys_);

		///////////////////////////////////////////
		//returns true if character is alphabetic//
		///////////////////////////////////////////
		bool isAlpha(char c);


		//////////////////////////////////////////////////////////////////
		//returns a word that is lined up with the rest of the paragraph//
		//////////////////////////////////////////////////////////////////
		void printRealignedWord(std::string &word, std::vector<size_t> &spacesFound, const size_t &maxSpacing_, std::ostream &out);

		///////////////////////////////////////
		//reallign each word in the paragraph//
		///////////////////////////////////////
		void reallignParagraph(std::vector<std::string> &s_, const size_t &maxSpacing_, std::vector<std::string> &keys_, std::ostream &out);
};

std::ostream &operator<<(std::ostream &os, Enemy &rhs);
#endif
