


const int SERVO_OFFSET_A = 2; // offset to match servo's "zero point"
const int SERVO_OFFSET_B = 1; // offset to match servo's "zero point"



#include <Servo.h>
#include <AccelStepper.h>
#include <Adafruit_MotorShield.h>
#include <Arduino_APDS9960.h>


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
  stepper_A->onestep(FORWARD, SINGLE);
}
void backwardstep1() {
  stepper_A->onestep(BACKWARD, SINGLE);
}
// wrappers for the second motor!
void forwardstep2() {
  stepper_B->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {
  stepper_B->onestep(BACKWARD, DOUBLE);
}

AccelStepper stepperA(forwardstep1, backwardstep1);   // assign wrappers
AccelStepper stepperB(forwardstep2, backwardstep2);

// ********************************************** SERVO WRAPPER FUNCTIONS ****************************


// -90 = CCW
//  0  = NOTHING
//  90 = CLOCKWISE
void turnServo(Servo target, int amount) {
//  if (target == servo_A) {
//    target.write(OFFSET_A + amount + 90); 
//  }
//  else {
//    target.write(OFFSET_B + amount + 90);
//  }
}
boolean isOpen;
void openServos() {
  if (isOpen) {return;}
  
}

// ********************************************** COLOUR WRAPPER FUNCTIONS ****************************
// OUTPUT
//    -1 INVALID
//     0 NOT RED
//     1 RED
int isRed() {
  Serial.begin(9600);
  
  // check if colour sensor returns "red"
  int r, g, b;
  if (APDS.colorAvailable()) {
    APDS.readColor(r, g, b);

    // R > 15, G < 15, B < 15

    // (G < 0.6 * R) and (B < 0.6 * R)
    if (g < 0.6 * r && b < 0.6 * r) {
      return 1;
    }
    else {
      return 0;
    }
  }
  else {
    return -1;
  }
}





// ****************************************************************************************************

void setup() {
  servo_A.attach(10);  // attaches the servo on pin 9 to the servo object
  servo_B.attach(9);  // attaches the servo on pin 9 to the servo object

//  turnServo(servo_A, 0);
//  turnServo(servo_B, 0);
  servo_A.write(90 + SERVO_OFFSET_A);
  servo_B.write(90 + SERVO_OFFSET_B);
  
  
  // start top shield, start bottom shield?
//  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield


  stepperA.setMaxSpeed(100.0);
  stepperA.setAcceleration(100.0);
  stepperA.moveTo(24);

  stepperB.setMaxSpeed(200.0);
  stepperB.setAcceleration(100.0);
  stepperB.moveTo(50000);

  
  // START COLOUR SENSOR
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
  }
  APDS.setLEDBoost(3);
  
}

void loop() {
//  int x;
//  x = isRed();
//  if (x != -1) {
//    Serial.print("VAL: ");
//    Serial.println(x);
//  }
//
//  delay(50);
  
  
//  openServos();

  // STATE MACHINE
  

  
}
