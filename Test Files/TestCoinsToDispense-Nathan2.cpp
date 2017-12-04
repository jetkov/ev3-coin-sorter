#include <iostream>

using namespace std;

int checkCoin(int & change, int & cCoin)
{
	int nCoin = 0;
	
	while ((change - cCoin) >= 0)
	{	
		change -= cCoin;
		nCoin++;
	}
	
	return nCoin;
}
int doubleCheck(int & change, int & cCoin)
{
	int nCoin = 0;
	
	do
	{	
		change -= cCoin;
		nCoin++;
	}while ((change - cCoin) >= 0);
	
	return nCoin;
}

void coinsToDispense (int change, int & nNickels, int & nDimes, int & nQuarters, int & nLoonies, int & nToonies, bool & yNickels, bool & yDimes, bool & yQuarters, bool & yLoonies, bool & yToonies)
{
	nNickels = nDimes = nQuarters = nLoonies = nToonies = 0;
	int cNickels = 5;
	int cDimes = 10;
	int cQuarters = 25;
	int cLoonies = 100;
	int cToonies = 200;

	if(yToonies)
		nToonies = checkCoin(change, cToonies);
	if(yLoonies)
		nLoonies = checkCoin(change, cLoonies);
	if(yQuarters)
		nQuarters = checkCoin(change, cQuarters);
	if(yDimes)
		nDimes = checkCoin(change, cDimes);
	if(yNickels)
		nNickels = checkCoin(change, cNickels);
	else if (yDimes)
		nDimes += doubleCheck(change, cDimes);
	else if (yQuarters)
		nQuarters += doubleCheck(change, cQuarters);
	else if (yLoonies)
		nLoonies += doubleCheck(change, cLoonies);
	else if (yToonies)
		nToonies += doubleCheck(change, cToonies);
		
	//Deals with special case were cents equals 95 and dollars equals anything
	if (yLoonies)
	{
		if(nDimes == 10)
		{
			nLoonies++;
			nDimes = 0;
		}
		if(nQuarters == 4)
		{
			nLoonies++;
			nQuarters = 0;
		}
	}
	//Deals with special case were cents equals 95 and dollars equal odd number
	if (yToonies && nLoonies == 2)
	{
		nToonies++;
		nLoonies =0;
	}
	
	cout <<change;
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
