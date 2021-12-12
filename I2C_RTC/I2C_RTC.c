#include "I2C_RTC.h"
#include <util/delay.h>
#include <I2CMaster.h>
#include <string.h>

void I2C_RTC_setTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t timeformat) {
    uint8_t am_pm_toggle = 0;

    sec = (sec > 59)? 59:sec;       // overflow-prev sec
    min = (min > 59)? 59:min;       // overflow-prev min
    hour = (hour > 23)? 23:hour;    // overflow-prev hour

    // timeformat correction 
    if (timeformat > 0) {
        timeformat = 1;

        if (hour > 12) {
            hour = hour - 12;
            am_pm_toggle = 1;
        }
    }

    I2CMasterStartWait(I2C_RTC_ADDRESS | I2C_RTC_WRITE);        // Start write to RTC (wait until BUS is free)
    I2CMasterWrite(I2C_RTC_ADDRESS_SECONDS);                    // Begin from Seconds
    I2CMasterWrite(((sec%10) & 0x0F) | ((sec/10%10)<<4 & 0x70));   // Write seconds
    I2CMasterWrite(((min%10) & 0x0F) | ((min/10%10)<<4 & 0x70));   // Write Minutes
    I2CMasterWrite(((hour%10) & 0x0F) | ((hour/10%10)<<4 & 0x30) | (am_pm_toggle<<5) | (timeformat<<6));    // Write hour + set am/pm + set time format
    I2CMasterStop();    // Stop I2C 
}

void I2C_RTC_setDate(uint8_t date, uint8_t month, uint8_t year) {
    if (date > 31) {
        date = 31;
    }

    if (month > 12) {
        month = 12;
    }

    if (year > 99) {
        year = 99;
    }

    I2CMasterStartWait(I2C_RTC_ADDRESS | I2C_RTC_WRITE);        // Start write to RTC (wait until BUS is free)
    I2CMasterWrite(I2C_RTC_ADDRESS_DAY);                       // Begin from Day
    I2CMasterWrite(0x00);
    I2CMasterWrite(((date%10) & 0x0F) | ((date/10%10)<<4 & 0x30));  // Write Date
    I2CMasterWrite(((month%10) & 0x0F) | ((month/10%10)<<4 & 0x10));// Write Month
    I2CMasterWrite(((year%10) & 0x0F) | ((year/10%10)<<4 & 0xF0));  // Write Year
    I2CMasterStop();    // Stop I2C 
}

void I2C_RTC_initDateTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t month, uint8_t year, uint8_t timeformat) {
    I2C_RTC_setTime(sec, min, hour, timeformat);
    I2C_RTC_setDate(day, month, year); 
}

void I2C_RTC_readTime(char* time) {
    char temp[9];

    I2CMasterStartWait(I2C_RTC_ADDRESS | I2C_RTC_WRITE);
    I2CMasterWrite(I2C_RTC_ADDRESS_SECONDS);
    I2CMasterRepStart(I2C_RTC_ADDRESS | I2C_RTC_READ);
    uint8_t sec = I2CMasterReadAck();
    uint8_t min = I2CMasterReadAck();
    uint8_t hour = I2CMasterReadNak();
    I2CMasterStop();

    // hh:mm:ss
    temp[0] = (hour>>4 & ((hour & 0x40) ? 0x01 : 0x03)) + 0x30;
    temp[1] = (hour & 0x0F) + 0x30;
    temp[2] = ':';
    temp[3] = ((min & 0x70)>>4) + 0x30;
    temp[4] = (min & 0x0F) + 0x30;
    temp[5] = ':';
    temp[6] = ((sec & 0x70)>>4) + 0x30;
    temp[7] = (sec & 0x0F) + 0x30;
    temp[8] = '\0';

    strcpy(time, temp);
}