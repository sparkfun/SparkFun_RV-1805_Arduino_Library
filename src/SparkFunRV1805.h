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

// Test derived class for base class SparkFunIMU
#ifndef __RV1805_H__
#define __RV1805_H__

#include "stdint.h"
#include <Wire.h>
#include <Arduino.h>
#define I2C_MODE 0
#define SPI_MODE 1

#define TWELVE_HOUR_MODE (1<<6)
#define TWELVE_HOUR_PM (1<<5)

#define RV1805_ADDR						0x69
//Register names:
#define RV1805_HUNDREDTHS               0x00
#define RV1805_SECONDS      			0x01
#define RV1805_MINUTES      			0x02
#define RV1805_HOURS        			0x03
#define RV1805_DATE         			0x04
#define RV1805_MONTHS        			0x05
#define RV1805_YEARS        			0x06
#define RV1805_WEEKDAYS      			0x07
#define RV1805_HUNDREDTHS_ALM           0x08
#define RV1805_SECONDS_ALM    			0x09
#define RV1805_MINUTES_ALM     			0x0A
#define RV1805_HOURS_ALM       			0x0B
#define RV1805_DATE_ALM        			0x0C
#define RV1805_MONTHS_ALM      			0x0D
#define RV1805_WEEKDAYS_ALM    			0x0E
#define RV1805_STATUS					0x0F
#define RV1805_CTRL1					0x10
#define RV1805_CTRL2					0x11
#define RV1805_INT_MASK					0x12
#define RV1805_SQW						0x13
#define RV1805_CAL_XT					0x14
#define RV1805_CAL_RC_UP				0x15
#define RV1805_CAL_RC_LO				0x16
#define RV1805_SLP_CTRL					0x17
#define RV1805_CTDWN_TMR_CTRL			0x18
#define RV1805_CTDWN_TMR				0x19
#define RV1805_TMR_INITIAL				0x1A
#define RV1805_WATCHDOG_TMR				0x1B
#define RV1805_OSC_CTRL					0x1C
#define RV1805_OSC_STATUS				0x1D
#define RV1805_CONF_KEY					0x1F
#define RV1805_TRICKLE_CHRG				0x20
#define RV1805_BREF_CTRL				0x21
#define RV1805_CAP_RC					0x26
#define RV1805_IOBATMODE				0x27
#define RV1805_ID						0x28
#define RV1805_ANLG_STAT				0x2F
#define RV1805_OUT_CTRL					0x30
#define RV1805_RAM_EXT					0x3F

#define TIME_ARRAY_LENGTH 8 // Total number of writable values in device
enum time_order {
	TIME_HUNDREDTHS, // 0
	TIME_SECONDS,    // 1
	TIME_MINUTES,    // 2
	TIME_HOURS,      // 3
	TIME_DATE,       // 4
	TIME_MONTH,      // 5
	TIME_YEAR,       // 6
	TIME_DAY,	     // 7
};

class RV1805
{
  public:
	
    RV1805( void );

    boolean begin( TwoWire &wirePort = Wire);

	bool setTime(uint8_t hund, uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year, uint8_t day);
	bool setTime(uint8_t * time, uint8_t len);
	bool setHundredths(uint8_t value);
	bool setSeconds(uint8_t value);
	bool setMinutes(uint8_t value);
	bool setHours(uint8_t value);
	bool setWeekday(uint8_t value);
	bool setDate(uint8_t value);
	bool setMonth(uint8_t value);
	bool setYear(uint8_t value);
	
	bool updateTime();
	
	void printTime();
	void getHundredths();
	void getSeconds();
	void getMinutes();
	void getHours();
	void getWeekday();
	void getDate();
	void getMonth();
	void getYear();	
	
	bool autoTime();
	
	bool setAlarm(uint8_t hund, uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year, uint8_t day);
	bool setAlarm(uint8_t * time, uint8_t len);
	void setAlarmRepeat(byte mode);
	
	void enableTrickleCharge(byte diode = 0b01, byte rOut = 0b01);
	void enableLowPower();
	
	uint8_t BCDtoDEC(uint8_t val);
	uint8_t DECtoBCD(uint8_t val);
	
	bool is12Hour();
	
	//Software reset routine
	void reset( void );
	
private:
	uint8_t _time[TIME_ARRAY_LENGTH];
	TwoWire *_i2cPort;
	
	//The following utilities read and write
    byte readRegister(byte addr);
    void writeRegister(byte addr, byte val);
	bool writeMultipleRegisters(byte addr, byte * values, uint8_t len);
	bool readMultipleRegisters(byte addr, byte * dest, uint8_t len);
	
	bool _pm;
	
byte _sensorVersion = 0;
};



#endif
