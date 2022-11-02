//Options must precede filenames. ./hw3 -i infile -v must attempt to process the file -v, which would probably fail. 
//The -i and -v options may be specified multiple times, with no additional effect. 
//how am I expected to use my readLine code- I feel like I was hacking

#include <time.h>
#include <iostream>
#include <cctype>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

string programName;

bool isLeapYear(const int &year);

//complains if day/year input is not valid and exits the program
void checkYearDayErrors(const string &input, const int &year, int day = 5/*random day that is valid*/)
{
	//invalid input for day integer
	if(day <= 0)
	{
		cerr << programName << ": day must be greater than 0! specifying " << day << " days -in year.day format- is invalid in input " << input << '\n';
		exit(1);
	}
	else if(day > 366)
	{
		cerr << programName << ": day cannot be greater than 366! Specifying " << day << " days -in year.day format- is invalid in input " << input << '\n';
		exit(1);
	}
	else if(day == 366 && !isLeapYear(year))
	{
		cerr << programName << ": This isn't a leap year! Specifying " << day << " days -in year.day format- is invalid for year " << year << "in input " << input << '\n';
		exit(1);
	}
	if(year < 1)
	{
		cerr << programName << ": year must be greater than 0! Specifying " << year << " years -in year.day format- is invalid in input " << input << '\n';
		exit(1);
	}
	else if(year > 9999)
	{
		cerr << programName << ": year (" << year << ") cannot be greater than 4 digits! -in year.day format- must be 4 digits in input " << input << '\n';
		exit(1);
	}
}

//input the year in 4-digit form
//outputs true if that year is a leap year. Otherwise, return false
bool isLeapYear(const int &year)
{
	//leap years occur in years divisible by four, unless the year is divisible by 100 (no leap year), unless it’s divisible by 400 (leap year)
	if(year%400 == 0)
	{
		return true;
	}
	else if(year%100 != 0 && year%4 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//input month and year and outputs number of days in that month. stops code and complains if input is not valid
int monthToDay(int month, int year)
{
	int day = -1;
	switch(month)
	{
		case 1: day = 31;break;
		case 2:
			if(isLeapYear(year))
				day = 29;
			else
				day = 28;
			break;
		case 3: day = 31;break;
		case 4: day = 30;break;
		case 5: day = 31;break;
		case 6: day = 30;break;
		case 7: day = 31;break;
		case 8: day = 31;break;
		case 9: day = 30;break;
		case 10: day = 31;break;
		case 11: day = 30;break;
		case 12: day = 31;break;
		default: cerr << programName << ": month needs to be 1-12 in monthToDay. month = " << month << '\n'; exit(1); break;
	}
	return day;
}

//returns doomsday (1/4, 2/29(28), 3/14...)given month (outputs the right number in l/r format
int doomsdayByMonth(int month, int year)
{
	int day = -1;
	
	switch(month)
	{
		case 1:
			if(isLeapYear(year))
				day = 4;
			else
				day = 3;
			break;
		case 2:
			if(isLeapYear(year))
				day = 29;
			else
				day = 28;
			break;
		case 3: day = 14; break;
		case 4: day = 4; break;
		case 5: day = 9; break;
		case 6: day = 6; break;
		case 7: day = 11; break;
		case 8: day = 8; break;
		case 9: day = 5; break;
		case 10: day = 10; break;
		case 11: day = 7; break;
		case 12: day = 12; break;
		default: cerr << programName << ": month needs to be 1-12 in doomsdayByMonth. month = " << month << '\n'; exit(1); break;
	}
	return day;
}

//turns year into century for comprehension help 2100->21st century a.k.a return 21;
int centuryFromYear(int year)
{
	return year/100;
}

//returns which day of the week all the doomsdays will be given year (Sunday-Saturday = 0-6)
int doomsdayByCentury(int year)
{
	int doomsday = -1;
	int century = centuryFromYear(year);
	
	switch(century%4)
	{
		case 0: doomsday = 2; break;
		case 1: doomsday = 0; break;
		case 2: doomsday = 5; break;
		case 3: doomsday = 3; break;
	}
	return doomsday;
}

///////////////////////////////////////////////////////////////////////////////
//                              to use                                       //
///////////////////////////////////////////////////////////////////////////////

//input:
//days since start of the year, empty month int, and year such as 2020
//outcome:
//day contains day after the month, month contains the month (1-12), year is unchanged
//MUST BE USED BEFORE ANY OF THE OTHER BELOW COMMANDS
void calculateDate(int &day, int &month,  const int &year)
{	
	for(month = 1;day-monthToDay(month, year) > 0; month++)
	{
		day -= monthToDay(month, year);
	}
}

//input DATE in day, month, and year format
//output Weekday that corresponds with that date in string format
int weekNumFromDate(int day, int month, int year)
{
	int fingerOne = doomsdayByCentury(year);
	int centRemainder = year - (centuryFromYear(year)*100);
	int fingerTwo = centRemainder/12;
	int fingerThree = centRemainder%12;
	int fingerFour = fingerThree/4;
	
	int doomsday = (fingerOne+fingerTwo+fingerThree+fingerFour)%7;

	int weekday = (doomsday+day+28-doomsdayByMonth(month, year))%7;
	
	string weekName = "N/A";	

	return weekday;
}

string weekWordFromNum(const int &num)
{
	string weekName = "N/A";
	switch(num)
	{
		case 0: weekName = "Sun"; break;
		case 1: weekName = "Mon"; break;
		case 2: weekName = "Tue"; break;
		case 3: weekName = "Wed"; break;
		case 4: weekName = "Thu"; break;
		case 5: weekName = "Fri"; break;
		case 6: weekName = "Sat"; break;
		default: cerr << programName << ": week needs to be 0-6 in weekWordFromNum. week = " << num << '\n'; exit(1); break;
	}
	return weekName;
}

//input month in number (1-12) format
//output month in string format
string monthToName(int month)
{
	string name;
	
	switch(month)
	{
		case 1: name = "Jan"; break;
		case 2: name = "Feb"; break;
		case 3: name = "Mar"; break;
		case 4: name = "Apr"; break;
		case 5: name = "May"; break;
		case 6: name = "Jun"; break;
		case 7: name = "Jul"; break;
		case 8: name = "Aug"; break;
		case 9: name = "Sep"; break;
		case 10: name = "Oct"; break;
		case 11: name = "Nov"; break;
		case 12: name = "Dec"; break;
		default: cerr << programName << ": month needs to be 1-12 in monthToName. month = " << month << '\n'; exit(1); break;
	}
	return name;
}

void calculateTM(const int &day, const int &month, const int &year, struct tm* timeInfo)
{
	int yday = 0;
	timeInfo->tm_mday = day;
	timeInfo->tm_mon = month - 1;
	timeInfo->tm_year = year - 1900;
	timeInfo->tm_wday = weekNumFromDate(day, month, year);

	//calculate yday from month and day and year	
	for(int i = 1; i <= month;i++)
		yday += monthToDay(i, year);
	yday += day;

	timeInfo->tm_yday = yday;
}

//returns -1 for bad, 1 for good, and 0 for end of file
bool processYD(string input, int &year, int &month, int &day)
{
	string syear = "";
	string sday = "";
	string smonth = "";

	int i;
	for(i = 0; input[i] >= '0' && input[i] <= '9'; i++)
	{
		syear += input[i];
	}

	if(syear == "")
		return 0;
	if(input[i] != '.')
		return 0;
	
	for(i ++; input[i] >= '0' && input[i] <= '9'; i++)
	{
		sday += input[i];
	}
	if(sday == "")
		return 0;
	if(input[i] != '\0')
		return 0;

	try
	{
		year = stoi(syear, nullptr, 10);	
		day = stoi(sday, nullptr, 10);
	}
	catch(...)
	{
		cerr << programName << ": failed to convert input " << input << " into an int from a string inside of processYD." << '\n';
		cerr << "syear = " << syear << " and sday = " << sday << '\n';
		exit(1);
	} 

	
	checkYearDayErrors(input, year, day);
	
	calculateDate(day, month, year);
	
	return 1;
}

//returns 1 for good, and 0 for bad
bool processYMD(const string &input, int &year, int &month, int &day)
{
	string syear = "";
	string sday = "";
	string smonth = "";

	for(int i = 0; i < 4 && input[i] >= '0' && input[i] <= '9'; i++)
	{
		syear += input[i];
	}
	if(syear == "")
		return 0;
	if(input[4] != '-')	
		return 0;
	
	for(int i = 5; i < 7 && input[i] >= '0' && input[i] <= '9'; i++)
	{
		smonth += input[i];
	}
	if(smonth == "")
		return 0;
	if(input[7] != '-')
		return 0;

	for(int i = 8; i < 10 && input[i] >= '0' && input[i] <= '9'; i++)
	{
		sday += input[i];
	}
	if(sday == "")
		return 0;
	if(input[10] != '\0')
		return 0;

	try
	{
		year = stoi(syear, nullptr, 10);	
		month = stoi(smonth, nullptr, 10);
		day = stoi(sday, nullptr, 10);
	}
	catch(...)
	{
		cerr << programName << ": failed to convert input " << input << " into an int from a string inside of processYMD." << '\n';
		cerr << "syear = " << syear << ", smonth = " << smonth << ", and sday = " << sday << '\n';
		exit(1);
	} 

	checkYearDayErrors(input, year);

	if(month < 1 || month > 12)
	{
		cerr << programName << ": month is " << month << ". This is not within the range of 1 <= MM <= 12 in input " << input << '\n';
		exit(1);
	}	

	if(day <= 0)
	{
		cerr << programName << ": day must be greater than 0! specifying " << day << " days -in YYY-MM-DD format- is invalid in input " << input << '\n';
		exit(1);
	}
	else if(day > monthToDay(month,year))
	{
		cerr << programName << ": day cannot be greater than " << monthToDay(month, year) << "for the month of " << weekWordFromNum(month) << "Specifying " << day << " days -in YYYY-MM-DD format- is invalid in input " << input << '\n';
		exit(1);
	}
	
	return 1;
}

bool processToday(const string &input, int &year, int &month, int &day, struct tm* timeInfo)
{
	if(!(input[0] == 't' || input[0] == 'T'))
		return 0;
	if(!(input[1] == 'o' || input[1] == 'O'))
		return 0;
	if(!(input[2] == 'd' || input[2] == 'D'))
		return 0;
	if(!(input[3] == 'a' || input[3] == 'A'))
		return 0;
	if(!(input[4] == 'y' || input[4] == 'Y'))
		return 0;
	if(input[5] != '\0')
		return 0;

	time_t rawtime;
	time (&rawtime);
  	timeInfo = localtime(&rawtime);
	
	day = timeInfo->tm_mday;
	month = timeInfo->tm_mon + 1;
	year = timeInfo->tm_year + 1900;
	
	return 1;
}

bool processYesterday(const string &input, int &year, int &month, int &day, struct tm* timeInfo)
{
	if(!(input[0] == 'y' || input[0] == 'Y'))
		return 0;
	if(!(input[1] == 'e' || input[1] == 'E'))
		return 0;
	if(!(input[2] == 's' || input[2] == 'S'))
		return 0;
	if(!(input[3] == 't' || input[3] == 'T'))
		return 0;
	if(!(input[4] == 'e' || input[4] == 'E'))
		return 0;
	if(!(input[5] == 'r' || input[5] == 'R'))
		return 0;
	if(!(input[6] == 'd' || input[6] == 'D'))
		return 0;
	if(!(input[7] == 'a' || input[7] == 'A'))
		return 0;
	if(!(input[8] == 'y' || input[8] == 'Y'))
		return 0;
	if(input[9] != '\0')
		return 0;
	
	time_t rawtime;
	time (&rawtime);
  	timeInfo = localtime(&rawtime);
	
	day = timeInfo->tm_yday;
	year = timeInfo->tm_year + 1900;
	if(day < 1)
	{
		year -= 1;
		month = 12;
		day = 31;
	}
	else
	{
		calculateDate(day, month, year);
	}

	return 1;
}

bool processTomorrow(const string &input, int &year, int &month, int &day, struct tm* timeInfo)
{
	if(!(input[0] == 't' || input[0] == 'T'))
		return 0;
	if(!(input[1] == 'o' || input[1] == 'O'))
		return 0;
	if(!(input[2] == 'm' || input[2] == 'M'))
		return 0;
	if(!(input[3] == 'o' || input[3] == 'O'))
		return 0;
	if(!(input[4] == 'r' || input[4] == 'R'))
		return 0;
	if(!(input[5] == 'r' || input[5] == 'R'))
		return 0;
	if(!(input[6] == 'o' || input[6] == 'O'))
		return 0;
	if(!(input[7] == 'w' || input[7] == 'W'))
		return 0;
	if(input[8] != '\0')
		return 0;

	time_t rawtime;
	time (&rawtime);
  	timeInfo = localtime(&rawtime);
	
	day = timeInfo->tm_yday+2;
	year = timeInfo->tm_year + 1900;
	if(day > 366 || (day == 366 && !isLeapYear(year)))
	{
		year ++;
		month = 1;
		day = 1;
	}
	else
	{
		calculateDate(day, month, year);
	}	
	
	return 1;
}

//reads a line from cin and fills both ints year and day
//if a problem occurs in reading proccess, complain and exit the program
bool readLine(istream &in, struct tm* timeInfo, int &year, int &month, int &day)
{
	string input;	
	if(!getline(in, input))
		return 0;
	if(processYesterday(input, year, month, day, timeInfo)){}
	else if(processToday(input, year, month, day, timeInfo)){}
	else if(processTomorrow(input, year, month, day, timeInfo)){}
	else if(processYMD(input, year, month, day)){}
	else if(processYD(input, year, month, day)){}
	else
	{
		cerr << programName << ": " << input << " is not in proper format. Proper format includes:" << '\n';
		cerr << "year.day, " << "YYYY-MM-DD, " << "today, " << "yesterday, " << "or tomorrow\n";
		exit(1);
	}
	
	return 1;
		
	
}

//assumes year has no errors
const char* findFormat(const bool &optF, const bool &optI, const int &year, string format)
{
	const char* word1 = "%a %b %d %Y";
	const char* word2 = "%a %b %d 0%Y";
	const char* word3 = "%a %b %d 00%Y";
	const char* word4 = "%a %b %d 000%Y";
	const char* iWord1 = "%F";
	const char* iWord2 = "0%F";
	const char* iWord3 = "00%F";
	const char* iWord4 = "000%F";

	if(optF)
		return format.c_str();
	else if(optI)
	{
		if(year > 999)
			return iWord1;
		else if(year > 99)
			return iWord2;
		else if(year > 9)
			return iWord3;
		else
			return iWord4;
	}
	else if(year > 999)
		return word1;
	else if(year > 99)
		return word2;
	else if(year > 9)
		return word3;
	else
		return word4;
}

int main(int argc, char* argv[])
{
	programName = argv[0];
	
	int day;
	int year;
	int month;
	char timeOutput[80];
	struct tm* timeInfo;
	time_t rawtime;
	time (&rawtime);
  	timeInfo = localtime(&rawtime);
	
	bool optF = false;
	bool optI = false;
	bool optV = false;
	
	int fileStart = 1;
	char opt;
	string format = "";

	//get opts
	for(int i = 2; (opt = getopt(argc, argv, "f:iv")) != -1; i++)
	{
		if(opt == 'f')
		{ 
			if(optF)
			{
				cerr << programName << ": -f cannot be specified more than once." << '\n';
				exit(1);
			}
			else
			{
				optF = true;
				format = argv[optind-1];

				if(format[0] == '-')
				{
					format = format.erase(0, format.find_first_of("f")+1);
				}
				else{i++;}
				//cout << "format = " << format << '\n';
			}
		}
		else if(opt == 'i'){ optI = true;}
		else if(opt == 'v'){ optV = true;}
		else{exit(1);}
		if(i > optind)
			i = optind;
		//check if an argument is attempting to be skipped
		//cout << "i = " << i << '\n';
		//cout << "optind = " << optind << '\n';		
		fileStart = i;		
		if(optind > i){fileStart = i-1; break;}
		
	}
	if(optF && optI)
	{
		cerr << programName << ": -f and -i cannot both be specified." << '\n';
		exit(1);
	}
	//cout << "fileStart = " << fileStart << '\n';
	//read from input file stream
	for(int i = fileStart; i < argc; i++)
	{
		//cout << "i = " << i << '\n';
		//cout << "argv[" << i << "] = " << argv[i] << '\n' << '\n';
		ifstream in(argv[i]);
		
		if(!in.is_open())
		{
			cerr << programName << ": file " << argv[i] << " was unable to be opened. " << '\n';
			exit(1);
		}
		if(optV)
			cout << "*** Processing " << argv[i] << '\n';
		while(readLine(in, timeInfo, year, month, day))
		{
			calculateTM(day, month, year, timeInfo);

			strftime(timeOutput, 80, findFormat(optF, optI, year, format), timeInfo);
			cout << timeOutput << '\n';
		}
	}

	//read from cin
	if(fileStart >= argc)
	{
		if(optV)
			cout << "*** Processing standard input" << '\n';
		//read from standard input
		while(readLine(cin, timeInfo, year, month, day))
		{
			calculateTM(day, month, year, timeInfo);
			
			strftime(timeOutput, 80, findFormat(optF, optI, year, format), timeInfo);
			cout << timeOutput << '\n';
		}
	}
	return 0;
}
