
/*
how do I check to see whether a file is a key or not?
*/
#include "Enemy.h"
#include "Gallery.h"
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

Gallery::Gallery()
{
	throw runtime_error("Gallery() is not defined for this class");
}
Gallery::Gallery(string filename)
{
	throw runtime_error("Gallery("+filename+") is not defined for this class");
}
Gallery::Gallery(string key, string filename)
{
	string input;
	//bool bad = false;

	ifstream keyIn(key);
	//if(!keyIn.is_open()){bad = true; throw runtime_error("can't open file " + key);}
	//else
	//{
		getline(keyIn, input);
		if(isOneWord(input))
		{
			keyTotal ++;
		}
		keyIn.close();
	//}

	ifstream fileIn(filename);
	//if(!fileIn.is_open()){bad = true;throw runtime_error("can't open file " + filename);}
	//else
	//{
		getline(fileIn, input);
		if(isOneWord(input))
		{
			swap(key, filename);
			keyTotal ++;
		}
		fileIn.close();
	//}

	//if(!bad)
	//{
		if(keyTotal < 1)
			throw runtime_error("no key file in Gallery("+key+", "+filename+")");
		else if(keyTotal > 1)
			throw runtime_error("too many key files in Gallery("+key+", "+filename+")");
		else
		{
			read(filename, key);
			//cout << enemyVector[0] << '\n';
		}
	//}
}
Gallery::Gallery(string key, string filename, string filename2)
{
	string input;
	
	ifstream keyIn(key);
	getline(keyIn, input);
	if(isOneWord(input))
	{
		keyTotal ++;
	}
	keyIn.close();
	
	ifstream fileIn(filename);
	getline(fileIn, input);
	if(isOneWord(input))
	{
		swap(key, filename);
		keyTotal ++;
	}
	fileIn.close();
	
	ifstream fileIn2(filename2);
	getline(fileIn2, input);
	if(isOneWord(input))
	{
		swap(key, filename2);
		keyTotal ++;
	}
	fileIn2.close();

	if(keyTotal < 1)
		throw runtime_error("no key file in Gallery("+key+", "+filename+", "+filename2+")");
	else if(keyTotal > 1)
		throw runtime_error("too many key files in Gallery("+key+", "+filename+", "+filename2+")");
	else
	{
		read(filename, key);
		read(filename2, key);
	}
}

Gallery::Gallery(string key, string filename, string filename2, string filename3)
{
	string input;
	
	ifstream keyIn(key);
	getline(keyIn, input);
	if(isOneWord(input))
	{
		keyTotal ++;
	}
	keyIn.close();
	
	ifstream fileIn(filename);
	getline(fileIn, input);
	if(isOneWord(input))
	{
		swap(key, filename);
		keyTotal ++;
	}
	fileIn.close();
	
	ifstream fileIn2(filename2);
	getline(fileIn2, input);
	if(isOneWord(input))
	{
		swap(key, filename2);
		keyTotal ++;
	}
	fileIn2.close();
	
	ifstream fileIn3(filename3);
	getline(fileIn3, input);
	if(isOneWord(input))
	{
		swap(key, filename3);
		keyTotal ++;
	}
	fileIn3.close();

	if(keyTotal < 1)
		throw runtime_error("no key file in Gallery("+key+", "+filename+", "+filename2+", "+filename3+")");
	else if(keyTotal > 1)
		throw runtime_error("too many key files in Gallery("+key+", "+filename+", "+filename2+", "+filename3+")");
	else
	{
		read(filename, key);
		read(filename2, key);
		read(filename3, key);
	}
}

Gallery::Gallery(string key, string filename, string filename2, string filename3, string filename4)
{
	string input;
	
	ifstream keyIn(key);
	getline(keyIn, input);
	if(isOneWord(input))
	{
		keyTotal ++;
	}
	keyIn.close();
	
	ifstream fileIn(filename);
	getline(fileIn, input);
	if(isOneWord(input))
	{
		swap(key, filename);
		keyTotal ++;
	}
	fileIn.close();
	
	ifstream fileIn2(filename2);
	getline(fileIn2, input);
	if(isOneWord(input))
	{
		swap(key, filename2);
		keyTotal ++;
	}
	fileIn2.close();
	
	ifstream fileIn3(filename3);
	getline(fileIn3, input);
	if(isOneWord(input))
	{
		swap(key, filename3);
		keyTotal ++;
	}
	fileIn3.close();

	ifstream fileIn4(filename4);
	getline(fileIn4, input);
	if(isOneWord(input))
	{
		swap(key, filename4);
		keyTotal ++;
	}
	fileIn4.close();

	if(keyTotal < 1)
		throw runtime_error("no key file in Gallery("+key+", "+filename+", "+filename2+", "+filename3+", "+filename4+")");
	else if(keyTotal > 1)
		throw runtime_error("too many key files in Gallery("+key+", "+filename+", "+filename2+", "+filename3+", "+filename4+")");
	else
	{
		read(filename, key);
		read(filename2, key);
		read(filename3, key);
		read(filename4, key);
	}
}
Gallery::Gallery(string key, string filename, string filename2, string filename3, string filename4, string filename5)
{
	string input;
	
	ifstream keyIn(key);
	getline(keyIn, input);
	if(isOneWord(input))
	{
		keyTotal ++;
	}
	keyIn.close();
	
	ifstream fileIn(filename);
	getline(fileIn, input);
	if(isOneWord(input))
	{
		swap(key, filename);
		keyTotal ++;
	}
	fileIn.close();
	
	ifstream fileIn2(filename2);
	getline(fileIn2, input);
	if(isOneWord(input))
	{
		swap(key, filename2);
		keyTotal ++;
	}
	fileIn2.close();
	
	ifstream fileIn3(filename3);
	getline(fileIn3, input);
	if(isOneWord(input))
	{
		swap(key, filename3);
		keyTotal ++;
	}
	fileIn3.close();

	ifstream fileIn4(filename4);
	getline(fileIn4, input);
	if(isOneWord(input))
	{
		swap(key, filename4);
		keyTotal ++;
	}
	fileIn4.close();
	
	ifstream fileIn5(filename5);
	getline(fileIn5, input);
	if(isOneWord(input))
	{
		swap(key, filename5);
		keyTotal ++;
	}
	fileIn5.close();

	if(keyTotal < 1)
		throw runtime_error("no key file in Gallery("+key+", "+filename+", "+filename2+", "+filename3+", "+filename4+", "+filename5+")");
	else if(keyTotal > 1)
		throw runtime_error("too many key files in Gallery("+key+", "+filename+", "+filename2+", "+filename3+", "+filename4+", "+filename5+")");
	else
	{
		read(filename, key);
		read(filename2, key);
		read(filename3, key);
		read(filename4, key);
		read(filename5, key);
	}
}

void Gallery::read(string filename, string key)
{
	Enemy enemy(key);
	ifstream in(filename);
	
	while(enemy.read(in))//runtime error is thrown inside of this method
	{
		add(enemy);
	}
}
void Gallery::add(Enemy &enemy)
{
	enemy.linkWithGal(this);
	enemyVector.push_back(enemy);
}
void Gallery::clear()
{
	eraseVector(enemyVector);
}
size_t Gallery::size()const
{
	return enemyVector.size();
}
bool Gallery::empty()const
{
	return (enemyVector.size()==0);
}
const Enemy* Gallery::get(size_t n)const
{
	const Enemy* enemyptr = nullptr;
	if(this->size() > n)
	{
		enemyptr = &enemyVector[n];
	}
	else
	{
		//cout << "this->size() = " << this->size() << '\n';
		throw range_error("range is: " + this->size());
	}
	return enemyptr;
}
Enemy* Gallery::get(size_t n)
{
	Enemy* enemyptr = nullptr;
	if(this->size() > n)
	{
		enemyptr = &enemyVector[n];
	}
	else
	{
		//cout << "this->size() = " << this->size() << '\n';
		throw range_error("range is: " + this->size());
	}

	return enemyptr;
}

//private

void Gallery::eraseVector(vector<Enemy> &e)
{
	while(e.size() > 0)
	{
		e.pop_back();
	}
}

void Gallery::swap(string &one, string &two)
{
	string temp;
	temp = one;
	one = two;
	two = temp;
}

bool Gallery::isOneWord(const string &word)
{
	bool returnVal;
	if(word.find_last_of(" ")+1 == word.length() || word.find_last_of(" ") == string::npos)//one word or none
	{
		returnVal = true;
	}
	else
	{
		returnVal = false;
	}

	if(returnVal && word == "")
	{
		returnVal = false;
	}

	return returnVal;
}

Enemy Gallery::operator[](size_t n)
{
	Enemy* enemyptr = this->get(n);

	return *enemyptr;
}

const Enemy Gallery::operator[](size_t n)const
{
	const Enemy* enemyptr = this->get(n);

	return *enemyptr;
}

Gallery::operator bool() const
{
	const bool result = this->empty();
	return !result;
}

ostream &operator<<(ostream &out, Gallery &rhs)
{
	for(size_t i=0; i < rhs.size(); i++)
	{
		rhs.get(i)->write(out);
		if(i+1 < rhs.size())
			cout << '\n';
	}
	return out << "";
}


