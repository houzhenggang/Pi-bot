#ifndef SENSOR_H
#define SENSOR_H
#include "InterInterface.h"

class Sensor : public InterInterface
{
  public:
    Sensor(int pin);
    bool trig();
    bool on();
    void reset();
    void pullup();
    int pin();
    void print();
    void trigHighLow();
    void trigLowHigh();
   
};

#endif
