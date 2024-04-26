#include <Stepper.h>

// Define the number of steps per revolution
const int stepsPerRevolution = 200;

// Initialize the stepper motor with the number of steps and pins used
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); // Pins connected to IN1, IN2, IN3, IN4 of ULN2003A

bool isMoving = false; // Flag to indicate if the motor is currently moving
int direction = 1; // Variable to store the direction of movement

void setup() {
  // Set the speed of the stepper motor (in RPM)
  myStepper.setSpeed(60); // Default speed (you can change this)
  Serial.begin(9600); // Initialize serial communication
  
  // Initial prompt
  Serial.println("Enter '1' for clockwise rotation, '2' for anti-clockwise rotation,");
  Serial.println("Press '3' to start and change speed. Enter the new speed after '3'.");
}

void loop() {
  if (Serial.available() > 0) {
    int command = Serial.parseInt(); // Read the serial input as integer

    switch(command) {
      case 1: // Clockwise rotation
        direction = 1;
        isMoving = true;
        break;
      case 2: // Anti-clockwise rotation
        direction = -1;
        isMoving = true;
        break;
      case 3: // Change speed
        Serial.println("Enter the new speed (RPM):");
        isMoving = true;
        while (!Serial.available()) {} // Wait until user input
        int newSpeed = Serial.parseInt();
        myStepper.setSpeed(newSpeed);
        Serial.print("Stepper motor speed changed to ");
        Serial.print(newSpeed);
        Serial.println(" RPM.");
        break;
      case 0: // Stop the motor
        myStepper.setSpeed(0); // Set speed to 0
        isMoving = false;
        Serial.println("Stepper motor stopped.");
        break;
      default:
        Serial.println("Invalid command. Please enter '0', '1', '2', or '3'.");
        break;
    }
  }

  // If the motor is supposed to be moving, keep stepping in the specified direction
  if (isMoving) {
    myStepper.step(stepsPerRevolution * direction);

    delay(10); // Small delay to ensure steps are executed properly
  }
}

