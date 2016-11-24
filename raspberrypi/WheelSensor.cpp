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

#include "WheelSensor.hpp"

WheelSensor::WheelSensor(int pin, int ticks) :
		InterInterface(pin) {
	pinMode(pin, OUTPUT);

	_previousDistance = 0;
	_distance = 0;
	_ticks = ticks;
	_omega = 0;
	_prevPulses = 0;
	_velocity = 0;
	_timeLastUpdate = std::chrono::high_resolution_clock::now();
}

/*
 *
 *Return the total distance travelled by the wheel
 *
 */

double WheelSensor::getDistance() {
	return _distance;
}

/*
 *
 * Get the velocity of the edge of the wheel
 *
 */

double WheelSensor::getVelocity() {
	return _velocity;

}

/*
 *
 *Update the state of the wheel
 *
 */
void WheelSensor::update(double diameter, bool forward) {
	_previousDistance = _distance;

	//Find out the distance the wheel has turned from the pulses;
	double cnst = M_PI * diameter / (2 * _ticks);

	//Avarage the pules to get a more accurate figure
	unsigned long pulses = (_upPulse + _downPulse);

	//change in the pulses since last time
	unsigned int deltaPulses = pulses - _prevPulses;
	_prevPulses = pulses;

	if (forward) {
		_distance = _distance + cnst * deltaPulses;
	} else {
		_distance = _distance - cnst * deltaPulses;
	}
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast
			< std::chrono::milliseconds > (now - _timeLastUpdate);
	//work out the rotational freqency in radians per second;
	double timespan = time_span.count();
	double f = ((double) deltaPulses) / (2 * _ticks * timespan);

	if (forward)
		_omega = 2 * M_PI * f;
	else
		_omega = -2 * M_PI * f;
	_velocity = _omega * diameter / 2;
	_timeLastUpdate = now;
}
Json::Value WheelSensor::getJSON() {
	Json::Value root;
	root["ticks"] = _ticks;
	root["distance"] = _distance;
	root["velocity"] = _velocity;
	root["previous-distance"] = _previousDistance;
	root["omega"] = _omega;
	root["previous-pulses"] = _prevPulses;
	root["previous-pulse-time"] = std::chrono::duration_cast
			< std::chrono::microseconds
			> (_timeLastUpdate.time_since_epoch()).count();
	//due to being in a potected method can access protected variables of inhertited class
	//may be better to write a method in the inhertited class that returns a json object
	root["pin"] = _pin;
	root["up-pulses"] = _upPulse;
	root["down-pulses"] = _downPulse;
	return root;

}
void WheelSensor::setJSON(Json::Value root) {
	if (root.isMember("ticks"))
		_ticks = root.get("ticks", 0).asInt();
	if (root.isMember("distance"))
		_distance = root.get("distance", 0).asDouble();
	if (root.isMember("velocity"))
		_velocity = root.get("velocity", 0).asDouble();
	if (root.isMember("previous-distance"))
		_previousDistance = root.get("previous-distance", 0).asDouble();
	if (root.isMember("omega"))
		_omega = root.get("omega", 0).asDouble();
	if (root.isMember("previous-pulses"))
		_prevPulses = root.get("previous-pulses", 0).asUInt64();
	if (root.isMember("previous-pulse-time")) {
		long t = root.get("previous-pulse-time", 0).asInt64();
		std::chrono::milliseconds ms { t };
		_timeLastUpdate = std::chrono::high_resolution_clock::time_point(ms);
	}

	//due to being in a potected method can access protected variables of inhertited class
	//may be better to write a method in the inhertited class that returns a json object
	if (root.isMember("pin"))
		_pin = root.get("pin", 0).asInt();
	if (root.isMember("up-pulses"))
		_upPulse = root.get("up-pulses", 0).asInt();
	if (root.isMember("down-pulses"))
		_downPulse = root.get("down-pulses", 0).asInt();

}

ostream& operator<<(ostream& stream, WheelSensor &ob) {
	Json::Value root = ob.getJSON();
	stream << root;
	return stream;
}
istream& operator>>(istream& stream, WheelSensor &ob) {
	Json::Value root;
	stream >> root;
	ob.setJSON(root);
	return stream;

}
