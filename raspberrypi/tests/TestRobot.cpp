/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 15-11-2016
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


#include "../Robot.h"
#include "sstream"
#include <time.h>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch/catch.hpp"


using namespace std;

TEST_CASE( "Robot object", "test methods" ) {
  //Test the constructor
  Robot *test = new Robot();

  int sensorPinLeft = 12;
  int sensorPinRight = 11;

  int forwardLeftpin = 9;
  int forwardRightpin = 10;

  int backwardLeftpin = 6;
  int backwardRightpin = 5;

  //Have to tell the system what pins are attached to the left and right wheel sensors
  sensorPin[forwardLeftpin] = sensorPinLeft;
  sensorPin[backwardLeftpin] = sensorPinLeft;
  //Have to tell the system how many ticks are on each of the wheel sensors
  ticks[sensorPinLeft] =20;

  sensorPin[forwardRightpin] = sensorPinRight;
  sensorPin[backwardRightpin] = sensorPinRight;
  ticks[sensorPinRight] =20;
  //test get

  SECTION("test get methods") {
    REQUIRE(test->getX() == 0);
    REQUIRE(test->getY() == 0);
    REQUIRE(test->getAngle() == 0);
    REQUIRE(test->getTargetX() == 0);
    REQUIRE(test->getTargetY() == 0);
    REQUIRE(test->getTargetAngle() == 0);

  }

  SECTION("test get methods") {
	//std::thread t1(std::bind(test->heartbeat,test));


	test->drive(50);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    test->stop();
    cout<<*test;
    delete test;







    REQUIRE(test->getX() != 0);

  }
}
