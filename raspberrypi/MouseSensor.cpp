/**
 * @Author: Kieran Wyse
 * @Date:   22-11-2016
 * @Email:  kieranwyse@gmail.com
 * @Project: Pi-Bot
 * @Last modified by:   Kieran Wyse
 * @Last modified time: 22-11-2016
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

 #ifndef MOUSESENSOR_CPP
 #define MOUSESENSOR_CPP

#include "MouseSensor.hpp"

MouseSensor::MouseSensor(std::string path ,double diameter, int millisecond_updates) {

	_distance = 0;
	_omega = 0;
	_diameter = diameter;
	_velocity = 0;
	_path = path;
	_millisecond_updates = millisecond_updates;
	_timeLastUpdate = std::time(nullptr);//time since epoch

	if ((_fd = open(path.c_str(), O_RDONLY)) == -1) {
		std::cerr << "error opening device::"<< path <<std::endl;
		exit(EXIT_FAILURE);
	}
	std::thread t2(std::bind(&MouseSensor::run, this));
	t1 = std::move(t2);
}

/*
 *
 *Return the total distance travelled by the wheel
 *
 */

double MouseSensor::getDistance() {
	distance_mtx.lock();
	double distance = _distance;
	distance_mtx.unlock();
	return distance;
}

/*
 *
 * Get the velocity of the edge of the wheel
 *
 */

double MouseSensor::getVelocity() {
	velocity_mtx.lock();
	double velocity = _velocity;
	velocity_mtx.unlock();
	return velocity;

}

/*
 *
 * Get the omega  of the wheel
 *
 */

double MouseSensor::getOmega() {
	omega_mtx.lock();
	double omega = _omega;
	omega_mtx.unlock();
	return omega;

}

/*
 *
 * Get the diameter  of the wheel
 *
 */

double MouseSensor::getDiameter() {
	omega_mtx.lock();
	double diameter = _diameter;
	omega_mtx.unlock();
	return diameter;

}

/*
 *
 *Set the total distance travelled by the wheel
 *
 */

void MouseSensor::setDistance(double distance) {
	distance_mtx.lock();
	_distance = distance;
	distance_mtx.unlock();
}

/*
 *
 * Set the velocity of the edge of the wheel
 *
 */

void MouseSensor::setVelocity(double velocity) {
	velocity_mtx.lock();
	_velocity = velocity;
	velocity_mtx.unlock();
}

/*
 *
 * Set the omega  of the wheel
 *
 */

void MouseSensor::setOmega(double omega) {
	omega_mtx.lock();
	_omega = omega;
	omega_mtx.unlock();
}


/*
 *
 * robot running method
 *
 */

void MouseSensor::run() {
	running_mtx.lock();
	bool running = _running;
	running_mtx.unlock();
	while(running) {
		update();
		std::this_thread::sleep_for(std::chrono::milliseconds(_millisecond_updates));
	}
}

/*
 *
 *Update the state of the wheel
 *
 */
void MouseSensor::update() {
	double previousDistance = getDistance();
	double deltaDistance = 0;

	if (read(_fd, &_ie, sizeof(struct input_event))) {

		if (_ie.type == EV_REL) {
			if (_ie.code == REL_X) {
				deltaDistance += _ie.value;
			}
		}
	} else {
		std::cerr << "error opening device::"<< _path <<std::endl;
	}

	double previous_time = _timeLastUpdate;
	_timeLastUpdate = _ie.time.tv_sec;

	double deltaTime = _ie.time.tv_sec - previous_time;

	setVelocity(deltaDistance / deltaTime);
	setOmega(2 * getVelocity() / getDiameter());
}
Json::Value MouseSensor::getJSON() {
	Json::Value root;
	root["distance"] = getDistance();
	root["velocity"] = getVelocity();
	root["omega"] = getOmega();
	root["diameter"] = getDiameter();
	update_mtx.lock();
	root["previous-pulse-time"] = _timeLastUpdate;
	update_mtx.unlock();
	path_mtx.lock();
	root["path"] = _path;
	path_mtx.unlock();
	return root;

}
void MouseSensor::setJSON(Json::Value root) {
	if (root.isMember("distance"))
		setDistance(root.get("distance", 0).asDouble());
	if (root.isMember("velocity"))
		setVelocity(root.get("velocity", 0).asDouble());
	if (root.isMember("omega"))
		setOmega(root.get("omega", 0).asDouble());
	if (root.isMember("previous-pulse-time"))
		_timeLastUpdate = root.get("previous-pulse-time", 0).asDouble();
	if (root.isMember("path")) {
		std::string path = root.get("path", "").asString();
		if ((_fd = open(path.c_str(), O_RDONLY)) == -1) {
			std::cerr << "error opening device::"<< path <<std::endl;
		} else {
			_path = path;
		}

	}

}

/*ostream& operator<<(ostream& stream, MouseSensor &ob) {
	Json::Value root = ob.getJSON();
	stream << root;
	return stream;
}
istream& operator>>(istream& stream, MouseSensor &ob) {
	Json::Value root;
	stream >> root;
	ob.setJSON(root);
	return stream;

}*/

MouseSensor::~MouseSensor() {
	running_mtx.lock();
	_running = false;
	running_mtx.unlock();
	if(t1.joinable())
		t1.join();

}

#endif
