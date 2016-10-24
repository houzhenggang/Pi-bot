#ifndef INTERINTERFACE_cpp
#define INTERINTERFACE_cpp

#include "InterInterface.h"



void InterInterface::pullup()
{
   pinMode(_pin, INPUT_PULLUP);

}


int InterInterface::pin()
{
    return _pin;
}

bool InterInterface::trig()
{
  if(_upPulse >0)
      return true;
   return false;
}
void InterInterface::reset()
{
    _upPulse = 0;
    _downPulse = 0;
}



//InterInterface * InterInterface::_regB = new InterInterface[8];

//InterInterface::InterInterface() {}
InterInterface::InterInterface(int pin) {
    _pin = pin;
    wiringPiISR (_pin, INT_EDGE_RISING,  InterInterface::trigLowHigh) ;
    wiringPiISR (_pin, INT_EDGE_FALLING,  InterInterface::trigHighLow) ;
}


int InterInterface::getDownPulse() {
   return InterInterface::_downPulse;
}
int InterInterface::getUpPulse() {
   return InterInterface::_upPulse;
}
void InterInterface::trigHighLow() {
  _downPulse++;
}
void InterInterface::trigLowHigh() {
  _upPulse++;
}


/*
*
*Print out the state of the object as json string
*
*/
ostream& operator<<(ostream& stream,Wheel ob)
{
  stream<<"{ pin : "<<ob._pin
    <<" , upPulse : "<<ob._upPulse
    <<" , downPulse : "<<ob._downPulse
    <<" } ";
  return stream;
}
/*
*
*Assume that that the input stream is well formatted json with white spsaces between all data and formatting
*
*/
istream& operator>>(istream& stream,Wheel  ob)
{
  char c;
  string txt;
  stream.get(c); //first character is a '{'
  stream >> txt; // next stream should be pin
  stream.get(c); //next character is ':'
  stream >> ob._pin; //input data for pin
  stream.get(c); //next character is a ','
  stream >> txt; // next stream should be upPulse
  stream.get(c); //next character is ':'
  stream >>ob._upPulse;
  stream.get(c); //next character is a ','
  stream >> txt; // next stream should be downPulse
  stream.get(c); //next character is ':'
  stream >>ob._downPulse;
  stream.get(c); //first character is a '}'
  return stream;
}


#endif
