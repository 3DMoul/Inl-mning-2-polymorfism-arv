#include <iostream>
#include <vector>
#include "SystemController.h"
#include "Storage.h"
#include "Utility.h"
#include "Sensor.h"
int main()
{
	Utility Utility;
	Storage MainStorage;
	SystemController Controller;
	MainStorage.ReadFile();
	Controller.loadFromFile();
	Controller.loadThresholdFromFile();
	bool MainLoopActive = true;
	while (MainLoopActive == true)
	{
		Controller.checkAlarm();
		Utility.printMenu(Controller.getAlarmCount());
		string NumberChoice = "Choice between [1]-[9]";
		int Choice = Utility.numberInputSafeGaurd(NumberChoice);
		switch (Choice)
		{
		case 1:
		{
			system("CLS");
			bool SimulatorRunning = true;
			while (SimulatorRunning == true)
			{
				Utility.simulationmenu();
				char typeChoice;
				cin >> typeChoice;
				//testa static_cast<char>(std::toupper(typeChoice)) så det inte spelar rol om man skrev liten eller stor bokstav
				if (static_cast<char>(std::toupper(typeChoice)) == 'T')
				{
					MainStorage.getMeasurementReading(static_cast<char>(std::toupper(typeChoice)));
					SimulatorRunning = false;
				}
				else if (static_cast<char>(std::toupper(typeChoice)) == 'A')
				{
					MainStorage.getMeasurementReading(static_cast<char>(std::toupper(typeChoice)));
					SimulatorRunning = false;
				}
				else if (static_cast<char>(std::toupper(typeChoice)) == 'H')
				{
					MainStorage.getMeasurementReading(static_cast<char>(std::toupper(typeChoice)));
					SimulatorRunning = false;
				}
				else if (static_cast<char>(std::toupper(typeChoice)) == 'E')
				{
					MainStorage.getMeasurementReading('T');
					MainStorage.getMeasurementReading('A');
					MainStorage.getMeasurementReading('H');
					SimulatorRunning = false;
				}
				else if (static_cast<char>(std::toupper(typeChoice)) == 'Q')
				{
					SimulatorRunning = false;
				}
				else
				{
					std::cout << "Wrong input" << endl;
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
				//kollar om man har några värden att kolla på
				if (MainStorage.sizeOfTypeSensor("%") > 0 || MainStorage.sizeOfTypeSensor("C") > 0 || MainStorage.sizeOfTypeSensor("AH") > 0)
				{

					Utility.printReadingMenu();
					char printRequest;
					cin >> printRequest;
					//använder toupper så man kan skriva bådde stor eller liten bokstav
					if ((char)toupper(printRequest) == 'T')
					{
						if (MainStorage.sizeOfTypeSensor("C") > 0)
						{
							MainStorage.printByTypeSensor("C", "Temperature");
							PrintLoopisRunning = false;
						}
						else
						{
							std::cout << "you have no temperature readings" << endl;
						}
					}
					else if ((char)toupper(printRequest) == 'A')
					{
						if (MainStorage.sizeOfTypeSensor("%") > 0)
						{
							MainStorage.printByTypeSensor("%", "Air quality");
							PrintLoopisRunning = false;
						}
						else
						{
							std::cout << "you have no airquality readings" << endl;
						}
					}
					else if ((char)toupper(printRequest) == 'H')
					{
						if (MainStorage.sizeOfTypeSensor("AH") > 0)
						{
							MainStorage.printByTypeSensor("AH", "Humidity");
							PrintLoopisRunning = false;
						}
						else
						{
							std::cout << "you have no humidity readings" << endl;
						}
					}
					else if ((char)toupper(printRequest) == 'E')
					{
						MainStorage.printByTypeSensor("C", "Temperature");
						MainStorage.printByTypeSensor("%", "Air quality");
						MainStorage.printByTypeSensor("AH", "Humidity");
					}
					else if ((char)toupper(printRequest) == 'Q')
					{
						PrintLoopisRunning = false;
					}
					else
					{
						std::cout << "Wrong input" << endl;
					}
				}
				else
				{
					std::cout << "you dont have anything to print" << endl;
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
				//kollar om man har några värden att kolla på
				if (MainStorage.sizeOfTypeSensor("%") > 0 || MainStorage.sizeOfTypeSensor("C") > 0 || MainStorage.sizeOfTypeSensor("AH") > 0)
				{
					Utility.statisticMenu();
					char sensorStat;
					cin >> sensorStat;
					if ((char)toupper(sensorStat) == 'T')
					{
						if (MainStorage.sizeOfTypeSensor("C") > 0)
						{
							double SumOfTemp = MainStorage.sumOfTypeSensor("C");
							std::cout << "The sum of all Temperature readings is: " << SumOfTemp << "C" << std::endl;
							std::cout << "and the avarage is: " << SumOfTemp / MainStorage.sizeOfTypeSensor("C") << "C" << std::endl;
							MainStorage.minMaxOfTypeSensor("C");
							double VarianceTemperature = MainStorage.varianceFromTypeSensor(SumOfTemp, "C");
							std::cout << "The sample varians is " << VarianceTemperature / (MainStorage.sizeOfTypeSensor("C") - 1) << "C" << std::endl;
							std::cout << "The population varians is " << VarianceTemperature / MainStorage.sizeOfTypeSensor("C") << "C" << std::endl;
						}
						else
						{
							std::cout << "You dont have any temperature readings" << std::endl;
						}
					}
					else if ((char)toupper(sensorStat) == 'A')
					{
						if (MainStorage.sizeOfTypeSensor("%") > 0)
						{
							double SumOfAirqual = MainStorage.sumOfTypeSensor("%");
							std::cout << "The sum of all airquality readings is: " << SumOfAirqual << "%" << std::endl;
							std::cout << "and the avarage is: " << SumOfAirqual / MainStorage.sizeOfTypeSensor("%") << "%" << std::endl;
							MainStorage.minMaxOfTypeSensor("%");
							double VarianceAirqual = MainStorage.varianceFromTypeSensor(SumOfAirqual, "%");
							std::cout << "The sample varians is " << VarianceAirqual / (MainStorage.sizeOfTypeSensor("%") - 1) << "%" << std::endl;
							std::cout << "The population varians is " << VarianceAirqual / MainStorage.sizeOfTypeSensor("%") << "%" << std::endl;
						}
						else
						{
							std::cout << "You dont have any airquality readings" << endl;
						}
					}
					else if ((char)toupper(sensorStat) == 'H')
					{
						if (MainStorage.sizeOfTypeSensor("AH") > 0)
						{
							double sumOfHumidity = MainStorage.sumOfTypeSensor("AH");
							std::cout << "The sum of all humidity readings is: " << sumOfHumidity << "AH" << std::endl;
							std::cout << "and the avarage is: " << sumOfHumidity / MainStorage.sizeOfTypeSensor("AH") << "AH" << std::endl;
							MainStorage.minMaxOfTypeSensor("AH");
							double varianceHumidity = MainStorage.varianceFromTypeSensor(sumOfHumidity, "AH");
							std::cout << "The sample varians is " << varianceHumidity / (MainStorage.sizeOfTypeSensor("AH") - 1) << "AH" << std::endl;
							std::cout << "The population varians is " << varianceHumidity / MainStorage.sizeOfTypeSensor("AH") << "AH" << std::endl;
						}
						else
						{
							std::cout << "You dont have any humidity readings" << std::endl;
						}
					}
					else if ((char)toupper(sensorStat) == 'E')
					{
						if (MainStorage.sizeOfTypeSensor("C") > 0)
						{
							double SumOfTemp = MainStorage.sumOfTypeSensor("C");
							std::cout << "The sum of all Temperature readings is: " << SumOfTemp << "C" << std::endl;
							std::cout << "and the avarage is: " << SumOfTemp / MainStorage.sizeOfTypeSensor("C") << "C" << std::endl;
							MainStorage.minMaxOfTypeSensor("C");
							double VarianceTemperature = MainStorage.varianceFromTypeSensor(SumOfTemp, "C");
							std::cout << "The sample varians is " << VarianceTemperature / (MainStorage.sizeOfTypeSensor("C") - 1) << "C" << std::endl;
							std::cout << "The population varians is " << VarianceTemperature / MainStorage.sizeOfTypeSensor("C") << "C" << std::endl;
						}
						else
						{
							std::cout << "You dont have any temperature readings" << std::endl;
						}
						if (MainStorage.sizeOfTypeSensor("%") > 0)
						{
							double SumOfAirqual = MainStorage.sumOfTypeSensor("%");
							std::cout << "The sum of all airquality readings is: " << SumOfAirqual << "%" << std::endl;
							std::cout << "and the avarage is: " << SumOfAirqual / MainStorage.sizeOfTypeSensor("%") << "%" << std::endl;
							MainStorage.minMaxOfTypeSensor("%");
							double VarianceAirqual = MainStorage.varianceFromTypeSensor(SumOfAirqual, "%");
							std::cout << "The sample varians is " << VarianceAirqual / (MainStorage.sizeOfTypeSensor("%") - 1) << "%" << std::endl;
							std::cout << "The population varians is " << VarianceAirqual / MainStorage.sizeOfTypeSensor("%") << "%" << std::endl;
						}
						else
						{
							std::cout << "You dont have any airquality readings" << std::endl;
						}
						if (MainStorage.sizeOfTypeSensor("AH") > 0)
						{
							double sumOfHumidity = MainStorage.sumOfTypeSensor("AH");
							std::cout << "The sum of all humidity readings is: " << sumOfHumidity << "AH" << std::endl;
							std::cout << "and the avarage is: " << sumOfHumidity / MainStorage.sizeOfTypeSensor("AH") << "AH" << std::endl;
							MainStorage.minMaxOfTypeSensor("AH");
							double varianceHumidity = MainStorage.varianceFromTypeSensor(sumOfHumidity, "AH");
							std::cout << "The sample varians is " << varianceHumidity / (MainStorage.sizeOfTypeSensor("AH") - 1) << "AH" << std::endl;
							std::cout << "The population varians is " << varianceHumidity / MainStorage.sizeOfTypeSensor("AH") << "AH" << std::endl;
						}
						else
						{
							std::cout << "You dont have any humidity readings" << std::endl;
						}
					}
					else if ((char)toupper(sensorStat) == 'Q')
					{
						StatisticsLoopRunning = false;
					}
					else
					{
						std::cout << "Wrong input" << std::endl;
					}
				}
				else
				{
					std::cout << "you dont have anything to check" << std::endl;
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
				//kollar om man har några värden att kolla på
				if (MainStorage.sizeOfTypeSensor("%") > 0 || MainStorage.sizeOfTypeSensor("C") > 0 || MainStorage.sizeOfTypeSensor("AH") > 0)
				{
					Utility.visualRepMenu();
					char visualisationRequest;
					cin >> visualisationRequest;
					//använder toupper så man kan skriva bådde stor eller liten bokstav
					if ((char)toupper(visualisationRequest) == 'T')
					{
						if (MainStorage.sizeOfTypeSensor("C") > 0)
						{
							//detta går igenom Measurementlistan och vissar '*' i olicka mängder beroende på reading valuen
							MainStorage.VisulisationOfTypeSensor("C");
							Utility.ENTER();
							VisualisationLoopRunning = false;
						}
						else
						{
							std::cout << "You dont have any temperatur readings" << std::endl;
						}
					}
					else if ((char)toupper(visualisationRequest) == 'A')
					{
						if (MainStorage.sizeOfTypeSensor("%") > 0)
						{
							MainStorage.VisulisationOfTypeSensor("%");
							Utility.ENTER();
							VisualisationLoopRunning = false;
						}
						else
						{
							std::cout << "You dont have any airquality readings" << std::endl;
						}
					}
					else if ((char)toupper(visualisationRequest) == 'H')
					{
						if (MainStorage.sizeOfTypeSensor("AH") > 0)
						{
							MainStorage.VisulisationOfTypeSensor("AH");
							Utility.ENTER();
							VisualisationLoopRunning = false;
						}
						else
						{
							std::cout << "You dont have any humidity readings" << std::endl;
						}
					}
					else if ((char)toupper(visualisationRequest) == 'E')
					{
						MainStorage.VisulisationOfTypeSensor("C");
						MainStorage.VisulisationOfTypeSensor("%");
						MainStorage.VisulisationOfTypeSensor("AH");
					}
					else if ((char)toupper(visualisationRequest) == 'Q')
					{
						VisualisationLoopRunning = false;
					}
					else
					{
						std::cout << "Wrong input" << std::endl;
					}
				}
				else
				{
					std::cout << "you dont have anything to check" << std::endl;
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
				//kollar om man har några värden att söka efter
				if (MainStorage.sizeOfTypeSensor("%") > 0 || MainStorage.sizeOfTypeSensor("C") > 0 || MainStorage.sizeOfTypeSensor("AH") > 0)
				{
					Utility.searchMenu();
					char searchRequest;
					cin >> searchRequest;
					if ((char)toupper(searchRequest) == 'N')
					{
						bool SearchNameRunning = true;
						while (SearchNameRunning == true)
						{
							std::cout << "what name does the sensor have: " << std::endl;
							std::cout << "If you dont remember the name of sensor press [P] to print out list" << std::endl;
							char SearchName;
							cin >> SearchName;
							if ((char)toupper(SearchName) == 'P')
							{
								MainStorage.printByTypeSensor("C", "Temperature");
								MainStorage.printByTypeSensor("%", "Air quality");
								MainStorage.printByTypeSensor("AH", "Humidity");
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
							std::cout << "What TimeStamp does the sensor have: " << std::endl;
							std::cout << "This is the template for the search (00:00:00)" << std::endl;
							std::cout << "If you dont remember the Time of the reading press [P] to print out list" << std::endl;
							char SearchTimeStamp;
							cin >> SearchTimeStamp;
							if ((char)toupper(SearchTimeStamp) == 'P')
							{
								MainStorage.printByTypeSensor("C", "Temperature");
								MainStorage.printByTypeSensor("%", "Air quality");
								MainStorage.printByTypeSensor("AH", "Humidity");
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
						std::cout << "Wrong input" << std::endl;
					}
				}
				else
				{
					std::cout << "You dont have any readings to search for" << std::endl;
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
				Utility.editMenu();
				char thresholdChoice;
				std::cin >> thresholdChoice;
				if ((char)toupper(thresholdChoice) == 'Y')
				{
					std::cout << "what is the name of the threshold you want to change: " << std::endl;
					std::string thresholdName;
					std::cin >> thresholdName;
					Controller.editThresHold(thresholdName);
					editLoopRunning = false;
				}
				else if ((char)toupper(thresholdChoice) == 'N')
				{
					editLoopRunning = false;
				}
				else
				{
					std::cout << "Wrong input" << std::endl;
				}
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
					Controller.showAlarms();
					showAlarmLoopRunning = false;
				}
				else if ((char)toupper(showAlarmChoice) == 'N')
				{
					showAlarmLoopRunning = false;
				}
				else
				{
					std::cout << "Wrong input" << std::endl;
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
					Controller.showSensorConfig();
					sensorConfigMenu = false;
				}
				else if ((char)toupper(sensorConfigChoice) == 'N')
				{
					sensorConfigMenu = false;
				}
				else
				{
					std::cout << "Wrong input" << std::endl;
				}
			}
			Utility.ENTER();
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
			std::cout << "Wrong input choices are between [1]-[9]" << std::endl;
		}
		break;
		}

	}
}
