#pragma once
#include <vector>
#include <fstream>
#include "Sensor.h"
#include "Measurement.h"
class Storage
{
public:
	static std::vector <Measurement> getMeasurments();
	static int SizeOfAirquality();
	static int SizeOfTemperature();
	static int sizeOfHumidity();
	static int SizeOfList();
	bool SearchForName(std::string Name);
	bool SearchForTimeStamp(std::string Name);
	static void GetMeasurementReading(char type);
	static void PrintTemperatureReadings();
	static void PrintAirqualityReadings();
	static void printHymidityReadings();
	static void PrintAll();
	static void WriteFile(Measurement& NewMeasurementReadings);
	static void ReadFile();
	static void Visulisation(const char IN);
	double SumOfTemperature();
	double SumOfAirquality();
	double sumOfHumidity();
	static double TemperatureVariance(double SumOfTemp);
	static double AirqualityVariance(double SumOfAirqual);
	static double humidityVariance(double sumOfHumidity);
	static void MinMaxTemperature();
	static void MinMaxAirquality();
	static void minMaxHumidity();
private:
	static std::vector <Measurement> MeasurmentsList;
};