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

std::ostream& operator<<(std::ostream& stream, Point ob)
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
*Assume that that the input stream is well formatted json with white spsaces between all data and formatting
*
*/
std::istream& operator>>(std::istream& stream,Point ob)
{
  Json::Value root;
  stream >> root;

  ob._x = root.get("x").asDouble();
  ob._y = root.get("y").asDouble();s
  return stream;
}
