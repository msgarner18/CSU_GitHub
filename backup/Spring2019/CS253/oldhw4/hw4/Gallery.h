#ifndef GALLERY_H_INCLUDED
#define GALLERY_H_INCLUDED

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
		Gallery(string fileName);
		void read(string filename, string keyfilename);
		void add(Enemy e);
		void clear();
		void size();
		void empty();
		void get(size_t n);
		
	//private:
};
std::ostream &operator<<(std::ostream &os, Gallery &rhs);
#endif
