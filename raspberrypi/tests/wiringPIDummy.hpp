/**
* @Author: Kieran Wyse
* @Date:   01-11-2016
* @Email:  kieranwyse@gmail.com
* @Project: Pi-Bot
* @Last modified by:   Kieran Wyse
* @Last modified time: 13-11-2016
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
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <math.h>
#include <iostream>
#include <chrono>
#define TESTING

#ifndef WIRINGDUMMY_HPP
#define WIRINGDUMMY_HPP



#define PUD_UP 1
#define INT_EDGE_FALLING 0
#define INT_EDGE_RISING 1
#define OUTPUT 1

#define PWMRANGE 100

extern void turn(int pin);



//extern static int PWMRANGE;

extern std::array<int ,17> pins;
extern std::array<int ,17> ticks;
extern std::array<int ,17> pwmRanges;
extern std::array<std::thread,17> wheelThreads;
extern std::array<int,17> sensorPin;

extern void (*pin0Risingfunc) (void);
extern void (*pin1Risingfunc) (void);
extern void (*pin2Risingfunc) (void);
extern void (*pin3Risingfunc) (void);
extern void (*pin4Risingfunc) (void);
extern void (*pin5Risingfunc) (void);
extern void (*pin6Risingfunc) (void);
extern void (*pin7Risingfunc) (void);
extern void (*pin8Risingfunc) (void);
extern void (*pin9Risingfunc) (void);
extern void (*pin10Risingfunc) (void);
extern void (*pin11Risingfunc) (void);
extern void (*pin12Risingfunc) (void);
extern void (*pin13Risingfunc) (void);
extern void (*pin14Risingfunc) (void);
extern void (*pin15Risingfunc) (void);
extern void (*pin16Risingfunc) (void);

extern void (*pin0Fallingfunc) (void);
extern void (*pin1Fallingfunc) (void);
extern void (*pin2Fallingfunc) (void);
extern void (*pin3Fallingfunc) (void);
extern void (*pin4Fallingfunc) (void);
extern void (*pin5Fallingfunc) (void);
extern void (*pin6Fallingfunc) (void);
extern void (*pin7Fallingfunc) (void);
extern void (*pin8Fallingfunc) (void);
extern void (*pin9Fallingfunc) (void);
extern void (*pin10Fallingfunc) (void);
extern void (*pin11Fallingfunc) (void);
extern void (*pin12Fallingfunc) (void);
extern void (*pin13Fallingfunc) (void);
extern void (*pin14Fallingfunc) (void);
extern void (*pin15Fallingfunc) (void);
extern void (*pin16Fallingfunc) (void);

void pinMode (int pin, int mode) ;
void wiringPiISR (int pin ,int edge, void (*foo)(void) ) ;
void pullUpDnControl(int pin, int control);
void softPwmCreate (int pin , int initialValue, int  pwmRange) ;
void softPwmWrite (int pin,int duty) ;

#endif
