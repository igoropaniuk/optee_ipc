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

#ifndef OPTEE_SMC_H
#define OPTEE_SMC_H

#include <smccc.h>

#define OPTEE_SMC_STD_CALL_VAL(func_num) \
	SMCCC_CALL_VAL(SMCCC_STD_CALL, SMCCC_SMC_32, \
			   SMCCC_OWNER_TRUSTED_OS, (func_num))
#define OPTEE_SMC_FAST_CALL_VAL(func_num) \
	SMCCC_CALL_VAL(SMCCC_FAST_CALL, SMCCC_SMC_32, \
			   SMCCC_OWNER_TRUSTED_OS, (func_num))

/*
 * Function specified by SMC Calling convention.
 */
#define OPTEE_SMC_FUNCID_CALLS_COUNT	0xFF00
#define OPTEE_SMC_CALLS_COUNT \
	SMCCC_CALL_VAL(OPTEE_SMC_FAST_CALL, SMCCC_SMC_32, \
			   SMCCC_OWNER_TRUSTED_OS_END, \
			   OPTEE_SMC_FUNCID_CALLS_COUNT)

#define OPTEE_SMC_RPC_FUNC_CMD		5
#define OPTEE_SMC_RETURN_RPC_CMD \
	OPTEE_SMC_RPC_VAL(OPTEE_SMC_RPC_FUNC_CMD)

/* Returned in a0 */
#define OPTEE_SMC_RETURN_UNKNOWN_FUNCTION 0xFFFFFFFF

/* Returned in a0 only from Trusted OS functions */
#define OPTEE_SMC_RETURN_OK		0x0
#define OPTEE_SMC_RETURN_ETHREAD_LIMIT	0x1
#define OPTEE_SMC_RETURN_EBUSY		0x2
#define OPTEE_SMC_RETURN_ERESUME	0x3
#define OPTEE_SMC_RETURN_EBADADDR	0x4
#define OPTEE_SMC_RETURN_EBADCMD	0x5
#define OPTEE_SMC_RETURN_ENOMEM		0x6
#define OPTEE_SMC_RETURN_ENOTAVAIL	0x7
#define OPTEE_SMC_RETURN_IS_RPC(ret)	__optee_smc_return_is_rpc((ret))

static inline bool __optee_smc_return_is_rpc(uint32_t ret)
{
	return ret != OPTEE_SMC_RETURN_UNKNOWN_FUNCTION &&
	       (ret & OPTEE_SMC_RETURN_RPC_PREFIX_MASK) ==
			OPTEE_SMC_RETURN_RPC_PREFIX;
}
#endif /* OPTEE_SMC_H */
