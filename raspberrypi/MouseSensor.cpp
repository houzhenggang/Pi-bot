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

/*
 * This class models a mouse used to get the position of a robot.
 * The mouse will be placed near to where the wheel is in contact with the floor
 * It should measure both the distance travelled and the velocity.
 *
 * By knowing the distance between the mouse sensors placed at each wheel it is possible
 * to work out the angle that the robot is at.
 *
 * When moving in a forward motion the rotational velocity of the wheels is proportional to the
 * velocity as measured by the mouse.
 *
 * TODO when the robot is turning there will be a slight discrepancy due to the wheel having longer or
 * shorter to travel. This is still to be accounted for.
 */

MouseSensor::MouseSensor(std::string path ,double diameter, int millisecond_updates)
  : WheelSensor(millisecond_updates,diameter){

	_path = path;


//TODO turn this code into c++ type file io
	if ((_fd = open(path.c_str(), O_RDWR | O_NOCTTY | O_NDELAY)) == -1) {
		std::cerr << "error opening device::"<< path <<std::endl;
		exit(EXIT_FAILURE);
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
  //clear the structure
  std::memset(&_ie,0,sizeof(struct input_event));
  //TODO turn this code into c++ type file io
	if (read(_fd, &_ie, sizeof(struct input_event))) {
		if (_ie.type == EV_REL) {
			if (_ie.code == REL_X) {
				deltaDistance += _ie.value;
        int value = _ie.value;
        std::cout <<"type:"<<_ie.type<<" code:"<<_ie.code <<" value:"<<value;

      	double deltaTime = 	getDuration();

        setDistance(previousDistance+deltaDistance);

      	setVelocity(deltaDistance / deltaTime);
      	setOmega(2 * getVelocity() / getDiameter());
			}
		}
	} else {
		std::cerr << "error opening device "<<std::endl;
	}

  /*//First two values refer to the time of the event
  //First value time in seconds
  fh.read(&_ie.time.tv_sec, sizeof(_ie.time.tv_sec));
  //Second value time in microseconds
  fh.read(&_ie.time.tv_usec, sizeof(_ie.time.tv_usec));
  fh.read(&_ie.type, sizeof(_ie.type));
  fh.read(&_ie.code, sizeof(_ie.code));
  fh.read(&_ie.value, sizeof(_ie.value));
  if (_ie.type == EV_REL) {
    if (_ie.code == REL_X) {
      deltaDistance += _ie.value;
    }
  }*/

}
Json::Value MouseSensor::getJSON() {
	Json::Value root;
  Json::Value ws = WheelSensor::getJSON();
  std::stringstream ss;
  ss << ws;
  ss >> root;

	path_mtx.lock();
	root["path"] = _path;
	path_mtx.unlock();
	return root;

}
void MouseSensor::setJSON(Json::Value root) {
  WheelSensor::setJSON(root);
  path_mtx.lock();
	if (root.isMember("path")) {
		std::string path = root.get("path", "").asString();
		if ((_fd = open(path.c_str(), O_RDONLY)) == -1) {
			std::cerr << "error opening device::"<< path <<std::endl;
		} else {
			_path = path;
		}

	}
  path_mtx.unlock();
}

std::ostream& operator<<(std::ostream& stream,MouseSensor &ob) {
  Json::Value root = ob.getJSON();
  stream << root;
  return stream;
}
std::istream& operator>>(std::istream& stream,MouseSensor  &ob) {
    Json::Value root;
    stream >> root;
    ob.setJSON(root);
    return stream;

}

MouseSensor::~MouseSensor() {
	stop();
  if (close(_fd) == -1) {
  		std::cerr << "error closing device::"<< _path <<std::endl;
  		exit(EXIT_FAILURE);
  	}

}

#endif
