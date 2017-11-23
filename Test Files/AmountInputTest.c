task main()
{
	displayBigTextLine(0, "Dispense: ");
	displayBigTextLine(8,  "    ^");
	displayBigTextLine(9, "  $%02d.%02d", 0, 0);
	displayBigTextLine(11, "    v");

	string coinType[5] = {"Nickel", "Dime", "Quarter", "Loonie", "Toonie"};
	short placeHolder = 1;
	int dollars = 0, cents = 0;

	while (getButtonPress(buttonBack) == 0)
	{
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

}
