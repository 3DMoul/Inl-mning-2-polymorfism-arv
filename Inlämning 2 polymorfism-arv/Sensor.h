#pragma once
#include <iostream>
#include <string>
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
	double minValue() const;
	double maxValue() const;
	std::string GetUnitOfMeasurment() const;
	SensorType sensorType()const;
};