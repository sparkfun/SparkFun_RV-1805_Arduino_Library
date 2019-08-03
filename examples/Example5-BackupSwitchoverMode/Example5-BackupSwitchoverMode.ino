/*
  Backup Switchover Mode of RV-3028-C7 Real Time Clock
  By: Constantin Koch
  Date: 7/31/2019
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting my work? Give me a star!
  https://github.com/constiko/RV-3028_C7-Arduino_Library

  This example shows how to set the Backup Switchover Mode of RTC RV-3028-C7.
  Open the serial monitor at 115200 baud.
*/

#include <RV-3028-C7.h>

RV3028 rtc;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Backup Switchover Mode - RTC Example");

  Wire.begin();
  if (rtc.begin() == false) {
    Serial.println("Something went wrong, check wiring");
    while (1);
  }
  else
    Serial.println("RTC online!");
  Serial.println();
  
  //Backup Switchover Mode
  Serial.print("Config EEPROM 0x37 before: ");
  Serial.println(rtc.readConfigEEPROM_RAMmirror(0x37));

  rtc.setBackupSwitchoverMode(0);   //Switchover disabled
  //rtc.setBackupSwitchoverMode(1); //Direct Switching Mode
  //rtc.setBackupSwitchoverMode(2); //Standby Mode
  //rtc.setBackupSwitchoverMode(3); //Level Switching Mode (default)

  Serial.print("Config EEPROM 0x37 after: ");
  Serial.println(rtc.readConfigEEPROM_RAMmirror(0x37));
  
  //For more information see https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=43
}

void loop() {

}
