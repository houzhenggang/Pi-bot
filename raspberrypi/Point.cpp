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

std::ostream &operator<<(std::ostream& stream, const Point &ob)
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
*Use jsoncpp to parse json string inputs
*
*/
std::istream &operator>>(std::istream& stream,Point &ob)
{
  Json::Value root;
  stream >> root;
  ob.setX(root.get("x","0").asDouble());
  ob.setY(root.get("y","0").asDouble());
  return stream;
}
