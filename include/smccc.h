
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

#ifndef SMCCC_H
#define SMCCC_H

#define SMCCC_STD_CALL		0UL
#define SMCCC_FAST_CALL		1UL
#define SMCCC_TYPE_SHIFT	31

#define SMCCC_SMC_32		0
#define SMCCC_SMC_64		1
#define SMCCC_CALL_CONV_SHIFT	30

#define SMCCC_OWNER_MASK	0x3F
#define SMCCC_OWNER_SHIFT	24

#define SMCCC_FUNC_MASK		0xFFFF

#define SMCCC_IS_FAST_CALL(smc_val)	\
	((smc_val) & (SMCCC_FAST_CALL << SMCCC_TYPE_SHIFT))
#define SMCCC_IS_64(smc_val) \
	((smc_val) & (SMCCC_SMC_64 << SMCCC_CALL_CONV_SHIFT))
#define SMCCC_FUNC_NUM(smc_val)	((smc_val) & SMCCC_FUNC_MASK)
#define SMCCC_OWNER_NUM(smc_val) \
	(((smc_val) >> SMCCC_OWNER_SHIFT) & SMCCC_OWNER_MASK)

#define SMCCC_CALL_VAL(type, calling_convention, owner, func_num) \
	(((type) << SMCCC_TYPE_SHIFT) | \
	((calling_convention) << SMCCC_CALL_CONV_SHIFT) | \
	(((owner) & SMCCC_OWNER_MASK) << SMCCC_OWNER_SHIFT) | \
	((func_num) & SMCCC_FUNC_MASK))

#define SMCCC_OWNER_ARCH		0
#define SMCCC_OWNER_CPU		1
#define SMCCC_OWNER_SIP		2
#define SMCCC_OWNER_OEM		3
#define SMCCC_OWNER_STANDARD	4
#define SMCCC_OWNER_TRUSTED_APP	48
#define SMCCC_OWNER_TRUSTED_APP_END	49
#define SMCCC_OWNER_TRUSTED_OS	50
#define SMCCC_OWNER_TRUSTED_OS_END	63

struct smccc_res {
	unsigned long a0;
	unsigned long a1;
	unsigned long a2;
	unsigned long a3;
};


asmlinkage void smccc_smc(unsigned long a0, unsigned long a1,
			unsigned long a2, unsigned long a3, unsigned long a4,
			unsigned long a5, unsigned long a6, unsigned long a7,
			struct arm_smccc_res *res);
#endif /* SMCCC_H */
