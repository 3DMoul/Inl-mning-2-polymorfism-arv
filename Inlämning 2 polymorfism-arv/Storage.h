#pragma once
#include <vector>
#include <fstream>
#include "Sensor.h"
#include "Measurement.h"
class Storage
{
public:
	static std::vector <Measurement> getMeasurments();
	static std::unique_ptr<Sensor> makeSensor(SensorType type, const std::string& newname, double min, double max);
	//detta kollar hur många av specefic sensortyp man har beroende på vilken string man lägger in
	static int sizeOfTypeSensor(const std::string& unitOfunitOfMeasurement);
	//detta kollar storleken på hela listan
	static int SizeOfList();
	//detta går igenom hela listan för att hitta en measurment med hjälp av namnet
	bool SearchForName(std::string Name);
	//detta går igenom hela listan för att hitta en measurment med hjälp av timestampen
	bool SearchForTimeStamp(std::string Name);
	//detta skapar  och lägger in measurement structen in i listan samt så skapas sensor settings och threshold här
	static void getMeasurementReading(char type);
	//detta printar beroende på vad för string man har
	static void printByTypeSensor(const std::string& unitOfMeasurement, const std::string& type);
	//detta skriver measurments till en txt fil
	static void WriteFile(Measurement& NewMeasurementReadings);
	//detta lässer in measurments från txt fil
	static void ReadFile();
	//detta går igenom specefic typ och vissar värdet med hjälp av '*'
	static void VisulisationOfTypeSensor(const std::string& unitOfMeasurement);
	//detta får fram summa av specefic sensortyp med hjälp av string unitOfMeasuremnt
	double sumOfTypeSensor(const std::string& unitOfMeasurement);
	//detta får fram variance av specefic sensortyp med hjälp av string unitOfMeasuremnt
	static double varianceFromTypeSensor(double& sum, const std::string& unitOfMeasurement);
	//detta får fram minmax av specefic sensortyp med hjälp av string unitOfMeasuremnt
	static void minMaxOfTypeSensor(const std::string& unitOfMeasurement);
private:
	static std::vector <Measurement> MeasurmentsList;
};