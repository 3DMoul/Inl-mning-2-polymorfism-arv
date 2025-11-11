#pragma once
#include <string>
using namespace std;

struct Measurement
{
	string SensorName;
	double Measurement;
	string UnitOfMeasurment;
	string TimeStamp;
	void GetReading(string NewSensorName, double NewMeasurement, string NewUnitOfMeasurment, string NewTimeStamp);
	void PrintMeasurement()const;
};