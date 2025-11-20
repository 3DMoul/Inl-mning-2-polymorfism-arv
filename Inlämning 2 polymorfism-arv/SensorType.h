#pragma once
#include <iostream>
#include "Sensor.h"
class AirqualitySensor : public Sensor
{
public:
	AirqualitySensor(std::string NewName, double MinSimulation, double MaxSimulation);
	double Read() const override;
};
class TemperatureSensor : public Sensor
{
public:
	TemperatureSensor(std::string NewName, double MinSimulation, double MaxSimulation);
	double Read() const override;
};
class HumiditySensor : public Sensor
{
public:
	HumiditySensor(std::string NewName, double MinSimulation, double MaxSimulation);
	double Read() const override;
};