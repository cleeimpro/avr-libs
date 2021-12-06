#ifndef _I2C_LCD_DIGITALNUMBER_H
#define _I2C_LCD_DIGITALNUMBER_H   1

#include "I2C_LCD.h"

#define FULL_BAR    0xFF
#define UPPER_BAR   0
#define LOWER_BAR   1
#define LEFT_BAR    2
#define RIGHT_BAR   3
#define LEFT_DOT    4
#define RIGHT_DOT   5
#define B_SLASH     6
#define F_SLASH     7

void I2C_LCD_DigitalNumber_customChars();
void I2C_LCD_DigitalNumber_init();

void writeDigital0(uint8_t col);
void writeDigital1(uint8_t col);
void writeDigital2(uint8_t col);
void writeDigital3(uint8_t col);
void writeDigital4(uint8_t col);
void writeDigital5(uint8_t col);
void writeDigital6(uint8_t col);
void writeDigital7(uint8_t col);
void writeDigital8(uint8_t col);
void writeDigital9(uint8_t col);

void writeDigitalNumber(uint8_t num, uint8_t col);
void writeDDot();
void clearDDot();
void toggleDDot();

uint8_t ddotState;

#endif
/**@}*/