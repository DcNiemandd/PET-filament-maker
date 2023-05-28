#include <AccelStepper.h>
#include "HCMotor.h" //Include HCMotor Code Library

//HCMotor
#define MOTOR_PIN 6 // Assign to PWM/Digital Pin 6
#define POT_PIN A1 // Set analog pin at A0 for the potentiometer
HCMotor HCMotor; // Create an instance of our code library

//AccelStepper
// Define the stepper motor and the pins that is connected to
AccelStepper stepper1(1, 4, 2); // (Type of driver: with 2 pins, STEP, DIR)

void setup()
{
  //HCMotor
  HCMotor.Init(); //Initialise our library
  HCMotor.attach(0, DCMOTOR, MOTOR_PIN); // Attach our motor to 0 to digital pin 6
  HCMotor.DutyCycle(0, 100);
  
  //AccelStepper
  // Set maximum speed value for the stepper
  stepper1.setMaxSpeed(500);
}
void loop()
{
  //HCMotor
  int Speed;
  Speed = map(analogRead(POT_PIN), 0, 1024, 0, 100); //Reading the A0 pin to determine the position of the pot.
  //mapping the motor which could be 0 - 1024 and reduce down to match the cyccle range of 0 to 100
  HCMotor.OnTime(0, Speed); // Set the duty cycle to match the position
  
  //AccelStepper
  stepper1.setSpeed((analogRead(A0)));
  // Step the motor with a constant speed previously set by setSpeed();
  stepper1.runSpeed();
}
