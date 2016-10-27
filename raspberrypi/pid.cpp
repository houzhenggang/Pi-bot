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

/*
*
*Uses jsoncpp to outputt stream of  values  of variables
*
* stream output of the format
*
*{
*   "linear" : 3,
*   "intergral" : 4,
*   "differential" : 2,
*   "error" : 0.3,
"   "previous_error": 0.4
*
*}
*
*/

std::ostream &operator<<(std::ostream& stream, PID &ob)
{
  Json::Value root;
  root["linear"] = ob.k_linear;
  root["intergral"] = ob.k_intergral;
  root["differential"] = ob.k_differential;
  root["error"] = ob.Error;
  root["previous_error"] = ob.old_error;
  stream << root;
  return stream;
}

/*
*
*Uses jsoncpp to parse input stream to values  of variables
*
* stream input of the format
*
*{
*   "linear" : 3,
*   "intergral" : 4,
*   "differential" : 2,
*   "error" : 0.3,
"   "previous_error": 0.4
*}
*
*/
std::istream &operator>>(std::istream& stream,Point &ob)
{
  Json::Value root;
  stream >> root;
  ob.k_linear = root.get("linear","0").asDouble();
  ob.k_intergral = root.get("intergral","0").asDouble();
  ob.k_differential = root.get("differentual","0").asDouble();
  ob.Error = root.get("error","0").asDouble();
  ob.previous_error = root.get("old_error","0").asDouble();
  return stream;
}
