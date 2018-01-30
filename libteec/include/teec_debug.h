/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2018, Linaro Limited
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TEEC_DEBUG_H
#define TEEC_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <teec_sysdeps.h>

#define TEE_PREFIX "OP-TEE Client"
/*
 * Trace levels.
 *
 * ERROR is used when some kind of error has happened, this is most likely the
 * print you will use most of the time when you report some kind of error.
 *
 * INFO is used when you want to print some 'normal' text to the user.
 * This is the default level.
 *
 * DEBUG is used to print extra information to enter deeply in the module.
 *
 * FLOW is used to print the execution flox, typically the in/out of functions.
 *
 * */
#define TRACE_ERROR  1
#define TRACE_INFO   2
#define TRACE_DEBUG  3
#define TRACE_FLOW   4

#if defined(DEBUGLEVEL_0) && !defined(DEBUGLEVEL)
#define DEBUGLEVEL TRACE_ERROR
#endif

#if defined(DEBUGLEVEL_1) && !defined(DEBUGLEVEL)
#define DEBUGLEVEL TRACE_ERROR
#endif

#if defined(DEBUGLEVEL_2) && !defined(DEBUGLEVEL)
#define DEBUGLEVEL TRACE_INFO
#endif

#if defined(DEBUGLEVEL_3) && !defined(DEBUGLEVEL)
#define DEBUGLEVEL TRACE_DEBUG
#endif

#if defined(DEBUGLEVEL_4) && !defined(DEBUGLEVEL)
#define DEBUGLEVEL TRACE_FLOW
#endif

#ifndef DEBUGLEVEL
/* Default debug level. */
#define DEBUGLEVEL TRACE_INFO
#endif

#define dprintf(level, fmt, args...) do { \
	if ((level) <= DEBUGLEVEL) { \
		teec_printv("[" TEE_PREFIX \
			"] : %s:%d:%s(): " fmt "\n", __FILE__, __LINE__, \
			__func__, ##args) \
		} \
	} while (0)

#define EMSG(fmt, ...)   dprintf(TRACE_ERROR, fmt "\n", ##__VA_ARGS__)
#define IMSG(fmt, ...)   dprintf(TRACE_INFO, fmt "\n", ##__VA_ARGS__)
#define DMSG(fmt, ...)   dprintf(TRACE_DEBUG, fmt "\n", ##__VA_ARGS__)
#define FMSG(fmt, ...)   dprintf(TRACE_FLOW, fmt "\n", ##__VA_ARGS__)

#define INMSG(fmt, ...)  FMSG("> " fmt, ##__VA_ARGS__)
#define OUTMSG(fmt, ...) FMSG("< " fmt, ##__VA_ARGS__)
#define OUTRMSG(r)                              \
	do {                                            \
		if (r)                                      \
			EMSG("Function returns with [%d]", r);  \
		OUTMSG("r=[%d]", r);                        \
		return r;                                   \
	} while (0)

#ifdef __cplusplus
}
#endif

#endif /* TEEC_DEBUG_H */
