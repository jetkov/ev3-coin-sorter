/*****************************
******** USER INPUT *********
*****************************/

void getInputAmounts(int & dollars, int & cents)
{
  displayBigTextLine(0, "Dispense: ");
  displayBigTextLine(8,  "    ^");
  displayBigTextLine(9, "  $%02d.%02d", 0, 0);
  displayBigTextLine(11, "    v");

  string coinType[5] = {"Nickel", "Dime", "Quarter", "Loonie", "Toonie"};
  short placeHolder = 1;

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
}

/*****************************
******** MONEY MATH *********
*****************************/

float round (float fnum)
{
  float fTemp = fnum;
  const float TOL = 0.001;

  if (fmod (fnum, 0.05) > TOL)
  fTemp = fnum - fmod(fnum, 0.05) + 0.05;

  return fTemp;
}

void coinsToDispense (float change, int coins[], bool coinsAvailable[])
{
  change = round(change);

  if (change >= 2 && coinsAvailable[TOONIES])
  {
    coins[TOONIES] = int (change / 2);

    change -= coins[TOONIES] * 2;
    change = round(change);
  }

  if (change >= 1 && coinsAvailable[LOONIES])
  {
    coins[LOONIES] = int (change);

    change -= coins[LOONIES];
    change = round(change);
  }

  if (change >= 0.25 && coinsAvailable[QUARTERS])
  {
    coins[QUARTERS] = int (change / 0.25);

    change -= coins[QUARTERS] * 0.25;
    change = round(change);
  }

  if (change >= 0.1 && coinsAvailable[DIMES]);
  {
    coins[DIMES] = int (change / 0.1);

    change -= coins[DIMES] * 0.1;
    change = round(change);
  }

  if (change >= 0.05 && coinsAvailable[NICKELS])
  {
    coins[NICKELS] = int (change / 0.05);

    change -= coins[NICKELS] * 0.05;
  }
}
