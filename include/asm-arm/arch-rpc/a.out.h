multiline_comment|/*&n; * linux/include/asm-arm/arch-rpc/a.out.h&n; *&n; * Copyright (C) 1996-1999 Russell King&n; */
macro_line|#ifndef __ASM_ARCH_A_OUT_H
DECL|macro|__ASM_ARCH_A_OUT_H
mdefine_line|#define __ASM_ARCH_A_OUT_H
macro_line|#include &lt;asm/arch/memory.h&gt;
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP &bslash;&n;&t;((current-&gt;personality == PER_LINUX_32BIT) ? &bslash;&n;&t; TASK_SIZE : 0x04000000)
macro_line|#endif
eof
