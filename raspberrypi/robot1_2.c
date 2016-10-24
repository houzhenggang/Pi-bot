

#include <wiringPi.h> //gpio respberry pi header
#include <softPwm.h>// software

#include <iostream>
#include <string>
using namespace std;

#include "Wheel.h"
#include "Sensor.h"
#include "Robot.h"


Robot *bot = new Robot(0.01);


String content = "";
char character;
int timer = 0;

int main( int argc, const char* argv[] ) {
  setup();
  loop();

}


void setup()
{
  wiringPiSetupGpio (void) ;
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
       if(content.substring(0,5) == "goto:") {
         string com = content.substring(5);
         int dev = com.indexOf(',');
         string xstr = com.substring(0,dev);
         string ystr = com.substring(dev+1,com.length());
         char bufx[xstr.length()+1];
         char bufy[ystr.length()+1];
         xstr.toCharArray(bufx,xstr.length()+1);
         ystr.toCharArray(bufy,ystr.length()+1);
         double x = atof(bufx);
         double y = atof(bufy);

         cout << "{ goto_x : " << x << " , goto_y:" << y << "}";
         bot->goTo(x,y);
       }
       if(content.substring(0,5) == "move:") {
         string com = content.substring(5);
         int dev = com.indexOf(',');
         int left = com.substring(0,dev).toInt();
         int right = com.substring(dev+1).toInt();
         bot->wheelLeft(left);
         bot->wheelRight(right);
       }
       if(content.substring(0,6) == "drive:") {
         String com = content.substring(6);
         int rspeed = com.toInt();
         cout << "{ drive : "<<rspeed<<" } ";
         bot->drive(rspeed);
       }
       if(content.substring(0,10) == "forwardTo:") {
         string com = content.substring(10);
         int distance = com.toInt();
         cout <<"{ forward_to : "<<distance<<" }"
         bot->forwardTo(distance);
       }
       if(content.substring(0,9) == "rotateTo:") {
         string com = content.substring(9);
         int rangle = com.toInt();
         cout << "{ rotate :"<<rangle<<" }";
         bot->rotateTo(rangle);
       }

       if(content.substring(0,5) == "stop") {
         bot->stop();
       }
       if(content == "reset") {
         delete bot;
         bot = new Robot(0.01);

       }
       if(content.substring(0,5) == "wheel") {

          if(content.substring(0,11) == "wheel-left:") {
            int f = content.substring(11).toInt();
            bot->stop();
            bot->wheelLeft(f);
          }
          if(content.substring(0,12) == "wheel-right:") {
            int f = content.substring(12).toInt();
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
