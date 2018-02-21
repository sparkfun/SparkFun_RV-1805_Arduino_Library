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
}

void loop() {
  if (rtc.updateTime()) {
      rtc.printTime();
  }
/*******************************************
The value of edgeTrigger controls whether or not the interrupt is 
triggered by rising above or falling below the reference voltage.
Different sets of reference voltages are available based on this value.

edgeTrigger = FALSE; Falling Voltage
0: 2.5V
1: 2.1V
2: 1.8V
3: 1.4V

edgeTrigger = TRUE; Rising Voltage
0: 3.0V
1: 2.5V
2: 2.2V
3: 1.6V
*******************************************/
  if(rtc.checkBattery(1, true))
  {
    Serial.print("Battery over 2.5V");
  }
  Serial.println();
  delay(1000);
  
}
