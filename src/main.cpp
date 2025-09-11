#include <Arduino.h>
#include <queue>
#include "EEPROM.h"

HardwareSerial mySerial1(USART1);
uint8_t State = LOW; // ledState used to set the LED
void setup() 
{
    std::queue<String> q;
    
    mySerial1.begin(115200);
    mySerial1.println("Hello, World!");
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off by making the voltage HIGHf

    EEPROM.begin();


}

void loop() 
{
    if (mySerial1.available() > 0) 
    {
        String incomingByte = mySerial1.readStringUntil('\n');
        if (incomingByte == "open the build in led")
        {
            digitalToggle(LED_BUILTIN);
            State++;
            if (State == 1)
                mySerial1.println("Hello from the stm32duino!");
            else if (State == 2)
            {
                mySerial1.println("Hello from the stm32duino!!!!!!");
                State = 0;
            }    
        }
    }
}

