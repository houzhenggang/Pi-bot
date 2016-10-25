#ifndef INTERINTERFACE_cpp
#define INTERINTERFACE_cpp


#include "InterInterface.h"


/*
*Constructor method
*
* pin- the pin on the system to listen for interupts on
*
*/
InterInterface::InterInterface(int pin) {
  _pin = pin;
  /*
  need to use bind here: http://stackoverflow.com/questions/400257/how-can-i-pass-a-class-member-function-as-a-callback
  boost::bind will let you take a function, and a parameter to that function, and make a new function where that parameter is 'locked' in place. So if I have a function that adds two integers, I can use boost::bind to make a new function where one of the parameters is locked to say 5. This new function will only take one integer parameter, and will always add 5 specifically to it. Using this technique, you can 'lock in' the hidden 'this' parameter to be a particular class instance, and generate a new function that only takes one parameter, just like you want (note that the hidden parameter is always the first parameter, and the normal parameters come in order after it). Look at the boost::bind docs for examples, they even specifically discuss using it for member functions. Technically there is a standard function called std::bind1st that you could use as well, but boost::bind is more general.

Of course, there's just one more catch. boost::bind will make a nice boost::function for you, but this is still technically not a raw function pointer like Init probably wants. Thankfully, boost provides a way to convert boost::function's to raw pointers, as documented on StackOverflow here. How it implements this is beyond the scope of this answer, though it's interesting too.

Don't worry if this seems ludicrously hard -- your question intersects several of C++'s darker corners, and boost::bind is incredibly useful once you learn it.

wireingPIISR is the interupt method in wiringpi Library. It will call the specified function each time the pin goes high ( rising) or low (falling)

  */
  auto func1 = std::bind(&InterInterface::trigLowHigh,this);
  auto func2 = std::bind(&InterInterface::trigLowHigh,this);

  std::function<void()> test1(func1);

  //wiringPiISR (_pin, INT_EDGE_RISING, *c_func1 ) ;
  //wiringPiISR (_pin, INT_EDGE_FALLING, *c_func2) ;
}

/*
*Depending on the configration of the system we may need to use a pull up resistor on the pin
*/
void InterInterface::pullup()
{
  pullUpDnControl(_pin, PUD_UP);

}

/*
*Return the pin that the InterInterface is attached to
*/
int InterInterface::pin()
{
  return _pin;
}

/*
*Returns true if there has been a trigger
*/
bool InterInterface::trig()
{
  if(_upPulse >0 || _downPulse>0)
    return true;
  return false;
}
/*
*Returns the system to its initial state after a trigger
*/
void InterInterface::reset()
{
  _upPulse = 0;
  _downPulse = 0;
}

/*
*Returns the number of time that the pin has gone from high to low. The time is the time since reset has been called
*/

int InterInterface::getDownPulse() {
  return InterInterface::_downPulse;
}
/*
*Returns the number of time that the pin has gone from low to high. The time is the time since reset has been called
*/
int InterInterface::getUpPulse() {
  return InterInterface::_upPulse;
}
/*
*function called when pin goes from high to low voltage
*/
void InterInterface::trigHighLow() {
  _downPulse++;
}
/*
*function called when pin goes from low to high voltage
*/
void InterInterface::trigLowHigh() {
  _upPulse++;
}


/*
*
*Print out the state of the object as json string
*
*/
ostream& operator<<(ostream& stream,InterInterface ob)
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
istream& operator>>(istream& stream,InterInterface  ob)
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
