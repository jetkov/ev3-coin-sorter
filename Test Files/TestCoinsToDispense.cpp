#include <iostream>

using namespace std;


void coinsToDispense (int change, int & nNickels, int & nDimes, int & nQuarters, int & nLoonies, int & nToonies, bool & yNickels, bool & yDimes, bool & yQuarters, bool & yLoonies, bool & yToonies)
{
	nNickels = nDimes = nQuarters = nLoonies = nToonies = 0;

	if (change >= 200 && yToonies)
	{
		nToonies = change / 200;

		change -= nToonies * 200;
	}

	if (change >= 100 && yLoonies)
	{
		nLoonies = change / 100;

		change -= nLoonies * 100;
	}

	if (change >= 25 && yQuarters)
	{
		nQuarters = change / 25;

		change -= nQuarters * 25;
	}

	if (change >= 10 && yDimes)
	{
		nDimes = change / 10;

		change -= nDimes * 10;
	}

	if (change >= 5 && yNickels)
	{
		nNickels = change / 5;

		change -= nNickels * 5;
	}

	if (change > 0)
	{
		change += 5;
		nDimes += change / 10;

		change -= (change / 10) * 10;
	}

	if (change > 0)
	{
		change += 15;
		nQuarters += change / 25;

		change -= (change / 25) * 25;
	}

	if (change > 0)
	{
		change += 75;
		nLoonies += change / 100;

		change -= (change / 100) * 100;
	}

	if (change > 0)
	{
		change += 100;
		nToonies += change / 200;

		change -= (change / 200) * 200;
	}

}

int main()
{
	while (true)
	{
		int change = 0;
		int nNickels = -1, nDimes = -1, nQuarters = -1, nLoonies = -1, nToonies = -1;
    	bool yNickels = true, yDimes = true, yQuarters = true, yLoonies = true, yToonies = true;
		
		cout << "\nEnter change: ";
		cin >> change;
		
		cout << "\nNickels available: ";
		cin >> yNickels;
		cout << "Dimes available: ";
		cin >> yDimes;
		cout << "Quarters available: ";
		cin >> yQuarters;
		cout << "Loonies available: ";
		cin >> yLoonies;
		cout << "Toonies available: ";
		cin >> yToonies;
		
		
		
		coinsToDispense(change, nNickels, nDimes, nQuarters, nLoonies, nToonies, yNickels, yDimes, yQuarters, yLoonies, yToonies);
		
		cout << "\nN" << nNickels << " D" << nDimes << " Q" << nQuarters << " L" << nLoonies << " T" << nToonies;
	}
}
