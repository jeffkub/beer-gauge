/*
  ADS1232.h - Library for reading from a ADS1232 24-bit ADC.
  Created by Jeffrey M. Kubascik, June 28, 2016.
  Released into the public domain.
*/
#ifndef ADS1232_h
#define ADS1232_h

#include <Arduino.h>
#include <SPI.h>

class ADS1232
{
  public:
    typedef enum
    {
      GAIN1 = 1,
      GAIN2,
      GAIN64,
      GAIN128
    } Gain;

    typedef enum
    {
      SLOW = 0,
      FAST
    } Speed;

    typedef enum
    {
      AIN1 = 0,
      AIN2,
      TEMP
    } Channel;

    ADS1232(int pin_sck, int pin_dout, int pin_pdwn, int pin_gain0, int pin_gain1, int pin_speed, int pin_a0, int pin_temp);

    void init(Gain gain = GAIN1, Speed speed = SLOW, Channel channel = AIN1);

    void enable(void);
    void disable(void);
    
    void setGain(Gain gain);
    void setSpeed(Speed speed);
    void setChannel(Channel channel);

    bool dataReady(void);
    int32_t read(void);

  private:
    int _pin_cs;
    int _pin_dout;
    int _pin_pdwn;
    int _pin_gain0;
    int _pin_gain1;
    int _pin_speed;
    int _pin_a0;
    int _pin_temp;

    SPISettings spi_settings;
};

#endif /* #ifndef ADS1232_h */

