#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

// Declare constants
#define DELAY 3
#define STEP 1

// Define global string variable request
String request;

// Custom class that inherits from Servo
// and has custom properties
class CustomServo : public Servo {
  public:
    // Custom properties
    int minVal;
    int maxVal;
};

// Servo motor objects
CustomServo base;
CustomServo shoulder;
CustomServo elbow;
CustomServo claw;

const char* ssid = "Tenda_1A5A60"; // name of your WiFi network
const char* password = "balaur20"; // password to your WiFi network

WiFiServer server(80);

void setup() {
  base.attach(2);
  shoulder.attach(4);
  elbow.attach(12);
  claw.attach(16);
  
  base.minVal = 25;
  base.maxVal = 110;
  shoulder.minVal = 25;
  shoulder.maxVal = 110;
  elbow.minVal = 25;
  elbow.maxVal = 110;
  claw.minVal = 25;
  claw.maxVal = 110;
  
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  
  server.begin();
  Serial.println("Server started");
  
  if (MDNS.begin("robot")) { // set the local mdns name to "robot.local"
    Serial.println("mDNS responder started");
  }
}

void loop() {
  WiFiClient client = server.available();
  MDNS.update(); // Update the mDNS service

  if (client) {
    request = client.readStringUntil('\r');
    client.flush();

    // HTML page with buttons to control the robotic arm
    if (request.indexOf("GET /") != -1) {
      client.print(
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n\r\n"
        "<!DOCTYPE html><html lang=\"en\"><head>"
        "<meta name=\"viewport\" content=\"width=device-width,"
        "initial-scale=1, shrink-to-fit=no\">"
        "<meta charset=\"utf-8\"><title>Mini Robotic Arm</title>"
        "<link href=\"https://cdn.jsdelivr.net/npm/bootstrap-icons/font/bootstrap-icons.css\""
        "rel=\"stylesheet\">"
        "<style>body {display: flex; justify-content: center;"
        "align-items: center; height: 100vh; margin: 0;"
        "flex-direction: column; background-color: #f1f1f1;}"
        "i {font-size: 4em;}"
        "h1 {text-align: center; margin-bottom: 20px;}"
        ".ctrl-pnl {display: flex; justify-content: center; align-items: center;}"
        ".ctrl-btn {width: 100px; height: 100px;"
        "border-radius: 50%; margin: 10px; background-color: #06D001;"
        "color: black; font-weight: bold; border: none;"
        "justify-content: center; align-items: center; cursor: pointer;"
        "transition: background-color 0.1s;}"
        ".ctrl-btn:hover {background-color: #059212;}"
        ".ctrl-btn:active {background-color: #9BEC00;}</style>"
        "</head><body><h1>Robotic Arm Control</h1>"
        "<div class=\"ctrl-pnl\"><table>"
        "<tr><td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('rotate_left')\" "
        "onmouseup=\"sendCommand('stop')\" "
        "ontouchstart=\"sendCommand('rotate_left')\" "
        "ontouchend=\"sendCommand('stop')\">"
        "<i class=\"bi bi-arrow-counterclockwise\"></i></button></td>"
        "<td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('rotate_right')\" "
        "onmouseup=\"sendCommand('stop')\" "
        "ontouchstart=\"sendCommand('rotate_right')\" "
        "ontouchend=\"sendCommand('stop')\">"
        "<i class=\"bi bi-arrow-clockwise\"></i></button></td></tr>"
        "<tr><td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('shoulder_fwd')\" "
        "onmouseup=\"sendCommand('stop')\" "
        "ontouchstart=\"sendCommand('shoulder_fwd')\" "
        "ontouchend=\"sendCommand('stop')\">"
        "<i class=\"bi bi-arrow-bar-up\"></i></button></td>"
        "<td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('shoulder_bkd')\" "
        "onmouseup=\"sendCommand('stop')\" "
        "ontouchstart=\"sendCommand('shoulder_bkd')\" "
        "ontouchend=\"sendCommand('stop')\">"
        "<i class=\"bi bi-arrow-bar-down\"></i></button></td></tr>"
        "<tr><td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('elbow_up')\" "
        "onmouseup=\"sendCommand('stop')\" "
        "ontouchstart=\"sendCommand('elbow_up')\" "
        "ontouchend=\"sendCommand('stop')\">"
        "<i class=\"bi bi-arrow-up-left\"></i></button></td>"
        "<td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('elbow_down')\" "
        "onmouseup=\"sendCommand('stop')\" "
        "ontouchstart=\"sendCommand('elbow_down')\" "
        "ontouchend=\"sendCommand('stop')\">"
        "<i class=\"bi bi-arrow-down-right\"></i></button></td></tr>"
        "<tr><td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('open_claw')\" "
        "onmouseup=\"sendCommand('stop')\" "
        "ontouchstart=\"sendCommand('open_claw')\" "
        "ontouchend=\"sendCommand('stop')\">"
        "<i class=\"bi bi-arrows\"></i></button></td>"
        "<td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('close_claw')\" "
        "onmouseup=\"sendCommand('stop')\" "
        "ontouchstart=\"sendCommand('close_claw')\" "
        "ontouchend=\"sendCommand('stop')\">"
        "<i class=\"bi bi-arrows-collapse-vertical\"></i></button></td></tr>"
        "</table></div>"
        "<script>"
        "function sendCommand(action) {"
        "var xhr = new XMLHttpRequest();"
        "xhr.open('GET', '/' + action, true);"
        "xhr.setRequestHeader('Connection', 'keep-alive');"
        "xhr.send();"
        "}"
        "</script></body></html>"
      );
    }

    if (request.indexOf("/rotate_left") != -1) {
      Serial.println("rotate_left");
      moveServo(base, "negative");
    }
    
    if (request.indexOf("/rotate_right") != -1) {
      Serial.println("rotate_right");
      moveServo(base, "positive");
    }

    if (request.indexOf("/shoulder_fwd") != -1) {
      Serial.println("shoulder_fwd");
      moveServo(shoulder, "positive");
    }

    if (request.indexOf("/shoulder_bkd") != -1) {
      Serial.println("shoulder_bkd");
      moveServo(shoulder, "negative");
    }

    if (request.indexOf("/elbow_up") != -1) {
      Serial.println("elbow_up");
      moveServo(elbow, "positive");
    }

    if (request.indexOf("/elbow_down") != -1) {
      Serial.println("elbow_down");
      moveServo(elbow, "negative");
    }

    if (request.indexOf("/open_claw") != -1) {
      Serial.println("open_claw");
      moveServo(claw, "positive");
    }

    if (request.indexOf("/close_claw") != -1) {
      Serial.println("close_claw");
      moveServo(claw, "negative");
    }
  }
}

void moveServo(CustomServo& servoObj, String direction) {
  if (direction == "positive") {
    int currVal = servoObj.read();
    while (currVal < servoObj.maxVal) {
      currVal += STEP;
      servoObj.write(currVal);
      delay(DELAY);
      if (request.indexOf("/stop") != -1) {
        Serial.println("stop");
        break;
      }
    }
  } else if (direction == "negative") {
    int currVal = servoObj.read();
    while (currVal > servoObj.minVal) {
      currVal -= STEP;
      servoObj.write(currVal);
      delay(DELAY);
      if (request.indexOf("/stop") != -1) {
        Serial.println("stop");
        break;
      }
    }
  }
} // end moveServo
