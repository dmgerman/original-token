multiline_comment|/*&n; * linux/include/asm-arm/hardware.h&n; *&n; * Copyright (C) 1996 Russell King&n; *&n; * Common hardware definitions&n; */
macro_line|#ifndef __ASM_HARDWARE_H
DECL|macro|__ASM_HARDWARE_H
mdefine_line|#define __ASM_HARDWARE_H
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#ifdef PARAMS_OFFSET
DECL|macro|PARAMS_BASE
mdefine_line|#define PARAMS_BASE&t;&t;((PAGE_OFFSET) + (PARAMS_OFFSET))
macro_line|#else
DECL|macro|PARAMS_BASE
mdefine_line|#define PARAMS_BASE&t;&t;0
macro_line|#endif
macro_line|#endif
eof
