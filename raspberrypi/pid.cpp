#include "pid.h"
#include <cmath>

PID::PID(double linear,double intergral, double differential) {
  k_linear = linear;
  k_intergral = intergral;
  k_differential = differential;
  Error = 0;
  old_error = 0;
}
void PID::reset(){
   Error = 0;
   old_error = 0;
}


double PID::next(Point *point,Point *target) {

   double diff_x = target->getX()-point->getX();
   double diff_y = target->getY()-point->getY();

   double e = sqrt(diff_x*diff_x+diff_y*diff_y);

   //differentual term
   double ed = e - old_error;
   //p i d regulator
   double result = k_linear*e+k_differential*ed+k_intergral*Error;
   Error = e + Error;
   old_error  = e;
   return result;

}
