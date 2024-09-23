#include <ESP8266WiFi.h>

#define GREEN_LED 16
#define RED_LED 4
#define BLUE_LED 2
#define YELLOW_LED 12

const char* ssid = "Tenda_1A5A60";
const char* password = "balaur20";

WiFiServer server(80);

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    // HTML page with buttons to control the robotic arm
    if (request.indexOf("GET /") != -1) {
      client.print(
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n\r\n"
        "<html><body>"
        "<h1>Robotic Arm Control</h1>"
        "<button onclick=\"sendCommand('rotate_left')\">Rotate Left</button>"
        "<button onclick=\"sendCommand('rotate_right')\">Rotate Right</button>"
        "<button onclick=\"sendCommand('open_claw')\">Open Claw</button>"
        "<button onclick=\"sendCommand('close_claw')\">Close Claw</button>"
        "<script>"
        "function sendCommand(action) {"
        "var xhr = new XMLHttpRequest();"
        "xhr.open('GET', '/' + action, true);"
        "xhr.send();"
        "}"
        "</script></body></html>"
      );
    }

    // Servo control logic based on button pressed
    if (request.indexOf("/rotate_left") != -1) {
      digitalWrite(GREEN_LED, HIGH);
      delay(1000);
      digitalWrite(GREEN_LED, LOW);
    }
    if (request.indexOf("/rotate_right") != -1) {
      digitalWrite(RED_LED, HIGH);
      delay(1000);
      digitalWrite(RED_LED, LOW);
    }
    if (request.indexOf("/open_claw") != -1) {
      digitalWrite(BLUE_LED, HIGH);
      delay(1000);
      digitalWrite(BLUE_LED, LOW);
    }
    if (request.indexOf("/close_claw") != -1) {
      digitalWrite(YELLOW_LED, HIGH);
      delay(1000);
      digitalWrite(YELLOW_LED, LOW);
    }
  }
}
