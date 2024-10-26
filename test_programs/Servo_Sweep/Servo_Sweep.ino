const int SERVO_OFFSET_A = 1; // offset to match servo's "zero point"
const int SERVO_OFFSET_B = 1; // offset to match servo's "zero point"




#include <Servo.h>

Servo servo_A;  // create servo object to control a servo
Servo servo_B;

int pos = 0;    // variable to store the servo position

void setup() {
  servo_A.attach(10);  // attaches the servo on pin 9 to the servo object
  servo_B.attach(9);  // attaches the servo on pin 9 to the servo object

  servo_A.write(90 + SERVO_OFFSET_A);
  servo_B.write(90 + SERVO_OFFSET_B);
}



void servo_open(float speed_factor) {
  if (speed_factor == 0) {speed_factor = 1;}
  
//  servo_B.write(90 + SERVO_OFFSET_B - 10 * speed_factor);
//  delay(850 / speed_factor);
//  servo_B.write(90 + SERVO_OFFSET_B - 3 * speed_factor);
//  delay(600 / speed_factor);
//  servo_B.write(90 + SERVO_OFFSET_B + 0);
  
  
  servo_B.write(90 + SERVO_OFFSET_B - 3 * speed_factor);
  delay(300 / abs(speed_factor));
  servo_A.write(90 + SERVO_OFFSET_A - 3 * -speed_factor);
  delay(100 / abs(speed_factor));

  servo_B.write(90 + SERVO_OFFSET_B - 10 * speed_factor);
  delay(300 / abs(speed_factor));
  servo_A.write(90 + SERVO_OFFSET_A - 10 * -speed_factor);
  delay(450 / abs(speed_factor));

  
  servo_B.write(90 + SERVO_OFFSET_B - 3 * speed_factor);
  delay(300 / abs(speed_factor));
  servo_A.write(90 + SERVO_OFFSET_A - 3 * -speed_factor);
  delay(300 / abs(speed_factor));
  
  
  servo_B.write(90 + SERVO_OFFSET_B + 0);
  delay(300 / abs(speed_factor));
  servo_A.write(90 + SERVO_OFFSET_A + 0);
}

void servo_close(float speed_factor) {
  if (speed_factor == 0) {speed_factor = 1;}
  servo_open(-speed_factor);
}

void loop() {
  
  servo_open(1);
  delay(1000);
  
 
  servo_close(1); 
  delay(3000);
}
