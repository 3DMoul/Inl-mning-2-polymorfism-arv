#include "Utility.h"
#include "Sensor.h"
#include <iostream>
#include <string>

Sensor::Sensor(SensorType type, std::string UnitOfMeasurment, std::string SensorName, double MinSimulation, double MaxSimulation)
	: type(type), SensorName(SensorName), UnitOfMeasurment(UnitOfMeasurment), MinSimulation(MinSimulation), MaxSimulation(MaxSimulation) {};
double Sensor::Read() const
{
	return Utility::randomMaxMinDecimal(MinSimulation, MaxSimulation);
}
string Sensor::name() const
{
	return SensorName;
}
double Sensor::minValue() const
{
	return MinSimulation;
}
double Sensor::maxValue() const
{
	return MaxSimulation;
}
string Sensor::GetUnitOfMeasurment() const
{
	return UnitOfMeasurment;
}
SensorType Sensor::sensorType()const
{
	return type;
}