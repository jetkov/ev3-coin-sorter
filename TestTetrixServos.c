#include "EV3Servo-lib-UW.c"

task main()
{
	// configure servo controller port
	SensorType[S1] = sensorI2CCustom9V;

	// servo is plugged into SV2, set to rotate at 45
	setServoPosition(S1, 1, 30);

	int servoPos = 0;
	int servoSpeed = 0;

	while (true) {
		displayBigTextLine(0, "Position %d %%", servoPos);
		displayBigTextLine(2, "Speed %d %%", motorSpeed);

		while (getButtonPress(buttonAny) == 0) {}

		if (getButtonPress(buttonUp) && servoSpeed < 100)
			servoSpeed++;
		if (getButtonPress(buttonDown) && servoSpeed > -100)
			servoSpeed--;
	  if (getButtonPress(buttonLeft) && servoPos < 180)
			servoPos++;
		if (getButtonPress(buttonRight) && servoPos > -180)
			servoPos--;
		if (getButtonPress(buttonEnter))
		{
			servoPos = servoSpeed = 0;

		delay(100);


		setServoPosition(S1, 1, 30);
	}
}
