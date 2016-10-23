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
