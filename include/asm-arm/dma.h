macro_line|#ifndef __ASM_ARM_DMA_H
DECL|macro|__ASM_ARM_DMA_H
mdefine_line|#define __ASM_ARM_DMA_H
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;14
DECL|macro|DMA_0
mdefine_line|#define DMA_0&t;&t;&t;8
DECL|macro|DMA_1
mdefine_line|#define DMA_1&t;&t;&t;9
DECL|macro|DMA_2
mdefine_line|#define DMA_2&t;&t;&t;10
DECL|macro|DMA_3
mdefine_line|#define DMA_3&t;&t;&t;11
DECL|macro|DMA_S0
mdefine_line|#define DMA_S0&t;&t;&t;12
DECL|macro|DMA_S1
mdefine_line|#define DMA_S1&t;&t;&t;13
DECL|macro|DMA_MODE_READ
mdefine_line|#define DMA_MODE_READ&t;&t;0x44
DECL|macro|DMA_MODE_WRITE
mdefine_line|#define DMA_MODE_WRITE&t;&t;0x48
r_extern
r_const
r_char
id|dma_str
(braket
)braket
suffix:semicolon
macro_line|#include &lt;asm/arch/dma.h&gt;
multiline_comment|/* These are in kernel/dma.c: */
multiline_comment|/* reserve a DMA channel */
r_extern
r_int
id|request_dma
c_func
(paren
r_int
r_int
id|dmanr
comma
r_const
r_char
op_star
id|device_id
)paren
suffix:semicolon
multiline_comment|/* release it again */
r_extern
r_void
id|free_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
macro_line|#endif /* _ARM_DMA_H */
eof
