/**
* @Author: Kieran Wyse
* @Date:   01-11-2016
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
#include "wiringPIDummy.hpp"


void (*pin0Risingfunc) (void);
 void (*pin1Risingfunc) (void);
 void (*pin2Risingfunc) (void);
 void (*pin3Risingfunc) (void);
 void (*pin4Risingfunc) (void);
 void (*pin5Risingfunc) (void);
 void (*pin6Risingfunc) (void);
 void (*pin7Risingfunc) (void);
 void (*pin8Risingfunc) (void);
 void (*pin9Risingfunc) (void);
 void (*pin10Risingfunc) (void);
 void (*pin11Risingfunc) (void);
 void (*pin12Risingfunc) (void);
 void (*pin13Risingfunc) (void);
 void (*pin14Risingfunc) (void);
 void (*pin15Risingfunc) (void);
 void (*pin16Risingfunc) (void);

 void (*pin0Fallingfunc) (void);
  void (*pin1Fallingfunc) (void);
  void (*pin2Fallingfunc) (void);
  void (*pin3Fallingfunc) (void);
  void (*pin4Fallingfunc) (void);
  void (*pin5Fallingfunc) (void);
  void (*pin6Fallingfunc) (void);
  void (*pin7Fallingfunc) (void);
  void (*pin8Fallingfunc) (void);
  void (*pin9Fallingfunc) (void);
  void (*pin10Fallingfunc) (void);
  void (*pin11Fallingfunc) (void);
  void (*pin12Fallingfunc) (void);
  void (*pin13Fallingfunc) (void);
  void (*pin14Fallingfunc) (void);
  void (*pin15Fallingfunc) (void);
  void (*pin16Fallingfunc) (void);


void wiringPiISR (int pin,int edge, void (*foo)(void) )  {
  if(edge == 1) {
    switch (pin) {
      case 0: pin0Risingfunc = foo;
      break;
      case 1: pin1Risingfunc = foo;
      break;
      case 2: pin2Risingfunc = foo;
      break;
      case 3: pin3Risingfunc = foo;
      break;
      case 4: pin4Risingfunc = foo;
      break;
      case 5: pin5Risingfunc = foo;
      break;
      case 6: pin6Risingfunc = foo;
      break;
      case 7: pin7Risingfunc = foo;
      break;
      case 8: pin8Risingfunc = foo;
      break;
      case 9: pin9Risingfunc = foo;
      break;
      case 10: pin10Risingfunc = foo;
      break;
      case 11: pin11Risingfunc = foo;
      break;
      case 12: pin12Risingfunc = foo;
      break;
      case 13: pin13Risingfunc = foo;
      break;
      case 14: pin14Risingfunc = foo;
      break;
      case 15: pin15Risingfunc = foo;
      break;
      case 16: pin16Risingfunc = foo;
      break;
    }
  }
  if(edge == 0) {
    switch (pin) {
      case 0: pin0Fallingfunc = foo;
      break;
      case 1: pin1Fallingfunc = foo;
      break;
      case 2: pin2Fallingfunc = foo;
      break;
      case 3: pin3Fallingfunc = foo;
      break;
      case 4: pin4Fallingfunc = foo;
      break;
      case 5: pin5Fallingfunc = foo;
      break;
      case 6: pin6Fallingfunc = foo;
      break;
      case 7: pin7Fallingfunc = foo;
      break;
      case 8: pin8Fallingfunc = foo;
      break;
      case 9: pin9Fallingfunc = foo;
      break;
      case 10: pin10Fallingfunc = foo;
      break;
      case 11: pin11Fallingfunc = foo;
      break;
      case 12: pin12Fallingfunc = foo;
      break;
      case 13: pin13Fallingfunc = foo;
      break;
      case 14: pin14Fallingfunc = foo;
      break;
      case 15: pin15Fallingfunc = foo;
      break;
      case 16: pin16Fallingfunc = foo;
      break;
    }
  }
}
std::array<int ,17> pwmRanges = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void softPwmCreate (int pin , int initialValue, int  pwmRange) {
  pwmRanges[pin] = pwmRange;

}


std::array<int ,17> pins = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void softPwmWrite (int pin,int duty) {

  pins[pin] =duty;

}

void pinMode (int pin, int mode)  {



}

void pullUpDnControl(int pin, int control) {

}
