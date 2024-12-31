#include "Arduino_LED_Matrix.h"

#define UP 0
#define DOWN 2
#define RIGHT 1
#define LEFT 3

// UP, RIGHT, DOWN, LEFT
byte currStates[] = {0, 0, 0, 0};
byte prevStates[] = {0, 0, 0, 0};

ArduinoLEDMatrix matrix;

const int HEIGHT = 8;
const int WIDTH = 12;

byte frame[HEIGHT][WIDTH] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

int x = 0;
int y = 0;


void setup()
{
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  Serial.begin(9600);
  matrix.begin();
}

bool justReleased(int key) {
  return currStates[key] == LOW && prevStates[key] == HIGH;
}

void loop()
{
  // read the state of the pushbutton value:
  currStates[UP] = digitalRead(3);
  currStates[RIGHT] = digitalRead(4);
  currStates[DOWN] = digitalRead(5);
  currStates[LEFT] = digitalRead(2);


  delay(10);

  frame[y][x] = 0;

  if (justReleased(UP)) {
    y = y - 1;
    if(y < 0) y=HEIGHT-1;
  }else if (justReleased(DOWN)) {
    y = y + 1;
    if(y >= HEIGHT) y=0;
  }
  
  if (justReleased(LEFT)) {
    x = x - 1;
    if(x < 0) x=WIDTH-1;
  }else if (justReleased(RIGHT)) {
   x = x + 1;
  if(x >= WIDTH) x=0;
  }

  frame[y][x] = 1;

  matrix.renderBitmap(frame, 8, 12);

  memcpy(prevStates, currStates, sizeof(byte)*4);
}