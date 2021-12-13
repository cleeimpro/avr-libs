/**
 * @file I2C_LCD_DN.h
 *
 * @author ClefaMedia
 *
 * @version 1.0
 *
 * @copyright
 * Copyright (C) ClefaMedia 2021. 
 * All Rights GNU GLP Licensed.
 *
 * @brief This library was created to display digital clock numbers fullsize on a 4x20 LCD.
 * 
 * The I2C library from clefa is used for the I2C-connection.
 * The I2C-LCD initialization for a 4x20 LCD is already integrated in this Library.
 */


#ifndef _I2C_LCD_DIGITALNUMBER_H        // prevents duplicate
#define _I2C_LCD_DIGITALNUMBER_H   1    // forward declarations


#include "I2C_LCD.h"                    // requires LCD over I2C

// CGRAM addresses of the custom characters
#define FULL_BAR    0xFF
#define UPPER_BAR   0
#define LOWER_BAR   1
#define LEFT_BAR    2
#define RIGHT_BAR   3
#define LEFT_DOT    4
#define RIGHT_DOT   5
#define B_SLASH     6
#define F_SLASH     7

// left column of the colon
#define COLON_COL   10

/** ===================================================
 * @brief function to initialize the display,
 * create the custom chars and
 * clear the colon.
 */
void I2C_LCD_DN_init();

/** ===================================================
 * @brief function to write all needed 
 * custom chars to the CGRAM of the LCD.
 */
void I2C_LCD_DN_customChars();

/** ===================================================
 * @brief function to write specific number to the LCD
 * 
 * @param num which number
 * @param col left column of number
 */
void I2C_LCD_DN_write(uint8_t num, uint8_t col);

/** ===================================================
 * @brief function to write a ZERO 
 * with 4x4 fields to the LCD
 * 
 * @param col left column of number
 */
void I2C_LCD_DN_write0(uint8_t col);

/** ===================================================
 * @brief function to write a ONE
 * with 4x4 fields to the LCD
 * 
 * @param col left column of number
 */
void I2C_LCD_DN_write1(uint8_t col);

/** ===================================================
 * @brief function to write a TWO 
 * with 4x4 fields to the LCD
 * 
 * @param col left column of number
 */
void I2C_LCD_DN_write2(uint8_t col);

/** ===================================================
 * @brief function to write a THREE
 * with 4x4 fields to the LCD
 * 
 * @param col left column of number
 */
void I2C_LCD_DN_write3(uint8_t col);

/** ===================================================
 * @brief function to write a FOUR
 * with 4x4 fields to the LCD
 * 
 * @param col left column of number
 */
void I2C_LCD_DN_write4(uint8_t col);

/** ===================================================
 * @brief function to write a FIVE
 * with 4x4 fields to the LCD
 * 
 * @param col left column of number
 */
void I2C_LCD_DN_write5(uint8_t col);

/** ===================================================
 * @brief function to write a SIX
 * with 4x4 fields to the LCD
 * 
 * @param col left column of number
 */
void I2C_LCD_DN_write6(uint8_t col);

/** ===================================================
 * @brief function to write a SEVEN
 * with 4x4 fields to the LCD
 * 
 * @param col left column of number
 */
void I2C_LCD_DN_write7(uint8_t col);

/** ===================================================
 * @brief function to write a EIGHT
 * with 4x4 fields to the LCD
 * 
 * @param col left column of number
 */
void I2C_LCD_DN_write8(uint8_t col);

/** ===================================================
 * @brief function to write a NINE
 * with 4x4 fields to the LCD
 * 
 * @param col left column of number
 */
void I2C_LCD_DN_write9(uint8_t col);

/** ===================================================
 * @brief function to print a colon over 
 * two columns to the LCD
 */
void I2C_LCD_DN_printColon();

/** ===================================================
 * @brief function to clear the colon on the LCD
 */
void I2C_LCD_DN_clearColon();

/** ===================================================
 * @brief function to toggle the status from the 
 * colon on the LCD.
 */
void I2C_LCD_DN_toggleColon();

/** @brief variable to store the state of the colon */
uint8_t colonState;

#endif                               // end prevent duplicate forward
/* _I2C_LCD_H */                     // declarations block

/**
 * This file is part of I2C_LCD_DN Library
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */