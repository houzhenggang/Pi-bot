/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 29-10-2016
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


#include "../Point.hpp"
#include "sstream"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch/catch.hpp"


using namespace std;

TEST_CASE( "Point object", "test methods" ) {
  //Test the constructor
  Point *test = new Point(5,4);
  //test get
  REQUIRE( test->getX() == 5 );
  REQUIRE( test->getY() == 4 );
  //test set
  //Test the set methods
  test->setX(6);
  test->setY(9);
  REQUIRE( test->getX() == 6 );
  REQUIRE( test->getY() == 9 );

  //test the stream out method
  std::stringstream sstream;
  Json::Value root;
  sstream << *test;
  sstream >> root;

  REQUIRE(root.get("x","0") == 6 );
  REQUIRE(root.get("y","0") == 9 );

  //Test the stream in mehtod
  root.clear();
  Point *second = new Point(0,0);
  stringstream ss;
  ss <<  "{ \"x\" : 10 , \"y\" : 10 }";
  ss << std::endl;

  ss >> *second;

  ss << *second;

  ss >> root;
  REQUIRE(root.get("x","0") == 10 );
  REQUIRE(root.get("y","0") == 10 );

  //test serialisation in jason
  ss << *second;
  ss >> *test;

  REQUIRE( test->getX() == 10 );
  REQUIRE( test->getY() == 10 );

}
