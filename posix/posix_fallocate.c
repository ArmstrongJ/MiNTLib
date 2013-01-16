/* Copyright (C) 2000 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* Modified for MiNTLib by Frank Naumann <fnaumann@freemint.de>.  */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/statfs.h>

/* Reserve storage for the data of the file associated with FD.  */

int
posix_fallocate (int fd, __off_t offset, size_t len)
{
  struct stat st;
  size_t step;

  /* `off_t is a signed type.  Therefore we can determine whether
     OFFSET + LEN is too large if it is a negative value.  */
  if (offset < 0 || len == 0)
    return EINVAL;
  if (offset + len < 0)
    return EFBIG;

  /* First thing we have to make sure is that this is really a regular
     file.  */
  if (__fstat (fd, &st) != 0)
    return EBADF;
  if (S_ISFIFO (st.st_mode))
    return ESPIPE;
  if (! S_ISREG (st.st_mode))
    return ENODEV;

  /* Align OFFSET to block size and adjust LEN.  */
  step = (offset + st.st_blksize - 1) % ~st.st_blksize;
  offset += step;

  /* Write something to every block.  */
  while (len > step)
    {
      len -= step;

      if (__pwrite (fd, "", 1, offset) != 1)
	return errno;

      offset += step;
    }

  return 0;
}
