#include "Ratio.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <pwd.h>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <cassert>
#include <stdexcept>
#include <sstream>

using namespace std;

Ratio::Ratio(long numerator, long denominator)
{
	simplify(numerator, denominator);
	num = numerator;
	den = denominator;
}

Ratio::Ratio(long numerator)
{
	num = numerator;
	den = 1;
}

Ratio::Ratio(int numerator, int denominator)
{
	simplify(numerator, denominator);
	num = numerator;
	den = denominator;
}

Ratio::Ratio(int numerator)
{
	num = numerator;
	den = 1;
}

long Ratio::numerator()const
{
	return num;
}

void Ratio::numerator(long numerator)
{
	long denominator = den;
	simplify(numerator, denominator);
	num = numerator;
	den = denominator;
}

long Ratio::denominator()const
{
	return den;
}

void Ratio::denominator(long denominator)
{
	long numerator = num;
	simplify(numerator, denominator);
	den = denominator;
	num = numerator;
}

long double Ratio::ratio() const
{
	return (num+0.0)/(den+0.0);
}

Ratio Ratio::add(Ratio r)const
{
	Ratio result(num*r.denominator() + r.numerator()*den, den*r.denominator());
	return result;
}

Ratio Ratio::add(Ratio r, Ratio r2)const
{
	Ratio result = add(r.add(r2));
	return result;
}

Ratio Ratio::add(Ratio r, Ratio r2, Ratio r3)const
{
	Ratio result = add(r.add(r2.add(r3)));
	return result;
}

Ratio Ratio::add(Ratio r, Ratio r2, Ratio r3, Ratio r4)const
{
	Ratio result = add(r.add(r2.add(r3.add(r4))));
	return result;
}

Ratio Ratio::add(Ratio r, Ratio r2, Ratio r3, Ratio r4, Ratio r5)const
{
	Ratio result = add(r.add(r2.add(r3.add(r4.add(r5)))));
	return result;
}

Ratio Ratio::add(Ratio r, Ratio r2, Ratio r3, Ratio r4, Ratio r5, Ratio r6)const
{
	Ratio result = add(r.add(r2.add(r3.add(r4.add(r5.add(r6))))));
	return result;
}

Ratio Ratio::add(Ratio r, Ratio r2, Ratio r3, Ratio r4, Ratio r5, Ratio r6, Ratio r7)const
{
	Ratio result = add(r.add(r2.add(r3.add(r4.add(r5.add(r6.add(r7)))))));
	return result;
}

Ratio Ratio::add(Ratio r, Ratio r2, Ratio r3, Ratio r4, Ratio r5, Ratio r6, Ratio r7, Ratio r8)const
{
	Ratio result = add(r.add(r2.add(r3.add(r4.add(r5.add(r6.add(r7.add(r8))))))));
	return result;
}

Ratio Ratio::subtract(Ratio r)const//good
{
	Ratio result(num*r.denominator() - r.numerator()*den, den*r.denominator());
	
	return result;
}

Ratio Ratio::multiply(Ratio r)const//good
{
	Ratio result(r.numerator()*num, r.denominator()*den);
	
	return result;
}

Ratio Ratio::divide(Ratio r)const//good
{
	//divide by zero is checked when result is created and simplified
	Ratio result(r.denominator()*num, r.numerator()*den);
	
	return result;
}
int Ratio::compare(Ratio r)const
{
	if(ratio() > r.ratio())
		return 1;
	else if(ratio() < r.ratio())
		return -1;
	return 0;
}

int Ratio::compare(long double n)const
{
	if(ratio() > n)
		return 1;
	else if(ratio() < n)
		return -1;
	return 0;
}

//private
void Ratio::simplify(long &numerator, long &denominator)
{
	if(denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}
	else if(numerator == 0 && denominator != 0)
		denominator = 1;
	else if(denominator == 0)
		throw runtime_error("denominator can't be zero");

	int max = numerator;
	if(denominator > max)
		max = denominator;
	for(int i = max; i > 1; i--)
	{
		if(numerator % i == 0 && denominator % i == 0)
		{
			numerator /= i;
			denominator /= i;
		}
	}
}

void Ratio::simplify(int &numerator, int &denominator)
{
	long numer = numerator;
	long denom = denominator;
	simplify(numer, denom);
	numerator = numer;
	denominator = denom;
}

ostream &operator<<(ostream &out, const Ratio &r)
{
	return out << r.numerator() << "/" << r.denominator();
}

istream &operator>>(istream &in, Ratio &r)
{
	long numer; in >> numer;
	char slash;in >> slash;
	long denom;in >> denom;

	Ratio newr(numer, denom);
	r = newr;

	return in;
}







