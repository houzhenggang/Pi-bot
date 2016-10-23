/*
  Tractinion control controlling robot.
  Created by Kieran Wyse.
  Released into the public domain.
*/
#ifndef TRACTIONCONTROL_H
#define TRACTIONCONTROL_H




class TractionControl
{
  public:
  TractionControl(double maxchange);
  double getMaxChange();
  void setMaxChange(double maxchange);
  double modify(double frequency);
  private:
  double _maxchange;
  double _prevfreq;
};

#endif
