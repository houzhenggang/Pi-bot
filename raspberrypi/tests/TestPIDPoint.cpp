/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 09-11-2016
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

#include "../PIDPoint.h"
#include "../json/json.h"
#include "sstream"
#include <iomanip>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch/catch.hpp"

double internal = 0;
double testsystem(double input) {
  internal = 0.5*input+internal;
  return internal;
}



using namespace std;

TEST_CASE( "PID object", "test methods" ) {

  PIDPoint *test = new PIDPoint(50,3,5);
  PIDPoint *second = new PIDPoint(0,0,0);
  stringstream ss;

  //Test the constructor
  SECTION("Test constructor ") {
    //test get
    REQUIRE( test->getLinear() == 50 );
    REQUIRE( test->getIntergral() == 3 );
    REQUIRE( test->getDifferential() == 5 );

  }
  //test the stream out method
  SECTION("Test stream out ") {
    Json::Value root;
    ss << *test;
    ss >> root;

    REQUIRE(root.get("linear","0") == 50 );
    REQUIRE(root.get("intergral","0") == 3 );
    REQUIRE(root.get("differential","0") == 5 );
    REQUIRE(root.get("error","0") == 0 );
    REQUIRE(root.get("previous_error","0") == 0 );
  }

  SECTION("Test stream in ") {
    //Test the stream in mehtod
    root.clear();

    ss <<  "{ \"linear\" : 20 , \"differential\" : 1, \"intergral\" : 3, \"error\" : 3, \"previous_error\" : 5  }";
    ss << std::endl;

    ss >> *second;

    ss << *second;

    ss >> root;
    REQUIRE(root.get("linear","0") == 20 );
    REQUIRE(root.get("differential","0") == 1 );
    REQUIRE(root.get("intergral","0") == 3 );
  }
  SECTION("Test serialisation ") {

    //test serialisation in jason
    ss << *second;
    ss >> *test;

    REQUIRE( test->getLinear() == 20 );
    REQUIRE( test->getDifferential() == 1 );
    REQUIRE( test->getIntergral() == 3 );
  }

  SECTION("Test pid next") {
    //test the pid achives the target for a systemPoint *point = new Point(100,-50);
    Point *target = new Point(100,-50);
    Point *value = new Point(0,0);
    double angleValue = 0;
    PIDAngle *pidAngle = new PIDAngle(0.2,0.02,0.02);

    test->setLinear(0.3);
    test->setDifferential(0.02);
    test->setIntergral(0.02);
    std::cout << "Target is:" << target<< std::endl;

    /*for(int i = 0; i < 100; i++) {
      input = test->next(value,target);


      double xdiff= targets->getX()-value->getX();
      double ydiff= targets->getY()-value->getY();

       double target_angle = atan2(ydiff,xdiff);
       angleinput = test->next(angleValue,target_angle);




      value = testsystem(input);
      angleValue = 0.02*angleinput*angleinput;


      //std::cout <<" "<<std::setprecision(2)<<value<<std::endl;
    }
    cout <<"value is"<<* std::endl;
    //value should be close to the target with in 2 decimal places
    value = round(value);

    REQUIRE(value == target );*/
  }
}
