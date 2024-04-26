#include <NewPing.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

bool displayInches = true;

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned int distance;

  distance = sonar.ping_cm(); // Send ping, get distance in cm.

  if (distance == 0) {
    Serial.println("Out of range");
  } else {
    if (displayInches) {
      float inches = distance * 0.393701;
      Serial.print("Distance: ");
      Serial.print(inches);
      Serial.println(" inches");
    } else {
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" mm");
    }
  }

  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'i') {
      displayInches = true;
      Serial.println("Displaying in inches");
    } else if (command == 'm') {
      displayInches = false;
      Serial.println("Displaying in millimeters");
    }
  }
  
  delay(100); // Wait 100ms between pings (about 10 pings/sec). 29ms should be the shortest delay between pings.
}
