

/*
  Robot.h - Library for controlling robot.
  Created by Kieran Wyse.
  Released into the public domain.
*/
#ifndef ROBOT_H
#define ROBOT_H

#include <queue>
#include <cmath>
#include "Wheel.h"
#include "Sensor.h"
#include "pid.h"
#include "pidAngle.h"
#include "pidDistance.h"



enum Behavour {Go,Avoid,Wall,Rotate,Forward,None};
enum Tests {Sensors,Wheels,Robots,Interfaces,Registers,Nones};

class Robot
{
  public:
    Robot(double timer_interval);
    //stops the robot
    void stop();
    void goTo(double x, double y);
    void rotateTo(double angle);
    void forwardTo(double distance);



    void pullup();
    //prints out a visual confirmation of that rpbot is doing to serial
    void print();
    double getX();
    double getY();
    double getAngle();
    double getTargetX();
    double getTargetY();
    double getTargetAngle();
    //directly sets left wheel to required freqency
    void wheelLeft(int frequency);
    //directly sets right wheel to required freqency
    void wheelRight(int frequency);

    //directly sets wheels to required freqency
    void drive(int frequency);

    void test(Tests t);
    void updateObserver();
    void updateRobot();

    void state();
    friend ostream& operator<<(ostream& stream,Robot ob);
    friend istream& operator>>(istream& stream,Robot ob);
  private:
    //enable external chips
    void enable();

    //disable external chips
    void disable();

    //robot is going to point and there are no obsicals
    void go();

    //robot is going forward a distance
    void forward();

    //robot is rotating to an angle
    void rotate();

    //robot is avoiding an obstical
    void avoid();

    //robot is travelling along a wall
    void wall();

    //heart beat turns a led on and off to shou robot is still functioning
    //led to turn on and off
    unsigned int _heart_beat;
    //how freqently turned on and of
    unsigned int _heart_count;

    //distance travelled by the robot
    double _distance;

    //angle the robot is going to used during rotation
    double _target_angle;

    //distance the robot is going to usded during forward to command
    double _target_distance;

    //current postion of the robot
    Point *_position;

    //current angle of the robot
    double _angle;

    //current position that the robot is going to
    Point *_target;

    //list of positions the robot will go to
    std::queue<Point*> _targets;


    PID * _pointPID;
    PIDAngle * _anglePID;
    PIDDistance * _distancePID;


    double _wheel_base;
    Behavour _state;
    Tests _test;

    Wheel *_left;
    Wheel *_right;
    Sensor *_left_1;
    Sensor *_left_2;
    Sensor *_center;
    Sensor *_right_1;
    Sensor *_right_2;


};

#endif
