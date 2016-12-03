/**
 * @Author: Kieran Wyse
 * @Date:   28-10-2016
 * @Email:  kieranwyse@gmail.com
 * @Project: Pi-Bot
 * @Last modified by:   Kieran Wyse
 * @Last modified time: 06-11-2016
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

#include "WheelEncoder.hpp"

WheelEncoder::WheelEncoder(int pin, int ticks, double diameter,int millisecond_updates) :
		InterInterface(pin), WheelSensor(millisecond_updates,diameter) {
	pinMode(pin, OUTPUT);
	_ticks = ticks;
	_prevPulses = 0;
	_forward = true;
}


/*
*
* The wheel sensor is forward_mtx
*
*/

bool WheelEncoder::getForward() {
 forward_mtx.lock();
 double forward = _forward;
 forward_mtx.unlock();
 return forward;

}

/*
*
*Set the wheel sensor to forward , true or backwards false
*
*/

void WheelEncoder::setForward(bool forward) {
 forward_mtx.lock();
 _forward = forward;
 forward_mtx.unlock();
}

/*
 *
 *Update the state of the wheel
 *
 */
void WheelEncoder::update() {

	//Find out the distance the wheel has turned from the pulses;
	double cnst = M_PI * getDiameter() / (2 * _ticks);

	//Avarage the pules to get a more accurate figure
	unsigned long pulses = (_upPulse + _downPulse);

	//change in the pulses since last time
	unsigned int deltaPulses = pulses - _prevPulses;
	_prevPulses = pulses;

	if (getForward()) {
		setDistance(getDistance() + cnst * deltaPulses);
	} else {
		setDistance(getDistance() - cnst * deltaPulses);
	}

	double f = ((double) deltaPulses) / (2 * _ticks * getDuration());

	if (getForward())
		setOmega(2 * M_PI * f);
	else
		setOmega(-2 * M_PI * f);
	setVelocity(getOmega() * getDiameter() / 2);
}
Json::Value WheelEncoder::getJSON() {
	Json::Value root;

	root["distance"] = getDistance();
	root["velocity"] = getVelocity();
	root["omega"] = getOmega();
	root["diameter"] = getDiameter();

	root["pin"] = pin();
  root["up-pulses"] = getUpPulse();
  root["down-pulses"]= getDownPulse();

	root["ticks"] = _ticks;
	root["forward"] = getForward();
	root["previous-pulses"] = _prevPulses;


	/*//due to being in a potected method can access protected variables of inhertited class
	//may be better to write a method in the inhertited class that returns a json object
	root["pin"] = _pin;
	root["up-pulses"] = _upPulse;
	root["down-pulses"] = _downPulse;*/
	return root;

}
void WheelEncoder::setJSON(Json::Value root) {
	WheelSensor::setJSON(root);
	InterInterface::setJSON(root);
	if (root.isMember("ticks"))
		_ticks = root.get("ticks", 0).asInt();
	if (root.isMember("forward"))
		setForward(root.get("forward", true).asBool());
	if (root.isMember("previous-pulses"))
		_prevPulses = root.get("previous-pulses", 0).asUInt64();

}

std::ostream& operator<<(std::ostream& stream, WheelEncoder &ob) {
	Json::Value root = ob.getJSON();
	stream << root;
	return stream;
}
std::istream& operator>>(std::istream& stream, WheelEncoder &ob) {
	Json::Value root;
	stream >> root;
	ob.setJSON(root);
	return stream;

}
