#include "led-matrix-driver.h"
#include "letters.h"

Matrix matrix;

void setup() {
  // Serial.begin(9600);
  matrix.begin();
}

byte heart[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,1,0,0,1,0,0},
  {0,1,0,1,1,0,1,0},
  {1,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0},
  {0,1,0,0,0,1,0,0},
  {0,0,1,0,1,0,0,0},
  {0,0,0,1,0,0,0,0},
};

byte frame[8][8] = {};

void getFrame(unsigned long elapsed) {
  if(elapsed < LENGTH / 2){
    for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
        if(i * 8 + j <= (elapsed / (LENGTH / 2.0)) * 63) {
          frame[i][j] = 1;
        }else{
          frame[i][j] = 0;
        }
      }
    }
  }else{ 
    for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
        if(i * 8 + j <= ((elapsed - 2000) / (LENGTH / 2)) * 63) {
          frame[j][i] = 1;
        }else{
          frame[j][i] = 0;
        }
      }
    }
  }
}

unsigned long timer = millis();

int index = 0;

void loop() {
  if(millis() - timer >= LENGTH) {
    timer = millis();
    index = (index + 1) % 26;
  }
  // getFrame(millis() - timer);
  matrix.draw(letters[index]);
  matrix.render();
}
