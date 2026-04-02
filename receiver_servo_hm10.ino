// ============================================================
//  RECEIVER
//  HM-10 on pins 2 (RX) & 3 (TX)  |  5 Servos on pins 8–12
//  Parses comma-separated flex values and drives each servo
//  Format expected: "512,490,323,601,450\n"
// ============================================================

#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BLE(2, 3);   // RX, TX

const int SERVO_PINS[5] = {8, 9, 10, 11, 12};
Servo servos[5];

const int FLEX_MIN = 0;
const int FLEX_MAX = 700;

void setup() {
  Serial.begin(9600);
  BLE.begin(9600);

  for (int i = 0; i < 5; i++) {
    servos[i].attach(SERVO_PINS[i]);
    servos[i].write(0);        // Start all servos at 0°
  }

  Serial.println("Receiver ready");
}

void loop() {
  if (BLE.available()) {
    String incoming = BLE.readStringUntil('\n');
    incoming.trim();

    if (incoming.length() > 0) {
      Serial.print("Received: ");
      Serial.println(incoming);

      // Parse comma-separated values into an array
      int fingers[5] = {0};
      int fingerIndex = 0;
      int lastComma = -1;

      for (int i = 0; i <= (int)incoming.length() && fingerIndex < 5; i++) {
        if (i == (int)incoming.length() || incoming.charAt(i) == ',') {
          // Slice the substring between the last comma and this one
          String token = incoming.substring(lastComma + 1, i);
          fingers[fingerIndex++] = token.toInt();
          lastComma = i;
        }
      }

      // Drive each servo from its parsed flex value
      for (int i = 0; i < 5; i++) {
        int flexValue = constrain(fingers[i], FLEX_MIN, FLEX_MAX);
        int angle     = map(flexValue, FLEX_MIN, FLEX_MAX, 0, 180);
        servos[i].write(angle);

        Serial.print("  Finger ");
        Serial.print(i + 1);
        Serial.print(": flex=");
        Serial.print(flexValue);
        Serial.print("  angle=");
        Serial.println(angle);
      }
    }
  }
}