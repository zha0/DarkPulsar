/*
Copyright © 2020 SecIdiot, realoriginal, Mumbai. All Rights Reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

3. The name of the author may not be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY AUTHORS "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include "common.h"

/* Hook: msv1_0!SpAcceptLsaModeContext */
NTSTATUS SpAcceptLsaModeContext(
	LSA_SEC_HANDLE CredentialHandle,
	LSA_SEC_HANDLE ContextHandle,
	PSecBufferDesc InputBuffer,
	ULONG ContextRequirements,
	ULONG TargetDataRep,
	PLSA_SEC_HANDLE NewContextHandle,
	PSecBufferDesc OutputBuffer,
	PULONG ContextAttributes,
	PTimeStamp ExpirationTime,
	PBOOLEAN MappedContext,
	PSecBuffer ContextData
	)
{
	FUNC(SpAcceptLsaModeContextFn);

	SpAcceptLsaModeContextFn = g_SpAcceptLsaModeContext;
	SpAcceptLsaModeContextFn
	(
		CredentialHandle,	/* arg 1  */
		ContextHandle,		/* arg 2  */
		InputBuffer,		/* arg 3  */
		ContextRequirements,	/* arg 4  */
		TargetDataRep,		/* arg 5  */
		NewContextHandle,	/* arg 6  */
		OutputBuffer,		/* arg 7  */
		ContextAttributes,	/* arg 8  */
		ExpirationTime,		/* arg 9  */
		MappedContext,		/* arg 10 */
		ContextData		/* arg 11 */
	);
};
