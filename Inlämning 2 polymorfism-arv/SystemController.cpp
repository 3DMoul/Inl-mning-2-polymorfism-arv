#include <iostream>
#include <string>
#include <fstream>
#include "SystemController.h"
#include "Storage.cpp"
std::vector<std::unique_ptr<Sensor>> SystemController::sensors;

void SystemController::addSensor(std::unique_ptr<Sensor> s)
{
	sensors.push_back(s);
}
void SystemController::sampleAllOnce()
{

}
void SystemController::configureThreshold()
{

}
void SystemController::showAlerts() const
{

}
void SystemController::showStatsFor(const std::string& sensorName) const
{
	for (auto& sensor : sensors)
	{
		if (sensor->name() == sensorName)
		{
			std::cout << "Sensor name: " << sensor->name() << "\nMax value: " << sensor->maxValue() << " Min value: " << sensor->minValue() << "\nUnit of measurement: " << sensor->GetUnitOfMeasurment() << std::endl;
		}
	}
}
void SystemController::saveToFile(std::unique_ptr<Sensor>& sensor) const
{
    std::ofstream sensorConfig;
    //här öppnar jag upp en ny txt.fil som jag lägger in värden i
    sensorConfig.open("SensorConfig.txt", std::ios::app);
    if (sensorConfig.is_open())
    {
        //här läggs det in i txt.filen
        sensorConfig << sensor->name() << ",";
        sensorConfig << sensor->GetUnitOfMeasurment() << ",";
        sensorConfig << sensor->maxValue() << ",";
        sensorConfig << sensor->minValue() << std::endl;
        sensorConfig.close();
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
            char* FileSegment = strtok_s(str, del, &next_token);
            int FileIteration = 0;
            
            std::string name;
            std::string unitOfMeasurment;
            double maxValue;
            double minValue;
            while (FileSegment != nullptr)
            {
                if (FileIteration == 0)
                {
                    name = FileSegment;
                }
                else if (FileIteration == 1)
                {
                    unitOfMeasurment = FileSegment;
                }
                else if (FileIteration == 2)
                {
                    maxValue = stod(FileSegment);
                }
                else if (FileIteration == 3)
                {
                    minValue = stod(FileSegment);
                }
                FileSegment = strtok_s(nullptr, del, &next_token);
                FileIteration++;
            }
            if (unitOfMeasurment == "C")
            {
                SensorType typeSens = static_cast<SensorType>('T');
                auto newSensor = MakeSensor(typeSens, name, minValue, maxValue);
                sensors.push_back(newSensor);
            }
            else if (unitOfMeasurment == "%")
            {
                SensorType typeSens = static_cast<SensorType>('A');
                auto newSensor = MakeSensor(typeSens, name, minValue, maxValue);
                sensors.push_back(newSensor);
            }
            else if (unitOfMeasurment == "AH")
            {
                SensorType typeSens = static_cast<SensorType>('H');
                auto newSensor = MakeSensor(typeSens, name, minValue, maxValue);
                sensors.push_back(newSensor);
            }
        }
        SensorConfig.close();
    }
}