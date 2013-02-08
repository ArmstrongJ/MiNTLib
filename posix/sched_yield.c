
/* Dummy function to yield the processor */

#include <unistd.h>

int sched_yield(void) 
{
	return usleep(1);
}

