/****************************
******** USER INPUT *********
*****************************/

int getInputAmounts() // returns cents
{
  displayBigTextLine(0, "Dispense: ");
  displayBigTextLine(8,  "    ^");
  displayBigTextLine(9, "  $%02d.%02d", 0, 0);
  displayBigTextLine(11, "    v");

  string coinType[5] = {"Nickel", "Dime", "Quarter", "Loonie", "Toonie"};
  short placeHolder = 1;

  int dollars = 0, cents = 0;

  while (getButtonPress(buttonEnter) == 0)
  {
    while (getButtonPress(buttonAny) == 0) {}

    if (getButtonPress(buttonRight))
    {
      while (getButtonPress(buttonRight)) {}
      placeHolder = 0;
      displayBigTextLine(8,  "       ^");
      displayBigTextLine(11, "       v");
    }
    else if (getButtonPress(buttonLeft))
    {
      while (getButtonPress(buttonLeft)) {}
      placeHolder = 1;
      displayBigTextLine(8,  "    ^");
      displayBigTextLine(11, "    v");
    }
    else if (getButtonPress(buttonUp))
    {
      while (getButtonPress(buttonUp)) {}
      if (placeHolder == 0 && cents < 100)
      cents += 5;
      if (placeHolder == 1 && dollars < 100)
      dollars++;
    }
    else if (getButtonPress(buttonDown))
    {
      while (getButtonPress(buttonDown)) {}
      if (placeHolder == 0 && cents > 0)
      cents -= 5;
      if (placeHolder == 1 && dollars > 0)
      dollars--;
    }

    displayBigTextLine(9, "  $%02d.%02d", dollars, cents);

    delay(100);
  }

  displayBigTextLine(9, "  $%02d.%02d", 0, 0);

  return 100 * dollars + cents;
}

/*****************************
******** MONEY MATH **********
******************************/

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

/*****************************
** COIN DISPENSER INTERFACE **
******************************/
