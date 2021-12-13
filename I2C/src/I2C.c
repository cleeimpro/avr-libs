/**
 * @file I2C.h
 *
 * @author ClefaMedia
 *
 * @version 1.0
 *
 * @copyright Copyright ClefaMedia 2021
 * All Rights GNU GLP Licensed.
 *
 * @brief This library was created to use the I2C as
 * master using the hardware I2C interface.
 *
 * Current state: only as MASTER
 *
 * based on Peter Fleurys I2CMaster 2005
 */

#include <util/twi.h>      // Requires definition of the TWI register
#include <util/delay.h>    // Requires delay
#include <avr/interrupt.h> // Requires interrupt
#include "I2C.h"

void I2C_init(uint32_t scl_clk)
{
    // initialize I2C clock: TWPS = 0 => prescaler = 1
    if (scl_clk >= 40000)
    {
        TWSR &= ~0x03;                       // no prescaler
        TWBR = ((F_CPU / scl_clk) - 16) / 2; // must be > 10 for stable operation
    }
    else if (scl_clk >= 8000)
    {
        TWSR &= ~0x03;
        TWSR |= 0x01;                            // prescaler set to 4
        TWBR = ((F_CPU / scl_clk) - 16) / 2 / 4; // must be > 10 for stable operation
    }
    else if (scl_clk >= 2000)
    {
        TWSR &= ~0x03;
        TWSR |= 0x02;                             // prescaler set to 16
        TWBR = ((F_CPU / scl_clk) - 16) / 2 / 16; // must be > 10 for stable operation
    }
    else if (scl_clk >= 500)
    {
        TWSR |= 0x03;                              // prescaler set to 64
        TWBR = ((F_CPU / scl_clk) - 16) / 2 / 256; // must be > 10 for stable operation
    }
    else
    {
        TWSR |= 0x03; // prescaler set to 64
        TWBR = 255;   // min. possible baud rate (490 Bps)
    }
}

uint8_t I2C_start(uint8_t address)
{
    uint8_t cnt = 0;

    // send START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    // wait until transmission completed
    while ((!(TWCR & (1 << TWINT))) && (cnt < 10))
    {
        _delay_us(100);
        cnt++;
    }

    // check value of I2C Status Register
    if ((TW_STATUS != TW_START) && (TW_STATUS != TW_REP_START))
        return 1; // ERROR
    cnt = 0;

    // send device address
    TWDR = address;
    TWCR = (1 << TWINT) | (1 << TWEN);

    // wail until transmission completed and ACK/NACK has been received
    while ((!(TWCR & (1 << TWINT))) && (cnt < 10))
    {
        _delay_us(100);
        cnt++;
    }

    // check value of I2C Status Register
    if ((TW_STATUS != TW_MT_SLA_ACK) && (TW_STATUS != TW_MR_SLA_ACK))
        return 1; // ERROR
    return 0;     // SUCCESS
}

void I2C_startWait(uint8_t address)
{
    uint8_t cnt = 0;

    while (1)
    {
        // send START condition
        TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

        // wait until transmission completed
        while ((!(TWCR & (1 << TWINT))) && (cnt < 10))
        {
            _delay_us(100);
            cnt++;
        }

        // check value of TWI Status Register. Mask prescaler bits.
        if ((TW_STATUS != TW_START) && (TW_STATUS != TW_REP_START))
            continue;
        cnt = 0;

        // send device address
        TWDR = address;
        TWCR = (1 << TWINT) | (1 << TWEN);

        // wail until transmission completed
        while ((!(TWCR & (1 << TWINT))) && (cnt < 10))
        {
            _delay_us(100);
            cnt++;
        }

        // check value of I2C Status Register. Mask prescaler bits.
        if ((TW_STATUS == TW_MT_SLA_NACK) || (TW_STATUS == TW_MR_DATA_NACK))
        {
            // device busy, send stop condition to terminate write operation
            TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
            cnt = 0;

            // wait until stop condition is executed and bus released
            while ((TWCR & (1 << TWSTO)) && (cnt < 10))
            {
                _delay_us(100);
                cnt++;
            }

            continue;
        }
        // if( TW_STATUS != TW_MT_SLA_ACK) return 1;
        break;
    }
}

uint8_t I2C_repStart(uint8_t address)
{
    return I2C_start(address);
}

void I2C_stop()
{
    uint8_t cnt = 0;
    /* send stop condition */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    // wait until stop condition is executed and bus released
    while ((TWCR & (1 << TWSTO)) && (cnt < 10))
    {
        _delay_us(100);
        cnt++;
    }
}

uint8_t I2C_write(uint8_t data)
{
    uint8_t cnt = 0;

    TWDR = data; // send data to the previously addressed device
    TWCR = (1 << TWINT) | (1 << TWEN);
    // wait until transmission completed
    while ((!(TWCR & (1 << TWINT))) && (cnt < 10))
    {
        _delay_us(100);
        cnt++;
    }
    // check value of TWI Status Register
    if (TW_STATUS != TW_MT_DATA_ACK)
        return 1;
    return 0;
}

uint8_t I2C_read(uint8_t ack)
{
    uint8_t cnt = 0;

    TWCR = (1 << TWINT) | (1 << TWEN) | (ack << TWEA);
    while ((!(TWCR & (1 << TWINT))) && (cnt < 10))
    {
        _delay_us(100);
        cnt++;
    }
    return TWDR;
}

/**
 * This file is part of I2C
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
