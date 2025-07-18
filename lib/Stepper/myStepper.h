#ifndef __MYSTEPPER_H__
#define __MYSTEPPER_H__
#include <Arduino.h>
#include "HardwareTimer.h"

class myStepper : public HardwareTimer
{
private:
    HardwareTimer *timer; // Pointer to the HardwareTimer instance
    uint32_t stepPin;     // Pin for step signal
    uint32_t dirPin;      // Pin for direction signal
    uint32_t enablePin;   // Pin to enable/disable the stepper motor
    /* data */
    
public:
    myStepper(/* args */);
    myStepper(uint32_t stepPin, uint32_t dirPin, uint32_t enablePin, TIM_TypeDef *instance = TIM2);
    
   
    ~myStepper();
};


#endif // __MYSTEPPER_H__