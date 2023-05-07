const byte NOP = 0b00000000;
const byte LDA = 0b00010000;
const byte ADD = 0b00100000;
const byte SUB = 0b00110000;
const byte STA = 0b01000000;
const byte LDI = 0b01010000;
const byte JMP = 0b01100000;
const byte JC  = 0b01110000;
const byte JZ  = 0b10000000;
const byte OUT = 0b11100000;
const byte HLT = 0b11110000;

const int clockPin = 4;           //D2
const int latchPin = 5;           //D1
const int dataPin = 16;           //D0
const int ramWritePin = 0;        //D3
const int resetPin = 14;          //D5
const int setProgModePin = 12;    //D6
const int ramInputSelector = 13;  //D7
const int haltSignal = 15;        //D8

/*byte program[16] = {LDA | 14,
                    ADD | 15,
                    OUT,
                    JMP | 1,
                    0,
                    0,
                    0,
                    0,
                    0,
                    0,
                    0,
                    0,
                    0,
                    0,
                    0,
                    1
                   };
*/
//Fibonacci
byte program[16] = {LDI | 1,
                    STA | 14,
                    LDI | 0,
                    OUT,
                    ADD | 14,
                    STA | 15,
                    LDA | 14,
                    STA | 13,
                    LDA | 15,
                    STA | 14,
                    LDA | 13,
                    JC | 0,
                    JMP | 3,
                    0,
                    0,
                    1
                   };

void setup() {
  Serial.begin(115200);
  Serial.println("setup");
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  pinMode(ramWritePin, OUTPUT);
  pinMode(ramInputSelector, OUTPUT);
  pinMode(setProgModePin, OUTPUT);
  pinMode(haltSignal, OUTPUT);

  digitalWrite(haltSignal, HIGH);
  digitalWrite(setProgModePin, HIGH);
  digitalWrite(ramInputSelector, HIGH);
  
  for (int addr = 0; addr <= 15; addr++) {
    Serial.print("programming ");
    Serial.print(addr);
    Serial.print(" ");
    Serial.println(program[addr], BIN);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, addr << 4);
    shiftOut(dataPin, clockPin, LSBFIRST, program[addr]);
    digitalWrite(latchPin, HIGH);

    delay(50);

    digitalWrite(ramWritePin, LOW);
    delayMicroseconds(100);
    digitalWrite(ramWritePin, HIGH);

    delay(250);
  }
  
  digitalWrite(setProgModePin, LOW);
  digitalWrite(ramInputSelector, LOW);
  Serial.println("Done programming");

  digitalWrite(resetPin, HIGH);
  delay(10);
  digitalWrite(haltSignal, LOW);
  digitalWrite(resetPin, LOW);
}

void loop() {
}
