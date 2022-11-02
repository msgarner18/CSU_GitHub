#include <iostream>
using namespace std;

int main()
{
    unsigned int a = 30, b = 20;
	if(a > b)
	{
		int temp = b;
		b = a;
		a = temp;
	}
    unsigned int diff = b - a;
    cout << "diff is " << diff << endl;
    return 0;
}
