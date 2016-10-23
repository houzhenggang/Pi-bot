#include "pidDistance.h"

PIDDistance::PIDDistance(double linear,double intergral, double differential) {
  k_linear = linear;
  k_intergral = intergral;
  k_differential = differential;
}

double PIDDistance::next(double actual,double target) {

   double e = target-actual;


   //differentual term
   double ed = e - old_error;


   //p i d regulator
   double result = k_linear*e+k_differential*ed+k_intergral*Error;

   Error = e + Error;
   old_error = e;
   return result;


}
