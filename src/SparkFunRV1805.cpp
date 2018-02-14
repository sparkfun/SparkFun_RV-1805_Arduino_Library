/******************************************************************************
SparkFunRV1805.h
RV1805 Arduino Library
Andy England @ SparkFun Electronics
February 5, 2018
https://github.com/sparkfun/Qwiic_RTC_Module

Resources:
Uses Wire.h for i2c operation
Uses SPI.h for SPI operation

Development environment specifics:
Arduino IDE 1.6.4

This code is released under the [MIT License](http://opensource.org/licenses/MIT).
Please review the LICENSE.md file included with this example. If you have any questions
or concerns with licensing, please contact techsupport@sparkfun.com.
Distributed as-is; no warranty is given.
******************************************************************************/

#include "SparkFunRV1805.h"
#include "stdint.h"

#include "Wire.h"

//****************************************************************************//
//
//  Settings and configuration
//
//****************************************************************************//

// Parse the __DATE__ predefined macro to generate date defaults:
// __Date__ Format: MMM DD YYYY (First D may be a space if <10)
// <MONTH>
#define BUILD_MONTH_JAN ((__DATE__[0] == 'J') && (__DATE__[1] == 'a')) ? 1 : 0
#define BUILD_MONTH_FEB (__DATE__[0] == 'F') ? 2 : 0
#define BUILD_MONTH_MAR ((__DATE__[0] == 'M') && (__DATE__[1] == 'a') && (__DATE__[2] == 'r')) ? 3 : 0
#define BUILD_MONTH_APR ((__DATE__[0] == 'A') && (__DATE__[1] == 'p')) ? 4 : 0
#define BUILD_MONTH_MAY ((__DATE__[0] == 'M') && (__DATE__[1] == 'a') && (__DATE__[2] == 'y')) ? 5 : 0
#define BUILD_MONTH_JUN ((__DATE__[0] == 'J') && (__DATE__[1] == 'u') && (__DATE__[2] == 'n')) ? 6 : 0
#define BUILD_MONTH_JUL ((__DATE__[0] == 'J') && (__DATE__[1] == 'u') && (__DATE__[2] == 'l')) ? 7 : 0
#define BUILD_MONTH_AUG ((__DATE__[0] == 'A') && (__DATE__[1] == 'u')) ? 8 : 0
#define BUILD_MONTH_SEP (__DATE__[0] == 'S') ? 9 : 0
#define BUILD_MONTH_OCT (__DATE__[0] == 'O') ? 10 : 0
#define BUILD_MONTH_NOV (__DATE__[0] == 'N') ? 11 : 0
#define BUILD_MONTH_DEC (__DATE__[0] == 'D') ? 12 : 0
#define BUILD_MONTH BUILD_MONTH_JAN | BUILD_MONTH_FEB | BUILD_MONTH_MAR | \
BUILD_MONTH_APR | BUILD_MONTH_MAY | BUILD_MONTH_JUN | \
BUILD_MONTH_JUL | BUILD_MONTH_AUG | BUILD_MONTH_SEP | \
BUILD_MONTH_OCT | BUILD_MONTH_NOV | BUILD_MONTH_DEC
// <DATE>
#define BUILD_DATE_0 ((__DATE__[4] == ' ') ? 0 : (__DATE__[4] - 0x30))
#define BUILD_DATE_1 (__DATE__[5] - 0x30)
#define BUILD_DATE ((BUILD_DATE_0 * 10) + BUILD_DATE_1)
// <YEAR>
#define BUILD_YEAR (((__DATE__[7] - 0x30) * 1000) + ((__DATE__[8] - 0x30) * 100) + \
((__DATE__[9] - 0x30) * 10)  + ((__DATE__[10] - 0x30) * 1))

// Parse the __TIME__ predefined macro to generate time defaults:
// __TIME__ Format: HH:MM:SS (First number of each is padded by 0 if <10)
// <HOUR>
#define BUILD_HOUR_0 ((__TIME__[0] == ' ') ? 0 : (__TIME__[0] - 0x30))
#define BUILD_HOUR_1 (__TIME__[1] - 0x30)
#define BUILD_HOUR ((BUILD_HOUR_0 * 10) + BUILD_HOUR_1)
// <MINUTE>
#define BUILD_MINUTE_0 ((__TIME__[3] == ' ') ? 0 : (__TIME__[3] - 0x30))
#define BUILD_MINUTE_1 (__TIME__[4] - 0x30)
#define BUILD_MINUTE ((BUILD_MINUTE_0 * 10) + BUILD_MINUTE_1)
// <SECOND>
#define BUILD_SECOND_0 ((__TIME__[6] == ' ') ? 0 : (__TIME__[6] - 0x30))
#define BUILD_SECOND_1 (__TIME__[7] - 0x30)
#define BUILD_SECOND ((BUILD_SECOND_0 * 10) + BUILD_SECOND_1)

RV1805::RV1805( void )
{

}

boolean RV1805::begin(TwoWire &wirePort)
{
	_i2cPort = &wirePort;
	_i2cPort->begin();
	Serial.begin(115200);
	_sensorVersion = readRegister(RV1805_ID);
	if (_sensorVersion != 0x18) //HW version for RV1805
	{
		Serial.print("ID (should be 0x18): 0x");
		Serial.println(_sensorVersion, HEX);
	}

	if (_sensorVersion == 0)
	{
		Serial.println("Sensor failed to respond. Check wiring.");
		while (1); //Freeze!
	}

	if (_sensorVersion == 0x18) Serial.println("RV-1805 online!");
	return (true);
}

//Strictly resets.  Run .begin() afterwards
void RV1805::reset( void )
{
	writeRegister(RV1805_CONF_KEY, 0x3C);	
}

void RV1805::printTime()
{
	Serial.print(BCDtoDEC(_time[TIME_MONTH]));
	Serial.print("/");
	Serial.print(BCDtoDEC(_time[TIME_DATE]));
	Serial.print("/");
	Serial.println(BCDtoDEC(_time[TIME_YEAR]));
	Serial.print(BCDtoDEC(_time[TIME_HOURS]));
	Serial.print(":");
	Serial.print(BCDtoDEC(_time[TIME_MINUTES]));
	Serial.print(":");
	Serial.print(BCDtoDEC(_time[TIME_SECONDS]));
	Serial.print(":");
	Serial.println(BCDtoDEC(_time[TIME_HUNDREDTHS]));
}

bool RV1805::setTime(uint8_t hund, uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year, uint8_t day)
{
	_time[TIME_HUNDREDTHS] = DECtoBCD(hund);
	_time[TIME_SECONDS] = DECtoBCD(sec);
	_time[TIME_MINUTES] = DECtoBCD(min);
	_time[TIME_HOURS] = DECtoBCD(hour);
	_time[TIME_DATE] = DECtoBCD(date);
	_time[TIME_MONTH] = DECtoBCD(month);
	_time[TIME_YEAR] = DECtoBCD(year);
	_time[TIME_DAY] = DECtoBCD(day);
		
	return setTime(_time, TIME_ARRAY_LENGTH);
}

// setTime -- Set time and date/day registers of RV1805 (using data array)
bool RV1805::setTime(uint8_t * time, uint8_t len)
{
	if (len != TIME_ARRAY_LENGTH)
	return false;
	
	return writeMultipleRegisters(RV1805_HUNDREDTHS, time, TIME_ARRAY_LENGTH);
}

bool RV1805::setHundredths(uint8_t value)
{
	_time[TIME_HUNDREDTHS] = DECtoBCD(value);
	return setTime(_time, TIME_ARRAY_LENGTH);
}

bool RV1805::setSeconds(uint8_t value)
{
	_time[TIME_SECONDS] = DECtoBCD(value);
	return setTime(_time, TIME_ARRAY_LENGTH);
}

bool RV1805::setMinutes(uint8_t value)
{
	_time[TIME_MINUTES] = DECtoBCD(value);
	return setTime(_time, TIME_ARRAY_LENGTH);
}

bool RV1805::setHours(uint8_t value)
{
	_time[TIME_HOURS] = DECtoBCD(value);
	return setTime(_time, TIME_ARRAY_LENGTH);
}

bool RV1805::setDate(uint8_t value)
{
	_time[TIME_DATE] = DECtoBCD(value);
	return setTime(_time, TIME_ARRAY_LENGTH);
}

bool RV1805::setMonth(uint8_t value)
{
	_time[TIME_MONTH] = DECtoBCD(value);
	return setTime(_time, TIME_ARRAY_LENGTH);
}

bool RV1805::setYear(uint8_t value)
{
	_time[TIME_YEAR] = DECtoBCD(value);
	return setTime(_time, TIME_ARRAY_LENGTH);
}

bool RV1805::setWeekday(uint8_t value)
{
	_time[TIME_DAY] = DECtoBCD(value);
	return setTime(_time, TIME_ARRAY_LENGTH);
}

bool RV1805::updateTime()
{
	uint8_t rtcReads[8];
	
	if (readMultipleRegisters(RV1805_HUNDREDTHS, rtcReads, 8))
	{
		for (int i=0; i<TIME_ARRAY_LENGTH; i++)
		{
			_time[i] = rtcReads[i];
		}
		
		_time[TIME_SECONDS] &= 0b01111111; // Mask out CH bit
		
		if (_time[TIME_HOURS] & TWELVE_HOUR_MODE)
		{
			if (_time[TIME_HOURS] & TWELVE_HOUR_PM)
				_pm = true;
			else
				_pm = false;
			_time[TIME_HOURS] &= 0x1F; // Mask out 24-hour bit from hours
		}
		
		return true;
	}
	else
	{
		return false;
	}
}

bool RV1805::autoTime()
{
	_time[TIME_SECONDS] = DECtoBCD(BUILD_SECOND);
	_time[TIME_MINUTES] = DECtoBCD(BUILD_MINUTE);
	_time[TIME_HOURS] = BUILD_HOUR;
	if (is12Hour())
	{
		uint8_t pmBit = 0;
		if (_time[TIME_HOURS] <= 11)
		{
			if (_time[TIME_HOURS] == 0)
			_time[TIME_HOURS] = 12;
		}
		else
		{
			pmBit = TWELVE_HOUR_PM;
			if (_time[TIME_HOURS] >= 13)
			_time[TIME_HOURS] -= 12;
		}
		DECtoBCD(_time[TIME_HOURS]);
		_time[TIME_HOURS] |= pmBit;
		_time[TIME_HOURS] |= TWELVE_HOUR_MODE;
	}
	else
	{
		DECtoBCD(_time[TIME_HOURS]);
	}
	
	_time[TIME_MONTH] = DECtoBCD(BUILD_MONTH);
	_time[TIME_DATE] = DECtoBCD(BUILD_DATE);
	_time[TIME_YEAR] = DECtoBCD(BUILD_YEAR - 2000); //! Not Y2K (or Y2.1K)-proof :\
	
	// Calculate weekday (from here: http://stackoverflow.com/a/21235587)
	// 0 = Sunday, 6 = Saturday
	int d = BUILD_DATE;
	int m = BUILD_MONTH;
	int y = BUILD_YEAR;
	int weekday = (d+=m<3?y--:y-2,23*m/9+d+4+y/4-y/100+y/400)%7 + 1;
	_time[TIME_DAY] = DECtoBCD(weekday);
	
	return setTime(_time, TIME_ARRAY_LENGTH);
}

bool RV1805::setAlarm(uint8_t hund, uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year, uint8_t day)
{
	_time[TIME_HUNDREDTHS] = DECtoBCD(hund);
	_time[TIME_SECONDS] = DECtoBCD(sec);
	_time[TIME_MINUTES] = DECtoBCD(min);
	_time[TIME_HOURS] = DECtoBCD(hour);
	_time[TIME_DATE] = DECtoBCD(date);
	_time[TIME_MONTH] = DECtoBCD(month);
	_time[TIME_YEAR] = DECtoBCD(year);
	_time[TIME_DAY] = DECtoBCD(day);
	
	return setAlarm(_time, TIME_ARRAY_LENGTH);
}

bool RV1805::setAlarm(uint8_t * time, uint8_t len)
{
	if (len != TIME_ARRAY_LENGTH)
	return false;
	
	return writeMultipleRegisters(RV1805_HUNDREDTHS_ALM, time, TIME_ARRAY_LENGTH);
}

/********************************
Mode must be between 0 and 7 to tell when the alarm should be triggered. 
Alarm is triggered when listed characteristics match
0: Disabled
1: Hundredths, seconds, minutes, hours, date and month match (once per year)
2: Hundredths, seconds, minutes, hours and date match (once per month)3: Hundredths, seconds, minutes, hours and weekday match (once per week)
4: Hundredths, seconds, minutes and hours match (once per day)
5: Hundredths, seconds and minutes match (once per hour)
6: Hundredths and seconds match (once per minute)
7: Depends on RV1805_HUNDREDTHS_ALM (0x08) value.
	0x08: 0x00-0x99 Hundredths match (once per second)
	0x08: 0xF0-0xF9 Once per tenth (10 Hz)
	0x08: 0xFF Once per hundredth (100 Hz)
********************************/

void RV1805::setAlarmRepeat(byte mode)
{
	if (mode > 0b111) mode = 0b111;
	
	byte value = readRegister(RV1805_CTDWN_TMR_CTRL);
	value &= 0b11100011;
	value |= (mode << 2);
	writeRegister(RV1805_CTDWN_TMR_CTRL, value);
}

void RV1805::enableTrickleCharge(byte diode, byte rOut)
{
	writeRegister(RV1805_CONF_KEY, 0x9D);
	byte value = readRegister(RV1805_TRICKLE_CHRG);
	value &= 0b00000000;
	value |= 0b10100000;
	value |= (diode << 2);
	value |= rOut;
	writeRegister(RV1805_TRICKLE_CHRG, value);
}

uint8_t RV1805::BCDtoDEC(uint8_t val)
{
	return ( ( val / 0x10) * 10 ) + ( val % 0x10 );
}

// BCDtoDEC -- convert decimal to binary-coded decimal (BCD)
uint8_t RV1805::DECtoBCD(uint8_t val)
{
	return ( ( val / 10 ) * 0x10 ) + ( val % 10 );
}

bool RV1805::is12Hour()
{
	uint8_t hourRegister = readRegister(RV1805_CTRL1);
	
	return hourRegister & TWELVE_HOUR_MODE;
}

byte RV1805::readRegister(byte addr)
{
	_i2cPort->beginTransmission(RV1805_ADDR);
	_i2cPort->write(addr);
	_i2cPort->endTransmission();

	_i2cPort->requestFrom(RV1805_ADDR, 1);
	if (_i2cPort->available()) {
		return (_i2cPort->read());
	}
	else {
		Serial.println("I2C Error");
		return (0xFF); //Error
	}
}

void RV1805::writeRegister(byte addr, byte val)
{
	_i2cPort->beginTransmission(RV1805_ADDR);
	_i2cPort->write(addr);
	_i2cPort->write(val);
	_i2cPort->endTransmission();
}

bool RV1805::writeMultipleRegisters(byte addr, byte * values, uint8_t len)
{
	_i2cPort->beginTransmission(RV1805_ADDR);
	_i2cPort->write(addr);
	for (int i = 0; i < len; i++)
	{
		_i2cPort->write(values[i]);
	}
	_i2cPort->endTransmission();
	return true;
}

bool RV1805::readMultipleRegisters(byte addr, byte * dest, uint8_t len)
{
	_i2cPort->beginTransmission(RV1805_ADDR);
	_i2cPort->write(addr);
	_i2cPort->endTransmission();

	_i2cPort->requestFrom(RV1805_ADDR, len);
	for (int i = 0; i < len; i++)
	{
		dest[i] = _i2cPort->read();
	}
	
	return true;
}
