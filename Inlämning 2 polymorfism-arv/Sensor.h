#pragma once
#include <iostream>
using namespace std;
class Sensor
{
private:
	string SensorName;
	double MinSimulation, MaxSimulation;
	string UnitOfMeasurment;
public:
	Sensor(string SensorName, double MinSimulation, double MaxSimulation);
	double Read(double MinSimulation, double MaxSimulation);
	string name() const;
	string GetUnitOfMeasurment() const;
};