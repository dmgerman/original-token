multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa110/a.out.h&n; *&n; * Copyright (C) 1996 Russell King&n; */
macro_line|#ifndef __ASM_ARCH_A_OUT_H
DECL|macro|__ASM_ARCH_A_OUT_H
mdefine_line|#define __ASM_ARCH_A_OUT_H
macro_line|#ifdef __KERNEL__
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP&t;&t;((current-&gt;personality==PER_LINUX_32BIT)? 0xc0000000 : 0x04000000)
DECL|macro|LIBRARY_START_TEXT
mdefine_line|#define LIBRARY_START_TEXT&t;(0x00c00000)
macro_line|#endif
macro_line|#endif
eof
