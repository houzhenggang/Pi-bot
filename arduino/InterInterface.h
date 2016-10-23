#ifndef INTERINTERFACE_H
#define INTERINTERFACE_H


#include "Arduino.h"
#include <stdint.h>            // has to be added to use uint8_t


class InterInterface {
    public:
    InterInterface(int pin);
    bool trig();
    bool on();
    void reset();
    void pullup();
    void trigHighLow();
    void trigLowHigh();
    static void callbackRegB();
    static void callbackRegC();
    static void callbackRegD();
    int getDownPulse();
    int getUpPulse();
    int pin();
    void print();
    protected:
    int _pin;
    volatile unsigned long _upPulse;
    volatile unsigned long _downPulse;
    private:

      static volatile uint8_t _registerHistoryB;
      static volatile uint8_t _registerHistoryC;
      static volatile uint8_t _registerHistoryD;

      static InterInterface *_regB[8];
      static InterInterface *_regC[8];
      static InterInterface *_regD[8];
      static volatile uint8_t test;

    
};


#endif
