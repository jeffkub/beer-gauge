/*
  ADS1232.cpp - Library for reading from a ADS1232 24-bit ADC.
  Created by Jeffrey M. Kubascik, June 28, 2016.
  Released into the public domain.
*/

#include "ADS1232.h"

ADS1232::ADS1232(int pin_cs, int pin_dout, int pin_pdwn, int pin_gain0, int pin_gain1, int pin_speed, int pin_a0, int pin_temp) :
  _pin_cs(pin_cs),
  _pin_dout(pin_dout),
  _pin_pdwn(pin_pdwn),
  _pin_gain0(pin_gain0),
  _pin_gain1(pin_gain1),
  _pin_speed(pin_speed),
  _pin_a0(pin_a0),
  _pin_temp(pin_temp),
  spi_settings(2000000, MSBFIRST, SPI_MODE1)
{
  return;
}

void ADS1232::init(Gain gain, Speed speed, Channel channel)
{
  pinMode(_pin_cs, OUTPUT);
  pinMode(_pin_pdwn, OUTPUT);
  pinMode(_pin_gain0, OUTPUT);
  pinMode(_pin_gain1, OUTPUT);
  pinMode(_pin_speed, OUTPUT);
  pinMode(_pin_a0, OUTPUT);
  pinMode(_pin_temp, OUTPUT);

  disable();

  setGain(gain);
  setSpeed(speed);
  setChannel(channel);

  delay(1);
  enable();
  
  return;
}

void ADS1232::enable(void)
{
  digitalWrite(_pin_pdwn, HIGH);
  
  return;
}

void ADS1232::disable(void)
{
  digitalWrite(_pin_pdwn, LOW);
  
  return;
}

void ADS1232::setGain(Gain gain)
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

void ADS1232::setSpeed(Speed speed)
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

void ADS1232::setChannel(Channel channel)
{
  switch(channel)
  {
    case AIN1:
    {
      digitalWrite(_pin_temp, LOW);
      digitalWrite(_pin_a0, LOW);
      break;
    }
    case AIN2:
    {
      digitalWrite(_pin_temp, LOW);
      digitalWrite(_pin_a0, HIGH);
      break;
    }
    case TEMP:
    {
      digitalWrite(_pin_temp, HIGH);
      digitalWrite(_pin_a0, LOW);
      break;
    }
  }
  
  return;
}

bool ADS1232::dataReady(void)
{
  return digitalRead(_pin_dout) == LOW;
}

int32_t ADS1232::read(void)
{
  int32_t data = 0;

  while(dataReady() == false);

  SPI.beginTransaction(spi_settings);
  digitalWrite(_pin_cs, LOW);
  
  data |= (uint32_t)SPI.transfer16(0) << 16;
  data |= (uint32_t)SPI.transfer16(0) <<  0;

  digitalWrite(_pin_cs, HIGH);
  SPI.endTransaction();

  return data;
}

