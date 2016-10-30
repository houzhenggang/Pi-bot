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

#include <wiringPi.h> //gpio respberry pi header
#include <softPwm.h>// software

#include <iostream>
#include <string>
using namespace std;

#include "Wheel.h"
#include "Sensor.h"
#include "Robot.h"


Robot *bot = new Robot(0.01);


string content = "";
char character;
int timer = 0;
std::string::size_type sz;



void setup()
{
  wiringPiSetupGpio();
  cout << "Finished setup...";

}
void loop()

{

     delay(20);
     bot->updateObserver();
     bot->updateRobot();
     if(timer % 10 == 0) {

     }
     if(timer>10) {
       string content;
       cin >> content;
       if(content == "print:state") {
          cout << bot;

       }

       if(content == "test:wheels")
         bot->test(Wheels);
       if(content == "test:sensors")
         bot->test(Sensors);
       if(content == "test:robots")
         bot->test(Robots);
       if(content == "test:none")
         bot->test(Nones);
       if(content == "test:interfaces")
         bot->test(Interfaces);
       if(content == "test:registers")
         bot->test(Registers);
       if(content.substr(0,5) == "goto:") {

         double x = std::stof(content,&sz);
         double y = std::stof(content,&sz);

         cout << "{ goto_x : " << x << " , goto_y:" << y << "}";
         bot->goTo(x,y);
       }
       if(content.substr(0,5) == "move:") {

         int left = std::stoi (content,&sz);
         int right = std::stoi (content,&sz);
         bot->wheelLeft(left);
         bot->wheelRight(right);
       }
       if(content.substr(0,6) == "drive:") {
         int rspeed = std::stoi (content.substr(6),&sz);
         cout << "{ drive : "<<rspeed<<" } ";
         bot->drive(rspeed);
       }
       if(content.substr(0,10) == "forwardTo:") {
         int distance = std::stoi (content.substr(10),&sz);
         cout <<"{ forward_to : "<<distance<<" }";
         bot->forwardTo(distance);
       }
       if(content.substr(0,9) == "rotateTo:") {
         int rangle = std::stoi (content.substr(9),&sz);

         cout << "{ rotate :"<<rangle<<" }";
         bot->rotateTo(rangle);
       }

       if(content.substr(0,5) == "stop") {
         bot->stop();
       }
       if(content == "reset") {
         delete bot;
         bot = new Robot(0.01);

       }
       if(content.substr(0,5) == "wheel") {

          if(content.substr(0,11) == "wheel-left:") {
            int f = std::stoi (content.substr(11),&sz);
            bot->stop();
            bot->wheelLeft(f);
          }
          if(content.substr(0,12) == "wheel-right:") {
            int f = std::stoi (content.substr(12),&sz);
            bot->stop();
            bot->wheelRight(f);
          }
       }
       content = "";
       bot->print();
       timer = 0;
     }
     timer++;

}

int main( int argc, const char* argv[] ) {
  setup();
  loop();

}
