/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 01-11-2016
* @License: GPL v3
*     This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



#ifndef INTERINTERFACE_cpp
#define INTERINTERFACE_cpp


#include "InterInterface.h"


/*
*Constructor method
*
* pin- the pin on the system to listen for interupts on
*
* The only information we get back from the wiringPiISR function is the name
* of the function called. This function cannot be a memmber function it has to
* be a static function.
*
* for every pin and event on that pin  a new static function must be declared
* in  order the system to know what event has occured.
*
* It is known before hand how many pins there are 0-16 and the events that can
* occur on them rising and falling.
*
* for this reason there are 17x2 static function declared
*
*
*
*/
InterInterface::InterInterface(int pin) {
  _pin = pin;
  _downPulse = 0;
  _upPulse = 0;
  registerListener(_pin);
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
ostream& operator<<(ostream& stream,InterInterface &ob)
{
  Json::Value root;
  root["pin"] = ob._pin;
  root["up-pulses"] = ob._upPulse;
  root["down-pulses"]= ob._downPulse;
  stream << root;
  return stream;
}
/*
*
*Assume that that the input stream is well formatted json with white spsaces between all data and formatting
*
*/
istream& operator>>(istream& stream,InterInterface  &ob)
{
  Json::Value root;
  stream >> root;
  ob._pin = root.get("pin","0").asInt();
  ob._upPulse = root.get("up-pulses","0").asInt();
  ob._downPulse = root.get("down-pulses","0").asInt();
  return stream;
}
/*
*
* Callback method of only allows the use of static methods thus the only information that can be returned
* is the function called back.
* In order to to intergrate this into a object orientated scheme each of the possible pins and actions will have
* its own method. This method then calls a list of member methods that have been registered for this type.
*
* This is not an ideal callback function but is necessery in order to keep the object orientated scheeme.
*/

void InterInterface::registerListener(int pin) {
  /*
  need to use bind here: http://stackoverflow.com/questions/400257/how-can-i-pass-a-class-member-function-as-a-callback
  boost::bind will let you take a function, and a parameter to that function, and make a new function where that parameter is 'locked' in place. So if I have a function that adds two integers, I can use boost::bind to make a new function where one of the parameters is locked to say 5. This new function will only take one integer parameter, and will always add 5 specifically to it. Using this technique, you can 'lock in' the hidden 'this' parameter to be a particular class instance, and generate a new function that only takes one parameter, just like you want (note that the hidden parameter is always the first parameter, and the normal parameters come in order after it). Look at the boost::bind docs for examples, they even specifically discuss using it for member functions. Technically there is a standard function called std::bind1st that you could use as well, but boost::bind is more general.

  Of course, there's just one more catch. boost::bind will make a nice boost::function for you, but this is still technically not a raw function pointer like Init probably wants. Thankfully, boost provides a way to convert boost::function's to raw pointers, as documented on StackOverflow here. How it implements this is beyond the scope of this answer, though it's interesting too.

  Don't worry if this seems ludicrously hard -- your question intersects several of C++'s darker corners, and boost::bind is incredibly useful once you learn it.

  wireingPIISR is the interupt method in wiringpi Library. It will call the specified function each time the pin goes high ( rising) or low (falling)

  */
  std::function<void()> memberFunctionR (std::bind(&InterInterface::trigLowHigh,this));
  std::function<void()> memberFunctionF (std::bind(&InterInterface::trigHighLow,this));
  switch(pin) {
    case 0:
    //add this function to the list
    pin0RisingListeners.push_back(memberFunctionR);
    pin0FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin0Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin0Falling ) ;
    case 1:
    //add this function to the list
    pin1RisingListeners.push_back(memberFunctionR);
    pin1FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin1Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin1Falling ) ;
    break;
    case 2:
    //add this function to the list
    pin2RisingListeners.push_back(memberFunctionR);
    pin2FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin2Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin2Falling ) ;
    break;
    case 3:
    //add this function to the list
    pin3RisingListeners.push_back(memberFunctionR);
    pin3FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin3Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin3Falling ) ;
    break;
    case 4:
    //add this function to the list
    pin4RisingListeners.push_back(memberFunctionR);
    pin4FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin4Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin4Falling ) ;
    break;
    case 5:
    //add this function to the list
    pin5RisingListeners.push_back(memberFunctionR);
    pin5FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin5Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin5Falling ) ;
    break;
    case 6:
    //add this function to the list
    pin6RisingListeners.push_back(memberFunctionR);
    pin6FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin6Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin6Falling ) ;
    break;
    case 7:
    //add this function to the list
    pin7RisingListeners.push_back(memberFunctionR);
    pin7FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin7Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin7Falling ) ;
    break;
    case 8:
    //add this function to the list
    pin8RisingListeners.push_back(memberFunctionR);
    pin8FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin8Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin8Falling ) ;
    break;
    case 9:
    //add this function to the list
    pin9RisingListeners.push_back(memberFunctionR);
    pin9FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin9Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin9Falling ) ;
    break;
    case 10:
    //add this function to the list
    pin10RisingListeners.push_back(memberFunctionR);
    pin10FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin10Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin10Falling ) ;
    break;
    case 11:
    //add this function to the list
    pin11RisingListeners.push_back(memberFunctionR);
    pin11FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin11Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin11Falling ) ;
    break;
    case 12:
    //add this function to the list
    pin12RisingListeners.push_back(memberFunctionR);
    pin12FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin12Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin12Falling ) ;
    break;
    case 13:
    //add this function to the list
    pin13RisingListeners.push_back(memberFunctionR);
    pin13FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin13Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin13Falling ) ;
    break;
    case 14:
    //add this function to the list
    pin14RisingListeners.push_back(memberFunctionR);
    pin14FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin14Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin14Falling ) ;
    break;
    case 15:
    //add this function to the list
    pin15RisingListeners.push_back(memberFunctionR);
    pin15FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin15Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin15Falling ) ;
    break;
    case 16:
    //add this function to the list
    pin16RisingListeners.push_back(memberFunctionR);
    pin16FallingListeners.push_back(memberFunctionF);
    //setup the Callback on the wiringPiISR
    wiringPiISR (_pin, INT_EDGE_RISING, *pin16Rising ) ;
    wiringPiISR (_pin, INT_EDGE_FALLING, *pin16Falling ) ;
    break;
  }
}
//There are 16 pins defined in wiringPi thus there are 16 pins that can be  listened on
std::list<std::function<void()>> InterInterface::pin0RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin0FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin1RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin1FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin2RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin2FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin3RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin3FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin4RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin4FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin5RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin5FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin6RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin6FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin7RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin7FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin8RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin8FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin9RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin9FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin10RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin10FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin11RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin11FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin12RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin12FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin13RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin13FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin14RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin14FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin15RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin15FallingListeners ={};
std::list<std::function<void()>> InterInterface::pin16RisingListeners ={};
std::list<std::function<void()>> InterInterface::pin16FallingListeners ={};

/*
*A rising voltage has been detected on pin 0 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin0Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin0RisingListeners.begin(); it != pin0RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 0 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin0Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin0FallingListeners.begin(); it != pin0FallingListeners.end(); ++it)
  (*it)();
}



/*
*A rising voltage has been detected on pin 1 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin1Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin1RisingListeners.begin(); it != pin1RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 1 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin1Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin1FallingListeners.begin(); it != pin1FallingListeners.end(); ++it)
  (*it)();
}


/*
*A rising voltage has been detected on pin 2 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin2Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin2RisingListeners.begin(); it != pin2RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 2 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin2Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin2FallingListeners.begin(); it != pin2FallingListeners.end(); ++it)
  (*it)();
}


/*
*A rising voltage has been detected on pin 3 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin3Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin3RisingListeners.begin(); it != pin3RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 3 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin3Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin3FallingListeners.begin(); it != pin3FallingListeners.end(); ++it)
  (*it)();
}


/*
*A rising voltage has been detected on pin 4 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin4Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin4RisingListeners.begin(); it != pin4RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 4 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin4Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin4FallingListeners.begin(); it != pin4FallingListeners.end(); ++it)
  (*it)();
}

/*
*A rising voltage has been detected on pin 5 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin5Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin5RisingListeners.begin(); it != pin5RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 5 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin5Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin5FallingListeners.begin(); it != pin5FallingListeners.end(); ++it)
  (*it)();
}

/*
*A rising voltage has been detected on pin 6 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin6Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin6RisingListeners.begin(); it != pin6RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 6 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin6Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin6FallingListeners.begin(); it != pin6FallingListeners.end(); ++it)
  (*it)();
}

/*
*A rising voltage has been detected on pin 6 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin7Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin7RisingListeners.begin(); it != pin7RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 7 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin7Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin7FallingListeners.begin(); it != pin7FallingListeners.end(); ++it)
  (*it)();
}

/*
*A rising voltage has been detected on pin 8 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin8Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin8RisingListeners.begin(); it != pin8RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 8 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin8Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin8FallingListeners.begin(); it != pin8FallingListeners.end(); ++it)
  (*it)();
}
/*
*A rising voltage has been detected on pin 9 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin9Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin9RisingListeners.begin(); it != pin9RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 9 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin9Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin9FallingListeners.begin(); it != pin9FallingListeners.end(); ++it)
  (*it)();
}

/*
*A rising voltage has been detected on pin 10 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin10Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin10RisingListeners.begin(); it != pin10RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 10 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin10Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin10FallingListeners.begin(); it != pin10FallingListeners.end(); ++it)
  (*it)();
}

/*
*A rising voltage has been detected on pin 11 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin11Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin11RisingListeners.begin(); it != pin11RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 11 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin11Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin11FallingListeners.begin(); it != pin11FallingListeners.end(); ++it)
  (*it)();
}

/*
*A rising voltage has been detected on pin 12 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin12Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin12RisingListeners.begin(); it != pin12RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 12 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin12Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin12FallingListeners.begin(); it != pin12FallingListeners.end(); ++it)
  (*it)();
}

/*
*A rising voltage has been detected on pin 13 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin13Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin13RisingListeners.begin(); it != pin13RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 13 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin13Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin13FallingListeners.begin(); it != pin13FallingListeners.end(); ++it)
  (*it)();
}

/*
*A rising voltage has been detected on pin 14 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin14Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin14RisingListeners.begin(); it != pin14RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 14 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin14Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin14FallingListeners.begin(); it != pin14FallingListeners.end(); ++it)
  (*it)();
}

#endif

/*
*A rising voltage has been detected on pin 15 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin15Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin15RisingListeners.begin(); it != pin15RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 15 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin15Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin15FallingListeners.begin(); it != pin15FallingListeners.end(); ++it)
  (*it)();
}

/*
*A rising voltage has been detected on pin 16 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin16Rising()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin16RisingListeners.begin(); it != pin16RisingListeners.end(); ++it)
  (*it)();
}

/*
*A falling voltage has been detected on pin 16 of the gpio - Call all memeber functions that are
* registered as listeners
*/
void InterInterface::pin16Falling()
{
  //Call each function that has registered to listen
  for (std::list<std::function<void()>>::iterator it=pin16FallingListeners.begin(); it != pin16FallingListeners.end(); ++it)
  (*it)();
}
