Objektorienterad-programmering
Line 10-13
deklarerar jag alla klasser jag använder i programet

Line 14 

använder jag ReadFile(); functionen för att läsa in text filen.

Line 15 
deklarerar jag "main menu" loopen så att programmet inte slutar efter ett menyval

Line 19-26
skrivs menyn ut

Line 27-29

deklarerar jag en string som används till menyval Choice i functionen NumberChoice(); samt börjar jag switchen

Line 31-109
case 1 
deklarerar jag en while loop så man kan välja vad för sensor värde man vill simulera jag gör även att man kan skriva 
skriva namnet till sensorn

Line 111-189
case 2
gör en while loop så man kan titta på alla värderna för sig eller alla samtidigt har även en if else statem som göra att om du inte har några värden att printa säger den att man inte har dem värdena

Line 190-298
case 3
gör den while loop så man kan välja vardera värde att få statistik från eller om man vill ha båda gör även att om man inte har båda värdena men försöker få ut statestic för båda så säger den att man inte har några av dem värdena att printa statestik till

Line 299-379
case 4
gör den while loop så man kan välja vardera värde att få visualisering  eller båda den säger även till om man inte har en visst sensor värde

Line 380-453
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
