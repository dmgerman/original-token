multiline_comment|/*&n; * linux/include/asm-arm/arch-rpc/system.h&n; *&n; * Copyright (c) 1996-1999 Russell King.&n; */
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#include &lt;asm/iomd.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|arch_do_idle
mdefine_line|#define arch_do_idle() cpu_do_idle()
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
r_extern
r_void
id|ecard_reset
c_func
(paren
r_int
id|card
)paren
suffix:semicolon
id|ecard_reset
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|IOMD_ROMCR0
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mcr  p15, 0, %0, c1, c0, 0&bslash;n&bslash;t&quot;
l_string|&quot;movs pc, #0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|cpu_reset
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
)brace
eof
