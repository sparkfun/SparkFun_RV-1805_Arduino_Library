/*
  Getting time from the RV-1805 Real Time Clock
  By: Andy England
  SparkFun Electronics
  Date: 2/22/2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!

  Read the time value from the RV-1805 RTC

  Hardware Connections:
  Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
  Plug the RTC into the shield (any port)
  Open the serial monitor at 115200 baud
*/

#include <SparkFunRV1805.h>

RV1805 rtc;

void setup() {
  Serial.begin(115200);
  delay(1);
  Serial.println("RTC BEGIN");
  if (!rtc.begin()) {
    Serial.println("Something went wrong, check wiring");
  }
  if (!rtc.autoTime()) {
    Serial.println("Something went wrong autotime");
  }
}

void loop() {
  if (rtc.updateTime()) {//updates time variable with time from current registers
      rtc.printTime(); //prints time values
  }
  Serial.println();
  delay(5000);
}
