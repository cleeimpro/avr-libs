/**
 * @file I2C_LCD_DN.c
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


#include "I2C_LCD_DN.h"
#include "I2C_LCD.h"
#include <util/delay.h>
#include <I2C.h>

void I2C_LCD_DN_init()
{
    I2C_LCD_init(20, 4);        // initialize display with 4 lines and 20 cols
    I2C_LCD_DN_customChars();   // initialize custom chars in the CGRAM
    I2C_LCD_DN_clearColon();    // clears the colon from the screen 
}

void I2C_LCD_DN_customChars()
{
    // create array containing custom char build information
    uint8_t upperBar[] = {0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t lowerBar[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F};
    uint8_t leftBar[] = {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
    uint8_t rightBar[] = {0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03};
    uint8_t bSlash[] = {0x18, 0x18, 0x0C, 0x0C, 0x06, 0x06, 0x03, 0x03};
    uint8_t fSlash[] = {0x03, 0x03, 0x06, 0x06, 0x0C, 0x0C, 0x18, 0x18};
    uint8_t dotRight[] = {0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00};
    uint8_t dotLeft[] = {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00};

    // push custom chars in CGRAM
    I2C_LCD_createChar(UPPER_BAR, upperBar);
    I2C_LCD_createChar(LOWER_BAR, lowerBar);
    I2C_LCD_createChar(LEFT_DOT, dotLeft);
    I2C_LCD_createChar(RIGHT_DOT, dotRight);
    I2C_LCD_createChar(LEFT_BAR, leftBar);
    I2C_LCD_createChar(RIGHT_BAR, rightBar);
    I2C_LCD_createChar(B_SLASH, bSlash);
    I2C_LCD_createChar(F_SLASH, fSlash);
}

void I2C_LCD_DN_write(uint8_t num, uint8_t col)
{
    switch (num)    // print selected number at given column position to the display
    {
    case 0: I2C_LCD_DN_write0(col); break;
    case 1: I2C_LCD_DN_write1(col); break;
    case 2: I2C_LCD_DN_write2(col); break;
    case 3: I2C_LCD_DN_write3(col); break;
    case 4: I2C_LCD_DN_write4(col); break;
    case 5: I2C_LCD_DN_write5(col); break;
    case 6: I2C_LCD_DN_write6(col); break;
    case 7: I2C_LCD_DN_write7(col); break;
    case 8: I2C_LCD_DN_write8(col); break; 
    case 9: I2C_LCD_DN_write9(col); break;
    default:                                    // if number is not between 0-9 print Yen at given position
        I2C_startWait(I2C_LCD_ADDRESS & ~I2C_WRITE);   // start I2C connection to LCD
        I2C_LCD_setCursorWOI2C(col, 1);                     // set cursor at top start position
        // write needed chars in this line
        I2C_LCD_write(B_SLASH);
        I2C_LCD_write(' ');
        I2C_LCD_write(' ');
        I2C_LCD_write(F_SLASH);
        I2C_LCD_setCursorWOI2C(col, 2);                     // set cursor at middle-top start position
        // write needed chars in this line
        I2C_LCD_write(' ');
        I2C_LCD_write(B_SLASH);
        I2C_LCD_write(F_SLASH);
        I2C_LCD_write(' ');
        I2C_LCD_setCursorWOI2C(col, 3);                     // set cursor at middle-bottom start position
        // write needed chars in this line
        I2C_LCD_write(UPPER_BAR);
        I2C_LCD_write(RIGHT_BAR);
        I2C_LCD_write(LEFT_BAR);
        I2C_LCD_write(UPPER_BAR);
        I2C_LCD_setCursorWOI2C(col, 4);                     // set cursor at bottom start position
        // write needed chars in this line
        I2C_LCD_write(UPPER_BAR);
        I2C_LCD_write(RIGHT_BAR);
        I2C_LCD_write(LEFT_BAR);
        I2C_LCD_write(UPPER_BAR);
        I2C_stop();                                    // stop I2C connection
        break;
    }
}

void I2C_LCD_DN_write0(uint8_t col)
{
    I2C_startWait(I2C_LCD_ADDRESS & ~I2C_WRITE);   // start I2C connection to LCD
    I2C_LCD_setCursorWOI2C(col, 1);                     // set cursor at top start position
    // write needed chars in this line
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);                     // set cursor at middle-top start position
    // write needed chars in this line
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 3);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 4);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_stop();                                    // stop I2C connection
}

void I2C_LCD_DN_write1(uint8_t col)
{
    I2C_startWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);                     // set cursor at top start position
    // write needed chars in this line
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);                     // set cursor at middle-top start position
    // write needed chars in this line
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 3);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 4);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2C_stop();
}

void I2C_LCD_DN_write2(uint8_t col)
{
    I2C_startWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);                     // set cursor at top start position
    // write needed chars in this line
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);                     // set cursor at middle-top start position
    // write needed chars in this line
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 3);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_setCursorWOI2C(col, 4);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_stop();
}

void I2C_LCD_DN_write3(uint8_t col)
{
    I2C_startWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);                     // set cursor at top start position
    // write needed chars in this line
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);                     // set cursor at middle-top start position
    // write needed chars in this line
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 3);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 4);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_stop();
}

void I2C_LCD_DN_write4(uint8_t col)
{
    I2C_startWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);                     // set cursor at top start position
    // write needed chars in this line
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_setCursorWOI2C(col, 2);                     // set cursor at middle-top start position
    // write needed chars in this line
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(' ');
    I2C_LCD_setCursorWOI2C(col, 3);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_setCursorWOI2C(col, 4);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(' ');
    I2C_stop();
}

void I2C_LCD_DN_write5(uint8_t col)
{
    I2C_startWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);                     // set cursor at top start position
    // write needed chars in this line
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);                     // set cursor at middle-top start position
    // write needed chars in this line
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_setCursorWOI2C(col, 3);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 4);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_stop();
}

void I2C_LCD_DN_write6(uint8_t col)
{
    I2C_startWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);                     // set cursor at top start position
    // write needed chars in this line
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);                     // set cursor at middle-top start position
    // write needed chars in this line
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_setCursorWOI2C(col, 3);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 4);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_stop();
}

void I2C_LCD_DN_write7(uint8_t col)
{
    I2C_startWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);                     // set cursor at top start position
    // write needed chars in this line
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);                     // set cursor at middle-top start position
    // write needed chars in this line
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 3);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 4);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2C_stop();
}

void I2C_LCD_DN_write8(uint8_t col)
{
    I2C_startWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);                     // set cursor at top start position
    // write needed chars in this line
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);                     // set cursor at middle-top start position
    // write needed chars in this line
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 3);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 4);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_stop();
}

void I2C_LCD_DN_write9(uint8_t col)
{
    I2C_startWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);                     // set cursor at top start position
    // write needed chars in this line
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);                     // set cursor at middle-top start position
    // write needed chars in this line
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 3);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 4);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_stop();
}

void I2C_LCD_DN_printColon()
{
    I2C_startWait(I2C_LCD_ADDRESS & ~I2C_WRITE);

    I2C_LCD_setCursorWOI2C(COLON_COL, 2);
    I2C_LCD_write(RIGHT_DOT);
    I2C_LCD_write(LEFT_DOT);
    I2C_LCD_setCursorWOI2C(COLON_COL, 3);
    I2C_LCD_write(RIGHT_DOT);
    I2C_LCD_write(LEFT_DOT);
    colonState = 1;

    I2C_stop();
}

void I2C_LCD_DN_clearColon()
{
    I2C_startWait(I2C_LCD_ADDRESS & ~I2C_WRITE);

    I2C_LCD_setCursorWOI2C(COLON_COL, 2);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_setCursorWOI2C(COLON_COL, 3);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    colonState = 0;

    I2C_stop();
}

void I2C_LCD_DN_toggleColon()
{
    I2C_startWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    if (colonState)
    {
        I2C_LCD_DN_clearColon();
    }
    else
    {
        I2C_LCD_DN_printColon();
    }
    I2C_stop();
}

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