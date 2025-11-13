#include "Utility.h"
#include "Sensor.h"
#include <iostream>
#include <string>

Sensor::Sensor(SensorType type, std::string SensorName, double MinSimulation, double MaxSimulation)
	: type(type), SensorName(SensorName), MinSimulation(MinSimulation), MaxSimulation(MaxSimulation) {};
double Sensor::Read() const
{
	return Utility::RandomTempreture(MinSimulation, MaxSimulation);
}
string Sensor::name() const
{
	return SensorName;
}
string Sensor::GetUnitOfMeasurment() const
{
	return UnitOfMeasurment;
}