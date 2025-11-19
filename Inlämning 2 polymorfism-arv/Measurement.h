#pragma once
#include "Sensor.h"
#include <string>
using namespace std;

struct Measurement
{
public:
	std::string SensorName;
	double SensorMeasurement;
	std::string UnitOfMeasurment;
	std::string TimeStamp;
	void GetReading(const Sensor& NewSensor);
	void PrintMeasurement()const;
};