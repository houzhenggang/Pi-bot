
/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 29-10-2016
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
#include "PID.h"
#include <cmath>

/*
*
*
*
*/
PIDPoint::PIDPoint(double linear,double intergral, double differential) :  PID(linear,intergral,differential) {
}
double PIDPoint::next(Point *point,Point *target) {

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
