multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa110/system.h&n; *&n; * Copyright (c) 1996-1998 Russell King.&n; */
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
multiline_comment|/*&n;&t; * loop endlessly&n;&t; */
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|arch_power_off
mdefine_line|#define arch_power_off()   do { } while (0)
DECL|macro|arch_do_idle
mdefine_line|#define arch_do_idle() do {} while (0)
multiline_comment|/*cpu_do_idle()*/
macro_line|#endif
eof
