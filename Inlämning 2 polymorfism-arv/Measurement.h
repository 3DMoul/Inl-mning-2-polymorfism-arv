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
	//detta tar värden från sensor klassen
	void GetReading(const Sensor& NewSensor);
	//detta skriver ut measurment värdena
	void PrintMeasurement()const;
};