multiline_comment|/*&n; * linux/include/asm-arm/hardware.h&n; *&n; * Copyright (C) 1996 Russell King&n; *&n; * Common hardware definitions&n; */
macro_line|#ifndef __ASM_HARDWARE_H
DECL|macro|__ASM_HARDWARE_H
mdefine_line|#define __ASM_HARDWARE_H
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#ifndef FLUSH_BASE
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;0xdf000000
macro_line|#endif
macro_line|#ifdef HAS_EXPMASK
macro_line|#ifndef __ASSEMBLER__
DECL|macro|__EXPMASK
mdefine_line|#define __EXPMASK(offset)&t;(((volatile unsigned char *)EXPMASK_BASE)[offset])
macro_line|#else
DECL|macro|__EXPMASK
mdefine_line|#define __EXPMASK(offset)&t;offset
macro_line|#endif
DECL|macro|EXPMASK_STATUS
mdefine_line|#define&t;EXPMASK_STATUS&t;__EXPMASK(0x00)
DECL|macro|EXPMASK_ENABLE
mdefine_line|#define EXPMASK_ENABLE&t;__EXPMASK(0x04)
macro_line|#endif
macro_line|#endif
eof
