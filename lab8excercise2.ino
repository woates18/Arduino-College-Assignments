// Libraries
#include <Arduino.h>

// Pin Definitions
const int fetGatePin = 5; // Use D5, D6, or D7 for FET gate
const int solenoidPin = 8; // Output pin connected to solenoid
const int loadCellPin = A0; // Analog input pin for load cell
const int activationThreshold = 500; // Load cell activation threshold

// Variables
bool solenoidActive = false;
unsigned long previousMillis = 0;
const unsigned long solenoidDuration = 200; // Duration to keep solenoid active in milliseconds

// Setup
void setup() {
  pinMode(fetGatePin, OUTPUT);
  pinMode(solenoidPin, OUTPUT);
  pinMode(loadCellPin, INPUT);
  
  digitalWrite(fetGatePin, LOW); // Ensure FET is off initially
  Serial.begin(9600);
}

// Main loop
void loop() {
  // Read load cell value
  int loadCellValue = analogRead(loadCellPin);
  
  // Check if load cell value exceeds activation threshold +/- 10%
  if (loadCellValue >= activationThreshold * 0.9 && loadCellValue <= activationThreshold * 1.1) {
    activateSolenoid();
  }
  
  // Deactivate solenoid after duration
  if (solenoidActive && millis() - previousMillis >= solenoidDuration) {
    deactivateSolenoid();
  }
}

// Function to activate solenoid
void activateSolenoid() {
  digitalWrite(fetGatePin, HIGH); // Turn on FET
  digitalWrite(solenoidPin, HIGH); // Activate solenoid
  solenoidActive = true;
  previousMillis = millis();
}

// Function to deactivate solenoid
void deactivateSolenoid() {
  digitalWrite(fetGatePin, LOW); // Turn off FET
  digitalWrite(solenoidPin, LOW); // Deactivate solenoid
  solenoidActive = false;
}

