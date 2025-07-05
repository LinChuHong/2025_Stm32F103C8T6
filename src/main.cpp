#include <Arduino.h>
#include "OneButton.h"
#define RELAY1 PA0
#define RELAY2 PA1
#define SWITCH1 PB12
#define SWITCH1GROUND PB13
#define TOSTARTSWITCH PB14



OneButton button(SWITCH1, true);

uint8_t SWITCH1State = 0;
int buttonState;



void buttonInit()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(TOSTARTSWITCH, INPUT_PULLUP);
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    pinMode(SWITCH1, INPUT_PULLUP);
    pinMode(SWITCH1GROUND, OUTPUT);
    digitalWrite(SWITCH1GROUND, LOW);
    button.attachPress([]() 
    {
        if (buttonState == LOW)
        {
            if (SWITCH1State == 0)
            {
                digitalToggle(LED_BUILTIN);
                digitalWrite(RELAY1,HIGH);
                digitalWrite(RELAY2,HIGH);
                delay(30);
                digitalWrite(RELAY1,LOW);
                digitalWrite(RELAY2,LOW);
                delay(30);


                SWITCH1State = 1;
            }
            else if (SWITCH1State == 1)
            {

                digitalToggle(LED_BUILTIN);
                digitalWrite(RELAY1,HIGH);
                digitalWrite(RELAY2,HIGH);
                delay(30);
                digitalWrite(RELAY1,LOW);
                digitalWrite(RELAY2,LOW);
                delay(30);
                SWITCH1State = 0;
            }
        }
        // if (SWITCH1State == 0)
        // {
        //     digitalToggle(LED_BUILTIN);
        //     digitalWrite(RELAY1,HIGH);
        //     digitalWrite(RELAY2,HIGH);
        //     delay(30);
        //     digitalWrite(RELAY1,LOW);
        //     digitalWrite(RELAY2,LOW);
        //     delay(30);


        //     SWITCH1State = 1;
        // }
        // else if (SWITCH1State == 1)
        // {

        //     digitalToggle(LED_BUILTIN);
        //     digitalWrite(RELAY1,HIGH);
        //     digitalWrite(RELAY2,HIGH);
        //     delay(30);
        //     digitalWrite(RELAY1,LOW);
        //     digitalWrite(RELAY2,LOW);
        //     delay(30);
        //     SWITCH1State = 0;
        // }

        
    }
    );
}
void setup() 
{
    Serial.begin(115200);
    buttonInit();
    

}

void loop() 
{
    button.tick();
    buttonState = digitalRead(TOSTARTSWITCH);
    Serial.println(buttonState);
}

