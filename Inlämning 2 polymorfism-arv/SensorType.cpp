#include "SensorType.h"
#include <iostream>


AirqualitySensor::AirqualitySensor(std::string NewName, double MinSimulation, double MaxSimulation)
	: Sensor(SensorType::Airquality, UnitOfMeasurment, NewName, MinSimulation, MaxSimulation) {
};

TemperatureSensor::TemperatureSensor(std::string NewName, double MinSimulation, double MaxSimulation)
	: Sensor(SensorType::Temperature, UnitOfMeasurment, NewName, MinSimulation, MaxSimulation) {
};

HumiditySensor::HumiditySensor(std::string NewName, double MinSimulation, double MaxSimulation)
	: Sensor(SensorType::Humidity, UnitOfMeasurment, NewName, MinSimulation, MaxSimulation) {
};
