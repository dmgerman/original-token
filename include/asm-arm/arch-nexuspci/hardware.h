multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/hardware.h&n; *&n; * Copyright (C) 1998-1999 Philip Blundell&n; *&n; * This file contains the hardware definitions of the Nexus PCI card.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
multiline_comment|/*    Logical    Physical&n; * 0xfff00000&t;0x10000000&t;SCC2691 DUART&n; * 0xffe00000&t;0x20000000&t;INTCONT&n; * 0xffd00000&t;0x30000000&t;Status&n; * 0xffc00000&t;0x60000000&t;PLX registers&n; * 0xfe000000&t;0x70000000&t;PCI I/O&n; */
multiline_comment|/*&n; * Mapping areas&n; */
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xfe000000
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;0xdf000000
multiline_comment|/*&n; * RAM definitions&n; */
DECL|macro|RAM_BASE
mdefine_line|#define RAM_BASE&t;&t;0x40000000
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0x40000000
macro_line|#endif
eof
