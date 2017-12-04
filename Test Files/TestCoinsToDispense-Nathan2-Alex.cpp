#include <iostream>

using namespace std;

int checkCoin(int & change, int coinValue)
{
	int nCoin = change / coinValue;
	change %= coinValue;
	
	return nCoin;
}

const int NICKEL_VAL = 5, DIME_VAL = 10, QUARTER_VAL = 25, LOONIE_VAL = 100, TOONIE_VAL = 200;

void coinsToDispense (int change, int & nNickels, int & nDimes, int & nQuarters, int & nLoonies, int & nToonies, bool & isNickels, bool & isDimes, bool & isQuarters, bool & isLoonies, bool & isToonies)
{
	nNickels = nDimes = nQuarters = nLoonies = nToonies = 0;

	if(isToonies)
		nToonies = checkCoin(change, TOONIE_VAL);
		
	if(isLoonies)
		nLoonies = checkCoin(change, LOONIE_VAL);
		
	if(isQuarters)
		nQuarters = checkCoin(change, QUARTER_VAL);
		
	if(isDimes)
		nDimes = checkCoin(change, DIME_VAL);
		
	if(isNickels)
		nNickels = checkCoin(change, NICKEL_VAL);
		
	else if (isDimes && change > 0)
	{
		nDimes++;
		change -= DIME_VAL;
	}	
	
	else if (isQuarters && change > 0)
	{
		nQuarters++;
		change -= QUARTER_VAL;
	}
		
	else if (isLoonies && change > 0)
	{
		nLoonies++;
		change -= LOONIE_VAL;
	}
	
	else if (isToonies && change > 0)
	{
		nToonies++;
		change -= TOONIE_VAL;
	}
		
	//Deals with special case were cents equals 95 and dollars equals anything
	if (isLoonies)
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
	if (isToonies && nLoonies == 2)
	{
		nToonies++;
		nLoonies = 0;
	}
}
	
int main()
{
	while (true)
	{
		int change = 0;
		int nNickels = -1, nDimes = -1, nQuarters = -1, nLoonies = -1, nToonies = -1;
    	bool isNickels = true, isDimes = true, isQuarters = true, isLoonies = true, isToonies = true;
		
		cout << "\n\nEnter change: ";
		cin >> change;
		
		cout << "\nNickels available: ";
		cin >> isNickels;
		cout << "Dimes available: ";
		cin >> isDimes;
		cout << "Quarters available: ";
		cin >> isQuarters;
		cout << "Loonies available: ";
		cin >> isLoonies;
		cout << "Toonies available: ";
		cin >> isToonies;
		
		coinsToDispense(change, nNickels, nDimes, nQuarters, nLoonies, nToonies, isNickels, isDimes, isQuarters, isLoonies, isToonies);
		
		cout << "\nN" << nNickels << " D" << nDimes << " Q" << nQuarters << " L" << nLoonies << " T" << nToonies;
	}
}
