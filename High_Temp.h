/*
  High_Temp.h

  2014 Copyright (c) Seeed Technology Inc.  All right reserved.
  
  Loovee
  2013-4-14

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef __HIGH_TEMP_H__
#define __HIGH_TEMP_H__

class HighTemp{

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