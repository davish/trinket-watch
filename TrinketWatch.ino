 /*********************************************************************
 * 
 * All functions defined here written by and (c) Davis Haupt under the MIT License.
 * 
 *
 * Graphics and Display Library Written by Limor Fried/Ladyada  for Adafruit Industries.  
 * BSD license, check license.txt for more information
 * All text above, and the splash screen must be included in any redistribution
 *********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 12
//#include "RTClib.h"

Adafruit_SSD1306 display(OLED_RESET);
//RTC_DS1307 rtc;

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int bpins[] = {5, 4, 3};
int buttons[] = {0, 0, 0};
long last = millis();

unsigned long sinceLast = millis();

int hours = 1;
int minutes = 0;
int seconds = 0;
int ms = 0;

void setup() { 
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  
  Serial.begin(9600);
  char h1[] = {__TIME__[0], __TIME__[1], '\0'};
  char m1[] = {__TIME__[3], __TIME__[4], '\0'};
  char s1[] = {__TIME__[6], __TIME__[7], '\0'};
  hours = atoi(h1);
  minutes = atoi(m1);
  seconds = atoi(s1);

//  Wire.begin();
//  rtc.begin();
//  
//  if (! rtc.isrunning()) {
//    Serial.println("RTC is NOT running!");
//    // following line sets the RTC to the date & time this sketch was compiled
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//    // This line sets the RTC with an explicit date & time, for example to set
//    // January 21, 2014 at 3am you would call:
//    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
//  }
  
  
  
  // initialize the display.
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display(); // display the splash screen that we have to
  delay(500);
  display.clearDisplay();
  // text display tests
  display.setTextColor(WHITE);  
  // INPUT_PULLUP because it's one less wire to solder per switch;
  // INPUT needs a connection to 3V and GND as well as the pin, INPUT_PULLUP you just attach to GND.
  pinMode(bpins[0], INPUT_PULLUP); 
  pinMode(bpins[1], INPUT_PULLUP);
  pinMode(bpins[2], INPUT_PULLUP);
  
}

int mnu = 0;
int timeMode = 0;


void loop() {
  updateInternalTime();
  display.clearDisplay();
  
  if (pressedOnce(1)) {
    mnu = (mnu + 1) % 4;
  }
  if (mnu == 0) {
    if (pressedOnce(0)) {
      timeMode = abs(timeMode-1) % 2;
    } else if (pressedOnce(2)) {
      timeMode = abs(timeMode+1) % 2;
    }
    if (millis() - last >= 40) {
      if (timeMode == 0)
        analogTime();
      else if (timeMode == 1)
        digitalTime();
      last = millis(); 
    }
  }
  else if (mnu == 1) {
    pong();
  } 
  else if (mnu == 2) {
    stopwatch();
  }
  else if (mnu == 3) {
    adjustTime();
  }
  display.display();
}


