#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo1;
Servo servo2;

SoftwareSerial espSerial(2, 3); // RX, TX

void setup() {
  servo1.attach(9);
  servo2.attach(10);
  
  espSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (espSerial.available()) {
    String command = espSerial.readStringUntil('\n');
    if (command == "rotate_left") {
      servo1.write(90);  // Rotate servo to 90 degrees
    } else if (command == "rotate_right") {
      servo1.write(0);   // Rotate servo back to 0 degrees
    }
    // Additional commands for other motors
  }
}

