#include "Utility.h"
#include "Sensor.h"
#include <iostream>

void Measurement::GetReading(const Sensor& NewSensor)
{
	SensorName = NewSensor.name();
	SensorMeasurement = NewSensor.Read();
	UnitOfMeasurment = NewSensor.GetUnitOfMeasurment();
	TimeStamp = Utility::TimeGenerator();
}
void Measurement::PrintMeasurement()const
{
	cout << SensorName << " \n" << TimeStamp << "\n" << SensorMeasurement << " " << UnitOfMeasurment << endl;
}
