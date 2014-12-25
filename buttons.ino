
int lastButtonStates[] = {0, 0, 0};
long lastDebounceTimes[] = {0, 0, 0};
long debounceDelay = 50;
int lastReadings[] = {0,0,0};

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
