/*
  Setting and reading UNIX time from the RV-3028-C7 Real Time Clock
  By: Constantin Koch
  Date: 7/31/2019
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting my work? Give me a star!
  https://github.com/constiko/RV-3028_C7-Arduino_Library

  This example shows how to set the UNIX time on the RTC, and how to read it.
  UNIX Time and Real Time are INDEPENDENT!
  Open the serial monitor at 115200 baud.
*/

#include <RV-3028-C7.h>

RV3028 rtc;

//The below variable controls what the UNIX time will be set to
uint32_t UNIX = 1234567890;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Read/Write UNIX Time - RTC Example");

  Wire.begin();
  if (rtc.begin() == false) {
    Serial.println("Something went wrong, check wiring");
    while (1);
  }
  else
    Serial.println("RTC online!");
}

void loop() {

  //PRINT TIME
  if (rtc.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.print("RTC failed to update");
  } else {
    String currentTime = rtc.stringTimeStamp();
    Serial.println(currentTime + "     \'s\' = set UNIX time (independent from real time)");
    Serial.print("UNIX Time: "); Serial.println(rtc.getUNIX());
    Serial.println();
  }
  delay(1000);

  //SET TIME?
  if (Serial.available()) {
    switch (Serial.read()) {
      case 's':
        if (rtc.setUNIX(UNIX) == false) {
          Serial.println("Something went wrong setting the time");
        }
        break;
    }
  }
}
