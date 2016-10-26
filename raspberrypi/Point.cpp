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

ostream& operator<<(ostream& stream, Point ob)
{
  //stream<<"{ x : "<<ob._x<<" , y : "<<ob._y<<" } ";
  json::Value root;
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
istream& operator>>(istream& stream,Point ob)
{
  char c;
  string txt;
  stream.get(c); //first character is a '{'
  stream >> txt; // next stream should be x
  stream.get(c); //next character is ':'
  stream >> ob._x; //input data for x
  stream.get(c); //next character is a ','
  stream >> txt; // next stream should be y
  stream.get(c); //next character is ':'
  stream >>ob._y;
  stream.get(c); //first character is a '}'
  return stream;
}
