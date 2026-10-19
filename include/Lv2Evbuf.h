// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019-2020 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


/*
 * The original code was written by David Robillard <http://drobilla.net>
 * Original version: 6f22ee0 from https://github.com/drobilla/jalv.git
 * Minor changes have been done, but no functional changes.
 * Considering this as an "external library", the identifiers do not need to
 * match the NoeMixerr coding conventions.
 */

#ifndef NoeMixerr_LV2_EVBUF_H
#define NoeMixerr_LV2_EVBUF_H

#include "noemixerrconfig.h"

#ifdef NoeMixerr_HAVE_LV2

#include <cstdint>


namespace noemixerr
{


/**
   An abstract/opaque LV2 event buffer.
*/
using LV2_Evbuf = struct LV2_Evbuf_Impl;

/**
   An iterator over an LV2_Evbuf.
*/
struct LV2_Evbuf_Iterator
{
	LV2_Evbuf* evbuf;
	uint32_t offset;
};

/**
   Allocate a new, empty event buffer.
   URIDs for atom:Chunk and atom:Sequence must be passed for LV2_EVBUF_ATOM.
*/
LV2_Evbuf*
lv2_evbuf_new(uint32_t capacity, uint32_t atom_Chunk, uint32_t atom_Sequence);

/**
   Free an event buffer allocated with lv2_evbuf_new.
*/
void
lv2_evbuf_free(LV2_Evbuf* evbuf);

/**
   Clear and initialize an existing event buffer.
   The contents of buf are ignored entirely and overwritten, except capacity
   which is unmodified.
   If input is false and this is an atom buffer, the buffer will be prepared
   for writing by the plugin.  This MUST be called before every run cycle.
*/
void
lv2_evbuf_reset(LV2_Evbuf* evbuf, bool input);

/**
   Return the total padded size of the events stored in the buffer.
*/
uint32_t
lv2_evbuf_get_size(LV2_Evbuf* evbuf);

/**
   Return the actual buffer implementation.
   The format of the buffer returned depends on the buffer type.
*/
void*
lv2_evbuf_get_buffer(LV2_Evbuf* evbuf);

/**
   Return an iterator to the start of `evbuf`.
*/
LV2_Evbuf_Iterator
lv2_evbuf_begin(LV2_Evbuf* evbuf);

/**
   Return an iterator to the end of `evbuf`.
*/
LV2_Evbuf_Iterator
lv2_evbuf_end(LV2_Evbuf* evbuf);

/**
   Check if `iter` is valid.
   @return True if `iter` is valid, otherwise false (past end of buffer)
*/
bool
lv2_evbuf_is_valid(LV2_Evbuf_Iterator iter);

/**
   Advance `iter` forward one event.
   `iter` must be valid.
   @return True if `iter` is valid, otherwise false (reached end of buffer)
*/
LV2_Evbuf_Iterator
lv2_evbuf_next(LV2_Evbuf_Iterator iter);

/**
   Dereference an event iterator (i.e. get the event currently pointed to).
   `iter` must be valid.
   `type` Set to the type of the event.
   `size` Set to the size of the event.
   `data` Set to the contents of the event.
   @return True on success.
*/
bool
lv2_evbuf_get(	LV2_Evbuf_Iterator iter,
				uint32_t* frames,
				uint32_t* type,
				uint32_t* size,
				uint8_t** data);

/**
   Write an event at `iter`.
   The event (if any) pointed to by `iter` will be overwritten, and `iter`
   incremented to point to the following event (i.e. several calls to this
   function can be done in sequence without twiddling iter in-between).
   @return True if event was written, otherwise false (buffer is full).
*/
bool
lv2_evbuf_write(	LV2_Evbuf_Iterator* iter,
					uint32_t frames,
					uint32_t type,
					uint32_t size,
					const uint8_t* data);


} // namespace noemixerr

#endif // NoeMixerr_HAVE_LV2

#endif // NoeMixerr_LV2_EVBUF_H
