#pragma once
#include "Storage.h"
using namespace std;
class Utility
{
public:
	static double RandomTempreture(double Min, double Max);
	static int RandomAirquality(int Max, int Min);
	static int NumberChoice(const string StringInput);
	static string TimeGenerator();
	void ENTER();
	void PrintMenu();
	void Simulationmenu();
	void PrintReadingMenu();
};
// here is all the text for all the different options
struct promt 
{//promt message
	virtual ~promt() = default;
	virtual string SimulatingSensorpromt()const = 0;
};
struct temperaturePromts : promt
{
	string SimulatingSensorpromt()const override;
};
struct airqualityPromts : promt
{
	string SimulatingSensorpromt()const override;
};
struct humidityPromts : promt
{
	string SimulatingSensorpromt()const override;
};