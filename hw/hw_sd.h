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
 * Copyright 2009 Develer S.r.l. (http://www.develer.com/)
 * All Rights Reserved.
 * -->
 *
 * \brief SD driver hardware-specific definitions.
 *
 * \version $Id: hw_sd.h 2834 2009-08-31 18:11:02Z batt $
 *
 * \author Luca Ottaviano <lottaviano@develer.com>
 */

#ifndef HW_SD_H
#define HW_SD_H

#include "hw_pin.h"


#define SD_CS_INIT() do { PIOA_PER = SD_CS_PIN; PIOA_OER = SD_CS_PIN; SD_CS_OFF(); } while(0)
#define SD_CS_ON()   do { PIOA_CODR = SD_CS_PIN; } while(0)
#define SD_CS_OFF()  do { PIOA_SODR = SD_CS_PIN; } while(0)


#define SD_PIN_INIT() \
	do { \
		PIOA_PER = SD_WRITE_PROTECT_PIN | SD_CARD_PRESENT_PIN; \
		PIOA_PUER = SD_WRITE_PROTECT_PIN | SD_CARD_PRESENT_PIN; \
	} while(0)

#define SD_CARD_PRESENT()  (!(PIOA_PDSR & SD_CARD_PRESENT_PIN))
#define SD_WRITE_PROTECT() ((PIOA_PDSR & SD_WRITE_PROTECT_PIN))

#endif /* HW_SD_H */
