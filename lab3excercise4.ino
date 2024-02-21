// Constant integer variable for switchPin
const int buttonPin = 2;
const int ledPin = 13;  
// Definine previousState as an integer variable
int previousState = LOW;
int currentState= 0;

volatile bool switchPressed = false; // Flag for switch press

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  // Set switchPin to input
  pinMode(buttonPin, INPUT);
  // Set previous state to switchPin's value
  previousState = digitalRead(buttonPin);
  // attach interupt function call
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleInterrupt, CHANGE);
}

void loop() {
  if (switchPressed) {
    // Blink LED
    digitalWrite(ledPin, HIGH);
    delay(190); // 200ms - 5%
    digitalWrite(ledPin, LOW);
    delay(190); // 200ms - 5%
    switchPressed = false; // Reset switchPressed flag
  }
}


void handleInterrupt() {
  currentState = digitalRead(buttonPin);
  // Check if switch state changed from high to low
  if (currentState == LOW && previousState == HIGH) {
    Serial.println("Switched from high to low");
    switchPressed = true; // Set switchPressed flag
  } else if (currentState == HIGH && previousState == LOW) {
    Serial.println("Switched from low to high");
  }
  previousState = currentState; // Update previous state
}