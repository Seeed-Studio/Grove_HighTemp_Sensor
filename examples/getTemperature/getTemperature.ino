// demo of Grove - High Temperature Sensor
// Thmc -> A5
// RoomTemp -> A4

#include "Streaming.h"
#include "High_Temp.h"


HighTemp ht(A4, A5);


void setup()
{
    Serial.begin(115200);
    cout << "hello world" << endl;
    
    cout << "Room Temperature = " << ht.getRoomTmp() << endl;
}

void loop()
{
    cout << ht.getThmc() << endl;
   //  cout << ht.K_VtoT(7) << endl;
    delay(100);
}
