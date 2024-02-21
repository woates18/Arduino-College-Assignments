#include <EEPROM.h>
int blinkArray[4] = {1,2,3,5};
int previousBlinkValue = 0;
int *ptr = blinkArray;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  previousBlinkValue = EEPROM.read(0);
  Serial.println("The previous blink value is:");
  Serial.println("Check");
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only

  }
  Serial.println("Press a, b or c");
}

void loop() {  
  if (Serial.available() > 0 & previousBlinkValue == -1) {   // if statment to retrieve user input
    int thisChar = Serial.read();
    switch (thisChar){ // switch statment returning number of blinks to blink loop
      case 'a':
        blink(*ptr);
        EEPROM.write(0,*ptr);
        break;
      case 'b':
        blink(*(ptr + 1));
        EEPROM.write(0,*ptr+1);
        break;
      case 'c':   
        blink(*(ptr + 2));
        EEPROM.write(0,*ptr+2);
        break;
      default:
        Serial.println("ERROR: neither a, b, or c were pressed");
        blink(*(ptr + 3));
        EEPROM.write(0,*ptr+3);
        break;
    }
  }
  if (previousBlinkValue > 0 ){
    blink(previousBlinkValue);
  previousBlinkValue = -1; //change previous blank value to an impossible value so next loop the previous blink value is not called again
  }
  
}

void blink(int times) { //blink loop which causes ARDUINO to blink a specified amount of timers
    if (previousBlinkValue > 0){
      times = *(ptr + previousBlinkValue-1);
    }
    if (previousBlinkValue == 0){
      times = 1;
    }
    for (int i = 0; i < times; i++) {
      pinMode(8, OUTPUT); 
      digitalWrite(8, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(500);                      // wait for a half second
      digitalWrite(8, LOW);   // turn the LED off by making the voltage LOW
      delay(500);                      // wait for a half second
    }
    Serial.println("Press a, b, or c again");

}