multiline_comment|/* $Id: scatterlist.h,v 1.4 1997/04/10 05:13:32 davem Exp $ */
macro_line|#ifndef _SPARC64_SCATTERLIST_H
DECL|macro|_SPARC64_SCATTERLIST_H
mdefine_line|#define _SPARC64_SCATTERLIST_H
macro_line|#include &lt;asm/page.h&gt;
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
DECL|member|dvma_address
id|__u32
id|dvma_address
suffix:semicolon
multiline_comment|/* A place to hang host-specific addresses at. */
)brace
suffix:semicolon
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD ((0xf0000000) + PAGE_OFFSET)
macro_line|#endif /* !(_SPARC64_SCATTERLIST_H) */
eof
