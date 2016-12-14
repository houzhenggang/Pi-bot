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

#include <iostream>
#include <string>
#include "json.h"

#ifndef POINT_H
#define POINT_H

class Point
{
  public:
  Point(double x,double y);
  double getX();
  double getY();
  void setX(double x);
  void setY(double y);
  Json::Value getJSON();
  void setJSON(Json::Value root);
  friend std::ostream& operator<<(std::ostream& stream,Point &ob);
  friend std::istream& operator>>(std::istream& stream,Point &ob);
  private:
  double _x;
  double _y;

};

#endif
