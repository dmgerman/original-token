macro_line|#ifndef _FTAPE_H
DECL|macro|_FTAPE_H
mdefine_line|#define _FTAPE_H
multiline_comment|/*&n; * Copyright (C) 1994-1995 Bas Laarhoven.&n;&n;This program is free software; you can redistribute it and/or modify&n;it under the terms of the GNU General Public License as published by&n;the Free Software Foundation; either version 2, or (at your option)&n;any later version.&n;&n;This program is distributed in the hope that it will be useful,&n;but WITHOUT ANY WARRANTY; without even the implied warranty of&n;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;GNU General Public License for more details.&n;&n;You should have received a copy of the GNU General Public License&n;along with this program; see the file COPYING.  If not, write to&n;the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; $Source: /home/bas/distr/ftape-2.03b/RCS/ftape.h,v $&n; $Author: bas $&n; *&n; $Revision: 1.18 $&n; $Date: 1995/05/06 16:11:53 $&n; $State: Beta $&n; *&n; *      This file contains global definitions, typedefs and macro&squot;s&n; *      for the QIC-40/80 floppy-tape driver for Linux.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
DECL|macro|SECTOR
mdefine_line|#define SECTOR(x)       (x+1)         /* sector offset into real sector */
DECL|macro|SECTOR_SIZE
mdefine_line|#define SECTOR_SIZE     (1024)
DECL|macro|SECTORS_PER_SEGMENT
mdefine_line|#define SECTORS_PER_SEGMENT (32)
DECL|macro|BUFF_SIZE
mdefine_line|#define BUFF_SIZE       (SECTORS_PER_SEGMENT * SECTOR_SIZE)
DECL|macro|FTAPE_UNIT
mdefine_line|#define FTAPE_UNIT      (ftape_unit &amp; 3)
DECL|macro|RQM_DELAY
mdefine_line|#define RQM_DELAY       (12)
DECL|macro|MILLISECOND
mdefine_line|#define MILLISECOND     (1)
DECL|macro|SECOND
mdefine_line|#define SECOND          (1000)
DECL|macro|FOREVER
mdefine_line|#define FOREVER         (-1)
macro_line|#ifndef HZ
macro_line|# error &quot;HZ undefined.&quot;
macro_line|#endif
DECL|macro|MSPT
mdefine_line|#define MSPT            (SECOND / HZ) /* milliseconds per tick */
multiline_comment|/* This defines the number of retries that the driver will allow&n; * before giving up (and letting a higher level handle the error).&n; */
macro_line|#ifdef TESTING
DECL|macro|SOFT_RETRIES
macro_line|# define SOFT_RETRIES 1          /* number of low level retries */
DECL|macro|RETRIES_ON_ECC_ERROR
macro_line|# define RETRIES_ON_ECC_ERROR 3  /* ecc error when correcting segment */
macro_line|#else
DECL|macro|SOFT_RETRIES
macro_line|# define SOFT_RETRIES 6          /* number of low level retries (triple) */
DECL|macro|RETRIES_ON_ECC_ERROR
macro_line|# define RETRIES_ON_ECC_ERROR 3  /* ecc error when correcting segment */
macro_line|#endif
multiline_comment|/*      some useful macro&squot;s&n; */
DECL|macro|ABS
mdefine_line|#define ABS(a)          ((a) &lt; 0 ? -(a) : (a))
DECL|macro|NR_ITEMS
mdefine_line|#define NR_ITEMS(x)     (sizeof(x)/ sizeof(*x))
DECL|typedef|byte
r_typedef
r_int
r_char
id|byte
suffix:semicolon
r_extern
r_int
id|ftape_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
