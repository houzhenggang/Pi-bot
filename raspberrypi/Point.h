/*
  Point.h - Library for controlling robot.
  Created by Kieran Wyse.
  Released into the public domain.
*/

#include <iostream>
#include <string>
#include "json/json.h"

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
  friend ostream& operator<<(ostream& stream,Point ob);
  friend istream& operator>>(istream& stream,Point ob);
  private:
  double _x;
  double _y;

};

#endif
