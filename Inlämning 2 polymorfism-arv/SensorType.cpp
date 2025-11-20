#include <iostream>
#include "SensorType.h"
#include "Utility.h"


AirqualitySensor::AirqualitySensor(std::string NewName, double MinSimulation, double MaxSimulation)
	: Sensor(SensorType::Airquality, "%", NewName, MinSimulation, MaxSimulation) {
};
double AirqualitySensor::Read() const
{
	return Utility::randomMaxMin(minValue(), maxValue());
}

TemperatureSensor::TemperatureSensor(std::string NewName, double MinSimulation, double MaxSimulation)
	: Sensor(SensorType::Temperature, "C", NewName, MinSimulation, MaxSimulation) {
};
double TemperatureSensor::Read() const
{
	return Utility::randomMaxMinDecimal(minValue(), maxValue());
}


HumiditySensor::HumiditySensor(std::string NewName, double MinSimulation, double MaxSimulation)
	: Sensor(SensorType::Humidity, "AH", NewName, MinSimulation, MaxSimulation) {
};
double HumiditySensor::Read() const
{
	return Utility::randomMaxMin(minValue(), maxValue());
}
