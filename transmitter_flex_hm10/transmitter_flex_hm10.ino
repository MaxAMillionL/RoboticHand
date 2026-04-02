// ============================================================
//  TRANSMITTER
//  HM-10 on pins 2 (RX) & 3 (TX)  |  Flex sensors on A0–A4
//  Reads all 5 flex sensors and sends a comma-separated string
//  over BLE every 50 ms, but only if a value changed.
//  Format:  "512,490,323,601,450\n"
// ============================================================

#include <SoftwareSerial.h>

SoftwareSerial BLE(2, 3);   // RX=2, TX=3

const int flexPins[5]   = {A0, A1, A2, A3, A4};
const int SEND_INTERVAL = 50;
const int FLEX_MIN      = 0;
const int FLEX_MAX      = 700;
const int MARGIN_OF_ERROR = 1;

int old_values[5] = {0, 0, 0, 0, 0};  // Fixed: was missing semicolon

void setup() {
  Serial.begin(9600);
  BLE.begin(9600);
  Serial.println("Transmitter ready");
}

void loop() {
  int fingers[5];
  bool changed = false;

  // Read and constrain all sensors
  for (int i = 0; i < 5; i++) {
    fingers[i] = analogRead(flexPins[i]);
    fingers[i] = constrain(fingers[i], FLEX_MIN, FLEX_MAX);

    // Check if any finger value changed beyond margin of error
    if (fingers[i] < old_values[i] - MARGIN_OF_ERROR ||
        fingers[i] > old_values[i] + MARGIN_OF_ERROR) {
      changed = true;
    }
  }

  // Only transmit if at least one value changed
  if (changed) {
    // Build comma-separated string: "512,490,323,601,450"
    String fingerData = "";
    for (int i = 0; i < 5; i++) {
      fingerData += String(fingers[i]);
      if (i < 4) fingerData += ",";
    }

    BLE.println(fingerData);   // Sends string + "\n"

    Serial.print("Sent: ");
    Serial.println(fingerData);

    // Update old values only after a successful send
    for (int i = 0; i < 5; i++) {
      old_values[i] = fingers[i];
    }
  }

  delay(SEND_INTERVAL);
}