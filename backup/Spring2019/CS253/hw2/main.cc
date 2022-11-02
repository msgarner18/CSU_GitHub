#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

string programName;

bool isOperator(string oper)
{
	if(oper == "+" || oper == "-" || oper == "*" || oper == "/" || oper == "@")
		return true;
	else
		return false;
}

bool isOpt(string opt)
{
	if(opt == "-h" || opt == "-o" || opt == "-d")
		return true;
	else
		return false;
}

void changeTotal(int &total, const string &oper, int &arg)
{
	if(oper == "+")
		total += arg;
	if(oper == "-")
		total -= arg;
	if(oper == "*")
		total *= arg;
	if(oper == "/")
	{
		if(arg == 0)
		{
			cerr << programName << ": argument " << arg << " is invalid- you can't divide by zero!" << '\n';
			exit(1);
		}
		total /= arg;
	}
	if(oper == "@")
	{
		if(abs(arg - 45) == abs(total - 45) && arg < total)
			total = arg;
		else if(abs(arg - 45) > abs(total - 45))
			total = arg;
	}
}

void outputTotal(const int &total, const char &opt)
{
	if(opt == 'h')
	{
		if(total < 0)
			cout << "-" << hex << -total << '\n';
		else
			cout << hex << total << '\n';
	}
	else if(opt == 'o')
		cout << oct << total << '\n';
	else
		cout << dec << total << '\n';
} 

void setArg(int &arg, const string &argv)
{
	try
	{
		if(argv.substr(0,2) == "0x")
			arg = stoi(argv.substr(2, argv.length()), nullptr, 16);
		else if(argv.substr(0,2) == "0b")
		{
			arg = stoi(argv.substr(2, argv.length()), nullptr, 2);
		}
		else if(argv.substr(0,1) == "0")
			arg = stoi(argv, nullptr, 8);
		else
			arg = stoi(argv, nullptr, 10);
	}
	catch(...)
	{
		cerr << programName << ": argument " << argv << " should have been a number!" << '\n';
		exit(1);
	} 
}
/*
void setTrim(char &opt, int &trim)
{
	if(opt == '?')
		trim = -1;
}
*/
int main(int argc, char* argv[])
{
	programName = argv[0];
	char opt;
	string oper;
	int trim = 0;
	int total;
	
	if(argc < 3)
	{
		cerr << programName << ": not enough arguments!" << '\n';
		return 1;
	}

	//get opt
	if(isOpt(argv[1]))
		opt = getopt(argc, argv, "h:o:d:");
	else if(isOperator(argv[1]))
		trim = -1;
	else
	{
		cerr << programName << ": argument " << argv[1] << " is not -h, -o, -d, or a valid operator!" << '\n';
		return 1;
	}

	//get operator
	if(isOperator(argv[2+trim]))
		oper = argv[2+trim];
	else
	{
		cerr << programName << ": argument " << argv[2+trim] << " is not a valid operator!" << '\n';
		return 1;
	}
	
	//set total to first argument after operator
	setArg(total, argv[3+trim]);

	//add up all other arguments past first one
	for(int i = 4+trim; i < argc; i++)
	{
		int arg;
		setArg(arg, argv[i]);
		changeTotal(total, oper, arg);
	}

	//output total
	outputTotal(total, opt);

	return 0;
}
