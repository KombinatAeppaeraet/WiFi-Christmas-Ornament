#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>   // Include the WebServer library
#include <Adafruit_NeoPixel.h>
#define NEOPIN D2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, NEOPIN, NEO_GRB + NEO_KHZ800);

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

String status = "";
int errorCounter = 0;

void handleRGB();
void handleNotFound();

void setup(void){
  Serial.begin(9600);        
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("your SSID #1", "your password #1");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("your SSID #2", "your password #2");

  Serial.println("Connecting ...");

  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("ornament")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/rgb", handleRGB);
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");

  pixels.begin(); // This initializes the NeoPixel library.

  pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // blue
  pixels.show(); 
}

void loop(void){
  server.handleClient();                    // Listen for HTTP requests from clients
}


// directly set RGB values on /rgb with GET parameters r, g, b from 0 to 255
void handleRGB(){
    server.send(200, "text/plain", "OK"); 

    int r = 0;
    int g = 0;
    int b = 0;

    r = server.arg("r").toInt();
    g = server.arg("g").toInt();
    b = server.arg("b").toInt();
    
    pixels.setPixelColor(0, pixels.Color(r, g, b));
    pixels.show(); 
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
  pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // blue
  pixels.show(); 
}
