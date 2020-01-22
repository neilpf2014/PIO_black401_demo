#include <Arduino.h>
#include <PushButton.h>

unsigned long pMills = 0;
unsigned long cMills = 0;
unsigned long pMills2 = 0;
unsigned long cTime1;
unsigned long cTime2;
uint8_t LEDstate = 1;
PushButton Btn1(PA0,2);
uint8_t cycCount;

// Toggle state of onboard led
uint8_t TogLED(uint8_t state)
{
  uint8_t rState;
  if (state > 0)
  {
    digitalWrite(LED_BUILTIN, LOW); 
    rState = 0;
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH);
    rState = 1;
  }
  return rState;
}

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  Serial.begin(115200);
  Serial.println("started");
  LEDstate = 1;
  cTime1 = 500;
  cTime2 = 1000;
}

// the loop function runs over and over again forever
void loop() 
{
  Btn1.update();
  cMills = millis();
  if(cMills - pMills > cTime1)
  {
    pMills = cMills;
    if(Btn1.isCycled())
      {
        if (cTime2 > 10)
          cTime2 = (cTime2 / 2);
        if (cTime2 < 10)
          cTime2 = 1000;
        Serial.println("Button pressed ");
        Serial.print(cMills/1000);
        Serial.println("sec since start");
        cycCount = Btn1.cycleCount();
      }
  }
  if(cMills - pMills2 > cTime2)
  {
    pMills2 = cMills;
    LEDstate = TogLED(LEDstate);
  }
}