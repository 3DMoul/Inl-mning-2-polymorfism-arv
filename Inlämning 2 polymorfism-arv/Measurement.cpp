#include "Measurement.h"
#include <iostream>

void Measurement::GetReading(string NewSensorName, double NewMeasurement, string NewUnitOfMeasurment, string NewTimeStamp)
{
	SensorName = NewSensorName;
	Measurement = NewMeasurement;
	UnitOfMeasurment = NewUnitOfMeasurment;
	TimeStamp = NewTimeStamp;
}
void Measurement::PrintMeasurement()const
{
	cout << SensorName << " \n" << TimeStamp << "\n" << Measurement << " " << UnitOfMeasurment << endl;
}
