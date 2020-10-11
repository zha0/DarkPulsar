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

PSECPKG_FUNCTION_TABLE SecPkgFind( IN PCHAR Module, IN PHEAP_LIST HeapList )
{
	HMODULE                Mod;
	FARPROC                Ndl;
	ULONG_PTR              Ptr;
	PHEAP_LIST             Lst;
	PLIST_ENTRY            Hdr;
	PLIST_ENTRY            Ent;
	PSECPKG_FUNCTION_TABLE Pkg;

	Hdr = &HeapList->Next;
	Ent = Hdr->Flink;

	/* Enumerate our Linked-List For the Heap */
	for ( Pkg = NULL ; Ent != Hdr ; Ent = Ent->Flink, Lst = CPTR( Ent ) ) 
	{
		/* Check if the allocation is larger than or equal to the table */
		if ( Lst->Size >= sizeof( SECPKG_FUNCTION_TABLE ) ) 
		{
			/* Get a handle to our module to parse the EAT */
			if ( (Mod = GetModuleHandleA( Module )) != NULL )
			{
				/* Create reference, get needle, and search for needle */
				Ptr = UPTR( Lst->Addr );
				Ndl = CPTR( GetProcAddress( Mod, "SpInitialize" ) );

				for ( int i=0;i<Lst->Size;++i,++Ptr )
				{
					if ( ((PSECPKG_FUNCTION_TABLE)Ptr)->Initialize == CPTR(Ndl) )
					{
						/* Found needle, break and return safely */
						Pkg = CPTR( Ptr ); break;
					};
				};
			};
		};
	};

	return Pkg;
};
