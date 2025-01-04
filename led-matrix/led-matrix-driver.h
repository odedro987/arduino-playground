#ifndef LED_MATRIX_DRIVER_h
#define LED_MATRIX_DRIVER_h

#include "Arduino.h"

#define LENGTH 1000.0

extern byte anodes[8];
extern byte cathodes[8];
extern byte pinMap[16];

class Matrix {
  public:
    Matrix();
    ~Matrix();
    void setupPins();
    void resetMatrix();
    void lightMatrix();
    void scrollFrame(int offset);
    void draw(byte matrix[8][8]);
  private:
    void lightLedId(byte id);
    void lightLed(byte anode, byte cathode);

    byte frame[8][8];
    unsigned long timer;
};

#endif