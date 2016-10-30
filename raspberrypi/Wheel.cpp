
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

#include "Wheel.h"
#include <math.h>
Wheel::Wheel(float diameter,int ticks,int motorPinForward,int motorPinReverse,int sensorPin) : InterInterface(sensorPin)
{
    _previousDistance = 0;
    _distance = 0;
    _velocity = 0;
    _frequency = 0;
    _motorPinForward = motorPinForward;
    _motorPinReverse = motorPinReverse;
    _sensorPin = sensorPin;
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


ostream& operator<<(ostream& stream,Wheel ob)
{
  stream<<ob._distance
    <<" "<<ob._previousDistance
    <<" "<<ob._velocity
    <<" "<<ob._frequency
    <<" "<<ob._motorPinForward
    <<" "<<ob._motorPinReverse
    <<" "<<ob._sensorPin
    <<" "<<ob._diameter
    <<" "<<ob._ticks
    <<" "<<ob._prevPulses
    <<" "<<ob._forward

    <<"\n";
  return stream;
}
istream& operator>>(istream& stream,Wheel  ob)
{
  stream>>ob._distance>>ob._previousDistance>>ob._velocity;
  return stream;
}
