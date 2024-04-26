#include <HX711.h>

// Define pin connections for HX711
const int LOADCELL_DOUT_PIN = 7;
const int LOADCELL_SCK_PIN = 6;

HX711 scale;

float calibration_factor = 12345.6; // Calibration factor for your load cell

void setup() {s
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); // Set the calibration factor
}

void loop() {
  // Perform calibration
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'c') {
      calibrate();
    }
  }
  
  // Read weight and output via serial monitor
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'r') {
      float weight = getWeight();
      Serial.println("Weight: " + String(weight) + " kg");
    }
  }
}

void calibrate() {
  Serial.println("Place a known weight on the load cell and press enter.");
  while (Serial.available() == 0);
  float known_weight = Serial.parseFloat(); // Read known weight from serial monitor
  scale.set_scale(known_weight); // Set the calibration factor
  calibration_factor = scale.get_units(10); // Calibrate the scale
  Serial.println("Calibration complete. Calibration Factor: " + String(calibration_factor));
}

float getWeight() {
  return scale.get_units();
}
