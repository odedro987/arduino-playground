#include "led-matrix-driver.h"
#include "letters.h"
#include <string.h>
#include <math.h>

byte anodes[] = {9,14,8,12,1,7,2,5};
byte cathodes[] = {13,3,4,10,6,11,15,16};
byte pinMap[] = {6,5,A5,A4,4,A3,3,2,7,A2,13,8,12,9,11,10};

Matrix::Matrix() {
  timer = 0;
  mode = MODE_DEFAULT;
  memset(buffer, 0, sizeof(buffer));
}

Matrix::~Matrix() {
  
}

void Matrix::displayText(char* text, unsigned long duration, char space) {
  mode = MODE_TEXT;
  textDuration = duration;
  textSpace = space;
  strncpy(currentText, text, MAX_TEXT_LENGTH);
  timer = millis();
  currentTextStep = 0;
}

void Matrix::lerpText(byte buffer[8][8], char a, char b, char offset, char space) {
  char aCols = 8 - offset;
  if(aCols > 0){
    for(char col = 0; col < aCols; col++){
      for(char row = 0; row < 8; row++){
        buffer[row][col] = letters[a - 0x40 - 1][row][offset + col];
      }
    }
  }

  char spaceCols = 0;
  if(space > 0 && offset > 0 && offset < 8 + space) {
    if(offset < 8) spaceCols = min(space, offset);
    if(offset >= 8) spaceCols = min(space, 8);

    for(char col = 0; col < spaceCols; col++){
      for(char row = 0; row < 8; row++){
        buffer[row][aCols + col] = 0;
      }
    }
  }

  if(offset > 0 && offset - space > 0 && offset - space <= 8) {
    for(char col = 0; col < 8 - aCols - spaceCols; col++){
      for(char row = 0; row < 8; row++){
        buffer[row][aCols + space + col] = letters[b - 0x40 - 1][row][col];
      }
    }
  }
}

void Matrix::lightLedId(byte id) {
  digitalWrite(pinMap[anodes[id / 8] - 1], HIGH);
  digitalWrite(pinMap[cathodes[id % 8] - 1], LOW);
}

void Matrix::lightLed(byte anode, byte cathode) {
  digitalWrite(pinMap[anodes[anode] - 1], HIGH);
  digitalWrite(pinMap[cathodes[cathode] - 1], LOW);
}

void Matrix::begin() {
  for(int i = 0; i < sizeof(pinMap) / sizeof(byte); i++){
    pinMode(pinMap[i], OUTPUT);
  }
}

void Matrix::reset() {
  for(int i = 0; i < 8; i++) {
    digitalWrite(pinMap[anodes[i] - 1], LOW);
  }

  for(int i = 0; i < 8; i++) {
    digitalWrite(pinMap[cathodes[i] - 1], HIGH);
  }
}

void Matrix::render() {
  if(mode == MODE_DEFAULT) {
   
  }else if(mode == MODE_TEXT) {
    float elapsed = millis() - timer;
    int textLen = strnlen(currentText, MAX_TEXT_LENGTH);
    char totalSteps = (textLen * 8 + textSpace * textLen);
    float stepDuration = textDuration / totalSteps;
    if(elapsed >= textDuration){
      elapsed = elapsed - textDuration;
      timer = millis();
    }
    if(floor(elapsed / stepDuration) >= currentTextStep) {
      currentTextStep = floor(elapsed / stepDuration);
      char aLetter = floor(currentTextStep / (8 + textSpace));
      if(aLetter >= textLen) {
        aLetter = 0;
      }
      char bLetter = aLetter + 1;
      if(bLetter >= textLen) {
        bLetter = 0;
      }
      Matrix::lerpText(buffer, currentText[aLetter], currentText[bLetter], currentTextStep % (8 + textSpace), textSpace);
      if(currentTextStep >= totalSteps - 1) {
        currentTextStep = 0;
      }
    }
  }

   for(int i = 0; i < 8; i++) {
      reset();
      for(int j = 0; j < 8; j++) {
        if(buffer[i][j] == 1) {
          lightLed(i, j);
        }
      }
      delay(1);
    }
}

void Matrix::draw(byte matrix[8][8]) {
  memcpy(&buffer[0][0], &matrix[0][0], 8*8*sizeof(byte));
}

char min(char a, char b) {
  if(a <= b) return a;
  return b;
}