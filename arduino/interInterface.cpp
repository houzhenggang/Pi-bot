#ifndef INTERINTERFACE_cpp
#define INTERINTERFACE_cpp

#include "InterInterface.h"

#include "Arduino.h"

#include <avr/io.h>


#include <avr/interrupt.h>    // Needed to use interrupts 

volatile uint8_t InterInterface::_registerHistoryB = PINB;
volatile uint8_t InterInterface::_registerHistoryC = PINC;
volatile uint8_t InterInterface::_registerHistoryD = PIND;

InterInterface *InterInterface::_regD[8] = {NULL};
InterInterface *InterInterface::_regC[8] = {NULL};
InterInterface *InterInterface::_regB[8] = {NULL};

void InterInterface::pullup() 
{
   pinMode(_pin, INPUT_PULLUP);
    
}


int InterInterface::pin() 
{
    return _pin;
}

bool InterInterface::trig() 
{
  if(_upPulse >0)
      return true;
   return false;
}
void InterInterface::reset() 
{
    _upPulse = 0;
    _downPulse = 0;
}



//InterInterface * InterInterface::_regB = new InterInterface[8];

//InterInterface::InterInterface() {}
InterInterface::InterInterface(int pin) {
    _pin = 0 ;
    _upPulse = 0;
    _downPulse = 0;
    _pin = pin;
    if(pin < 8) {
        _regD[pin] = this;
        PCMSK2 |= (1 << pin ) ;
	PCICR |= (1 << PCIE2); // set PCIE2 to enable PCMSK2 scan
    } else {
        _regB[pin-8] = this;
        PCMSK0 |= (1 << (pin-8) ) ;
        PCICR |= (1 << PCIE0); // set PCIE0 to enable PCMSK0 scan
    }
}

void InterInterface::callbackRegB() {
    uint8_t changedbits;

    
    changedbits = PINB ^ InterInterface::_registerHistoryB;
    InterInterface::_registerHistoryB = PINB;
    for(int i = 0; i <8; i++) {
      if(changedbits & 1 << i && _regB[i]) {
        if(PINB & 1 << i) {
           
           _regB[i]->trigLowHigh();
        } else {
           _regB[i]->trigHighLow();
        }
      }
    } 
}
void InterInterface::callbackRegC(){


     uint8_t changedbits;

 
    changedbits = PINC ^ InterInterface::_registerHistoryC;
    InterInterface::_registerHistoryC = PINC;
    for(int i = 0; i <8; i++) {
      if(changedbits & 1 << i && _regC[i]) {
        if(PINC & 1 << i) {
           _regC[i]->trigLowHigh();
        } else {
           _regC[i]->trigHighLow();
        }
      }
    } 
}

void InterInterface::callbackRegD(){


    uint8_t changedbits;

 
    changedbits = PIND ^ InterInterface::_registerHistoryD;
    InterInterface::_registerHistoryD = PIND;
    for(int i = 0; i <8; i++) {
      if(changedbits & 1 << i && _regD[i]) {
        if(PIND & 1 << i) {
           _regD[i]->trigLowHigh();
        } else {
           _regD[i]->trigHighLow();
        }
      }
    } 
}

int InterInterface::getDownPulse() {
   return InterInterface::_downPulse;
}
int InterInterface::getUpPulse() {
   return InterInterface::_upPulse;
}
void InterInterface::trigHighLow() {
  _downPulse++;
}
void InterInterface::trigLowHigh() {
  _upPulse++;
}



void InterInterface::print() 
{
    Serial.print("| InterInterface register history B:");
    Serial.print(InterInterface::_registerHistoryB,BIN);
     Serial.print(" register history C:");
    Serial.print(InterInterface::_registerHistoryC,BIN);
     Serial.print(" register history D:");
    Serial.println(InterInterface::_registerHistoryD,BIN);
    Serial.print("_regB[8]");
    Serial.print("_registery array B:");
    for(int i= 0; i < 8; i++) {
     Serial.print(" ");
     if(InterInterface::_regB[i])
        Serial.print(InterInterface::_regB[i]->_pin); 
     else 
        Serial.print("Null");
    }
    Serial.print("_registery array C:");
    for(int i= 0; i < 8; i++) {
     Serial.print(" ");
     if(InterInterface::_regC[i])
        Serial.print(InterInterface::_regC[i]->_pin); 
     else 
        Serial.print("Null");
    }
    Serial.print("_registery array D:");
    for(int i= 0; i < 8; i++) {
     Serial.print(" ");
     if(InterInterface::_regD[i])
        Serial.print(InterInterface::_regD[i]->_pin); 
     else
         Serial.print("Null");
    }
    Serial.print('\n');
    Serial.print(" up pulses:");
    Serial.print(InterInterface::_upPulse);
    Serial.print(" down pulses:");
    Serial.print(InterInterface::_downPulse);
    Serial.print(" |");
}


#endif
