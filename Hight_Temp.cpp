/*
  High_Temp.cpp

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

#include <Arduino.h>
#include "High_Temp.h"


const float VOL_OFFSET = 350;                       // offset voltage, mv
const float AMP_AV     = 54.16;                     // Av of amplifier


const float Var_VtoT_K[3][10] =
{
    {0, 2.5173462e1, -1.1662878, -1.0833638, -8.9773540/1e1, -3.7342377/1e1,
    -8.6632643/1e2, -1.0450598/1e2, -5.1920577/1e4},
    {0, 2.508355e1, 7.860106/1e2, -2.503131/1e1, 8.315270/1e2,
    -1.228034/1e2, 9.804036/1e4, -4.413030/1e5, 1.057734/1e6, -1.052755/1e8},
    {-1.318058e2, 4.830222e1, -1.646031, 5.464731/1e2, -9.650715/1e4,
    8.802193/1e6, -3.110810/1e8}
};


HighTemp::HighTemp(int _pinTmp, int _pinThmc)
{

    pinRoomTmp = _pinTmp;
    pinThmc    = _pinThmc;
    

}

void HighTemp::begin()
{

    tempRoom   = getRoomTmp();
    
    Serial.print("tempRoom = ");
    Serial.println(tempRoom);
    
    delay(10);
    Serial.print("pinRoomTmp = ");Serial.println(pinRoomTmp);
    
    delay(10);
    Serial.print("pinThmc = ");Serial.println(pinThmc);
}

float HighTemp::getThmc()
{
    float vol  = getThmcVol();

    tempThmc = K_VtoT(vol) + tempRoom;
    
    return tempThmc;
}


int HighTemp::getAnalog(int pin)
{
    long sum = 0;

    for(int i=0; i<32; i++)
    {
        sum += analogRead(pin);
    }

    return ((sum>>5));                                              // 3.3V supply
}


float HighTemp::getRoomTmp()
{
    int a = getAnalog(pinRoomTmp)*50/33;                                // 3.3V supply
    float resistance=(float)(1023-a)*10000/a;                           // get the resistance of the sensor;
    float temperature=1/(log(resistance/10000)/3975+1/298.15)-273.15;   // convert to temperature via datasheet ;
    
    
    Serial.print("a = ");Serial.println(a);
    Serial.print("resistance = ");Serial.println(resistance);
   // Serial.print("temperature = ");Serial.println(temperature);
    
    tempRoom = temperature;
    return temperature;
}


float HighTemp::getThmcVol()                                             // get voltage of thmc in mV
{
    float vout = (float)getAnalog(pinThmc)/1023.0*5.0*1000;
    float vin  = (vout - VOL_OFFSET)/AMP_AV;
    return (vin);    
}


float HighTemp::K_VtoT(float mV)
{
    int i = 0;
    float value = 0;

    if(mV >= -6.478 && mV < 0)
    {
        value = Var_VtoT_K[0][8];

        for(i = 8; i >0; i--)
        value = mV * value + Var_VtoT_K[0][i-1];
    }
    else if(mV >= 0 && mV < 20.644)
    {
        value = Var_VtoT_K[1][9];

        for(i = 9; i >0; i--)
        {
            value = mV * value + Var_VtoT_K[1][i-1];
        }
    }
    else if(mV >= 20.644 && mV <= 54.900)
    {
        value = Var_VtoT_K[2][6];

        for(i = 6; i >0; i--)
        value = mV * value + Var_VtoT_K[2][i-1];
    }

    return value;
}