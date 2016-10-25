#ifndef WHEEL_H
#define WHEEL_H

#include "InterInterface.h"

#include "TractionControl.h"

class Wheel: public InterInterface
{
  public:
    Wheel(float diameter,int ticks,int motorPinForward,int motorPinReverse,int sensorPin);
    double distance();
    double velocity();
    int getFrequency();
    void setFrequency(int frequency);
    void stop();
    double update();
    void pullup(int pin);
    friend ostream& operator<<(ostream& stream,Wheel ob);
    friend istream& operator>>(istream& stream,Wheel ob);

  private:
    TractionControl *_contol;
    void pwm(int pin,int duty);
    double _previousDistance;
    double _distance;
    double _velocity;
    int _frequency;
    int _motorPinForward;
    int _motorPinReverse;
    int _sensorPin;
    float _diameter;
    int _ticks;
    double _const;
    unsigned long _prevPulses;
    bool _forward;

};

#endif
