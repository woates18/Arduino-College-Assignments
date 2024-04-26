#include <Wire.h>      // Include the Wire library for I2C communication
#include <LiquidCrystal.h>  // Include the LiquidCrystal library
#include <NewPing.h>  // Include the NewPing library for ultrasonic sensor

// Define the pins for the LED panel
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define TRIGGER_PIN 6
#define ECHO_PIN 7
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

bool displayInches = true;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.print("Hello World!");  // Display "Hello World!" on the LCD
}

void loop() {
  unsigned int distance;

  distance = sonar.ping_cm(); // Send ping, get distance in cm.

  if (distance == 0) {
    lcd.setCursor(0, 1);
    lcd.print("Out of range");
  } else {
    lcd.setCursor(0, 1);
    if (displayInches) {
      float inches = distance * 0.393701;
      lcd.print("Distance: ");
      lcd.print(inches);
      lcd.print(" inches   ");
    } else {
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.print(" mm   ");
    }
  }

  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'i' || command == 'I') {
      displayInches = true;
      Serial.println("Displaying in inches");
    } else if (command == 'm' || command == 'M') {
      displayInches = false;
      Serial.println("Displaying in millimeters");
    }
  }
  
  delay(500); // Delay for stability
}
