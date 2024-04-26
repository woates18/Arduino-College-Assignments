#include <Servo.h>

// Define the range of angles for the servo motor
const int minAngle = -90;
const int maxAngle = 90;

// Initialize the servo motor object
Servo myServo;

void setup() {
  // Attach the servo motor to pin 6
  myServo.attach(6);
  Serial.begin(9600); // Initialize serial communication
  
  // Initial prompt
  Serial.println("Enter angle (-90 to +90 degrees) to control the servo motor.");
}

void loop() {
  if (Serial.available() > 0) {
    int angle = Serial.parseInt(); // Read the serial input as integer

    // Ensure the angle is within the specified range
    if (angle >= minAngle && angle <= maxAngle) {
      // Map the angle to the servo motor's range (0 to 180)
      int servoAngle = map(angle, minAngle, maxAngle, 0, 180);
      
      // Set the servo motor's position
      myServo.write(servoAngle);
      
      // Print feedback to the serial monitor
      Serial.print("Servo motor set to ");
      Serial.print(angle);
      Serial.println(" degrees.");
    } else {
      // Print error message if the angle is out of range
      Serial.println("Invalid angle. Please enter an angle between -90 and +90 degrees.");
    }
  }
}

