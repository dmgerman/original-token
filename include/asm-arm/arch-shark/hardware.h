multiline_comment|/*&n; * linux/include/asm-arm/arch-shark/hardware.h&n; *&n; * by Alexander.Schulz@stud.uni-karlsruhe.de&n; *&n; * derived from:&n; * linux/include/asm-arm/arch-ebsa110/hardware.h&n; * Copyright (C) 1996-1999 Russell King.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Mapping areas&n; */
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xe0000000
multiline_comment|/*&n; * RAM definitions&n; */
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0x60000000
macro_line|#else
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0
macro_line|#endif
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;0x10000000
DECL|macro|IO_START
mdefine_line|#define IO_START&t;&t;0x40000000
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;0xdf000000
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xe0000000
multiline_comment|/* defines for the Framebuffer */
DECL|macro|FB_BASE
mdefine_line|#define FB_BASE                 0xd0000000
DECL|macro|FB_START
mdefine_line|#define FB_START                0x06000000
DECL|macro|FB_SIZE
mdefine_line|#define FB_SIZE                 0x00200000
multiline_comment|/* Registers for Framebuffer */
DECL|macro|FBREG_BASE
mdefine_line|#define FBREG_BASE              (FB_BASE + FB_SIZE)
DECL|macro|FBREG_START
mdefine_line|#define FBREG_START             0x06800000
DECL|macro|FBREG_SIZE
mdefine_line|#define FBREG_SIZE              0x000c0000
macro_line|#endif
eof
