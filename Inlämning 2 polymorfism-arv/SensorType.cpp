#include "Sensor.h"
#include "SensorType.h"
#include <iostream>


AirqualitySensor::AirqualitySensor(std::string NewName, double MinSimulation, double MaxSimulation)
	: Sensor(SensorType::Airquality, NewName, MinSimulation, MaxSimulation) {
};

TemperatureSensor::TemperatureSensor(std::string NewName, double MinSimulation, double MaxSimulation)
	: Sensor(SensorType::Temperature, NewName, MinSimulation, MaxSimulation) {
};

HumiditySensor::HumiditySensor(std::string NewName, double MinSimulation, double MaxSimulation)
	: Sensor(SensorType::Humidity, NewName, MinSimulation, MaxSimulation) {
};
