multiline_comment|/* iommu.h: Definitions for the sun5 IOMMU.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_IOMMU_H
DECL|macro|_SPARC64_IOMMU_H
mdefine_line|#define _SPARC64_IOMMU_H
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/sysio.h&gt;
multiline_comment|/* The iommu handles all virtual to physical address translations&n; * that occur between the SYSIO and physical memory.  Access by&n; * the cpu to IO registers and similar go over the UPA so are&n; * translated by the on chip TLB&squot;s.  The iommu and the TLB do&n; * not need to have the same translations at all, in fact most&n; * of the time the translations they handle are a disjoint set.&n; * Basically the iommu handles all SYSIO dvma translations.&n; */
multiline_comment|/* The IOMMU register set. */
DECL|macro|IOMMU_CTRL_IMPL
mdefine_line|#define IOMMU_CTRL_IMPL     0xf000000000000000 /* Implementation                */
DECL|macro|IOMMU_CTRL_VERS
mdefine_line|#define IOMMU_CTRL_VERS     0x0f00000000000000 /* Version                       */
DECL|macro|IOMMU_CTRL_TSBSZ
mdefine_line|#define IOMMU_CTRL_TSBSZ    0x0000000000070000 /* TSB Size                      */
DECL|macro|IOMMU_TSBSZ_1K
mdefine_line|#define IOMMU_TSBSZ_1K      0x0000000000000000 /* TSB Table 1024 8-byte entries */
DECL|macro|IOMMU_TSBSZ_2K
mdefine_line|#define IOMMU_TSBSZ_2K      0x0000000000010000 /* TSB Table 2048 8-byte entries */
DECL|macro|IOMMU_TSBSZ_4K
mdefine_line|#define IOMMU_TSBSZ_4K      0x0000000000020000 /* TSB Table 4096 8-byte entries */
DECL|macro|IOMMU_TSBSZ_8K
mdefine_line|#define IOMMU_TSBSZ_8K      0x0000000000030000 /* TSB Table 8192 8-byte entries */
DECL|macro|IOMMU_TSBSZ_16K
mdefine_line|#define IOMMU_TSBSZ_16K     0x0000000000040000 /* TSB Table 16k 8-byte entries  */
DECL|macro|IOMMU_TSBSZ_32K
mdefine_line|#define IOMMU_TSBSZ_32K     0x0000000000050000 /* TSB Table 32k 8-byte entries  */
DECL|macro|IOMMU_TSBSZ_64K
mdefine_line|#define IOMMU_TSBSZ_64K     0x0000000000060000 /* TSB Table 64k 8-byte entries  */
DECL|macro|IOMMU_TSBSZ_128K
mdefine_line|#define IOMMU_TSBSZ_128K    0x0000000000070000 /* TSB Table 128k 8-byte entries */
DECL|macro|IOMMU_CTRL_TBWSZ
mdefine_line|#define IOMMU_CTRL_TBWSZ    0x0000000000000004 /* Assumed page size, 0=8k 1=64k */
DECL|macro|IOMMU_CTRL_DENAB
mdefine_line|#define IOMMU_CTRL_DENAB    0x0000000000000002 /* Diagnostic mode enable        */
DECL|macro|IOMMU_CTRL_ENAB
mdefine_line|#define IOMMU_CTRL_ENAB     0x0000000000000001 /* IOMMU Enable                  */
multiline_comment|/* The format of an iopte in the page tables, we only use 64k pages. */
DECL|macro|IOPTE_VALID
mdefine_line|#define IOPTE_VALID         0x8000000000000000 /* IOPTE is valid                   */
DECL|macro|IOPTE_64K
mdefine_line|#define IOPTE_64K           0x2000000000000000 /* IOPTE is for 64k page            */
DECL|macro|IOPTE_STBUF
mdefine_line|#define IOPTE_STBUF         0x1000000000000000 /* DVMA can use streaming buffer    */
DECL|macro|IOPTE_INTRA
mdefine_line|#define IOPTE_INTRA         0x0800000000000000 /* SBUS slot--&gt;slot direct transfer */
DECL|macro|IOPTE_CONTEXT
mdefine_line|#define IOPTE_CONTEXT&t;    0x07ff800000000000 /* Context number&t;&t;   */
DECL|macro|IOPTE_PAGE
mdefine_line|#define IOPTE_PAGE          0x00007fffffffe000 /* Physical page number (PA[40:13]) */
DECL|macro|IOPTE_CACHE
mdefine_line|#define IOPTE_CACHE         0x0000000000000010 /* Cached (in UPA E-cache)          */
DECL|macro|IOPTE_WRITE
mdefine_line|#define IOPTE_WRITE         0x0000000000000002 /* Writeable                        */
DECL|struct|iommu_struct
r_struct
id|iommu_struct
(brace
DECL|member|sysio_regs
r_struct
id|sysio_regs
op_star
id|sysio_regs
suffix:semicolon
DECL|member|page_table
id|iopte_t
op_star
id|page_table
suffix:semicolon
DECL|member|flushflag
r_volatile
r_int
r_int
id|flushflag
suffix:semicolon
DECL|member|strbuf_enabled
r_int
r_int
id|strbuf_enabled
suffix:semicolon
DECL|member|iommu_lock
id|spinlock_t
id|iommu_lock
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !(_SPARC_IOMMU_H) */
eof
