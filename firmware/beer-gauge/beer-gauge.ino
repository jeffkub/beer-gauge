#include <limits.h>
#include <SPI.h>

#include <Adafruit_SSD1305.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include "ADS1232.h"
#include "pitches.h"

#define SPI_SCK     13
#define SPI_MOSI    11
#define SPI_MISO    12

#define LED         20

#define BUZZER       6

#define SWITCH_RST  21

#define DISP_RESET   8
#define DISP_CS     10
#define DISP_DC      9

#define SCALE_CS     7
#define SCALE_PDWN   2
#define SCALE_GAIN0  0
#define SCALE_GAIN1  1
#define SCALE_SPEED  3
#define SCALE_A0     4
#define SCALE_TEMP   5

#define TOUCH_UP    15
#define TOUCH_DOWN  16
#define TOUCH_LEFT  22
#define TOUCH_RIGHT 23
#define TOUCH_ENTER 17
#define TOUCH_COM   25

Adafruit_SSD1305 display(DISP_DC, DISP_RESET, DISP_CS);
ADS1232 scale_adc(SCALE_CS, SPI_MISO, SCALE_PDWN, SCALE_GAIN0, SCALE_GAIN1, SCALE_SPEED, SCALE_A0, SCALE_TEMP);

void setup()
{
  Serial.begin(9600);

  /* Initialize SPI bus */
  SPI.setSCK(SPI_SCK);
  SPI.setMOSI(SPI_MOSI);
  SPI.setMISO(SPI_MISO);
  SPI.begin();

  /* Initialize I2C bus */

  /* Show splashscreen? */
  display.begin();
  display.display();

  scale_adc.init(ADS1232::GAIN128);

  tone(BUZZER, NOTE_C4, 250);
  
  return;
}

void loop()
{
  int touchval;
  int32_t scaleval;
  
  touchval = touchRead(TOUCH_ENTER);
  scaleval = scale_adc.read();

  Serial.print(touchval);
  Serial.print(scaleval);

  delay(1000);
  
  return;
}

