const int clockPin = 4; //GPIO4
const int latchPin = 5; //GPIO5
const int dataPin = 16; //GPIO6
const int ramWritePin = 0; //GPIO10
const int resetPin = 9; //GPIO9


void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(ramWritePin, OUTPUT);
  pinMode(resetPin, OUTPUT);


  Serial.begin(115200);
}

void loop() {

  for (int addr = 0; addr <= 15; addr++) {
    Serial.println("BEEP");
    for (int numberToDisplay = 0; numberToDisplay <= 255; numberToDisplay++) {

      digitalWrite(latchPin, LOW);

      shiftOut(dataPin, clockPin, LSBFIRST, addr << 4);
      shiftOut(dataPin, clockPin, LSBFIRST, numberToDisplay);

      digitalWrite(latchPin, HIGH);

      delay(50);

      digitalWrite(ramWritePin, LOW);
      delayMicroseconds(100);
      digitalWrite(ramWritePin, HIGH);
      Serial.print(addr);
      Serial.print(" ");
      Serial.println(numberToDisplay);
      delay(100);

    }
  }



}
