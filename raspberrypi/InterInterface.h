/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 29-10-2016
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


#include <wiringPi.h> //gpio respberry pi header
#include <softPwm.h>// software
#include <functional> //needed for bind

#include <iostream>
#include <string>
#include <list>
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
      friend ostream& operator<<(ostream& stream,InterInterface ob);
      friend istream& operator>>(istream& stream,InterInterface ob);

    protected:
      int _pin;
      volatile unsigned long _upPulse;
      volatile unsigned long _downPulse;

    private:
      void registerListener(int pin);

      static std::list<std::function<void()>> pin1RisingListeners;
      static std::list<std::function<void()>> pin1FallingListeners;
      static void pin1Rising();
      static void pin1Falling();






};


#endif
