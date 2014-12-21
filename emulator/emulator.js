window.SQUARE_SIZE = 5;

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

function step() {
  smile();
}

function smile() {
  // face
  gfx.drawCircle(64, 32, 10);

  // eyes
  drawPixel(60, 28);
  drawPixel(68, 28);

  // mouth
  gfx.drawLine(60, 35, 68, 35);
  drawPixel(60, 34);
  drawPixel(68, 34);
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
*/

var gfx = {
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
