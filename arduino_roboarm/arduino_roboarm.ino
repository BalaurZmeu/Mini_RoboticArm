#include <SoftwareSerial.h>

#define GREEN_LED 2
#define RED_LED 4
#define BLUE_LED 6
#define YELLOW_LED 8 

String incomingString;


void setup() {

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);

  Serial.begin(115200);
}


void loop() {
  if (Serial.available() > 0) {
    incomingString = Serial.readString();

    if (incomingString.equals("rotate_left_on")) {
      digitalWrite(GREEN_LED, HIGH); // Turn LED ON while pressed
    }
    if (incomingString.equals("rotate_left_off")) {
      digitalWrite(GREEN_LED, LOW); // Turn LED OFF when released
    }
    
    if (incomingString.equals("rotate_right_on")) {
      digitalWrite(GREEN_LED, HIGH);
    }
    if (incomingString.equals("rotate_right_off")) {
      digitalWrite(GREEN_LED, LOW);
    }

    if (incomingString.equals("shoulder_fwd_on")) {
      digitalWrite(RED_LED, HIGH);
    }
    if (incomingString.equals("shoulder_fwd_off")) {
      digitalWrite(RED_LED, LOW);
    }

    if (incomingString.equals("shoulder_bkd_on")) {
      digitalWrite(RED_LED, HIGH);
    }
    if (incomingString.equals("shoulder_bkd_off")) {
      digitalWrite(RED_LED, LOW);
    }
    
    if (incomingString.equals("elbow_up_on")) {
      digitalWrite(BLUE_LED, HIGH);
    }
    if (incomingString.equals("elbow_up_off")) {
      digitalWrite(BLUE_LED, LOW);
    }

    if (incomingString.equals("elbow_down_on")) {
      digitalWrite(BLUE_LED, HIGH);
    }
    if (incomingString.equals("elbow_down_off")) {
      digitalWrite(BLUE_LED, LOW);
    }

    if (incomingString.equals("open_claw_on")) {
      digitalWrite(YELLOW_LED, HIGH);
    }
    if (incomingString.equals("open_claw_off")) {
      digitalWrite(YELLOW_LED, LOW);
    }

    if (incomingString.equals("close_claw_on")) {
      digitalWrite(YELLOW_LED, HIGH);
    }
    if (incomingString.equals("close_claw_off")) {
      digitalWrite(YELLOW_LED, LOW);
    }
  }
}
