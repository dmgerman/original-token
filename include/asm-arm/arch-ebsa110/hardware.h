multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa110/hardware.h&n; *&n; * Copyright (C) 1996,1997,1998 Russell King.&n; *&n; * This file contains the hardware definitions of the EBSA-110.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
multiline_comment|/*&n; * What hardware must be present&n; */
DECL|macro|HAS_PCIO
mdefine_line|#define HAS_PCIO
macro_line|#ifndef __ASSEMBLER__
multiline_comment|/*&n; * IO definitions&n; */
DECL|macro|PIT_CTRL
mdefine_line|#define PIT_CTRL&t;&t;((volatile unsigned char *)0xf200000d)
DECL|macro|PIT_T2
mdefine_line|#define PIT_T2&t;&t;&t;((volatile unsigned char *)0xf2000009)
DECL|macro|PIT_T1
mdefine_line|#define PIT_T1&t;&t;&t;((volatile unsigned char *)0xf2000005)
DECL|macro|PIT_T0
mdefine_line|#define PIT_T0&t;&t;&t;((volatile unsigned char *)0xf2000001)
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xf0000000
multiline_comment|/*&n; * Mapping areas&n; */
DECL|macro|IO_END
mdefine_line|#define IO_END&t;&t;&t;0xffffffff
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xe0000000
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;(IO_END - IO_BASE)
DECL|macro|IO_START
mdefine_line|#define IO_START&t;&t;0xe0000000
multiline_comment|/*&n; * RAM definitions&n; */
DECL|macro|MAPTOPHYS
mdefine_line|#define MAPTOPHYS(a)&t;&t;((unsigned long)(a) - PAGE_OFFSET)
DECL|macro|KERNTOPHYS
mdefine_line|#define KERNTOPHYS(a)&t;&t;((unsigned long)(&amp;a))
DECL|macro|KERNEL_BASE
mdefine_line|#define KERNEL_BASE&t;&t;(0xc0008000)
macro_line|#else
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xf0000000
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0
macro_line|#endif
macro_line|#endif
eof
