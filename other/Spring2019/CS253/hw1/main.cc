//how am I expected to use my readLine code- I feel like I was hacking

#include <iostream>
#include <cctype>
#include <stdio.h>
#include <ctype.h>

using namespace std;

string programName;

bool isLeapYear(const int &year);

//complains if day/year input is not valid and exits the program
void checkYearDayErrors(const int &year, int day = 5/*random day that is valid*/)
{
	//invalid input for day integer
	if(day <= 0)
	{
		cerr << programName << ": day must be greater than 0! specifying " << day << " days -in year.day format- is invalid." << '\n';
		exit(1);
	}
	else if(day > 366)
	{
		cerr << programName << ": day cannot be greater than 366! Specifying " << day << " days -in year.day format- is invalid." << '\n';
		exit(1);
	}
	else if(day == 366 && !isLeapYear(year))
	{
		cerr << programName << ": This isn't a leap year! Specifying " << day << " days -in year.day format- is invalid for year " << year << "." << '\n';
		exit(1);
	}
	if(year < 1)
	{
		cerr << programName << ": year cannot be negative! Specifying " << year << " years -in year.day format- is invalid." << '\n';
		exit(1);
	}
	else if(year > 9999)
	{
		cerr << programName << ": year cannot be greater than 4 digits! -in year.day format- must be 4 digits!" << '\n';
		exit(1);
	}
}

//input the year in 4-digit form
//outputs true if that year is a leap year. Otherwise, return false
bool isLeapYear(const int &year)
{
	checkYearDayErrors(year);
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
	checkYearDayErrors(year);
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
	checkYearDayErrors(year);
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
//output:
//day contains day after the month, month contains the month (1-12), year is unchanged
//MUST BE USED BEFORE ANY OF THE OTHER BELOW COMMANDS
void calculateDate(int &day, int &month,  const int &year)
{
	checkYearDayErrors(year, day);
	
	for(month = 1;day-monthToDay(month, year) > 0; month++)
	{
		day -= monthToDay(month, year);
	}
}

//input DATE in day, month, and year format
//output Weekday that corresponds with that date in string format
string weekdayFromDate(int day, int month, int year)
{
	int fingerOne = doomsdayByCentury(year);
	int centRemainder = year - (centuryFromYear(year)*100);
	int fingerTwo = centRemainder/12;
	int fingerThree = centRemainder%12;
	int fingerFour = fingerThree/4;
	
	int doomsday = (fingerOne+fingerTwo+fingerThree+fingerFour)%7;

	int weekday = (doomsday+day+28-doomsdayByMonth(month, year))%7;
	
	string weekName = "N/A";	

	switch(weekday)
	{
		case 0: weekName = "Sun"; break;
		case 1: weekName = "Mon"; break;
		case 2: weekName = "Tue"; break;
		case 3: weekName = "Wed"; break;
		case 4: weekName = "Thu"; break;
		case 5: weekName = "Fri"; break;
		case 6: weekName = "Sat"; break;
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

//prints day in 2 digit format with no preceding or trailing space
void outputDay(int day)
{
	if(day < 10)
		cout << "0";
	cout << day;
}

//prints year in 4 digit format with no preceding or trailing space
void outputYear(int year)
{
	for(int i = 1000; year < i; i/=10)
		cout << "0";
	cout << year;
}

//reads a line from cin and fills both ints year and day
//if a problem occurs in reading proccess, complain and exit the program
bool readLine(int &year, int &day)
{
	string syear = "";
	string sday = "";
	char c;
	while(cin.get(c) && c >= '0' && c <= '9')
	{
		syear += c;
	}
	if(syear == "" && !isspace(c))
		return false;
	if(c != '.')
	{
		cerr << programName << ": Improper format! Usage: year.day" << '\n';
		exit(1);
	}
	
	year = stoi(syear, nullptr, 10);	
	checkYearDayErrors(year);

	while(cin.get(c) && c >= '0' && c <= '9')
	{
		sday += c;
	}
	if(c != '\n')
	{
		cerr << programName << ": Improper format! Usage: year.day" << '\n';
		exit(1);
	}

	day = stoi(sday, nullptr, 10);
	checkYearDayErrors(year, day);
	
	return true;
}

int main(int argc, char* argv[])
{
	programName = argv[0];
	
	if(argc > 1){cerr << programName << ": Usage: year.day -please don't give arguments" << '\n'; exit(1);}//just so that the compiler doesn't complain that I am not using argc :)
	
	//input
	int day;
	int year;
	int month;
	
	while(readLine(year, day))
	{
		calculateDate(day, month, year);//input day and year
		
		cout << weekdayFromDate(day, month, year) << " ";
		outputDay(day);
		cout << " " << monthToName(month) << " ";
		outputYear(year);
		cout << '\n';
		
	}
}

/*
//complains if day or year is outside of the range of the int data type
void checkRange(const int &year, const int &day = 5)
{	
	int intSize = sizeof(int)*8-2;
	int intMax = 2;
	for(int i = 1; i < intSize; i++)
	{
		intMax *= 2;
	}
	intMax = (intMax-1)*2+1;
	
	if(year >= intMax && day >= intMax)
	{
		cerr << programName << ": both year AND day -in year.day format- are too large for the data type I am using. :(" << '\n';
		cerr << programName << ": also, day should never be larger than 366, and year should never be larger than 4 digits, so you have thoroughly failed!" << '\n';
	}
	else if(year >= intMax)
	{
		cerr << programName << ": year -in year.day format- is too large for the data type I am using. :(" << '\n';
		cerr << programName << ": also, year should not be larger than 4 digits, so you have failed!" << '\n';
		exit(1);
	}
	
	else if(day >= intMax)
	{
		cerr << programName << ": day -in year.day format- is too large for the data type I am using. :(" << '\n';
		cerr << programName << ": also, day should never be larger than 366, so you have thoroughly failed!" << '\n';
		exit(1);
	}
}
*/




