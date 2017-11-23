
task main()
{
	SensorType[S2] = sensorEV3_Color;
	SensorMode[S2] = modeEV3Color_Reflected;

  bool coinDetected = false;

	time1[T2] = 0;
	while(time1[T2] < 5000)
	{
		displayBigTextLine(0, "Refl: %d", SensorValue[S2]);
		if (SensorValue[S2] > 20)
			coinDetected = true;
		delay(25);
	}

	displayBigTextLine(2, "Det: %d", coinDetected);

	delay(5000);

}
