multiline_comment|/*&n; * linux/include/asm-arm/arch-rpc/system.h&n; *&n; * Copyright (c) 1996-1999 Russell King.&n; */
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#include &lt;asm/iomd.h&gt;
macro_line|#include &lt;asm/io.h&gt;
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
multiline_comment|/*&n;&t; * Jump into the ROM&n;&t; */
id|cpu_reset
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
