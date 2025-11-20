#include <iostream>
#include <string>
#include <fstream>
#include "SystemController.h"
#include "ThresHold.h"
#include "Storage.h"
#include "Sensor.h"
std::vector<std::unique_ptr<Sensor>> SystemController::sensors;
std::vector <Threshold> SystemController::thresholdList;
void SystemController::addSensor(std::unique_ptr<Sensor> s) 
{
    sensors.push_back(std::move(s));
}
void SystemController::checkAlarm()
{
    for (auto& currentThresHold : thresholdList)
    {
        for (auto& currentMeasurement : Storage::getMeasurments())
        {
            if (currentThresHold.SensorNamn == currentMeasurement.SensorName)
            {
                if (currentThresHold.Limit < currentMeasurement.SensorMeasurement)
                {
                    if (currentThresHold.Over == true) { alarmCount++; currentThresHold.Over = false; }
                }
            }

        }
    }
}
int SystemController::getAlarmCount() const
{
    return alarmCount;
}
void SystemController::addThresholdForSensor(const std::string& name)
{
    Threshold newThresHold;
    newThresHold.SensorNamn = name;
    std::cout << "what do you want your threshold limit to be: ";
    std::cin >> newThresHold.Limit;
    saveThresholdToFile(newThresHold);
    thresholdList.push_back(newThresHold);

}
void SystemController::saveThresholdToFile(Threshold newThresHold)
{
    std::ofstream thresHoldConfig("ThresHoldConfig.txt", std::ios::app);
    if (thresHoldConfig.is_open())
    {
        thresHoldConfig << newThresHold.SensorNamn << ",";
        thresHoldConfig << newThresHold.Limit << ",";
        thresHoldConfig << newThresHold.Over << std::endl;
    }
}
void SystemController::loadThresholdFromFile()
{
    std::ifstream thresHoldConfig;
    //går igenom värdena som var innan och skickar in dem i listan
    thresHoldConfig.open("ThresHoldConfig.txt", std::ios::in);
    if (thresHoldConfig.is_open())
    {
        int times = 0;
        std::string line;
        //här går den igenom alla lines av txt filen samt lägger dem in i vector som sätts in i listan
        while (std::getline(thresHoldConfig, line))
        {
            char str[256];
            strcpy_s(str, line.c_str());
            const char* del = ",";
            char* next_token = nullptr;
            char* FileSegment = strtok_s(str, del, &next_token);
            int FileIteration = 0;
            Threshold newThreshold;
            
            while (FileSegment != nullptr)
            {
                if (FileIteration == 0)
                {
                    newThreshold.SensorNamn = FileSegment;
                }
                else if (FileIteration == 1)
                {
                    newThreshold.Limit = stod(FileSegment);
                }
                else if (FileIteration == 2)
                {
                    newThreshold.Over = FileSegment;
                }
                FileSegment = strtok_s(nullptr, del, &next_token);
                FileIteration++;
            }
            thresholdList.push_back(newThreshold);
        }
        thresHoldConfig.close();
    }
}
void SystemController::showAlerts() const
{
    for (auto& currentThresHold : thresholdList)
    {
        std::cout << "------------------------------" << std::endl;
        std::cout << currentThresHold.SensorNamn << std::endl;
        std::cout << currentThresHold.Limit << std::endl;
        std::cout << currentThresHold.Over << std::endl;
        std::cout << "------------------------------" << std::endl;

    }
}
void SystemController::showSensorConfig()
{
    std::cout << "Temperature sensors: " << std::endl;
    for (auto& CurrentSensor : sensors)
    {
        if (CurrentSensor->GetUnitOfMeasurment() == "C")
        {

            std::cout << "Sensor name: " << CurrentSensor->name() << std::endl;
            std::cout << "Maxvalue is: " << CurrentSensor->maxValue() << std::endl;
            std::cout << "Minvalue is: " << CurrentSensor->minValue() << std::endl;

        }
    }
    std::cout << "Airquality sensors: " << std::endl;
    for (auto& CurrentSensor : sensors)
    {
        if (CurrentSensor->GetUnitOfMeasurment() == "%")
        {
            std::cout << "Sensor name: " << CurrentSensor->name() << std::endl;
            std::cout << "Maxvalue is: " << CurrentSensor->maxValue() << std::endl;
            std::cout << "Minvalue is: " << CurrentSensor->minValue() << std::endl;
        }
    }
    std::cout << "Humidity sensors: " << std::endl;
    for (auto& CurrentSensor : sensors)
    {
        if (CurrentSensor->GetUnitOfMeasurment() == "AH")
        {
            std::cout << "Sensor name: " << CurrentSensor->name() << std::endl;
            std::cout << "Maxvalue is: " << CurrentSensor->maxValue() << std::endl;
            std::cout << "Minvalue is: " << CurrentSensor->minValue() << std::endl;
        }
    }


}
void SystemController::showStatsFor(std::string sensorName) const
{
	for (auto& sensor : sensors)
	{
		if (sensor->name() == sensorName)
		{
			std::cout << "Sensor name: " << sensor->name() << "\nMax value: " << sensor->maxValue() << " Min value: " << sensor->minValue() << "\nUnit of measurement: " << sensor->GetUnitOfMeasurment() << std::endl;
		}
	}
}
void SystemController::saveToFile(const Sensor& sensor)
{
    std::ofstream sensorConfig("SensorConfig.txt", std::ios::app);
    if (sensorConfig.is_open())
    {
        sensorConfig << sensor.name() << ",";
        sensorConfig << sensor.GetUnitOfMeasurment() << ",";
        sensorConfig << sensor.maxValue() << ",";
        sensorConfig << sensor.minValue() << std::endl;
    }
}
void SystemController::loadFromFile()
{
    std::ifstream SensorConfig;
    //går igenom värdena som var innan och skickar in dem i listan
    SensorConfig.open("SensorConfig.txt", std::ios::in);
    if (SensorConfig.is_open())
    {
        int times = 0;
        std::string line;
        //här går den igenom alla lines av txt filen samt lägger dem in i vector som sätts in i listan
        while (std::getline(SensorConfig, line))
        {
            char str[256];
            strcpy_s(str, line.c_str());
            const char* del = ",";
            char* next_token = nullptr;
            char* fileSegment = strtok_s(str, del, &next_token);
            int fileIteration = 0;
            
            std::string name;
            std::string unitOfMeasurment;
            double maxValue;
            double minValue;
            while (fileSegment != nullptr)
            {
                if (fileIteration == 0)
                {
                    name = fileSegment;
                }
                else if (fileIteration == 1)
                {
                    unitOfMeasurment = fileSegment;
                }
                else if (fileIteration == 2)
                {
                    maxValue = std::stod(fileSegment);
                }
                else if (fileIteration == 3)
                {
                    minValue = std::stod(fileSegment);
                }
                fileSegment = strtok_s(nullptr, del, &next_token);
                fileIteration++;
            }
            if (unitOfMeasurment == "C")
            {
                SensorType typeSens = static_cast<SensorType>('T');
                auto newSensor = Storage::makeSensor(typeSens, name, minValue, maxValue);
                sensors.push_back(std::move(newSensor));
            }
            else if (unitOfMeasurment == "%")
            {
                SensorType typeSens = static_cast<SensorType>('A');
                auto newSensor = Storage::makeSensor(typeSens, name, minValue, maxValue);
                sensors.push_back(std::move(newSensor));
            }
            else if (unitOfMeasurment == "AH")
            {
                SensorType typeSens = static_cast<SensorType>('H');
                auto newSensor = Storage::makeSensor(typeSens, name, minValue, maxValue);
                sensors.push_back(std::move(newSensor));
            }
        }
        SensorConfig.close();
    }
}
void SystemController::editThresHold(const std::string& thresholdName)
{
    for (auto& currentThreshold : thresholdList)
    {
        if (currentThreshold.SensorNamn == thresholdName)
        {
            std::cout << "The current threshold for " << currentThreshold.SensorNamn << "is " << currentThreshold.Limit << std::endl;
            std::cout << "´What do you want to change the threshold to: ";
            std::cin >> currentThreshold.Limit;
        }
    }
}