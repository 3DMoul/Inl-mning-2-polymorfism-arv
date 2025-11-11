#include "Sensor.h"
#include "SensorType.h"
#include <iostream>

AirqualitySensor::AirqualitySensor(double MinSimulation, double MaxSimulation, string NewName)
	: Sensor(NewName, MinSimulation, MaxSimulation) {
};

TemperatureSensor::TemperatureSensor(double MinSimulation, double MaxSimulation, string NewName)
	: Sensor(NewName, MinSimulation, MaxSimulation) {
};

HumiditySensor::HumiditySensor(double MinSimulation, double MaxSimulation, string NewName)
	: Sensor(NewName, MinSimulation, MaxSimulation) {
};
