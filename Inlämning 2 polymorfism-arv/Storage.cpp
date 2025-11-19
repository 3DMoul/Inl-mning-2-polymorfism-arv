#include <iostream>
#include <string>
#include <thread>
#include "Storage.h"
#include "Utility.h"
#include "Sensor.h"
#include "SensorType.h"
#include "SystemController.h"
std::vector <Measurement> Storage::MeasurmentsList;
// Puts Readings in vector 
std::unique_ptr<Sensor> Storage::MakeSensor(SensorType type, const std::string& newname, double min, double max)
{
    switch (type) 
    {
        case SensorType::Airquality: return std::make_unique<AirqualitySensor>(newname, min, max);
        case SensorType::Temperature: return std::make_unique<TemperatureSensor>(newname, min, max);
        case SensorType::Humidity: return std::make_unique<HumiditySensor>(newname, min, max);

        default: return nullptr;
    }
}
static std::unique_ptr<prompt> makePrompt(SensorType& type)
{
    switch (type)
    {
    case SensorType::Airquality: return std::make_unique<airqualityPrompts>();
    case SensorType::Temperature: return std::make_unique<temperaturePrompts>();
    case SensorType::Humidity: return std::make_unique<humidityPrompts>();

    default: return nullptr;
    }
}
void Storage::GetMeasurementReading(char type)
{
    SensorType sensorType = static_cast<SensorType>(type);
    auto sensorPrompt = makePrompt(sensorType);
    if (!sensorPrompt)
    {
        std::cerr << "Invalid sensor type!\n";
        return;
    }
    string strPromt = sensorPrompt->SimulatingSensorprompt();
    int amountOfSensors = Utility::NumberChoice(strPromt);//amout of sensors
    for (int i = 0; i < amountOfSensors; i++)
    {
        system("CLS");
        std::cout << "What is the name of your sensor: " << std::endl;
        std::string newSensorName;
        std::cin >> newSensorName;
        SystemController::addThresholdForSensor(newSensorName);
        for (auto& currentName : MeasurmentsList)
        {
            while (currentName.SensorName == newSensorName)
            {
                std::cout << "You cant have the same sensor name as another sensor" << std::endl;
                std::cin >> newSensorName;
            }
        }
        std::cout << "Pick your interval values MinValue: " << std::endl;
        double minValue = 0;
        std::cin >> minValue;
        std::cout << "Pick your interval values MaxValue: " << std::endl;
        double maxValue = 0;
        std::cin >> maxValue;
        SensorType typeSens = static_cast<SensorType>(type);
        auto newSensor = MakeSensor(typeSens, newSensorName, minValue, maxValue);
        std::cout << " here" << std::endl;
        SystemController::saveToFile(*newSensor);
        Measurement newMeasurement;
        newMeasurement.GetReading(*newSensor);
        SystemController::addSensor(std::move(newSensor));
        WriteFile(newMeasurement);
        MeasurmentsList.push_back(newMeasurement);
    }
}
void Storage::printByTypeSensor(const std::string& unitOfMeasurement, const std::string& type)
{
    std::cout << type << endl;
    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == unitOfMeasurement)
        {
            std::cout << CurrentSensor.SensorName << "\n" << CurrentSensor.SensorMeasurement << " " << CurrentSensor.UnitOfMeasurment << ", " << CurrentSensor.TimeStamp << endl;
        }
    }
}
//Takes readings and puts them in text file
void Storage::WriteFile(Measurement& NewMeasurementReadings)
{
    ofstream SensorFile;
    //här öppnar jag upp en ny txt.fil som jag lägger in värden i
    SensorFile.open("SensorReading2.txt", ios::app);
    if (SensorFile.is_open())
    {
        //här läggs det in i txt.filen
        SensorFile << NewMeasurementReadings.UnitOfMeasurment << ",";
        SensorFile << NewMeasurementReadings.SensorName << ",";
        SensorFile << NewMeasurementReadings.SensorMeasurement << ",";
        SensorFile << NewMeasurementReadings.TimeStamp << endl;
        SensorFile.close();
    }
}
//takes readings from text file and puts them in vector
void Storage::ReadFile()
{
    ifstream SensorFile;
    //går igenom värdena som var innan och skickar in dem i listan
    SensorFile.open("SensorReading2.txt", ios::in);
    if (SensorFile.is_open())
    {
        int times = 0;
        string line;
        //här går den igenom alla lines av txt filen samt lägger dem in i vector som sätts in i listan
        while (getline(SensorFile, line))
        {
            char str[256];
            strcpy_s(str, line.c_str());
            const char* del = ",";
            char* next_token = nullptr;
            char* FileSegment = strtok_s(str, del, &next_token);
            int FileIteration = 0;
            Measurement New_Measurement;
            while (FileSegment != nullptr)
            {
                if (FileIteration == 0)
                {
                    New_Measurement.UnitOfMeasurment = FileSegment;
                }
                else if (FileIteration == 1)
                {
                    New_Measurement.SensorName = FileSegment;
                }
                else if (FileIteration == 2)
                {
                    New_Measurement.SensorMeasurement = stod(FileSegment);
                }
                else if (FileIteration == 3)
                {
                    New_Measurement.TimeStamp = FileSegment;
                }
                FileSegment = strtok_s(nullptr, del, &next_token);
                FileIteration++;
            }
            MeasurmentsList.push_back(New_Measurement);
        }
        SensorFile.close();
    }
}
//Goes throu list to see how many of different readings you have from vector
int Storage::sizeOfTypeSensor(const std::string& unitOfunitOfMeasurement)
{
    int Size = 0;
    for (int i = 0; i < size(MeasurmentsList); i++)
    {
        if (MeasurmentsList[i].UnitOfMeasurment == unitOfunitOfMeasurement)
        {
            Size++;
        }
    }
    return Size;
}
int Storage::SizeOfList()
{
    return size(MeasurmentsList);
}
//Binary search algoritm
bool Storage::SearchForName(string Name)
{
    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.SensorName == Name)
        {
            std::cout << CurrentSensor.SensorName << endl;
            std::cout << CurrentSensor.SensorMeasurement << CurrentSensor.UnitOfMeasurment << endl;
            std::cout << CurrentSensor.TimeStamp << endl;
            return false;
        }
    }
    std::cout << "Did not find that sensorname in the list try with another name:" << endl;
    return true;

}
bool Storage::SearchForTimeStamp(string TimeStamp)
{

    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.TimeStamp == TimeStamp)
        {
            std::cout << CurrentSensor.SensorName << endl;
            std::cout << CurrentSensor.SensorMeasurement << CurrentSensor.UnitOfMeasurment << endl;
            std::cout << CurrentSensor.TimeStamp << endl;
            return false;
        }
    }
    std::cout << "Did not find that TimeStamp in the list try with another TimeStamp:" << endl;
    return true;

}
//Takes value of reading and show it with sequences of "*" symbols
void Storage::VisulisationOfTypeSensor(const std::string& unitOfMeasurement)
{
    // går genom alla vectorer
    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == unitOfMeasurement)
        {
            int temp = round(CurrentSensor.SensorMeasurement);
            for (int i = 0; i < round(temp / 4); i++) // for loopen printar "*" så att man kan se visualiserat hur tempraturen går ne och up
            {
                std::cout << "*";
                //andvänder den här för att den inte bara pruntar ut alla "*" på en gång
                this_thread::sleep_for(chrono::seconds(1));
            }
            std::cout << "   " << CurrentSensor.SensorMeasurement << " " << CurrentSensor.UnitOfMeasurment << endl;
            std::cout << "\n";
        }
    }
}
double Storage::sumOfTypeSensor(const std::string& unitOfMeasurement)
{
    double Sum = 0;

    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == unitOfMeasurement)
        {
            Sum += CurrentSensor.SensorMeasurement;
        }
    }

    return Sum;
}
//Gives variance of Temperature
double Storage::varianceFromTypeSensor(double& sum, const std::string& unitOfMeasurement)
{
    //vector för att hålla värderna för varians
    vector<double> StandardDeviation = {};
    double StandAvg = sum / sizeOfTypeSensor(unitOfMeasurement);
    //detta subtraherar alla värderna med medelvärdet
    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == unitOfMeasurement)
        {
            double Temp = CurrentSensor.SensorMeasurement;
            double TempVar = Temp - StandAvg;
            StandardDeviation.push_back(TempVar);
        }
    }
    //detta kvadrerar alla dem subtraherade nummrena
    for (auto& CurrentValue : StandardDeviation)
    {
        double TempVar = pow(CurrentValue, 2);
        CurrentValue = TempVar;
    }
    // deklarering a kvadrerade tal
    double Squere = 0;
    //loop för att addera ihop all Kvad tal
    for (double i : StandardDeviation)
    {
        Squere = Squere + i;
    }
    return Squere;
}
void Storage::minMaxOfTypeSensor(const std::string& unitOfMeasurement)
{
    Measurement MaxReading;
    Measurement MinReading;
    double MaxTemp = MeasurmentsList[0].SensorMeasurement;
    double MinTemp = MeasurmentsList[0].SensorMeasurement;
    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == unitOfMeasurement)
        {
            if (MaxTemp < CurrentSensor.SensorMeasurement)
            {
                MaxTemp = CurrentSensor.SensorMeasurement;
                MaxReading.SensorMeasurement = CurrentSensor.SensorMeasurement;
                MaxReading.TimeStamp = CurrentSensor.TimeStamp;
                MaxReading.SensorName = CurrentSensor.SensorName;
                MaxReading.UnitOfMeasurment = CurrentSensor.UnitOfMeasurment;
            }
            else if (MinTemp > CurrentSensor.SensorMeasurement)
            {
                MinTemp = CurrentSensor.SensorMeasurement;
                MinReading.SensorMeasurement = CurrentSensor.SensorMeasurement;
                MinReading.TimeStamp = CurrentSensor.TimeStamp;
                MinReading.SensorName = CurrentSensor.SensorName;
                MinReading.UnitOfMeasurment = CurrentSensor.UnitOfMeasurment;
            }
        }
    }
    std::cout << "--------------------------------" << endl;
    std::cout << "Max Reading is" << endl;
    MaxReading.PrintMeasurement();
    std::cout << "Minx Reading is" << endl;
    MinReading.PrintMeasurement();
    std::cout << "--------------------------------" << endl;
}
std::vector <Measurement> Storage::getMeasurments()
{
    return MeasurmentsList;
}