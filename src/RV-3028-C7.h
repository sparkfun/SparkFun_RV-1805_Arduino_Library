/******************************************************************************
RV-3028-C7.h
RV-3028-C7 Arduino Library
Constantin Koch
July 25, 2019
https://github.com/constiko/RV-3028_C7-Arduino_Library

Resources:
Uses Wire.h for I2C operation
Uses SPI.h for SPI operation

Development environment specifics:
Arduino IDE 1.6.4

This code is released under the [MIT License](http://opensource.org/licenses/MIT).
Please review the LICENSE.md file included with this example. If you have any questions 
or concerns with licensing, please contact constantinkoch@outlook.com.
Distributed as-is; no warranty is given.
******************************************************************************/

#pragma once

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

//The 7-bit I2C address of the RV3028
#define RV3028_ADDR						(uint8_t)0x52//###

//The upper part of the part number is always 0x18
//#define RV3028_PART_NUMBER_UPPER		0x18		//at RV-3028, Register 0x28 (ID) is not always constant

//Possible CONFKEY Values
#define RV3028_CONF_RST					0x3C //value written to Configuration Key for reset
#define RV3028_CONF_OSC					0xA1 //value written to Configuration Key for oscillator control register write enable
#define RV3028_CONF_WRT					0x9D //value written to Configuration Key to enable write of trickle charge, BREF, CAPRC, IO Batmode, and Output Control Registers

//Bits in Control1 Register
#define CTRL1_STOP	7
#define CTRL1_12_24	6
#define CTRL1_PSWB	5
#define CTRL1_ARST						1 << 2 //Enables reset of interrupt flags in status register 

//Bits in Hours register
#define HOURS_AM_PM						5

//Trickle Charge Control
#define TRICKLE_CHARGER_TCS_OFFSET				4
#define TRICKLE_CHARGER_DIODE_OFFSET			2
#define TRICKLE_CHARGER_ROUT_OFFSET			0
#define TRICKLE_ENABLE					0b1010
#define TRICKLE_DISABLE					0b0000
#define DIODE_DISABLE 					0b00
#define DIODE_0_3V						0b01
#define DIODE_0_6V						0b10
#define ROUT_DISABLE					0b00
#define ROUT_3K							0b01
#define ROUT_6K							0b10
#define ROUT_11K						0b11

//Interrupt Enable Bits
#define INTERRUPT_BLIE	4
#define INTERRUPT_TIE	3
#define INTERRUPT_AIE	2
#define INTERRUPT_EIE	1


//PSW Pin Function Selection Bits
#define PSWS_OFFSET     2
#define PSWS_INV_IRQ    0b000
#define PSWS_SQW        0b001
#define PSWS_INV_AIRQ   0b011
#define PSWS_TIRQ       0b100
#define PSWS_INV_TIRQ   0b101
#define PSWS_SLEEP      0b110
#define PSWS_STATIC     0b111

//Countdown Timer Control
#define COUNTDOWN_SECONDS		0b10
#define COUNTDOWN_MINUTES		0b11
#define CTDWN_TMR_TE_OFFSET		7
#define CTDWN_TMR_TM_OFFSET		6
#define CTDWN_TMR_TRPT_OFFSET	5


//Status Bits
#define STATUS_CB	7
#define STATUS_BAT 6
#define STATUS_WDF 5
#define STATUS_BLF 4
#define STATUS_TF 3
#define STATUS_AF 2
#define STATUS_EVF 1

//Reference Voltage
#define TWO_FIVE						0x70
#define TWO_ONE							0xB0
#define ONE_EIGHT						0xD0
#define ONE_FOUR						0xF0

//REGISTERS
//Clock registers
#define RV3028_SECONDS      			0x00//###
#define RV3028_MINUTES      			0x01//###
#define RV3028_HOURS        			0x02//###
//Calendar registers
#define RV3028_WEEKDAY					0x03//###
#define RV3028_DATE         			0x04//###
#define RV3028_MONTHS        			0x05//###
#define RV3028_YEARS        			0x06//###

//Alarm registers
#define RV3028_MINUTES_ALM     			0x07//###
#define RV3028_HOURS_ALM       			0x08//###
#define RV3028_DATE_ALM        			0x09//###

//Periodic Countdown Timer registers
#define RV3028_TIMERVAL_0				0x0A//###
#define RV3028_TIMERVAL_1				0x0B//###
#define RV3028_TIMERSTAT_0				0x0C//###
#define RV3028_TIMERSTAT_1				0x0D//###

//Configuration registers
#define RV3028_STATUS					0x0E//###
#define RV3028_CTRL1					0x0F//###
#define RV3028_CTRL2					0x10//###
#define RV3028_GPBITS					0x11//###
#define RV3028_INT_MASK					0x12//###

//Eventcontrol/Timestamp registers
#define RV3028_EVENTCTRL				0x13//###
#define RV3028_COUNT_TS					0x14//###
#define RV3028_SECONDS_TS				0x15//###
#define RV3028_MINUTES_TS				0x16//###
#define RV3028_HOURS_TS					0x17//###
#define RV3028_DATE_TS					0x18//###
#define RV3028_MONTH_TS					0x19//###
#define RV3028_YEAR_TS					0x1A//###

//Unix Time registers
#define RV3028_UNIX_TIME0				0x1B//###
#define RV3028_UNIX_TIME1				0x1C//###
#define RV3028_UNIX_TIME2				0x1D//###
#define RV3028_UNIX_TIME3				0x1E//###

//RAM registers
#define RV3028_USER_RAM1				0x1F//###
#define RV3028_USER_RAM2				0x20//###

//Password registers
#define RV3028_PASSWORD0				0x21//###
#define RV3028_PASSWORD1				0x22//###
#define RV3028_PASSWORD2				0x23//###
#define RV3028_PASSWORD3				0x24//###

//EEPROM Memory Control registers
#define RV3028_EEPROM_ADDR				0x25//###
#define RV3028_EEPROM_DATA				0x26//###
#define RV3028_EEPROM_CMD				0x27//###

//ID register
#define RV3028_ID						0x28//###



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

class RV3028
{
  public:
	
    RV3028( void );

    boolean begin( TwoWire &wirePort = Wire);

	bool setTime(uint8_t hund, uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint16_t year, uint8_t day);
	bool setTime(uint8_t * time, uint8_t len);
	bool setHundredths(uint8_t value);
	bool setSeconds(uint8_t value);
	bool setMinutes(uint8_t value);
	bool setHours(uint8_t value);
	bool setWeekday(uint8_t value);
	bool setDate(uint8_t value);
	bool setMonth(uint8_t value);
	bool setYear(uint8_t value);
	
	bool updateTime(); //Update the local array with the RTC registers
	
	char* stringDateUSA(); //Return date in mm-dd-yyyy
	char* stringDate(); //Return date in dd-mm-yyyy
	char* stringTime(); //Return time hh:mm:ss with AM/PM if in 12 hour mode
	char* stringTimeStamp(); //Return timeStamp in ISO 8601 format yyyy-mm-ddThh:mm:ss
	
	uint8_t getHundredths();
	uint8_t getSeconds();
	uint8_t getMinutes();
	uint8_t getHours();
	uint8_t getWeekday();
	uint8_t getDate();
	uint8_t getMonth();
	uint8_t getYear();	
	
	bool setToCompilerTime(); //Uses the hours, mins, etc from compile time to set RTC
	
	bool is12Hour(); //Returns true if 12hour bit is set
	bool isPM(); //Returns true if is12Hour and PM bit is set
	void set12Hour();
	void set24Hour();
	
	uint8_t status(); //Returns the status byte
	
	bool setAlarm(uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month);
	bool setAlarm(uint8_t * time, uint8_t len);
	void setAlarmMode(uint8_t mode); //0 to 7, alarm goes off with match of second, minute, hour, etc
 
 	void enableSleep();
    void setPowerSwitchFunction(uint8_t function);
    void setPowerSwitchLock(bool lock);
    void setStaticPowerSwitchOutput(bool psw); // PSW pin must be unlocked using setPSWLock(false) to enable static PSW output
	
	void setCountdownTimer(uint8_t duration, uint8_t unit, bool repeat = true, bool pulse = true);

	void enableTrickleCharge(uint8_t diode = DIODE_0_3V, uint8_t rOut = ROUT_3K); //Diode default 0.3V, rOut default 3k
	void disableTrickleCharge();
	void enableLowPower();

	void enableInterrupt(uint8_t source); //Enables a given interrupt within Interrupt Enable register
	void disableInterrupt(uint8_t source); //Disables a given interrupt within Interrupt Enable register
	void enableBatteryInterrupt(uint8_t voltage, bool edgeTrigger);
	void enableAlarmInterrupt(); //Use in conjuction with setAlarm and setAlarmMode
	
	void clearInterrupts();
	
	bool checkBattery(uint8_t voltage);
	void setEdgeTrigger(bool edgeTrigger);
	void setReferenceVoltage(uint8_t voltage);
	
	//Values in RTC are stored in Binary Coded Decimal. These functions convert to/from Decimal
	uint8_t BCDtoDEC(uint8_t val); 
	uint8_t DECtoBCD(uint8_t val);

	void reset(void); //Fully reset RTC to all zeroes
	
    uint8_t readRegister(uint8_t addr);
    bool writeRegister(uint8_t addr, uint8_t val);
	bool readMultipleRegisters(uint8_t addr, uint8_t * dest, uint8_t len);
	bool writeMultipleRegisters(uint8_t addr, uint8_t * values, uint8_t len);

private:
	uint8_t _time[TIME_ARRAY_LENGTH];
	TwoWire *_i2cPort;
};
