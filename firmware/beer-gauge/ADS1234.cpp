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

void ADS1234::init(Gain gain, Speed speed, Channel channel)
{
  SPI.setSCK(_pin_sclk);
  SPI.setMISO(_pin_dout);
  SPI.begin();
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE1));

  pinMode(_pin_pdwn, OUTPUT);
  pinMode(_pin_gain0, OUTPUT);
  pinMode(_pin_gain1, OUTPUT);
  pinMode(_pin_speed, OUTPUT);
  pinMode(_pin_a0, OUTPUT);
  pinMode(_pin_a1, OUTPUT);

  disable();

  setGain(gain);
  setSpeed(speed);
  setChannel(channel);

  delay(1);
  enable();
  
  return;
}

void ADS1234::enable(void)
{
  digitalWrite(_pin_pdwn, HIGH);
  
  return;
}

void ADS1234::disable(void)
{
  digitalWrite(_pin_pdwn, LOW);
  
  return;
}

void ADS1234::setGain(Gain gain)
{
  switch(gain)
  {
    case GAIN1:
    {
      digitalWrite(_pin_gain1, LOW);
      digitalWrite(_pin_gain0, LOW);
      break;
    }
    case GAIN2:
    {
      digitalWrite(_pin_gain1, LOW);
      digitalWrite(_pin_gain0, HIGH);
      break;
    }
    case GAIN64:
    {
      digitalWrite(_pin_gain1, HIGH);
      digitalWrite(_pin_gain0, LOW);
      break;
    }
    case GAIN128:
    {
      digitalWrite(_pin_gain1, HIGH);
      digitalWrite(_pin_gain0, HIGH);
      break;
    }
  }
  
  return;
}

void ADS1234::setSpeed(Speed speed)
{
  switch(speed)
  {
    case SLOW:
    {
      digitalWrite(_pin_speed, LOW);
      break;
    }
    case FAST:
    {
      digitalWrite(_pin_speed, HIGH);
      break;
    }
  }
  
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

bool ADS1234::dataReady(void)
{
  return digitalRead(_pin_dout) == LOW;
}

int32_t ADS1234::read(void)
{
  int32_t data = 0;

  while(dataReady() == false);

  data |= (uint32_t)SPI.transfer16(0) << 16;
  data |= (uint32_t)SPI.transfer16(0) <<  0;

  return data;
}

