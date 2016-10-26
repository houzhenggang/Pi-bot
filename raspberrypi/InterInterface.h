#ifndef INTERINTERFACE_H
#define INTERINTERFACE_H


#include <wiringPi.h> //gpio respberry pi header
#include <softPwm.h>// software
#include <functional> //needed for bind

#include <iostream>
#include <string>
#include <list>
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
      void registerListener(int pin);
        static std::list<int> pin1RisingListeners;
      //static std::list<std::function<void()>> pin1RisingListeners;
      //static std::list<std::function<void()>> pin1FallingListeners;
      static void pin1Rising();
      static void pin1Falling();






};


#endif
