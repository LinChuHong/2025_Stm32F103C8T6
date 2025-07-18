#include "myStepper.h"


myStepper::myStepper(/* args */)
{
}
myStepper::myStepper(uint32_t stepPin, uint32_t dirPin, uint32_t enablePin, TIM_TypeDef *instance)
    : HardwareTimer(instance), stepPin(stepPin), dirPin(dirPin), enablePin(enablePin)
{
    Serial.println("myStepper constructor with parameters called");
    // Initialize the stepper motor pins
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    
    // Set initial state
    digitalWrite(enablePin, LOW); // Enable the stepper motor
    
}

myStepper::~myStepper()
{
    Serial.println("myStepper destructor called");
}
