multiline_comment|/*&n; * linux/include/asm-arm/arch-arc/dma.h&n; *&n; * Copyright (C) 1996-1998 Russell King&n; *&n; * Acorn Archimedes/A5000 architecture virtual DMA&n; * implementation&n; *&n; * Modifications:&n; *  04-04-1998&t;RMK&t;Merged arc and a5k versions&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0x03000000
multiline_comment|/*&n; * DMA modes - we have two, IN and OUT&n; */
r_typedef
r_enum
(brace
DECL|enumerator|DMA_MODE_READ
id|DMA_MODE_READ
comma
DECL|enumerator|DMA_MODE_WRITE
id|DMA_MODE_WRITE
DECL|typedef|dmamode_t
)brace
id|dmamode_t
suffix:semicolon
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;4
DECL|macro|DMA_0
mdefine_line|#define DMA_0&t;&t;&t;0
DECL|macro|DMA_1
mdefine_line|#define DMA_1&t;&t;&t;1
DECL|macro|DMA_VIRTUAL_FLOPPY
mdefine_line|#define DMA_VIRTUAL_FLOPPY&t;2
DECL|macro|DMA_VIRTUAL_SOUND
mdefine_line|#define DMA_VIRTUAL_SOUND&t;3
macro_line|#ifdef CONFIG_ARCH_A5K
DECL|macro|DMA_FLOPPY
mdefine_line|#define DMA_FLOPPY&t;&t;DMA_VIRTUAL_FLOPPY
macro_line|#endif
macro_line|#endif /* _ASM_ARCH_DMA_H */
eof
