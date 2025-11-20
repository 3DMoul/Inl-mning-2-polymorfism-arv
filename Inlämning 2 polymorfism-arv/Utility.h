#pragma once
#include "Storage.h"
using namespace std;
class Utility
{
public:
	static double randomMaxMinDecimal(double Min, double Max);
	static int randomMaxMin(int Max, int Min);
	static int numberInputSafeGaurd(const string StringInput);
	static string TimeGenerator();
	void ENTER();
	void printMenu(int alarmcount);
	void simulationmenu();
	void printReadingMenu();
	void statisticMenu();
	void visualRepMenu();
	void searchMenu();
	void editMenu();
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