task main()
{

	int motorSpeed = 0;

	while (true) {
		displayBigTextLine(0, "Speed %d %%", motorSpeed);

		while (getButtonPress(buttonAny) == 0) {}

		if (getButtonPress(buttonUp) && motorSpeed < 100)
			motorSpeed++;
		if (getButtonPress(buttonDown) && motorSpeed > -100)
			motorSpeed--;
		if (getButtonPress(buttonEnter))
			motorSpeed = 0;

		delay(50);

		motor[motorA] = motorSpeed;
	}
}
