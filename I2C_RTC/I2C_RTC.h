/**
 * @file I2C_RTC.h
 *
 * @author ClefaMedia, Deniel Skopek & Manuel Rathbauer
 *
 * @version 1.0
 *
 * @copyright
 * Copyright (C) ClefaMedia 2021. 
 * All Rights MIT Licensed.
 *
 * @brief This library was created to connect a Real Time Clock in 24h format via I2C
 * 
 * The I2C-Master library from Peter Fleury is used for the I2C-connection.
 */

#ifndef _I2C_RTC_H                      // Prevents duplicate
#define _I2C_RTC_H   1                  // forward declarations

#include <avr/io.h>                     // Requires AVR Input/Output
#include <inttypes.h>                   // Requires Inttypes

#define I2C_RTC_ADDRESS 0xD0            // full 8-bit address of the I2C-Modul

#define I2C_RTC_WRITE   0x00            // write bit to combine with the address
#define I2C_RTC_READ    0x01            // read bit to combine with the address

#define I2C_RTC_ADDRESS_SECONDS 0x00    // RTC address for the second register
#define I2C_RTC_ADDRESS_MINUTES 0x01    // RTC address for the minute register
#define I2C_RTC_ADDRESS_HOUR    0x02    // RTC address for the hour register
#define I2C_RTC_ADDRESS_DAY     0x03    // RTC address for the weekday register
#define I2C_RTC_ADDRESS_DATE    0x04    // RTC address for the date register
#define I2C_RTC_ADDRESS_MONTH   0x05    // RTC address for the month register
#define I2C_RTC_ADDRESS_YEAR    0x06    // RTC address for the year register
#define I2C_RTC_ADDRESS_ControlRegister 0x0E    // RTC address for the control register

/** ===================================================
 * @brief function to initialize the RTC module
 * 
 * Need to be called only once
 * 
 * The I2C-Bus must be initialized in the main-file (f.e. 80kHz)
 * with this code: "I2CMasterInit(SCL_CLK)"
 * 
 * @param sec seconds from 0 to 59
 * @param min minutes from 0 to 59
 * @param hour hours from 0 to 24
 * @param date day from 0 to (27-31)
 * @param month month from 0 to 12
 * @param year years from 0 to 99
 */
void I2C_RTC_setDateTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year);

/** ===================================================
 * @brief function to set the time and timeformate on the RTC
 * 
 * @param sec seconds from 0 to 59
 * @param min minutes from 0 to 59
 * @param hour hours from 0 to 24
 */
void I2C_RTC_setTime(uint8_t sec, uint8_t min, uint8_t hour);

/** ===================================================
 * @brief function to set the date on the RTC
 * 
 * @param date day from 0 to (27-31)
 * @param month month from 0 to 12
 * @param year years from 0 to 99
 */
void I2C_RTC_setDate(uint8_t date, uint8_t month, uint8_t year);


/** ===================================================
 * @brief function to get the current time
 * 
 * @param time char pointer - points to array where the time will be saved (optimal format: hh:mm:ss\0, required length: 9)
 */
void I2C_RTC_readTime(char *time);

/** ===================================================
 * @brief function to enable square wave output on sqw - pin
 * 
 * @param clk_speed 0x00: 1Hz, 0x01: 1.024kHz, 0x02: 4.096kHz, 0x03: 8.192kHz
 */
void I2C_RTC_setSQW(uint8_t clk_speed);

#endif                              // End prevent duplicate forward
/* _I2C_RTC_H */                    // declarations block