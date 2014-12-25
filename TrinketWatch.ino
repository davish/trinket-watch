/*********************************************************************
 * This is an example for our Monochrome OLEDs based on SSD1306 drivers
 * 
 * Pick one up today in the adafruit shop!
 * ------> http://www.adafruit.com/category/63_98
 * 
 * This example is for a 128x64 size display using I2C to communicate
 * 3 pins are required to interface (2 I2C and one reset)
 * 
 * Adafruit invests time and resources providing this open source code, 
 * please support Adafruit and open-source hardware by purchasing 
 * products from Adafruit!
 * 
 * Written by Limor Fried/Ladyada  for Adafruit Industries.  
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



// Button Variables

int bpins[] = {8, 9, 10};// pin 2 isn't exposed on the trinket, just a placeholder.
int buttons[] = {0, 0, 0};
int lastButtonStates[] = {0, 0, 0};
long lastDebounceTimes[] = {0, 0, 0};
long debounceDelay = 50;

long last = millis();
int lastReadings[] = {0,0,0};

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
    mnu = (mnu + 1) % 2;
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
  }  
}

void menu() {
  boolean b = true;
  display.setTextSize(1);
  int m = 0;
  while (b) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Time\nPong");
    if (pressedOnce(0))
      m = abs(m-1) % 2;
    else if (pressedOnce(2))
      m = abs(m+1) % 2;
    else if (pressedOnce(1))
      Serial.println(m);
    
    
    if (m == 0) {
      display.setCursor(30, 0);
    }
    else {
      display.setCursor(30, 10);
    }
    display.println("*");
    display.display();
  }
}


void updateButtonStates() {
  for (int i = 0; i < 3; ++i) {
    int reading = digitalRead(bpins[i]);
    if (reading != lastButtonStates[i]) {
      lastDebounceTimes[i] = millis();
    }
    if ((millis() - lastDebounceTimes[i]) > debounceDelay) {
      if (reading == LOW) {
       buttons[i] = 1;
      } else {
       buttons[i] = 0;
      } 
    }
    lastButtonStates[i] = reading;
  }
}

boolean pressedOnce(int b) {
  updateButtonStates();
  boolean r;
  if (buttons[b] != lastReadings[b] && buttons[b])
    r = true;
  else
    r = false;
  lastReadings[b] = buttons[b];
  return r;
}
