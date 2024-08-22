#include "esp_html.h"
#include <WiFi.h>
#include <WebServer.h>

#define LOCAL_SSID "Ricky-Guest"
#define LOCAL_PASS "insert_pass"
#define PIN_LED 2

bool LED0 = false;

WebServer server(80);

void setup() {
  Serial.begin(115200);  // Initialize Serial Monitor
  Serial1.begin(115200); // Initialize Serial1 for communication with Arduino

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  // Attempt to connect to WiFi
  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
    Serial.print("IP address: "); Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi");
  }

  // Define routes for the web server
  server.on("/", SendWebsite);
  server.on("/xml", SendXML);
  server.on("/BUTTON_ON", [](){ ProcessButtonOn(); });
  server.on("/BUTTON_OFF", [](){ ProcessButtonOff(); });

  server.begin();
}

void loop() {
  // Handle incoming data from Serial Monitor
  if (Serial.available()) {
    char incomingByte = Serial.read();
    Serial.print("Received from Serial: ");
    Serial.println(incomingByte);
  }

  // Handle incoming data from Arduino (via Serial1)
  if (Serial1.available()) {
    char incomingByte = Serial1.read();
    Serial.print("Received from Arduino: ");
    Serial.println(incomingByte);

    // Handle Arduino commands
    if (incomingByte == '1') {
      ProcessButtonOn(false);
    } else if (incomingByte == '0') {
      ProcessButtonOff(false);
    }
  }

  // Handle incoming HTTP requests
  server.handleClient();
}

void SendWebsite() {
  server.send(200, "text/html", PAGE_MAIN);
  Serial.println("Sent website");
}

void SendXML() {
  String xml = "<?xml version='1.0'?>\n<Data>\n";
  xml += "<LED>" + String(LED0 ? "1" : "0") + "</LED>\n";
  xml += "</Data>\n";
  server.send(200, "text/xml", xml);
  Serial.println("Sent XML data");
}

void ProcessButtonOn(bool sendSignal = true) {
  LED0 = true;
  digitalWrite(PIN_LED, HIGH);
  Serial.println("LED ON");
  server.send(200, "text/plain", "LED ON");
  Serial.println("Button ON processed");

  // Send signal to Arduino
  if(sendSignal) Serial1.println('1');  // '1' indicates turn on
}

void ProcessButtonOff(bool sendSignal = true) {  // Added `sendSignal` parameter
  LED0 = false;
  digitalWrite(PIN_LED, LOW);
  Serial.println("LED OFF");
  server.send(200, "text/plain", "LED OFF");
  Serial.println("Button OFF processed");

  // Send signal to Arduino
  if(sendSignal) Serial1.println('0');  // '0' indicates turn off
}
