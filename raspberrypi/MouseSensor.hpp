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

#include <typeinfo>
#include "json/json.h"




#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>
#include <fcntl.h>

#include "WheelSensor.hpp"


class MouseSensor : public WheelSensor
{
public:
  	MouseSensor(std::string path= "/dev/input/mouse0",double diameter = 0.1, int millisecond_updates = 10, int dpi=800);
    int getDPI();
    void setDPI(int dpi);
    ~MouseSensor();

    friend std::ostream& operator<<(std::ostream& stream,MouseSensor &ob);
    friend std::istream& operator>>(std::istream& stream,MouseSensor &ob);
    Json::Value getJSON();
    void setJSON(Json::Value root);

  protected:
    void update();

  private:
    std::mutex path_mtx;
    std::string _path;
    //TODO turn this code into c++ type file io
    int _fd;
    //std::fstream fh;
    struct input_event _ie;
    std::mutex dpi_mtx;
    int _dpi;
    static double INCHTOM;
};

#endif
