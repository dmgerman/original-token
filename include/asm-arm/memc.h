DECL|macro|VDMA_ALIGNMENT
mdefine_line|#define VDMA_ALIGNMENT&t;PAGE_SIZE
DECL|macro|VDMA_XFERSIZE
mdefine_line|#define VDMA_XFERSIZE&t;16
DECL|macro|VDMA_INIT
mdefine_line|#define VDMA_INIT&t;0
DECL|macro|VDMA_START
mdefine_line|#define VDMA_START&t;1
DECL|macro|VDMA_END
mdefine_line|#define VDMA_END&t;2
macro_line|#ifndef __ASSEMBLER__
r_extern
r_void
id|memc_write
c_func
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|macro|video_set_dma
mdefine_line|#define video_set_dma(start,end,offset)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;memc_write (VDMA_START, (start &gt;&gt; 2));&t;&t;&t;&bslash;&n;&t;memc_write (VDMA_END, (end - VDMA_XFERSIZE) &gt;&gt; 2);&t;&bslash;&n;&t;memc_write (VDMA_INIT, (offset &gt;&gt; 2));&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif
eof
