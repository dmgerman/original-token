multiline_comment|/* $Id: conv.h,v 1.2 1997/09/03 12:29:13 jj Exp $&n; * conv.h: Utility macros for Solaris emulation&n; *&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
multiline_comment|/* #define DEBUG_SOLARIS */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/unistd.h&gt;
multiline_comment|/* As gcc will warn about casting u32 to some ptr, we have to cast it to&n; * unsigned long first, and that&squot;s what is A() for.&n; * You just do (void *)A(x), instead of having to&n; * type (void *)((unsigned long)x) or instead of just (void *)x, which will&n; * produce warnings.&n; */
DECL|macro|A
mdefine_line|#define A(x) ((unsigned long)x)
r_extern
r_int
id|sys_call_table
(braket
)braket
suffix:semicolon
r_extern
r_int
id|sys_call_table32
(braket
)braket
suffix:semicolon
r_extern
r_int
id|sunos_sys_table
(braket
)braket
suffix:semicolon
DECL|macro|SYS
mdefine_line|#define SYS(name) ((long)sys_call_table[__NR_##name])
DECL|macro|SUNOS
mdefine_line|#define SUNOS(x) ((long)sunos_sys_table[x])
macro_line|#endif /* __ASSEMBLY__ */
eof
