#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:

#define dirPin 4
#define stepPin 3
#define motorInterfaceType 1
#define button1Pin 43
#define button2Pin 42
#define ledPin 13

#define button1Turns 160
#define button2Turns 260

#define stepsPerTurn 200
#define velocity 400

int button1State, button2State = 0;

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  stepper.setCurrentPosition(0);
  stepper.setMaxSpeed(1000);
}

void turn(int turns) {
  digitalWrite(ledPin, HIGH);
  while(stepper.currentPosition() != stepsPerTurn * turns)
  {
    button1State = digitalRead(button1Pin);
    button2State = digitalRead(button2Pin);

    if(button1State == HIGH && button2State == HIGH) {
      delay(500);
      break;     
    }   

    stepper.setSpeed(velocity);
    stepper.runSpeed();
  } 
  digitalWrite(ledPin, LOW);
}

void loop() { 
    stepper.setCurrentPosition(0);
  
    button1State = digitalRead(button1Pin);
    button2State = digitalRead(button2Pin);

    if (button1State == HIGH)
      turn(button1Turns);
    
    else if (button2State == HIGH)
      turn(button2Turns);
     
}
