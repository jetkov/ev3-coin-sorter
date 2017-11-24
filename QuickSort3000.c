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
    int nNickelsR = 0, nDimesR = 0, nQuartersR = 0, nLooniesR = 0, nTooniesR = 0;
    bool yNickels = true, yDimes = true, yQuarters = true, yLoonies = true, yToonies = true;

    while (change > 0)
  	{
  		coinsToDispense(change, nNickels, nDimes, nQuarters, nLoonies, nToonies,
    						  	  yNickels, yDimes, yQuarters, yLoonies, yToonies);

    	displayTextLine(15, "%dN %dD %dQ %dL %dT", nNickels, nDimes, nQuarters, nLoonies, nToonies);

    	delay(2000);

    	// Number of each coin output stored in nCoin
	    nNickelsR = getCoins(0, nNickels);
	    nDimesR = getCoins(1, nDimes);
	    nQuartersR = getCoins(2, nQuarters);
	    nLooniesR = getCoins(3, nLoonies);
	    nTooniesR = getCoins(4, nToonies);

	    // Comares wanted outout to what actually got but if was false before remains false
	    yNickels = yNickels && nNickelsR == nNickels;
	    yDimes = yDimes && nDimesR == nDimes;
	    yQuarters = yQuarters && nQuartersR == nQuarters;
	    yLoonies = yLoonies && nLooniesR == nLoonies;
	    yToonies = yToonies && nTooniesR == nToonies;

	    change = change - (nNickelsR * 5 + nDimesR * 10 + nQuartersR * 25 + nLooniesR * 100 + nTooniesR * 200);

	    displayTextLine(14, "%dN %dD %dQ %dL %dT", yNickels, yDimes, yQuarters, yLoonies, yToonies);
	    displayTextLine(15, "%dN %dD %dQ %dL %dT CHANGE LEFT: %d", nNickelsR, nDimesR, nQuartersR, nLooniesR, nTooniesR, change);

	    delay(2000);

	 	}

  }
}
