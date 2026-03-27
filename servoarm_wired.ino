#include <AltSoftSerial.h>
#include <ServoTimer2.h>

AltSoftSerial BTserial;

ServoTimer2 servo1;
ServoTimer2 servo2;
ServoTimer2 servo3;
ServoTimer2 servo4;
ServoTimer2 servo5;

int flex1 = A1;
int flex2 = A2;
int flex3 = A3;
int flex4 = A4;
int flex5 = A5;

void setup()  
{
  Serial.begin(9600);
  BTserial.begin(9600);
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
}


void loop()
{
  int flex1_pos;  
  int servo1_pos;  
  flex1_pos = analogRead(flex1); 
  servo1_pos = map(flex1_pos, 0, 700, 0, 180); 
  servo1_pos = constrain(servo1_pos, 0, 180);  
  // Serial.println(servo1_pos);
  servo1.write(servo1_pos);

  int flex2_pos;  
  int servo2_pos;  
  flex2_pos = analogRead(flex2); 
  servo2_pos = map(flex2_pos, 879, 882, 0, 180); 
  servo2_pos = constrain(servo2_pos, 0, 180);  
  servo2.write(servo2_pos);
  

  int flex3_pos;  
  int servo3_pos;  
  flex3_pos = analogRead(flex3); 
  servo3_pos = map(flex3_pos, 828, 824, 180, 0); 
  servo3_pos = constrain(servo3_pos, 180, 0);  
  servo3.write(servo3_pos);
  
  int flex4_pos;  
  int servo4_pos;  
  flex4_pos = analogRead(flex4); 
  servo4_pos = map(flex4_pos, 874, 878, 0, 180); 
  servo4_pos = constrain(servo4_pos, 0, 180);  
  servo4.write(servo4_pos);
  
  int flex5_pos;  
  int servo5_pos;  
  flex5_pos = analogRead(flex5); 
  servo5_pos = map(flex5_pos, 855, 851, 180, 0); 
  servo5_pos = constrain(servo5_pos, 180, 0);  
  servo5.write(servo5_pos);
  
  // Transmitter - replace BTserial.write(flex1_pos) with:
  BTserial.print(flex1_pos);
  // BTserial.print("\n"); // newline so receiver knows where value ends
  /*
Serial.print(servo1_pos);
Serial.print("--");
Serial.print(servo2_pos);
Serial.print("--");
Serial.print(servo3_pos);
Serial.print("--");
Serial.print(servo4_pos);
Serial.print("--");
Serial.print(servo5_pos);
Serial.println("--");
*/

Serial.println(flex1_pos);
// Serial.print("--");
// Serial.print(flex2_pos);
// Serial.print("--");
// Serial.print(flex3_pos);
// Serial.print("--");
// Serial.print(flex4_pos);
// Serial.print("--");
// Serial.print(flex5_pos);
// Serial.println("--");

  delay(50);
 
 
}
