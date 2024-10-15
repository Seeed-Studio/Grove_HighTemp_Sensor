/*
    High_Temp.h

    2014 Copyright (c) Seeed Technology Inc.  All right reserved.

    Loovee
    2013-4-14
*/
#ifndef __HIGH_TEMP_H__
#define __HIGH_TEMP_H__

class HighTemp {

  public:

    HighTemp(int _pinTmp, int _pinThmc);

    float getRoomTmp();                      //
    float getThmc();

    void begin();


  private:

    int pinRoomTmp;                         // pin of temperature sensor
    int pinThmc;                            // pin of thermocouple

    float tempRoom;                         // room temperature
    float tempThmc;                         // thermocouple temperature

  public:

    int getAnalog(int pin);
    float K_VtoT(float mV);                 // K type thermocouple, mv->oC
    float getThmcVol();                     // get voltage of thmc in mV
};


#endif