#include "esp_html.h"
#include <WiFi.h>
#include <WebServer.h>

#define LOCAL_SSID "Ricky-Guest"
#define LOCAL_PASS "564us90OP0"
#define PIN_LED 12 //Set GPIO PIN for turning LED ON/OFF
#define DIGITAL_PIN 34  //set Digital PIN for Sound Sensor
#define RGB_BLUE 25 //set Digital Blue Pin for RGB
#define RGB_GREEN 26 //set Digital Green Pin for RGB
#define RGB_RED 27 //set Digital Red Pin for RGB

//set rgb global colors as white initially
int red = 255, blue = 255, green = 255;

// Create a WebServer object that listens on port 80
WebServer server(80);

// state of LED, initially off
bool LED_State = false;

void setup() {
  Serial.begin(115200);
  delay(500);
  
  // Setting LED pin
  pinMode(PIN_LED, OUTPUT);

  // Setting LED to OFF
  digitalWrite(PIN_LED, LOW);
  
  // Setting RGB Pin
  pinMode(RGB_BLUE, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(RGB_RED, OUTPUT);
  
  // Setting RGB to OFF
  digitalWrite(RGB_BLUE, LOW);
  digitalWrite(RGB_GREEN, LOW);
  digitalWrite(RGB_BLUE, LOW);

  // Set the digital pin for input
  pinMode(DIGITAL_PIN, INPUT);
  
  delay(500);
  // Start WiFi and server
  connectWiFiAndStartServer();
}

void loop() {
  // Regularly handle client incoming requests
  server.handleClient();

  // Perform a digital read
  int digitalVal = digitalRead(DIGITAL_PIN);

  // Check if the digital value indicates sound detection
  if(digitalVal == HIGH)
    {
      if(LED_State == true) {
        LED_State = false;
        Serial.println("Sound Sensor: LED OFF");  
        digitalWrite(PIN_LED, LOW); // Turn ON Arduino's LED
        setColor(0,0,0); //Turn off RGB
        delay(100);
      } 
      
      else {
        LED_State = true;
        Serial.println("Sound Sensor: LED ON");  
        digitalWrite(PIN_LED, HIGH); // Turn ON Arduino's LED
        setColor(red,green,blue); //Turn on RGB to white color
        delay(100);
      }
    }  
  
  //troubleshooting sound sensor digital output HIGH = 1/LOW = 0
  /*
  Serial.print("Digital Value: ");
  Serial.println(digitalVal);
  delay(500);*/
}

//Establish WiFi connection and start server, runs in setup()
void connectWiFiAndStartServer() {
  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("Connected to WiFi");
  Serial.println("Paste IP address into web-browser!");
  Serial.print("IP address: "); Serial.println(WiFi.localIP());

  server.on("/", SendWebsite);
  server.on("/xml", SendXML);
  server.on("/BUTTON_ON", ProcessButtonOn);
  server.on("/BUTTON_OFF", ProcessButtonOff);
  server.on("/COLOR", HTTP_PUT, ProcessSetColor);
  server.begin();
}

//Send website
void SendWebsite() {
  server.send(200, "text/html", PAGE_MAIN);
}

//SendXML
void SendXML() {
  String xml = "<?xml version='1.0'?>\n<Data>\n";
  xml += "<LED>" + String(LED_State ? "1" : "0") + "</LED>\n";
  xml += "</Data>\n";
  server.send(200, "text/xml", xml);
}

//sets rgb color
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(RGB_RED, redValue);
  analogWrite(RGB_GREEN, greenValue);
  analogWrite(RGB_BLUE, blueValue);
}

//Process button as ON from website
void ProcessButtonOn() {
  LED_State = true;
  digitalWrite(PIN_LED, HIGH);
  setColor(red,green,blue);
  Serial.println("Website: LED ON");
  server.send(200, "text/plain", "LED ON");
}

//Process button as OFF from website
void ProcessButtonOff() {
  LED_State = false;
  digitalWrite(PIN_LED, LOW);
  setColor(0,0,0);
  Serial.println("Website: LED OFF");
  server.send(200, "text/plain", "LED OFF");
}

//Process rgb color from website
void ProcessSetColor() {
  String redValue = server.arg("R");
  String greenValue = server.arg("G");
  String blueValue = server.arg("B");

  red = redValue.toInt();
  green = greenValue.toInt();
  blue = blueValue.toInt();

  if (red >= 0 && red <= 255 && green >= 0 && green <= 255 && blue >= 0 && blue <= 255) {
    setColor(red, green, blue);
    server.send(200, "text/plain", "Color set");
  } else {
    server.send(400, "text/plain", "Invalid color values");
  }
}

