/**
 * \file
 * <!--
 * This file is part of BeRTOS.
 *
 * Bertos is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As a special exception, you may use this file as part of a free software
 * library without restriction.  Specifically, if other files instantiate
 * templates or use macros or inline functions from this file, or you compile
 * this file and link it with other files to produce an executable, this
 * file does not by itself cause the resulting executable to be covered by
 * the GNU General Public License.  This exception does not however
 * invalidate any other reasons why the executable file might be covered by
 * the GNU General Public License.
 *
 * Copyright 2008 Develer S.r.l. (http://www.develer.com/)
 * All Rights Reserved.
 * -->
 *
 * \brief Configuration file for lcd display module.
 *
 * \version $Id: cfg_lcd.h 2563 2009-04-20 09:47:08Z batt $
 *
 * \author Daniele Basile <asterix@develer.com>
 */

#ifndef CFG_LCD_H
#define CFG_LCD_H

/**
 * Use 4 bit addressing mode.
 * $WIZ$ type = "boolean"
 */
#define CONFIG_LCD_4BIT            0

/**
 * Use a table to speed up LCD memory addressing.
 * This will use about 100 bytes of RAM.
 * $WIZ$ type = "boolean"
 */
#define CONFIG_LCD_ADDRESS_FAST    1

/**
 * LCD setting for 32122A (AVR implementation).
 * $WIZ$ type = "boolean"
 * $WIZ$ supports = "avr and False"
 */
#define CONFIG_LCD_SOFTINT_REFRESH 0

/**
 * LCD setting for 32122A (AVR implementation).
 * $WIZ$ type = "boolean"
 * $WIZ$ supports = "avr and False"
 */
#define CONFIG_LCD_WAIT            1


#endif /* CFG_LCD_H */

