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

#include "PID.h"

#ifndef PID_ANGLE_H
#define PID_ANGLE_H

class PIDAngle : public PID
{
  public:
  PIDAngle(double linear,double intergral, double differential);
  double next(double angle,double targety);
  friend std::ostream& operator<<(std::ostream& stream,PIDAngle &ob);
  friend std::istream& operator>>(std::istream& stream,PIDAngle &ob);
  private:

};

#endif
