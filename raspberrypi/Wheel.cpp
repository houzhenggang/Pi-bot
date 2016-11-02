
/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 02-11-2016
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

#include "Wheel.h"
#include <math.h>
const double M_PI  =3.141592653589793238463;
Wheel::Wheel(float diameter,int ticks,int motorPinForward,int motorPinReverse,int sensorPin) : InterInterface(sensorPin)
{


    _previousDistance = 0;
    _distance = 0;
    _velocity = 0;
    _frequency = 0;
    _motorPinForward = motorPinForward;
    _motorPinReverse = motorPinReverse;
    _diameter = diameter;
    _ticks = ticks;
     _prevPulses = 0;
    _forward = true;

    _ticks = ticks;
    _const = M_PI*_diameter/ticks;
    _contol = new TractionControl(10);

    int pwmRange = 255;
    softPwmCreate (_motorPinForward , 0, pwmRange) ;
    softPwmCreate (_motorPinReverse , 0, pwmRange) ;

}

double Wheel::distance(){
   if(_forward)
        return _distance;
    else
        return -_distance;

}

int Wheel::getFrequency(){
   return _frequency;
}

double Wheel::update() {

    //Find out the distance the wheel has turned from the pulses;


   //Avarage the pules to get a more accurate figure
   unsigned long pulses =  (_upPulse+_downPulse);

   //change in the pulses since last time
   unsigned int deltaPulses = pulses-_prevPulses;
   _prevPulses = pulses;


    if(_forward) {
        _distance = _distance + _const*deltaPulses;
        return _const*deltaPulses;
    } else {
        _distance = _distance - _const*deltaPulses;
        return -_const*deltaPulses;
    }
}
void Wheel::setFrequency(int frequency) {

   if(frequency > 255)
      frequency = 255;
   if(frequency < -255)
      frequency = -255;
   //frequency = _contol->modify( frequency);
   if(frequency > 0) {
       _forward = true;
       pwm(_motorPinForward,frequency);
       pwm(_motorPinReverse,0);
   } else {
       _forward = false;
       pwm(_motorPinForward,0);
       pwm(_motorPinReverse,-frequency);
   }
   _frequency = frequency;
}

void Wheel::pwm(int pin,int duty) {


    softPwmWrite (pin,duty) ;


}
void Wheel::stop() {
   _frequency = 0;
   pwm(_motorPinReverse,0);
   pwm(_motorPinForward,0);
}

double Wheel::velocity() {
   return _velocity;
}


ostream& operator<<(ostream& stream,Wheel &ob)
{
  Json::Value root;
  root["diameter"] = ob._diameter;
  root["ticks"] =ob._ticks;
  root["forward"] =ob._forward;
  root["distance"] = ob._distance;
  root["previous-distance"] = ob._previousDistance;
  root["velocity"] = ob._velocity;
  root["frequency"] = ob._frequency;
  root["motor-forward-pin"] = ob._motorPinForward;
  root["motor-reverse-pin"] = ob._motorPinReverse;

  root["previous-pulses"] = ob._prevPulses;

  stream << root;
  //stream the parent class
  InterInterface newob = (InterInterface) ob;
  stream << newob;
  return stream;
}
istream& operator>>(istream& stream,Wheel  &ob)
{
    Json::Value root;
    stream >> root;
    ob._diameter = root.get("diameter","0").asFloat();
    ob._ticks = root.get("up-pulses","0").asInt();
    ob._forward = root.get("down-pulses","0").asBool();
    ob._distance = root.get("distance","0").asDouble();
    ob._previousDistance = root.get("previous-distance","0").asDouble();
    ob._velocity =root.get("velocity","0").asDouble();
    ob._frequency = root.get("frequency","0").asInt();
    ob._motorPinForward = root.get("motor-forward-pin","0").asInt();
    ob._motorPinReverse = root.get("motor-reverse-pin","0").asInt();
    ob._prevPulses = root.get("previous-pulses","0").asUInt64();
    ob._const = M_PI*ob._diameter/ob._ticks;

    InterInterface newob = (InterInterface) ob;
    stream >> newob;
    return stream;

}
