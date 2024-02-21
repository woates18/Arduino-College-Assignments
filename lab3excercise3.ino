// Constant integer variable for switchPin
const int buttonPin = 5;

// Definine previousState as an integer variable
int previousState = LOW;
int currentState= 0;
void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  // Set switchPin to input
  pinMode(buttonPin, INPUT);
  // Set previous state to switchPin's value
  previousState = digitalRead(buttonPin);
}

void loop() {
  // Read the current state of the switch
  currentState = digitalRead(buttonPin);
  if (currentState != previousState){
    delay(10);
  }
  // If state has changed switch statment activates and prints a 0 for LOW and 1 for HIGH
  if (currentState != previousState) {
    switch(currentState){
      case 0:
      Serial.println("Switched from high to low");
      break;
      default:
      Serial.println("Switched from low to high");
      break;
  }
    // Update the previous state to the current state for next iteration of the loop
    previousState = currentState;
    
  } 
}
