/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 01-11-2016
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


#include "TestInterInterface.hpp"
#include "../InterInterface.hpp"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch/catch.hpp"

TEST_CASE( "InterInterface constructor", "test methods" ) {
  //Test the constructor
  SECTION( "Test constructor" )  {
    InterInterface *test = new InterInterface(1);
    //test get
    REQUIRE( test->pin() == 1 );
    REQUIRE( test->getDownPulse() == 0 );
    REQUIRE( test->getUpPulse() == 0 );
    REQUIRE( test->trig() == false);
  }
}

TEST_CASE( "InterInterface Trigger", "trigger events" ) {
  SECTION( "Simulate a trigger up event on 0" )  {
    InterInterface *test = new InterInterface(0);
    REQUIRE( test->trig() == false );
    pin0Risingfunc();
    REQUIRE( test->getUpPulse() == 1 );
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger up event on 1" )  {

    InterInterface *test = new InterInterface(1);
    REQUIRE( test->trig() == false );
    pin1Risingfunc();
    REQUIRE( test->trig() == true );
  }

  SECTION( "Simulate a trigger up event on 2" )  {
    InterInterface *test = new InterInterface(2);
    REQUIRE( test->trig() == false );
    pin2Risingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger up event on 3" )  {

    InterInterface *test = new InterInterface(3);
    REQUIRE( test->trig() == false );
    pin3Risingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger up event on 4" )  {
    InterInterface *test = new InterInterface(4);
    REQUIRE( test->trig() == false );
    pin4Risingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger up event on 5" )  {

    InterInterface *test = new InterInterface(5);
    REQUIRE( test->trig() == false );
    pin5Risingfunc();
    REQUIRE( test->trig() == true );
  }

  SECTION( "Simulate a trigger up event on 6" )  {
    InterInterface *test = new InterInterface(6);
    REQUIRE( test->trig() == false );
    pin6Risingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger up event on 7" )  {

    InterInterface *test = new InterInterface(7);
    REQUIRE( test->trig() == false );
    pin7Risingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger up event on 8" )  {
    InterInterface *test = new InterInterface(8);
    REQUIRE( test->trig() == false );
    pin8Risingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger up event on 9" )  {

    InterInterface *test = new InterInterface(9);
    REQUIRE( test->trig() == false );
    pin9Risingfunc();
    REQUIRE( test->trig() == true );
  }

  SECTION( "Simulate a trigger up event on 10" )  {
    InterInterface *test = new InterInterface(10);
    REQUIRE( test->trig() == false );
    pin10Risingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger up event on 11" )  {

    InterInterface *test = new InterInterface(11);
    REQUIRE( test->trig() == false );
    pin11Risingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger up event on 12" )  {
    InterInterface *test = new InterInterface(12);
    REQUIRE( test->trig() == false );
    pin12Risingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger up event on 13" )  {

    InterInterface *test = new InterInterface(13);
    REQUIRE( test->trig() == false );
    pin13Risingfunc();
    REQUIRE( test->trig() == true );
  }

  SECTION( "Simulate a trigger up event on 14" )  {
    InterInterface *test = new InterInterface(14);
    REQUIRE( test->trig() == false );
    pin14Risingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger up event on 15" )  {

    InterInterface *test = new InterInterface(15);
    REQUIRE( test->trig() == false );
    pin15Risingfunc();
    REQUIRE( test->trig() == true );
  }

  SECTION( "Simulate a trigger up event on 16" )  {

    InterInterface *test = new InterInterface(16);
    REQUIRE( test->trig() == false );
    pin16Risingfunc();
    REQUIRE( test->trig() == true );
  }

  SECTION( "add more than one listener for a pin and trig up event") {
    InterInterface *test1 = new InterInterface(5);
    InterInterface *test2 = new InterInterface(5);
    InterInterface *test3 = new InterInterface(5);
    pin5Risingfunc();
    REQUIRE( test1->trig() == true );
    REQUIRE( test2->trig() == true );
    REQUIRE( test3->trig() == true );
  }
  SECTION( "Simulate a trigger down event on 0" )  {
    InterInterface *test = new InterInterface(0);
    REQUIRE( test->trig() == false );
    pin0Fallingfunc();
    REQUIRE( test->getDownPulse() == 1 );
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger down event on 1" )  {
    InterInterface *test = new InterInterface(1);
    REQUIRE( test->trig() == false );
    pin1Fallingfunc();
    REQUIRE( test->trig() == true );
  }

  SECTION( "Simulate a trigger down event on 2" )  {
    InterInterface *test = new InterInterface(2);
    REQUIRE( test->trig() == false );
    pin2Risingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger up event on 3" )  {

    InterInterface *test = new InterInterface(3);
    REQUIRE( test->trig() == false );
    pin3Fallingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger down event on 4" )  {
    InterInterface *test = new InterInterface(4);
    REQUIRE( test->trig() == false );
    pin4Fallingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger down event on 5" )  {

    InterInterface *test = new InterInterface(5);
    REQUIRE( test->trig() == false );
    pin5Fallingfunc();
    REQUIRE( test->trig() == true );
  }

  SECTION( "Simulate a trigger down event on 6" )  {
    InterInterface *test = new InterInterface(6);
    REQUIRE( test->trig() == false );
    pin6Fallingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger down event on 7" )  {

    InterInterface *test = new InterInterface(7);
    REQUIRE( test->trig() == false );
    pin7Fallingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger down event on 8" )  {
    InterInterface *test = new InterInterface(8);
    REQUIRE( test->trig() == false );
    pin8Fallingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger down event on 9" )  {

    InterInterface *test = new InterInterface(9);
    REQUIRE( test->trig() == false );
    pin9Fallingfunc();
    REQUIRE( test->trig() == true );
  }

  SECTION( "Simulate a trigger down event on 10" )  {
    InterInterface *test = new InterInterface(10);
    REQUIRE( test->trig() == false );
    pin10Fallingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger down event on 11" )  {

    InterInterface *test = new InterInterface(11);
    REQUIRE( test->trig() == false );
    pin11Fallingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger down event on 12" )  {
    InterInterface *test = new InterInterface(12);
    REQUIRE( test->trig() == false );
    pin12Fallingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger down event on 13" )  {

    InterInterface *test = new InterInterface(13);
    REQUIRE( test->trig() == false );
    pin13Fallingfunc();
    REQUIRE( test->trig() == true );
  }

  SECTION( "Simulate a trigger down event on 14" )  {
    InterInterface *test = new InterInterface(14);
    REQUIRE( test->trig() == false );
    pin14Fallingfunc();
    REQUIRE( test->trig() == true );
  }
  SECTION( "Simulate a trigger down event on 15" )  {

    InterInterface *test = new InterInterface(15);
    REQUIRE( test->trig() == false );
    pin15Fallingfunc();
    REQUIRE( test->trig() == true );
  }

  SECTION( "Simulate a trigger down event on 16" )  {

    InterInterface *test = new InterInterface(16);
    REQUIRE( test->trig() == false );
    pin16Fallingfunc();
    REQUIRE( test->trig() == true );
  }

  SECTION( "add more than one listener for a pin and trig down event") {
    InterInterface *test1 = new InterInterface(5);
    InterInterface *test2 = new InterInterface(5);
    InterInterface *test3 = new InterInterface(5);
    pin5Fallingfunc();
    REQUIRE( test1->trig() == true );
    REQUIRE( test2->trig() == true );
    REQUIRE( test3->trig() == true );
  }
}
  TEST_CASE( "InterInterface etream", "streem methods" ) {
    //test the stream out method
    SECTION( "Test stream out method" )  {
      InterInterface *test = new InterInterface(2);
      std::stringstream sstream;
      Json::Value root;
      sstream << *test;
      sstream >> root;

      REQUIRE(root.get("pin","0") == 2 );
      REQUIRE(root.get("up-pulses","0") == 0 );
      REQUIRE(root.get("down-pulses","0") == 0 );
    }
    SECTION( "Test stream in method" )  {
      //Test the stream in mehtod
      Json::Value root;
      InterInterface *second = new InterInterface(10);
      std::stringstream ss;
      ss <<  "{ \"pin\" : 20 , \"up-pulses\" : 14, \"down-pulses\" : 13 }";
      ss << std::endl;

      ss >> *second;

      ss << *second;

      ss >> root;
      REQUIRE(root.get("pin","0") == 20 );
      REQUIRE(root.get("up-pulses","0") == 14 );
      REQUIRE(root.get("down-pulses","0") == 13 );
    }
    SECTION( "Test stream serialisation " )  {
      //test serialisation in jason
      std::stringstream ss;
      InterInterface *test = new InterInterface(2);
      InterInterface *second = new InterInterface(12);
      pin12Fallingfunc();
      pin12Fallingfunc();
      pin12Fallingfunc();

      pin12Risingfunc();
      pin12Risingfunc();

      ss << *second;
      ss >> *test;

      REQUIRE( test->pin() == 12 );

      REQUIRE( test->getUpPulse() == 2 );
      REQUIRE( test->getDownPulse() == 3 );
    }
  }
