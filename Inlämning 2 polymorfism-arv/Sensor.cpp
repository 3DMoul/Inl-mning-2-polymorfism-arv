#include "Utility.h"
#include "Sensor.h"
#include <iostream>
#include <string>

Sensor::Sensor(std::string SensorName, double MinSimulation, double MaxSimulation)
	: SensorName(SensorName), MinSimulation(MinSimulation), MaxSimulation(MaxSimulation) {};
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