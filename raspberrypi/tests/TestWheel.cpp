/**
* @Author: Kieran Wyse
* @Date:   02-11-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 14-11-2016
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
#include <thread>
#include <chrono>
#include "../Wheel.h"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch/catch.hpp"

const double M_PI = 3.14159265359;

/*
*simulate a wheel turning
*
*/
//int duty =0;



TEST_CASE( "Wheel constructor", "test methods" ) {
  //Test the constructor
  Wheel *test = new Wheel(0.1,2,3,new WheelSensor(4,20));
  SECTION( "Test constructor" )  {
    //test get
  }
}

TEST_CASE( "Wheel get and set methods", "test methods" ) {
  //Test the constructor
  int forwardpin = 1;
  int backwardpin = 2;
  int sensorPin1 = 4;
  sensorPin[forwardpin] = sensorPin1;
  sensorPin[backwardpin] = sensorPin1;
  ticks[sensorPin1] =20;

  int forwardpin2 = 11;
  int backwardpin2 = 12;
  int sensorPin2 = 13;
  sensorPin[forwardpin2] = sensorPin2;
  sensorPin[backwardpin2] = sensorPin2;
  ticks[sensorPin2] =20;



  float diameter = 0.1;

  Wheel *test = new Wheel(diameter,forwardpin,backwardpin,new WheelSensor(sensorPin1,ticks[sensorPin1]));

  Wheel *test2 = new Wheel(diameter,forwardpin2,backwardpin2,new WheelSensor(sensorPin2,ticks[sensorPin2]));

  SECTION( "Test frequency" )  {


    //test get
    REQUIRE(pwmRanges[forwardpin] == PWMRANGE);
    REQUIRE(pwmRanges[backwardpin] == PWMRANGE);
    double vel = test->getVelocity();
    REQUIRE( vel == Approx( 0 ).epsilon( 0.01 ) );
    test->setFrequency(50);
    REQUIRE( test->getFrequency() == 50 );
    REQUIRE(pins[forwardpin] == 50);
    REQUIRE(pins[backwardpin] == 0);

    test->setFrequency(-50);

    REQUIRE(pins[forwardpin] == 0);
    REQUIRE(pins[backwardpin] == 50);

    test->setFrequency(200);

    REQUIRE(pins[forwardpin] == PWMRANGE);
    REQUIRE(pins[backwardpin] == 0);

    test->setFrequency(-200);

    REQUIRE(pins[forwardpin] == 0);
    REQUIRE(pins[backwardpin] == PWMRANGE);

    test->setFrequency(0);
  }
  SECTION( "simulate wheel turning 1 second" )  {
    test->setFrequency(50);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    test->update();
    test->setFrequency(0);
    std::cout << *test;
    REQUIRE(test->getDistance() > 0);

    test->setFrequency(0);
  }
  SECTION( "simulate wheel turning 10 meters" )  {
    test->setFrequency(50);

    while(test->getDistance() < 10) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      test->update();
    }
    test->setFrequency(0);
    REQUIRE(test->getDistance() > 10);
    test->setFrequency(0);
  }
  SECTION ("Test two wheels concurrently") {
      	test->setFrequency(50);
      	test2->setFrequency(100);
      	for(int i = 0; i < 10;i++){
      		std::this_thread::sleep_for(std::chrono::milliseconds(100));
      		test2->update();
      		test->update();
      	}

      	//maximum rate is5 revolutions per second
      	std::cout <<*test;
      	std::cout <<*test2;
      	REQUIRE(test2->getVelocity() == Approx( (double)5*diameter*M_PI ).epsilon( 0.01 ));
      	REQUIRE(test->getVelocity() == Approx( (double)2.5*diameter*M_PI ).epsilon( 0.01 ));

      	test->setFrequency(0);
      	test2->setFrequency(0);

      }
}
  TEST_CASE( "Wheel stream", "streem methods" ) {
    //test the stream out method
    double diameter1 = 0.1;
    bool forward1 = true;
    int ticks1 = 20;
    int sensorpin1 = 10;



    WheelSensor *sensor = new WheelSensor(sensorpin1,ticks1);

    for(int i = 0; i < ticks1; i++) {
      pin10Risingfunc();
      pin10Fallingfunc();
    }
    //wait one second
    std::this_thread::sleep_for(std::chrono::seconds(1));
    sensor->update(diameter1,forward1);
    int forwardpin = 6;
    int backwardpin = 7;
    float diameter = 0.2;
    int frequency = 60;

    sensorPin[forwardpin] = sensorpin1;
    sensorPin[backwardpin] = sensorpin1;
    ticks[sensorpin1] =ticks1;

    Wheel *test = new Wheel(diameter,forwardpin,backwardpin,sensor);
    test->setFrequency(frequency);





    Wheel *test2 = new Wheel(0.1,2,3,new WheelSensor(4,10));
    SECTION( "Test stream out method" )  {
      std::stringstream sstream;
      Json::Value root;
      sstream << *test;
      sstream >> root;
      Json::Value s =root.get("sensor","");
      REQUIRE(s.get("pin",0) ==  sensorpin1);
      REQUIRE(s.get("up-pulses",0) == ticks1 );
      REQUIRE(s.get("down-pulses",0) == ticks1 );
      REQUIRE(s.get("distance",0) == M_PI*diameter1 );
      REQUIRE(s.get("velocity",0) == M_PI*diameter1 );
      REQUIRE(s.get("omega",0) == 2*M_PI);
      REQUIRE(s.get("previous-distance",0) ==0);
      REQUIRE(s.get("previous-pulses",0) == 2*ticks1);

      REQUIRE(root.get("diameter",0) == diameter);
      REQUIRE(root.get("forward",0) == true);
      REQUIRE(root.get("motor-forward-pin",0) == forwardpin);
      REQUIRE(root.get("motor-reverse-pin",0) == backwardpin);
      REQUIRE(root.get("frequency",0) == frequency);

      test->setFrequency(0);


    }

    SECTION( "Test stream in method" )  {
      //Test the stream in mehtod
      Json::Value root;
      std::stringstream ss;
      ss << "{" << std::endl;
      ss << "\"diameter\": 0.14,"<< std::endl;
      ss << "\"forward\": false,"<< std::endl;
      ss << "\"motor-forward-pin\": 12,"<< std::endl;
      ss << "\"motor-reverse-pin\": 15," << std::endl;
      ss <<" \"frequency\": 22 ," << std::endl;
      ss <<  "\"sensor\" : " << std::endl;
      ss <<"{" <<std::endl;
      ss <<" \"pin\" : 2 ," <<std::endl;
      ss <<" \"up-pulses\" : 14, " <<std::endl;
      ss <<" \"down-pulses\" : 13, " <<std::endl;
      ss << "\"distance\" : 5.3, " <<std::endl;
      ss << "\"velocity\" : 1.1, " << std::endl;
      ss << "\"omega\" : 4.5, \"previous-distance\" : 5.0, \"previous-pulses\" : 15 , \"ticks\" : 27 }";
      ss << "}";
      ss << std::endl;


      ss >> *test;


      ss << *test;

      ss >> root;
      Json::Value s = root.get("sensor","");
      REQUIRE(s.get("ticks",0) == 27 );
      REQUIRE(s.get("pin",0) == 2 );
      REQUIRE(s.get("up-pulses",0) == 14 );
      REQUIRE(s.get("down-pulses",0) == 13 );
      REQUIRE(s.get("distance",0) == 5.3 );
      REQUIRE(s.get("velocity",0) == 1.1 );
      REQUIRE(s.get("omega",0) ==4.5 );
      REQUIRE(s.get("previous-distance",0).asDouble() == 5.0 );
      REQUIRE(s.get("previous-pulses",0) == 15 );

      REQUIRE(root.get("diameter",0).asDouble() == Approx( 0.14 ).epsilon( 0.01 ) );
      REQUIRE(root.get("forward",0).asBool() == false);
      REQUIRE(root.get("motor-forward-pin",0).asInt() == 12);
      REQUIRE(root.get("motor-reverse-pin",0).asInt() == 15);
      REQUIRE(root.get("frequency",0).asInt() == 22);

      test->setFrequency(0);

    }
    SECTION( "Test stream serialisation " )  {
      //test serialisation in jason
      std::stringstream ss;


      ss << *test;
      ss >> *test2;

      REQUIRE( test2->getSensor()->pin() == sensorpin1 );
      REQUIRE( test2->getSensor()->getDownPulse() == test->getSensor()->getDownPulse() );
      REQUIRE( test2->getSensor()->getUpPulse() == test->getSensor()->getUpPulse());
      REQUIRE( test2->getSensor()->trig() == test->getSensor()->trig());
      //test get
      REQUIRE( test2->getVelocity() == test->getVelocity() );
      REQUIRE( test2->getDistance() == test->getDistance() );


    }

}
