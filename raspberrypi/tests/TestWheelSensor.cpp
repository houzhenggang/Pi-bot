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
#include "../WheelSensor.hpp"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch/catch.hpp"
#include <thread>
#include <chrono>

//const double M_PI = 3.14159265359;

TEST_CASE( "WheelSensor constructor", "test methods" ) {
  //Test the constructor
  SECTION( "Test constructor" )  {

    WheelSensor *test = new WheelSensor();
    //test get
    REQUIRE( test->getDistance() == 0 );
    REQUIRE( test->getVelocity() == 0 );
    REQUIRE( test->getDiameter() == 0 );


  }
}

TEST_CASE( "WheelSensor get and set update methods", "test methods" ) {
  double diameter = 0.3;
  WheelSensor *test = new WheelSensor(3,0.3);
  test->setVelocity(10);
  test->setDistance(20);
  test->setOmega(40);
  //Test the constructor
  SECTION( "Test get methods" )  {

    REQUIRE( test->getDiameter() == 0.3 );
    //test get
    REQUIRE( test->getVelocity() == 10 );
    REQUIRE( test->getDistance() == 20 );
    REQUIRE( test->getOmega() == 40 );
  }


}
  TEST_CASE( "Wheel Sensor stream", "streem methods" ) {
    //test the stream out method

    WheelSensor *test = new WheelSensor(2,0.4);
    test->setVelocity(15);
    test->setDistance(22);
    test->setOmega(44);

    SECTION( "Test stream out method" )  {
      std::stringstream sstream;
      Json::Value root;
      sstream << *test;
      sstream >> root;
      std::cout << *test;

      REQUIRE(root.get("distance","0") == 22 );
      REQUIRE(root.get("velocity","0") == 15 );
      REQUIRE(root.get("omega","0") == 44);
    }
    SECTION( "Test stream in method" )  {
      //Test the stream in mehtod
      Json::Value root;

      std::stringstream ss;
      ss <<  "{ \"distance\" : 2 , \"velocity\" : 14, \"omega\" : 13, \"diameter\" : 5.3, \"previous-pulse-time\" : 120000   }";
      ss << std::endl;

      ss >> *test;

      ss << *test;

      ss >> root;
      REQUIRE(root.get("distance","0") == 2 );
      REQUIRE(root.get("velocity","0") == 14 );
      REQUIRE(root.get("omega","0") == 13 );
      REQUIRE(root.get("diameter","0") == 5.3 );
      REQUIRE(root.get("previous-pulse-time","0") == 120000 );

    }
    SECTION( "Test stream serialisation " )  {
      //test serialisation in jason
      std::stringstream ss;


      ss << *test;
      WheelSensor *test2 = new WheelSensor(4,0.56);
      ss >> *test2;

      REQUIRE( test2->getDistance() == 2 );
      REQUIRE( test2->getVelocity() == 14 );
      REQUIRE( test2->getDiameter() == 5.3);
      REQUIRE( test2->getOmega() == 13);


    }
  }
