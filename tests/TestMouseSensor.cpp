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
#include "MouseSensor.hpp"
#include "wiringPIDummy.hpp"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch/catch.hpp"






TEST_CASE( "WheelEncoder", "test methods" ) {
  std::string s = "/dev/input/event7";

  MouseSensor *test = new MouseSensor(s);


  //test get
  //Test the constructor
  SECTION( "Test get methods" )  {


    REQUIRE( test->getDistance() == 0 );
    REQUIRE( test->getVelocity() == 0 );
    REQUIRE( test->getOmega() == 0 );
    delete test;
  }
}
/*
*
*
*  Testing by sending mouse information directly via mouse events use swmouse as a dummy mouse
*
*	Asume that the mouse has a dpi of 400;
*/


TEST_CASE( "WheelEncoder  update static test", "test mouse event " ) {
  std::string line;
  //This file has detials of the input devices attached to the system
  std::ifstream myfile ("/proc/bus/input/devices");
  std::string device;
  //Guess that the last mouse added is the mouse that is used to test
  if (myfile.is_open()) {
    for(std::string word; myfile >> word; )
    if(word.compare(0,14,"Handlers=mouse") == 0) {
      myfile >> word;
      device = word;
    }
    myfile.close();
  } else std::cerr << "Unable to open file" << std::endl;

  std::string s = "/dev/input/"+ device;
  MouseSensor *test = new MouseSensor(s,0.1,1);

  //Mouse has 800 dpi in this case
  test->start();
  writeEvent(0,1,s);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  writeEvent(0,799,s);


  std::cout<<*test;
  REQUIRE( test->getDistance() == 0.0254 );
  REQUIRE( test->getVelocity() == Approx( 0.0254 ).epsilon( 0.01 )  );
  REQUIRE( test->getOmega() == Approx( 0.0254/0.05 ).epsilon( 0.01 ) );
  delete test;

}

TEST_CASE( "MouseSensor test movement", "test methods" ) {
  std::string line;
  std::ifstream myfile ("/proc/bus/input/devices");
  std::string device;
  if (myfile.is_open()) {
    for(std::string word; myfile >> word; )
    if(word.compare(0,14,"Handlers=mouse") == 0) {
      myfile >> word;
      device = word;
    }
    myfile.close();
  } else std::cout << "Unable to open file";

  std::string s = "/dev/input/"+ device;
  MouseSensor *test = new MouseSensor(s,0.1,5);
  //dpi is 400;
  test->start();
  auto start = std::chrono::high_resolution_clock::now();
  std::cout << "move the mouse 10cm "<< std::endl;

  while(test->getDistance() < 0.1) {
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    std::cout << test->getDistance() << std::endl;;
  }

  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> time_span = std::chrono::duration_cast
  < std::chrono::seconds > (end - start);

  std::cout<<*test;
  REQUIRE( test->getDistance() == Approx(0.1).epsilon(0.01) );
  REQUIRE( test->getVelocity() == Approx( 0.1/time_span.count() ).epsilon( 0.01 )  );
  REQUIRE( test->getOmega() == Approx( 0.1/(time_span.count()*0.05)  ).epsilon( 10 ) );
  delete test;

}

TEST_CASE( "Wheel Encoder stream", "streem methods" ) {
  std::vector<std::string> s = getMouseDevices();
  double diameter = 0.4;
  int dpi = 400;
  int updatetime = 3;
  double distance = 120;
  double velocity = 69;
  double omega = 23;
  MouseSensor *test = new MouseSensor(s[0],diameter,updatetime,dpi);
  test->setDistance(distance);
  test->setVelocity(velocity);
  test->setOmega(omega);

  MouseSensor *test2 = new MouseSensor(s[1]);

  SECTION( "Test stream out method" )  {
    std::stringstream sstream;
    Json::Value root;
    sstream << *test;
    sstream >> root;

    REQUIRE(root.get("path","").asString() ==  s[0]);
    REQUIRE(root.get("dpi",0).asInt() == dpi );
    REQUIRE(root.get("distance",0).asDouble() == distance );
    REQUIRE(root.get("velocity",0).asDouble() == velocity );
    REQUIRE(root.get("omega",0).asDouble() == omega);
    REQUIRE(root.get("diameter",0).asDouble() == diameter);
  }
  SECTION( "Test stream in method" )  {
    //Test the stream in mehtod
    Json::Value root;

    std::stringstream ss;
    ss <<  "{ \"path\" : \""+s[1]+"\" ,";
    ss <<  " \"dpi\" : 211,";
    ss <<  " \"distance\" : 13,";
    ss <<  " \"velocity\" : 5.3, ";
    ss <<  "\"omega\" : 1.1, ";
    ss <<  "\"diameter\" : 4.5 }";

    ss << std::endl;

    ss >> *test2;

    ss << *test2;

    ss >> root;
    REQUIRE(root.get("path","").asString() == s[1] );
    REQUIRE(root.get("dpi",0).asInt() == 211 );
    REQUIRE(root.get("distance",0).asDouble() == 13 );
    REQUIRE(root.get("velocity",0).asDouble() == 5.3 );
    REQUIRE(root.get("omega",0).asDouble() == 1.1 );
    REQUIRE(root.get("diameter",0).asDouble() ==4.5 );
  }
  SECTION( "Test stream serialisation " )  {
    //test serialisation in jason
    std::stringstream ss;

    ss << *test;
    std::cout << ss.str();
    ss >> *test2;

    //test get
    REQUIRE( test2->getVelocity() == velocity );
    REQUIRE( test2->getDistance() == distance );
    REQUIRE( test2->getOmega() == omega);
    REQUIRE( test2->getDPI() == dpi);
    REQUIRE( test2->getDiameter() == diameter );
  }
}
