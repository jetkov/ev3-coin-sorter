task main()
{
	displayBigTextLine(0, "Dispense: ");
	displayBigTextLine(8,  "   ^");
	displayBigTextLine(11, "   v");

	string coinType[5] = {"Nickel", "Dime", "Quarter", "Loonie", "Toonie"};
	short placeHolder = 0;
	int dollars = 0, cents = 0;
	const int MAX_NUM = 99;

	while (getButtonPress(buttonBack) == 0)
	{
		while (getButtonPress(buttonEnter) == 0)
		{
      while (getButtonPress(buttonAny) == 0) {}

      if (getButtonPress(buttonRight))
      {
        while (getButtonPress(buttonRight)) {}
        placeHolder = 0;
        displayBigTextLine(8,  "     ^");
        displayBigTextLine(11, "     v");
      }
      else if (getButtonPress(buttonLeft) && typeIndex > 0)
      {
        while (getButtonPress(buttonLeft)) {}
        placeHolder = 1;
        displayBigTextLine(8,  "   ^");
        displayBigTextLine(11, "   v");
      }
      else if (getButtonPress(buttonUp))
      {
        while (getButtonPress(buttonUp)) {}
        if (placeHolder == 0 && cents < 100)
          cents++;
        if (placeHolder == 1 && dollars < 100)
          dollars++;
      }
      else if (getButtonPress(buttonDown))
      {
        while (getButtonPress(buttonDown)) {}
        if (placeHolder == 0 && cents > 0)
          cents--;
        if (placeHolder == 1 && dollars > 0)
          dollars--;
      }

      displayBigTextLine(9, "  $%d.%d", dollars, cents);

      delay(100);
		}

		displayBigTextLine(14, "%s: %d", coinType[typeIndex], number);

		delay(1000);
	}

}
