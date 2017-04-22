#include <Arduino.h>
#include "BasicStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// All the wires needed for full functionality
#define DIR 8
#define STEP 9
//Uncomment line to use enable/disable functionality
#define ENBL 7

// Since microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 2

// 2-wire basic config, microstepping is hardwired on the driver
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

//Uncomment line to use enable/disable functionality
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, ENBL);
char buffer[10];
int data[2];
int bindex,dindex=0;
int incomingByte;

void setup() {
   
    Serial.begin(9600);
}

void loop() {

  Serial.println("Warten auf Eingabe...");
  //Wenn eine Serielle eingabe getätigt wurde
  if (Serial.available() > 0) {  
    String myString = Serial.readString();
    int Index1 = myString.indexOf(',');
    int Index2 = myString.indexOf(',', Index1+1);
    int Index3 = myString.indexOf(',', Index2+1);
    String secondValue = myString.substring(Index1+1, Index2);
    String firstValue = myString.substring(Index2+1, Index3);  

    int mmode = firstValue.toInt();
    int mspeed = secondValue.toInt();
    int vorwaerts = 1;
    int rueckwerts = 2;
    int disablemotor = 9;
    int maxspeed = 799;

    if (mmode == vorwaerts)
    {
    stepper.enable();
    if(mspeed >= maxspeed){
      int mspeed = 700;
    }
    stepper.setRPM(mspeed);
    stepper.setMicrostep(MICROSTEPS);
    stepper.rotate(3600);
    //stepper.disable();
    
    } 

    if (mmode == rueckwerts)
    {
    Serial.println("Step5");
    stepper.setRPM(mspeed);
    stepper.enable();
    stepper.setMicrostep(MICROSTEPS);
    stepper.rotate(-3600);
    //stepper.disable();
    }   

    if (mmode == disablemotor)
    {
      stepper.disable();
    }
  }
  delay(500);
}
