#pragma once
#include "Sensor.h"
#include <iostream>
enum SensorType { AirqualitySensor = 1, TemperatureSensor, HumiditySensor };
class AirqualitySensor : public Sensor
{
private:
	string UnitOfMeasurment = "%";
public:
	AirqualitySensor(double MinSimulation, double MaxSimulation, string NewName);
};
class TemperatureSensor : public Sensor
{
private:
	string UnitOfMeasurment = "C";
public:
	TemperatureSensor(double MinSimulation, double MaxSimulation, string NewName);
};
class HumiditySensor : public Sensor
{
private:
	string UnitOfMeasurment = "AH";
public:
	HumiditySensor(double MinSimulation, double MaxSimulation, string NewName);
};