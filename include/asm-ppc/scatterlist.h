macro_line|#ifndef _PPC_SCATTERLIST_H
DECL|macro|_PPC_SCATTERLIST_H
mdefine_line|#define _PPC_SCATTERLIST_H
macro_line|#include &lt;linux/config.h&gt;
DECL|struct|scatterlist
r_struct
id|scatterlist
(brace
DECL|member|address
r_char
op_star
id|address
suffix:semicolon
multiline_comment|/* Location data is to be transferred to */
DECL|member|alt_address
r_char
op_star
id|alt_address
suffix:semicolon
multiline_comment|/* Location of actual if address is a &n;&t;&t;&t; * dma indirect buffer.  NULL otherwise */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_PMAC
multiline_comment|/*&n; * This is used in the scsi code to decide if bounce buffers are needed.&n; * Fortunately the dma controllers on the PowerMac are a bit better&n; * than on PCs...&n; */
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (~0UL)
macro_line|#endif
macro_line|#ifdef CONFIG_PREP
multiline_comment|/* PReP systems are like PCs */
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (0x00ffffff)
macro_line|#endif
macro_line|#endif /* !(_PPC_SCATTERLIST_H) */
eof
