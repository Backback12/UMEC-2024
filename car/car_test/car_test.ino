


const float SERVO_OFFSET_A = 1.0; // offset to match servo's "zero point"
const float SERVO_OFFSET_B = 1.0; // offset to match servo's "zero point"

const float SERVO_FACTOR_A = 1.0; // servo speed factor
const float SERVO_FACTOR_B = 1.0;

const float MOTOR_FACTOR_A = 1.0;
const float MOTOR_FACTOR_B = 1.0;





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
//AccelStepper stepperB(forwardstep2, backwardstep2);
AccelStepper stepperB(backwardstep2, forwardstep2);   // INVERT STEPPER B

// ********************************************** SERVO WRAPPER FUNCTIONS ****************************



// ********************************************** COLOUR WRAPPER FUNCTIONS ****************************
// OUTPUT
//    -1 INVALID
//     0 NOT RED
//     1 RED
int isRed() {
  
  
  // check if colour sensor returns "red"
  int r, g, b;
  if (APDS.colorAvailable()) {
    APDS.readColor(r, g, b);

    // R > 15, G < 15, B < 15

    // (G < 0.6 * R) and (B < 0.6 * R)
    if (g < 0.6 * r && b < 0.6 * r) {
      return 1;     // valid read, is RED! ! return 1
    }
    else {
      return 0;     // valid read, NOT RED
    }
  }
  else {
    return -1;      // invalid read
  }
}


// ****************************************************************************************************
// ****************************************************************************************************
// ********************* DRIVING HELPER FUNCTIONS ****************************
void motor_drive(float speed_A, float speed_B, float duration) {
  // duration is NOT seconds
  //
  stepperA.setMaxSpeed(speed_A * abs(MOTOR_FACTOR_A)); 
  stepperB.setMaxSpeed(speed_B * abs(MOTOR_FACTOR_B));
  stepperA.moveTo(duration * MOTOR_FACTOR_A);
  stepperB.moveTo(duration * MOTOR_FACTOR_B);
  
  while (stepperA.distanceToGo() != 0 && stepperB.distanceToGo() != 0) {
    stepperA.run();
    stepperB.run();
  }
  
}

void drive_until_red() {
  int x = isRed();
  while (x == -1) {x = isRed();} // read until valid read
  if (x == 1) {return;}    // ALREADY RED
  
  stepperA.setMaxSpeed(500 * abs(MOTOR_FACTOR_A));
  stepperB.setMaxSpeed(500 * abs(MOTOR_FACTOR_B));
  stepperA.moveTo(1000000); // infinite
  stepperB.moveTo(1000000);

  while (isRed() != 1) {
    stepperA.run();
    stepperB.run();
  }

  stepperA.stop();
  stepperB.stop(); 
}

void drive_little_bit() {
  stepperA.setMaxSpeed(500 * abs(MOTOR_FACTOR_A)); 
  stepperB.setMaxSpeed(500 * abs(MOTOR_FACTOR_B));
  stepperA.moveTo(100 * MOTOR_FACTOR_A);
  stepperB.moveTo(100 * MOTOR_FACTOR_B);
  
  while (stepperA.distanceToGo() != 0 && stepperB.distanceToGo() != 0) {
    stepperA.run();
    stepperB.run();
  }

//  stepperA.stop();
//  stepperB.stop();
}


void sweep_out() {
// SWEEP A
  int sign = 1;
  servo_A.write(90 + SERVO_OFFSET_A + 3 * SERVO_FACTOR_A * sign);
  delay(100 / abs(SERVO_FACTOR_A));
  servo_A.write(90 + SERVO_OFFSET_A + 10 * SERVO_FACTOR_A * sign);
  delay(850 / abs(SERVO_FACTOR_A));
  servo_A.write(90 + SERVO_OFFSET_A + 3 * SERVO_FACTOR_A * sign);
  delay(300 / abs(SERVO_FACTOR_A));
  servo_A.write(90 + SERVO_OFFSET_A + 0);

// SWEEP B
  sign = -1;
  servo_B.write(90 + SERVO_OFFSET_B + 3 * SERVO_FACTOR_B * sign);
  delay(100 / abs(SERVO_FACTOR_B));
  servo_B.write(90 + SERVO_OFFSET_B + 10 * SERVO_FACTOR_B * sign);
  delay(850 / abs(SERVO_FACTOR_B));
  servo_B.write(90 + SERVO_OFFSET_B + 3 * SERVO_FACTOR_B * sign);
  delay(300 / abs(SERVO_FACTOR_B));
  servo_B.write(90 + SERVO_OFFSET_B + 0);
}


void sweep_in() {
// SWEEP A
  int sign = -1;
  servo_A.write(90 + SERVO_OFFSET_A + 3 * SERVO_FACTOR_A * sign);
  delay(100 / abs(SERVO_FACTOR_A));
  servo_A.write(90 + SERVO_OFFSET_A + 10 * SERVO_FACTOR_A * sign);
  delay(850 / abs(SERVO_FACTOR_A));
  servo_A.write(90 + SERVO_OFFSET_A + 3 * SERVO_FACTOR_A * sign);
  delay(300 / abs(SERVO_FACTOR_A));
  servo_A.write(90 + SERVO_OFFSET_A + 0);

// SWEEP B
  sign = 1;
  servo_B.write(90 + SERVO_OFFSET_B + 3 * SERVO_FACTOR_B * sign);
  delay(100 / abs(SERVO_FACTOR_B));
  servo_B.write(90 + SERVO_OFFSET_B + 10 * SERVO_FACTOR_B * sign);
  delay(850 / abs(SERVO_FACTOR_B));
  servo_B.write(90 + SERVO_OFFSET_B + 3 * SERVO_FACTOR_B * sign);
  delay(300 / abs(SERVO_FACTOR_B));
  servo_B.write(90 + SERVO_OFFSET_B + 0);
}


void printstate(String text) {
  Serial.println(text);
}

// ****************************************************************************************************
// ****************************************************************************************************
// ****************************************************************************************************

void setup() {
  Serial.begin(9600);


  
  servo_A.attach(10);  // attaches the servo on pin 9 to the servo object
  servo_B.attach(9);  // attaches the servo on pin 9 to the servo object

//  turnServo(servo_A, 0);
//  turnServo(servo_B, 0);
  servo_A.write(90 + SERVO_OFFSET_A);
  servo_B.write(90 + SERVO_OFFSET_B);
  servo_A.write(90 + SERVO_OFFSET_A + 4);
  
  
  // start top shield, start bottom shield?
//  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield


//  stepperA.setMaxSpeed(100.0);
  stepperA.setAcceleration(1000.0);
//  stepperA.moveTo(24);

//  stepperB.setMaxSpeed(200.0);
  stepperB.setAcceleration(1000.0);
//  stepperB.moveTo(50000);

  
  // START COLOUR SENSOR
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
  }
  APDS.setLEDBoost(3);
  
}

void loop() {

//  while (true) {
//    drive_little_bit();
//    delay(3000);
//  }

  // STATE MACHINE
  

//  drive_until_red();

//-----------------------------------------------------------
// =================== START ==================
  // move to starting line

  printstate("GOING TO START");
  drive_until_red();




  //snow (assume servos start closed fully)
  // - drive until color sensor sees red
  //   - fully open servos (clearing snow)
  //   - drive a little forward
  //   - repeat up until red
  printstate("STARTING SNOW SECTION 1");  
  drive_little_bit();
  drive_until_red();
  sweep_out();
  
  //people
  // - drive until color sensor sees red
  // - fully close servos (collecting people)
  printstate("STARTING PEOPLE SECTION 1");
  drive_little_bit();
  drive_until_red();
  sweep_in();
  
  //snow (assume servos start closed fully)
  // - drive until color sensor sees red
  // - fully open servos (clearing snow)
  printstate("STARTING SNOW SECTION 2");
  drive_little_bit();
  drive_until_red();
  sweep_out();
  
  //people
  // - drive until color sensor sees red
  // - fully close servos (collecting people)
  printstate("STARTING PEOPLE SECTION 2");
  drive_little_bit();
  drive_until_red();
  sweep_in();

  //snow (assume servos start closed fully)
  // - drive until color sensor sees red
  // - fully open servos (clearing snow)
  printstate("STARTING SNOW SECTION 3");
  drive_little_bit();
  drive_until_red();
  sweep_out();

  //people
  // - drive until color sensor sees red
  // - fully close servos (collecting people)
  printstate("STARTING PEOPLE SECTION 3");
  drive_little_bit();
  drive_until_red();
  sweep_in();

  //turn
  // - drive the turn
  printstate("STARTING TURN");
  motor_drive(300, 50, 5000); // mot_A: 500, mot_B: 50, duration: 5000ms
  motor_drive(-50, -100, 3000); // mot_A: 500, mot_B: 50, duration: 5000ms
  motor_drive(300, 50, 3000); // mot_A: 500, mot_B: 50, duration: 5000ms
  

  

  //snow (assume servos start closed fully)
  // - drive until color sensor sees red
  // - fully open servos (clearing snow)
  printstate("STARTING SNOW SECTION 4");
  drive_little_bit();
  drive_until_red();
  sweep_out();

  //people
  // - drive until color sensor sees red
  // - fully close servos (collecting people)
  printstate("STARTING PEOPLE SECTION 4");
  drive_little_bit();
  drive_until_red();
  sweep_in();
  
//-----------------------------------------------------------
}
