multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/system.h&n; *&n; * Copyright (c) 1996,1997,1998 Russell King.&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
DECL|function|arch_hard_reset
r_extern
id|__inline__
r_void
id|arch_hard_reset
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * loop endlessly - the watchdog will reset us if it&squot;s enabled.&n;&t; */
id|cli
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
