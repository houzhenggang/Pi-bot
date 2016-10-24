#ifndef INTERINTERFACE_H
#define INTERINTERFACE_H


#include <wiringPi.h> //gpio respberry pi header
#include <softPwm.h>// software

#include <iostream>
#include <string>
/*
*
*Wrapper arround the interupts
*
*/
using namespace std;

class InterInterface {
    public:
    InterInterface(int pin);
    bool trig();
    void reset();
    void pullup();
    void trigHighLow();
    void trigLowHigh();
    int getDownPulse();
    int getUpPulse();
    int pin();
    protected:
    int _pin;
    volatile unsigned long _upPulse;
    volatile unsigned long _downPulse;
    friend ostream& operator<<(ostream& stream,InterInterface ob);
    friend istream& operator>>(istream& stream,InterInterface ob);
    private:




};


#endif
