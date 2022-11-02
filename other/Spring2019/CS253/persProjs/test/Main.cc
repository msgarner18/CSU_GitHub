#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

void counter()
{
	static int count;
	cout << count++ << '\n';
}

int main(int argc, char *argv[])
{
	cout << "argc: " << argc << '\n';
	for(int i = 0; i < argc; i++)
	{
		cout << "argv[" << i << "]: " << argv[i] << '\n';
	}

	cout << '\n';
	/*
	cout << "sizeof(short): " << sizeof(short)  << '\n';
	cout << "sizeof(int): " << sizeof(int)  << '\n';
	cout << "sizeof(long): " << sizeof(long)  << '\n';
	cout << "sizeof(long long): " << sizeof(long long)  << '\n';
	cout << "sizeof(char): " << sizeof(char)  << '\n';
	
	cout << '\n';
	
	cout << "sizeof(short*): " << sizeof(short*)  << '\n';
	cout << "sizeof(int*): " << sizeof(int*)  << '\n';
	cout << "sizeof(long*): " << sizeof(long*)  << '\n';
	cout << "sizeof(long long*): " << sizeof(long long*)  << '\n';
	cout << "sizeof(char*): " << sizeof(char*)  << '\n';

	for(int i = 0; i < 3; i++)
	{
		counter();
	}
	

	using intp = int*;
	
	int x = 5;
	intp pointer = &x;
	x++;
	//cout << "x = " << x << '\n';
	cout << "*pointer = " << *pointer << '\n';
	return 0;

	int x = 13;
	switch(x)
	{
		case 1: case 3: case 5: case 7: case 9: case 11:
			cout << "odd" << '\n'; break;
		case 2: case 4: case 6: case 8: case 10: case 12:
			cout << "even" << '\n'; break;
		default: 
			cout << "in default!" << '\n';
	}
	

	int a[] = {11, 22, 33};
	for(auto val : a)
		cout << val << '\n';
	
	
	int x = 016;

	cout << "before, x = 0x" << hex << x << '\n';
	x <<= 1;
	cout << "after, x = 0x" << hex << x << '\n';
	
	string s = "FF";
	cin >> s;
	cout << s << '\n';
	cout << s.size() << '\n';
	
	vector<int> v;
	for(int i=0; i<10; i++)
		v.push_back(i*i*i);
	v.erase(v.begin()+5);
	for (size_t i=0; i<v.size(); i++)
		cout << v[i] << ' ';
	cout << '\n';
	
	string hi = (30, '#');;
	const char *hello = hi.c_str();
	cout << hello << ": " << strlen(hello) << '\n';
	
	cout << "\a|\b|\f|\n|\r|\t|\v|\'|\"|\\|\n";
	
	cout << R"(Don't be "afraid" of letters: \a\b\c\d\e\f\g)";
	*/
	
	cout << R"x(What the #"%'&*)?)x" <<'\n';
}


//0b or 0B is binary
//0x or 0X is hexadecimal
//0 is octal
//otherwise, decimal
//0b10101
//0Xa93d
//03741



