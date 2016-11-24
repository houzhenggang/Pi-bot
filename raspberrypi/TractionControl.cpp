/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 08-11-2016
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

#include "TractionControl.hpp"

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
    //frequency is not modified if the maxchange variable is set to 0
    if(_maxchange) {
      if(frequency - _prevfreq > _maxchange) {
         frequency =  _prevfreq+_maxchange;
      }
      if(frequency - _prevfreq < -_maxchange) {
          frequency =  _prevfreq-_maxchange;
      }
    }

    _prevfreq = frequency;
    return frequency;

}

Json::Value TractionControl::getJSON() {
  Json::Value root;
  root["max-change"] = _maxchange;
  return root;
}


void TractionControl::setJSON(Json::Value root) {
  if(root.isMember("max-change"))
    _maxchange = root.get("max-change",0).asDouble();
}

/*
*
*Uses jsoncpp to outputt stream of  values  of variables
*
* stream output of the format
*
*{
*   "max-change" : 3,
*}
*
*/

std::ostream &operator<<(std::ostream& stream, TractionControl &ob)
{
  Json::Value root = ob.getJSON();
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
*   "max-change" : 3,
*}
*
*/
std::istream &operator>>(std::istream& stream,TractionControl &ob)
{
  Json::Value root;
  stream >> root;
  ob.setJSON(root);
  return stream;
}
