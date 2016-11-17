/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 14-11-2016
* @License: License: GPL v3
#     This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "Robot.h"
const double M_PI = 3.14159265359;

Robot::Robot()
{




   _state = None;
   _wheel_base = 0.155;

   //_target_omega = 0;
   _target_angle = 0;
   _target_distance = 0;


   int sensor_left_1 = 8;
   int sensor_left_2 = 7;
   int sensor_center = 4;

   int wheel_left_reverse = 6;
   int wheel_right_reverse = 5;

   int sensor_right_1 = 2;
   int sensor_right_2 = 3;

   int wheel_right_forward = 10;
   int wheel_left_forward = 9;

   int wheel_sensor_left = 12;
   int wheel_sensor_right = 11;


    _distance= 0;
    _angle  = 0;



   _position = new Point(0,0);


  _pointPID = new PIDPoint(100,1,1);
   _anglePID = new PIDAngle(20,0.001,0.001);
   _pid = new PID(100,1,1);

   double wheel_diameter = 0.065;
   int wheel_ticks = 40;

    _left = new Wheel(wheel_diameter,wheel_left_forward,wheel_left_reverse, new WheelSensor(wheel_sensor_left,wheel_ticks));
    _right = new Wheel(wheel_diameter,wheel_right_forward,wheel_right_reverse,new WheelSensor(wheel_sensor_right,wheel_ticks));
    _left_1 = new Sensor(sensor_left_1);
    _left_2 = new Sensor(sensor_left_2);
    _center = new Sensor(sensor_center);
    _right_1 = new Sensor(sensor_right_1);
    _right_2 = new Sensor(sensor_right_2);


    time_between_updates = 100;
    std::thread t2(std::bind(Robot::heartbeat,this));
    t1 = std::move(t2);

}

/*
*Add at a later date to control motor driver hardware, enable and dispable to save power
*/
/*void Robot::enable() {
   pinMode(A0, OUTPUT);
   digitalWrite(A0, HIGH);
}

void Robot::disable() {
   pinMode(A0, OUTPUT);
   digitalWrite(A0, LOW);
}*/

/*
*
*Pull up the pins to voltage hight on the pins that are defined as sensors
*
*/
void Robot::pullup() {
    _left_1->pullup();
    _left_2->pullup();
    _center->pullup();
    _right_1->pullup();
    _right_2->pullup();
    _left->getSensor()->pullup();
    _right->getSensor()->pullup();
}
/*
 * Get the x postion of the robot in metres
 */

double Robot::getX() {

   return _position->getX();
}

/*
 * Get the distance travelled by the robot in metres
 */

double Robot::getDistance() {

   return _distance;
}




/*
 * Get the y postion of the robot in metres
 */
double Robot::getY() {
   return _position->getY();
}
double Robot::getAngle() {
   return _angle;
}


double Robot::getTargetX() {
  if(_targets.size())
    return _targets.front()->getX();
  std::cerr << "/*Error: Requested target value were no target set */" << '\n';
  return 0;
}

double Robot::getTargetY() {
  if(_targets.size())
    return _targets.front()->getX();
  std::cerr << "/*Error: Requested target value were no target set */" << '\n';
  return 0;
}
double Robot::getTargetAngle() {
   return _target_angle;
}

void Robot::goTo(double x, double y) {
    _state = Go;
    time_between_updates = 100;
    _targets.push(new Point(x,y));
}
/*
 * Stop the robot moving
 */

void Robot::stop() {
   _state = None;
   _left->stop();
   _right->stop();;
}
/*
 * rotate the robot to the angle, in radians
 */
void Robot::rotateTo(double angle) {
	_target_angle = angle;
    _state = Rotate;

}
/*
 * The robot goes forward a distance
 */

void Robot::forwardTo(double distance) {
	_target_distance = distance+_distance;
	_target_angle = _angle;
    _state = Forward;

}

/*
 * set both of the wheels to go with the frequency
 * set the pwm directly
 */


void Robot::drive(int frequency) {
	_left->setFrequency(frequency);
    _right->setFrequency(frequency);
}
/*
 * set the left wheels to go with the frequency
 * set the pwm directly
 */
void Robot::wheelLeft(int frequency) {
	time_between_updates = 100;
	_left->setFrequency(frequency);
}
/*
 * set the right wheels to go with the frequency
 * set the pwm directly
 */
void Robot::wheelRight(int frequency) {
	_right->setFrequency(frequency);
}


void Robot::updateObserver() {

   //previous left distance
   double pld = _left->getDistance();
   _left->update();
   double ldist =_left->getDistance() -pld;


   double prd = _right->getDistance();
   _right->update();
   double rdist =_right->getDistance() -prd;


   //distance travelled since last update is
   double deltaDistance = 0.5*(ldist+rdist);
   double deltaAngle = (rdist-ldist)/_wheel_base;

   _angle = deltaAngle+_angle;

   _distance = deltaDistance + _distance;

   _position->setX(deltaDistance*cos(_angle)+_position->getX());
   _position->setY(deltaDistance*sin(_angle)+_position->getY());
}

void Robot::updateRobot() {

     state();
    _left_1->reset();
    _left_2->reset();
    _center->reset();
    _right_1->reset();
    _right_2->reset();

}

void Robot::state() {
	bool trigger = false;
    if(_left_1->trig() || _left_2->trig() || _center->trig()   ||_right_1->trig() ||  _right_2->trig()) {
    	trigger = true;
    }
     if( _state == Rotate && !trigger) {
          rotate();
     } else if( _state == Forward && !trigger) {
           forward();
     } else if( _state == Go &&  _targets.front() != NULL && !trigger) {
          avoid();
     } else if( _state == Go &&  _targets.front() != NULL) {
          go();
     } else if(trigger){
    	 pause();
     }


  }


void Robot::forward() {
   double freq_velocity = _pid->next(_distance,_target_distance);
    if(freq_velocity>100)
       freq_velocity = 100;
    _left->setFrequency(freq_velocity);
    _right->setFrequency(freq_velocity);
}

void Robot::rotate() {

   double freq_velocity = _anglePID->next(_angle,_target_angle);
    if(freq_velocity>100)
       freq_velocity = 100;
    if(freq_velocity<-100)
       freq_velocity = -100;
   _left->setFrequency(-freq_velocity);
   _right->setFrequency(freq_velocity);
   if(_angle > M_PI) {
	   _angle = _angle - 2*M_PI;
   }

   if(_angle < -M_PI) {
   	   _angle = _angle + 2*M_PI;
      }
}


void Robot::go() {

    double freq_velocity = _pointPID->next(_position,_targets.front());
    if(freq_velocity>100)
        freq_velocity = 100;

   double xdiff= _targets.front()->getX()-_position->getX();
   double ydiff= _targets.front()->getY()-_position->getY();

    _target_angle = atan2(ydiff,xdiff);

   double freq_omega = _anglePID->next(_angle, _target_angle);
   double lf = freq_velocity-freq_omega;
   double rf = freq_velocity+freq_omega;

   if(xdiff*xdiff+ydiff*ydiff>0.01) {
     _left->setFrequency(lf);
     _right->setFrequency(rf);

   } else {
      //if there is another target
      if(!_targets.empty()) {
         _targets.pop();
         _pointPID->reset();
         _anglePID->reset();
      } else {
          _pointPID->reset();
          _anglePID->reset();
          stop();
      }
   }
}
void Robot::avoid() {
   double freq_velocity = _pointPID->next(_position,_targets.front());


   double avoid_angle = 0;
   //number of sensors triggered
   int trig_num = 0;
   //if sensor 1 triggered left hand side ouside
   if(_left_1->trig()) {
     //go in the opposit direction to the sensor
      avoid_angle = 3*M_PI/2;
      //interate number if triggers
      trig_num++;
   }

   //if sensor 2 triggered left hand side near centre
   if(_left_2->trig()) {
      //go in the opposit direction to the sensor
      avoid_angle = 5*M_PI/4;
      //interate number if triggers
      trig_num++;
   }

    //if sensor 3 triggered  centre
   if(_center->trig()) {
      //go in the opposit direction to the sensor
      avoid_angle = M_PI;
      //interate number if triggers
      trig_num++;
   }

   //if sensor 4 triggered right hand side near centre
   if(_right_2->trig()) {
      //go in the opposit direction to the sensor
      avoid_angle = 3*M_PI/4;
      //interate number if triggers
      trig_num++;
   }

   //if sensor 5 triggered right hand side outside
   if(_right_1->trig()) {
      //go in the opposit direction to the sensor
      avoid_angle = 2*M_PI/4;
      //interate number if triggers
      trig_num++;
   }
   //average angle to avoid in respect to the robot
   avoid_angle = avoid_angle/trig_num;

   //add it to the angle of the robot to get the angle in respect to the global co-ordinate system
   avoid_angle = avoid_angle + _angle;

   //scale angle to 0 to 2pi
   avoid_angle = fmod(avoid_angle,2*M_PI);

   //scale angle to -pi to pi
   if(avoid_angle > M_PI) {
      avoid_angle = avoid_angle - M_PI;
   }

   //work out where robot should go if no obstical
   double xdiff= _targets.front()->getX()-_position->getX();
   double ydiff= _targets.front()->getY()-_position->getY();

   double target_angle = atan2(ydiff,xdiff);


    //blend behavours
    _target_angle = (target_angle+avoid_angle)/2;

    //get the diiferentail in frequency of wheels from pid controller
    double freq_omega = 0;
    if(_anglePID != NULL)
        freq_omega = _anglePID->next(_angle, _target_angle);

    //set the left and right wheels
     _left->setFrequency(freq_velocity-freq_omega);
     _right->setFrequency(freq_velocity+freq_omega);

}

/*
 * Pause the robot
 */

void Robot::pause() {
	stop();
}
/*
*Update the robot few milliseconds
* milliseconds are set in the time_between_updates variable
* when this varabile is set to 0 thread neds;
*
*
*/
void Robot::heartbeat() {


	while(time_between_updates) {
		std::this_thread::sleep_for(std::chrono::milliseconds(time_between_updates));
		updateObserver();
		updateRobot();

	}
}
Json::Value Robot::getJSON(){
  Json::Value root;
  root["distance"] = _distance;
  root["angle"] = _angle;
  root["position"] = _position->getJSON();
  root["target-angle"] = _target_angle;
  root["target-distance"] = _target_distance;

  root["PID-2d-points"] = _pointPID->getJSON();
  root["PID-angle"] = _anglePID->getJSON();
  root["PID-angle"] = _pid->getJSON();

  root["left-wheel"] = _left->getJSON();
  root["right-wheel"] = _right->getJSON();

  root["left_1"] = _left_1->getJSON();
  root["left_2"] = _left_2->getJSON();
  root["center"] = _center->getJSON();
  root["right_1"] = _right_1->getJSON();
  root["right_2"] = _right_2->getJSON();

  return root;
}
void Robot::setJSON(Json::Value root){
  if(root.isMember("distance"))
    _distance = root.get("distance",0).asDouble();
  if(root.isMember("angle"))
    _angle = root.get("angle",0).asDouble();
  if(root.isMember("position"))
    _position->setJSON(root.get("position",""));
  if(root.isMember("target-angle"))
    _target_angle = root.get("target-angle",0).asDouble();
  if(root.isMember("target-distance"))
    _target_distance = root.get("target-distance",0).asDouble();
}
ostream& operator<<(ostream& stream,Robot &ob) {
  stream<< ob.getJSON();
  return stream;
}
istream& operator>>(istream& stream,Robot &ob) {
  Json::Value root;
  stream>>root;
  ob.setJSON(root);
  return stream;
}

Robot::~Robot() {
	time_between_updates = 0;
	//wait for thread to finish (all variables should still be accessable to destructor has finished)

	if(t1.joinable())
	    	t1.join();
	stop();
}
