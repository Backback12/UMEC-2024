/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo servo_A;  // create servo object to control a servo
Servo servo_B;

int pos = 0;    // variable to store the servo position

void setup() {
  servo_A.attach(10);  // attaches the servo on pin 9 to the servo object
  servo_B.attach(9);  // attaches the servo on pin 9 to the servo object

//  servo_90.write(90);
//  servo_40.write(90);
//  servo_90.writeMicroseconds(1500);
//  servo_40.writeMicroseconds(1500);

//  delay(5000);
  
//  servo_90.detach();
//  servo_40.detach();
}

void loop() {
//  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    servo_90.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);
//  }
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    servo_90.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15 ms for the servo to reach the position
//  }
//  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    servo_40.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15 ms for the servo to reach the position
//  }
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    servo_40.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15 ms for the servo to reach the position
//  }
  
//  servo_90.write(0);
//  servo_40.write(0);
//
//  delay(200);
//
//  servo_90.write(90);
//  servo_40.write(90);
//
//  delay(200);
// 
//  servo_90.write(180);
//  servo_40.write(180);
//
//  delay(200);
//
//  servo_90.write(270);
//  servo_40.write(270);
//
//  delay(200);

//  servo_A.write(92);
//  servo_B.write(92);
  int OFFSET = 2;
  
//  int i = 0;
//  for (i = 0; i < 4; i++) {
//    
//    servo_A.write(OFFSET + i * 90);
////    servo_90.write(90 - 10 + (i * 10));
//    
//    delay(500);
//
//    servo_B.write(OFFSET + 180 - i * 90);
////    servo_40.write(90 + 10 - (i * 10));
//
//    delay(500);
//  }

//  servo_90.write


servo_A.write(OFFSET + 0); // A LEFT
servo_B.write(OFFSET + 90); // B STOP
delay(500);
servo_A.write(OFFSET + 90); // A STOP
servo_B.write(OFFSET + 180); // B RIGHT
delay(500);
servo_A.write(OFFSET + 180); // A RIGHT
servo_B.write(OFFSET + 90); // B STOP
delay(500);
servo_A.write(OFFSET + 90); // A STOP
servo_B.write(OFFSET + 0); // B LEFT
delay(500);



}
