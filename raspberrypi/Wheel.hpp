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

#ifndef WHEEL_H
#define WHEEL_H
#include <typeinfo>
#include "InterInterface.hpp"

#include "WheelSensor.hpp"
#include "WheelEncoder.hpp"
#include "MouseSensor.hpp"

#include "TractionControl.hpp"

class Wheel
{
  public:
    Wheel(int motorPinForward,int motorPinReverse,WheelSensor *sensor);
    double getVelocity();
    double getDistance();
    void setDistance(double distance);
    int getFrequency();
    void setFrequency(int frequency);
    void stop();
    void update();
    void setSensor(WheelSensor *sensor);
    WheelSensor* getSensor();
    friend std::ostream& operator<<(std::ostream& stream,Wheel &ob);
    friend std::istream& operator>>(std::istream& stream,Wheel &ob);
    Json::Value getJSON();
    void setJSON(Json::Value root);
    ~Wheel();

  private:
    TractionControl *_contol;
    WheelSensor *_sensor;
    void pwm(int pin,int duty);
    int _frequency;
    int _motorPinForward;
    int _motorPinReverse;


};

#endif
