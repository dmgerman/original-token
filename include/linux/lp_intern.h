macro_line|#ifndef _LINUX_LP_INTERN_H_
DECL|macro|_LINUX_LP_INTERN_H_
mdefine_line|#define _LINUX_LP_INTERN_H_
multiline_comment|/*&n; * split in two parts by Joerg Dorchain&n; * usr/include/linux/lp.h  modified for Amiga by Michael Rausch&n; * modified for Atari by Andreas Schwab&n; * bug fixed by Jes Sorensen 18/8-94:&n; *     It was not possible to compile the kernel only for Atari or Amiga.&n; *&n; * linux i386 version  c.1991-1992 James Wiegand&n; * many modifications copyright (C) 1992 Michael K. Johnson&n; * Interrupt support added 1993 Nigel Gamble&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/lp_m68k.h&gt;
r_int
id|lp_internal_init
c_func
(paren
r_struct
id|lp_struct
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
