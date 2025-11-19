#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Sensor.h"
#include "ThresHold.h"
class SystemController 
{
	static std::vector<std::unique_ptr<Sensor>> sensors;
	static std::vector <Threshold> thresholdList;
public:
	void addSensor(std::unique_ptr<Sensor>& s);
	void checkAlarm();
	int getAlarmCount() const;
	static void addThresholdForSensor(const std::string& name);
	void showAlerts() const;
	void showSensorConfig();
	void showStatsFor(std::string sensorName) const;
	static void saveToFile(std::unique_ptr<Sensor>& sensor);
	void loadFromFile();

private:
	int alarmCount = 0;
};