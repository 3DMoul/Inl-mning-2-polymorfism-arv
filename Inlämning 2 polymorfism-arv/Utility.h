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
struct Script {//promt message
	virtual ~Script() = default;
	virtual string SimulatingSensorScript()const = 0;
};
struct TemperatureScripts : Script
{
	string SimulatingSensorScript()const override;
};
struct AirqualityScripts : Script
{
	string SimulatingSensorScript()const override;
};
struct HumidityScripts : Script
{
	string SimulatingSensorScript()const override;
};