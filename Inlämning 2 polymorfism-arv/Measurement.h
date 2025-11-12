#pragma once
#include "Sensor.h"
#include <string>
using namespace std;

struct Measurement
{
	static std::string SensorName;
	static double SensorMeasurement;
	static std::string UnitOfMeasurment;
	static std::string TimeStamp;
	static void GetReading(unique_ptr<Sensor>& NewSensor);
	void PrintMeasurement()const;
};