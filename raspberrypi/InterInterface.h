/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 09-11-2016
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

#ifndef INTERINTERFACE_H
#define INTERINTERFACE_H
#define TESTING
#ifndef TESTING
#include <wiringPi.h> //gpio respberry pi header
#include <softPwm.h>// software
#else
#include "tests/wiringPIDummy.hpp"
#endif

#include <functional> //needed for bind

#include <iostream>
#include <string>
#include <list>
#include "json/json.h"
/*
*
*Wrapper arround the interupts
*
*/
using namespace std;

class InterInterface {
    public:
      InterInterface(int pin);
      bool trig();
      void reset();
      void pullup();
      void trigHighLow();
      void trigLowHigh();
      int getDownPulse();
      int getUpPulse();
      int pin();
      Json::Value getJSON();
      void setJSON(Json::Value root);
      friend ostream& operator<<(ostream& stream,InterInterface &ob);
      friend istream& operator>>(istream& stream,InterInterface &ob);

    protected:
      int _pin;
      volatile unsigned long _upPulse;
      volatile unsigned long _downPulse;

    private:
      void registerListener(int pin);
      static std::list<std::function<void()>> pin0RisingListeners;
      static std::list<std::function<void()>> pin0FallingListeners;
      static std::list<std::function<void()>> pin1RisingListeners;
      static std::list<std::function<void()>> pin1FallingListeners;
      static std::list<std::function<void()>> pin2RisingListeners;
      static std::list<std::function<void()>> pin2FallingListeners;
      static std::list<std::function<void()>> pin3RisingListeners;
      static std::list<std::function<void()>> pin3FallingListeners;
      static std::list<std::function<void()>> pin4RisingListeners;
      static std::list<std::function<void()>> pin4FallingListeners;
      static std::list<std::function<void()>> pin5RisingListeners;
      static std::list<std::function<void()>> pin5FallingListeners;
      static std::list<std::function<void()>> pin6RisingListeners;
      static std::list<std::function<void()>> pin6FallingListeners;
      static std::list<std::function<void()>> pin7RisingListeners;
      static std::list<std::function<void()>> pin7FallingListeners;
      static std::list<std::function<void()>> pin8RisingListeners;
      static std::list<std::function<void()>> pin8FallingListeners;
      static std::list<std::function<void()>> pin9RisingListeners;
      static std::list<std::function<void()>> pin9FallingListeners;
      static std::list<std::function<void()>> pin10RisingListeners;
      static std::list<std::function<void()>> pin10FallingListeners;
      static std::list<std::function<void()>> pin11RisingListeners;
      static std::list<std::function<void()>> pin11FallingListeners;
      static std::list<std::function<void()>> pin12RisingListeners;
      static std::list<std::function<void()>> pin12FallingListeners;
      static std::list<std::function<void()>> pin13RisingListeners;
      static std::list<std::function<void()>> pin13FallingListeners;
      static std::list<std::function<void()>> pin14RisingListeners;
      static std::list<std::function<void()>> pin14FallingListeners;
      static std::list<std::function<void()>> pin15RisingListeners;
      static std::list<std::function<void()>> pin15FallingListeners;
      static std::list<std::function<void()>> pin16RisingListeners;
      static std::list<std::function<void()>> pin16FallingListeners;

      static void pin0Rising();
      static void pin0Falling();
      static void pin1Rising();
      static void pin1Falling();
      static void pin2Rising();
      static void pin2Falling();
      static void pin3Rising();
      static void pin3Falling();
      static void pin4Rising();
      static void pin4Falling();
      static void pin5Rising();
      static void pin5Falling();
      static void pin6Rising();
      static void pin6Falling();
      static void pin7Rising();
      static void pin7Falling();
      static void pin8Rising();
      static void pin8Falling();
      static void pin9Rising();
      static void pin9Falling();
      static void pin10Rising();
      static void pin10Falling();
      static void pin11Rising();
      static void pin11Falling();
      static void pin12Rising();
      static void pin12Falling();
      static void pin13Rising();
      static void pin13Falling();
      static void pin14Rising();
      static void pin14Falling();
      static void pin15Rising();
      static void pin15Falling();
      static void pin16Rising();
      static void pin16Falling();
      static void pin17Rising();
      static void pin17Falling();

};


#endif
