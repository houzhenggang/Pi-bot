/*
  PID.h - Library for controlling robot.
  Created by Kieran Wyse.
  Released into the public domain.
*/
#ifndef PID_ANGLE_H
#define PID_ANGLE_H

class PIDAngle
{
  public:
  PIDAngle(double linear,double intergral, double differential);
  double next(double angle,double targety);

  void reset();
  void setLinear(double linear);
  void setIntergral(double intergral);
  void setDifferential(double differential);
  private:
  double Error;
  double old_error;
  double k_linear;
  double k_intergral;
  double k_differential;

};

#endif
