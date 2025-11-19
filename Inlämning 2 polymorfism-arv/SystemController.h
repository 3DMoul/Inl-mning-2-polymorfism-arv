#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Sensor.h"
#include "ThresHold.h"
class SystemController 
{
public:
	static std::vector<std::unique_ptr<Sensor>> sensors;
	static std::vector <Threshold> thresholdList;
	static void addSensor(std::unique_ptr<Sensor> s);
	void checkAlarm();
	int getAlarmCount() const;
	static void addThresholdForSensor(const std::string& name);
	void showAlerts() const;
	void showSensorConfig();
	void showStatsFor(std::string sensorName) const;
	static void saveToFile(const Sensor& sensor);
	void loadFromFile();
	void editThresHold(const std::string& thresholdName);
private:
	int alarmCount = 0;
};