// this function assumes that the function recieves the value of change * 100
// ex: 1 dollar of change should be change = 100
void coinsToDispense (int change, int & nNickels, int & nDimes, int & nQuarters, int & nLoonies, int & nToonies, bool & yNickels, bool & yDimes, bool & yQuarters, bool & yLoonies, bool & yToonies)
{
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
}

task main ()
{
	int change = 355;

	int nNickels = 0, nDimes = 0, nQuarters = 0, nLoonies = 0, nToonies = 0;
	bool yNickels = true, yDimes = true, yQuarters = true, yLoonies = true, yToonies = true;

	coinsToDispense(change, nNickels, nDimes, nQuarters, nLoonies, nToonies, yNickels, yDimes, yQuarters, yLoonies, yToonies);
}

const int TOONIES = 4;
const int LOONIES = 3;
const int QUARTERS = 2;
const int DIMES = 1;
const int NICKELS = 0;

void printInfo (float change, int coins[], bool coinsAvailable[])
{
	cout << "  0.05  0.10  0.25  1.00  2.00" << endl;
	cout << "--------------------------------" << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << setw(6) << coins[i];
	}

	cout << endl;
}

int main ()
{
	int change = 355;

	int coins[5] = {0,0,0,0,0};
	bool coinsAvailable [5] = {1, 1, 1, 1, 1};

	coinsToDispense(change, coins, coinsAvailable);

	printInfo(change, coins, coinsAvailable);
}
