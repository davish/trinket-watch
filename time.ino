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
