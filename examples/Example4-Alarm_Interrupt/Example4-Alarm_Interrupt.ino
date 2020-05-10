/*
  Setting alarm interrupts at RV-3028-C7 Real Time Clock
  By: Constantin Koch
  Date: 7/31/2019
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting my work? Give me a star!
  https://github.com/constiko/RV-3028_C7-Arduino_Library

  This example shows how to set alarm interrupts at RV-3028-C7 Real Time Clock.
  Open the serial monitor at 115200 baud
*/

#include <RV-3028-C7.h>

RV3028 rtc;

//The below variables control what the date will be set to
int sec = 45;
int minute = 59;
int hour = 19;
int day = 5;
int date = 2;
int month = 8;
int year = 2019;

//The below variables control what the alarm will be set to
int alm_minute = 0;
int alm_hour = 20;
int alm_date_or_weekday = 2;
bool alm_isweekday = false;
uint8_t alm_mode = 0;
/*********************************
  Set the alarm mode in the following way:
  0: When minutes, hours and weekday/date match (once per weekday/date)
  1: When hours and weekday/date match (once per weekday/date)
  2: When minutes and weekday/date match (once per hour per weekday/date)
  3: When weekday/date match (once per weekday/date)
  4: When hours and minutes match (once per day)
  5: When hours match (once per day)
  6: When minutes match (once per hour)
  7: All disabled – Default value
  If you want to set a weekday alarm (alm_isweekday = true), set 'alm_date_or_weekday' from 0 (Sunday) to 6 (Saturday)
********************************/
void setup() {

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Read/Write Time - RTC Example");

  Wire.begin();
  if (rtc.begin() == false) {
    Serial.println("Something went wrong, check wiring");
    while (1);
  }
  else
    Serial.println("RTC online!");
  delay(1000);

  //Enable alarm interrupt
  rtc.enableAlarmInterrupt(alm_minute, alm_hour, alm_date_or_weekday, alm_isweekday, alm_mode);
  //rtc.disableAlarmInterrupt();  //Only disables the interrupt (not the alarm flag)
}

void loop() {

  //PRINT TIME
  if (rtc.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.print("RTC failed to update");
  } else {
    String currentTime = rtc.stringTimeStamp();
    Serial.println(currentTime + "     \'s\' = set time");
  }
  
  //Read Alarm Flag
  if (rtc.readAlarmInterruptFlag()) {
    Serial.println("ALARM!!!!");
    rtc.clearAlarmInterruptFlag();
    delay(3000);
  }

  //SET TIME???
  if (Serial.available()) {
    switch (Serial.read()) {
      case 's':
        //Use the time from the Arduino compiler (build time) to set the RTC
        //Keep in mind that Arduino does not get the new compiler time every time it compiles. to ensure the proper time is loaded, open up a fresh version of the IDE and load the sketch.
        /*if (rtc.setToCompilerTime() == false) {
          Serial.println("Something went wrong setting the time");
          }*/
        if (rtc.setTime(sec, minute, hour, day, date, month, year) == false) {
          Serial.println("Something went wrong setting the time");
        }
        break;
    }
  }
}
