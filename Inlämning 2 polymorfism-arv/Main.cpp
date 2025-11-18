#include "Storage.h"
#include "Utility.h"
#include "Sensor.h"
#include "SensorType.h"
#include <iostream>
#include <vector>
#include "SystemController.h"
using namespace std;
int main()
{
	Utility Utility;
	Storage MainStorage;
	SystemController systemController;
	MainStorage.ReadFile();
	systemController.loadFromFile();
	bool MainLoopActive = true;
	while (MainLoopActive == true)
	{
		systemController.checkAlarm();
		int alarmCounts = systemController.getAlarmCount();
		std::cout << "The amount of alarms active is: " << alarmCounts << std::endl;
		Utility.PrintMenu();
		string NumberChoice = "Choice between [1]-[9]";
		int Choice = Utility.NumberChoice(NumberChoice);
		switch (Choice)
		{
		case 1:
		{
			system("CLS");
			bool SimulatorRunning = true;
			while (SimulatorRunning == true)
			{
				Utility.Simulationmenu();
				char typeChoice;
				cin >> typeChoice;
				//använder toupper så man kan skriva bådde stor eller liten bokstav
				if (static_cast<char>(std::toupper(typeChoice)) == 'T')
				{
					MainStorage.GetMeasurementReading(static_cast<char>(std::toupper(typeChoice)));
					SimulatorRunning = false;
				}
				else if (static_cast<char>(std::toupper(typeChoice)) == 'A')
				{
					MainStorage.GetMeasurementReading(static_cast<char>(std::toupper(typeChoice)));
					SimulatorRunning = false;
				}
				else if (static_cast<char>(std::toupper(typeChoice)) == 'H')
				{
					MainStorage.GetMeasurementReading(static_cast<char>(std::toupper(typeChoice)));
					SimulatorRunning = false;
				}
				else if (static_cast<char>(std::toupper(typeChoice)) == 'E')
				{
					MainStorage.GetMeasurementReading('T');
					MainStorage.GetMeasurementReading('A');
					MainStorage.GetMeasurementReading('H');
					SimulatorRunning = false;
				}
				else if (static_cast<char>(std::toupper(typeChoice)) == 'Q')
				{
					SimulatorRunning = false;
				}
				else
				{
					cout << "Wrong input" << endl;
				}
			}
			Utility.ENTER();
		}
		break;
		case 2:
		{
			system("CLS");
			bool PrintLoopisRunning = true;
			while (PrintLoopisRunning == true)
			{
				if (MainStorage.SizeOfAirquality() > 0 || MainStorage.SizeOfTemperature() > 0 || MainStorage.sizeOfHumidity() > 0)
				{

					Utility.PrintReadingMenu();
					char printRequest;
					cin >> printRequest;
					//använder toupper så man kan skriva bådde stor eller liten bokstav
					if ((char)toupper(printRequest) == 'T')
					{
						if (MainStorage.SizeOfTemperature() > 0)
						{
							MainStorage.PrintTemperatureReadings();
							PrintLoopisRunning = false;
						}
						else
						{
							cout << "you have no temperature readings" << endl;
						}
					}
					else if ((char)toupper(printRequest) == 'A')
					{
						if (MainStorage.SizeOfAirquality() > 0)
						{
							MainStorage.PrintAirqualityReadings();
							PrintLoopisRunning = false;
						}
						else
						{
							cout << "you have no airquality readings" << endl;
						}
					}
					else if ((char)toupper(printRequest) == 'H')
					{
						if (MainStorage.sizeOfHumidity() > 0)
						{
							MainStorage.printHymidityReadings();
							PrintLoopisRunning = false;
						}
						else
						{
							cout << "you have no humidity readings" << endl;
						}
					}
					else if ((char)toupper(printRequest) == 'E')
					{
							MainStorage.PrintAll();
					}
					else if ((char)toupper(printRequest) == 'Q')
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
				if (MainStorage.SizeOfAirquality() > 0 || MainStorage.SizeOfTemperature() > 0 || MainStorage.sizeOfHumidity() > 0)
				{
					Utility.StatisticMenu();
					char sensorStat;
					cin >> sensorStat;
					if ((char)toupper(sensorStat) == 'T')
					{
						if (MainStorage.SizeOfTemperature() > 0)
						{
							double SumOfTemp = MainStorage.SumOfTemperature();
							cout << "The sum of all Temperature readings is: " << SumOfTemp << "C" << endl;
							cout << "and the avarage is: " << SumOfTemp / MainStorage.SizeOfTemperature() << "C" << endl;
							MainStorage.MinMaxTemperature();
							double VarianceTemperature = MainStorage.TemperatureVariance(SumOfTemp);
							cout << "The sample varians is " << VarianceTemperature / (MainStorage.SizeOfTemperature() - 1) << "C" << std::endl;
							cout << "The population varians is " << VarianceTemperature / MainStorage.SizeOfTemperature() << "C" << std::endl;
						}
						else
						{
							cout << "You dont have any temperature readings" << endl;
						}
					}
					else if ((char)toupper(sensorStat) == 'A')
					{
						if (MainStorage.SizeOfAirquality() > 0)
						{
							double SumOfAirqual = MainStorage.SumOfAirquality();
							cout << "The sum of all airquality readings is: " << SumOfAirqual << "%" << endl;
							cout << "and the avarage is: " << SumOfAirqual / MainStorage.SizeOfAirquality() << "%" << endl;
							MainStorage.MinMaxAirquality();
							double VarianceAirqual = MainStorage.AirqualityVariance(SumOfAirqual);
							cout << "The sample varians is " << VarianceAirqual / (MainStorage.SizeOfAirquality() - 1) << "%" << endl;
							cout << "The population varians is " << VarianceAirqual / MainStorage.SizeOfAirquality() << "%" << endl;
						}
						else
						{
							cout << "You dont have any airquality readings" << endl;
						}
					}
					else if ((char)toupper(sensorStat) == 'H')
					{
						if (MainStorage.sizeOfHumidity() > 0)
						{
							double sumOfHumidity = MainStorage.sumOfHumidity();
							cout << "The sum of all humidity readings is: " << sumOfHumidity << "AH" << endl;
							cout << "and the avarage is: " << sumOfHumidity / MainStorage.sizeOfHumidity() << "AH" << endl;
							MainStorage.MinMaxAirquality();
							double varianceHumidity = MainStorage.humidityVariance(sumOfHumidity);
							cout << "The sample varians is " << varianceHumidity / (MainStorage.sizeOfHumidity() - 1) << "AH" << endl;
							cout << "The population varians is " << varianceHumidity / MainStorage.sizeOfHumidity() << "AH" << endl;
						}
						else
						{
							cout << "You dont have any humidity readings" << endl;
						}
					}
					else if ((char)toupper(sensorStat) == 'E')
					{
						if (MainStorage.SizeOfTemperature() > 0)
						{
							double SumOfTemp = MainStorage.SumOfTemperature();
							cout << "The sum of all Temperature readings is: " << SumOfTemp << "C" << endl;
							cout << "and the avarage is: " << SumOfTemp / MainStorage.SizeOfTemperature() << "C" << endl;
							MainStorage.MinMaxTemperature();
							double VarianceTemperature = MainStorage.TemperatureVariance(SumOfTemp);
							cout << "The sample varians is " << VarianceTemperature / (MainStorage.SizeOfTemperature() - 1) << "C" << std::endl;
							cout << "The population varians is " << VarianceTemperature / MainStorage.SizeOfTemperature() << "C" << std::endl;
						}
						else
						{
							cout << "You dont have any temperature readings" << endl;
						}
						if (MainStorage.SizeOfAirquality() > 0)
						{
							double SumOfAirqual = MainStorage.SumOfAirquality();
							cout << "The sum of all airquality readings is: " << SumOfAirqual << "%" << endl;
							cout << "and the avarage is: " << SumOfAirqual / MainStorage.SizeOfAirquality() << "%" << endl;
							MainStorage.MinMaxAirquality();
							double VarianceAirqual = MainStorage.AirqualityVariance(SumOfAirqual);
							cout << "The sample varians is " << VarianceAirqual / (MainStorage.SizeOfAirquality() - 1) << "%" << endl;
							cout << "The population varians is " << VarianceAirqual / MainStorage.SizeOfAirquality() << "%" << endl;
						}
						else
						{
							cout << "You dont have any airquality readings" << endl;
						}
						if (MainStorage.sizeOfHumidity() > 0)
						{
							double sumOfHumidity = MainStorage.sumOfHumidity();
							cout << "The sum of all humidity readings is: " << sumOfHumidity << "AH" << endl;
							cout << "and the avarage is: " << sumOfHumidity / MainStorage.sizeOfHumidity() << "AH" << endl;
							MainStorage.MinMaxAirquality();
							double varianceHumidity = MainStorage.humidityVariance(sumOfHumidity);
							cout << "The sample varians is " << varianceHumidity / (MainStorage.sizeOfHumidity() - 1) << "AH" << endl;
							cout << "The population varians is " << varianceHumidity / MainStorage.sizeOfHumidity() << "AH" << endl;
						}
						else
						{
							cout << "You dont have any humidity readings" << endl;
						}
					}
					else if ((char)toupper(sensorStat) == 'Q')
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

				if (MainStorage.SizeOfAirquality() > 0 || MainStorage.SizeOfTemperature() > 0 || MainStorage.sizeOfHumidity() > 0)
				{
					Utility.visualRepMenu();
					char visualisationRequest;
					cin >> visualisationRequest;
					//använder toupper så man kan skriva bådde stor eller liten bokstav
					if ((char)toupper(visualisationRequest) == 'T')
					{
						if (MainStorage.SizeOfTemperature() > 0)
						{
							//detta går igenom Measurementlistan och vissar '*' i olicka mängder beroende på reading valuen
							MainStorage.Visulisation(visualisationRequest);
							Utility.ENTER();
							VisualisationLoopRunning = false;
						}
						else
						{
							cout << "You dont have any temperatur readings" << endl;
						}
					}
					else if ((char)toupper(visualisationRequest) == 'A')
					{
						if (MainStorage.SizeOfAirquality() > 0)
						{
							MainStorage.Visulisation(visualisationRequest);
							Utility.ENTER();
							VisualisationLoopRunning = false;
						}
						else
						{
							cout << "You dont have any airquality readings" << endl;
						}
					}
					else if ((char)toupper(visualisationRequest) == 'H')
					{
						if (MainStorage.sizeOfHumidity() > 0)
						{
							MainStorage.Visulisation(visualisationRequest);
							Utility.ENTER();
							VisualisationLoopRunning = false;
						}
						else
						{
							cout << "You dont have any humidity readings" << endl;
						}
					}
					else if ((char)toupper(visualisationRequest) == 'E')
					{
						MainStorage.Visulisation(visualisationRequest);
					}
					else if ((char)toupper(visualisationRequest) == 'Q')
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
				if (MainStorage.SizeOfAirquality() > 0 || MainStorage.SizeOfTemperature() > 0)
				{
					Utility.searchMenu();
					char searchRequest;
					cin >> searchRequest;
					if ((char)toupper(searchRequest) == 'N')
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
					else if ((char)toupper(searchRequest) == 'T')
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
					else if ((char)toupper(searchRequest) == 'Q')
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
					SearchIsRunning = false;
				}
				Utility.ENTER();
			}


		}
		break;
		case 6:
		{
			system("CLS");
			bool editLoopRunning = true;
			while (editLoopRunning == true)
			{

			}
		}
		break;
		case 7:
		{
			system("CLS");
			bool showAlarmLoopRunning = true;
			while (showAlarmLoopRunning == true)
			{
				Utility.showAlarmMenu();
				char showAlarmChoice;
				std::cin >> showAlarmChoice;
				if((char)toupper(showAlarmChoice) == 'Y')
				{
					systemController.showAlerts();
					showAlarmChoice = false;
				}
				else if ((char)toupper(showAlarmChoice) == 'N')
				{
					showAlarmChoice = false;
				}
				else
				{
					cout << "Wrong input" << endl;
				}
			}
			Utility.ENTER();
		}
		break;
		case 8:
		{
			system("CLS");
			bool sensorConfigMenu = true;
			while (sensorConfigMenu == true)
			{
				Utility.sensorConfigsMenu();
				char sensorConfigChoice;
				std::cin >> sensorConfigChoice;
				if ((char)toupper(sensorConfigChoice) == 'Y')
				{
					systemController.showSensorConfig();
					sensorConfigMenu = false;
				}
				else if ((char)toupper(sensorConfigChoice) == 'N')
				{
					sensorConfigMenu = false;
				}
				else
				{
					cout << "Wrong input" << endl;
				}
			}
		}
		break;
		case 9:
		{
			Utility.ENTER();
			MainLoopActive = false;
		}
		break;
		default:
		{
			cout << "Wrong input choices are between [1]-[9]" << endl;
		}
		break;
		}

	}
}
