#include <AltSoftSerial.h>
AltSoftSerial BTserial;

String c;
void setup() {
  // put your setup code here, to run once:
  BTserial.begin(9600);
  Serial.begin(9600);
  pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // c = BTserial.read();
  if (BTserial.available() > 0) {
    String val = BTserial.readStringUntil('\n');
    int flex1_pos = val.toInt();
    Serial.println(flex1_pos);

    // Map to PWM if needed
    int brightness = map(flex1_pos, 790, 880, 0, 255);
    brightness = constrain(brightness, 0, 255);
    analogWrite(6, brightness); // pin 6 is PWM
  }

}
