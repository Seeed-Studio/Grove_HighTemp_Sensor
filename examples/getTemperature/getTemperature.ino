// demo of Grove - High Temperature Sensor
// Thmc -> A5
// RoomTemp -> A4

#ifdef USE_TINYUSB
#include <Adafruit_TinyUSB.h>
#endif

#include "High_Temp.h"

HighTemp ht(A0, A1);

void setup() {
    Serial.begin(115200);
    Serial.println("grove - hight temperature sensor test demo");
    ht.begin();
}

void loop() {
    Serial.println(ht.getThmc());
    delay(100);
}
