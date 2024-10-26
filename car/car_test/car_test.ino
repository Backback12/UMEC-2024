
#include <Servo.h>
#include <AccelStepper.h>
#include <Adafruit_MotorShield.h>


Adafruit_MotorShield AFMSbot(0x61); // included in example and it worked
Adafruit_MotorShield AFMStop(0x60);

Adafruit_StepperMotor *stepper_A = AFMStop.getStepper(200, 1);  // 200 steps per rev (1.8deg)
Adafruit_StepperMotor *stepper_B = AFMStop.getStepper(200, 2);

Servo servo_A;
Servo servo_B;



// ********************************************** STEPPER MOTOR WRAPPER FUNCTIONS ****************************

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {
  myStepper1->onestep(FORWARD, SINGLE);
}
void backwardstep1() {
  myStepper1->onestep(BACKWARD, SINGLE);
}
// wrappers for the second motor!
void forwardstep2() {
  myStepper2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {
  myStepper2->onestep(BACKWARD, DOUBLE);
}

AccelStepper stepper1(forwardstep1, backwardstep1);   // assign wrappers
AccelStepper stepper2(forwardstep2, backwardstep2);


void setup() {
  servo_A.attach(10);  // attaches the servo on pin 9 to the servo object
  servo_B.attach(9);  // attaches the servo on pin 9 to the servo object

  
  // start top shield, start bottom shield?
//  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield


  stepper1.setMaxSpeed(100.0);
  stepper1.setAcceleration(100.0);
  stepper1.moveTo(24);

  stepper2.setMaxSpeed(200.0);
  stepper2.setAcceleration(100.0);
  stepper2.moveTo(50000);
}

void loop() {
  
}
