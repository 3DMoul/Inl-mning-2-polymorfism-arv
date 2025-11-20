polymorfism-arv
line 11-16
deklarerar jag alla klasser jag använder i programet samt så lässer jag in all info som finns i text filerna  ThresHold.txt, SensorConfig.txt, SensorReading2.txt


Line 17-21
så checkar jag om något larm(threshold) har blivit utlöst först av allt i varje rotation av whileloopen och lägger in det nummeret in i printMenu() functionen

void Utility::printMenu(int alarmcount)
{
    system("CLS");
    std::cout << "The amount of alarms active is: " << alarmcount << std::endl;
    cout << "---------------------------------" << endl;
    cout << "[1] Adding sensor readings" << endl;
    cout << "[2] Read out readings" << endl;
    cout << "[3] Statistics of readings" << endl;
    cout << "[4] Visual representation of data" << endl;
    cout << "[5] Search for readings" << endl;
    cout << "[6] Edit threshold rules" << endl;
    cout << "[7] Show alarm" << endl;
    cout << "[8] Show sensor configs" << endl;
    cout << "[9] Exit program" << endl;
    cout << "---------------------------------" << endl;
}

Line 22-24

deklarerar jag en string som används till menyval Choice i functionen NumberChoice(); samt börjar jag switchen

Line 26-69
case 1 
deklarerar jag en while loop så man kan välja vilken sensortype värde man vill simulera valet går in i getMeasurementReading() och beroende på vilken typ man valde så använder den den subclassen för att få rätt reading.
void Storage::getMeasurementReading(char type)
{
    SensorType sensorType = static_cast<SensorType>(type);
    //här får man rätt sensortyp med hjälp av enum
    auto sensorPrompt = makePrompt(sensorType);
    if (!sensorPrompt)
    {
        std::cerr << "Invalid sensor type!\n";
        return;
    }
    string strPromt = sensorPrompt->SimulatingSensorprompt();
    int amountOfSensors = Utility::numberInputSafeGaurd(strPromt);//amout of sensors
    std::cout << "Pick your interval values MinValue: " << std::endl;
    double minValue = 0;
    std::cin >> minValue;
    std::cout << "Pick your interval values MaxValue: " << std::endl;
    double maxValue = 0;
    std::cin >> maxValue;
    for (int i = 0; i < amountOfSensors; i++)
    {
        system("CLS");
        std::cout << "What is the name of your sensor: " << std::endl;
        std::string newSensorName;
        std::cin >> newSensorName;
        for (auto& currentName : MeasurmentsList)
        {
            while (currentName.SensorName == newSensorName)
            {
                std::cout << "You cant have the same sensor name as another sensor" << std::endl;
                std::cin >> newSensorName;
            }
        }
        SystemController::addThresholdForSensor(newSensorName);
        auto newSensor = makeSensor(sensorType, newSensorName, minValue, maxValue);
        SystemController::saveToFile(*newSensor);
        Measurement newMeasurement;
        newMeasurement.GetReading(*newSensor);
        SystemController::addSensor(std::move(newSensor));
        WriteFile(newMeasurement);
        MeasurmentsList.push_back(newMeasurement);
    }
}
functionen sparar även alla värderna till respective txt fil

Line 70-142
case 2
gör en while loop så man kan titta på alla värderna för sig eller alla samtidigt har även en if else statem som göra att om du inte har några värden att printa säger den att man inte har dem värdena

//gör detta så jag inte behöver skriva en specific function för varje sensortyp
void Storage::printByTypeSensor(const std::string& unitOfMeasurement, const std::string& type)
{
    std::cout << type << endl;
    for (auto& CurrentSensor : MeasurmentsList)
    {
        if (CurrentSensor.UnitOfMeasurment == unitOfMeasurement)
        {
            std::cout << CurrentSensor.SensorName << "\n" << CurrentSensor.SensorMeasurement << " " << CurrentSensor.UnitOfMeasurment << ", " << CurrentSensor.TimeStamp << endl;
        }
    }
}

Line 143-267
case 3
gör den while loop så man kan välja vardera sensortype att få statistik från eller om man vill ha från alla. om man inte har några värden av en typ av sensor så kommer den säga att man inte har såna värden men fortfarande printa ut statestic från dem andra sensor typerna

Line 268-345
case 4
gör den while loop så man kan välja vilken sensor typ man vill  få visualisering från. man kan även välja att visualisera från alla typerna

Line 346-421
case 5
är för att söka på specific sensornamn eller timestamp
gör while loop så man kan välja namn eller tid att söka på den kollar om man har värden i listan om man inte har det säger den att man inte har något att söka på
om man har något att söka på så går den in i en while loop som runnar tills SearchTimeStamp() eller SearchForName() (beroende på vad man valde) ger bool SearchTimeRunning en false value  

bool Storage::SearchForTimeStamp(string TimeStamp)
{
    
    for (int i = 0; i < size(MeasurmentsList); i++)
    {
        if (MeasurmentsList[i].TimeStamp == TimeStamp)
        {
            cout << MeasurmentsList[i].SensorName << endl;
            cout << MeasurmentsList[i].Measurement << MeasurmentsList[i].UnitOfMeasurment << endl;
            cout << MeasurmentsList[i].TimeStamp << endl;
            return false;
        }
    }
    cout << "Did not find that TimeStamp in the list try with another TimeStamp:" << endl;
    return true;

}

line 422-449
case 6
gör en while loop sen kan man välja om man vill edita threshold limit på en specific threshold

void SystemController::editThresHold(const std::string& thresholdName)
{
    for (auto& currentThreshold : thresholdList)
    {
        if (currentThreshold.SensorNamn == thresholdName)
        {
            std::cout << "The current threshold for " << currentThreshold.SensorNamn << "is " << currentThreshold.Limit << std::endl;
            std::cout << "´What do you want to change the threshold to: ";
            std::cin >> currentThreshold.Limit;
        }
    }
}

line 450-475
case 7
gör en while loop sen kan man välja om man vill se alla alarm om man klickar ja så kommer den printa ut från threshold listan så kommer den vissa vad för namn dem har och vad thresholden(limit) är samt om den har löst ut eller inte den kommer vara false om den har löst ut och då kommer den printa ut 0 istället för 1.

void SystemController::showAlerts() const
{
    for (auto& currentThresHold : thresholdList)
    {
        std::cout << "------------------------------" << std::endl;
        std::cout << currentThresHold.SensorNamn << std::endl;
        std::cout << currentThresHold.Limit << std::endl;
        std::cout << currentThresHold.Over << std::endl;
        std::cout << "------------------------------" << std::endl;

    }
}

line 476-501
case 8
gör en while loop sen kan man välja om man vill se settings för varje sensor  
void SystemController::showSensorConfig()
{
    std::cout << "Temperature sensors: " << std::endl;
    for (auto& CurrentSensor : sensors)
    {
        if (CurrentSensor->GetUnitOfMeasurment() == "C")
        {

            std::cout << "Sensor name: " << CurrentSensor->name() << std::endl;
            std::cout << "Maxvalue is: " << CurrentSensor->maxValue() << std::endl;
            std::cout << "Minvalue is: " << CurrentSensor->minValue() << std::endl;

        }
    }
    std::cout << "Airquality sensors: " << std::endl;
    for (auto& CurrentSensor : sensors)
    {
        if (CurrentSensor->GetUnitOfMeasurment() == "%")
        {
            std::cout << "Sensor name: " << CurrentSensor->name() << std::endl;
            std::cout << "Maxvalue is: " << CurrentSensor->maxValue() << std::endl;
            std::cout << "Minvalue is: " << CurrentSensor->minValue() << std::endl;
        }
    }
    std::cout << "Humidity sensors: " << std::endl;
    for (auto& CurrentSensor : sensors)
    {
        if (CurrentSensor->GetUnitOfMeasurment() == "AH")
        {
            std::cout << "Sensor name: " << CurrentSensor->name() << std::endl;
            std::cout << "Maxvalue is: " << CurrentSensor->maxValue() << std::endl;
            std::cout << "Minvalue is: " << CurrentSensor->minValue() << std::endl;
        }
    }


}

line 502-507
case 9
här avslutas programet

line 508-512
default
det här kommer upp om man skriver in ett nummer som inte finns med i swicthen
