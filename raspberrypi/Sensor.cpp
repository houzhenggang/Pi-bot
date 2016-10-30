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
