#include "Morse.h"

Morse morse(13);

void setup() {
  Serial.begin(9600);
}

void loop() {
  morse.dot(); morse.dot(); morse.dot();
  morse.dash(); morse.dash(); morse.dash();
  morse.dot(); morse.dot(); morse.dot();
  delay(3000);
}
