multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa110/dma.h&n; *&n; * Architecture DMA routes&n; *&n; * Copyright (C) 1997.1998 Russell King&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
multiline_comment|/*&n; * This is the maximum DMA address that can be DMAd to.&n; * There should not be more than (0xd0000000 - 0xc0000000)&n; * bytes of RAM.&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xd0000000
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;8
macro_line|#endif /* _ASM_ARCH_DMA_H */
eof
