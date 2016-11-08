/**
* @Author: Kieran Wyse
* @Date:   08-11-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 08-11-2016
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



#include "../TractionControl.h"
#include "sstream"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch/catch.hpp"


using namespace std;

TEST_CASE( "Traction object", "test methods" ) {
  //Test the constructor
  TractionControl *test = new TractionControl(50);
  //test get
  REQUIRE( test->getMaxChange() == 50);

  //test set
  //Test the set methods
  test->setMaxChange(20);

  REQUIRE( test->getMaxChange() == 20 );


  //test the stream out method
  std::stringstream sstream;
  Json::Value root;
  sstream << *test;
  sstream >> root;

  REQUIRE(root.get("max-change",0) == 20 );

  //Test the stream in mehtod
  root.clear();
  TractionControl *second = new TractionControl(11);
  stringstream ss;
  ss <<  "{ \"max-change\" : 15  }";
  ss << std::endl;

  ss >> *second;

  ss << *second;

  ss >> root;
  REQUIRE(root.get("max-change",0) == 15 );


  //test serialisation in jason
  ss << *second;
  ss >> *test;

  REQUIRE( test->getMaxChange() == 15 );

  SECTION ( "test modify method") {

  REQUIRE(test->modify(200) == 15);
  REQUIRE(test->modify(200) == 30);
  REQUIRE(test->modify(200) == 45);

  REQUIRE(test->modify(-200) == 30);
  test->setMaxChange(0);
  REQUIRE(test->modify(200) == 200);
}


}
