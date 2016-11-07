/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 05-11-2016
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


#ifndef WHEELSENSOR_H
#define WHEELSENSOR_H
#include "InterInterface.h"
#include <chrono>
#include <ctime>


class WheelSensor : public InterInterface
{
  public:
    WheelSensor(int pin,int ticks);
    double getDistance();
    double getVelocity();
    void update(double diameter, bool forward);
    friend std::ostream& operator<<(std::ostream& stream,WheelSensor &ob);
    friend std::istream& operator>>(std::istream& stream,WheelSensor &ob);
  protected:
    Json::Value getJSON();
    void setJSON(Json::Value root);
  private:
    double _previousDistance;
    double _distance;
    double _omega;
    double _velocity;
    int _ticks;
    unsigned long _prevPulses;
    std::chrono::high_resolution_clock::time_point  _timeLastUpdate;
};

#endif
