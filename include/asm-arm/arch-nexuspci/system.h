multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/system.h&n; *&n; * Copyright (c) 1996,1997,1998 Russell King.&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
DECL|function|arch_reset
r_extern
id|__inline__
r_void
id|arch_reset
c_func
(paren
r_char
id|mode
)paren
(brace
multiline_comment|/*&n;&t; * loop endlessly - the watchdog will reset us if it&squot;s enabled.&n;&t; */
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
