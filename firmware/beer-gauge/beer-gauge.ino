#include <Adafruit_SSD1305.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include "ADS1234.h"

#define LED         13

#define BUZZER       6

#define DISP_RESET  20
#define DISP_SCL    19
#define DISP_SDA    18

#define SCALE_DOUT  12
#define SCALE_SCLK  14
#define SCALE_PDWN   2
#define SCALE_GAIN0  0
#define SCALE_GAIN1  1
#define SCALE_SPEED  3
#define SCALE_A0     4
#define SCALE_A1     5

#define TOUCH_UP    15
#define TOUCH_DOWN  16
#define TOUCH_LEFT  22
#define TOUCH_RIGHT 23
#define TOUCH_ENTER 17
#define TOUCH_COM   25

Adafruit_SSD1305 display(DISP_RESET);
ADS1234 scale_adc(SCALE_DOUT, SCALE_SCLK, SCALE_PDWN, SCALE_GAIN0, SCALE_GAIN1, SCALE_SPEED, SCALE_A0, SCALE_A1);

void setup()
{
  Serial.begin(9600);

  /* Show splashscreen? */
  display.begin();
  display.display();

  scale_adc.init();

  return;
}

void loop()
{
  int touchVal;
  
  touchVal = touchRead(TOUCH_ENTER);

  Serial.print(touchVal);

  delay(1000);
  
  return;
}

