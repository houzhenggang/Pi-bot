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
