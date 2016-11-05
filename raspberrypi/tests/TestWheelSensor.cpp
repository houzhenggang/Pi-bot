/**
* @Author: Kieran Wyse
* @Date:   02-11-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 05-11-2016
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



#include "TestInterInterface.hpp"
#include "../WheelSensor.h"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch/catch.hpp"
#include <thread>

const double M_PI = 3.14159265359;

TEST_CASE( "WheelSensor constructor", "test methods" ) {
  //Test the constructor
  SECTION( "Test constructor" )  {

    WheelSensor *test = new WheelSensor(10,20);
    //test get
    REQUIRE( test->pin() == 10 );
    REQUIRE( test->getDownPulse() == 0 );
    REQUIRE( test->getUpPulse() == 0 );
    REQUIRE( test->trig() == false);

  }
}

TEST_CASE( "WheelSensor get and set update methods", "test methods" ) {
  //Test the constructor
  SECTION( "Test update" )  {
    double diameter = 0.1;
    bool forward = true;
    int ticks = 20;
    int pin = 10;
    WheelSensor *test = new WheelSensor(pin,ticks);
    REQUIRE( test->pin() == 10 );
    REQUIRE( test->getDownPulse() == 0 );
    REQUIRE( test->getUpPulse() == 0 );
    REQUIRE( test->trig() == false);
    //test get
    REQUIRE( test->getVelocity() == 0 );
    REQUIRE( test->getDistance() == 0 );

    //simulate one revolution
    for(int i = 0; i < ticks; i++) {
      pin10Risingfunc();
      pin10Fallingfunc();
    }
    //wait one second
    std::this_thread::sleep_for(std::chrono::seconds(1));

    test->update(diameter,forward);



    //distance travelled by wheel is pi*d
    REQUIRE( test->getDistance() == M_PI*diameter );

    //one revolution per second or omega is 3.14 radians/s

    //velocity is 0.314 m/s

    cout << *test;
    REQUIRE( test->getVelocity() == M_PI*diameter );




  }
}
