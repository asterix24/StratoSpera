#include "radio.h"

#include "measures.h"
#include "status_mgr.h"
#include "logging.h"

#include <kern/proc.h>
#include <kern/sem.h>

#include <drv/timer.h>
#include <net/afsk.h>
#include <net/ax25.h>

#include <string.h>

#define LOG_LEVEL LOG_LVL_INFO
#include <cfg/log.h>

static Afsk afsk;
static AX25Ctx ax25;

static void ax25_log(struct AX25Msg *msg)
{
	logging_msg("%.*s\n", msg->len, msg->info);
	kprintf("%.*s\n", msg->len, msg->info);
}

static AX25Call ax25_path[2]=
{
	AX25_CALL("APZBRT", 0),
};
static mtime_t aprs_interval;

static Semaphore radio_sem;

void radio_send(char *buf, size_t len)
{
	sem_obtain(&radio_sem);
	ax25_sendVia(&ax25, ax25_path, countof(ax25_path), buf, len);
	sem_release(&radio_sem);
}

static char msg[100];

#define STARTUP_SETUP_TIME  (3 * 60 * 1000) // 3 minutes
#define STARTUP_SETUP_DELAY ms_to_ticks(15 * 1000) // 15 seconds

static void NORETURN radio_process(void)
{
	ticks_t start = timer_clock();
	ticks_t delay;

	while (1)
	{
		ax25_poll(&ax25);
		timer_delay(100);

		if (status_missionTime() < STARTUP_SETUP_TIME)
		{
			/* At startup we need to test communications, so use a short delay */
			delay = STARTUP_SETUP_DELAY;
		}
		else if (status_currStatus() == BSM2_NOFIX
			  || status_currStatus() == BSM2_GROUND_WAIT)
		{
			/* When we are at ground or with no fix, relax timings in order to
			 * save radio battery */
			delay = ms_to_ticks(aprs_interval * 4);
		}
		else
			delay = ms_to_ticks(aprs_interval);

		if (timer_clock() - start > delay)
		{
			start = timer_clock();
			measures_aprsFormat(msg, sizeof(msg));
			radio_send(msg, strnlen(msg, sizeof(msg)));
		}
	}
}

void radio_init(RadioCfg *cfg)
{
	LOG_INFO("Setting radio configuration\n");
	LOG_INFO(" APRS messages interval %ld seconds\n", cfg->aprs_interval);
	LOG_INFO(" Send CALL [%.6s]\n", cfg->send_call);

	aprs_interval = cfg->aprs_interval;
	memcpy(ax25_path[1].call, cfg->send_call, sizeof(ax25_path[1].call));
	ax25_path[1].ssid = 0;

	sem_init(&radio_sem);
	afsk_init(&afsk, ADC_RADIO_CH, 0);
	ax25_init(&ax25, &afsk.fd, ax25_log);
	proc_new(radio_process, NULL, KERN_MINSTACKSIZE * 4, NULL);
}
