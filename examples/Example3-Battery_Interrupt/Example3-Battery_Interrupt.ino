#include <SparkFunRV1805.h>

RV1805 rtc;

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
  rtc.setAlarmRepeat(7);
  rtc.setInterruptSource(0);
}

void loop() {
  if (rtc.updateTime()) {
      rtc.printTime();
  }
  Serial.println();
  delay(1000);
  
}
