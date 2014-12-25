window.SQUARE_SIZE = 5;

var startTime = Date.now();
function initScreen(id){
  // initialize the canvas and grid, with the width and height as parameters
  window.canvas = document.getElementById(id);

  window.grid_width = Math.floor(canvas.width / SQUARE_SIZE); 
  window.grid_height = Math.floor(canvas.height / SQUARE_SIZE);

  if (canvas.getContext){
    window.ctx = canvas.getContext('2d');
    clearDisplay();
    window.startTime = Date.now();
    window.loop = setInterval(step, 1); // fastest delay between cycles in JS.
  }
}

var last = millis();
function step() {
  if (millis() - last >= 10) {
    clearDisplay();
    // demo();
    // analogTime();
    pong();
    last = millis();
  }
}

var m = [
                [64, 10], [69, 11], // :00
                [74, 12], [79, 16], // :05
                [83, 20], [85, 26], // :10
                [85, 32], [84, 38], // :15
                [83, 43], [78, 49], // :20
                [73, 52], [68, 53], // :25
                [64, 54], [59, 53], // :30
                [55, 52], [50, 47], // :35
                [45, 43], [43, 38], // :40
                [42, 32], [44, 26], // :45
                [45, 20], [50, 16], // :50
                [53, 14], [59, 12]  // :55
              ];


var h = [  
                [70, 23], // 1
                [73, 27], // 2
                [75, 32], // 3
                [73, 37], // 4
                [70, 42], // 5
                [64, 43], // 6
                [58, 40], // 7
                [55, 37], // 8
                [53, 32], // 9
                [54, 27], // 10
                [59, 24], // 11
                [64, 21] // 12
]

var hours = 12;
var minutes = 0;
function analogTime() {
  display.drawCircle(64, 32, 27); // clock face

  var mi = Math.round((minutes/60*24)%23);
  var hi = hours - 1;

  display.drawLine(64, 32, m[mi%60][0], m[mi%60][1]);
  display.drawLine(64, 32, h[hi%12][0], h[hi%12][1]);
}

function demo() {
  if (minutes >= 60) {
    hours++;
    minutes = 0;
  }
  if (hours > 23)
    hours = 1;
  minutes++;
}

var upPressed = false;
var downPressed = false;

window.onkeydown = function(e) {
  if (e.which == 38) {
    upPressed = true;
  }
  else if (e.which == 40) {
    downPressed = true;
  }
};
window.onkeyup = function(e) {
  if (e.which == 38) {
    upPressed = false;
  }
  else if (e.which == 40) {
    downPressed = false;
  }
}

var playerPos = 32;

var ballDir = -1;
var ballAngle = 0; // between 0 and 1; this way we can keep it on the screen
var stepCount = 0;

var ballC = [20, 32];

var movePaddles = true;

var cpuPos = 34;
var cpuDir = 1;

var strategy = false;

ballDir = 1;
ballAngle = -.5;
ballC = [65, 62];

var scorePlayer = 0;
var scoreCPU = 0;

function pong() {
  buildField();
  /*
    Paddle Logic, runs once for every step for the ball.
  */
  if (movePaddles) {
    if (upPressed) {
      if (playerPos > 5)
        playerPos--;
    } 
    else if (downPressed) {
      if (playerPos < 58)
        playerPos++;
    }

    if (cpuPos > ballC[1] && cpuPos > 5)
      cpuPos--;
    else if (cpuPos < ballC[1] && cpuPos < 58)
      cpuPos++;
    else {
      cpuPos = cpuPos;

      /*if (ballDir > 0) { // ball's heading away from us
        strategy = false; // just let it ride
        cpuPos = cpuPos;
      } else {
        strategy = true;
        if (true && cpuPos > 5 && cpuPos < 58) { // Math.abs(playerPos - cpuPos) < 15
          if (Math.abs(cpuPos - ballC[1]) < 3 || Math.abs(cpuPos - ballC[1]) > 3) {
            console.log(Math.abs(cpuPos - ballC[1]));
            cpuPos += (Math.abs(playerPos - ballC[1]) > 0 ? 1 : -1);
          } else {
            cpuPos = cpuPos;
          }
        } else {
          cpuPos = cpuPos; // the player might be too far away to catch it in time, so hit it straight.
        }
      } */
    }
    movePaddles = false;
  } else {
    movePaddles = true;
  }

  /*
    Logic for the ball
  */
  if (ballC[1] == 0 || ballC[1] == 63) {
    ballAngle *= -1;
    ballC[1] += (ballC[1] > 32 ? -1 : 1);
  }

  // if it hits a paddle
  if (ballC[0] == 123 && Math.abs(playerPos-ballC[1]) <= 5) {  // player
    ballDir *= -1;
    switch(Math.abs(playerPos-ballC[1])) {
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
  else if (ballC[0] == 4 && Math.abs(cpuPos-ballC[1]) <= 5) { // if u hit the CPU
    ballDir *= -1; // bounce
    switch(Math.abs(cpuPos-ballC[1])) {
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

  if (ballC[0] > 128) { // player lost point
    scoreCPU++;
    console.log("CPU:" + scoreCPU + " Player:" + scorePlayer);

    ballDir = -1;
    ballAngle = .5;
    ballC = [63, 1];
  } 
  else if (ballC[0] < 0) { // computer lost point
    scorePlayer++;
    console.log("CPU:" + scoreCPU + " Player:" + scorePlayer);

    ballDir = 1;
    ballAngle = -.5;
    ballC = [65, 62];
  }

  ballC[0] += ballDir;

  if (stepCount >= Math.floor(1/Math.abs(ballAngle))) {
    stepCount = 0;
    ballC[1] += 1 * (ballAngle >= 0 ? 1 : -1);
  }
  stepCount++;

  display.drawPixel(ballC[0], ballC[1]);

  display.drawLine(3, cpuPos-5, 3, cpuPos+5);
  display.drawLine(124, playerPos-5, 124, playerPos+5)
}

function buildField() {
  for (var i = 1; i < 63; i=i+2)
    display.drawPixel(63, i);
}

function smile() {
  // face
  display.drawCircle(64, 32+dy, 10);

  // eyes
  drawPixel(60, 28+dy);
  drawPixel(68, 28+dy);

  // mouth
  display.drawLine(60, 35+dy, 68, 35+dy);
  drawPixel(60, 34+dy);
  drawPixel(68, 34+dy);
}

function clearDisplay() {
  for (var x = 0; x < grid_width; x++) {
    for(var y = 0; y < grid_height; y++) {
      drawPixel(x,y, true);
    }
  }
}

function drawPixel(x, y, inverted) {
  ctx.fillStyle = inverted ? "#000000" : "#FFFFFF";
  ctx.fillRect(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
}

function drawGrid(interval) {
  // draw a grid with the interval between lines in px for dev purposes
  ctx.beginPath();
  for (var x = interval; x < canvas.width; x=x+interval) {
    ctx.moveTo(x, 0);
    ctx.lineTo(x, canvas.height);
  }

  for (var y = interval; y < canvas.height; y=y+interval) {
    ctx.moveTo(0, y);
    ctx.lineTo(canvas.width, y);
  }
  ctx.stroke(); 
}

function millis() {
  return Date.now() - startTime;
}


/*
  Functions ported from the Adafruit Graphics Library
  https://github.com/adafruit/Adafruit-GFX-Library


  Software License Agreement (BSD License)

  Copyright (c) 2012 Adafruit Industries.  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  - Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

*/

var display = {
  drawPixel: drawPixel,
  drawCircle: function(x0, y0, r, color) {
    if (color)
      color = true;
    else
      color = false;

    var f = 1 - r;
    var ddF_x = 1;
    var ddF_y = -2 * r;
    var x = 0;
    var y = r;

    drawPixel(x0  , y0+r, color);
    drawPixel(x0  , y0-r, color);
    drawPixel(x0+r, y0  , color);
    drawPixel(x0-r, y0  , color);

    while (x<y) {
      if (f >= 0) {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x;
    
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 - x, y0 + y, color);
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 - x, y0 - y, color);
      drawPixel(x0 + y, y0 + x, color);
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 + y, y0 - x, color);
      drawPixel(x0 - y, y0 - x, color);
    }
  },
  drawLine: function(x0, y0, x1, y1, color) {
    if (color)
      color = true;
    else
      color = false;

    var steep = Math.abs(y1 - y0) > Math.abs(x1 - x0);
    if (steep) {
      // swap(x0, y0);
      var temp =  x0;
      x0 = y0;
      y0 = temp;
      // swap(x1, y1);
      temp = x1;
      x1 = y1;
      y1 = temp;
    }

    if (x0 > x1) {
      // swap(x0, x1);
      var temp =  x0;
      x0 = x1;
      x1 = temp;
      // swap(y0, y1);
      temp = y0;
      y0 = y1;
      y1 = temp;
    }

    var dx, dy;
    dx = x1 - x0;
    dy = Math.abs(y1 - y0);

    var err = dx / 2;
    var ystep;

    if (y0 < y1) {
      ystep = 1;
    } else {
      ystep = -1;
    }

    for (; x0<=x1; x0++) {
      if (steep) {
        drawPixel(y0, x0, color);
      } else {
        drawPixel(x0, y0, color);
      }
      err -= dy;
      if (err < 0) {
        y0 += ystep;
        err += dx;
      }
    }
  }
}
