multiline_comment|/*&n; * linux/include/asm-arm/arch-rpc/system.h&n; *&n; * Copyright (c) 1996 Russell King&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
macro_line|#include &lt;asm/proc-fns.h&gt;
DECL|macro|arch_reset
mdefine_line|#define arch_reset(mode) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern void ecard_reset (int card);&t;&t;&t;&t;&bslash;&n;&t;outb (0, IOMD_ROMCR0);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ecard_reset(-1);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;cli();&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&quot;msr  spsr, r1;&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;     &quot;mcr  p15, 0, %0, c1, c0, 0;&quot;&t;&t;&bslash;&n;&t;&t;&t;     &quot;movs pc, #0&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t; : &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t; : &quot;r&quot; (processor.u.armv3v4.reset()));&t;&t;&bslash;&n;&t;}
macro_line|#endif
eof
