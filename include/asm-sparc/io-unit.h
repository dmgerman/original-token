multiline_comment|/* io-unit.h: Definitions for the sun4d IO-UNIT.&n; *&n; * Copyright (C) 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#ifndef _SPARC_IO_UNIT_H
DECL|macro|_SPARC_IO_UNIT_H
mdefine_line|#define _SPARC_IO_UNIT_H
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/spinlock.h&gt;
multiline_comment|/* The io-unit handles all virtual to physical address translations&n; * that occur between the SBUS and physical memory.  Access by&n; * the cpu to IO registers and similar go over the xdbus so are&n; * translated by the on chip SRMMU.  The io-unit and the srmmu do&n; * not need to have the same translations at all, in fact most&n; * of the time the translations they handle are a disjunct set.&n; * Basically the io-unit handles all dvma sbus activity.&n; */
multiline_comment|/* AIEEE, unlike the nice sun4m, these monsters have &n;   fixed DMA range 64M */
DECL|macro|IOUNIT_DMA_BASE
mdefine_line|#define IOUNIT_DMA_BASE&t;    0xfc000000 /* TOP - 64M */
DECL|macro|IOUNIT_DMA_SIZE
mdefine_line|#define IOUNIT_DMA_SIZE&t;    0x04000000 /* 64M */
multiline_comment|/* We use last 1M for sparc_dvma_malloc */
DECL|macro|IOUNIT_DVMA_SIZE
mdefine_line|#define IOUNIT_DVMA_SIZE    0x00100000 /* 1M */
multiline_comment|/* The format of an iopte in the external page tables */
DECL|macro|IOUPTE_PAGE
mdefine_line|#define IOUPTE_PAGE          0xffffff00 /* Physical page number (PA[35:12]) */
DECL|macro|IOUPTE_CACHE
mdefine_line|#define IOUPTE_CACHE         0x00000080 /* Cached (in Viking/MXCC) */
DECL|macro|IOUPTE_STREAM
mdefine_line|#define IOUPTE_STREAM        0x00000040
DECL|macro|IOUPTE_INTRA
mdefine_line|#define IOUPTE_INTRA&t;     0x00000008 /* Not regular memory - probably direct sbus&lt;-&gt;sbus dma &n;&t;&t;&t;&t;&t;   FIXME: Play with this and find out how we can make use of this */
DECL|macro|IOUPTE_WRITE
mdefine_line|#define IOUPTE_WRITE         0x00000004 /* Writeable */
DECL|macro|IOUPTE_VALID
mdefine_line|#define IOUPTE_VALID         0x00000002 /* IOPTE is valid */
DECL|macro|IOUPTE_PARITY
mdefine_line|#define IOUPTE_PARITY        0x00000001
DECL|struct|iounit_struct
r_struct
id|iounit_struct
(brace
DECL|member|bmap
r_int
r_int
id|bmap
(braket
(paren
id|IOUNIT_DMA_SIZE
op_rshift
(paren
id|PAGE_SHIFT
op_plus
l_int|3
)paren
)paren
op_div
r_sizeof
(paren
r_int
r_int
)paren
)braket
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|page_table
id|iopte_t
op_star
id|page_table
suffix:semicolon
DECL|member|rotor
r_int
r_int
id|rotor
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|limit
r_int
r_int
id|limit
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IOUNIT_BMAP1_START
mdefine_line|#define IOUNIT_BMAP1_START&t;0x00000000
DECL|macro|IOUNIT_BMAP1_END
mdefine_line|#define IOUNIT_BMAP1_END&t;(IOUNIT_DMA_SIZE &gt;&gt; (PAGE_SHIFT + 1))
DECL|macro|IOUNIT_BMAP2_START
mdefine_line|#define IOUNIT_BMAP2_START&t;IOUNIT_BMAP1_END
DECL|macro|IOUNIT_BMAP2_END
mdefine_line|#define IOUNIT_BMAP2_END&t;IOUNIT_BMAP2_START + (IOUNIT_DMA_SIZE &gt;&gt; (PAGE_SHIFT + 2))
DECL|macro|IOUNIT_BMAPM_START
mdefine_line|#define IOUNIT_BMAPM_START&t;IOUNIT_BMAP2_END
DECL|macro|IOUNIT_BMAPM_END
mdefine_line|#define IOUNIT_BMAPM_END&t;((IOUNIT_DMA_SIZE - IOUNIT_DVMA_SIZE) &gt;&gt; PAGE_SHIFT)
macro_line|#endif /* !(_SPARC_IO_UNIT_H) */
eof
