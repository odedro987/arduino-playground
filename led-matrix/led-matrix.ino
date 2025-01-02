byte anodes[] = {9,14,8,12,1,7,2,5};
byte cathodes[] = {13,3,4,10,6,11,15,16};

byte pinMap[] = {6,5,A5,A4,4,A3,3,2,7,A2,13,8,12,9,11,10};

void lightLedId(byte id) {
  digitalWrite(pinMap[anodes[id / 8] - 1], HIGH);
  digitalWrite(pinMap[cathodes[id % 8] - 1], LOW);
}

void lightLed(byte anode, byte cathode) {
  digitalWrite(pinMap[anodes[anode] - 1], HIGH);
  digitalWrite(pinMap[cathodes[cathode] - 1], LOW);
}

void setup() {
  pinMode(2, OUTPUT); // pin 8
  pinMode(3, OUTPUT); // pin 7
  pinMode(4, OUTPUT); // pin 5
  pinMode(5, OUTPUT); // pin 2
  pinMode(6, OUTPUT); // pin 1
  pinMode(7, OUTPUT); // pin 9
  pinMode(8, OUTPUT); // pin 12
  pinMode(9, OUTPUT); // pin 14
  pinMode(A2, OUTPUT); // pin 10
  pinMode(A3, OUTPUT); // pin 6
  pinMode(A4, OUTPUT); // pin 4
  pinMode(A5, OUTPUT); // pin 3
  pinMode(10, OUTPUT); // pin 16
  pinMode(11, OUTPUT); // pin 15
  pinMode(12, OUTPUT); // pin 13
  pinMode(13, OUTPUT); // pin 11
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

void resetMatrix() {
  for(int i = 0; i < 8; i++) {
    digitalWrite(pinMap[anodes[i] - 1], LOW);
  }

  for(int i = 0; i < 8; i++) {
    digitalWrite(pinMap[cathodes[i] - 1], HIGH);
  }
}

void lightMatrix(byte matrix[8][8]) {
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

void loop() {
  lightMatrix(heart);
}
