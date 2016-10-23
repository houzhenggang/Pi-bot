/*
  PID.h - Library for controlling robot.
  Created by Kieran Wyse.
  Released into the public domain.
*/
#ifndef PID_DISTANCE_H
#define PID_DISTANCE_H

class PIDDistance
{
  public:
  PIDDistance(double linear,double intergral, double differential);
  double next(double distace,double target);
  private:
  double Error;
  double old_error;
  double k_linear;
  double k_intergral;
  double k_differential;

};

#endif
