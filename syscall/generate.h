/*
 * $Id: generate.h,v 1.2 2005/12/22 09:37:57 fna Exp $
 * 
 * This file belongs to FreeMiNT. It's not in the original MiNT 1.12
 * distribution. See the file CHANGES for a detailed log of changes.
 * 
 * 
 * Copyright 2000-2005 Frank Naumann <fnaumann@freemint.de>
 * All rights reserved.
 * 
 * Please send suggestions, patches or bug reports to me or
 * the MiNT mailing list.
 * 
 * 
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 */

#ifndef _generate_h
#define _generate_h

#include <stdio.h>
#include "syscallparser.h"


void generate_bindings_proto(FILE *out, struct systab *tab, int trapnr);
void generate_bindings_impl(FILE *out, struct systab *tab, int trapnr);
void generate_bindings_old(FILE *out, struct systab *tab, int trapnr);


#endif /* _generate_h */
