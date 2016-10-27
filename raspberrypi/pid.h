/*
  PID.h - Library for controlling robot.
  Created by Kieran Wyse.
  Released into the public domain.
*/
#ifndef PID_H
#define PID_H

#include "Point.h"

class PID
{
  public:
  PID(double linear,double intergral, double differential);
  double next(Point *point,Point *target);
  void reset();
  friend std::ostream& operator<<(std::ostream& stream,PID &ob);
  friend std::istream& operator>>(std::istream& stream,PID &ob);
  private:
  double Error;
  double old_error;
  double k_linear;
  double k_intergral;
  double k_differential;

};

#endif
