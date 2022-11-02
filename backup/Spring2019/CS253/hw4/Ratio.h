#ifndef Ratio_H_INCLUDED
#define Ratio_H_INCLUDED

#include <iostream>
#include <vector>
#include <sys/types.h>
#include <pwd.h>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <cassert>
#include <stdexcept>
#include <sstream>


class Ratio
{
	public:
	Ratio() = delete;
	Ratio(long numerator, long denominator);//good
	Ratio(long numerator);
	Ratio(int numerator, int denominator);//good
	Ratio(int numerator);

	long numerator()const;//good
	void numerator(long numerator);//good

	long denominator()const;//good
	void denominator(long denominator);//good

	long double ratio() const;//good

	Ratio add(Ratio r)const;
	Ratio add(Ratio r, Ratio r2)const;
	Ratio add(Ratio r, Ratio r2, Ratio r3)const;
	Ratio add(Ratio r, Ratio r2, Ratio r3, Ratio r4)const;
	Ratio add(Ratio r, Ratio r2, Ratio r3, Ratio r4, Ratio r5)const;
	Ratio add(Ratio r, Ratio r2, Ratio r3, Ratio r4, Ratio r5, Ratio r6)const;
	Ratio add(Ratio r, Ratio r2, Ratio r3, Ratio r4, Ratio r5, Ratio r6, Ratio r7)const;
	Ratio add(Ratio r, Ratio r2, Ratio r3, Ratio r4, Ratio r5, Ratio r6, Ratio r7, Ratio r8)const;

	Ratio subtract(Ratio r)const;
	Ratio multiply(Ratio r)const;
	Ratio divide(Ratio r)const;

	int compare(Ratio r)const;
	int compare(long double n)const;
	

	private:
	long num;
	long den;
	
	void simplify(long &numerator, long &denominator);
	void simplify(int &numerator, int &denominator);
};

std::ostream &operator<<(std::ostream &out, const Ratio &r);//good
std::istream &operator>>(std::istream &in, Ratio &r);

#endif
