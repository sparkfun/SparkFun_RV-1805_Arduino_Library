/*
  Prints the UNIX Epoch time from the RV-1805 Real Time Clock
  By: Andy England
  SparkFun Electronics
  Updated by: Adam Garbo
  Date: 3/14/2020
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14642

  This example shows to print the UNIX Epoch time from the RTC.

  Hardware Connections:
    Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
    Plug the RTC into the shield (any port)
    Open the serial monitor at 9600 baud
*/

#include <SparkFun_RV1805.h>

RV1805 rtc;

void setup() {

  Wire.begin();

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Print UNIX Epoch Time Example");
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

  // Get the UNIX Epoch time
  unsigned long unixtime = rtc.getEpoch();
  Serial.println(unixtime);

  delay(1000);
}
