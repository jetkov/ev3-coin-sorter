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
