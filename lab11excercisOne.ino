#include <SoftwareSerial.h>

#define BLE_RX_PIN 8     // Connect BLE module TX pin to Arduino pin 2
#define BLE_TX_PIN 9     // Connect BLE module RX pin to Arduino pin 3
#define BUZZER_PIN 10    // Buzzer connected to pin 9

int buzzerFrequency = 400; // Initial frequency for the buzzer

SoftwareSerial mySerial(8,9);  //TX is on pin8 and RX on pin 9
void setup()
{
mySerial.begin(9600);   
Serial.begin(9600);   
delay(100);

mySerial.write("AT\r\n");  //put HM10 in AT command mode
delay(100);
mySerial.write("AT+NAME williamoates\r\n");  //Name our HM10 something so as to not interfere with others
delay(100);
mySerial.write("AT+NAME\r\n");  //Verify new name
delay(100);
mySerial.write("AT+RESET\r\n");  //reset HM10 so new name will take effect


}

/* This loop allows you to input any AT commands. But after a BLE connection you can't send AT commands.
  You can modify this loop to look for characters from your BLE phone app and to send data to your 
  phone app
  */
void loop() {
  if (mySerial.available()) { // Check if data is available to read from BLE module
    char receivedChar = mySerial.read(); // Read the incoming byte from BLE module
    if (receivedChar == '1') { // If '1' is received, turn on Buzzer
      tone(BUZZER_PIN, buzzerFrequency); // Play a tone with current frequency
      mySerial.println("Buzzer turned on");
    } else if (receivedChar == '0') { // If '0' is received, turn off Buzzer
      noTone(BUZZER_PIN); // Stop playing tone
      mySerial.println("Buzzer turned off");
    } else if (receivedChar == 'F') { // If 'F' is received, adjust buzzer frequency
      buzzerFrequency = getFrequencyFromBluetooth(); // Get frequency value from Bluetooth
      mySerial.print("Buzzer frequency set to: ");
      mySerial.println(buzzerFrequency);
      // If the buzzer is already on, update the frequency
      if (digitalRead(BUZZER_PIN) == HIGH) {
        tone(BUZZER_PIN, buzzerFrequency);
      }
    }
  }
}
int getFrequencyFromBluetooth() {
  int frequency = 0;
  
  return frequency;
}

