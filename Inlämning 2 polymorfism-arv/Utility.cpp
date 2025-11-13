#include "Utility.h"
#include "Storage.h"
#include <random>
#include <iostream>
#include <fstream>
using namespace std;
//enum class SensorScript {};
double Utility::RandomTempreture(double Min, double Max)
{
    double f = (double)rand() / RAND_MAX;
    double RandomTempreture = Min + f * (Max - Min);
    return RandomTempreture;
}
int Utility::RandomAirquality(int Max, int Min)
{
    return rand() % (Min - Max) + Max;
}
int Utility::NumberChoice(string StringInput)
{
    std::cout << StringInput << std::endl;
    int Choice;
    //failsafe loop för val
    while (!(cin >> Choice))
    {
        cout << "Error you have inputed a invalid value please input a number:  " << std::endl;
        cin.clear();
        streamsize InputBufferLimit = 10000;
        cin.ignore(InputBufferLimit, '\n');
        cout << StringInput << endl;
    }
    return Choice;
}
string Utility::TimeGenerator()
{
    time_t TimeStamp;
    time(&TimeStamp);
    struct tm timeInfo;
    localtime_s(&timeInfo, &TimeStamp);
    char temp[26];
    asctime_s(temp, sizeof(temp), &timeInfo);
    temp[strlen(temp) - 1] = '\0'; // tar bort newline
    return temp;
}
void Utility::ENTER()
{
    cout << "Klick \"ENTER\" too continue" << endl;
    string str;
    getline(cin, str);
    streamsize InputBufferLimit = 10000;
    cin.ignore(InputBufferLimit, '\n');
}
void Utility::PrintMenu()
{
    system("CLS");
    cout << "---------------------------------" << endl;
    cout << "[1] Adding sensor readings" << endl;
    cout << "[2] Read out readings" << endl;
    cout << "[3] Statistics of readings" << endl;
    cout << "[4] Visual representation of data" << endl;
    cout << "[5] Search for readings" << endl;
    cout << "[6] Exit program" << endl;
    cout << "---------------------------------" << endl;
}
void Utility::Simulationmenu()
{
    cout << "Do you want to simulate sensor readings" << endl;
    cout << "[T]emperature / [A]irquality / [H]umidity / [B]oth" << endl;
    cout << "If you dont want to simulate anything press [Q]" << endl;
}
void Utility::PrintReadingMenu()
{
    cout << "You have [" << Storage::SizeOfAirquality() << "]" << " Airquality readings" << endl;
    cout << "You have [" << Storage::SizeOfTemperature() << "]" << " Temperature readings" << endl;
    cout << "Do you want to print sensor readings" << endl;
    cout << "[T]emperature / [A]irquality / [H]umidity / [A]ll" << endl;
    cout << "If you dont want to print anything press [Q]" << endl;
}
string TemperatureScripts::SimulatingSensorScript()const
{
    return "How many Temperature readings do you want to simulate?";
}
string AirqualityScripts::SimulatingSensorScript()const
{
    return "How many Airquality readings do you want to simulate?";
}
string HumidityScripts::SimulatingSensorScript()const
{
    return "How many Humidity readings do you want to simulate?";
}