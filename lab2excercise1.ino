int blinkArray[4] = {1,2,3,5};

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // initialize digital pin 8 as an output.
  pinMode(8, OUTPUT);

  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only

  }
  Serial.println("Press a, b or c");
}

void loop() {  
  if (Serial.available() > 0) {   // if statment to retrieve user input
    char thisChar = Serial.read();

    Serial.println(thisChar);
    switch (thisChar){ // switch statment returning number of blinks to blink loop
      case 'a':
        blink(blinkArray[0]);
        break;
      case 'b':
        blink(blinkArray[1]);
        break;
      case 'c':   
        blink(blinkArray[2]);
        break;
      default:
        Serial.println("ERROR: neither a, b, or c were pressed");
        blink(blinkArray[3]);
        break;
    }
  }
}

void blink(int times) { //blink loop which causes ARDUINO to blink a specified amount of timers
    for (int i = 0; i < times; i++) {
      pinMode(8, OUTPUT); 
      digitalWrite(8, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(500);                      // wait for a half second
      digitalWrite(8, LOW);   // turn the LED off by making the voltage LOW
      delay(500);                      // wait for a half second

    }
    Serial.println("Press a, b, or c again");
}
