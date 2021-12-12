#include "I2C_RTC.h"        // Requires header file
#include <I2CMaster.h>      // Requires I2CMaster lib by Peter Fleury
#include <string.h>         // Requires strings library

void I2C_RTC_setTime(uint8_t sec, uint8_t min, uint8_t hour) {
    uint8_t am_pm = 0;

    if (sec > 59) {     // limit sec to 59
        sec = 59;
    }

    if (min > 59) {     // limit min to 59
        min = 59;
    }

    if (hour > 23) {    // limit hour to 23
        hour = 23;
    }

    I2CMasterStartWait(I2C_RTC_ADDRESS | I2C_RTC_WRITE);        // Start write to RTC (wait until BUS is free)
    I2CMasterWrite(I2C_RTC_ADDRESS_SECONDS);                    // Begin from Seconds
    I2CMasterWrite((sec%10) | (sec/10)<<4);                     // Write seconds
    I2CMasterWrite((min%10) | (min/10)<<4);                     // Write Minutes
    I2CMasterWrite((hour%10) | (hour/10)<<4);                   // Write hour + set time format
    I2CMasterStop();                                            // Stop I2C 
}

void I2C_RTC_setDate(uint8_t date, uint8_t month, uint8_t year) {
    if (date > 31) {      // Limit date to 31
        date = 31;
    }

    if (month > 12) {    // Limit month to 12
        month = 12;
    }

    if (year > 99) {     // Limit year to 99
        year = 99;
    }

    I2CMasterStartWait(I2C_RTC_ADDRESS | I2C_RTC_WRITE);        // Start write to RTC (wait until BUS is free)
    I2CMasterWrite(I2C_RTC_ADDRESS_DATE);                       // Begin from Date
    I2CMasterWrite((date%10) | (date/10)<<4);                   // Write Date
    I2CMasterWrite((month%10) | (month/10)<<4);                 // Write Month
    I2CMasterWrite((year%10) | (year/10)<<4);                   // Write Year
    I2CMasterStop();                                            // Stop I2C 
}

void I2C_RTC_setDateTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year) {
    I2C_RTC_setTime(sec, min, hour);            // set Time
    I2C_RTC_setDate(date, month, year);         // set Date
}

void I2C_RTC_readTime(char* time) {
    char tmpTime[9];                                        // Temporary Array to save the read time

    I2CMasterStartWait(I2C_RTC_ADDRESS | I2C_RTC_WRITE);    // Start write to RTC (wait until BUS is free)
    I2CMasterWrite(I2C_RTC_ADDRESS_SECONDS);                // Begin from seconds
    I2CMasterRepStart(I2C_RTC_ADDRESS | I2C_RTC_READ);      // start read from RTC (repeated start)
    uint8_t sec = I2CMasterReadAck();                       // save read value (sec) + ack
    uint8_t min = I2CMasterReadAck();                       // save read value (min) + ack
    uint8_t hour = I2CMasterReadNak();                      // save read value (hour) + nak
    I2CMasterStop();                                        // stop I2C

    // hh:mm:ss
    tmpTime[0] = (hour>>4 & 0x03) + '0';    // ten's from hour
    tmpTime[1] = (hour & 0x0F) + '0';       // unit place from hour
    tmpTime[2] = ':';
    tmpTime[3] = (min>>4 & 0x07) + '0';     // ten's from min
    tmpTime[4] = (min & 0x0F) + '0';        // unit place from min
    tmpTime[5] = ':';
    tmpTime[6] = (sec>>4 & 0x07) + '0';     // ten's from sec
    tmpTime[7] = (sec & 0x0F) + '0';        // unit place from sec
    tmpTime[8] = '\0';                      // End Array

    strcpy(time, tmpTime);                  // copy into array time
}

void I2C_RTC_setSQW(uint8_t clk_speed) {
    I2CMasterStartWait(I2C_RTC_ADDRESS | I2C_RTC_WRITE);        // Start write to RTC (wait until BUS is free) 
    I2CMasterWrite(I2C_RTC_ADDRESS_ControlRegister);            // Start from Control Register
    I2CMasterWrite(clk_speed << 3);                             // Write clock speed
    I2CMasterStop();                                            // Stop I2C
}