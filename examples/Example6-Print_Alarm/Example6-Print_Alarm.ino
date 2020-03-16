/*
  Prints the alarm date and time from the RV-1805 Real Time Clock
  By: Andy England
  SparkFun Electronics
  Updated by: Adam Garbo
  Date: 3/14/2020
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14642

  This example shows how to print alarm date and time from the RTC.

  Hardware Connections:
    Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
    Plug the RTC into the shield (any port)
    Open the serial monitor at 9600 baud
*/
#include <SparkFun_RV1805.h>

RV1805 rtc;

byte secondsAlarm = 0;
byte minuteAlarm = 59;
byte hourAlarm = 23;
byte dateAlarm = 31;
byte monthAlarm = 12;

void setup() {

  Wire.begin();

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Print RTC Alarm Example");
  if (rtc.begin() == false) {
    Serial.println("Something went wrong, check wiring");
  }
  
  // Use the time from the Arduino compiler (build time) to set the RTC
  // Keep in mind that Arduino does not get the new compiler time every time it compiles. 
  // To ensure the proper time is loaded, open up a fresh version of the IDE and load the sketch.
  if (rtc.setToCompilerTime() == false) {
    Serial.println("Something went wrong setting the time");
  }
  Serial.println("RTC online!");
}

void loop() {

  // Update the time variables from RTC
  if (rtc.updateTime() == false) {
    Serial.print("RTC failed to update");
  }

  // Get the time
  String currentTime = rtc.stringTimeStamp();
  Serial.println(currentTime);

  // Set the alarm with the values initialized above
  rtc.setAlarm(secondsAlarm, minuteAlarm, hourAlarm, dateAlarm, monthAlarm);

  // Print alarm date and time (Note that there is no year alarm register)
  char alarmBuffer[20];
  sprintf(alarmBuffer, "2020-%02d-%02dT%02d:%02d:%02d",
          rtc.getAlarmMonth(),
          rtc.getAlarmDate(),
          rtc.getAlarmHours(),
          rtc.getAlarmMinutes(),
          rtc.getAlarmSeconds());
  Serial.println(alarmBuffer);

  delay(5000);
}
