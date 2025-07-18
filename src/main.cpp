#include <Arduino.h>
#include "OneButton.h"

OneButton button1(PB12, true); // Button on PA2 with pull-up enabled
OneButton button2(PB13, true); // Button on PA2 with pull-up enabled

HardwareTimer *myTimer2 = new HardwareTimer(TIM2);
#define MYSREPPER1DIR PA2
uint32_t stepCount = 0;
uint8_t stepper1State = 0; // 0: stopped, 1: running
void setup() 
{
    Serial.begin(115200);
   
    pinMode(MYSREPPER1DIR, OUTPUT); // Set DIR pin as output
    digitalWrite(MYSREPPER1DIR, LOW); // Set initial direction to LOW

    myTimer2->setPrescaleFactor(72); // 72 MHz / 72 = 1 MHz timer clock (1 tick = 1 us)
    myTimer2->setOverflow(50, MICROSEC_FORMAT); // PWM period: 30 us (~33.3 kHz)

    
    
    


    

 
    button1.setup(PB12, INPUT_PULLUP, true); // Initialize button on PB12 with pull-up enabled
    button2.setup(PB13, INPUT_PULLUP, true); // Initialize button on PB12 with pull-up enabled

    button1.attachPress([]() {
        myTimer2->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PA0); // Channel 1, PWM mode, output on PA0
        myTimer2->setCaptureCompare(1, 25, MICROSEC_COMPARE_FORMAT); // 50% duty cycle (15/30)

        myTimer2->setMode(2, TIMER_OUTPUT_COMPARE_PWM1, PA1); // Channel 1, PWM mode, output on PA0
        myTimer2->setCaptureCompare(2, 25, MICROSEC_COMPARE_FORMAT); // 50% duty cycle (15/30)
        myTimer2->resume(); // Start the timer when button 1 is pressed
    });
    button2.attachPress([]() {
        myTimer2->pause(); // Pause the timer after 3200 steps
        myTimer2->pauseChannel(1); // Pause channel 1
        myTimer2->pauseChannel(2); // Pause channel 1
    });
    myTimer2->attachInterrupt([]() {
        stepCount++; // Increment step count on each timer interrupt
        if (stepCount >= 320000)
        {
            myTimer2->pause(); // Pause the timer after 3200 steps
            Serial.printf("Paused after %d steps\n", stepCount);
            stepCount = 0; // Reset step count
        }
    }); // Attach an interrupt callback

}

void loop() 
{
    button1.tick(); // Check button state
    button2.tick(); // Check button state
  
}
