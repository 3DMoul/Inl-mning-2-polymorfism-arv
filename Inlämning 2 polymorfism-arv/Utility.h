#pragma once
#include "Storage.h"
using namespace std;
class Utility
{
public:
	//detta skapar random value med decimaler
	static double randomMaxMinDecimal(double Min, double Max);
	//detta skapar en random int value
	static int randomMaxMin(int Max, int Min);
	//detta gör att man inte av mistaf ger en int en string value vilket kommer krasha programet
	static int numberInputSafeGaurd(const string StringInput);
	//detta får fram Timestamp
	static string TimeGenerator();
	//detta gör att man ska klicka enter om man vill fortsätta så att man kan se värdet på det man kolla på innnan det försviner
	void ENTER();
	//detta är bara en bunt av menyer till varje menu val
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