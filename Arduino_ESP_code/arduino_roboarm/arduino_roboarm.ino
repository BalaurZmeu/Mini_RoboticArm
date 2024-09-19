#include <SoftwareSerial.h>

#define GREEN_LED 4
#define RED_LED 8
#define BLUE_LED 12

SoftwareSerial espSerial(2, 3); // RX, TX

void setup() {

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);

  espSerial.begin(115200);
  Serial.begin(115200);
}

void loop() {
  if (espSerial.available()) {
    String command = espSerial.readStringUntil('\n');
    if (command == "rotate_left") {
      digitalWrite(GREEN_LED, HIGH);
      delay(1000);
      digitalWrite(GREEN_LED, LOW);
    } else if (command == "rotate_right") {
      digitalWrite(RED_LED, HIGH);
      delay(1000);
      digitalWrite(RED_LED, LOW);
    } else if (command == "open_claw") {
      digitalWrite(BLUE_LED, HIGH);
      delay(1000);
      digitalWrite(BLUE_LED, LOW);
    }
  }
}
