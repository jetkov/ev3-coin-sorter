#include <iostream>

using namespace std;


void coinsToDispense (int change, int & nNickels, int & nDimes, int & nQuarters, int & nLoonies, int & nToonies, bool & yNickels, bool & yDimes, bool & yQuarters, bool & yLoonies, bool & yToonies)
{
	nNickels = nDimes = nQuarters = nLoonies = nToonies = 0;

	if (yToonies)
	{
		nToonies = change / 200;
		change %= 200;
	}
	
	if (yLoonies)
	{
		nLoonies = change / 100;
		change %= 100;
	}
	
	if (yQuarters)
	{
		nQuarters = change / 25;
		change %= 25;
	}
	
	if (yDimes)
	{
		nDimes = change / 10;
		change %= 10;
	}
	
	if (yNickels)
	{
		nNickels = change / 5;
		change %= 5;
	} 
	
	else if (yDimes && change > 0)
	{
		nDimes++;
		change -= 10;
	}
		
	else if (yQuarters && change > 0)
	{
		nQuarters++;
		change -= 25;
	}
		
	else if (yLoonies && change > 0)
	{
		nLoonies++;
		change -= 100;
	}
	
	else if (yToonies && change > 0)
	{
		nToonies++;
		change -= 200;
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
