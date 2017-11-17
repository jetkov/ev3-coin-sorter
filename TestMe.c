#include "EV3Servo-lib-UW.c"

const int HOPPER_PORT = 0, HOPPER_SPEED = 45, HOPPER_REVERSE_SPEED = 75;

void runHopper(int time)
{
	motor[HOPPER_PORT] = -HOPPER_SPEED;

	time1[T1] = 0;
	while (time1[T1] < time)
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

const int CLR_SENS_PT = S4, CLR_SENS_THRESHOLD = 20;

bool coinDispensed(int time)
{
	bool coinDetected = false;

	time1[T2] = 0;
	while(time1[T2] < time)
	{
		//displayBigTextLine(0, "Refl: %d", SensorValue[CLR_SENS_PT]);
		if (SensorValue[CLR_SENS_PT] > CLR_SENS_THRESHOLD)
			coinDetected = true;
		delay(25);
	}

	return coinDetected;
}

const int SERVO_CTRLR_PT = S1;

const int DIME_MTR_PT = motorB, DIME_MTR_SPD = 10, DIME_DISPENSE_TIME = 2000;

const int NICKL_QRTR_SVO_PT = 1, NICKL_QRTR_OUT_POS = 11, NICKL_POS = 74, QRTR_POS = -53, ;
const int LNIE_TNIE_SVO_PT = 2, LNIE_TNIE_OUT_POS = 24, LNIE_POS = -46, TNIE_POS = 95;
const int SERVO_GETCOIN_DELAY = 600; // ms

const int COIN_SENSE_TIME = 1000;

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

				bool dispensed = false;

				time1[T3] = 0;
				while(time1[T3] < DIME_DISPENSE_TIME)
				{
					if (SensorValue[CLR_SENS_PT] > CLR_SENS_THRESHOLD)
						dispensed = true;
					delay(25);

					if (nMotorEncoder[DIME_MTR_PT] >= 500)
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


task main()
{
	SensorType[CLR_SENS_PT] = sensorEV3_Color;
	delay(50);
	SensorMode[CLR_SENS_PT] = modeEV3Color_Reflected;
	delay(50);

	homeServos();

	/*
	getCoins(0, 2);
	getCoins(1, 2);
	getCoins(2, 2);
	getCoins(3, 2);
	getCoins(4, 2);
  */

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

		displayBigTextLine(14, "Detected: %d", getCoins(typeIndex, number));

	}

}
