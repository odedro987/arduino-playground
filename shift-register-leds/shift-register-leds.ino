#define CLK_PIN 3
#define LATCH_PIN 4
#define SER_PIN 5

byte leds = 0b10000000;

void setup() {
  Serial.begin(9600);
  pinMode(LATCH_PIN, OUTPUT); // latch
  pinMode(CLK_PIN, OUTPUT); // clock
  pinMode(SER_PIN, OUTPUT); // serial
}


void writeBytes(byte data) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(SER_PIN, CLK_PIN, MSBFIRST, data);
  digitalWrite(LATCH_PIN, HIGH);
}

unsigned long timer = millis();

void loop() {
  if(millis() - timer <= 2000) {
    unsigned long step = (millis() - timer) / (2000 / 16);
    leds = 0b10000000 >> step;
    writeBytes(leds);
  }else {
    unsigned long step = (millis() - timer - 2000) / (2000 / 16);
    leds = 0b10000000;
    for(int i = 1; i <= step; i++){
      leds = (leds >> 1) + 0b10000000;
      Serial.println(leds, BIN);
    }
    writeBytes(leds);
  }
  if(millis() - timer > 4000){
      timer = millis();
  }
}
