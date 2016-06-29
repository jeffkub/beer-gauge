/*
  ADS1234.h - Library for reading from a ADS1232 or ADS1234 24-bit ADC.
  Created by Jeffrey M. Kubascik, June 28, 2016.
  Released into the public domain.
*/
#ifndef ADS1234_h
#define ADS1234_h

#include "Arduino.h"

class ADS1234
{
  public:
    typedef enum
    {
      AIN1,
      AIN2,
      AIN3,
      AIN4
    } Channel;
  
    ADS1234(int pin_dout, int pin_sclk, int pin_pdwn, int pin_gain0, int pin_gain1, int pin_speed, int pin_a0, int pin_a1);

    void init(void);
    
    void setGain(int gain);
    void setSpeed(int speed);
    void setChannel(Channel channel);

  private:
    int _pin_dout;
    int _pin_sclk;
    int _pin_pdwn;
    int _pin_gain0;
    int _pin_gain1;
    int _pin_speed;
    int _pin_a0;
    int _pin_a1;
};

#endif /* #ifndef ADS1234_h */

