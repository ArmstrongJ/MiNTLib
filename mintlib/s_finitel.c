/* s_finitel.c -- long double version of s_finite.c.
 * Conversion to IEEE quad long double by Jakub Jelinek, jj@ultra.linux.cz.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

/*
 * finitel(x) returns 1 is x is finite, else 0;
 * no branching!
 */

#include "math.h"
#include "math_private.h"

int
__finitel(long double x)
{
	int64_t hx;
	GET_LDOUBLE_MSW64(hx,x);
	return (int)((u_int64_t)((hx&0x7fffffffffffffffLL)
				 -0x7fff000000000000LL)>>63);
}
weak_alias (__finitel, finitel)
