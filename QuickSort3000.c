#include "Interface.c"
#include "Hardware.c"

task main()
{
	startTask(autoHopper);
	homeServos();

  while (getButtonPress(buttonBack) == 0)
  {
    int change = getInputAmounts();

    int nNickels = -1, nDimes = -1, nQuarters = -1, nLoonies = -1, nToonies = -1;
    bool yNickels = true, yDimes = true, yQuarters = true, yLoonies = true, yToonies = true;

    coinsToDispense(change, nNickels, nDimes, nQuarters, nLoonies, nToonies,
    							  yNickels, yDimes, yQuarters, yLoonies, yToonies);

    while (nNickels != 0 && nDimes != 0 && nQuarters != 0 && nLoonies != 0 && nToonies != 0)
  	{
	    nNickels = getCoins(0, nNickels);
	    nDimes = getCoins(1, nDimes);
	    nQuarters = getCoins(2, nQuarters);
	    nLoonies = getCoins(3, nLoonies);
	    nToonies = getCoins(4, nToonies);

	    yNickels = (bool) nNickels;
	    yDimes = (bool) nDimes;
	    yQuarters = (bool) nQuarters;
	    yLoonies = (bool) nLoonies;
	    yToonies = (bool) nToonies;

	    change = nNickels * 5 + nDimes * 10 + nQuarters * 25 + nLoonies * 100 + nToonies * 200;
	 	}

  }
}
