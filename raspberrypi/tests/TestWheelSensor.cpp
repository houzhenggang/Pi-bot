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



#include "TestInterInterface.hpp"
#include "../WheelSensor.h"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch/catch.hpp"
#include <thread>
#include <chrono>

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
  double diameter = 0.1;
  bool forward = true;
  int ticks = 20;
  int pin = 10;
  WheelSensor *test = new WheelSensor(pin,ticks);
  //Test the constructor
  SECTION( "Test get methods" )  {

    REQUIRE( test->pin() == 10 );
    REQUIRE( test->getDownPulse() == 0 );
    REQUIRE( test->getUpPulse() == 0 );
    REQUIRE( test->trig() == false);
    //test get
    REQUIRE( test->getVelocity() == 0 );
    REQUIRE( test->getDistance() == 0 );
  }
  SECTION( "Test update 1 second" )  {
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
    REQUIRE( test->getVelocity() == M_PI*diameter );

    for(int i = 0; i < ticks/4; i++) {
      pin10Risingfunc();
      pin10Fallingfunc();
    }
  }
  SECTION( "Test update 2 second and 10 ticks" )  {
    //simulate one revolution
    for(int i = 0; i < ticks/2; i++) {
      pin10Risingfunc();
      pin10Fallingfunc();
    }
    //wait one second
    std::this_thread::sleep_for(std::chrono::seconds(2));

    test->update(diameter,forward);

    //distance travelled by wheel is pi*d
    REQUIRE( test->getDistance() == (M_PI*diameter/2) );

    //one revolution per second or omega is 3.14 radians/s

    //velocity is 0.314/4 m/s
    REQUIRE( test->getVelocity() == (M_PI*diameter/4) );

  }
  SECTION( "Test update 2 second and 10 ticks" )  {
    forward = false;
    //simulate one revolution
    for(int i = 0; i < ticks/2; i++) {
      pin10Risingfunc();
      pin10Fallingfunc();
    }
    //wait one second
    std::this_thread::sleep_for(std::chrono::seconds(2));

    test->update(diameter,forward);

    //distance travelled by wheel is pi*d
    REQUIRE( test->getDistance() == -(M_PI*diameter/2) );

    //one revolution per second or omega is 3.14 radians/s

    //velocity is 0.314/4 m/s
    REQUIRE( test->getVelocity() == -(M_PI*diameter/4) );

  }
}
TEST_CASE( "Wheel sesnor test second update", "streem methods" ) {
  double diameter1 = 0.1;
  bool forward1 = true;
  int ticks1 = 20;
  int pin1 = 10;
  WheelSensor *test1 = new WheelSensor(pin1,ticks1);

 //One rotation in a second
  for(int i = 0; i < ticks1; i++) {
    pin10Risingfunc();
    pin10Fallingfunc();
  }
  //wait one second
  std::this_thread::sleep_for(std::chrono::seconds(1));
  test1->update(diameter1,forward1);

  //Two rotations in a second
  for(int i = 0; i < 2*ticks1; i++) {
    pin10Risingfunc();
    pin10Fallingfunc();
  }
  //wait one second
  std::this_thread::sleep_for(std::chrono::seconds(1));
  test1->update(diameter1,forward1);
  SECTION( " multiple update calls" )  {
    // Two rotations per second
    REQUIRE( test1->getVelocity() == M_PI*2*diameter1 );
    // A total of 3 rotations
    REQUIRE( test1->getDistance() == 3*M_PI*diameter1 );
  }

  SECTION( " reverse the wheel" )  {
    //One rotation in a second
    forward1 = false;
     for(int i = 0; i < ticks1; i++) {
       pin10Risingfunc();
       pin10Fallingfunc();
     }
     //wait one second
     std::this_thread::sleep_for(std::chrono::seconds(1));
     test1->update(diameter1,forward1);

    // Two rotations per second
    REQUIRE( test1->getVelocity() == -M_PI*diameter1 );
    // A total of 2 rotations
    REQUIRE((double) test1->getDistance() == Approx( 2*M_PI*diameter1 ).epsilon( 0.01 ) );
  }
}
  TEST_CASE( "Wheel Sensor stream", "streem methods" ) {
    //test the stream out method
    double diameter1 = 0.1;
    bool forward1 = true;
    int ticks1 = 20;
    int pin1 = 10;
    double diameter2 = 0.2;
    bool forward2 = false;
    int ticks2 = 10;
    int pin2 = 5;
    WheelSensor *test1 = new WheelSensor(pin1,ticks1);

    for(int i = 0; i < ticks1; i++) {
      pin10Risingfunc();
      pin10Fallingfunc();
    }
    //wait one second
    std::this_thread::sleep_for(std::chrono::seconds(1));
    test1->update(diameter1,forward1);


    WheelSensor *test2 = new WheelSensor(pin2,ticks2);
    SECTION( "Test stream out method" )  {
      std::stringstream sstream;
      Json::Value root;
      sstream << *test1;
      sstream >> root;
      cout << *test1;
      REQUIRE(root.get("pin","0") ==  pin1);
      REQUIRE(root.get("up-pulses","0") == ticks1 );
      REQUIRE(root.get("down-pulses","0") == ticks1 );
      REQUIRE(root.get("distance","0") == M_PI*diameter1 );
      REQUIRE(root.get("velocity","0") == M_PI*diameter1 );
      REQUIRE(root.get("omega","0") == 2*M_PI);
      REQUIRE(root.get("previous-distance","0") ==0);
      REQUIRE(root.get("previous-pulses","0") == 2*ticks1);
    }
    SECTION( "Test stream in method" )  {
      //Test the stream in mehtod
      Json::Value root;
      InterInterface *second = new InterInterface(10);
      std::stringstream ss;
      ss <<  "{ \"pin\" : 2 , \"up-pulses\" : 14, \"down-pulses\" : 13, \"distance\" : 5.3, \"velocity\" : 1.1, \"omega\" : 4.5, \"previous-distance\" : 5.0, \"previous-pulses\" : 15 , \"ticks\" : 27   }";
      ss << std::endl;

      ss >> *test2;

      ss << *test2;

      ss >> root;
      REQUIRE(root.get("ticks","0") == 27 );
      REQUIRE(root.get("pin","0") == 2 );
      REQUIRE(root.get("up-pulses","0") == 14 );
      REQUIRE(root.get("down-pulses","0") == 13 );
      REQUIRE(root.get("distance","0") == 5.3 );
      REQUIRE(root.get("velocity","0") == 1.1 );
      REQUIRE(root.get("omega","0") ==4.5 );
      REQUIRE(root.get("previous-distance","0").asDouble() == 5.0 );
      REQUIRE(root.get("previous-pulses","0") == 15 );

    }
    SECTION( "Test stream serialisation " )  {
      //test serialisation in jason
      std::stringstream ss;


      ss << *test1;
      ss >> *test2;

      REQUIRE( test2->pin() == pin1 );
      REQUIRE( test2->getDownPulse() == ticks1 );
      REQUIRE( test2->getUpPulse() == ticks1);
      REQUIRE( test2->trig() == true);
      //test get
      REQUIRE( test2->getVelocity() == M_PI*diameter1 );
      REQUIRE( test2->getDistance() == M_PI*diameter1 );


    }
  }
