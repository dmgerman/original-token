multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/dma.h&n; *&n; * Architecture DMA routines&n; *&n; * Copyright (C) 1998 Russell King&n; * Copyright (C) 1998 Philip Blundell&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
multiline_comment|/*&n; * This is the maximum DMA address that can be DMAd to.&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xffffffff
multiline_comment|/*&n; * DMA modes - we have two, IN and OUT&n; */
DECL|typedef|dmamode_t
r_typedef
r_int
id|dmamode_t
suffix:semicolon
DECL|macro|DMA_MODE_READ
mdefine_line|#define DMA_MODE_READ&t;&t;0x44
DECL|macro|DMA_MODE_WRITE
mdefine_line|#define DMA_MODE_WRITE&t;&t;0x48
multiline_comment|/*&n; * The 21285 has two internal DMA channels; we call these 0 and 1.&n; * On CATS hardware we have an additional eight ISA dma channels&n; * numbered 2..9.&n; */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;10
DECL|macro|DMA_ISA_BASE
mdefine_line|#define DMA_ISA_BASE&t;&t;2
DECL|macro|DMA_FLOPPY
mdefine_line|#define DMA_FLOPPY&t;&t;(DMA_ISA_BASE + 2)
macro_line|#endif /* _ASM_ARCH_DMA_H */
eof
