/*
  ADS1234.cpp - Library for reading from a ADS1232 or ADS1234 24-bit ADC.
  Created by Jeffrey M. Kubascik, June 28, 2016.
  Released into the public domain.
*/

#include <SPI.h>

#include "ADS1234.h"

ADS1234::ADS1234(int pin_dout, int pin_sclk, int pin_pdwn, int pin_gain0, int pin_gain1, int pin_speed, int pin_a0, int pin_a1) :
  _pin_dout(pin_dout),
  _pin_sclk(pin_sclk),
  _pin_pdwn(pin_pdwn),
  _pin_gain0(pin_gain0),
  _pin_gain1(pin_gain1),
  _pin_speed(pin_speed),
  _pin_a0(pin_a0),
  _pin_a1(pin_a1)
{
  return;
}

void ADS1234::init(void)
{
  SPI.setSCK(_pin_sclk);
  SPI.setMISO(_pin_dout);

  pinMode(_pin_pdwn, OUTPUT);
  pinMode(_pin_gain0, OUTPUT);
  pinMode(_pin_gain1, OUTPUT);
  pinMode(_pin_speed, OUTPUT);
  pinMode(_pin_a0, OUTPUT);
  pinMode(_pin_a1, OUTPUT);
  
  return;
}

void ADS1234::setGain(int gain)
{
  return;
}

void ADS1234::setSpeed(int speed)
{
  return;
}

void ADS1234::setChannel(Channel channel)
{
  switch(channel)
  {
    case AIN1:
    {
      digitalWrite(_pin_a1, LOW);
      digitalWrite(_pin_a0, LOW);
      break;
    }
    case AIN2:
    {
      digitalWrite(_pin_a1, LOW);
      digitalWrite(_pin_a0, HIGH);
      break;
    }
    case AIN3:
    {
      digitalWrite(_pin_a1, HIGH);
      digitalWrite(_pin_a0, LOW);
      break;
    }
    case AIN4:
    {
      digitalWrite(_pin_a1, HIGH);
      digitalWrite(_pin_a0, HIGH);
      break;
    }
  }
  
  return;
}

