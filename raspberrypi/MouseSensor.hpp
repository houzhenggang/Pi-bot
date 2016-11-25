/**
* @Author: Kieran Wyse
* @Date:   22-11-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 22-11-2016
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


#ifndef MOUSESENSOR_H
#define MOUSESENSOR_H


#include "json/json.h"

#include <chrono>
#include <ctime>
#include <thread>
#include <string>
#include <iostream>
#include <mutex>

#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>
#include <fcntl.h>


class MouseSensor
{
public:
  	MouseSensor(std::string path= "/dev/input/mouse0",double diameter = 0.1, int millisecond_updates = 2, double ratio =1);
    double getDistance();
    double getVelocity();
    double getDiameter();
    double getOmega();
    ~MouseSensor();

    friend std::ostream& operator<<(std::ostream& stream,MouseSensor &ob);
    friend std::istream& operator>>(std::istream& stream,MouseSensor &ob);
    Json::Value getJSON();
    void setJSON(Json::Value root);

  protected:
    void update();

    void setDistance(double distance);
    void setVelocity(double velocity);
    void setDiameter(double diameter);
    void setOmega(double omega);

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
    double  _timeLastUpdate;
    std::mutex path_mtx;
    std::string _path;
    int _fd;
    struct input_event _ie;
};

#endif
