#pragma once
#include <iostream>
#include "Sensor.h"
class AirqualitySensor : public Sensor
{
public:
	AirqualitySensor(std::string NewName, double MinSimulation, double MaxSimulation);
private:
	std::string UnitOfMeasurment = "%";
};
class TemperatureSensor : public Sensor
{
public:
	TemperatureSensor(std::string NewName, double MinSimulation, double MaxSimulation);
private:
	std::string UnitOfMeasurment = "C";
};
class HumiditySensor : public Sensor
{
public:
	HumiditySensor(std::string NewName, double MinSimulation, double MaxSimulation);
private:
	std::string UnitOfMeasurment = "AH";
};