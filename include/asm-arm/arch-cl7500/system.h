multiline_comment|/*&n; * linux/include/asm-arm/arch-cl7500/system.h&n; *&n; * Copyright (c) 1999 Nexus Electronics Ltd.&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
macro_line|#include &lt;asm/iomd.h&gt;
DECL|macro|arch_do_idle
mdefine_line|#define arch_do_idle()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;outb(0, IOMD_SUSMODE)
DECL|macro|arch_reset
mdefine_line|#define arch_reset(mode) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;outb (0, IOMD_ROMCR0);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;cli();&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&quot;msr  spsr, r1;&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;     &quot;mcr  p15, 0, %0, c1, c0, 0;&quot;&t;&t;&bslash;&n;&t;&t;&t;     &quot;movs pc, #0&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t; : &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t; : &quot;r&quot; (cpu_reset()));&t;&t;&t;&t;&bslash;&n;&t;}
DECL|macro|arch_power_off
mdefine_line|#define arch_power_off()&t;do { } while (0)
DECL|macro|arch_power_off
mdefine_line|#define arch_power_off()&t;do { } while (0)
macro_line|#endif
eof
