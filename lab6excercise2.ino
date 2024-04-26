#include <HX711.h>

// Define pin connections for HX711
const int LOADCELL_DOUT_PIN = 7;
const int LOADCELL_SCK_PIN = 6;

HX711 scale;

// Define pin connection for solenoid
const int SOLENOID_PIN = 5; // Connect to the gate pin of the FET driver module

float calibration_factor = 12345.6; // Calibration factor for your load cell
float activation_value = 0; // Activation value for the solenoid

void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); // Set the calibration factor
  
  pinMode(SOLENOID_PIN, OUTPUT);
}

void loop() {
  // Read weight and output via serial monitor
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'r') {
      float weight = getWeight();
      Serial.println("Weight: " + String(weight) + " kg");
      // Check if weight exceeds activation value
      if (weight >= activation_value * 0.9 && weight <= activation_value * 1.1) {
        activateSolenoid();
      }
    }
    else if (command == 'a') {
      Serial.println("Enter activation value (in kg): ");
      while (Serial.available() == 0);
      activation_value = Serial.parseFloat();
      Serial.println("Activation value set to: " + String(activation_value) + " kg");
    }
  }
}

float getWeight() {
  return scale.get_units();
}

void activateSolenoid() {
  digitalWrite(SOLENOID_PIN, HIGH); // Activate solenoid
  delay(200); // Keep solenoid activated for 200ms
  digitalWrite(SOLENOID_PIN, LOW); // Deactivate solenoid
}
