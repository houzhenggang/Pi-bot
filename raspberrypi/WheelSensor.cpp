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

#ifndef WheelSENSOR_CPP
#define WheelSENSOR_CPP



WheelSensor::WheelSensor(int millisecond_updates, double diameter) {

  _distance = 0;
  _omega = 0;
  _velocity = 0;
  _diameter = diameter;
  _millisecond_updates = millisecond_updates;

  /*using namespace std::chrono;
  microseconds micros = duration_cast< microseconds >(system_clock::now().time_since_epoch());

  using namespace std;
  _timeLastUpdate = ((double)micros.count()/1000000);*/

  _timeLastUpdate  = std::chrono::high_resolution_clock::now();

}
/*
*Start the sensor listening
*/
void WheelSensor::start() {

  running_mtx.lock();
  if(!_running) {
    _running = true;
    std::thread t2(std::bind(&WheelSensor::run, this));
    t1 = std::move(t2);
  }
  running_mtx.unlock();
}
/*
*Stop the sensor listening
*/
void WheelSensor::stop() {
  running_mtx.lock();
  _running = false;
  running_mtx.unlock();
  if(t1.joinable())
  t1.join();
  //TODO turn this code into c++ type file io
}

/*
*
* The wheel sensor is forward_mtx
*
*/

bool WheelSensor::getForward() {
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

void WheelSensor::setForward(bool forward) {
  forward_mtx.lock();
  _forward = forward;
  forward_mtx.unlock();
}


/*
*
*Return the total distance travelled by the wheel
*
*/

double WheelSensor::getDistance() {
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

double WheelSensor::getVelocity() {
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

double WheelSensor::getOmega() {
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

double WheelSensor::getDiameter() {
  omega_mtx.lock();
  double diameter = _diameter;
  omega_mtx.unlock();
  return diameter;

}

/*
*
* Set the diameter of the edge of the wheel
*
*/

void WheelSensor::setDiameter(double diameter) {
  diameter_mtx.lock();
  _diameter = diameter;
  diameter_mtx.unlock();
}




/*
*
*Set the total distance travelled by the wheel
*
*/

void WheelSensor::setDistance(double distance) {
  distance_mtx.lock();
  _distance = distance;
  distance_mtx.unlock();
}

/*
*
* Set the velocity of the edge of the wheel
*
*/

void WheelSensor::setVelocity(double velocity) {
  velocity_mtx.lock();
  _velocity = velocity;
  velocity_mtx.unlock();
}

/*
*
* Set the omega  of the wheel
*
*/

void WheelSensor::setOmega(double omega) {
  omega_mtx.lock();
  _omega = omega;
  omega_mtx.unlock();
}


/*
*
* robot running method
*
*/

void WheelSensor::run() {
  running_mtx.lock();
  bool running = _running;
  running_mtx.unlock();

  while(running) {

    running_mtx.lock();
    running = _running;
    running_mtx.unlock();
    update();
    std::this_thread::sleep_for(std::chrono::milliseconds(_millisecond_updates));
  }
}

double WheelSensor::getDuration() {
  auto now = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_span = std::chrono::duration_cast
  < std::chrono::microseconds > (now - _timeLastUpdate);
  //work out the rotational freqency in radians per second;
  double timespan = time_span.count();
  _timeLastUpdate = now;
  return timespan;
}


Json::Value WheelSensor::getJSON() {
  Json::Value root;
  root["distance"] = getDistance();
  root["velocity"] = getVelocity();
  root["omega"] = getOmega();
  root["diameter"] = getDiameter();
  root["forward"] = getForward();
  update_mtx.lock();
  std::chrono::microseconds micros = std::chrono::duration_cast< std::chrono::microseconds >( _timeLastUpdate.time_since_epoch());
  root["previous-pulse-time"] =micros.count();
  update_mtx.unlock();
  return root;

}
void WheelSensor::setJSON(Json::Value root) {
  if (root.isMember("distance"))
  setDistance(root.get("distance", 0).asDouble());
  if (root.isMember("velocity"))
  setVelocity(root.get("velocity", 0).asDouble());
  if (root.isMember("omega"))
  setOmega(root.get("omega", 0).asDouble());
  if (root.isMember("diameter"))
  setDiameter(root.get("diameter", 0).asDouble());
  if (root.isMember("forward"))
  setForward(root.get("forward", true).asBool());
  if (root.isMember("previous-pulse-time")) {
    long micros = root.get("previous-pulse-time", 0).asUInt64();

    const std::chrono::microseconds  duration_microseconds = std::chrono::microseconds(micros);
    update_mtx.lock();
    _timeLastUpdate = std::chrono::high_resolution_clock::time_point(duration_microseconds);
    update_mtx.unlock();
  }

}

std::ostream& operator<<(std::ostream& stream,WheelSensor &ob) {
  Json::Value root = ob.getJSON();
  stream << root;
  return stream;
}
std::istream& operator>>(std::istream& stream,WheelSensor  &ob) {
  Json::Value root;
  stream >> root;
  ob.setJSON(root);
  return stream;

}


WheelSensor::~WheelSensor() {
  stop();
}

#endif
