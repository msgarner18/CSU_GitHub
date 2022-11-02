#include <iostream>

using namespace std;

float exp(float first, float second)
{
	float total = 1;
	if(second == 1)
		total = first;
	else
	{
		for(int i = 1; i <= second; i++)
			total *= first;
	} 
	return total;
}

int main()
{
	float total = 0;
	float firstTerm;
	char op;
	float secondTerm;
	while(true)
	{
		cout << "peek = " << cin.peek() << '\n';
		if(cin.peek() == 'c')
			total = 0;
		else
		{
			
			if(cin.peek() >= 0 && cin.peek() <= 9){cin >> firstTerm; cout << firstTerm << '\n';}
			else{firstTerm = total;}
			cin >> op;
			cin >> secondTerm;

			if(op == '+')
				total = firstTerm + secondTerm;
			else if(op == '-')
				total = firstTerm - secondTerm;
			else if(op == '*')
				total = firstTerm * secondTerm;
			else if(op == '/')
				total = firstTerm / secondTerm;
			else if(op == '^')
				total = exp(firstTerm, secondTerm);
			cout << "total = " << total << '\n';
		}
	}

	return 0;
}
