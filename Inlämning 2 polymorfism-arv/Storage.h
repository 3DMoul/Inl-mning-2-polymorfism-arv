#pragma once
#include "TemperatureSensor.h"
#include "AirqualitySensor.h"
#include "Measurement.h"
#include <vector>
#include <fstream>

using namespace std;
class Storage
{
private:
	static vector <Measurement> MeasurmentsList;
public:
	static int SizeOfAirquality();
	static int SizeOfTemperature();
	static int SizeOfList();
	bool SearchForName(string Name);
	bool SearchForTimeStamp(string Name);
	static void GetMeasurementReading(const Measurement& NewMeasurement);
	static void PrintTemperatureReadings();
	static void PrintAirqualityReadings();
	static void PrintAll();
	static void WriteFile(string TimeStamp, string UnitOfMeasurment, string SensorName, double SensorReading);
	static void ReadFile();
	static void Visulisation(const char IN);
	double SumOfTemperature();
	double SumOfAirquality();
	static double TemperatureVariance(double SumOfTemp);
	static double AirqualityVariance(double SumOfAirqual);
	static void MinMaxTemperature();
	static void MinMaxAirquality();
};