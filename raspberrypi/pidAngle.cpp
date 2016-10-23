#include "pidAngle.h"

PIDAngle::PIDAngle(double linear,double intergral, double differential) {
  k_linear = linear;
  k_intergral = intergral;
  k_differential = differential;
  Error = 0;
  old_error = 0;
}


void PIDAngle::reset(){
   Error = 0;
   old_error = 0;
}
void PIDAngle::setLinear(double linear){
    k_linear = linear;
}
void PIDAngle::setIntergral(double intergral) {
    k_intergral = intergral;
}
void PIDAngle::setDifferential(double differential) {
    k_differential = differential;
}

double PIDAngle::next(double actual,double target) {

   double e = target-actual;
   double edas = atan2(sin(e),cos(e));



   //differentual term
   double ed = edas - old_error;


   //p i d regulator
   double result = k_linear*edas+k_differential*ed+k_intergral*Error;

   Error = edas + Error;
   old_error = edas;
   return result;


}
