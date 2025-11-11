#include "Storage.h"
#include "TemperatureSensor.h"
#include "AirqualitySensor.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
vector <Measurement> Storage::MeasurmentsList;
void Storage::GetMeasurementReading(const Measurement& NewMeasurement)
{
    MeasurmentsList.push_back(NewMeasurement);
}
void Storage::PrintTemperatureReadings()
{
    cout << "Temperature: " << endl;
    for (int i = 0; i < size(MeasurmentsList); i++)
    {
        if (MeasurmentsList[i].UnitOfMeasurment == "C")
        {
            cout << MeasurmentsList[i].SensorName << "\n" << MeasurmentsList[i].Measurement << " " << MeasurmentsList[i].UnitOfMeasurment << ", " << MeasurmentsList[i].TimeStamp << endl;
        }
    }
}
void Storage::PrintAirqualityReadings()
{
    cout << "AirQualityReadings: " << endl;
    for (int i = 0; i < size(MeasurmentsList); i++)
    {
        if (MeasurmentsList[i].UnitOfMeasurment == "%")
        {
            cout << MeasurmentsList[i].SensorName << "\n" << MeasurmentsList[i].Measurement << " " << MeasurmentsList[i].UnitOfMeasurment << ", " << MeasurmentsList[i].TimeStamp << endl;
        }
    }
}
void Storage::PrintAll()
{
    PrintTemperatureReadings();
    PrintAirqualityReadings();
}
void Storage::WriteFile(string TimeStamp, string UnitOfMeasurment, string SensorName, double SensorReading)
{
    ofstream SensorFile;
    //här öppnar jag upp en ny txt.fil som jag lägger in värden i
    SensorFile.open("SensorReading2.txt", ios::app);
    if (SensorFile.is_open())
    {
        //här läggs det in i txt.filen
        SensorFile << UnitOfMeasurment << ",";
        SensorFile << SensorName << ",";
        SensorFile << SensorReading << ",";
        SensorFile << TimeStamp << endl;
        SensorFile.close();
    }
}
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
                    New_Measurement.Measurement = stod(FileSegment);
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
bool Storage::SearchForName(string Name)
{
    for (int i = 0; i < size(MeasurmentsList); i++)
    {
        if (MeasurmentsList[i].SensorName == Name)
        {
            cout << MeasurmentsList[i].SensorName << endl;
            cout << MeasurmentsList[i].Measurement << MeasurmentsList[i].UnitOfMeasurment << endl;
            cout << MeasurmentsList[i].TimeStamp << endl;
            return false;
        }
    }
    cout << "Did not find that sensorname in the list try with another name:" << endl;
    return true;

}
bool Storage::SearchForTimeStamp(string TimeStamp)
{

    for (int i = 0; i < size(MeasurmentsList); i++)
    {
        if (MeasurmentsList[i].TimeStamp == TimeStamp)
        {
            cout << MeasurmentsList[i].SensorName << endl;
            cout << MeasurmentsList[i].Measurement << MeasurmentsList[i].UnitOfMeasurment << endl;
            cout << MeasurmentsList[i].TimeStamp << endl;
            return false;
        }
    }
    cout << "Did not find that TimeStamp in the list try with another TimeStamp:" << endl;
    return true;

}
void Storage::Visulisation(char IN)
{
    if (IN == 'A')
    {
        // går genom alla vectorer
        for (int i = 0; i < size(MeasurmentsList); i++)
        {
            if (MeasurmentsList[i].UnitOfMeasurment == "%")
            {
                int temp = round(MeasurmentsList[i].Measurement);
                for (int i = 0; i < round(temp / 4); i++) // for loopen printar "*" så att man kan se visualiserat hur tempraturen går ne och up
                {
                    cout << "*";
                    //andvänder den här för att den inte bara pruntar ut alla "*" på en gång
                    this_thread::sleep_for(chrono::seconds(1));
                }
                cout << "   " << MeasurmentsList[i].Measurement << " " << MeasurmentsList[i].UnitOfMeasurment << endl;
                cout << "\n";
            }
        }
    }
    else if (IN == 'T')
    {
        for (int i = 0; i < size(MeasurmentsList); i++)
        {
            if (MeasurmentsList[i].UnitOfMeasurment == "%")
            {
                int temp = round(MeasurmentsList[i].Measurement);
                for (int i = 0; i < round(temp / 2); i++) // for loopen printar "*" så att man kan se visualiserat hur tempraturen går ne och up
                {
                    cout << "*";
                    //andvänder den här för att den inte bara pruntar ut alla "*" på en gång
                    this_thread::sleep_for(chrono::seconds(1));
                }
                cout << "   " << MeasurmentsList[i].Measurement << " " << MeasurmentsList[i].UnitOfMeasurment << endl;
                cout << "\n";
            }
        }
    }
    else
    {
        for (int i = 0; i < size(MeasurmentsList); i++)
        {
            if (MeasurmentsList[i].UnitOfMeasurment == "%")
            {
                int temp = round(MeasurmentsList[i].Measurement);
                for (int i = 0; i < round(temp / 4); i++) // for loopen printar "*" så att man kan se visualiserat hur tempraturen går ne och up
                {
                    cout << "*";
                    //andvänder den här för att den inte bara pruntar ut alla "*" på en gång
                    this_thread::sleep_for(chrono::seconds(1));
                }
                cout << "   " << MeasurmentsList[i].Measurement << " " << MeasurmentsList[i].UnitOfMeasurment << endl;
                cout << "\n";
            }
        }
        for (int i = 0; i < size(MeasurmentsList); i++)
        {
            if (MeasurmentsList[i].UnitOfMeasurment == "%")
            {
                int temp = round(MeasurmentsList[i].Measurement);
                for (int i = 0; i < round(temp / 2); i++) // for loopen printar "*" så att man kan se visualiserat hur tempraturen går ne och up
                {
                    cout << "*";
                    //andvänder den här för att den inte bara pruntar ut alla "*" på en gång
                    this_thread::sleep_for(chrono::seconds(1));
                }
                cout << "   " << MeasurmentsList[i].Measurement << " " << MeasurmentsList[i].UnitOfMeasurment << endl;
                cout << "\n";
            }
        }
    }
}
double Storage::SumOfTemperature()
{
    double Sum = 0;

    for (int i = 0; i < size(MeasurmentsList); i++)
    {
        if (MeasurmentsList[i].UnitOfMeasurment == "C")
        {
            Sum += MeasurmentsList[i].Measurement;
        }
    }

    return Sum;
}
double Storage::SumOfAirquality()
{
    double Sum = 0;
    for (int i = 0; i < size(MeasurmentsList); i++)
    {
        if (MeasurmentsList[i].UnitOfMeasurment == "%")
        {
            Sum += MeasurmentsList[i].Measurement;
        }
    }
    return Sum;
}
double Storage::TemperatureVariance(double SumOfTemp)
{

    //vector för att hålla värderna för varians
    vector<double> StandardDeviation = {};
    double StandAvg = SumOfTemp;
    StandAvg = StandAvg / SizeOfTemperature();
    //detta subtraherar alla värderna med medelvärdet
    for (int i = 0; i < size(MeasurmentsList); i++)
    {
        if (MeasurmentsList[i].UnitOfMeasurment == "C")
        {
            double Temp = MeasurmentsList[i].Measurement;
            double TempVar = Temp - StandAvg;
            StandardDeviation.push_back(TempVar);
        }
    }
    //detta kvadrerar alla dem subtraherade nummrena
    for (int i = 0; i < size(StandardDeviation); i++)
    {
        double TempVar = pow(StandardDeviation[i], 2);
        StandardDeviation[i] = TempVar;
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
double Storage::AirqualityVariance(double SumOfAirqual)
{

    //vector för att hålla värderna för varians
    vector<double> StandardDeviation = {};
    double StandAvg = SumOfAirqual;
    StandAvg = StandAvg / SizeOfAirquality();
    //detta subtraherar alla värderna med medelvärdet
    for (int i = 0; i < size(MeasurmentsList); i++)
    {
        if (MeasurmentsList[i].UnitOfMeasurment == "%")
        {
            double Temp = MeasurmentsList[i].Measurement;
            double TempVar = Temp - StandAvg;
            StandardDeviation.push_back(TempVar);
        }
    }
    //detta kvadrerar alla dem subtraherade nummrena
    for (int i = 0; i < size(StandardDeviation); i++)
    {
        double TempVar = pow(StandardDeviation[i], 2);
        StandardDeviation[i] = TempVar;
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
    double MaxTemp = MeasurmentsList[0].Measurement;
    string MaxTimeStamp = MeasurmentsList[0].TimeStamp;
    string MaxSensorName = MeasurmentsList[0].SensorName;
    string MaxUnitOfMeasurment = MeasurmentsList[0].UnitOfMeasurment;
    for (int i = 0; i < SizeOfTemperature(); i++)
    {
        if (MeasurmentsList[i].UnitOfMeasurment == "C")
        {
            if (MaxTemp < MeasurmentsList[i].Measurement)
            {
                MaxTemp = MeasurmentsList[i].Measurement;
                MaxTimeStamp = MeasurmentsList[i].TimeStamp;
                MaxSensorName = MeasurmentsList[i].SensorName;
                MaxUnitOfMeasurment = MeasurmentsList[i].UnitOfMeasurment;
            }
        }

    }
    double MinTemp = MeasurmentsList[0].Measurement;
    string MinTimeStamp = MeasurmentsList[0].TimeStamp;
    string MinSensorName = MeasurmentsList[0].SensorName;
    string MinUnitOfMeasurment = MeasurmentsList[0].UnitOfMeasurment;
    for (int i = 0; i < SizeOfTemperature(); i++)
    {
        if (MeasurmentsList[i].UnitOfMeasurment == "C")
        {
            if (MinTemp > MeasurmentsList[i].Measurement)
            {
                MinTemp = MeasurmentsList[i].Measurement;
                MinTimeStamp = MeasurmentsList[i].TimeStamp;
                MinSensorName = MeasurmentsList[i].SensorName;
                MinUnitOfMeasurment = MeasurmentsList[i].UnitOfMeasurment;
            }
        }

    }
    Measurement MaxReading;
    Measurement MinReading;
    MaxReading.GetReading(MaxSensorName, MaxTemp, MaxUnitOfMeasurment, MaxTimeStamp);
    MinReading.GetReading(MinSensorName, MinTemp, MinUnitOfMeasurment, MinTimeStamp);
    cout << "--------------------------------" << endl;
    cout << "Max Reading is" << endl;
    MaxReading.PrintMeasurement();
    cout << "Minx Reading is" << endl;
    MinReading.PrintMeasurement();
    cout << "--------------------------------" << endl;
}
void Storage::MinMaxAirquality()
{
    double MaxAirqual = MeasurmentsList[0].Measurement;
    string MaxTimeStamp = MeasurmentsList[0].TimeStamp;
    string MaxSensorName = MeasurmentsList[0].SensorName;
    string MaxUnitOfMeasurment = MeasurmentsList[0].UnitOfMeasurment;
    for (int i = 0; i < SizeOfAirquality(); i++)
    {
        if (MeasurmentsList[i].UnitOfMeasurment == "%")
        {
            if (MaxAirqual < MeasurmentsList[i].Measurement)
            {
                MaxAirqual = MeasurmentsList[i].Measurement;
                MaxTimeStamp = MeasurmentsList[i].TimeStamp;
                MaxSensorName = MeasurmentsList[i].SensorName;
                MaxUnitOfMeasurment = MeasurmentsList[i].UnitOfMeasurment;
            }
        }
    }
    double MinAirqual = MeasurmentsList[0].Measurement;
    string MinTimeStamp = MeasurmentsList[0].TimeStamp;
    string MinSensorName = MeasurmentsList[0].SensorName;
    string MinUnitOfMeasurment = MeasurmentsList[0].UnitOfMeasurment;
    for (int i = 0; i < SizeOfAirquality(); i++)
    {
        if (MeasurmentsList[i].UnitOfMeasurment == "%")
        {
            if (MinAirqual > MeasurmentsList[i].Measurement)
            {
                MinAirqual = MeasurmentsList[i].Measurement;
                MinTimeStamp = MeasurmentsList[i].TimeStamp;
                MinSensorName = MeasurmentsList[i].SensorName;
                MinUnitOfMeasurment = MeasurmentsList[i].Measurement;
            }
        }
    }
    Measurement MaxReading;
    Measurement MinReading;
    MaxReading.GetReading(MaxSensorName, MaxAirqual, MaxUnitOfMeasurment, MaxTimeStamp);
    MinReading.GetReading(MinSensorName, MinAirqual, MinUnitOfMeasurment, MinTimeStamp);
    cout << "--------------------------------" << endl;
    cout << "Max Reading is" << endl;
    MaxReading.PrintMeasurement();
    cout << "Minx Reading is" << endl;
    MinReading.PrintMeasurement();
    cout << "--------------------------------" << endl;
}