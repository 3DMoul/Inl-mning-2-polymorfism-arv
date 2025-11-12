#pragma once
#include "Sensor.h"
#include <vector>
#include <memory>
#include <string>
//class SystemController {
//public:
//	void addSensor(std::unique_ptr<Sensor> s);
//	void sampleAllOnce();
//	void configureThreshold();
//	void showAlerts() const;
//	void showStatsFor(const std::string& sensorName) const;
//	void saveToFile(const std::string& path) const;
//	void loadFromFile(const std::string& path);
//private:
//	std::vector<std::unique_ptr<Sensor>> sensors;
//};