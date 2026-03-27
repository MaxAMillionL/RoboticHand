// ============================================================
//  TRANSMITTER
//  HM-10 on pins 2 (RX) & 3 (TX)  |  Flex sensor on A0
//  Reads the flex sensor and sends its raw value over BLE
//  every 50 ms so the receiver can drive a servo.
// ============================================================

#include <SoftwareSerial.h>

// HM-10 wiring:  Arduino pin 2  → HM-10 TX
//                Arduino pin 3  → HM-10 RX
SoftwareSerial BLE(2, 3);   // RX, TX

const int FLEX_PIN     = A0;
const int SEND_INTERVAL = 50;   // ms between transmissions

// Calibration — tune these to your physical flex sensor
const int FLEX_MIN = 0;     // fully bent reading
const int FLEX_MAX = 700;   // fully straight reading

void setup() {
  Serial.begin(9600);
  BLE.begin(9600);           // HM-10 default baud rate
  Serial.println("Transmitter ready");
}

void loop() {
  int raw = analogRead(FLEX_PIN);

  // Clamp to calibrated range before sending
  raw = constrain(raw, FLEX_MIN, FLEX_MAX);

  // Send as plain ASCII integer terminated with newline
  // e.g.  "512\n"
  BLE.println(raw);

  Serial.print("Sent: ");
  Serial.println(raw);

  delay(SEND_INTERVAL);
}
