/****************************
******** USER INPUT *********
*****************************/

int getInputAmounts() // returns cents
{
  displayBigTextLine(0, "Dispense: ");
  displayBigTextLine(7,  "  ^");
  displayBigTextLine(8, "$%02d.%02d  Preset", 0, 0);
  displayBigTextLine(10, "  v");

  string preset[5] = {"Preset", "Coffee", "Latte", "Donut", "Max"};
  int presetValue[5] = {0, 125, 340, 150, 9999};
  int presetIndex = 0;

  short placeHolder = 0;

  int dollars = 0, cents = 0;

  while (getButtonPress(buttonEnter) == 0)
  {
    while (getButtonPress(buttonAny) == 0) {}

    if (getButtonPress(buttonRight))
    {
      while (getButtonPress(buttonRight)) {}
      if (placeHolder < 2)
      	placeHolder++;
    }
    else if (getButtonPress(buttonLeft))
    {
      while (getButtonPress(buttonLeft)) {}
      if (placeHolder > 0)
      	placeHolder--;
    }
    else if (getButtonPress(buttonUp))
    {
    	while (getButtonPress(buttonUp)) {}
    	if (placeHolder == 0 && dollars < 100)
      	dollars++;
      if (placeHolder == 1 && cents < 100)
      	cents += 5;
     	if (placeHolder == 2 && presetIndex < 4)
     		presetIndex++;


    }
    else if (getButtonPress(buttonDown))
    {
      while (getButtonPress(buttonDown)) {}
      if (placeHolder == 0 && dollars > 0)
      	dollars--;
      if (placeHolder == 1 && cents > 0)
      	cents -= 5;
     	if (placeHolder == 2 && presetIndex > 0)
     		presetIndex--;
    }

    switch(placeHolder)
    {
      case 0:
        displayBigTextLine(7,  "  ^");
  			displayBigTextLine(10, "  v");
  			break;
  	  case 1:
  	    displayBigTextLine(7,  "     ^");
  			displayBigTextLine(10, "     v");
  			break;
  		case 2:
  		  displayBigTextLine(7,  "          ^");
  			displayBigTextLine(10, "          v");
  			break;
    }

    if (presetIndex > 0)
    {
    	dollars = presetValue[presetIndex] / 100;
    	cents = presetValue[presetIndex] % 100;
  	}

    displayBigTextLine(8, "$%02d.%02d  %s", dollars, cents, preset[presetIndex]);

    delay(100);
  }

  displayBigTextLine(8, "$%02d.%02d  Preset", 0, 0);

  return 100 * dollars + cents;
}

/*****************************
******** MONEY MATH **********
******************************/

const int NICKEL_VAL = 5, DIME_VAL = 10, QUARTER_VAL = 25, LOONIE_VAL = 100, TOONIE_VAL = 200;

int checkCoin(int & change, int coinValue)
{
	int nCoin = change / coinValue;
	change %= coinValue;

	return nCoin;
}

// This function assumes that the function recieves the value of change in cents, as well as in increments of 5 only
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

/*****************************
** COIN DISPENSER INTERFACE **
******************************/
