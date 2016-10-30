/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 29-10-2016
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

#include "Point.h"




Point::Point(double x,double y) {
   _x = x;
   _y = y;

}

void Point::setX(double x) {
   _x = x;
}

void Point::setY(double y) {
   _y = y;
}

double Point::getX() {
   return _x;
}

double Point::getY() {
   return _y;
}

/*
*
*Uses jsoncpp to outputt stream of  values  of variables
*
* stream output of the format
*
*{
*   "x" : 3,
*   "y" : 4
*}
*
*/

std::ostream &operator<<(std::ostream& stream, Point &ob)
{
  //stream<<"{ x : "<<ob._x<<" , y : "<<ob._y<<" } ";
  Json::Value root;
  root["x"] = ob._x;
  root["y"] = ob._y;
  stream << root;
  return stream;
}

/*
*
*Uses jsoncpp to parse input stream to values  of variables
*
* stream input of the format
*
*{
*   "x" : 3,
*   "y" : 4
*}
*
*/
std::istream &operator>>(std::istream& stream,Point &ob)
{
  Json::Value root;
  stream >> root;
  ob._x = root.get("x","0").asDouble();
  ob._y = root.get("y","0").asDouble();
  return stream;
}
