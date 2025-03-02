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
 * Copyright 2010 Develer S.r.l. (http://www.develer.com/)
 *
 * -->
 *
 * \brief LM3S1986: OLED-RIT-128x96 (P14201) low-level hardware macros
 *
 * \author Andrea Righi <arighi@develer.com>
 */

#ifndef HW_RIT128x96_H
#define HW_RIT128x96_H

#include "cfg/macros.h"   /* BV() */
#include "cfg/debug.h"

#include <cpu/attr.h>
#include <cpu/irq.h>
#include <cpu/types.h>

/**
 * \name LCD I/O pins/ports
 * @{
 */
/* OLED Data/Command control pin */
#define GPIO_OLEDDC_PIN 0 /* Implement me! */

/* OLED enable pin */
#define GPIO_OLEDEN_PIN 0 /* Implement me! */
/*@}*/

/**
 * \name LCD bus control macros
 * @{
 */
/* Enter command mode */
#define LCD_SET_COMMAND() /* Implement me! */

/* Enter data mode */
#define LCD_SET_DATA() /* Implement me! */

/* Send data to the display */
#define LCD_WRITE(x)    ((void)x)/* Implement me! */
/*@}*/

INLINE void lcd_bus_init(void)
{
	/* Implement me! */
}

#endif /* HW_RIT128x96_H */
