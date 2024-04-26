// Define the pins connected to the 74HC595 shift register
#define DS 10   // Data pin
#define ST_CP 11 // Latch pin
#define SH_CP 12 // Clock pin

// Define the number of LEDs in the array
#define NUM_LEDS 8

// Define the delay range (in milliseconds) for controlling the speed
#define MAX_DELAY 250   // 4Hz
#define MIN_DELAY 1000  // 0.25Hz

// Define the initial delay (in milliseconds)
unsigned long delayTime = MAX_DELAY;

// Define the bit patterns for the Knight Rider effect
byte patterns[] = {
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000
};

void setup() {
  // Set the shift register pins as outputs
  pinMode(DS, OUTPUT);
  pinMode(ST_CP, OUTPUT);
  pinMode(SH_CP, OUTPUT);
  
  // Initialize the serial communication
  Serial.begin(9600);
}

void loop() {
  // Update the delay time based on serial input
  if (Serial.available() > 0) {
    int input = Serial.parseInt();
    if (input >= 250 && input <= 4000) { // Ensure input is within valid range
      delayTime = input;
    }
  }

  // Loop through the bit patterns to create the Knight Rider effect
  for (int i = 0; i < NUM_LEDS; i++) {
    // Output the current bit pattern to the shift register
    digitalWrite(ST_CP, LOW);  // Prepare for data transfer
    shiftOut(DS, SH_CP, MSBFIRST, patterns[i]); // Send the pattern
    digitalWrite(ST_CP, HIGH); // Register the data

    // Delay to control the speed of the effect
    delay(delayTime);
  }

  // Reverse the order of bit patterns for the return path
  for (int i = NUM_LEDS - 2; i > 0; i--) {
    // Output the current bit pattern to the shift register
    digitalWrite(ST_CP, LOW);  // Prepare for data transfer
    shiftOut(DS, SH_CP, MSBFIRST, patterns[i]); // Send the pattern
    digitalWrite(ST_CP, HIGH); // Register the data

    // Delay to control the speed of the effect
    delay(delayTime);
  }
}
