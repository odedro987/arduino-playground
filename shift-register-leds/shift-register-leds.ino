#include <stdint.h>

#define CLK_PIN 3
#define LATCH_PIN 4
#define SER_PIN 5

uint16_t leds = 0b1000000000000000;

void setup() {
  Serial.begin(9600);
  pinMode(LATCH_PIN, OUTPUT); // latch
  pinMode(CLK_PIN, OUTPUT); // clock
  pinMode(SER_PIN, OUTPUT); // serial
}


void writeBytes(uint16_t data) {
  uint8_t chunks[2] = { (data >> 8) & 0xff, data & 0xff };
  char test[1024];
  sprintf(test, "data: %d, c1: %d, c2: %d", data, chunks[0], chunks[1]);
  Serial.println(test);
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(SER_PIN, CLK_PIN, LSBFIRST, chunks[0]);
  shiftOut(SER_PIN, CLK_PIN, LSBFIRST, chunks[1]);
  digitalWrite(LATCH_PIN, HIGH);
}

unsigned long timer = millis();

void loop() {
  if(millis() - timer <= 2000) {
    unsigned long step = (millis() - timer) / (2000 / 16);
    leds = 0b1000000000000000 >> step;
    writeBytes(leds);
  }else {
    unsigned long step = (millis() - timer - 2000) / (2000 / 16);
    leds = 0b1000000000000000;
    for(int i = 1; i <= step; i++){
      leds = (leds >> 1) + 0b1000000000000000;
    }
    writeBytes(leds);
  }
  if(millis() - timer > 4000){
      timer = millis();
  }
}
