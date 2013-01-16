/* sbrk: emulate Unix sbrk call */
/* by ERS */
/* jrb: added support for allocation from _heapbase when _stksize == -1 
	thanks to Piet van Oostrum & Atze Dijkstra for this idea and
        their diffs. */

/* WARNING: sbrk may not allocate space in continguous memory, i.e.
   two calls to sbrk may not return consecutive memory. This is
   unlike Unix.
*/

/* Further WARNING: in a split_mem model the memory addresses will NOT
   be monotonous. sigh!  (i hate these mem models as much as the next
   person. as usual, people at atari are totally oblivious to such
   brain damage, even when pointed out to them. sigh!)
*/

/*
 * support heat and serve C -- whose author continues to be adamant about
 * size_t -- big sigh!
 */

#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include <mint/osbind.h>
#include "lib.h"

static void *
HeapAlloc (unsigned long sz)
{
	char slush [64];
	register void *sp;
	
	sp = (void *)slush;
	sz = (sz + 7) & ~((unsigned long) 7L); /* round up request size next octet */

	if (sp < (void *)((char *) _heapbase + sz))
		return NULL;

	sp = _heapbase;
	_heapbase = (void *)((char *)_heapbase + sz);
	_stksize -= (long) sz;

	return sp;
}

/* provided for compilers with sizeof(int) == 2 */
void *
__sbrk (size_t n)
{
	void *rval;

	if ((!_split_mem) && (_heapbase != NULL)) {
		if (n) rval = HeapAlloc (n);
		else rval = _heapbase;
	}
	else {
		rval = (void *) Malloc (n);
	}

	if (rval == NULL) {
		if(_split_mem) { 
			/* now switch over to own heap for further requests,
			 * including this one */
			_split_mem = 0;
			return __sbrk (n);
		}

		__set_errno (ENOMEM);
		rval = (void *)(-1L);
	}
	return rval;
}
weak_alias (__sbrk, sbrk)
