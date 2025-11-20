#pragma once
#include <iostream>
#include "Sensor.h"
class AirqualitySensor : public Sensor
{
public:
	AirqualitySensor(std::string NewName, double MinSimulation, double MaxSimulation);
	//har get denna för att airquality behöver inte decimaler i sina measurments
	double Read() const override;
};
class TemperatureSensor : public Sensor
{
public:
	TemperatureSensor(std::string NewName, double MinSimulation, double MaxSimulation);
	//denna ger measurment med decimaler
	double Read() const override;
};
class HumiditySensor : public Sensor
{
public:
	HumiditySensor(std::string NewName, double MinSimulation, double MaxSimulation);
	//har get denna för att Humidity behöver inte decimaler i sina measurments
	double Read() const override;
};