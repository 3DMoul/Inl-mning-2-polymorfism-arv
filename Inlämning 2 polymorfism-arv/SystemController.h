#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Sensor.h"
#include "ThresHold.h"
class SystemController 
{
public:
	void addSensor(std::unique_ptr<Sensor>& s);
	void checkAlarm();
	int getAlarmCount() const;
	static void configureThreshold(const std::string& name);
	void showAlerts() const;
	void showSensorConfig();
	void showStatsFor(std::string sensorName) const;
	void saveToFile(std::unique_ptr<Sensor>& sensor) const;
	void loadFromFile();

private:
	static std::vector<std::unique_ptr<Sensor>> sensors;
	static std::vector <Threshold> thresholdList;
	int alarmCount = 0;

};