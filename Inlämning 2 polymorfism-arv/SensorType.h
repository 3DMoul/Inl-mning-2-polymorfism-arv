#pragma once
#include "Sensor.h"
#include <iostream>
enum class SensorType { AirqualitySensor = 'A', TemperatureSensor = 'T', HumiditySensor = 'H'};
class AirqualitySensor : public Sensor
{
private:
	std::string UnitOfMeasurment = "%";
public:
	AirqualitySensor(std::string NewName, double MinSimulation, double MaxSimulation);
};
class TemperatureSensor : public Sensor
{
private:
	std::string UnitOfMeasurment = "C";
public:
	TemperatureSensor(std::string NewName, double MinSimulation, double MaxSimulation);
};
class HumiditySensor : public Sensor
{
private:
	std::string UnitOfMeasurment = "AH";
public:
	HumiditySensor(std::string NewName, double MinSimulation, double MaxSimulation);
};