#include <ESP8266WiFi.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);  // Communicate with ATmega328
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String req = client.readStringUntil('\r');
    if (req.indexOf("/control?action=rotate_left") != -1) {
      Serial.println("rotate_left");
    } else if (req.indexOf("/control?action=rotate_right") != -1) {
      Serial.println("rotate_right");
    }
    client.flush();
  }
}

