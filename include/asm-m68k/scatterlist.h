macro_line|#ifndef _M68K_SCATTERLIST_H
DECL|macro|_M68K_SCATTERLIST_H
mdefine_line|#define _M68K_SCATTERLIST_H
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
macro_line|#ifdef __sparc__
DECL|member|dvma_address
r_char
op_star
id|dvma_address
suffix:semicolon
multiline_comment|/* A place to hang host-specific addresses at. */
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (0x00ffffff)
macro_line|#endif /* !(_M68K_SCATTERLIST_H) */
eof
