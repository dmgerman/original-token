multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa110/system.h&n; *&n; * Copyright (c) 1996-1999 Russell King.&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
DECL|macro|arch_do_idle
mdefine_line|#define arch_do_idle()&t;&t;cpu_do_idle()
DECL|macro|arch_power_off
mdefine_line|#define arch_power_off()&t;do { } while (0)
DECL|macro|arch_reset
mdefine_line|#define arch_reset(mode)&t;cpu_reset(0x80000000)
macro_line|#endif
eof
