macro_line|#ifndef __ASM_SH_DMA_H
DECL|macro|__ASM_SH_DMA_H
mdefine_line|#define __ASM_SH_DMA_H
multiline_comment|/* Don&squot;t define MAX_DMA_ADDRESS; it&squot;s useless on the SuperH and any&n;   occurrence should be flagged as an error.  */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS 8
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
multiline_comment|/* reserve a DMA channel */
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
multiline_comment|/* release it again */
macro_line|#endif /* __ASM_SH_DMA_H */
eof
