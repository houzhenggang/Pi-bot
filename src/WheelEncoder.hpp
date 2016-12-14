/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 08-11-2016
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


#ifndef WHEELENCODER_H
#define WHEELENCODER_H


#include <typeinfo>
#include "InterInterface.hpp"
#include "WheelSensor.hpp"
#include <chrono>
#include <ctime>
#include <sstream>



class WheelEncoder : public InterInterface, public WheelSensor
{
  public:
    WheelEncoder(int pin,int ticks,double diameter = 0.1, int millisecond_updates = 10);

    void update();
    friend std::ostream& operator<<(std::ostream& stream,WheelEncoder &ob);
    friend std::istream& operator>>(std::istream& stream,WheelEncoder &ob);
    Json::Value getJSON();
    void setJSON(Json::Value root);
  protected:

  private:
    int _ticks;
    unsigned long _prevPulses;
    
};

#endif
