multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa110/system.h&n; *&n; * Copyright (c) 1996-1999 Russell King.&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
DECL|macro|arch_do_idle
mdefine_line|#define arch_do_idle()&t;&t;cpu_do_idle()
DECL|macro|arch_power_off
mdefine_line|#define arch_power_off()&t;do { } while (0)
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
r_if
c_cond
(paren
id|mode
op_eq
l_char|&squot;s&squot;
)paren
(brace
id|__asm__
r_volatile
(paren
"&quot;"
id|mcr
id|p15
comma
l_int|0
comma
op_mod
l_int|0
comma
id|c1
comma
id|c0
comma
l_int|0
"@"
id|MMU
id|off
id|mov
id|pc
comma
macro_line|#0x80000000&t;&t;@ jump to flash&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|cpu_reset
c_func
(paren
)paren
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
