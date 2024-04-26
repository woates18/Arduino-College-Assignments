// Include the necessary libraries
#include "LedControl.h"

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

// Define the delay time (in milliseconds) between displaying each frame
#define FRAME_DELAY 100

// Define the bit patterns for the arrow image
byte arrowPatterns[][NUM_LEDS] = {
  {B00000000, B00011000, B00011000, B11111111, B00011000, B00011000, B00000000, B00000000},
  {B00000000, B00000000, B00011000, B00011000, B11111111, B00011000, B00011000, B00000000},
  {B00000000, B00000000, B00000000, B00011000, B00011000, B11111111, B00011000, B00011000},
  {B00000000, B00000000, B00000000, B00000000, B00011000, B00011000, B11111111, B00011000},
  {B00000000, B00000000, B00000000, B00000000, B00000000, B00011000, B00011000, B11111111},
  {B11111111, B00000000, B00000000, B00000000, B00000000, B00000000, B00011000, B00011000},
  {B00011000, B11111111, B00000000, B00000000, B00000000, B00000000, B00000000, B00011000},
  {B00011000, B00011000, B11111111, B00000000, B00000000, B00000000, B00000000, B00000000}
};

// We always have to include the library
LedControl lc = LedControl(12, 11, 10, 1);

/* we always wait a bit between updates of the display */
unsigned long lcdelaytime = 100;

void setup() {
  // Set the shift register pins as outputs
  pinMode(DS, OUTPUT);
  pinMode(ST_CP, OUTPUT);
  pinMode(SH_CP, OUTPUT);
  
  // Initialize the serial communication
  Serial.begin(9600);

  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
  */
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);
}

void loop() {
  // Exercise 1: Knight Rider Effect
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

  // Exercise 2: Arrow Image
  for (int frame = 0; frame < 8; frame++) {
    // Output the current frame to the shift register
    for (int i = 0; i < NUM_LEDS; i++) {
      digitalWrite(ST_CP, LOW);  // Prepare for data transfer
      shiftOut(DS, SH_CP, MSBFIRST, arrowPatterns[frame][i]); // Send the pattern for the current LED
      digitalWrite(ST_CP, HIGH); // Register the data
    }

    // Delay to control the speed of the effect
    delay(FRAME_DELAY);
  }

  // LCDemoMatrix: Display "Arduino" on the LED matrix
  writeArduinoOnMatrix();
  rows();
  columns();
  single();
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 */
void writeArduinoOnMatrix() {
  /* here is the data for the characters */
  byte a[5] = {B01111110, B10001000, B10001000, B10001000, B01111110};
  byte r[5] = {B00111110, B00010000, B00100000, B00100000, B00010000};
  byte d[5] = {B00011100, B00100010, B00100010, B00010010, B11111110};
  byte u[5] = {B00111100, B00000010, B00000010, B00000100, B00111110};
  byte i[5] = {B00000000, B00100010, B10111110, B00000010, B00000000};
  byte n[5] = {B00111110, B00010000, B00100000, B00100000, B00011110};
  byte o[5] = {B00011100, B00100010, B00100010, B00100010, B00011100};

  /* now display them one by one with a small delay */
  lc.setRow(0, 0, a[0]);
  lc.setRow(0, 1, a[1]);
  lc.setRow(0, 2, a[2]);
  lc.setRow(0, 3, a[3]);
  lc.setRow(0, 4, a[4
