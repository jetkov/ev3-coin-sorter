
task main()
{

	displayBigTextLine(0, "Dispense: ");
	displayBigTextLine(8, "   ^");
	displayBigTextLine(11, "   v");

	string coinType[5] = {"Nickel", "Dime", "Quarter", "Loonie", "Toonie"};
	int typeIndex = 0;
	int number = 1;
	const int MAX_NUM = 20;

	displayBigTextLine(4, "  < >  %s", coinType[0]);
	displayBigTextLine(9, "       %d", number);

	while (getButtonPress(buttonBack) == 0)
	{
		while (getButtonPress(buttonEnter) == 0)
		{
			while (getButtonPress(buttonAny) == 0) {}

			if (getButtonPress(buttonRight) && typeIndex < 4)
			{
				while (getButtonPress(buttonRight)) {}
				typeIndex++;
			}
			else if (getButtonPress(buttonLeft) && typeIndex > 0)
			{
				while (getButtonPress(buttonLeft)) {}
				typeIndex--;
			}
			else if (getButtonPress(buttonUp) && number < MAX_NUM)
			{
				while (getButtonPress(buttonUp)) {}
				number++;
			}
			else if (getButtonPress(buttonDown) && number > 0)
			{
				while (getButtonPress(buttonDown)) {}
				number--;
			}

			displayBigTextLine(4, "  < >  %s", coinType[typeIndex]);
			displayBigTextLine(9, "       %d", number);

			delay(100);

		}

		displayBigTextLine(14, "%s: %d", coinType[typeIndex], number);

		delay(1000);
	}

}
