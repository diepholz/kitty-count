#include "arduino_secrets.h"
/*
  Simple POST client for ArduinoHttpClient library
  Connects to server once every five seconds, sends a POST request
  and a request body
  created 14 Feb 2016
  modified 22 Jan 2019
  by Tom Igoe
  
  EXTENDED
  5 May 2020
  by Will Diepholz
 */
#include <SPI.h>
#include <WiFiNINA.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
// IPAddress server(192,168,1,8);  // numeric IP for Google (no DNS)
// int port = 5000;
char server[]= "diepholz.pythonanywhere.com";
int port = 80;

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

#define input_pin 2
#define led_pin 3
#define reset_pin_out 4
#define reset_pin_in 5
int pir_val = 0;
int reset_val = 0;
int count = 0;


void setup() {
  pinMode(input_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(reset_pin_out, OUTPUT);
  pinMode(reset_pin_in, INPUT);
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  Serial.println("\nStarting connection...");
  // if you get a connection, report back via serial:
  if (client.connect(server, port)) {
    Serial.println("connected");
  }
}

void loop() {
  
  digitalWrite(reset_pin_out, HIGH);
  pir_val = digitalRead(input_pin);
  if (pir_val == HIGH) {
    count += 1;
    Serial.println("Gotcha!");
    Serial.println("The kitty has been caught this many times:");
    Serial.println(count);
    digitalWrite(led_pin, HIGH);
    
    Serial.println("making POST request");
    String contentType = "application/json";
    String postData = "{\"count\":\"";
    postData += count;
    postData += "\"}";
    Serial.println(postData);
  
    if (client.connect(server, port)) {
      client.println("POST /webhook HTTP/1.1");
      client.print("Host: ");
      client.print(server);
      client.print(":");
      client.println(port);
      client.println("Content-Type: application/json; charset=UTF-8");
      client.println("Connection:close");
      client.print("Content-Length: ");
      client.println(postData.length());
      client.println();
      client.println(postData);
    }
    
    delay(4000);
  }
  else {
    digitalWrite(led_pin, LOW);
  }
  
  reset_val = digitalRead(reset_pin_in);
  if (reset_val == HIGH) {
    Serial.println("Kitty count reset.");
    count = 0;
    delay(500);
  }

}




