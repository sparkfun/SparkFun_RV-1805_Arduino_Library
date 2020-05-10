/*
  Trickle Charge Configuration of RV-3028-C7 Real Time Clock
  By: Constantin Koch
  Date: 7/31/2019
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting my work? Give me a star!
  https://github.com/constiko/RV-3028_C7-Arduino_Library

  This example shows how to set the Trickle Charge Configuration of RTC RV-3028-C7.
  Open the serial monitor at 115200 baud.
*/

#include <RV-3028-C7.h>

RV3028 rtc;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Trickle Charging - RTC Example");

  Wire.begin();
  if (rtc.begin() == false) {
    Serial.println("Something went wrong, check wiring");
    while (1);
  }
  else
    Serial.println("RTC online!");
  Serial.println();

  //Trickle Charger
  Serial.print("Config EEPROM 0x37 before: ");
  Serial.println(rtc.readConfigEEPROM_RAMmirror(0x37));

  rtc.enableTrickleCharge(0);   //series resistor 3kOhm
  //rtc.enableTrickleCharge(1); //series resistor 5kOhm
  //rtc.enableTrickleCharge(2); //series resistor 9kOhm
  //rtc.enableTrickleCharge(3); //series resistor 15kOhm
  //rtc.disableTrickleCharge(); //Trickle Charger disabled

  Serial.print("Config EEPROM 0x37 after: ");
  Serial.println(rtc.readConfigEEPROM_RAMmirror(0x37));

  //For more information see https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=48
}

void loop() {

}
