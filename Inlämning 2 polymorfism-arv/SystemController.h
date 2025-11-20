#pragma once
#include <vector>
#include <string>
#include "Sensor.h"
#include "ThresHold.h"
class SystemController 
{
public:
	static std::vector<std::unique_ptr<Sensor>> sensors;
	static std::vector <Threshold> thresholdList;
	//lägger till sensor settings in i sensor listan
	static void addSensor(std::unique_ptr<Sensor> s);
	//printar ut alla thresholds från thresholdslistan
	void checkAlarm();
	//har detta så jag kan kalla på alarmcount
	int getAlarmCount() const;
	//detta lägger till threshold till specefic sensor
	static void addThresholdForSensor(const std::string& name);
	//sparar threshold till txt fil
	static void saveThresholdToFile(Threshold newThresHold);
	//detta lägger in thresholds från txt fil
	static void loadThresholdFromFile();
	//detta printar utt alla värden för varje threshold i vectorn
	void showAlarms() const;
	//detta printar ut settings för varje sensor
	void showSensorConfig();
	//detta vissar setting för specefic sensor
	void showStatsFor(std::string sensorName) const;
	//detta sparar settings för sensorn till en txt fil
	static void saveToFile(const Sensor& sensor);
	//detta laddar in från samma txt fil
	void loadFromFile();
	//detta gör att man kan ändra threshold limiten på specefic threshold
	void editThresHold(const std::string& thresholdName);
private:
	int alarmCount = 0;
};