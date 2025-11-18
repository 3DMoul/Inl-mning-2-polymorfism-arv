#pragma once
#include <vector>
#include <fstream>
#include "Sensor.h"
#include "Measurement.h"
class Storage
{
private:
	static std::vector <Measurement> MeasurmentsList;
public:
	static int SizeOfAirquality();
	static int SizeOfTemperature();
	static int SizeOfList();
	bool SearchForName(std::string Name);
	bool SearchForTimeStamp(std::string Name);
	static void GetMeasurementReading(char type);
	static void PrintTemperatureReadings();
	static void PrintAirqualityReadings();
	static void PrintAll();
	static void WriteFile(Measurement& NewMeasurementReadings);
	static void ReadFile();
	static void Visulisation(const char IN);
	double SumOfTemperature();
	double SumOfAirquality();
	static double TemperatureVariance(double SumOfTemp);
	static double AirqualityVariance(double SumOfAirqual);
	static void MinMaxTemperature();
	static void MinMaxAirquality();
};