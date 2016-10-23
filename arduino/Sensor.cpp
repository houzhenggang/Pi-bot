#include "Arduino.h"
#include "Sensor.h"

Sensor::Sensor(int pin)  : InterInterface(pin)
{
   pinMode(_pin, INPUT);
}

void Sensor::pullup() 
{
   pinMode(_pin, INPUT_PULLUP);
    
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


void Sensor::print()
{
    Serial.print("| Sensor pin:");
    Serial.print(_pin);
    Serial.print(" up pulses:");
    Serial.print(InterInterface::_upPulse);
    Serial.print(" down pulses:");
    Serial.print(InterInterface::_downPulse);
    if(trig()) 
       Serial.print(" Sensor on");
    else
       Serial.print(" Sensor off");
    Serial.print(" |");
}

