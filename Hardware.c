#include "EV3Servo-lib-UW.c"

/*****************************
********** HOPPER ***********
*****************************/

const int HOP_TIMER1 = T1, HOP_TIMER2 = T2, HOP_PORT = motorD;
const int HOP_SPEED = 25, HOP_REVERSE_SPEED = 75, HOP_REVERSE_TIME = 500, HOP_REVERSE_INTERVAL = 4500;

void runHopper(int time)
{

  time1[HOP_TIMER1] = 0;
  time1[HOP_TIMER2] = 0;

  while(time1[HOP_TIMER1] < time)
  {
    motor[HOP_PORT] = -HOP_SPEED;

    while (time1[HOP_TIMER2] < HOP_REVERSE_INTERVAL)
    {
      nMotorEncoder[HOP_PORT] = 0;
      delay(250);
      if (nMotorEncoder[HOP_PORT] > -360 / HOP_SPEED)
      {
        motor[HOP_PORT] = HOP_REVERSE_SPEED;
        delay(HOP_REVERSE_TIME);
        motor[HOP_PORT] = -HOP_SPEED;
        time1[HOP_TIMER1] = 0;
      }
    }

    time1[HOP_TIMER2] = 0;

    motor[HOP_PORT] = HOP_REVERSE_SPEED;
    delay(HOP_REVERSE_TIME);
  }

  motor[HOP_PORT] = 0;
}

const int USONIC_SENS_PT = S1, USONIC_SENS_THRESHOLD = 30;
const int HOP_TIMEOUT = 15000;

task autoHopper()
{
	while (getButtonPress(buttonBack) == 0)
	{
		while (SensorValue[USONIC_SENS_PT] > USONIC_SENS_THRESHOLD)
		{}

		runHopper(HOP_TIMEOUT);
	}
}

/*****************************
****** COIN DISPENSER *******
*****************************/

const int CLR_SENS_PT = S4, CLR_SENS_THRESHOLD = 13;

bool coinDispensed(int time)
{
	bool coinDetected = false;

	time1[T2] = 0;
	while(time1[T2] < time)
	{
		//displayBigTextLine(0, "Refl: %d", SensorValue[CLR_SENS_PT]);
		if (SensorValue[CLR_SENS_PT] > CLR_SENS_THRESHOLD)
		{
			coinDetected = true;
			displayBigTextLine(14, "Detected!");
			delay(750);
			displayBigTextLine(14, "");
		}
		delay(25);
	}

	return coinDetected;
}

const int SERVO_CTRLR_PT = S3;

const int DIME_MTR_PT = motorB, DIME_MTR_SPD = 10, DIME_DISPENSE_TIME = 5000;

const int NICKL_QRTR_SVO_PT = 1, NICKL_QRTR_OUT_POS = 5, NICKL_POS = 70, QRTR_POS = -58, ;
const int LNIE_TNIE_SVO_PT = 2, LNIE_TNIE_OUT_POS = 24, LNIE_POS = -46, TNIE_POS = 95;
const int SERVO_GETCOIN_DELAY = 600; // ms

const int COIN_SENSE_TIME = 1500;

void homeServos()
{
	setServoPosition(SERVO_CTRLR_PT, NICKL_QRTR_SVO_PT, NICKL_QRTR_OUT_POS);
	setServoPosition(SERVO_CTRLR_PT, LNIE_TNIE_SVO_PT, LNIE_TNIE_OUT_POS);
	delay(SERVO_GETCOIN_DELAY);
}

int getCoins(int coinType, int number)
{
	bool dispensed = true;
	int count = 0;

	switch (coinType)
	{
		// Nickels
		case 0:

			while (count < number && dispensed)
			{
				setServoPosition(SERVO_CTRLR_PT, NICKL_QRTR_SVO_PT, NICKL_POS);
				delay(SERVO_GETCOIN_DELAY);
				setServoPosition(SERVO_CTRLR_PT, NICKL_QRTR_SVO_PT, NICKL_QRTR_OUT_POS);
				dispensed = coinDispensed(COIN_SENSE_TIME);
				if (dispensed)
					count++;
			}
			break;

		// Dimes
		case 1:

			while (count < number && dispensed)
			{
				motor[DIME_MTR_PT] = DIME_MTR_SPD;

				nMotorEncoder[DIME_MTR_PT] = 0;

			  dispensed = false;

				time1[T3] = 0;
				while(time1[T3] < DIME_DISPENSE_TIME)
				{
					displayBigTextLine(0, "Refl: %d Time: %d", SensorValue[CLR_SENS_PT], time1[T3] / 1000);
					if (SensorValue[CLR_SENS_PT] > CLR_SENS_THRESHOLD)
						dispensed = true;
					delay(25);

					if (nMotorEncoder[DIME_MTR_PT] > 370)
						motor[DIME_MTR_PT] = 0;
				}

				motor[DIME_MTR_PT] = 0;

				if (dispensed)
					count++;
			}
			break;

		// Quarters
		case 2:

			while (count < number && dispensed)
			{
				setServoPosition(SERVO_CTRLR_PT, NICKL_QRTR_SVO_PT, QRTR_POS);
				delay(SERVO_GETCOIN_DELAY);
				setServoPosition(SERVO_CTRLR_PT, NICKL_QRTR_SVO_PT, NICKL_QRTR_OUT_POS);
				dispensed = coinDispensed(COIN_SENSE_TIME);
				if (dispensed)
					count++;
			}
			break;

		// Loonies
		case 3:

			while (count < number && dispensed)
			{
				setServoPosition(SERVO_CTRLR_PT, LNIE_TNIE_SVO_PT, LNIE_POS);
				delay(SERVO_GETCOIN_DELAY);
				setServoPosition(SERVO_CTRLR_PT, LNIE_TNIE_SVO_PT, LNIE_TNIE_OUT_POS);
				dispensed = coinDispensed(COIN_SENSE_TIME);
				if (dispensed)
					count++;
			}
			break;

		// Toonies
		case 4:

			while (count < number && dispensed)
			{
				setServoPosition(SERVO_CTRLR_PT, LNIE_TNIE_SVO_PT, TNIE_POS);
				delay(SERVO_GETCOIN_DELAY);
				setServoPosition(SERVO_CTRLR_PT, LNIE_TNIE_SVO_PT, LNIE_TNIE_OUT_POS);
				dispensed = coinDispensed(COIN_SENSE_TIME);
				if (dispensed)
					count++;
			}
			break;

		default:
			return -1;
			break;
	}

	return count;
}
