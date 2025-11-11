#pragma once
#include "Storage.h"
using namespace std;
class Utility
{
public:
	static double RandomTempreture(double Min, double Max);
	static int RandomAirquality(int Max, int Min);
	void ReadFile();
	void WriteFile(const string TimeStamp, const string UnitOfMeasurment, double Temperature);
	static int NumberChoice(const string StringInput);
	static string TimeGenerator();
	void ENTER();
};