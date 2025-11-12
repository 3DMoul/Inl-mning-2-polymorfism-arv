#pragma once
#include <iostream>
#include <string>
class Sensor
{
private:
	std::string SensorName;
	double MinSimulation, MaxSimulation;
	std::string UnitOfMeasurment;
public:
	Sensor(std::string SensorName, double MinSimulation, double MaxSimulation);
	virtual ~Sensor() = default;
	double Read() const;
	std::string name() const;
	std::string GetUnitOfMeasurment() const;
};