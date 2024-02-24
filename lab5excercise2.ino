// Define analog sensor pin
const int sensorPin = A0;
// Motor control pin
const int motorSpeedPin = 9; // Connected to the FET motor driver

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(motorSpeedPin, OUTPUT); // Set motor speed pin as output
}

void loop() {
  // Read sensor value
  int sensorValue = analogRead(sensorPin);
  
  // Map sensor value to motor speed range (0-255)
  int motorSpeed = map(sensorValue, 0, 175, 0, 255);

  // Set motor speed using PWM
  analogWrite(motorSpeedPin, motorSpeed);

  // Print sensor value and mapped motor speed to serial monitor
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(" - Motor Speed: ");
  Serial.println(motorSpeed);

  // Delay for stability
  delay(100);
}
