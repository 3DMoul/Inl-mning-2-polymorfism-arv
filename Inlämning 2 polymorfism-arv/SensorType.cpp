#include "Sensor.h"
#include "SensorType.h"
#include <iostream>


AirqualitySensor::AirqualitySensor(std::string NewName, double MinSimulation, double MaxSimulation)
	: Sensor(NewName, MinSimulation, MaxSimulation) {
};

TemperatureSensor::TemperatureSensor(std::string NewName, double MinSimulation, double MaxSimulation)
	: Sensor(NewName, MinSimulation, MaxSimulation) {
};

HumiditySensor::HumiditySensor(std::string NewName, double MinSimulation, double MaxSimulation)
	: Sensor(NewName, MinSimulation, MaxSimulation) {
};
