
/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 15-11-2016
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

#include "Wheel.hpp"
#include <math.h>


//std::clock_t c_start = std::clock();


//const double M_PI  =3.141592653589793238463;
const int MAX_FREQUENCY = 100;
Wheel::Wheel(int motorPinForward,int motorPinReverse,WheelSensor *sensor)
{
  _sensor = sensor;
    _frequency = 0;
    _motorPinForward = motorPinForward;
    _motorPinReverse = motorPinReverse;

    _forward = true;

    _contol = new TractionControl(10);

    int pwmRange = MAX_FREQUENCY;
    softPwmCreate (_motorPinForward , 0, pwmRange) ;
    softPwmCreate (_motorPinReverse , 0, pwmRange) ;

}
/*
*
* Set the wheel sensor.
* This sensor is the senosr used to return state of the wheel
*
*/
void Wheel::setSensor(WheelSensor *sensor) {
  _sensor = sensor;
    }
/*
*
* get the wheel sensor.
* This sensor is the senosr used to return the state of the wheel
*
*/
WheelSensor* Wheel::getSensor() {
  return _sensor;
    }

int Wheel::getFrequency(){
   return _frequency;
}

void Wheel::update() {
  _sensor->update();
}

/*
*
*Return the distance travelled by the wheel
*
*/

double Wheel::getDistance() {
  return _sensor ->getDistance();
}

/*
*
*Return the velocity at the edge of the wheel
*
*/

double Wheel::getVelocity() {
  return _sensor->getVelocity();
}

/*
*
*Set the frequency of pwm pin. A postive frequency turns on  pwm on the forward pin
* a negative frequency turns on pwm on the reverse pin
*
*/
void Wheel::setFrequency(int frequency) {

   if(frequency > MAX_FREQUENCY)
      frequency = MAX_FREQUENCY;
   if(frequency < -MAX_FREQUENCY)
      frequency = -MAX_FREQUENCY;
   //frequency = _contol->modify( frequency);
   if(frequency != _frequency) {
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

}

void Wheel::pwm(int pin,int duty) {


    softPwmWrite (pin,duty) ;


}
void Wheel::stop() {
   _frequency = 0;
   pwm(_motorPinReverse,0);
   pwm(_motorPinForward,0);
}
void Wheel::setJSON(Json::Value root) {
  if(root.isMember("forward"))
    _forward = root.get("forward",0).asBool();
  if(root.isMember("frequency"))
    _frequency = root.get("frequency",0).asInt();
  if(root.isMember("motor-forward-pin"))
    _motorPinForward = root.get("motor-forward-pin",0).asInt();
  if(root.isMember("motor-reverse-pin"))
    _motorPinReverse = root.get("motor-reverse-pin",0).asInt();
  if(root.isMember("sensor")) {
      _sensor->setJSON(root.get("sensor",""));
    } else if(root.isMember("wheel-encoder")) {
      _sensor->setJSON(root.get("wheel-encoder",""));
    } else if(root.isMember("mouse-sensor")){
      _sensor->setJSON(root.get("mouse-sensor",""));
    }



}

Json::Value Wheel::getJSON() {
  Json::Value root;
  root["forward"] =_forward;
  root["frequency"] = _frequency;
  root["motor-forward-pin"] = _motorPinForward;
  root["motor-reverse-pin"] = _motorPinReverse;

  WheelEncoder * encoder = dynamic_cast<WheelEncoder *>(_sensor);
  if(encoder != NULL)
    root["wheel-encoder"] = encoder->getJSON();
  MouseSensor* msensor = dynamic_cast<MouseSensor *>(_sensor);
  if(msensor != NULL)
    root["mouse-sensor"] = msensor->getJSON();
  if(_sensor !=NULL)
    root["sensor"] = _sensor->getJSON();
  return root;
}

std::ostream& operator<<(std::ostream& stream,Wheel &ob)
{
  Json::Value root = ob.getJSON();
  stream << root;
  return stream;
}
std::istream& operator>>(std::istream& stream,Wheel  &ob)
{
    Json::Value root;
    stream >> root;
    ob.setJSON(root);
    return stream;

}
Wheel::~Wheel() {
  stop();
}
