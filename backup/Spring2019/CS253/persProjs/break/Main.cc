#include <iostream>

using namespace std;

constexpr long long int largestNumber = 999999999999999999; 
void recursion(long long int x)
{
	if(x < largestNumber)
		recursion(++x);
	
}

int main()
{
	for(long long int i = largestNumber; i > -largestNumber; i--)
	{
		recursion(i);
	}
	cout << "done" << '\n';
}
