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

// this function assumes that the function recieves the value of change * 100
// ex: 1 dollar of change should be change = 100
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

/*****************************
** COIN DISPENSER INTERFACE **
******************************/
