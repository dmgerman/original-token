multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/hardware.h&n; *&n; * Copyright (C) 1997 Philip Blundell&n; *&n; * This file contains the hardware definitions of the Nexus PCI card.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
multiline_comment|/*&n; * What hardware must be present&n; */
macro_line|#ifndef __ASSEMBLER__
multiline_comment|/*&n; * Mapping areas&n; */
DECL|macro|IO_END
mdefine_line|#define IO_END&t;&t;&t;0xffffffff
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xd0000000
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;(IO_END - IO_BASE)
DECL|macro|IO_START
mdefine_line|#define IO_START&t;&t;0xd0000000
multiline_comment|/*&n; * RAM definitions&n; */
DECL|macro|RAM_BASE
mdefine_line|#define RAM_BASE&t;&t;0x40000000
DECL|macro|MAPTOPHYS
mdefine_line|#define MAPTOPHYS(a)&t;&t;((unsigned long)(a) - PAGE_OFFSET + RAM_BASE)
DECL|macro|KERNTOPHYS
mdefine_line|#define KERNTOPHYS(a)&t;&t;((unsigned long)(&amp;a))
DECL|macro|KERNEL_BASE
mdefine_line|#define KERNEL_BASE&t;&t;(0xc0008000)
macro_line|#else
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0
macro_line|#endif
macro_line|#endif
eof
