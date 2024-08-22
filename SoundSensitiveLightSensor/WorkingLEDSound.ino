#include <SoftwareSerial.h>

SoftwareSerial arduinoSerial(10, 11); // RX, TX pins

// Setup for Arduino for LED and Sound Sensor
int digitalPin = 7;   // KY-037 digital interface
int analogPin = A0;   // KY-037 analog interface
int ledPin = 13;      // Arduino LED pin
int digitalVal;       // Digital readings
int analogVal;        // Analog readings
bool onVal = false;

void setup()
{
  // PinMode Assignments for Sound Sensor LED
  pinMode(digitalPin, INPUT);
  pinMode(analogPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200); 
  arduinoSerial.begin(115200);  // Communication with ESP32
  Serial.println("Arduino setup complete.");
}

void loop()
{
  // Check for commands from the ESP32
  if (arduinoSerial.available()) {
    char command = arduinoSerial.read();
    Serial.print("Received command: ");
    Serial.println(command);
    if (command == '1') {
      ProcessOn();
    } else if (command == '0') {
      ProcessOff();
    }
  }

  analogVal = analogRead(analogPin);  // Read analog interface

  // Code that makes LED turn on/off when noise is detected
  if (analogVal > 550) {
    if (onVal) {
      ProcessOff();
      Serial.println("Turned off from sound");
      arduinoSerial.println('0'); // Communicate to ESP32 off
    } else {
      ProcessOn();
      Serial.println("Turned on from sound");
      arduinoSerial.println('1'); // Communicate to ESP32 on
    }
  }

  // Print analogValue to serial
  Serial.println(analogVal); 
}

void ProcessOn() {
  delay(500);
  onVal = true;
  digitalWrite(ledPin, HIGH); // Turn ON Arduino's LED
}

void ProcessOff() {
  delay(500);
  onVal = false;
  digitalWrite(ledPin, LOW); // Turn OFF Arduino's LED
}
