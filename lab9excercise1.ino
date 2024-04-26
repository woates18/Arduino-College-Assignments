// Include the Arduino library
#include <Arduino.h>

// pin connections
#define IA1_PIN 3
#define IA2_PIN 5
#define IB1_PIN 2
#define IB2_PIN 4

void setup() {
  // pin modes
  pinMode(IA1_PIN, OUTPUT);
  pinMode(IA2_PIN, OUTPUT);
  pinMode(IB1_PIN, OUTPUT);
  pinMode(IB2_PIN, OUTPUT);

  // Initialize the serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the serial input
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    // Change the polarity of the magnetic field
    switch (command) {
      case '1':
        digitalWrite(IA1_PIN, HIGH);
        digitalWrite(IA2_PIN, LOW);
        digitalWrite(IB1_PIN, LOW);
        digitalWrite(IB2_PIN, HIGH);
        Serial.println("Polarity changed to North-South");
        break;
      case '2':
        digitalWrite(IA1_PIN, LOW);
        digitalWrite(IA2_PIN, HIGH);
        digitalWrite(IB1_PIN, HIGH);
        digitalWrite(IB2_PIN, LOW);
        Serial.println("Polarity changed to South-North");
        break;
      default:
        Serial.println("Invalid command. Enter 1 or 2.");
        break;
    }
  }
}