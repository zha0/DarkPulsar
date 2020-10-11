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

static PVOID InitHeap( IN ULONG Size )
{
	/* Allocate memory like malloc() */
	return HeapAlloc( g_Heap, 0, Size );
};

static BOOL FreeHeap( IN PVOID Buff )
{
	/* Free memory like free() */
	return HeapFree( g_Heap, 0, Buff );
};

BOOL InitHeapList( IN PHEAP_LIST HeapList )
{
	PHEAP_LIST         hptr = NULL;
	PROCESS_HEAP_ENTRY heap = { 0 };

	/* Initialize linked list safely */
	InitializeListHead( &HeapList->Next );

	/* Lock the heap to prevent changes */
	if ( HeapLock( GetProcessHeap() ) )
	{
		/* Start "walking" the heaps created */
		while ( HeapWalk( GetProcessHeap(), &heap ) )
		{
			/* Check if its a valid heap pointer */
			if ( (heap.wFlags & PROCESS_HEAP_ENTRY_BUSY) )
			{
				/* Check if its been a commited region */
				if ( !(heap.wFlags & (PROCESS_HEAP_REGION | PROCESS_HEAP_UNCOMMITTED_RANGE)) )
				{
					/* Allocate a list entry and add to the list */
					if ( (hptr = InitHeap(sizeof(HEAP_LIST))) )
					{
						hptr->Addr = UPTR( heap.lpData );
						hptr->Size = heap.cbData;

						InsertTailList( &HeapList->Next, &hptr->Next );
					};
				};
			};
		};
		/* Unlock heap to allow access */
		HeapUnlock( GetProcessHeap() );
	};

	/* Check if the above code succeeded. */
	return IsListEmpty( &HeapList->Next ) ? FALSE : TRUE;
};
