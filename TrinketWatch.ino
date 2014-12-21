/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
  
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif



unsigned long stopWatchStart = -1;
int hours = 9;
int minutes = 50;

void setup() {
 Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  delay(200);
  display.clearDisplay();
  // text display tests
  display.setTextColor(WHITE);
}

void loop() {
  demo(); // update the time, now it's the demo but eventually it'll be a function calling the RTC
  digitalTime(); // display the time in a digital format.
}

void demo() {
  if (minutes >= 60) {
    hours++;
    minutes = 0;
  }
  if (hours > 23)
    hours = 1;
  minutes++;
}

void updateButtonStates() {
  
}

void digitalTime() {
  display.clearDisplay();
  display.setTextSize(4);

  if (hours < 10)
    display.setCursor(17,10);
  else
    display.setCursor(5,10);
  display.print(hours, DEC);
  display.print(":");
  if (minutes < 10)
    display.print("0");
  display.print(minutes, DEC);
  display.println();
  display.display();
  delay(200);
  
}

void stopwatch() {
  display.clearDisplay();
  display.setTextSize(2);
  if (stopWatchStart != -1) {
    unsigned long stopTime = millis() - stopWatchStart; 

    int days, hours, mins, secs;
    int fractime;
    unsigned long inttime;

    /*
      davekw7x from Arduino forms wrote the code to get mins, secs, etc. from milliseconds.
      http://forum.arduino.cc/index.php?topic=18588.0
    */

    inttime  = stopTime / 1000;
    fractime = stopTime % 1000;
    // inttime is the total number of number of seconds
    // fractimeis the number of thousandths of a second

    // number of days is total number of seconds divided by 24 divided by 3600
    days     = inttime / (24*3600);
    inttime  = inttime % (24*3600);

    // Now, inttime is the remainder after subtracting the number of seconds
    // in the number of days
    hours    = inttime / 3600;
    inttime  = inttime % 3600;

    // Now, inttime is the remainder after subtracting the number of seconds
    // in the number of days and hours
    mins     = inttime / 60;
    inttime  = inttime % 60;

    // Now inttime is the number of seconds left after subtracting the number
    // in the number of days, hours and minutes. In other words, it is the
    // number of seconds.
    secs = inttime;
    
    display.setCursor(5,10);
    if (mins < 10)
      display.print("0");
    display.print(mins, DEC);
    display.print(":");
    if (secs < 10)
      display.print("0");
    display.print(secs, DEC);
    display.print(":");
    int centisec = (int)floor(fractime / 10);
    if (centisec < 10)
      display.print("0");
    display.print(centisec);
    display.println();
    display.display();
  }
}


