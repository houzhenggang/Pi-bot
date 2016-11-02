/**
* @Author: Kieran Wyse
* @Date:   02-11-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 02-11-2016
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
#include "../Wheel.h"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch/catch.hpp"

TEST_CASE( "InterInterface constructor", "test methods" ) {
  //Test the constructor
  SECTION( "Test constructor" )  {
    Wheel *test = new Wheel(0.1,20,2,3,4);
    //test get
    REQUIRE( test->pin() == 4 );
    REQUIRE( test->getDownPulse() == 0 );
    REQUIRE( test->getUpPulse() == 0 );
    REQUIRE( test->trig() == false);
  }
}
