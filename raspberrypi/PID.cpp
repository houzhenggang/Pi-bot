/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 02-11-2016
* @License: GPL v3
*     This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "PID.hpp"
/*
*Implementaion of a PID controller
*
* https://en.wikipedia.org/wiki/PID_controller
*
*/

PID::PID(double linear,double intergral, double differential) {
  _linear = linear;
  _intergral = intergral;
  _differential = differential;
  Error = 0;
  old_error = 0;
}

/*
*
*Return controller to its original state
*
*/
void PID::reset() {
   Error = 0;
   old_error = 0;
}

/*
*
*Returns what the input value of the system should be set to to achive the target value of output of the system
*
*value - value as measured by the system in its current state
*target - value the system should be at
*
*return value - value to input into the system
*
*/
double PID::next(double value,double target) {

   double e = target - value;

   //differentual term
   double ed = e - old_error;
   //p i d regulator
   double result = _linear*e+_differential*ed+_intergral*Error;
   Error = e + Error;
   old_error  = e;
   return result;

}



/*
*
*Uses jsoncpp to outputt  values  of variables
*
* m output of the format
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
* Can be used in inherited classes to get arround ristrinction on friend methods access to internal veriables ,
* in particular the stream operator
*
*
*/
Json::Value PID::getJSON() {
  Json::Value root;
  root["linear"] = _linear;
  root["intergral"] = _intergral;
  root["differential"] = _differential;
  root["error"] = Error;
  root["previous_error"] = old_error;
  return root;

}

/*
*
*Uses jsoncpp to parse input values  of variables
*
* json input of the format
*
*{
*   "linear" : 3,
*   "intergral" : 4,
*   "differential" : 2,
*   "error" : 0.3,
"   "previous_error": 0.4
*}
*
** Can be used in inherited classes to get arround ristrinction on friend methods access to internal veriables ,
* in particular the stream operator
*
*
*/


void PID::setJSON(Json::Value root) {

  _linear = root.get("linear","0").asDouble();
  _intergral = root.get("intergral","0").asDouble();
  _differential = root.get("differential","0").asDouble();
  Error = root.get("error","0").asDouble();
  old_error = root.get("previous_error","0").asDouble();
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
  stream << ob.getJSON();
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
std::istream &operator>>(std::istream& stream,PID &ob)
{
  Json::Value root;
  stream >> root;
  /*ob._linear = root.get("linear","0").asDouble();
  ob._intergral = root.get("intergral","0").asDouble();
  ob._differential = root.get("differential","0").asDouble();
  ob.Error = root.get("error","0").asDouble();
  ob.old_error = root.get("previous_error","0").asDouble();*/
  ob.setJSON(root);
  return stream;
}
