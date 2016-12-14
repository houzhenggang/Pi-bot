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


#include "Robot.hpp"

Robot::Robot(double wheelbase, Wheel* left, Wheel* right)
{

  _state = None;
  _wheel_base = wheelbase;

  //_target_omega = 0;
  _target_angle = 0;
  _target_distance = 0;


  int sensor_left_1 = 8;
  int sensor_left_2 = 7;
  int sensor_center = 4;
  int sensor_right_1 = 2;
  int sensor_right_2 = 3;

  _distance= 0;
  _angle  = 0;

  _position = new Point(0,0);


  _pointPID = new PIDPoint(80,0.05,0.002);
  _anglePID = new PIDAngle(20,0.01,0.001);
  _pid = new PID(100,1,1);

  double wheel_diameter = 0.065;

  _left = left;
  _right = right;

  _left_1 = new Sensor(sensor_left_1);
  _left_2 = new Sensor(sensor_left_2);
  _center = new Sensor(sensor_center);
  _right_1 = new Sensor(sensor_right_1);
  _right_2 = new Sensor(sensor_right_2);




  time_between_updates = 100;
  running = true;
  std::thread t2(std::bind(&Robot::heartbeat,this));
  t1 = std::move(t2);

  start();
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
  WheelEncoder *left = dynamic_cast <WheelEncoder *> (_left->getSensor());
  if(left != NULL)
  left->pullup();
  WheelEncoder *right = dynamic_cast <WheelEncoder *> (_right->getSensor());
  if(right != NULL)
  right->pullup();
}
/*
* Get the x postion of the robot in metres
*/

double Robot::getX() {
  mtxPoint.lock();
  double x = _position->getX();
  mtxPoint.unlock();
  return x;
}

/*
* Get the distance travelled by the robot in metres
*/

double Robot::getDistance() {
  mtxDistance.lock();
  double distance = _distance;
  mtxDistance.unlock();
  return distance;
}




/*
* Get the y postion of the robot in metres
*/
double Robot::getY() {
  mtxPoint.lock();
  double y =  _position->getY();
  mtxPoint.unlock();
  return y;
}
double Robot::getAngle() {
  mtxAngle.lock();
  double angle = _angle;
  mtxAngle.unlock();
  return angle;
}


double Robot::getTargetX() {
  mtxTargets.lock();
  double x = 0;
  if(_targets.size()) {
    x = _targets.front()->getX();
  } else {
    std::cerr << "/*Error: Requested target value were no target set */" << '\n';
  }
  mtxTargets.unlock();
  return x;
}

double Robot::getTargetY() {
  mtxTargets.lock();
  double y = 0;
  if(_targets.size()) {
    y =_targets.front()->getY();
  } else {
    std::cerr << "/*Error: Requested target value were no target set */" << '\n';

  }
  mtxTargets.unlock();
  return y;
}
double Robot::getTargetAngle() {
  mtxTargetAngle.lock();
  double target_angle = _target_angle;
  mtxTargetAngle.unlock();
  return target_angle;
}

/*
*Return the state that the robot is in
*/

Behavour Robot::getState() {
  mtxState.lock();
  Behavour state = _state;
  mtxState.unlock();
  return state;
}


/*
*Set the state that the robot is in
*/

void Robot::setState( Behavour  state) {
  mtxState.lock();
  _state = state;
  mtxState.unlock();
}

void Robot::goTo(double x, double y) {
  setState(Go);
  mtxTargets.lock();
  _targets.push_back(new Point(x,y));
  mtxTargets.unlock();
}
/*
* Start the robot
*/

void Robot::start() {


}
/*
* Stop the robot
*/

void Robot::stop() {

  setState(None);
  update_mtx.lock();
  _left->stop();
  _right->stop();
  update_mtx.unlock();
}
/*
* rotate the robot to the angle, in radians
*/
void Robot::rotateTo(double angle) {
  mtxTargetAngle.lock();
  _target_angle = angle;
  mtxTargetAngle.unlock();
  setState(Rotate);

}
/*
* The robot goes forward a distance
*/

void Robot::forwardTo(double distance) {

  _target_distance = getDistance()+distance;

  _target_angle = getTargetAngle();
  setState(Forward);

}

/*
* set both of the wheels to go with the frequency
* set the pwm directly
*/


void Robot::drive(int frequency) {
  wheelLeft(frequency);
  wheelRight(frequency);
}
/*
* set the left wheels to go with the frequency
* set the pwm directly
*/
void Robot::wheelLeft(int frequency) {
  update_mtx.lock();
  _left->setFrequency(frequency);
  update_mtx.unlock();
}
/*
* set the right wheels to go with the frequency
* set the pwm directly
*/
void Robot::wheelRight(int frequency) {
  update_mtx.lock();
  _right->setFrequency(frequency);
  update_mtx.unlock();
}


void Robot::updateObserver() {

  double ldist = _left->getDistance();
  _left->setDistance(0);

  double rdist = _right->getDistance();
  _right->setDistance(0);


  //distance travelled since last update is
  double deltaDistance = 0.5*(ldist+rdist);
  double deltaAngle = (rdist-ldist)/_wheel_base;

  mtxAngle.lock();
  _angle = deltaAngle+_angle;
  if(_angle > M_PI) {
    _angle = _angle - 2*M_PI;
  }

  if(_angle < -M_PI) {
    _angle = _angle + 2*M_PI;
  }
  mtxAngle.unlock();

  mtxDistance.lock();
  _distance = deltaDistance + _distance;
  mtxDistance.unlock();

  mtxPoint.lock();
  _position->setX(deltaDistance*cos(_angle)+_position->getX());
  _position->setY(deltaDistance*sin(_angle)+_position->getY());
  mtxPoint.unlock();
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
  Behavour state = getState();
  if( state == Rotate && !trigger) {
    rotate();
  } else if( state == Forward && !trigger) {
    forward();
  } else if( state == Go && trigger) {
    avoid();
  } else if( state == Go) {
    go();
  } else if(trigger){
    pause();
  }

}

/*
* Go forward in a straight line
*/
void Robot::forward() {

  double freq_velocity = _pid->next(getDistance(),_target_distance);

  //Try to keep it in a straigt line by keeping the angle pointed by the robot the same as the intial angle
  double freq_omega = _anglePID->next(getAngle(),getTargetAngle());

  update_mtx.lock();
  _left->setFrequency(freq_velocity-freq_omega);
  _right->setFrequency(freq_velocity+freq_omega);
  update_mtx.unlock();
}

void Robot::rotate() {

  double freq_velocity = _anglePID->next(getAngle(),getTargetAngle());

  update_mtx.lock();
  _left->setFrequency(-freq_velocity);
  _right->setFrequency(freq_velocity);
  update_mtx.unlock();


}


void Robot::go() {
  mtxPoint.lock();
  mtxTargets.lock();
  if(_targets.empty()) {
    mtxTargets.unlock();
    mtxPoint.unlock();
    stop();
    return;
  }

  double freq_velocity = _pointPID->next(_position,_targets.front());;
  mtxTargets.unlock();
  if(freq_velocity>100)
    freq_velocity  = 100;


  double xdiff= _targets.front()->getX()-_position->getX();
  double ydiff= _targets.front()->getY()-_position->getY();
  mtxPoint.unlock();
  mtxTargetAngle.lock();
  _target_angle = atan2(ydiff,xdiff);
  mtxTargetAngle.unlock();

  mtxAngle.lock();
  mtxTargetAngle.lock();
  double freq_omega = _anglePID->next(_angle, _target_angle);
  mtxTargetAngle.unlock();
  mtxAngle.unlock();
  double lf = freq_velocity-freq_omega;
  double rf = freq_velocity+freq_omega;

  if(xdiff*xdiff+ydiff*ydiff>0.0001) {
    update_mtx.lock();
    _left->setFrequency(lf);
    _right->setFrequency(rf);
    update_mtx.unlock();

  } else {
    //if there is another target
    mtxTargets.lock();
    _targets.pop_front();
    mtxTargets.unlock();
    _pointPID->reset();
    _anglePID->reset();
  }
}
void Robot::avoid() {
  mtxPoint.lock();
  mtxTargetAngle.lock();
  double freq_velocity = _pointPID->next(_position,_targets.front());
  mtxTargetAngle.unlock();
  mtxPoint.unlock();

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
  mtxPoint.lock();
  double xdiff= _targets.front()->getX()-_position->getX();
  double ydiff= _targets.front()->getY()-_position->getY();
  mtxPoint.unlock();


  double target_angle = atan2(ydiff,xdiff);


  //blend behavours
  mtxTargetAngle.lock();
  _target_angle = (target_angle+avoid_angle)/2;


  //get the diiferentail in frequency of wheels from pid controller
  double freq_omega = 0;
  if(_anglePID != NULL)
  freq_omega = _anglePID->next(_angle, _target_angle);
  mtxTargetAngle.unlock();
  //set the left and right wheels
  update_mtx.lock();
  _left->setFrequency(freq_velocity-freq_omega);
  _right->setFrequency(freq_velocity+freq_omega);
  update_mtx.unlock();

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

  update_mtx.lock();

  while(running) {
    update_mtx.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds( time_between_updates));
    updateObserver();
    updateRobot();
    update_mtx.lock();
  }
  update_mtx.unlock();
}
Json::Value Robot::getJSON(){
  Json::Value root;
  mtxDistance.lock();
  root["distance"] = _distance;
  mtxDistance.unlock();
  mtxAngle.lock();
  root["angle"] = _angle;
  mtxAngle.unlock();
  mtxPoint.lock();
  root["position"] = _position->getJSON();
  mtxPoint.unlock();
  mtxTargetAngle.lock();
  root["target-angle"] = _target_angle;
  mtxTargetAngle.unlock();
  root["target-distance"] = _target_distance;

  root["PID-2d-points"] = _pointPID->getJSON();
  root["PID-angle"] = _anglePID->getJSON();
  root["PID-angle"] = _pid->getJSON();

  update_mtx.lock();
  root["left-wheel"] = _left->getJSON();
  root["right-wheel"] = _right->getJSON();
  update_mtx.unlock();

  root["left_1"] = _left_1->getJSON();
  root["left_2"] = _left_2->getJSON();
  root["center"] = _center->getJSON();
  root["right_1"] = _right_1->getJSON();
  root["right_2"] = _right_2->getJSON();
  mtxTargets.lock();
  std::deque<Point*>::iterator iterator =_targets.begin();
  while( iterator!= _targets.end()) {
    root["targets"].append( (*iterator)->getJSON());
    iterator++;
  }
  mtxTargets.unlock();

  switch(getState()) {
    case Go :
    root["state"] = "Go";
    break;
    case Avoid:
    root["state"] = "Avoid";
    break;
    case Rotate :
    root["state"] = "Rotate";
    break;
    case Pause:
    root["state"] = "Pause";
    break;
    case None:
    root["state"] = "None";
    break;
  }
  return root;
}
void Robot::setJSON(Json::Value root){
  mtxDistance.lock();
  if(root.isMember("distance"))
  _distance = root.get("distance",0).asDouble();
  mtxDistance.unlock();
  mtxAngle.lock();
  if(root.isMember("angle"))
  _angle = root.get("angle",0).asDouble();
  mtxAngle.unlock();
  mtxPoint.lock();
  if(root.isMember("position"))
    _position->setJSON(root.get("position",""));
  mtxPoint.unlock();
  mtxTargetAngle.lock();
  if(root.isMember("target-angle"))
    _target_angle = root.get("target-angle",0).asDouble();
  mtxTargetAngle.unlock();
  if(root.isMember("target-distance"))
    _target_distance = root.get("target-distance",0).asDouble();
  update_mtx.unlock();
}
std::ostream& operator<<(std::ostream& stream,Robot &ob) {
  stream<< ob.getJSON();
  return stream;
}
std::istream& operator>>(std::istream& stream,Robot &ob) {
  Json::Value root;
  stream>>root;
  ob.setJSON(root);
  return stream;
}

Robot::~Robot() {

  //wait for thread to finish (all variables should still be accessable to destructor has finished)
  stop();
  update_mtx.lock();
  running = false;
  update_mtx.unlock();

  if(t1.joinable())
  t1.join();


  delete _left;
  delete _right;
  delete _position;
  delete _pointPID;
  delete _anglePID;
  delete _pid;
  delete _left_1;
  delete _left_2;
  delete _center;
  delete _right_1;
  delete _right_2;
}
