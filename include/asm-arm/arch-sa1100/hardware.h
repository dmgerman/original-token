multiline_comment|/*&n; * linux/include/asm-arm/arch-brutus/hardware.h&n; *&n; * Copyright (C) 1998 Nicolas Pitre &lt;nico@visuaide.com&gt;&n; *&n; * This file contains the hardware definitions for SA1100 architecture&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
multiline_comment|/* Flushing areas */
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0xe0000000&t;/* SA1100 zero bank */
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;0xdf000000
DECL|macro|FLUSH_BASE_MINICACHE
mdefine_line|#define FLUSH_BASE_MINICACHE&t;0xde000000
multiline_comment|/*&n; * PCMCIA IO is mapped to 0xe0000000.  We are likely to use in*()/out*()&n; * IO macros for what might appear there...&n; * The SA1100 PCMCIA interface can be seen like a PC ISA bus for IO.&n; */
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xe0000000&t;/* PCMCIA0 IO space */
macro_line|#endif
eof
