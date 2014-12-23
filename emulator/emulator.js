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
  if (millis() - last >= 20) {
    clearDisplay();
    pong();
    last = millis();
  }

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
var cpuPos = 31;

var ballDir = 1;
var ballAngle = 0; // between 0 and 1; this way we can keep it on the screen
var stepCount = 0;


var ballC = [5, 32];

function pong() {
  if (upPressed) {
    if (playerPos > 5)
      playerPos--;
  } 
  else if (downPressed) {
    if (playerPos < 58)
      playerPos++;
  }

  buildField();
  // bugs: when hitting the top wall, the ball just goes through.
  // if you hit a side wall
  if (ballC[1] == 0 || ballC[1] == 63) {
    ballAngle *= -1;
    ballC < 32 ? ballC[1] += 5 : ballC[1]--;
    console.log("bounce!");
  }

  // if you hit a paddle
  if (ballC[0] == 123 && Math.abs(playerPos-ballC[1]) <= 5) { 
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
  }

  if (ballC[0] > 128) { // player lost point
    ballDir = 1;
    ballC = [5, 32];
  } 
  else if (ballC[0] < 0) { // computer lost point
    ballDir = -1;
    ballC = [123, 32];
  }

  ballC[0] += ballDir;

  if (stepCount >= Math.floor(1/Math.abs(ballAngle))) {
    stepCount = 0;
    ballC[1] += 1 * (ballAngle >= 0 ? 1 : -1);
  }
  stepCount++;

  // ballC[1] += ballV[1];
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
  // reset all blocks to white except for the boundaries
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
