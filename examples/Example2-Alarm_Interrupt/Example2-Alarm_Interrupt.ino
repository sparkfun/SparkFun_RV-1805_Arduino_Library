/*
  Getting time from the RV-1805 Real Time Clock
  By: Andy England
  SparkFun Electronics
  Date: 2/22/2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!

  Set an alarm and make the RTC generate an interrupt when the clock time matches the alarm time

  Hardware Connections:
  Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
  Plug the RTC into the shield (any port)
  Open the serial monitor at 115200 baud
*/

#include <SparkFunRV1805.h>

RV1805 rtc;


//Change the following values to change the time you want your alarm to sound
uint8_t hundredthsAlarm = 0;
uint8_t secondsAlarm = 45;
uint8_t minuteAlarm = 5;
uint8_t hourAlarm = 10;
uint8_t dateAlarm = 13;
uint8_t monthAlarm = 7;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("RTC BEGIN");
  if (!rtc.begin()) {
    Serial.println("Something went wrong");
  }
  if (!rtc.autoTime()) {
    Serial.println("Something went wrong autotime");
  }
  rtc.setAlarm(hundredthsAlarm, secondsAlarm, minuteAlarm, hourAlarm, dateAlarm, monthAlarm); //sets the alarm with the values initialized above
/********************************
Mode must be between 0 and 7 to tell when the alarm should be triggered. 
Alarm is triggered when listed characteristics match
0: Disabled
1: Hundredths, seconds, minutes, hours, date and month match (once per year)
2: Hundredths, seconds, minutes, hours and date match (once per month)
3: Hundredths, seconds, minutes, hours and weekday match (once per week)
4: Hundredths, seconds, minutes and hours match (once per day)
5: Hundredths, seconds and minutes match (once per hour)
6: Hundredths and seconds match (once per minute)
7: Depends on hundredthsAlarm (0x08) value.
  0x08: 0x00-0x99 Hundredths match (once per second)
  0x08: 0xF0-0xF9 Once per tenth (10 Hz)
  0x08: 0xFF Once per hundredth (100 Hz)
********************************/
  rtc.setAlarmRepeat(1);//Sets the alarm so it will go off only when every characteristic matches. I have it set to go off July 13, 10:05:45.
  rtc.setInterruptSource(0);
}

void loop() {
  if (rtc.updateTime()) {
      rtc.printTime();
  }
  Serial.println();
  delay(1000);
  
}
