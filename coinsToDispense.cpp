#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <iostream>

using namespace std;

const int TOONIES = 4;
const int LOONIES = 3;
const int QUARTERS = 2;
const int DIMES = 1;
const int NICKELS = 0;

void coinsToDispense (float change, int coins[], bool coinsAvailable[])
{
	// change = round(change);

	if (change >= 2 && coinsAvailable[TOONIES])
	{
		coins[TOONIES] = int (change / 2);
		change -= coins[TOONIES] * 2;
	}
	
	if (change >= 1 && coinsAvailable[LOONIES])
	{
		coins[LOONIES] = int (change);
		change -= coins[LOONIES];
	}
	
	if (change >= 0.25 && coinsAvailable[QUARTERS])
	{
		coins[QUARTERS] = int (change / 0.25);
		change -= coins[QUARTERS] * 0.25;
	}
	
	if (change >= 0.1 && coinsAvailable[DIMES]);
	{
		coins[DIMES] = int (change / 0.1);
		change -= coins[DIMES] * 0.1;
	}
	
	if (change >= 0.05 && coinsAvailable[NICKELS])
		coins[NICKELS] = int (change / 0.05);
}

// this function rounds the passed by reference money to the closest 0.05
float round (float fnum)
{
	float fTemp = fnum;
	const float TOL = 0.001;
	
	if (fmod (fnum, 0.05) > TOL)
		fTemp = fnum - fmod(fnum, 0.05) + 0.05;

	return fTemp;
}

int main ()
{
	float change = 1.95;

	//change = round(change);
	//out << change << endl;

	int coins[5] = {0};
	bool coinsAvailable [5] = {1, 1, 1, 1, 0};

	coinsToDispense(change, coins, coinsAvailable);
	
	cout << "  0.05  0.10  0.25  1.00  2.00" << endl;
	cout << "--------------------------------" << endl;
	
	for (int i = 0; i < 5; i++)
	{
		cout << setw(6) << coins[i];
	}
}
