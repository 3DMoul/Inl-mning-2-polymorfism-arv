#include "Utility.h"
#include "Sensor.h"
double Sensor::Read(double MinSimulation, double MaxSimulation)
{
	return RandomTempreture(MinSimulation, MaxSimulation);
}
string Sensor::name() const
{

}
string Sensor::GetUnitOfMeasurment() const
{

}