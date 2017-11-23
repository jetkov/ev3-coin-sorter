const int HOP_TIMER1 = T1, HOP_TIMER2 = T2, HOP_PORT = 0;
const int HOP_SPEED = 25, HOP_REVERSE_SPEED = 75, HOP_REVERSE_TIME = 250, HOP_REVERSE_INTERVAL = 5000;

task main()
{

	int time = 15000;

	time1[HOP_TIMER1] = 0;
	time1[HOP_TIMER2] = 0;

	while(time1[HOP_TIMER1] < time)
	{
		motor[HOP_PORT] = -HOP_SPEED;

		while (time1[HOP_TIMER2] < HOP_REVERSE_INTERVAL)
		{
			nMotorEncoder[HOP_PORT] = 0;
			delay(250);
			displayBigTextLine(0, "%d", nMotorEncoder[HOP_PORT]);
			if (nMotorEncoder[HOP_PORT] > -360 / HOP_SPEED)
			{
				motor[HOP_PORT] = HOP_REVERSE_SPEED;
				delay(HOP_REVERSE_TIME);
				motor[HOP_PORT] = -HOP_SPEED;
			}
		}

		time1[HOP_TIMER2] = 0;

		motor[HOP_PORT] = HOP_REVERSE_SPEED;
		delay(HOP_REVERSE_TIME);
	}

}