#include "TractionControl.h"

TractionControl::TractionControl(double maxchange)
{
   _maxchange=maxchange;
   _prevfreq=0;
}

double TractionControl::getMaxChange()
{
    return _maxchange;
}
void TractionControl::setMaxChange(double maxchange)
{
    _maxchange=maxchange;
}
double TractionControl::modify(double frequency)
{
    
    if(frequency - _prevfreq > _maxchange)
    {
       frequency =  _prevfreq+_maxchange;
    }
    if(frequency - _prevfreq < -_maxchange)
    {
        frequency =  _prevfreq-_maxchange;
    }
    _prevfreq = frequency;
    return frequency;
    
}
