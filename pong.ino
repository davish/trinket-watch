/*
PONG
Should be fun.
*/

int playerPos = 32;

int ballDir = 1;
float ballAngle = -1;
int stepCount = 0;

int ballC[] = {65, 62};

int cpuPos = 32;
int cpuDir = 0;

int playerScore = 0;
int CPUScore = 0;

boolean movePaddles = true;

void pong() {
  buildField();
  /*
    Paddle Logic, runs once for every step for the ball.
  */
  if (movePaddles) {
    if (buttons[0]) {
      if (playerPos > 5)
        playerPos--;
    } 
    else if (buttons[2]) {
      if (playerPos < 58)
        playerPos++;
    }

    if (cpuPos > ballC[1] && cpuPos > 5)
      cpuPos--;
    else if (cpuPos < ballC[1] && cpuPos < 58)
      cpuPos++;
    else {
      cpuPos = cpuPos;
    }
    movePaddles = false;
  } else {
    movePaddles = true;
  }

  /*
    Logic for the ball
  */
  if (ballC[1] == 0 || ballC[1] == 63) { // if it hits a wall
    Serial.println("Before");
    Serial.println(ballAngle);
    Serial.println(ballC[1]);
    ballAngle *= -1; // bounce
    ballC[1] += (ballC[1] > 32 ? -1 : 1);
    Serial.println("After");
    Serial.println(ballAngle);
    Serial.println(ballC[1]);
    Serial.println();
  }
  
  // if it hits a paddle
  if (ballC[0] == 123 && abs(playerPos-ballC[1]) <= 5) {  // player
    ballDir *= -1;
    switch(abs(playerPos-ballC[1])) {
      case 0:
        ballAngle = 0;
        break;
      case 1:
        ballAngle = .5;
        break;
      case 2:
        ballAngle = .6;
        break;
      case 3:
        ballAngle = .7;
        break;
      case 4:
        ballAngle = .8;
        break;
      case 5:
        ballAngle = .85;
        break;
    }
    ballAngle *= (playerPos-ballC[1] >= 0 ? -1 : 1);
  }
  else if (ballC[0] == 4 && abs(cpuPos-ballC[1]) <= 5) { // if u hit the CPU
    ballDir *= -1; // bounce
    switch(abs(cpuPos-ballC[1])) {
      case 0:
        ballAngle = 0;
        break;
      case 1:
        ballAngle = .5;
        break;
      case 2:
        ballAngle = .6;
        break;
      case 3:
        ballAngle = .7;
        break;
      case 4:
        ballAngle = .8;
        break;
      case 5:
        ballAngle = .85;
        break;
    }
    ballAngle *= (cpuPos-ballC[1] >= 0 ? -1 : 1);
  }

  ballC[0] += ballDir;

  if (stepCount >= floor(1/abs(ballAngle))) {
    stepCount = 0;
    ballC[1] += 1 * (ballAngle >= 0 ? 1 : -1);
  }
  stepCount++;

  if (ballC[0] > 128) { // player lost point
    CPUScore++;

    ballDir = -1;
    ballAngle = .5;
    ballC[0] = 63;
    ballC[1] = 1;
  } 
  else if (ballC[0] < 0) { // computer lost point
    playerScore++;

    ballDir = 1;
    ballAngle = -.5;
    ballC[0] = 65;
    ballC[1] = 62;
  }

  display.drawPixel(ballC[0], ballC[1], WHITE);

  display.drawLine(3, cpuPos-5, 3, cpuPos+5, WHITE);
  display.drawLine(124, playerPos-5, 124, playerPos+5, WHITE);
  
  display.setTextSize(2);
  display.setCursor(30, 0);
  display.print(CPUScore, DEC);
  display.setCursor(96, 0);
  display.println(playerScore, DEC);
}

void buildField() {
  for (int i = 1; i < 63; i=i+2)
    display.drawPixel(63, i, WHITE);
}

