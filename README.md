RTC RV-3028-C7 Arduino Library
========================================

![Real Time Clock](https://www.mouser.de/images/microcrystal/images/RV-3028-C7_series_t.jpg)

[*Application Manual*](https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf)

The RV-3028-C7 is an extremely precise, extremely low power, highly configurable RTC. Under ideal conditions it runs at approximately 40nA with +/-5ppm per year of deviation (+/- 160 seconds worst case per year).
This library was originally forked from the [Sparkfun RV-1805 library](https://github.com/sparkfun/SparkFun_RV-1805_Arduino_Library), and costumized and enhanced to the RV-3028-C7.

This library allows the user to:

* Set time using hard numbers or the BUILD_TIME from the Arduino compiler
* Read time
* Configure various aspects of the RTC including setting of alarms, trickle charging or power switchover mode

Examples are included to get you started.

Repository Contents
-------------------

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
* **/src** - Source files for the library (.cpp, .h).
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE. 
* **library.properties** - General library properties for the Arduino package manager. 

Documentation
--------------
The library enables the following functions:
<hr>

#### General functions
<hr>

Please call begin() sometime after initializing the I2C interface with Wire.begin().

###### `begin()`
###### `is12Hour()`
###### `isPM()`
###### `set12Hour()`
###### `set24Hour()`

<hr>

#### Set Time functions
<hr>

###### `setTime(sec, min, hour, weekday, date, month, year);`
###### `setSeconds(value)`
###### `setMinutes(value)`
###### `setHours(value)`
###### `setWeekday(value)`
###### `setDate(value)`
###### `setMonth(value)`
###### `setYear(value)`
###### `setToCompilerTime()`

<hr>

#### Get Time functions
<hr>

Please call "updateTime()" before calling one of the other getTime functions.

###### `updateTime()`
###### `getSeconds()`
###### `getMinutes()`
###### `getHours()`
###### `getWeekday()`
###### `getDate()`
###### `getMonth()`
###### `getYear()`
###### `stringDateUSA()`
###### `stringDate()`
###### `stringTime()`
###### `stringTimeStamp()`

<hr>

#### UNIX Time functions
<hr>

Attention: UNIX Time and real time are INDEPENDENT!

###### `setUNIX(value)`
###### `getUNIX()`

<hr>

#### Alarm Interrupt functions
<hr>

###### `enableAlarmInterrupt(min, hour, date_or_weekday, bool setWeekdayAlarm_not_Date, mode)`
###### `disableAlarmInterrupt()`
###### `readAlarmInterruptFlag()`

Set the alarm mode in the following way:  
0: When minutes, hours and weekday/date match (once per weekday/date)  
1: When hours and weekday/date match (once per weekday/date)  
2: When minutes and weekday/date match (once per hour per weekday/date)  
3: When weekday/date match (once per weekday/date)  
4: When hours and minutes match (once per day)  
5: When hours match (once per day)  
6: When minutes match (once per hour)  
7: All disabled – Default value  
If you want to set a weekday alarm (setWeekdayAlarm_not_Date = true), set 'date_or_weekday' from 0 (Sunday) to 6 (Saturday).  
For further information about the alarm mode see [*Application Manual p. 68*](https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=68).

<hr>

#### Trickle charge functions
<hr>

###### `enableTrickleCharge(uint8_t tcr = TCR_11K)`
###### `disableTrickleCharge()`

At "enableTrickleCharge" you can choose the series resistor:  
TCR_1K for 1kOhm  
TCR_3K for 3kOhm  
TCR_6K for 6kOhm  
TCR_11K for 11kOhm  
See [*Application Manual p. 48*](https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=48) for more information.

<hr>

#### Backup Switchover Mode
<hr>

###### `setBackupSwitchoverMode(mode)`

0 = Switchover disabled  
1 = Direct Switching Mode  
2 = Standby Mode  
3 = Level Switching Mode  
See [*Application Manual p. 45*](https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=45) for more information.

License Information
-------------------

This product is _**open source**_! 

Please review the LICENSE.md file for license information. 

If you have any questions or concerns on licensing, please contact constantinkoch@outlook.com.

Distributed as-is; no warranty is given.
