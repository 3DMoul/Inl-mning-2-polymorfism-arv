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
	void StatisticMenu();
	void visualRepMenu();
	void searchMenu();
	void showAlarmMenu();
	void sensorConfigsMenu();
};
// here is all the text for all the different options
struct prompt 
{//promt message
	virtual ~prompt() = default;
	virtual string SimulatingSensorprompt()const = 0;
};
struct temperaturePrompts : prompt
{
	string SimulatingSensorprompt()const override;
};
struct airqualityPrompts : prompt
{
	string SimulatingSensorprompt()const override;
};
struct humidityPrompts : prompt
{
	string SimulatingSensorprompt()const override;
};