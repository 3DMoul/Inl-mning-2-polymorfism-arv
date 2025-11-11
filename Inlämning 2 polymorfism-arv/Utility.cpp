#include "Utility.h"
#include "Storage.h"
#include <random>
#include <iostream>
#include <fstream>
using namespace std;
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