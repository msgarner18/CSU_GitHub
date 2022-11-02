#ifndef GALLERY_H_INCLUDED
#define GALLERY_H_INCLUDED
#include "Enemy.h"
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

class Gallery
{
	public:
		Gallery();
		Gallery(std::string filename);
		Gallery(std::string key, std::string filename);
		Gallery(std::string key, std::string filename, std::string filename2);

		Gallery(std::string key, std::string filename, std::string filename2, std::string filename3);
		Gallery(std::string key, std::string filename, std::string filename2, std::string filename3, std::string filename4);
		Gallery(std::string key, std::string filename, std::string filename2, std::string filename3, std::string filename4, std::string filename5);
		Gallery(std::string key, std::string filename, std::string filename2, std::string filename3, std::string filename4, std::string filename5, std::string filename6);

		
		void read(std::string filename, std::string key);
		void add(Enemy &e);
		void clear();
		size_t size()const;
		bool empty()const;
		const Enemy* get(size_t n)const;
		Enemy* get(size_t n);
		
	private:
		std::string s1;
		std::string s2;
		size_t size1;
		std::vector<Enemy> enemyVector;
		int keyTotal = 0;
		void eraseVector(std::vector<Enemy> &e);
		void swap(std::string &one, std::string &two);
		bool isOneWord(const std::string &word);


};
std::ostream &operator<<(std::ostream &os, Gallery &rhs);
#endif
