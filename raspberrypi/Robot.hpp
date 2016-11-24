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



/*
  Robot.h - Library for controlling robot.
  Created by Kieran Wyse.
  Released into the public domain.
*/
#ifndef ROBOT_H
#define ROBOT_H

const double M_PI = 3.14159265359;


#include <queue>
#include <cmath>
#include <mutex>
#include <algorithm>
#include "Wheel.hpp"
#include "Sensor.hpp"
#include "PIDPoint.hpp"
#include "PIDAngle.hpp"
#include "PID.hpp"



enum Behavour {Go,Avoid,Wall,Rotate,Forward,Pause,None};

class Robot
{
  public:
    Robot();
    //stops the robot
    void stop();
    void goTo(double x, double y);
    void rotateTo(double angle);
    void forwardTo(double distance);



    void pullup();
    //prints out a visual confirmation of that rpbot is doing to serial

    double getX();
    double getY();
    double getAngle();
    double getTargetX();
    double getTargetY();
    double getTargetAngle();
    double getDistance();
    //directly sets left wheel to required freqency
    void wheelLeft(int frequency);
    //directly sets right wheel to required freqency
    void wheelRight(int frequency);

    //directly sets wheels to required freqency
    void drive(int frequency);
    void updateObserver();
    void updateRobot();
    void state();

    Json::Value getJSON();
    void setJSON(Json::Value root);
    friend ostream& operator<<(ostream& stream,Robot &ob);
    friend istream& operator>>(istream& stream,Robot &ob);

    ~Robot();
  private:
    //the main thread that controls the program
    std::thread t1;

    //The method called by the main thread
    void heartbeat();

    //The main thread lock, need due to any external modifications of the state of the robot will cause segmentaion faults
    std::mutex update_mtx;
    int time_between_updates;

    ///Used by the main thread to determin wether to stop
    bool running;



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

    //robot is paused
    void pause();

    //robot is travelling along a wall
    void wall();

    //distance travelled by the robot
    std::mutex mtxDistance;
    double _distance;

    //current angle of the robot
    std::mutex mtxAngle;
    double _angle;

    //current postion of the robot
    std::mutex mtxPoint;
    Point *_position;


    //angle the robot is going to used during rotation
    std::mutex mtxTargetAngle;
    double _target_angle;

    //distance the robot is going to used during forward to command
    double _target_distance;

    //list of positions the robot will go to
    std::mutex mtxTargets;
    std::deque<Point*> _targets;


    PIDPoint * _pointPID;
    PIDAngle * _anglePID;
    PID * _pid;


    double _wheel_base;
    std::mutex mtxState;
    Behavour _state;

    Wheel *_left;
    Wheel *_right;
    Sensor *_left_1;
    Sensor *_left_2;
    Sensor *_center;
    Sensor *_right_1;
    Sensor *_right_2;


};

#endif
