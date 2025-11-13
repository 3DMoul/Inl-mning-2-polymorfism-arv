#pragma once
#include <iostream>
#include <string>
#include "SensorType.h"
enum class SensorType { Airquality = 'A', Temperature = 'T', Humidity = 'H' };

class Sensor
{
private:
	std::string SensorName;
	double MinSimulation, MaxSimulation;
	std::string UnitOfMeasurment;
	SensorType type;
public:
	Sensor(SensorType type, std::string SensorName, double MinSimulation, double MaxSimulation);
	virtual ~Sensor() = default;
	double Read() const;
	std::string name() const;
	std::string GetUnitOfMeasurment() const;
};