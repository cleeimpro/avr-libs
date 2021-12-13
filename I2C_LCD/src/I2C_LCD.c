/**
 * @file I2C_LCD.c
 *
 * @author ClefaMedia
 *
 * @version 1.0
 *
 * @copyright
 * Copyright (C) ClefaMedia 2021. 
 * All Rights MIT Licensed.
 *
 * @brief This library was created to connect a Liquid Crystal Display 
 * with a Hitachi HD44780U controller and an I2C-I/O-Expander PCF8574 over I2C.
 * Maximum display dimensions: 1x80, 2x40, 4x20
 * 
 * The I2C-Master library from Peter Fleury is used for the I2C-connection.
 */


#include "I2C_LCD.h"        // requires I2C_LCD
#include <util/delay.h>     // requires Util delay
#include <I2CMaster.h>      // requires I2CMaster (by Peter Fleury)

void I2C_LCD_push(uint8_t i2c_data)
{
    // command with Enable HIGH
    I2CMasterWrite((i2c_data & ~I2C_LCD_BL) | I2C_LCD_E | (backlight? I2C_LCD_BL:0x00));
    // command with Enable LOW
    I2CMasterWrite((i2c_data & ~I2C_LCD_BL & ~I2C_LCD_E) | (backlight? I2C_LCD_BL:0x00));
    _delay_us(100);     // delay to give processing time
}

void I2C_LCD_command4bit(uint8_t command)
{
    I2C_LCD_push(command & 0xF0);   // send first nipple
    I2C_LCD_push(command << 4);     // send second nipple
}

void I2C_LCD_command8bit(uint8_t command)
{
    I2C_LCD_push(command & 0xF0);   // send byte
}

void I2C_LCD_write(uint8_t c)
{
    I2C_LCD_push((c & 0xF0) | I2C_LCD_RS);  // send first nipple
    I2C_LCD_push((c << 4) | I2C_LCD_RS);    // send second nipple
}

void I2C_LCD_init(uint8_t cols, uint8_t lines)
{
    backlight = I2C_LCD_ON;     // set backlight storrage to on
    _delay_ms(40);              // wait for the display to start
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);   // connect in write mode to display

    // set 8-Bit Mode
    I2C_LCD_command8bit(I2C_LCD_FUNCTIONSET | I2C_LCD_8BITMODE);
    _delay_us(4500);
    I2C_LCD_command8bit(I2C_LCD_FUNCTIONSET | I2C_LCD_8BITMODE);
    _delay_us(150);
    I2C_LCD_command8bit(I2C_LCD_FUNCTIONSET | I2C_LCD_8BITMODE);
    // set 4-Bit mode
    I2C_LCD_command8bit(I2C_LCD_FUNCTIONSET | I2C_LCD_4BITMODE);

    // set lines in displayfunction storrage
    if (lines > 1) {
        displayfunction |= I2C_LCD_2LINE;
    }
    // set line and columns 
    numlines = lines;
    numcols = cols;

    // set offset
    I2C_LCD_setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);

    // set 4-Bit mode & lines & font
    I2C_LCD_command4bit(I2C_LCD_FUNCTIONSET | displayfunction);

    // turn the display on with no cursor or blinking default
    displaycontrol = I2C_LCD_DISPLAY;  
    I2C_LCD_command4bit(I2C_LCD_DISPLAYCONTROL | displaycontrol);

    // display clear
    I2C_LCD_command4bit(I2C_LCD_CLEARDISPLAY);

    // entry mode set
    displaymode = I2C_LCD_ENTRYLEFT | I2C_LCD_ENTRYSHIFTDECREMENT;
    I2C_LCD_command4bit(I2C_LCD_ENTRYMODESET | displaymode);

    I2CMasterStop();    // stop the I2C connection
}

void I2C_LCD_print(char c[])
{
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);   // start I2C connection to LCD
    // send each char 
    for (uint8_t i = 0; c[i] != '\0'; ++i)
    {
        I2C_LCD_write(c[i]);    // send char as data
    }
    I2CMasterStop();    // stop I2C connection
}

void I2C_LCD_printChar(char c)
{
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);   // start I2C connection to LCD
    I2C_LCD_write(c);   // send char as data
    I2CMasterStop();    // stop I2C connection
}

void I2C_LCD_setRowOffsets(uint8_t row1, uint8_t row2, uint8_t row3, uint8_t row4)
{
    row_offsets[0] = row1;  // row 1 start address
    row_offsets[1] = row2;  // row 2 start address
    row_offsets[2] = row3;  // row 3 start address
    row_offsets[3] = row4;  // row 4 start address
}

void I2C_LCD_setCursorWOI2C(uint8_t col, uint8_t row)
{
    col = (col >= numcols) ? numcols : col;         // limit to initialized cols
    row = (row >= numlines) ? numlines : row;       // limit to initialized lines

    I2C_LCD_command4bit(I2C_LCD_SETDDRAMADDR | ((col-1) + row_offsets[row-1])); // send row/col address
}

void I2C_LCD_setCursor(uint8_t col, uint8_t row)
{
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);   // start I2C connection to LCD
    I2C_LCD_setCursorWOI2C(col, row);                   // send row/col to LCD
    I2CMasterStop();                                    // stop I2C connection to LCD
}

void I2C_LCD_cursor(uint8_t state)
{
    displaycontrol &= ~I2C_LCD_CURSOR;                              // clear cursor status
    displaycontrol |= state?(I2C_LCD_CURSOR):0;                     // set cursor status

    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);               // start I2C connection to LCD
    I2C_LCD_command4bit(I2C_LCD_DISPLAYCONTROL | displaycontrol);   // send displycontrols
    I2CMasterStop();                                                // stop I2C connection to LCD
}

void I2C_LCD_blink(uint8_t state)
{
    displaycontrol &= ~I2C_LCD_BLINK;                               // clear cursor blink status
    displaycontrol |= state?(I2C_LCD_BLINK) : 0;                    // set cursor blink status

    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);               // start I2C connection to LCD
    I2C_LCD_command4bit(I2C_LCD_DISPLAYCONTROL | displaycontrol);   // send displaycontrols
    I2CMasterStop();                                                // stop I2C connection to LCD
}

void I2C_LCD_display(uint8_t state)
{
    displaycontrol &= ~ I2C_LCD_DISPLAY;                            // clear display status
    displaycontrol |= state?(I2C_LCD_DISPLAY):0;                    // set display status

    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);               // start I2C connection to LCD
    I2C_LCD_command4bit(I2C_LCD_DISPLAYCONTROL | displaycontrol);   // send displaycontrols
    I2CMasterStop();                                                // stop I2C connection to LCD
}

void I2C_LCD_backlight(uint8_t state)
{
    backlight = state;

    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);               // start I2C connection to LCD
    I2C_LCD_command4bit(I2C_LCD_DISPLAYCONTROL | displaycontrol);   // send displaycontrols
    I2CMasterStop();                                                // stop I2C connection to LCD
}

void I2C_LCD_home(){
    I2C_LCD_setCursor(1,1); // set cursor to home position (row one, line one)
}

void I2C_LCD_clear(){
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);   // start I2C connection to LCD
    I2C_LCD_command4bit(I2C_LCD_CLEARDISPLAY);          // send displayclear command
    I2CMasterStop();                                    // stop I2C connection to LCD
}

// These commands scroll the display without changing the RAM
void I2C_LCD_scrollDisplayLeft() {
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);   // start I2C connection to LCD
    I2C_LCD_command4bit(I2C_LCD_CURSORSHIFT | I2C_LCD_DISPLAYMOVE | I2C_LCD_MOVELEFT);  // send scroll left command
    I2CMasterStop();    // stop I2C connection to LCD
}

void I2C_LCD_scrollDisplayRight() {
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);   // start I2C connection to LCD
    I2C_LCD_command4bit(I2C_LCD_CURSORSHIFT | I2C_LCD_DISPLAYMOVE | I2C_LCD_MOVERIGHT); // send scroll right command
    I2CMasterStop();    // stop I2C connection to LCD
}

// This is for text that flows Left to Right
void I2C_LCD_leftToRight() {
    displaymode |= I2C_LCD_ENTRYLEFT;   // set displaymode to left entry

    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);   // start I2C connection to LCD
    I2C_LCD_command4bit(I2C_LCD_ENTRYMODESET | displaymode);    // send entrymode command
    I2CMasterStop();    // stop I2C connection to LCD
}

// This is for text that flows Right to Left
void I2C_LCD_rightToLeft() {
    displaymode &= ~I2C_LCD_ENTRYLEFT;  // set displaymode to right entry

    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);   // start I2C connection to LCD
    I2C_LCD_command4bit(I2C_LCD_ENTRYMODESET | displaymode);    // send entrymode command
    I2CMasterStop();    // stop I2C connection to LCD
}

void I2C_LCD_cursorFixPosition(uint8_t state) {
    displaymode &= ~ I2C_LCD_ENTRYSHIFTINCREMENT;               // clear entry shift mode
    displaymode |= state? I2C_LCD_ENTRYSHIFTINCREMENT:0;        // set displaymode to entry shift - if state == true

    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);           // start I2C connection to LCD
    I2C_LCD_command4bit(I2C_LCD_ENTRYMODESET | displaymode);    // send fix cursor command
    I2CMasterStop();    // stop I2C connection to LCD
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void I2C_LCD_createChar(uint8_t location, uint8_t charmap[]) {
    location &= 0x7;    // limit location to 4 bit (8 locations)
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);               // start I2C connection to LCD
    I2C_LCD_command4bit(I2C_LCD_SETCGRAMADDR | (location << 3));    // send set CGram + ram address
    for (uint8_t i=0; i<8; i++) {           // loop though the character lines
        I2C_LCD_write(charmap[i] & 0x1F);   // mask each line to 5 bit 
    }
    I2CMasterStop();    // stop I2C connection to LCD
}

/**
 * TERMS OF USE: MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */