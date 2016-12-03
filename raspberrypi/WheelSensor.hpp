/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 08-11-2016
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


#ifndef WHEELSENSOR_H
#define WHEELSENSOR_H


#include <typeinfo>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>
#include <sstream>
#include <cstring>
#include <iostream>
#include <mutex>

#include "json/json.h"




class WheelSensor
{
  public:
    WheelSensor(int millisecond_updates = 10, double diameter = 0.1);
    double getDiameter();
    double getDistance();
    double getVelocity();
    double getOmega();
    void setDistance(double distance);
    void setVelocity(double velocity);
    void setDiameter(double diameter);
    void setOmega(double omega);
    void start();
    void stop();
    virtual void update() = 0;
    friend std::ostream& operator<<(std::ostream& stream,WheelSensor &ob);
    friend std::istream& operator>>(std::istream& stream,WheelSensor &ob);
    Json::Value getJSON();
    void setJSON(Json::Value root);
    ~WheelSensor();
  protected:
    std::chrono::high_resolution_clock::time_point  _timeLastUpdate;


    double getDuration();
    private:
      std::thread t1;
      void run();
      std::mutex running_mtx;
      bool _running;
      int _millisecond_updates;
      std::mutex distance_mtx;
      double _distance;
      std::mutex omega_mtx;
      double _omega;
      std::mutex velocity_mtx;
      double _velocity;
      std::mutex diameter_mtx;
      double  _diameter;

      std::mutex update_mtx;
      //double  _timeLastUpdate;

};

#endif
