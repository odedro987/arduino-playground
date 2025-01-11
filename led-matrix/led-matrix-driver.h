#ifndef LED_MATRIX_DRIVER_h
#define LED_MATRIX_DRIVER_h

#include "Arduino.h"

#define LENGTH 1000.0

#define MAX_TEXT_LENGTH 20

#define MODE_DEFAULT 0
#define MODE_TEXT 1

extern byte anodes[8];
extern byte cathodes[8];
extern byte pinMap[16];

class Matrix {
  public:
    Matrix();
    ~Matrix();
    void begin();
    void reset();
    void render();
    void draw(byte matrix[8][8]);
    void displayText(char* text, unsigned long duration, char space);
  private:
    void lightLedId(byte id);
    void lightLed(byte anode, byte cathode);
    void lerpText(byte buffer[8][8], char a, char b, char offset, char space);

    byte buffer[8][8];
    unsigned long timer;
    char currentText[MAX_TEXT_LENGTH];
    char textSpace;
    unsigned long textDuration;
    char currentTextStep;
    char mode;

};

#endif