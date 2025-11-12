#pragma once
#include "Storage.h"
using namespace std;
enum class TypeScript { AirqualityScrips = 'A', TemperatureScrips = 'T', HumidityScrips = 'H'};
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
struct Script {
	virtual ~Script() = default;
	virtual string SimulatingSensorScript()const = 0;
};
struct TemperatureScrips : Script
{
	string SimulatingSensorScript()const override;
};
struct AirqualityScrips : Script
{
	string SimulatingSensorScript()const override;
};
struct HumidityScrips : Script
{
	string SimulatingSensorScript()const override;
};