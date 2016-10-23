

#include <wiringPi.h> //gpio respberry pi header
#include <softPwm.h>// software

#include <iostream>
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

       cin >> content;
       if(content == "print:state") {
          bot->print();

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
         String com = content.substring(5);
         int dev = com.indexOf(',');
         String xstr = com.substring(0,dev);
         String ystr = com.substring(dev+1,com.length());
         char bufx[xstr.length()+1];
         char bufy[ystr.length()+1];
         xstr.toCharArray(bufx,xstr.length()+1);
         ystr.toCharArray(bufy,ystr.length()+1);
         double x = atof(bufx);
         double y = atof(bufy);

         Serial.print("goto:");
         Serial.print(x);
         Serial.print(",");
         Serial.println(y);
         bot->goTo(x,y);
       }
       if(content.substring(0,5) == "move:") {
         String com = content.substring(5);
         int dev = com.indexOf(',');
         int left = com.substring(0,dev).toInt();
         int right = com.substring(dev+1).toInt();
         bot->wheelLeft(left);
         bot->wheelRight(right);
       }
       if(content.substring(0,6) == "drive:") {
         String com = content.substring(6);
         int rspeed = com.toInt();
         Serial.print("drive:");
         Serial.print(rspeed);
         bot->drive(rspeed);
       }
       if(content.substring(0,10) == "forwardTo:") {
         String com = content.substring(10);
         int distance = com.toInt();
         Serial.print("forward to:");
         Serial.print(distance);
         bot->forwardTo(distance);
       }
       if(content.substring(0,9) == "rotateTo:") {
         String com = content.substring(9);
         int rangle = com.toInt();
         Serial.print("rotate:");
         Serial.print(rangle);
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
