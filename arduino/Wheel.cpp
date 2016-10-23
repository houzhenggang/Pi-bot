#include "Arduino.h"
#include "Wheel.h"
#include <math.h>
Wheel::Wheel(float diameter,int ticks,int motorPinForward,int motorPinReverse,int sensorPin) : InterInterface(sensorPin)
{
    _previousDistance = 0;
    _distance = 0;
    _velocity = 0;
    _frequency = 0;
    _motorPinForward = motorPinForward;
    _motorPinReverse = motorPinReverse;
    _sensorPin = sensorPin;
    _diameter = diameter;
    _ticks = ticks;
     _prevPulses = 0;
    _forward = true;

    _ticks = ticks;
    _const = M_PI*_diameter/ticks;
    _contol = new TractionControl(10);

}

double Wheel::distance(){
   if(_forward)
        return _distance;
    else
        return -_distance;
     
}

int Wheel::getFrequency(){
   return _frequency;
}

double Wheel::update() {
   
    //Find out the distance the wheel has turned from the pulses;
   

   //Avarage the pules to get a more accurate figure
   unsigned long pulses =  (_upPulse+_downPulse);

   //change in the pulses since last time
   unsigned int deltaPulses = pulses-_prevPulses;
   _prevPulses = pulses;


    if(_forward) {
        _distance = _distance + _const*deltaPulses;
        return _const*deltaPulses;
    } else {
        _distance = _distance - _const*deltaPulses;
        return -_const*deltaPulses;
    }
}
void Wheel::setFrequency(int frequency) {
   
   if(frequency > 255)
      frequency = 255;
   if(frequency < -255)
      frequency = -255; 
   //frequency = _contol->modify( frequency);
   if(frequency > 0) {
       _forward = true;
       pwm(_motorPinForward,frequency);
       pwm(_motorPinReverse,0);
   } else {
       _forward = false;
       pwm(_motorPinForward,0);
       pwm(_motorPinReverse,-frequency);
   }
   _frequency = frequency;
}

void Wheel::pwm(int pin,int duty) {

    analogWrite(pin,duty);

}
void Wheel::stop() {
   _frequency = 0;
   pwm(_motorPinReverse,0);
   pwm(_motorPinForward,0);
}

double Wheel::velocity() {
   return _velocity;
}

void Wheel::pullup() 
{
   pinMode(_pin, INPUT_PULLUP);
    
}

void Wheel::print() {
    Serial.print("| Wheel distance ");
    Serial.print(_distance,4);
    Serial.print(" pervious distance ");
    Serial.print(_previousDistance,4);
    Serial.print(" velocity ");
    Serial.print(_velocity);
    Serial.print(" frequency ");
    Serial.print(_frequency);
    Serial.print(" motor pin forward ");
    Serial.print(_motorPinForward);
    Serial.print(" motor pin reverse ");
    Serial.print(_motorPinReverse);
    Serial.print(" sensor pin ");
    Serial.print(_sensorPin);
    Serial.print(" diameter ");
    Serial.print(_diameter);
    Serial.print(" ticks ");
    Serial.print(_ticks);
    Serial.print(" previous pulses ");
    Serial.print(_prevPulses);
    if(_forward)
      Serial.print(" goforward ");
    else
      Serial.print(" backward ");
    Serial.print('|');
}




