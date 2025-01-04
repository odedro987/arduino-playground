#include "led-matrix-driver.h"

byte anodes[] = {9,14,8,12,1,7,2,5};
byte cathodes[] = {13,3,4,10,6,11,15,16};
byte pinMap[] = {6,5,A5,A4,4,A3,3,2,7,A2,13,8,12,9,11,10};

Matrix::Matrix() {

}

void Matrix::lightLedId(byte id) {
  digitalWrite(pinMap[anodes[id / 8] - 1], HIGH);
  digitalWrite(pinMap[cathodes[id % 8] - 1], LOW);
}

void Matrix::lightLed(byte anode, byte cathode) {
  digitalWrite(pinMap[anodes[anode] - 1], HIGH);
  digitalWrite(pinMap[cathodes[cathode] - 1], LOW);
}

void Matrix::setupPins() {
  for(int i = 0; i < sizeof(pinMap) / sizeof(byte); i++){
    pinMode(pinMap[i], OUTPUT);
  }
}

void Matrix::resetMatrix() {
  for(int i = 0; i < 8; i++) {
    digitalWrite(pinMap[anodes[i] - 1], LOW);
  }

  for(int i = 0; i < 8; i++) {
    digitalWrite(pinMap[cathodes[i] - 1], HIGH);
  }
}

void Matrix::lightMatrix(byte matrix[8][8]) {
  for(int i = 0; i < 8; i++) {
    resetMatrix();
    for(int j = 0; j < 8; j++) {
      if(matrix[i][j] == 1) {
        lightLed(i, j);
      }
    }
    delay(1);
  }
}

void Matrix::scrollFrame(int offset) {

}
