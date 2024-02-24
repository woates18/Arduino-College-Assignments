// define analog sensor pin
const int sensorPin = A0;
// Motor control pins
const int motor1Pin1 = 8; // Connected to IN1 on L298N
const int motor1Pin2 = 9; // Connected to IN2 on L298N
const int motor1SpeedPin = 7; // Connected to ENA on L298N

void setup() {
  Serial.begin(9600); // Iinitialization of serial communication
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1SpeedPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  // Set the direction of the motor
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  
  //test of vlues
  if (sensorValue > 100){
    Serial.println("The sensor is being pressed");
  }
  else{
    Serial.println("The Sensor is not being pressed");

  }

  analogWrite(motor1SpeedPin, 255); // if pressed set fan speed to high
  delay(1000);
  Serial.println(sensorValue);
}