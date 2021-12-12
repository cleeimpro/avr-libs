#include "I2C_LCD.h"
#include <util/delay.h>
#include <I2CMaster.h>

void I2C_LCD_push(uint8_t i2c_data)
{
    // Command with Enable HIGH
    I2CMasterWrite((i2c_data & ~I2C_LCD_BL) | I2C_LCD_E | (I2C_LCD_BL & backlight));
    // Command with Enable LOW
    I2CMasterWrite((i2c_data & ~I2C_LCD_BL & ~I2C_LCD_E) | (I2C_LCD_BL & backlight));
    _delay_us(100);
}

// RS immer LOW
void I2C_LCD_command4bit(uint8_t command)
{
    I2C_LCD_push(command & 0xF0);
    I2C_LCD_push(command << 4);
}

void I2C_LCD_command8bit(uint8_t command)
{
    I2C_LCD_push(command & 0xF0);
}

// RS High
void I2C_LCD_write(uint8_t c)
{
    I2C_LCD_push((c & 0xF0) | I2C_LCD_RS);
    I2C_LCD_push((c << 4) | I2C_LCD_RS);
}

void I2C_LCD_init(uint8_t cols, uint8_t lines)
{
    backlight = I2C_LCD_ON;
    _delay_ms(40);
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);

    // Set 8-Bit Mode
    I2C_LCD_command8bit(I2C_LCD_FUNCTIONSET | I2C_LCD_8BITMODE);
    _delay_us(4500);
    I2C_LCD_command8bit(I2C_LCD_FUNCTIONSET | I2C_LCD_8BITMODE);
    _delay_us(150);
    I2C_LCD_command8bit(I2C_LCD_FUNCTIONSET | I2C_LCD_8BITMODE);
    // Set 4-Bit mode
    I2C_LCD_command8bit(I2C_LCD_FUNCTIONSET | I2C_LCD_4BITMODE);

    if (lines > 1) {
        displayfunction |= I2C_LCD_2LINE;
    }
    numlines = lines;
    numcols = cols;

    // set offset
    I2C_LCD_setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);

    // Set 4-Bit mode & lines & font
    I2C_LCD_command4bit(I2C_LCD_FUNCTIONSET | displayfunction);

    // turn the display on with no cursor or blinking default
    displaycontrol = I2C_LCD_DISPLAY;  
    I2C_LCD_command4bit(I2C_LCD_DISPLAYCONTROL | displaycontrol);

    // Display clear
    I2C_LCD_command4bit(I2C_LCD_CLEARDISPLAY);

    // Entry mode set
    displaymode = I2C_LCD_ENTRYLEFT | I2C_LCD_ENTRYSHIFTDECREMENT;
    I2C_LCD_command4bit(I2C_LCD_ENTRYMODESET | displaymode);

    I2CMasterStop();
}

void I2C_LCD_print(char c[])
{
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    // Send each char 
    for (uint8_t i = 0; c[i] != '\0'; ++i)
    {
        I2C_LCD_write(c[i]);
    }
    I2CMasterStop();
}

void I2C_LCD_printChar(char c)
{
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    // Send char 
    I2C_LCD_write(c);
    I2CMasterStop();
}

void I2C_LCD_setRowOffsets(uint8_t row1, uint8_t row2, uint8_t row3, uint8_t row4)
{
    row_offsets[0] = row1;
    row_offsets[1] = row2;
    row_offsets[2] = row3;
    row_offsets[3] = row4;
}

void I2C_LCD_setCursorWOI2C(uint8_t col, uint8_t row)
{
    if ( col >= numcols ) {
        col = numcols;
    }
    if ( row >= numlines ) {
        row = numlines;
    }

    I2C_LCD_command4bit(I2C_LCD_SETDDRAMADDR | ((col-1) + row_offsets[row-1]));
}

void I2C_LCD_setCursor(uint8_t col, uint8_t row)
{
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, row);
    I2CMasterStop();
}

void I2C_LCD_cursor(uint8_t state) {

    displaycontrol &= ~I2C_LCD_CURSOR;
    if(state){
        displaycontrol |= I2C_LCD_CURSOR;
    }

    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_command4bit(I2C_LCD_DISPLAYCONTROL | displaycontrol);
    I2CMasterStop();
}

void I2C_LCD_blink(uint8_t state) {

    displaycontrol &= ~I2C_LCD_BLINK;
    if(state){
        displaycontrol |= I2C_LCD_BLINK;
    }

    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_command4bit(I2C_LCD_DISPLAYCONTROL | displaycontrol);
    I2CMasterStop();
}

void I2C_LCD_display(uint8_t state) {

    displaycontrol &= ~I2C_LCD_DISPLAY;
    if(state){
        displaycontrol |= I2C_LCD_DISPLAY;
    }

    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_command4bit(I2C_LCD_DISPLAYCONTROL | displaycontrol);
    I2CMasterStop();
}

void I2C_LCD_backlight(uint8_t state) {

    backlight = state;

    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_command4bit(I2C_LCD_DISPLAYCONTROL | displaycontrol);
    I2CMasterStop();
}

void I2C_LCD_home(){
    I2C_LCD_setCursor(1,1);
}

void I2C_LCD_clear(){
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_command4bit(I2C_LCD_CLEARDISPLAY);
    I2CMasterStop();
}

// These commands scroll the display without changing the RAM
void I2C_LCD_scrollDisplayLeft() {
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_command4bit(I2C_LCD_CURSORSHIFT | I2C_LCD_DISPLAYMOVE | I2C_LCD_MOVELEFT);
    I2CMasterStop();
}

void I2C_LCD_scrollDisplayRight() {
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_command4bit(I2C_LCD_CURSORSHIFT | I2C_LCD_DISPLAYMOVE | I2C_LCD_MOVERIGHT);
    I2CMasterStop();
}

// This is for text that flows Left to Right
void I2C_LCD_leftToRight() {
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    displaymode |= I2C_LCD_ENTRYLEFT;
    I2C_LCD_command4bit(I2C_LCD_ENTRYMODESET | displaymode);
    I2CMasterStop();
}

// This is for text that flows Right to Left
void I2C_LCD_rightToLeft() {
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    displaymode &= ~I2C_LCD_ENTRYLEFT;
    I2C_LCD_command4bit(I2C_LCD_ENTRYMODESET | displaymode);
    I2CMasterStop();
}

void I2C_LCD_cursorFixPosition(uint8_t state) {
    displaymode &= ~I2C_LCD_ENTRYSHIFTINCREMENT;
    if(state){
        displaymode |= I2C_LCD_ENTRYSHIFTINCREMENT;
    }
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_command4bit(I2C_LCD_ENTRYMODESET | displaymode);
    I2CMasterStop();
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void I2C_LCD_createChar(uint8_t location, uint8_t charmap[]) {
    location &= 0x7; // we only have 8 locations 0-7
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_command4bit(I2C_LCD_SETCGRAMADDR | (location << 3));
    for (uint8_t i=0; i<8; i++) {
        I2C_LCD_write(charmap[i]);
    }
    I2CMasterStop();
}