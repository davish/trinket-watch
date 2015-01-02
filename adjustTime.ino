int adjustMenu = 0;

void adjustTime() {
  
  if (pressedOnce(0)) {
    switch(adjustMenu) {
      case 0:
        hours++;
        break;
      case 1:
        minutes++;
        break;
    }
  }
  else if (pressedOnce(2)) {
    adjustMenu = (adjustMenu + 1) % 2;
  }
  
  if (minutes >= 60) {
    minutes = 0;
    hours++;
  }
  if (hours >= 24)
    hours = 0;
  display.setTextSize(4);
  int h = hours;
  if (hours == 0) {
    h = 12;
  }
  if (h < 10)
    display.setCursor(17,20);
  else
    display.setCursor(5,20);
  
  display.print(h, DEC);
  display.print(":");
  if (minutes < 10)
    display.print("0");
  display.print(minutes, DEC);
  display.println();
  
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print((adjustMenu == 0) ? "H" : "M");
  display.setCursor(20, 0);
  display.print("ADJUST TIME");
  
}
