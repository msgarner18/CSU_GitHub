#include <iostream>

using namespace std;

int main()
{
	//int y = 0;
	int x = 0;
	/*while(y < 70)
	{*/
		while(x < 254)
		{
			for(int j = 0; j < 70; j++)
			{
				for(int i = 0; i < 254; i++)
				{
					if(i == x && j > 35)
						cout << "1";
					else
						cout << "0";
				}
				cout << '\n';
			}
			x++;
		}
		x = 0;
		//y++;
	//}
}
