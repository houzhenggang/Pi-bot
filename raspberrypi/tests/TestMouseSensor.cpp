/**
* @Author: Kieran Wyse
* @Date:   02-11-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 07-11-2016
* @License: License: GPL v3
#     This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



//#include "TestInterInterface.hpp"
#include "../MouseSensor.hpp"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch/catch.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>




TEST_CASE( "WheelSensor constructor", "test methods" ) {
  //Test the constructor
  SECTION( "Test constructor" )  {
	std::string s = "/dev/input/event4";

    MouseSensor *test = new MouseSensor(s);
    //test get
    REQUIRE( test->getDistance() == 0 );
    REQUIRE( test->getVelocity() == 0 );
    REQUIRE( test->getOmega() == 0 );
  }
}
/*
 *
 *
 *  Testing by sending mouse information directly via mouse events use swmouse as a dummy mouse
 *
 *	Asume that the mouse has a dpi of 400;
 */

TEST_CASE( "WheelSensor get and set update methods", "test methods" ) {
	ofstream myfile;
	  myfile.open ("/dev/swmouse");
	  //One inch in x direction
	  myfile << "x 400";
	  myfile.close();

}
