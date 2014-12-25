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

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int bpins[] = {8, 9, 10};// pin 2 isn't exposed on the trinket, just a placeholder.
int buttons[] = {0, 0, 0};
long last = millis();

void setup() {
  
  // INPUT_PULLUP because it's one less wire to soler per switch;
  // INPUT needs a connection to 3V and GND as well as the pin, INPUT_PULLUP you just attach to GND.
  pinMode(bpins[0], INPUT_PULLUP); 
  pinMode(bpins[1], INPUT_PULLUP);
  pinMode(bpins[2], INPUT_PULLUP);
  
  Serial.begin(9600);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display(); // display the splash screen that we have to
  delay(500);
  display.clearDisplay();
  // text display tests
  display.setTextColor(WHITE);
  
}

int mnu = 0;
int timeMode = 0;


void loop() {
  if (pressedOnce(1)) {
    mnu = (mnu + 1) % 3;
  }
  if (mnu == 0) {
    if (pressedOnce(0)) {
      timeMode = abs(timeMode-1) % 2;
    } else if (pressedOnce(2)) {
      timeMode = abs(timeMode+1) % 2;
    }
    if (millis() - last >= 40) {
      display.clearDisplay();
      demo();
      if (timeMode == 0)
        analogTime();
      else if (timeMode == 1)
        digitalTime();
      last = millis(); 
    }
  }
  else if (mnu == 1) {
    display.clearDisplay();
    pong();
  } else if (mnu == 2) {
    display.clearDisplay();
    stopwatch();
  }
}


