#include <random>
#include <iostream>
#include <fstream>
#include "Utility.h"
#include "Storage.h"
#include "SystemController.h"
using namespace std;
//enum class SensorScript {};
double Utility::randomMaxMinDecimal(double Min, double Max)
{
    double f = (double)rand() / RAND_MAX;
    double RandomTempreture = Min + f * (Max - Min);
    return RandomTempreture;
}
int Utility::randomMaxMin(int Max, int Min)
{
    return rand() % (Min - Max) + Max;
}
int Utility::numberInputSafeGaurd(string StringInput)
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
void Utility::printMenu(int alarmcount)
{
    system("CLS");
    std::cout << "The amount of alarms active is: " << alarmcount << std::endl;
    cout << "---------------------------------" << endl;
    cout << "[1] Adding sensor readings" << endl;
    cout << "[2] Read out readings" << endl;
    cout << "[3] Statistics of readings" << endl;
    cout << "[4] Visual representation of data" << endl;
    cout << "[5] Search for readings" << endl;
    cout << "[6] Edit threshold rules" << endl;
    cout << "[7] Show alarm" << endl;
    cout << "[8] Show sensor configs" << endl;
    cout << "[9] Exit program" << endl;
    cout << "---------------------------------" << endl;
}
void Utility::simulationmenu()
{
    cout << "Do you want to simulate sensor readings" << endl;
    cout << "[T] emperature / [A]irquality / [H]umidity / [E]very sensor type" << endl;
    cout << "If you dont want to simulate anything press [Q]" << endl;
}
void Utility::printReadingMenu()
{
    cout << "You have [" << Storage::sizeOfTypeSensor("%") << "]" << " Airquality readings" << endl;
    cout << "You have [" << Storage::sizeOfTypeSensor("C") << "]" << " Temperature readings" << endl;
    cout << "You have [" << Storage::sizeOfTypeSensor("AH") << "]" << " Humidity readings" << endl;
    cout << "Do you want to print sensor readings" << endl;
    cout << "[T] emperature / [A]irquality / [H]umidity / [E]very sensor type" << endl;
    cout << "If you dont want to print anything press [Q]" << endl;
}
void Utility::statisticMenu()
{
    cout << "You have [" << Storage::sizeOfTypeSensor("%") << "] Airquality readings" << endl;
    cout << "You have [" << Storage::sizeOfTypeSensor("C") << "] Temperature readings" << endl;
    cout << "You have [" << Storage::sizeOfTypeSensor("AH") << "] Humidity readings" << endl;
    cout << "What do you want statistics of" << endl;
    cout << "[T] emperature / [A]irquality / [H]umidity / [E]very sensor type" << endl;
    cout << "If you dont want statistics of anything press [Q]" << endl;
}
void Utility::visualRepMenu() 
{
    cout << "Do you want to print sensor readings" << endl;
    cout << "[T] emperature / [A]irquality / [H]umidity / [E]very sensor type" << endl;
    cout << "If you dont want to print anything press [Q]" << endl;
}
void Utility::searchMenu()
{
    cout << "What Sensor do you want a reading from" << endl;
    cout << "You can search with [N]ames or [T]ime" << endl;
    cout << "If you dont want to search for anything press [Q]" << endl;
}
void Utility::editMenu()
{
    cout << "Do you want to edit threshold: " << endl;
    cout << "[Y]es / [N]o" << endl;
}
void Utility::showAlarmMenu()
{
    cout << "Do you want to see all the alarms" << endl;
    cout << "[Y]es / [N]o" << endl;
}
void Utility::sensorConfigsMenu()
{
    cout << "Do you want to see all the sensor configs" << endl;
    cout << "[Y]es / [N]o" << endl;
}
string temperaturePrompts::SimulatingSensorprompt()const
{
    return "How many Temperature readings do you want to simulate?";
}
string airqualityPrompts::SimulatingSensorprompt()const
{
    return "How many Airquality readings do you want to simulate?";
}
string humidityPrompts::SimulatingSensorprompt()const
{
    return "How many Humidity readings do you want to simulate?";
}