/*
 * The code that keeps the time, displays it, plus a demo function to just run the clock up.
 * Stopwatch included.
*/

void demo() {
  if (minutes >= 60) {
    hours++;
    minutes = 0;
  }
  if (hours > 23)
    hours = 1;
  minutes++;
}

//void updateTime() {
//  DateTime now = rtc.now();
//  hours = now.hour();
//  minutes = now.minute();
//  seconds = now.second();
//  display.setTextSize(1);
//  display.setCursor(0,0);
//  display.print(now.unixtime());
//  display.display();
//}


void updateInternalTime() {
  ms += millis() - sinceLast;
  sinceLast = millis();
  if (ms >= 1000) {
    seconds += ms / 1000;
    ms = ms % 1000;
  }
  if (seconds >= 60) {
    minutes += seconds/60;
    seconds = seconds % 60;
  }
  if (minutes >= 60) {
    hours += minutes / 60;
    minutes = minutes % 60;
  }
  if (hours >= 24) {
    hours = 0;
  }
}

void timeTest() {
}
void digitalTime() {
//  display.clearDisplay();
  display.setTextSize(4);

  int h = hours % 12;
  if (h == 0) h = 12;

  if (h < 10)
    display.setCursor(17,10);
  else
    display.setCursor(5,10);
  
  display.print(h%12, DEC);
  display.print(":");
  if (minutes < 10)
    display.print("0");
  display.print(minutes, DEC);
  display.println();
  
  display.setCursor(110, 50);
  display.setTextSize(1);
  display.print(seconds, DEC);
}


int mins[][2] = {
                {64, 10}, {69, 11}, // :00
                {74, 12}, {79, 16}, // :05
                {83, 20}, {85, 26}, // :10
                {85, 32}, {84, 38}, // :15
                {83, 43}, {78, 49}, // :20
                {73, 52}, {68, 53}, // :25
                {64, 54}, {59, 53}, // :30
                {55, 52}, {50, 47}, // :35
                {45, 43}, {43, 38}, // :40
                {42, 32}, {44, 26}, // :45
                {45, 20}, {50, 16}, // :50
                {53, 14}, {59, 12}  // :55
};
           
int hors[][2] = {  
                {70, 23}, // 1
                {73, 27}, // 2
                {75, 32}, // 3
                {73, 37}, // 4
                {70, 42}, // 5
                {64, 43}, // 6
                {58, 40}, // 7
                {55, 37}, // 8
                {53, 32}, // 9
                {54, 27}, // 10
                {59, 24}, // 11
                {64, 21} // 12
};


void analogTime() {
  display.drawCircle(64, 32, 27, WHITE); // clock face
//  int mi = round((minutes/60*24)%23)%60;
  int mi = round(minutes/60.0*23.0);
  int hi = hours - 1;
  
  display.drawLine(64, 32, mins[mi][0], mins[mi][1], WHITE);
  display.drawLine(64, 32, hors[hi%12][0], hors[hi%12][1], WHITE);
  display.setCursor(110, 50);
  display.setTextSize(1);
  display.print(seconds, DEC);
}
