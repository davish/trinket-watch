long stopWatchStart = -1;
long lastLoop = millis();
boolean paused = false;
void stopwatch() {
  unsigned long stopTime;
  

  if (pressedOnce(0)) {
    if (stopWatchStart == -1) {
      stopWatchStart = millis();
    } else {
      paused = !paused;
    }
  } 
  else if (pressedOnce(2) && paused) {
    stopWatchStart = -1;
    paused = false;
  }
  
  if (paused) {
    stopWatchStart += (millis() - lastLoop);
  }
  lastLoop = millis();
  if (stopWatchStart != -1) {
    stopTime = millis() - stopWatchStart; 
  }
  else {
    stopTime = 0;
  }
  
  int days, hours, mins, secs;
  int fractime;
  days = hours = mins = secs = fractime = 0;
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

  display.setTextSize(2);
  display.setCursor(17,20);
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
}
