#include "cfg/cfg_boot.h"

#include <cfg/macros.h>
#include <cfg/debug.h>

// Define log settings for cfg/log.h
#define LOG_LEVEL    CONFIG_BOOT_LOG_LEVEL
#define LOG_FORMAT   CONFIG_BOOT_LOG_FORMAT
#include <cfg/log.h>

#include "hw/hw_boot.h"
#include "hw/hw_pin.h"
#include "hw/hw_sd.h"

#include <cpu/detect.h>
#include <cpu/irq.h>
#include <cpu/power.h>

#include <drv/flash.h>
#include <drv/spi_dma_at91.h>
#include <drv/timer.h>
#include <drv/sd.h>

#include <fs/fat.h>

#include <io/arm.h>

#include <string.h>

#include <verstag.h>

/*
 * Define pointer function to main program.
 */
void (*rom_start)(void) NORETURN = (void *)(FLASH_BOOT_SIZE + FLASH_BASE);

#define START_APP() rom_start()

static Flash flash;
static KFileBlock kflash;
static SpiDmaAt91 spi_dma;

static uint8_t fw_buf[FLASH_PAGE_SIZE_BYTES * 16];
static uint8_t fw_buf1[FLASH_PAGE_SIZE_BYTES * 16];

static FATFS fs;
static FatFile fw_file;
static Sd sd;

int main(void)
{
	IRQ_ENABLE;
	kdbg_init();
	PIOA_CODR = LEDR | LEDG | BUZZER_BIT | CUTOFF_PIN | CAMPULSE_PIN;
	PIOA_OER = LEDR | LEDG | BUZZER_BIT | CUTOFF_PIN | CAMPULSE_PIN;

	kprintf("BSM-2 bootloader, ver %s\n", vers_tag);
	timer_init();
	spi_dma_init(&spi_dma);
	spi_dma_setclock(20000000L);
	SD_PIN_INIT();
	flash_init(&flash, 0);
	block_idx_t boot_size = DIV_ROUNDUP(FLASH_BOOT_SIZE, flash.blk.blk_size);
	kblock_trim(&flash.blk, boot_size, flash.blk.blk_cnt - boot_size);
	kfileblock_init(&kflash, &flash.blk);

	if (!SD_CARD_PRESENT() || !sd_init(&sd, &spi_dma.fd, false))
		goto end;

	if (f_mount(0, &fs))
	{
		LOG_ERR("f_mount error\n");
		goto end;
	}

	timer_delay(500);
	if (fatfile_open(&fw_file, "bsm-2.bin", FA_READ))
	{
		LOG_INFO("firmware file not found\n");
		goto end;
	}

	kfile_off_t fw_len = fw_file.fat_file.fsize;
	LOG_INFO("Firmware file found, size %ld, checking for update...\n", fw_len);

	if (fw_len > (kfile_off_t)(FLASH_MEM_SIZE - FLASH_BOOT_SIZE))
	{
		LOG_ERR("Fw file too large\n");
		goto end;
	}

	size_t len;

	while (fw_len)
	{
		len = MIN((kfile_off_t)sizeof(fw_buf), fw_len);

		if (kfile_read(&fw_file.fd, fw_buf, len) != len)
		{
			LOG_ERR("Error reading fw file\n");
			goto end;
		}

		if (kfile_read(&kflash.fd, fw_buf1, len) != len)
		{
			LOG_ERR("Error reading from flash\n");
			goto end;
		}
		if (memcmp(fw_buf, fw_buf1, len))
			break;

		fw_len -= len;
	}

	if (fw_len == 0)
	{
		LOG_INFO("Already up-to date\n");
		goto end;
	}

	LOG_INFO("Firmware file differs from memory, reprogramming...\n");
	fw_len = fw_file.fat_file.fsize;
	kfile_seek(&fw_file.fd, 0, KSM_SEEK_SET);
	kfile_seek(&kflash.fd, 0, KSM_SEEK_SET);

	while (fw_len)
	{
		len = MIN((kfile_off_t)sizeof(fw_buf), fw_len);

		if (kfile_read(&fw_file.fd, fw_buf, len) != len)
		{
			LOG_ERR("Error reading fw file\n");
			goto end;
		}
		if (kfile_write(&kflash.fd, fw_buf, len) != len)
		{
			LOG_ERR("Error writing flash!\n");
			goto end;
		}

		fw_len -= len;
	}


	LOG_INFO("Done!\n");

end:
	kfile_flush(&kflash.fd);
	IRQ_DISABLE;

	LOG_INFO("Jump to main application.\n");
	START_APP();
}
