
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

#include <teec_core.h>
#include <teec_debug.h>
#include <teec_smc.h>
#include <teec_msg.h>
#include <teec_sysdeps.h>

static int32_t optee_do_call_with_arg(phys_addr_t parg)
{
	struct optee_rpc_param param = { };
	uint32_t ret;

	param.a0 = OPTEE_SMC_CALL_WITH_ARG;
	reg_pair_from_64(&param.a1, &param.a2, parg);
	while (true) {
		struct smccc_res res;

		smccc_smc(param.a0, param.a1, param.a2, param.a3, param.a4,
				param.a5, param.a6, param.a7, &res);

		if (res.a0 == OPTEE_SMC_RETURN_ETHREAD_LIMIT) {
			/* TODO:
			 * Out of threads in secure world, wait for a thread
			 * become available.
			 */
		} else if (OPTEE_SMC_RETURN_IS_RPC(res.a0)) {
			param.a0 = res.a0;
			param.a1 = res.a1;
			param.a2 = res.a2;
			param.a3 = res.a3;

			/* TODO: Handle RPC  */
		} else {
			ret = res.a0;
			break;
		}
	}

	return ret;
}

int optee_open_session(struct tee_open_session_arg *arg,
		       struct tee_param *param)
{
	struct optee_msg_arg *msg_arg;
	phys_addr_t msg_parg;
	int rc;

	msg_arg = teec_alloc(OPTEE_MSG_GET_ARG_SIZE(arg->num_params + 2));

	msg_arg->cmd = OPTEE_MSG_CMD_OPEN_SESSION;
	msg_arg->cancel_id = arg->cancel_id;

	if (msg_arg)
		return -ENOMEM;

	msg_parg = teec_virt2phys(msg_arg);
	/*
	 * Initialize and add the meta parameters needed when opening a
	 * session.
	 */
	msg_arg->params[0].attr = OPTEE_MSG_ATTR_TYPE_VALUE_INPUT |
				  OPTEE_MSG_ATTR_META;
	msg_arg->params[1].attr = OPTEE_MSG_ATTR_TYPE_VALUE_INPUT |
				  OPTEE_MSG_ATTR_META;


	teec_memcpy(&msg_arg->params[0].u.value, arg->uuid, sizeof(arg->uuid));
	teec_memcpy(&msg_arg->params[1].u.value, arg->uuid,
			sizeof(arg->clnt_uuid));

	msg_arg->params[1].u.value.c = arg->clnt_login;


	if (optee_do_call_with_arg(msg_parg)) {
		msg_arg->ret = TEEC_ERROR_COMMUNICATION;
		msg_arg->ret_origin = TEEC_ORIGIN_COMMS;
	}


	if (msg_arg->ret == TEEC_SUCCESS) {
		/* TODO */
	}
out:
	/* TODO: clean up */
	if (msg_arg)
		teec_free(msg_arg);
	return rc;
}
