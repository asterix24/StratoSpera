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
 *
 * -->
 *
 * \author Francesco Sacchi <batt@develer.com>
 *
 * \brief KBlock private interface
 */

#ifndef IO_KBLOCK_P_H
#define IO_KBLOCK_P_H

#include "kblock.h"

#include <cfg/compiler.h>
#include <cfg/debug.h>
#include <cfg/macros.h>

/**
 * \name Prototypes for KBlock access functions.
 *
 * A KBlock user can choose which function subset to implement,
 * but has to set to NULL unimplemented features.
 *
 *  \{
 */
typedef size_t (* kblock_read_direct_t) (struct KBlock *b, block_idx_t index, void *buf, size_t offset, size_t size);
typedef size_t (* kblock_read_t)        (struct KBlock *b, void *buf, size_t offset, size_t size);
typedef size_t (* kblock_write_t)       (struct KBlock *b, const void *buf, size_t offset, size_t size);
typedef int    (* kblock_load_t)        (struct KBlock *b, block_idx_t index);
typedef int    (* kblock_store_t)       (struct KBlock *b, block_idx_t index);

typedef int    (* kblock_write_block_t) (struct KBlock *b, block_idx_t index, const void *buf);
typedef int    (* kblock_read_block_t)  (struct KBlock *b, block_idx_t index, void *buf);

typedef int    (* kblock_error_t)       (struct KBlock *b);
typedef int    (* kblock_clearerr_t)    (struct KBlock *b);
typedef int    (* kblock_close_t)       (struct KBlock *b);
/* \} */

/**
 * Table of interface functions for a KBlock device.
 */
typedef struct KBlockVTable
{
	kblock_read_direct_t readDirect;

	kblock_read_t  readBuf;
	kblock_write_t writeBuf;
	kblock_load_t  load;
	kblock_store_t store;
	
	kblock_read_block_t readBlock;
	kblock_write_block_t writeBlock;
	
	kblock_error_t    error;    ///< \sa kblock_error()
	kblock_clearerr_t clearerr; ///< \sa kblock_clearerr()

	kblock_close_t  close; ///< \sa kblock_close()
} KBlockVTable;


#define KB_BUFFERED BV(0)

/**
 * KBlock private members.
 * These are the private members of the KBlock class, please do not
 * access these directly, use the KBlock API.
 */
typedef struct KBlockPriv
{
	DB(id_t type);         ///< Used to keep track, at runtime, of the class type.
	int flags;             ///< Status and error flags.
	void *buf;
	block_idx_t blk_start; ///< Start block number when the device is trimmed. \sa kblock_trim()
	block_idx_t curr_blk;
	bool cache_dirty;

	const struct KBlockVTable *vt; ///< Virtual table of interface functions.
} KBlockPriv;

int kblock_swWriteBlock(struct KBlock *b, block_idx_t index, const void *buf);
int kblock_swReadBlock(struct KBlock *b, block_idx_t index, void *buf);

size_t kblock_swReadDirect(struct KBlock *b, block_idx_t index, void *buf, size_t offset, size_t size);
int kblock_swLoad(struct KBlock *b, block_idx_t index);
int kblock_swStore(struct KBlock *b, block_idx_t index);
size_t kblock_swReadBuf(struct KBlock *b, void *buf, size_t offset, size_t size);
size_t kblock_swWriteBuf(struct KBlock *b, const void *buf, size_t offset, size_t size);

#endif /* IO_KBLOCK_P_H */
