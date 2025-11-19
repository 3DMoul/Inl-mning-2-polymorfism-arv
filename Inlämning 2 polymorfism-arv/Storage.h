#pragma once
#include <vector>
#include <fstream>
#include "Sensor.h"
#include "Measurement.h"
class Storage
{
public:
	static std::vector <Measurement> getMeasurments();
	static std::unique_ptr<Sensor> MakeSensor(SensorType type, const std::string& newname, double min, double max);
	static int sizeOfTypeSensor(const std::string& unitOfunitOfMeasurement);
	static int SizeOfList();
	bool SearchForName(std::string Name);
	bool SearchForTimeStamp(std::string Name);
	static void GetMeasurementReading(char type);
	static void printByTypeSensor(const std::string& unitOfMeasurement, const std::string& type);
	static void WriteFile(Measurement& NewMeasurementReadings);
	static void ReadFile();
	static void VisulisationOfTypeSensor(const std::string& unitOfMeasurement);
	double sumOfTypeSensor(const std::string& unitOfMeasurement);
	static double varianceFromTypeSensor(double& sum, const std::string& unitOfMeasurement);
	static void minMaxOfTypeSensor(const std::string& unitOfMeasurement);
private:
	static std::vector <Measurement> MeasurmentsList;
};