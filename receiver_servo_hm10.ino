// ============================================================
//  RECEIVER
//  HM-10 on pins 2 (RX) & 3 (TX)  |  Servo on digital pin 8
//  Reads the raw flex value sent by the transmitter and maps
//  it to a servo angle (0–180°).
// ============================================================

#include <SoftwareSerial.h>
#include <Servo.h>

// HM-10 wiring:  Arduino pin 2  → HM-10 TX
//                Arduino pin 3  → HM-10 RX
SoftwareSerial BLE(2, 3);   // RX, TX

Servo myServo;
const int SERVO_PIN = 8;

// Must match the calibration values used in the transmitter
const int FLEX_MIN = 0;
const int FLEX_MAX = 700;

void setup() {
  Serial.begin(9600);
  BLE.begin(9600);           // HM-10 default baud rate
  myServo.attach(SERVO_PIN);
  myServo.write(0);          // Start at 0°
  Serial.println("Receiver ready");
}

void loop() {
  // Read a complete line sent by the transmitter
  if (BLE.available()) {
    String incoming = BLE.readStringUntil('\n');
    incoming.trim();          // Strip whitespace / CR

    if (incoming.length() > 0) {
      int flexValue = incoming.toInt();

      // Guard against garbage / out-of-range data
      flexValue = constrain(flexValue, FLEX_MIN, FLEX_MAX);

      // Map raw flex value → servo angle 0–180°
      int angle = map(flexValue, FLEX_MIN, FLEX_MAX, 0, 180);

      myServo.write(angle);

      Serial.print("Received: ");
      Serial.print(flexValue);
      Serial.print("  →  Angle: ");
      Serial.println(angle);
    }
  }
}
