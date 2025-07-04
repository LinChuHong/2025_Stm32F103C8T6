#include <Arduino.h>
#include "OneButton.h"
#define RELAY1 PA0
#define RELAY2 PA1
#define SWITCH1 PB12
#define SWITCH1GROUND PB13
OneButton button(SWITCH1, true);

uint8_t SWITCH1State = 0;




void buttonInit()
{
    
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    pinMode(SWITCH1, INPUT_PULLUP);
    pinMode(SWITCH1GROUND, OUTPUT);
    digitalWrite(SWITCH1GROUND, LOW);
    button.attachPress([]() 
    {
        if (SWITCH1State == 0)
        {
            digitalWrite(RELAY1, HIGH);
            delay(30);
            digitalWrite(RELAY1, LOW);
            delay(30);
            SWITCH1State = 1;
        }
        else if (SWITCH1State == 1)
        {
            digitalWrite(RELAY2, HIGH);
            delay(30);
            digitalWrite(RELAY2, LOW);
            delay(30);
            SWITCH1State = 2;
        }
        else if (SWITCH1State == 2) 
        {
            digitalWrite(RELAY1, HIGH);
            digitalWrite(RELAY2, HIGH);
            delay(30);
            digitalWrite(RELAY1, LOW);
            digitalWrite(RELAY2, LOW);
            delay(30);
            SWITCH1State = 0;


        }
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
}

