multiline_comment|/*&n; * linux/include/asm-arm/arch-cl7500/dma.h&n; *&n; * Copyright (C) 1999 Nexus Electronics Ltd.&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
multiline_comment|/* DMA is not yet implemented! It should be the same as acorn, copy over.. */
multiline_comment|/*&n; * This is the maximum DMA address that can be DMAd to.&n; * There should not be more than (0xd0000000 - 0xc0000000)&n; * bytes of RAM.&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xd0000000
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;0
DECL|macro|DMA_S0
mdefine_line|#define DMA_S0&t;&t;&t;0
macro_line|#endif /* _ASM_ARCH_DMA_H */
eof
