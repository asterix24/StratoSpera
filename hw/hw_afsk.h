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
 * Copyright 2006 Develer S.r.l. (http://www.develer.com/)
 * All Rights Reserved.
 * -->
 *
 * \brief AFSK modem hardware-specific definitions.
 *
 * \author Francesco Sacchi <batt@develer.com>
 */

#ifndef HW_AFSK_H
#define HW_AFSK_H

#include <cfg/compiler.h>
#include "hw_pin.h"
#include <bsm-2/adc_mgr.h>

/**
 * Initialize the specified channel of the ADC for AFSK needs.
 * The adc should be configured to have a continuos stream of convertions.
 * For every convertion there must be an ISR that read the sample
 * and call afsk_adc_isr(), passing the context and the sample.
 *
 * \param ch channel to be used for AFSK demodulation.
 * \param ctx AFSK context (\see Afsk). This parameter must be saved and
 *            passed back to afsk_adc_isr() for every convertion.
 */
#define AFSK_ADC_INIT(ch, ctx) adc_mgr_init(ch, ctx)


#define DAC_PIN_MASK (BV(DAC_PIN_START) | BV(DAC_PIN_START+1) | BV(DAC_PIN_START+2) | BV(DAC_PIN_START+3))

#define AFSK_STROBE_INIT() \
	do { \
			PIOA_PER  = AFSK_STROBE_PIN; \
			PIOA_OER =  AFSK_STROBE_PIN; \
			PIOA_CODR = AFSK_STROBE_PIN; \
	} while (0)

#define AFSK_STROBE_ON()   do { PIOA_SODR = AFSK_STROBE_PIN; } while (0)
#define AFSK_STROBE_OFF()  do { PIOA_CODR = AFSK_STROBE_PIN; } while (0)


/**
 * Initialize the specified channel of the DAC for AFSK needs.
 * The DAC has to be configured in order to call an ISR for every sample sent.
 * The DAC doesn't have to start the IRQ immediatly but have to wait
 * the AFSK driver to call AFSK_DAC_IRQ_START().
 * The ISR must then call afsk_dac_isr() passing the AFSK context.
 * \param ch DAC channel to be used for AFSK modulation.
 * \param ctx AFSK context (\see Afsk).  This parameter must be saved and
 *             passed back to afsk_dac_isr() for every convertion.
 */
#define AFSK_DAC_INIT(ch, ctx) \
	do { \
		(void)ch, (void)ctx; \
		/* Disable pullups */ \
		PIOA_PUDR = DAC_PIN_MASK | PTT_PIN; \
		/* Set PIO to pin */ \
		PIOA_PER  = DAC_PIN_MASK | PTT_PIN; \
		/* Enable block writing */ \
		PIOA_OWER = DAC_PIN_MASK; \
		/* Enanble as autput */ \
		PIOA_OER = DAC_PIN_MASK | PTT_PIN; \
		PIOA_CODR = PTT_PIN; \
	} while (0)

/**
 * Start DAC convertions on channel \a ch.
 * \param ch DAC channel.
 */
#define AFSK_DAC_IRQ_START(ch) \
	do { \
		(void)ch; \
		extern volatile bool hw_afsk_dac_isr; \
		PIOA_SODR = PTT_PIN; \
		hw_afsk_dac_isr = true; \
	} while (0)

/**
 * Stop DAC convertions on channel \a ch.
 * \param ch DAC channel.
 */
#define AFSK_DAC_IRQ_STOP(ch) \
	do { \
	(void)ch; \
	extern volatile bool hw_afsk_dac_isr; \
	PIOA_CODR = PTT_PIN; \
	hw_afsk_dac_isr = false; \
	} while (0)


#endif /* HW_AFSK_H */
