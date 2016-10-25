#include "Sensor.h"

Sensor::Sensor(int pin) : InterInterface(pin)
{
   pinMode(_pin, INPUT);
}


int Sensor::pin()
{
    return _pin;
}

bool Sensor::trig()
{
  if(_downPulse >0)
      return true;
   return false;
}
void Sensor::reset()
{
    if(digitalRead(_pin)==1)
    {

       _upPulse = 0;
       _downPulse = 0;
   }
}
