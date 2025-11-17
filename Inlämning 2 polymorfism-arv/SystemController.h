#pragma once
#include "Sensor.h"
#include <vector>
#include <memory>
#include <string>
class SystemController {
public:
	void addSensor(std::unique_ptr<Sensor> s);
	void sampleAllOnce();
	void configureThreshold();
	void showAlerts() const;
	void showStatsFor(const std::string& sensorName) const;
	void saveToFile(std::unique_ptr<Sensor>& sensor) const;
	void loadFromFile();
private:
	static std::vector<std::unique_ptr<Sensor>> sensors;
};