// demo of Grove - High Temperature Sensor
// Thmc -> A5
// RoomTemp -> A4


#include "High_Temp.h"

HighTemp ht(A4, A5);

void setup()
{
    Serial.begin(115200);
    Serial.println("grove - hight temperature sensor test demo");
    ht.begin();
}

void loop()
{
    Serial.println(ht.getThmc());
    delay(100);
}