#include "Storage.h"
#include "Utility.h"
#include "Sensor.h"
#include "SensorType.h"
#include <iostream>
#include <string>
#include <thread>
#include "SystemController.h"
std::vector <Measurement> Storage::MeasurmentsList;
// Puts Readings in vector 
static std::unique_ptr<Sensor> MakeSensor(SensorType& type, const std::string& newname, double min, double max)
{
    switch (type) 
    {
        case SensorType::Airquality: return std::make_unique<AirqualitySensor>(newname, min, max);
        case SensorType::Temperature: return std::make_unique<TemperatureSensor>(newname, min, max);
        case SensorType::Humidity: return std::make_unique<HumiditySensor>(newname, min, max);

        default: return nullptr;
    }
}
static std::unique_ptr<promt> makePromt(SensorType& type)
{
    switch (type)
    {
    case SensorType::Airquality: return std::make_unique<airqualityPromts>();
    case SensorType::Temperature: return std::make_unique<temperaturePromts>();
    case SensorType::Humidity: return std::make_unique<humidityPromts>();

    default: return nullptr;
    }
}
void Storage::GetMeasurementReading(char type)
{
    std::cout << "here" << std::endl;
    SensorType sensorType = static_cast<SensorType>(type);
    auto sensorPrompt = makePromt(sensorType);
    if (!sensorPrompt)
    {
        std::cerr << "Invalid sensor type!\n";
        return;
    }
    string strPromt = sensorPrompt->SimulatingSensorpromt();
    int amountOfSensors = Utility::NumberChoice(strPromt);//amout of sensors
    for (int i = 0; i < amountOfSensors; i++)
    {
        std::cout << "What is the name of your sensor: " << std::endl;
        std::string newSensorName;
        std::cin >> newSensorName;
        std::cout << "Pick your interval values MinValue: " << std::endl;
        double minValue = 0;
        std::cin >> minValue;
        std::cout << "Pick your interval values MaxValue: " << std::endl;
        double maxValue = 0;
        std::cin >> maxValue;
        SensorType typeSens = static_cast<SensorType>(type);
        auto newSensor = MakeSensor(typeSens, newSensorName, minValue, maxValue);
        SystemController sensorFile;
        sensorFile.saveToFile(newSensor);
        Measurement newMeasurement;
        newMeasurement.GetReading(newSensor);
        WriteFile(newMeasurement);
        MeasurmentsList.push_back(newMeasurement);
    }
}

void Storage::PrintTemperatureReadings()
{
    if (SizeOfTemperature() > 0)
    {
        cout << "Temperature: " << endl;
        for (auto& CurrentSensor : MeasurmentsList)
        {
            if (CurrentSensor.UnitOfMeasurment == "C")
            {
                cout << CurrentSensor.SensorName << "\n" << CurrentSensor.SensorMeasurement << " " << CurrentSensor.UnitOfMeasurment << ", " << CurrentSensor.TimeStamp << endl;
            }
        }
    }
    else
    {
        cout << "you have no temperature readings" << endl;
    }
    
}
void Storage::PrintAirqualityReadings()
{
    cout << "AirQualityReadings: " << endl;
    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == "%")
        {
            cout << CurrentSensor.SensorName << "\n" << CurrentSensor.SensorMeasurement << " " << CurrentSensor.UnitOfMeasurment << ", " << CurrentSensor.TimeStamp << endl;
        }
    }
}
void Storage::PrintAll()
{
    PrintTemperatureReadings();
    PrintAirqualityReadings();
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
int Storage::SizeOfAirquality()
{
    int Size = 0;
    for (int i = 0; i < size(MeasurmentsList); i++)
    {
        if (MeasurmentsList[i].UnitOfMeasurment == "%")
        {
            Size++;
        }
    }


    return Size;
}
int Storage::SizeOfTemperature()
{
    int Size = 0;
    for (int i = 0; i < size(MeasurmentsList); i++)
    {
        if (MeasurmentsList[i].UnitOfMeasurment == "C")
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
            cout << CurrentSensor.SensorName << endl;
            cout << CurrentSensor.SensorMeasurement << CurrentSensor.UnitOfMeasurment << endl;
            cout << CurrentSensor.TimeStamp << endl;
            return false;
        }
    }
    cout << "Did not find that sensorname in the list try with another name:" << endl;
    return true;

}
bool Storage::SearchForTimeStamp(string TimeStamp)
{

    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.TimeStamp == TimeStamp)
        {
            cout << CurrentSensor.SensorName << endl;
            cout << CurrentSensor.SensorMeasurement << CurrentSensor.UnitOfMeasurment << endl;
            cout << CurrentSensor.TimeStamp << endl;
            return false;
        }
    }
    cout << "Did not find that TimeStamp in the list try with another TimeStamp:" << endl;
    return true;

}
//Takes value of reading and show it with sequences of "*" symbols
void Storage::Visulisation(char IN)
{
    if (IN == 'A')
    {
        // går genom alla vectorer
        for (auto& CurrentSensor : MeasurmentsList)
        {
            if (CurrentSensor.UnitOfMeasurment == "%")
            {
                int temp = round(CurrentSensor.SensorMeasurement);
                for (int i = 0; i < round(temp / 4); i++) // for loopen printar "*" så att man kan se visualiserat hur tempraturen går ne och up
                {
                    cout << "*";
                    //andvänder den här för att den inte bara pruntar ut alla "*" på en gång
                    this_thread::sleep_for(chrono::seconds(1));
                }
                cout << "   " << CurrentSensor.SensorMeasurement << " " << CurrentSensor.UnitOfMeasurment << endl;
                cout << "\n";
            }
        }
    }
    else if (IN == 'T')
    {
        for (auto& CurrentSensor : MeasurmentsList)
        {
            if (CurrentSensor.UnitOfMeasurment == "%")
            {
                int temp = round(CurrentSensor.SensorMeasurement);
                for (int i = 0; i < round(temp / 2); i++) // for loopen printar "*" så att man kan se visualiserat hur tempraturen går ne och up
                {
                    cout << "*";
                    //andvänder den här för att den inte bara pruntar ut alla "*" på en gång
                    this_thread::sleep_for(chrono::seconds(1));
                }
                cout << "   " << CurrentSensor.SensorMeasurement << " " << CurrentSensor.UnitOfMeasurment << endl;
                cout << "\n";
            }
        }
    }
    else
    {
        for (auto& CurrentSensor : MeasurmentsList)
        {
            if (CurrentSensor.UnitOfMeasurment == "%")
            {
                int temp = round(CurrentSensor.SensorMeasurement);
                for (int i = 0; i < round(temp / 4); i++) // for loopen printar "*" så att man kan se visualiserat hur tempraturen går ne och up
                {
                    cout << "*";
                    //andvänder den här för att den inte bara pruntar ut alla "*" på en gång
                    this_thread::sleep_for(chrono::seconds(1));
                }
                cout << "   " << CurrentSensor.SensorMeasurement << " " << CurrentSensor.UnitOfMeasurment << endl;
                cout << "\n";
            }
        }
        for (auto& CurrentSensor : MeasurmentsList)
        {
            if (CurrentSensor.UnitOfMeasurment == "%")
            {
                int temp = round(CurrentSensor.SensorMeasurement);
                for (int i = 0; i < round(temp / 2); i++) // for loopen printar "*" så att man kan se visualiserat hur tempraturen går ne och up
                {
                    cout << "*";
                    //andvänder den här för att den inte bara pruntar ut alla "*" på en gång
                    this_thread::sleep_for(chrono::seconds(1));
                }
                cout << "   " << CurrentSensor.SensorMeasurement << " " << CurrentSensor.UnitOfMeasurment << endl;
                cout << "\n";
            }
        }
    }
}
double Storage::SumOfTemperature()
{
    double Sum = 0;

    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == "C")
        {
            Sum += CurrentSensor.SensorMeasurement;
        }
    }

    return Sum;
}
double Storage::SumOfAirquality()
{
    double Sum = 0;
    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == "%")
        {
            Sum += CurrentSensor.SensorMeasurement;
        }
    }
    return Sum;
}
//Gives variance of Temperature
double Storage::TemperatureVariance(double SumOfTemp)
{

    //vector för att hålla värderna för varians
    vector<double> StandardDeviation = {};
    double StandAvg = SumOfTemp / SizeOfTemperature();
    //detta subtraherar alla värderna med medelvärdet
    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == "C")
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
//Gives variance of Airquality
double Storage::AirqualityVariance(double SumOfAirqual)
{

    //vector för att hålla värderna för varians
    vector<double> StandardDeviation = {};
    double StandAvg = SumOfAirqual / SizeOfAirquality();
    //detta subtraherar alla värderna med medelvärdet
    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == "%")
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
    cout << Squere;
    return Squere;
}
void Storage::MinMaxTemperature()
{
    Measurement MaxReading;
    double MaxTemp = MeasurmentsList[0].SensorMeasurement;
    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == "C")
        {
            if (MaxTemp < CurrentSensor.SensorMeasurement)
            {
                MaxTemp = CurrentSensor.SensorMeasurement;
                MaxReading.SensorMeasurement = CurrentSensor.SensorMeasurement;
                MaxReading.TimeStamp = CurrentSensor.TimeStamp;
                MaxReading.SensorName = CurrentSensor.SensorName;
                MaxReading.UnitOfMeasurment = CurrentSensor.UnitOfMeasurment;
            }
        }
    }
    Measurement MinReading;
    double MinTemp = MeasurmentsList[0].SensorMeasurement;
    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == "C")
        {
            if (MinTemp > CurrentSensor.SensorMeasurement)
            {
                MinTemp = CurrentSensor.SensorMeasurement;
                MinReading.SensorMeasurement = CurrentSensor.SensorMeasurement;
                MinReading.TimeStamp = CurrentSensor.TimeStamp;
                MinReading.SensorName = CurrentSensor.SensorName;
                MinReading.UnitOfMeasurment = CurrentSensor.UnitOfMeasurment;
            }
        }
    }
    cout << "--------------------------------" << endl;
    cout << "Max Reading is" << endl;
    MaxReading.PrintMeasurement();
    cout << "Minx Reading is" << endl;
    MinReading.PrintMeasurement();
    cout << "--------------------------------" << endl;
}
void Storage::MinMaxAirquality()
{
    Measurement MaxReading;
    double MaxAirqual = MeasurmentsList[0].SensorMeasurement;
    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == "%")
        {
            if (MaxAirqual < CurrentSensor.SensorMeasurement)
            {
                MaxAirqual = CurrentSensor.SensorMeasurement;
                MaxReading.SensorMeasurement = CurrentSensor.SensorMeasurement;
                MaxReading.TimeStamp = CurrentSensor.TimeStamp;
                MaxReading.SensorName = CurrentSensor.SensorName;
                MaxReading.UnitOfMeasurment = CurrentSensor.UnitOfMeasurment;
            }
        }
    }
    Measurement MinReading;
    double MinAirqual = MeasurmentsList[0].SensorMeasurement;
    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == "%")
        {
            if (MinAirqual > CurrentSensor.SensorMeasurement)
            {
                MinAirqual = CurrentSensor.SensorMeasurement;
                MinReading.SensorMeasurement = CurrentSensor.SensorMeasurement;
                MinReading.TimeStamp = CurrentSensor.TimeStamp;
                MinReading.SensorName = CurrentSensor.SensorName;
                MinReading.UnitOfMeasurment = CurrentSensor.UnitOfMeasurment;
            }
        }
    }
    cout << "--------------------------------" << endl;
    cout << "Max Reading is" << endl;
    MaxReading.PrintMeasurement();
    cout << "Minx Reading is" << endl;
    MinReading.PrintMeasurement();
    cout << "--------------------------------" << endl;
}