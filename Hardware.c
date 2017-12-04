#include "EV3Servo-lib-UW.c"

/*****************************
********** HOPPER ***********
*****************************/

// AUTHOR: Suchir Navalyal

const int HOP_RUN_TIMER = T1, HOP_REVERSE_INTERVAL_TIMER = T2, HOP_PORT = motorD;
const int HOP_SPEED = 25, HOP_REVERSE_SPEED = 75, HOP_REVERSE_TIME = 500, HOP_REVERSE_INTERVAL = 4500;

// Runs the hopper motor with feedback control. If a motor stall is detected (using the encoder)
// the hopper is run in reverse for a short time to unjam stuck coins. Additionally a interval
// based reverse feature is in place to prevent coin buildups.
void runHopper(int time)
{

  time1[HOP_RUN_TIMER] = 0;
  time1[HOP_REVERSE_INTERVAL_TIMER] = 0;

  while(time1[HOP_RUN_TIMER] < time)
  {
    motor[HOP_PORT] = -HOP_SPEED;

    while (time1[HOP_REVERSE_INTERVAL_TIMER] < HOP_REVERSE_INTERVAL)
    {
      nMotorEncoder[HOP_PORT] = 0;
      delay(250);
      if (nMotorEncoder[HOP_PORT] > -360 / HOP_SPEED)
      {
        motor[HOP_PORT] = HOP_REVERSE_SPEED;
        delay(HOP_REVERSE_TIME);
        motor[HOP_PORT] = -HOP_SPEED;
        time1[HOP_RUN_TIMER] = 0;
      }
    }

    time1[HOP_REVERSE_INTERVAL_TIMER] = 0;

    motor[HOP_PORT] = HOP_REVERSE_SPEED;
    delay(HOP_REVERSE_TIME);
  }

  motor[HOP_PORT] = 0;
}

const int USONIC_SENS_PT = S1, USONIC_SENS_THRESHOLD = 30;
const int HOP_TIMEOUT = 15000;

// Runs parallel to the rest of the program, to run the hopper when coins are placed into it
// (triggered by a hand passing over the ultrasonic sensor).
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

// AUTHOR: Alex Petkovic

const int CLR_SENS_PT = S4, CLR_SENS_THRESHOLD = 13, COIN_DETECT_TIMER = T3;

// Checks if a coin is dispensed withing the given timeframe, using the colour sensor.
bool coinDispensed(int time)
{
  bool coinDetected = false;

  time1[COIN_DETECT_TIMER] = 0;
  while(time1[COIN_DETECT_TIMER] < time)
  {
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

// Dime dispenser module specific constants (as dimes are run on an EV3 motor)
const int SERVO_CTRLR_PT = S3;
const int DIME_MTR_PT = motorB, DIME_MTR_SPD = 10, DIME_DISPENSE_TIME = 5000;

// Port and position constants for the rest of the coins dispensing modules,
// which are run on standard 180 degree servos
const int NICKL_QRTR_SVO_PT = 1, NICKL_QRTR_OUT_POS = 5, NICKL_POS = 70, QRTR_POS = -58;
const int LNIE_TNIE_SVO_PT = 2, LNIE_TNIE_OUT_POS = 24, LNIE_POS = -46, TNIE_POS = 95;
const int SERVO_GETCOIN_DELAY = 600;

// The amount of time alloted for a dispensed coin to clear the system
const int COIN_SENSE_TIME = 1500;

// Returns the coin dispensing servos to their home position (at the output hole).
void homeServos()
{
  setServoPosition(SERVO_CTRLR_PT, NICKL_QRTR_SVO_PT, NICKL_QRTR_OUT_POS);
  setServoPosition(SERVO_CTRLR_PT, LNIE_TNIE_SVO_PT, LNIE_TNIE_OUT_POS);
  delay(SERVO_GETCOIN_DELAY);
}

const int DIME_MOTOR_TIMER = T4;

// Dispenses a specified amount of coins of a specific type, and returns the amount
// of coins that were successfully dispensed.
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
    // Since the dime dispenser module is operated on a EV3 motor with an encoder,
    // a separate loop was necessary to also allow for checking of coin dispensing
    // during the dispensing operation as it was slower and more unpredicatable
    // than the servos.
    case 1:
    while (count < number && dispensed)
    {
      motor[DIME_MTR_PT] = DIME_MTR_SPD;
      nMotorEncoder[DIME_MTR_PT] = 0;
      dispensed = false;
      time1[DIME_MOTOR_TIMER] = 0;

      while(time1[DIME_MOTOR_TIMER] < DIME_DISPENSE_TIME)
      {
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
