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

#include "TractionControl.h"

TractionControl::TractionControl(double maxchange)
{
   _maxchange=maxchange;
   _prevfreq=0;
}

double TractionControl::getMaxChange()
{
    return _maxchange;
}
void TractionControl::setMaxChange(double maxchange)
{
    _maxchange=maxchange;
}
double TractionControl::modify(double frequency)
{

    if(frequency - _prevfreq > _maxchange)
    {
       frequency =  _prevfreq+_maxchange;
    }
    if(frequency - _prevfreq < -_maxchange)
    {
        frequency =  _prevfreq-_maxchange;
    }
    _prevfreq = frequency;
    return frequency;

}
