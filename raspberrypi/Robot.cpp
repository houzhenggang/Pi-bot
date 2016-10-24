/*
  Robot.cpp - Library for  code.
  Created by Kieran Wuse.
  Released into the public domain.
*/


#include "Robot.h"


Robot *Robot::_bot;

Robot::Robot(double timer_interval)
{

   _state = None;
   _wheel_base = 0.155;
   _target = NULL;

   //_target_omega = 0;
   _target_angle = 0;
   _target_distance = 0;

   _heart_beat = 13;

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


    pinMode(_heart_beat, OUTPUT);

    _distance= 0;
    _angle  = 0;



   _position = new Point(0,0);


  _pointPID = new PID(100,1,1);
   _anglePID = new PIDAngle(120,0,5);

   double wheel_diameter = 0.065;
   int wheel_ticks = 40;

    _left = new Wheel(wheel_diameter,wheel_ticks,wheel_left_forward,wheel_left_reverse,wheel_sensor_left);
    _right = new Wheel(wheel_diameter,wheel_ticks,wheel_right_forward,wheel_right_reverse,wheel_sensor_right);
    _left_1 = new Sensor(sensor_left_1);
    _left_2 = new Sensor(sensor_left_2);
    _center = new Sensor(sensor_center);
    _right_1 = new Sensor(sensor_right_1);
    _right_2 = new Sensor(sensor_right_2);
    _test = Nones;

    _bot = this;



    enable();

}
void Robot::enable() {
   pinMode(A0, OUTPUT);
   digitalWrite(A0, HIGH);
}

void Robot::disable() {
   pinMode(A0, OUTPUT);
   digitalWrite(A0, LOW);
}

void Robot::pullup() {
    _left_1->pullup();
    _left_2->pullup();
    _center->pullup();
    _right_1->pullup();
    _right_2->pullup();
    _left->pullup();
    _right->pullup();
}
void Robot::test(Tests t) {
   _test = t;
}
double Robot::getX() {

   return _position->getX();
}

double Robot::getY() {
   return _position->getY();
}
double Robot::getAngle() {
   return _angle;
}


double Robot::getTargetX() {
   return _target->getX();
}

double Robot::getTargetY() {
   return _target->getY();
}
double Robot::getTargetAngle() {
   return _target_angle;
}

void Robot::goTo(double x, double y) {
    _state = Go;
    if(_target != NULL) {
    } else {
       _target = new Point(x,y);
    }

}


void Robot::stop() {
   _state = None;
   _left->stop();
   _right->stop();;
}
void Robot::rotateTo(double angle)
{
    _target_angle = angle;
    _state = Rotate;

}

void Robot::forwardTo(double distance)
{
    _target_distance = distance+_distance;
    _state = Forward;
    delete _distancePID;
    _distancePID = new PIDDistance(255,0,0);

}


void Robot::drive(int frequency)
{
    _left->setFrequency(frequency);
    _right->setFrequency(frequency);
}
void Robot::wheelLeft(int frequency)
{
    _left->setFrequency(frequency);
}
void Robot::wheelRight(int frequency)
{
    _right->setFrequency(frequency);
}


void Robot::updateObserver()
{

   double ldist =_left->update();
   double rdist = _right->update();

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

    if(_heart_count> 50) {
       digitalWrite(_heart_beat, HIGH);
       if(_heart_count> 100) {
          _heart_count = 0;
       }
    }
    else {
       digitalWrite(_heart_beat, LOW);
    }
    _heart_count++;


}

void Robot::state()
{
  if(_bot->_state == Go || _bot->_state == Avoid || _bot->_state == Rotate || _bot->_state == Forward )
  {

     if(_bot->_left_1->trig() || _bot->_left_2->trig() || _bot->_center->trig()   ||_bot->_right_1->trig() || _bot->_right_2->trig()) {
         _bot->_state = Avoid;
     }
     else {
          _bot->_state = Go;
     }

     if(_bot->_state == Rotate) {
         _bot->rotate();
     }
     else if(_bot->_state == Forward) {
          _bot->forward();
     }
     else if(_bot->_state == Avoid && _bot->_target != NULL) {
         _bot->avoid();
     }
     else if(_bot->_state == Go && _bot->_target != NULL) {
         _bot->go();
     }


  }

}

void Robot::forward() {
   double freq_velocity = _distancePID->next(_distance,_target_distance);
    if(freq_velocity>255)
       freq_velocity = 255;
    _left->setFrequency(freq_velocity);
    _right->setFrequency(freq_velocity);
}

void Robot::rotate() {

   double freq_velocity = _anglePID->next(_angle,_target_angle);
    if(freq_velocity>255)
       freq_velocity = 255;
   _left->setFrequency(freq_velocity);
   _right->setFrequency(-freq_velocity);
}


void Robot::go()
{

    double freq_velocity = _pointPID->next(_position,_target);
    if(freq_velocity>255)
        freq_velocity = 255;

   double xdiff= _target->getX()-_position->getX();
   double ydiff= _target->getY()-_position->getY();

    _target_angle = atan2(ydiff,xdiff);

   double freq_omega = _anglePID->next(_angle, _target_angle);
   double lf = freq_velocity-freq_omega;
   double rf = freq_velocity+freq_omega;

   if(xdiff*xdiff+ydiff*ydiff>0.01) {
     _left->setFrequency(lf);
     _right->setFrequency(rf);

   } else {
      //if there is another target
      if(!_targets.isEmpty()) {
        //there is another target pop it of the stack
        _target = _targets.pop();
         _pointPID->reset();
         _anglePID->reset();
      } else {
         //there are no more targets
         delete _target;
         _target = NULL;
         //stop the robot
          _pointPID->reset();
          _anglePID->reset();
          stop();
      }
   }
}
void Robot::avoid()
{
   double freq_velocity = _pointPID->next(_position,_target);


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
   double xdiff= _target->getX()-_position->getX();
   double ydiff= _target->getY()-_position->getY();

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
ostream& operator<<(ostream& stream,Robot ob)
{
  stream<<ob._x
    <<" "<<ob._y
    <<" "<<ob._angle
    <<" "<<ob._distance
    <<" "<<ob._wheel_base
    <" "<<ob._state
    <<"\n";
  return stream;
}
istream& operator>>(istream& stream,Robot  ob)
{
  stream>>ob._x>>ob._y>>ob._angle;
  return stream;
}

void Robot::print()
{
    if(_test == Robots) {
        cout << this;
    }

    if( _test == Wheels) {
    	cout << _left;
    	cout << _righy;
    }
    if(_test == Sensors) {
  	   cout << _left_1;
    	 cout << _left_2;
    	cout << _center;
    	cout << _right_1;
    	cout <<_right_2;
    }
}
