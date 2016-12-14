/**
* @Author: Kieran Wyse
* @Date:   28-10-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 30-10-2016
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
#include <wiringPi.h> //gpio respberry pi header
#include <softPwm.h>// software

#include <iostream>
#include <string>
using namespace std;

#include "Robot.hpp"


Robot *bot = new Robot();

string content = "";

void setup()
{
  wiringPiSetup (void) ;
  /*
This initialises wiringPi and assumes that the calling program is going to be using
 the wiringPi pin numbering scheme. This is a simplified numbering scheme which provides
  a mapping from virtual pin numbers 0 through 16 to the real underlying Broadcom
  GPIO pin numbers. See the pins page for a table which maps the wiringPi pin number
   to the Broadcom GPIO pin number to the physical location on the edge connector.
*/
  wiringPiSetupGpio();
  cout << "Finished setup...";

}
void loop() {
  string content;
  cin >> content;

  /*
  *Move in a line from point x1 , y1 to point x2 y2
  */


}
void run(std::stack<string> commands) {
  string comman;
  if(command.compare(0,5,"<line") {
    bot->goto(x1,y1);
    while(bot->getstate() != None) {
      std::sleep_for(std::chrono::milliseconds(50));
    }
    bot->rotateTo(arctan((x1-x2)/(y1-y2)));
    while(bot->getstate() != None) {
      std::sleep_for(std::chrono::milliseconds(50));
    }
    bot->goto(x2,y2);
    while(bot->getstate() != None) {
      std::sleep_for(std::chrono::milliseconds(50));
    }
  }
}

int main( int argc, const char* argv[] ) {
  setup();
  loop();

}
