/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 30-10-2016
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

#include "PIDAngle.hpp"
#include <cmath>

PIDAngle::PIDAngle(double linear,double intergral, double differential) : PID(linear,intergral,differential) {
}


double PIDAngle::next(double actual,double target) {

   double e = target-actual;
   double edas = atan2(sin(e),cos(e));



   //differentual term
   double ed = edas - old_error;


   //p i d regulator
   double result = _linear*edas+_differential*ed+_intergral*Error;

   Error = edas + Error;
   old_error = edas;
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

std::ostream &operator<<(std::ostream& stream, PIDAngle &ob)
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
std::istream &operator>>(std::istream& stream,PIDAngle &ob)
{
  Json::Value root;
  stream >> root;
  ob.setJSON(root);
  return stream;
}
