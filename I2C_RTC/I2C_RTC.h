/**
 * @file I2C_RTC.h
 *
 * @author ClefaMedia
 *
 * @version 1.0
 *
 * @copyright
 * Copyright (C) ClefaMedia 2021. 
 * All Rights MIT Licensed.
 *
 * @brief This library was created to connect a Real Time Clock
 * 
 * The I2C-Master library from Peter Fleury is used for the I2C-connection.
 */

#ifndef _I2C_RTC_H                  // Prevents duplicate
#define _I2C_RTC_H   1              // forward declarations

#include <avr/io.h>                 // Requires AVR Input/Output
#include <inttypes.h>               // Requires Inttypes

#define I2C_RTC_ADDRESS 0xD0        // full 8-bit address of the I2C-Modul

#define I2C_RTC_WRITE   0x00        // write bit to combine with the address
#define I2C_RTC_READ    0x01        // read bit to combine with the address

/** ===================================================
 * @brief function to initialize the RTC module
 * 
 * Need to be called only once
 * 
 * The I2C-Bus must be initialized in the main-file (f.e. 80kHz)
 * with this code: "I2CMasterInit(SCL_CLK)"
 */
void I2c_RTC_init();

void I2C_RTC_setTime(uint8_t sec, uint8_t min, uint8_t hour);
void I2C_RTC_setDate(uint8_t day, uint8_t month, uint8_t year);

#endif                              // End prevent duplicate forward
/* _I2C_RTC_H */                    // declarations block