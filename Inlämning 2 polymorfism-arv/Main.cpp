#include "Storage.h"
#include "AirqualitySensor.h"
#include "TemperatureSensor.h"
#include "Utility.h"
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	Utility Utility;
	Storage MainStorage;
	AirqualitySensor MainAirqiality;
	TemperatureSensor MainTemperature;
	MainStorage.ReadFile();
	bool MainLoopActive = true;
	while (MainLoopActive == true)
	{
		system("CLS");
		cout << "---------------------------------" << endl;
		cout << "[1] Adding sensor readings" << endl;
		cout << "[2] Read out readings" << endl;
		cout << "[3] Statistics of readings" << endl;
		cout << "[4] Visual representation of data" << endl;
		cout << "[5] Search for readings" << endl;
		cout << "[6] Exit program" << endl;
		cout << "---------------------------------" << endl;
		string NumberChoice = "Choice between [1]-[6]";
		int Choice = Utility.NumberChoice(NumberChoice);
		switch (Choice)
		{
		case 1:
		{
			system("CLS");
			bool SimulatorRunning = true;
			while (SimulatorRunning == true)
			{
				cout << "Do you want to simulate sensor readings" << endl;
				cout << "[T]emperature / [A]irquality / [B]oth" << endl;
				cout << "If you dont want to simulate anything press [Q]" << endl;
				char Des;
				cin >> Des;
				//använder toupper så man kan skriva bådde stor eller liten bokstav
				if ((char)toupper(Des) == 'T')
				{
					string TimeQuestion = "How many Temperature readings do you want to simulate?";
					int Iterations = Utility.NumberChoice(TimeQuestion);
					for (int i = 0; i < Iterations; i++)
					{
						string NewSensorName;
						cin >> NewSensorName;
						TemperatureSensor New_Temperature_Reading;
						Measurement TemperatureReading;
						TemperatureReading.GetReading(NewSensorName, New_Temperature_Reading.Read(), New_Temperature_Reading.GetUnitOfMeasurment(), Utility.TimeGenerator());
						MainStorage.WriteFile(TemperatureReading.TimeStamp, TemperatureReading.UnitOfMeasurment, TemperatureReading.SensorName, TemperatureReading.Measurement);
						MainStorage.GetMeasurementReading(TemperatureReading);
					}
					Utility.ENTER();
					SimulatorRunning = false;
				}
				else if ((char)toupper(Des) == 'A')
				{
					string TimeQuestion = "How many Airquality readings do you want to simulate?";
					int Iterations = Utility.NumberChoice(TimeQuestion);
					for (int i = 0; i < Iterations; i++)
					{
						string NewSensorName;
						cin >> NewSensorName;
						AirqualitySensor New_Airquality_Reading;
						Measurement AirqualityReading;
						AirqualityReading.GetReading(NewSensorName, New_Airquality_Reading.Read(), New_Airquality_Reading.GetUnitOfMeasurment(), Utility.TimeGenerator());
						MainStorage.WriteFile(AirqualityReading.TimeStamp, AirqualityReading.UnitOfMeasurment, AirqualityReading.SensorName, AirqualityReading.Measurement);
						MainStorage.GetMeasurementReading(AirqualityReading);
					}
					Utility.ENTER();
					SimulatorRunning = false;
				}
				else if ((char)toupper(Des) == 'B')
				{
					string TimeQuestion = "How many readings do you want to simulate?";
					int Iterations = Utility.NumberChoice(TimeQuestion);
					for (int i = 0; i < Iterations; i++)
					{
						string NewSensorName;
						cin >> NewSensorName;
						TemperatureSensor New_Temperature_Reading;
						Measurement TemperatureReading;
						TemperatureReading.GetReading(NewSensorName, New_Temperature_Reading.Read(), New_Temperature_Reading.GetUnitOfMeasurment(), Utility.TimeGenerator());
						MainStorage.WriteFile(TemperatureReading.TimeStamp, TemperatureReading.UnitOfMeasurment, TemperatureReading.SensorName, TemperatureReading.Measurement);
						MainStorage.GetMeasurementReading(TemperatureReading);
					}
					for (int i = 0; i < Iterations; i++)
					{
						string NewSensorName;
						cin >> NewSensorName;
						AirqualitySensor New_Airquality_Reading;
						Measurement AirqualityReading;
						AirqualityReading.GetReading(NewSensorName, New_Airquality_Reading.Read(), New_Airquality_Reading.GetUnitOfMeasurment(), Utility.TimeGenerator());
						MainStorage.WriteFile(AirqualityReading.TimeStamp, AirqualityReading.UnitOfMeasurment, AirqualityReading.SensorName, AirqualityReading.Measurement);
						MainStorage.GetMeasurementReading(AirqualityReading);
					}
					Utility.ENTER();
					SimulatorRunning = false;
				}
				else
				{
					cout << "Wrong input" << endl;
				}
			}
		}
		break;
		case 2:
		{
			system("CLS");
			bool PrintLoopisRunning = true;
			while (PrintLoopisRunning == true)
			{
				if (MainStorage.SizeOfAirquality() >= 1 || MainStorage.SizeOfTemperature() >= 1)
				{

					cout << "You have [" << MainStorage.SizeOfAirquality() << "]" << " Airquality readings" << endl;
					cout << "You have [" << MainStorage.SizeOfTemperature() << "]" << " Temperature readings" << endl;
					cout << "Do you want to print sensor readings" << endl;
					cout << "[T]emperature / [A]irquality / [B]oth" << endl;
					cout << "If you dont want to print anything press [Q]" << endl;
					char Des;
					cin >> Des;
					//använder toupper så man kan skriva bådde stor eller liten bokstav
					if ((char)toupper(Des) == 'T')
					{
						if (MainStorage.SizeOfTemperature() >= 1)
						{
							MainStorage.PrintTemperatureReadings();
							PrintLoopisRunning = false;
						}
						else
						{
							cout << "you have no temperature readings" << endl;
						}
					}
					else if ((char)toupper(Des) == 'A')
					{
						if (MainStorage.SizeOfAirquality() >= 1)
						{
							MainStorage.PrintAirqualityReadings();
							PrintLoopisRunning = false;
						}
						else
						{
							cout << "you have no airquality readings" << endl;
						}
					}
					else if ((char)toupper(Des) == 'B')
					{
						if (MainStorage.SizeOfAirquality() >= 1 && MainStorage.SizeOfTemperature() >= 1)
						{
							MainStorage.PrintAll();
						}
						else if (MainStorage.SizeOfAirquality() < 1)
						{
							cout << "you have no airquality readings" << endl;
							MainStorage.PrintTemperatureReadings();
						}
						else if (MainStorage.SizeOfTemperature() < 1)
						{
							cout << "you have no temperature readings" << endl;
							MainStorage.PrintAirqualityReadings();
						}
						Utility.ENTER();
						PrintLoopisRunning = false;
					}
					else if ((char)toupper(Des) == 'Q')
					{
						Utility.ENTER();
						PrintLoopisRunning = false;
					}
					else
					{
						cout << "Wrong input" << endl;
					}
				}
				else
				{
					cout << "you dont have anything to print" << endl;
					PrintLoopisRunning = false;
				}
				Utility.ENTER();
			}
		}
		break;
		case 3:
		{
			system("CLS");
			bool StatisticsLoopRunning = true;
			while (StatisticsLoopRunning == true)
			{
				cout << "You have [" << MainStorage.SizeOfAirquality() << "] Airquality readings" << endl;
				cout << "You have [" << MainStorage.SizeOfTemperature() << "] Temperature readings" << endl;
				if (MainStorage.SizeOfAirquality() >= 1 || MainStorage.SizeOfTemperature() >= 1)
				{
					cout << "What do you want statistics of" << endl;
					cout << "[T]emperature / [A]irquality / [B]oth" << endl;
					cout << "If you dont want statistics of anything press [Q]" << endl;
					char Des;
					cin >> Des;
					if ((char)toupper(Des) == 'T')
					{
						if (MainStorage.SizeOfTemperature() >= 1)
						{
							double SumOfTemp = MainStorage.SumOfTemperature();
							cout << "The sum of all Temperature readings is: " << SumOfTemp << MainTemperature.GetUnitOfMeasurment() << endl;
							cout << "and the avarage is: " << SumOfTemp / MainStorage.SizeOfTemperature() << MainTemperature.GetUnitOfMeasurment() << endl;
							void MinMaxTemperature();
							double VarianceTemperature = MainStorage.TemperatureVariance(SumOfTemp);
							cout << "The sample varians is " << VarianceTemperature / (MainStorage.SizeOfTemperature() - 1) << MainTemperature.GetUnitOfMeasurment() << std::endl;
							cout << "The population varians is " << VarianceTemperature / MainStorage.SizeOfTemperature() << MainTemperature.GetUnitOfMeasurment() << std::endl;
						}
						else
						{
							cout << "You dont have any temperature readings" << endl;
						}
					}
					else if ((char)toupper(Des) == 'A')
					{
						if (MainStorage.SizeOfAirquality() >= 1)
						{
							double SumOfAirqual = MainStorage.SumOfAirquality();
							cout << "The sum of all airquality readings is: " << SumOfAirqual << MainAirqiality.GetUnitOfMeasurment() << endl;
							cout << "and the avarage is: " << SumOfAirqual / MainStorage.SizeOfAirquality() << MainAirqiality.GetUnitOfMeasurment() << endl;
							void MinMaxAirquality();
							double VarianceAirqual = MainStorage.AirqualityVariance(SumOfAirqual);
							cout << "The sample varians is " << VarianceAirqual / (MainStorage.SizeOfAirquality() - 1) << MainAirqiality.GetUnitOfMeasurment() << endl;
							cout << "The population varians is " << VarianceAirqual / MainStorage.SizeOfAirquality() << MainAirqiality.GetUnitOfMeasurment() << endl;
						}
						else
						{
							cout << "You dont have any airquality readings" << endl;
						}
					}
					else if ((char)toupper(Des) == 'B')
					{
						if (MainStorage.SizeOfAirquality() >= 1 && MainStorage.SizeOfTemperature() >= 1)
						{
							double SumOfTemp = MainStorage.SumOfTemperature();
							cout << "The sum of all Temperature readings is: " << SumOfTemp << MainTemperature.GetUnitOfMeasurment() << endl;
							cout << "and the avarage is: " << SumOfTemp / MainStorage.SizeOfTemperature() << MainTemperature.GetUnitOfMeasurment() << endl;
							void MinMaxTemperature();
							double VarianceTemperature = MainStorage.TemperatureVariance(SumOfTemp);
							cout << "The sample varians is " << VarianceTemperature / (MainStorage.SizeOfTemperature() - 1) << MainTemperature.GetUnitOfMeasurment() << endl;
							cout << "The population varians is " << VarianceTemperature / MainStorage.SizeOfTemperature() << MainTemperature.GetUnitOfMeasurment() << endl;
							double SumOfAirqual = MainStorage.SumOfAirquality();
							cout << "The sum of all airquality readings is: " << SumOfAirqual << MainAirqiality.GetUnitOfMeasurment() << endl;
							cout << "and the avarage is: " << SumOfAirqual / MainStorage.SizeOfAirquality() << MainAirqiality.GetUnitOfMeasurment() << endl;
							void MinMaxAirquality();
							double VarianceAirqual = MainStorage.AirqualityVariance(SumOfAirqual);
							cout << "The sample varians is " << VarianceAirqual / (MainStorage.SizeOfAirquality() - 1) << MainAirqiality.GetUnitOfMeasurment() << endl;
							cout << "The population varians is " << VarianceAirqual / MainStorage.SizeOfAirquality() << MainAirqiality.GetUnitOfMeasurment() << endl;
						}
						else if (MainStorage.SizeOfAirquality() >= 1 && MainStorage.SizeOfTemperature() < 1)
						{
							cout << "You dont have any temperature readings" << endl;
							double SumOfAirqual = MainStorage.SumOfAirquality();
							cout << "The sum of all airquality readings is: " << SumOfAirqual << MainAirqiality.GetUnitOfMeasurment() << endl;
							cout << "and the avarage is: " << SumOfAirqual / MainStorage.SizeOfTemperature() << MainAirqiality.GetUnitOfMeasurment() << endl;
							void MinMaxAirquality();
							double VarianceAirqual = MainStorage.TemperatureVariance(SumOfAirqual);
							cout << "The sample varians is " << VarianceAirqual / (MainStorage.SizeOfAirquality() - 1) << MainAirqiality.GetUnitOfMeasurment() << endl;
							cout << "The population varians is " << VarianceAirqual / MainStorage.SizeOfAirquality() << MainAirqiality.GetUnitOfMeasurment() << endl;
						}
						else if (MainStorage.SizeOfAirquality() < 1 && MainStorage.SizeOfTemperature() >= 1)
						{
							cout << "You dont have any airquality readings" << endl;
							double SumOfTemp = MainStorage.SumOfTemperature();
							cout << "The sum of all Temperature readings is: " << SumOfTemp << MainTemperature.GetUnitOfMeasurment() << endl;
							cout << "and the avarage is: " << SumOfTemp / MainStorage.SizeOfTemperature() << MainTemperature.GetUnitOfMeasurment() << endl;
							void MinMaxTemperature();
							double VarianceTemperature = MainStorage.TemperatureVariance(SumOfTemp);
							cout << "The sample varians is " << VarianceTemperature / (MainStorage.SizeOfTemperature() - 1) << MainTemperature.GetUnitOfMeasurment() << endl;
							cout << "The population varians is " << VarianceTemperature / MainStorage.SizeOfTemperature() << MainTemperature.GetUnitOfMeasurment() << endl;
						}
					}
					else if ((char)toupper(Des) == 'Q')
					{
						StatisticsLoopRunning = false;
					}
					else
					{
						cout << "Wrong input" << endl;
					}
				}
				else
				{
					cout << "you dont have anything to check" << endl;
					StatisticsLoopRunning = false;
				}
				Utility.ENTER();
			}
		}
		break;
		case 4:
		{
			system("CLS");
			bool VisualisationLoopRunning = true;
			while (VisualisationLoopRunning == true)
			{

				if (MainStorage.SizeOfAirquality() >= 1 || MainStorage.SizeOfTemperature() >= 1)
				{
					cout << "Do you want to print sensor readings" << endl;
					cout << "[T]emperature / [A]irquality / [B]oth" << endl;
					cout << "If you dont want to print anything press [Q]" << endl;
					char Des;
					cin >> Des;
					//använder toupper så man kan skriva bådde stor eller liten bokstav
					if ((char)toupper(Des) == 'T')
					{
						if (MainStorage.SizeOfTemperature() >= 1)
						{
							//detta går igenom bådde <TemperatureSensor> och <AirqualitySensor>
							MainStorage.Visulisation(Des);
							Utility.ENTER();
							VisualisationLoopRunning = false;
						}
						else
						{
							cout << "You dont have any temperatur readings" << endl;
						}
					}
					else if ((char)toupper(Des) == 'A')
					{
						if (MainStorage.SizeOfAirquality() >= 1)
						{
							MainStorage.Visulisation(Des);
							Utility.ENTER();
							VisualisationLoopRunning = false;
						}
						else
						{
							cout << "You dont have any airquality readings" << endl;
						}
					}
					else if ((char)toupper(Des) == 'B')
					{
						if (MainStorage.SizeOfAirquality() >= 1 && MainStorage.SizeOfTemperature() >= 1)
						{
							MainStorage.Visulisation(Des);
							VisualisationLoopRunning = false;
						}
						else if (MainStorage.SizeOfAirquality() >= 1 && MainStorage.SizeOfTemperature() < 1)
						{
							cout << "You dont have any temperatur readings" << endl;
							MainStorage.Visulisation(Des);
							VisualisationLoopRunning = false;
						}
						else if (MainStorage.SizeOfAirquality() < 1 && MainStorage.SizeOfTemperature() >= 1)
						{
							cout << "You dont have any airquality readings" << endl;
							MainStorage.Visulisation(Des);
							VisualisationLoopRunning = false;
						}
					}
					else if ((char)toupper(Des) == 'Q')
					{
						VisualisationLoopRunning = false;
					}
					else
					{
						cout << "Wrong input" << endl;
					}
				}
				else
				{
					cout << "you dont have anything to check" << endl;
					VisualisationLoopRunning = false;
				}
				Utility.ENTER();
			}

		}
		break;
		case 5:
		{
			system("CLS");
			bool SearchIsRunning = true;
			while (SearchIsRunning == true)
			{
				if (MainStorage.SizeOfAirquality() >= 1 || MainStorage.SizeOfTemperature() >= 1)
				{
					cout << "What Sensor do you want a reading from" << endl;
					cout << "You can search with [N]ames or [T]ime" << endl;
					cout << "If you dont want to search for anything press [Q]" << endl;
					char Des;
					cin >> Des;
					if ((char)toupper(Des) == 'N')
					{
						bool SearchNameRunning = true;
						while (SearchNameRunning == true)
						{
							cout << "what name does the sensor have: " << endl;
							cout << "If you dont remember the name of sensor press [P] to print out list" << endl;
							char SearchName;
							cin >> SearchName;
							if ((char)toupper(SearchName) == 'P')
							{
								MainStorage.PrintAll();
							}
							else
							{
								SearchNameRunning = MainStorage.SearchForName(string(1, SearchName));
							}
						}
						SearchIsRunning = false;
					}
					else if ((char)toupper(Des) == 'T')
					{
						bool SearchTimeRunning = true;
						while (SearchTimeRunning == true)
						{
							cout << "What TimeStamp does the sensor have: " << endl;
							cout << "This is the template for the search (00:00:00)" << endl;
							cout << "If you dont remember the Time of the reading press [P] to print out list" << endl;
							char SearchTimeStamp;
							cin >> SearchTimeStamp;
							if ((char)toupper(SearchTimeStamp) == 'P')
							{
								MainStorage.PrintAll();
							}
							else
							{
								SearchTimeRunning = MainStorage.SearchForTimeStamp(string(1, SearchTimeStamp));
							}
						}
						SearchIsRunning = false;
					}
					else if ((char)toupper(Des) == 'Q')
					{
						SearchIsRunning = false;
					}
					else
					{
						cout << "Wrong input" << endl;
					}
				}
				else
				{
					cout << "You dont have any readings to search for" << endl;
					SearchIsRunning == false;
				}
				Utility.ENTER();
			}


		}
		break;
		case 6:
		{
			Utility.ENTER();
			MainLoopActive = false;
		}
		break;
		default:
		{
			cout << "Wrong input choices are between [1]-[6]" << endl;
		}
		break;
		}

	}
}
