const int HOPPER_PORT = 0, HOPPER_SPEED = 45, HOPPER_REVERSE_SPEED = 75;

task main()
{

	motor[HOPPER_PORT] = -HOPPER_SPEED;

	while (true)
	{
		nMotorEncoder[HOPPER_PORT] = 0;
		delay(500);
		displayBigTextLine(0, "%d", nMotorEncoder[HOPPER_PORT]);
		if (nMotorEncoder[HOPPER_PORT] > -360 / HOPPER_SPEED)
		{
			motor[HOPPER_PORT] = HOPPER_REVERSE_SPEED;
			delay(250);
			motor[HOPPER_PORT] = -HOPPER_SPEED;
		}
	}

}
