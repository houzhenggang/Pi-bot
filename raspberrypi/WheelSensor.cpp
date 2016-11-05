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

#include "WheelSensor.h"

const double M_PI = 3.14159265359;

WheelSensor::WheelSensor(int pin,int ticks) : InterInterface(pin) {
  pinMode (pin, OUTPUT) ;

  _previousDistance = 0;
  _distance = 0;
  _ticks = ticks;
  _omega = 0;
  _prevPulses = 0;
  _velocity = 0;
   _timeLastUpdate = std::chrono::high_resolution_clock::now();
}

/*
*
*Return the total distance travelled by the wheel
*
*/

double WheelSensor::getDistance() {
    return _distance;
}

/*
*
* Get the velocity of the edge of the wheel
*
*/

double WheelSensor::getVelocity() {
  return _velocity;

}


/*
*
*Update the state of the wheel
*
*/
void WheelSensor::update(double diameter, bool forward) {

    //Find out the distance the wheel has turned from the pulses;
   double cnst = M_PI*diameter/(2*_ticks);

   //Avarage the pules to get a more accurate figure
   unsigned long pulses =  (_upPulse+_downPulse);

   //change in the pulses since last time
   unsigned int deltaPulses = pulses-_prevPulses;
   _prevPulses = pulses;


    if(forward) {
        _distance = _distance + cnst*deltaPulses;
    } else {
        _distance = _distance - cnst*deltaPulses;
    }
  auto now = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::seconds>(now - _timeLastUpdate);
  //work out the rotational freqency in radians per second;
  double timespan =  time_span.count();
  double f = ((double)deltaPulses)/ (2*_ticks*timespan);
  _omega = 2*M_PI*f;
  _velocity = _omega*diameter/2;
  _timeLastUpdate = now;
}

ostream& operator<<(ostream& stream,WheelSensor &ob)
{
  Json::Value root;
  root["ticks"] =ob._ticks;
  root["distance"] = ob._distance;
  root["previous-distance"] = ob._previousDistance;
  root["omega"] = ob._omega;
  root["previous-pulses"] = ob._prevPulses;
  std::time_t ppt = std::chrono::system_clock::to_time_t(ob._timeLastUpdate);
  root["previous-pulse-time"] =std::ctime(&ppt);

  stream << root;
  //stream the parent class
  InterInterface newob = (InterInterface) ob;
  stream << newob;
  return stream;
}
istream& operator>>(istream& stream,WheelSensor  &ob)
{
    Json::Value root;
    stream >> root;
    ob._ticks = root.get("up-pulses","0").asInt();
    ob._distance = root.get("distance","0").asDouble();
    ob._previousDistance = root.get("previous-distance","0").asDouble();
    ob._omega =root.get("omega","0").asDouble();

    ob._prevPulses = root.get("previous-pulses","0").asUInt64();

    InterInterface newob = (InterInterface) ob;
    stream >> newob;
    return stream;

}
