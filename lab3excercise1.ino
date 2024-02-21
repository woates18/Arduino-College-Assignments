// Constant integer variable for switchPin
const int buttonPin = A5;

// Definine previousState as an integer variable
int previousState = LOW;
int currentState= 0;
void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  // Set switchPin to input
  pinMode(buttonPin, INPUT);
  // Set previous state to switchPin's value
  previousState = analogRead(buttonPin);
}

void loop() {
  // Read the current state of the switch
  currentState = analogRead(buttonPin);
  // If state has changed switch statment activates and prints a 0 for LOW and 1 for HIGH
  if (currentState != previousState) {
    switch(currentState){
      case 0:
      Serial.println('0');
      break;
      case 1023:
      Serial.println('1');
      break;
    } 
    // Update the previous state to the current state for next iteration of the loop
    previousState = currentState;
  } 
}


