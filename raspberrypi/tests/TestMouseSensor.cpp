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
#include "../MouseSensor.hpp"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch/catch.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>


/*
* Writing evelnts to input echos the events back.
*/

void writeEvent(int x,int y,std::string mouse) {
  struct input_event event, event_end;

  int fd = open(mouse.c_str(), O_RDWR);
  if (fd < 0) {
    std::cerr << "/* Errro open mouse: */" << std::strerror(errno)<< '\n';
    return;
  }
  std::memset(&event, 0, sizeof(event));
  std::memset(&event, 0, sizeof(event_end));
  gettimeofday(&event.time, NULL);
  event.type = EV_REL;
  event.code = REL_X;
  event.value = x;
  gettimeofday(&event_end.time, NULL);
  event_end.type = EV_SYN;
  event_end.code = SYN_REPORT;
  event_end.value = 0;

  //Writing evelnts to input echos the events back.
  write(fd, &event, sizeof(event));// Move the mouse
  write(fd, &event_end, sizeof(event_end));// Show move

  gettimeofday(&event.time, NULL);
  event.type = EV_REL;
  event.code = REL_Y;
  event.value = y;
  gettimeofday(&event_end.time, NULL);
  event_end.type = EV_SYN;
  event_end.code = SYN_REPORT;
  event_end.value = 0;

  //Writing evelnts to input echos the events back.
  write(fd, &event, sizeof(event));// Move the mouse
  write(fd, &event_end, sizeof(event_end));// Show move

  close(fd);
  return;
}



TEST_CASE( "WheelSensor", "test methods" ) {
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

TEST_CASE( "WheelSensor get and set update methods", "test methods" ) {
  std::string s = "/dev/input/event6";
  MouseSensor *test = new MouseSensor(s);
  //dpi is 400;




  std::this_thread::sleep_for(std::chrono::seconds(10));
  writeEvent(400,0,s);

  std::cout<<*test;
  REQUIRE( test->getDistance() == 400 );
  REQUIRE( test->getVelocity() == Approx( 400/10 ).epsilon( 0.1 )  );
  REQUIRE( test->getOmega() == Approx( 4000 ).epsilon( 10 ) );
  delete test;

}
