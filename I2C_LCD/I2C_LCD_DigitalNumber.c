#include "I2C_LCD_DigitalNumber.h"
#include "I2C_LCD.h"
#include <util/delay.h>
#include <I2CMaster.h>

void I2C_LCD_DigitalNumber_customChars(){
    uint8_t upperBar[] = {0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t lowerBar[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F};
    uint8_t leftBar[] = {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
    uint8_t rightBar[] = {0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03};
    uint8_t bSlash[] = {0x18, 0x18, 0x0C, 0x0C, 0x06, 0x06, 0x03, 0x03};
    uint8_t fSlash[] = {0x03, 0x03, 0x06, 0x06, 0x0C, 0x0C, 0x18, 0x18};
    uint8_t dotRight[] = {0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00};
    uint8_t dotLeft[] = {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00};

    I2C_LCD_createChar(UPPER_BAR, upperBar);
    I2C_LCD_createChar(LOWER_BAR, lowerBar);
    I2C_LCD_createChar(LEFT_DOT, dotLeft);
    I2C_LCD_createChar(RIGHT_DOT, dotRight);
    I2C_LCD_createChar(LEFT_BAR, leftBar);
    I2C_LCD_createChar(RIGHT_BAR, rightBar);
    I2C_LCD_createChar(B_SLASH, bSlash);
    I2C_LCD_createChar(F_SLASH, fSlash);
}

void I2C_LCD_DigitalNumber_init() {
    I2C_LCD_init(20, 4);
    I2C_LCD_DigitalNumber_customChars();
    clearDDot();
}

void writeDigital0(uint8_t col){
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);
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
    I2CMasterStop();
}

void writeDigital1(uint8_t col){
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);
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
    I2CMasterStop();
}

void writeDigital2(uint8_t col){
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);
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
    I2CMasterStop();
}

void writeDigital3(uint8_t col){
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);
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
    I2CMasterStop();
}

void writeDigital4(uint8_t col){
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_setCursorWOI2C(col, 2);
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
    I2CMasterStop();
}

void writeDigital5(uint8_t col){
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);
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
    I2CMasterStop();
}

void writeDigital6(uint8_t col){
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col,1);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_setCursorWOI2C(col,2);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_setCursorWOI2C(col,3);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col,4);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2CMasterStop();
}

void writeDigital7(uint8_t col){
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col,1);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col,2);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col,3);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col,4);
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(' ');
    I2C_LCD_write(FULL_BAR);
    I2CMasterStop();
}

void writeDigital8(uint8_t col){
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col, 1);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col, 2);
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
    I2CMasterStop();
}

void writeDigital9(uint8_t col){
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    I2C_LCD_setCursorWOI2C(col,1);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col,2);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col,3);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(UPPER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2C_LCD_setCursorWOI2C(col,4);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(LOWER_BAR);
    I2C_LCD_write(FULL_BAR);
    I2CMasterStop();
}

void writeDigitalNumber(uint8_t num, uint8_t col) {
    switch (num)
    {
    case 0:
        writeDigital0(col);
        break;
    
    case 1:
        writeDigital1(col);
        break;

    case 2:
        writeDigital2(col);
        break;
    
    case 3:
        writeDigital3(col);
        break;
    
    case 4:
        writeDigital4(col);
        break;

    case 5:
        writeDigital5(col);
        break;

    case 6:
        writeDigital6(col);
        break;

    case 7:
        writeDigital7(col);
        break;

    case 8: 
        writeDigital8(col);
        break;

    case 9:
        writeDigital9(col);
        break;

    default:
        I2C_LCD_setCursorWOI2C(col,1);
        I2C_LCD_write(B_SLASH);
        I2C_LCD_write(' ');
        I2C_LCD_write(' ');
        I2C_LCD_write(F_SLASH);
        I2C_LCD_setCursorWOI2C(col,2);
        I2C_LCD_write(' ');
        I2C_LCD_write(B_SLASH);
        I2C_LCD_write(F_SLASH);
        I2C_LCD_write(' ');
        I2C_LCD_setCursorWOI2C(col,3);
        I2C_LCD_write(UPPER_BAR);
        I2C_LCD_write(RIGHT_BAR);
        I2C_LCD_write(LEFT_BAR);
        I2C_LCD_write(UPPER_BAR);
        I2C_LCD_setCursorWOI2C(col,4);
        I2C_LCD_write(UPPER_BAR);
        I2C_LCD_write(RIGHT_BAR);
        I2C_LCD_write(LEFT_BAR);
        I2C_LCD_write(UPPER_BAR);
        break;
    }
}

void writeDDot() 
{
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);

    I2C_LCD_setCursorWOI2C(10,2);
    I2C_LCD_write(RIGHT_DOT);
    I2C_LCD_write(LEFT_DOT);
    I2C_LCD_setCursorWOI2C(10,3);
    I2C_LCD_write(RIGHT_DOT);
    I2C_LCD_write(LEFT_DOT);
    ddotState = 1;

    I2CMasterStop();
}

void clearDDot() 
{
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);

    I2C_LCD_setCursorWOI2C(10,2);
    I2C_LCD_write(0x20);
    I2C_LCD_write(0x20);
    I2C_LCD_setCursorWOI2C(10,3);
    I2C_LCD_write(0x20);
    I2C_LCD_write(0x20);
    ddotState = 0;

    I2CMasterStop();
}

void toggleDDot()
{
    I2CMasterStartWait(I2C_LCD_ADDRESS & ~I2C_WRITE);
    if(ddotState){
        clearDDot();
    }else{
        writeDDot();
    }
    ddotState = !ddotState;
    I2CMasterStop();
}
