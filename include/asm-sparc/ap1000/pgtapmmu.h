multiline_comment|/*&n;   * Copyright 1996 The Australian National University.&n;   * Copyright 1996 Fujitsu Laboratories Limited&n;   * &n;   * This software may be distributed under the terms of the Gnu&n;   * Public License version 2 or later&n;  */
multiline_comment|/* &n; * based on pgtsrmmu.h&n; *&n; */
macro_line|#ifndef _SPARC_PGTAPMMU_H
DECL|macro|_SPARC_PGTAPMMU_H
mdefine_line|#define _SPARC_PGTAPMMU_H
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/ap1000/apreg.h&gt;
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|APMMU_PMD_SHIFT
mdefine_line|#define APMMU_PMD_SHIFT         18
DECL|macro|APMMU_PMD_SIZE
mdefine_line|#define APMMU_PMD_SIZE          (1UL &lt;&lt; APMMU_PMD_SHIFT)
DECL|macro|APMMU_PMD_MASK
mdefine_line|#define APMMU_PMD_MASK          (~(APMMU_PMD_SIZE-1))
DECL|macro|APMMU_PMD_ALIGN
mdefine_line|#define APMMU_PMD_ALIGN(addr)   (((addr)+APMMU_PMD_SIZE-1)&amp;APMMU_PMD_MASK)
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|APMMU_PGDIR_SHIFT
mdefine_line|#define APMMU_PGDIR_SHIFT       24
DECL|macro|APMMU_PGDIR_SIZE
mdefine_line|#define APMMU_PGDIR_SIZE        (1UL &lt;&lt; APMMU_PGDIR_SHIFT)
DECL|macro|APMMU_PGDIR_MASK
mdefine_line|#define APMMU_PGDIR_MASK        (~(APMMU_PGDIR_SIZE-1))
DECL|macro|APMMU_PGDIR_ALIGN
mdefine_line|#define APMMU_PGDIR_ALIGN(addr) (((addr)+APMMU_PGDIR_SIZE-1)&amp;APMMU_PGDIR_MASK)
DECL|macro|APMMU_PTRS_PER_PTE
mdefine_line|#define APMMU_PTRS_PER_PTE      64
DECL|macro|APMMU_PTRS_PER_PMD
mdefine_line|#define APMMU_PTRS_PER_PMD      64
DECL|macro|APMMU_PTRS_PER_PGD
mdefine_line|#define APMMU_PTRS_PER_PGD      256
DECL|macro|APMMU_PTE_TABLE_SIZE
mdefine_line|#define APMMU_PTE_TABLE_SIZE    0x100 /* 64 entries, 4 bytes a piece */
DECL|macro|APMMU_PMD_TABLE_SIZE
mdefine_line|#define APMMU_PMD_TABLE_SIZE    0x100 /* 64 entries, 4 bytes a piece */
DECL|macro|APMMU_PGD_TABLE_SIZE
mdefine_line|#define APMMU_PGD_TABLE_SIZE    0x400 /* 256 entries, 4 bytes a piece */
DECL|macro|APMMU_VMALLOC_START
mdefine_line|#define APMMU_VMALLOC_START   (0xfe300000)
multiline_comment|/* Definition of the values in the ET field of PTD&squot;s and PTE&squot;s */
DECL|macro|APMMU_ET_MASK
mdefine_line|#define APMMU_ET_MASK         0x3
DECL|macro|APMMU_ET_INVALID
mdefine_line|#define APMMU_ET_INVALID      0x0
DECL|macro|APMMU_ET_PTD
mdefine_line|#define APMMU_ET_PTD          0x1
DECL|macro|APMMU_ET_PTE
mdefine_line|#define APMMU_ET_PTE          0x2
DECL|macro|APMMU_ET_REPTE
mdefine_line|#define APMMU_ET_REPTE        0x3 /* AIEEE, SuperSparc II reverse endian page! */
multiline_comment|/* Physical page extraction from PTP&squot;s and PTE&squot;s. */
DECL|macro|APMMU_CTX_PMASK
mdefine_line|#define APMMU_CTX_PMASK    0xfffffff0
DECL|macro|APMMU_PTD_PMASK
mdefine_line|#define APMMU_PTD_PMASK    0xfffffff0
DECL|macro|APMMU_PTE_PMASK
mdefine_line|#define APMMU_PTE_PMASK    0xffffff00
multiline_comment|/* The pte non-page bits.  Some notes:&n; * 1) cache, dirty, valid, and ref are frobbable&n; *    for both supervisor and user pages.&n; * 2) exec and write will only give the desired effect&n; *    on user pages&n; * 3) use priv and priv_readonly for changing the&n; *    characteristics of supervisor ptes&n; */
DECL|macro|APMMU_CACHE
mdefine_line|#define APMMU_CACHE        0x80
DECL|macro|APMMU_DIRTY
mdefine_line|#define APMMU_DIRTY        0x40
DECL|macro|APMMU_REF
mdefine_line|#define APMMU_REF          0x20
DECL|macro|APMMU_EXEC
mdefine_line|#define APMMU_EXEC         0x08
DECL|macro|APMMU_WRITE
mdefine_line|#define APMMU_WRITE        0x04
DECL|macro|APMMU_VALID
mdefine_line|#define APMMU_VALID        0x02 /* APMMU_ET_PTE */
DECL|macro|APMMU_PRIV
mdefine_line|#define APMMU_PRIV         0x1c
DECL|macro|APMMU_PRIV_RDONLY
mdefine_line|#define APMMU_PRIV_RDONLY  0x18
DECL|macro|APMMU_CHG_MASK
mdefine_line|#define APMMU_CHG_MASK    (0xffffff00 | APMMU_REF | APMMU_DIRTY)
multiline_comment|/*&n; * &quot;normal&quot; sun systems have their memory on bus 0. This means the top&n; * 4 bits of 36 bit physical addresses are 0. We use this define to&n; * determine if a piece of memory might be normal memory, or if its&n; * definately some sort of device memory.  &n; *&n; * On the AP+ normal memory is on bus 8. Why? Ask Fujitsu :-)&n;*/
DECL|macro|MEM_BUS_SPACE
mdefine_line|#define MEM_BUS_SPACE 8
multiline_comment|/* Some day I will implement true fine grained access bits for&n; * user pages because the APMMU gives us the capabilities to&n; * enforce all the protection levels that vma&squot;s can have.&n; * XXX But for now...&n; */
DECL|macro|APMMU_PAGE_NONE
mdefine_line|#define APMMU_PAGE_NONE    __pgprot((MEM_BUS_SPACE&lt;&lt;28) | &bslash;&n;&t;&t;&t;&t;    APMMU_VALID | APMMU_CACHE | &bslash;&n;&t;&t;&t;&t;    APMMU_PRIV | APMMU_REF)
DECL|macro|APMMU_PAGE_SHARED
mdefine_line|#define APMMU_PAGE_SHARED  __pgprot((MEM_BUS_SPACE&lt;&lt;28) | &bslash;&n;&t;&t;&t;&t;    APMMU_VALID | APMMU_CACHE | &bslash;&n;&t;&t;&t;&t;    APMMU_EXEC | APMMU_WRITE | APMMU_REF)
DECL|macro|APMMU_PAGE_COPY
mdefine_line|#define APMMU_PAGE_COPY    __pgprot((MEM_BUS_SPACE&lt;&lt;28) | &bslash;&n;&t;&t;&t;&t;    APMMU_VALID | APMMU_CACHE | &bslash;&n;&t;&t;&t;&t;    APMMU_EXEC | APMMU_REF)
DECL|macro|APMMU_PAGE_RDONLY
mdefine_line|#define APMMU_PAGE_RDONLY  __pgprot((MEM_BUS_SPACE&lt;&lt;28) | &bslash;&n;&t;&t;&t;&t;    APMMU_VALID | APMMU_CACHE | &bslash;&n;&t;&t;&t;&t;    APMMU_EXEC | APMMU_REF)
DECL|macro|APMMU_PAGE_KERNEL
mdefine_line|#define APMMU_PAGE_KERNEL  __pgprot((MEM_BUS_SPACE&lt;&lt;28) | &bslash;&n;&t;&t;&t;&t;    APMMU_VALID | APMMU_CACHE | APMMU_PRIV | &bslash;&n;&t;&t;&t;&t;    APMMU_DIRTY | APMMU_REF)
DECL|macro|APMMU_CTXTBL_PTR
mdefine_line|#define APMMU_CTXTBL_PTR         0x00000100
DECL|macro|APMMU_CTX_REG
mdefine_line|#define APMMU_CTX_REG            0x00000200
DECL|function|apmmu_get_ctable_ptr
r_extern
id|__inline__
r_int
r_int
id|apmmu_get_ctable_ptr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|APMMU_CTXTBL_PTR
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
r_return
(paren
id|retval
op_amp
id|APMMU_CTX_PMASK
)paren
op_lshift
l_int|4
suffix:semicolon
)brace
DECL|function|apmmu_set_context
r_extern
id|__inline__
r_void
id|apmmu_set_context
c_func
(paren
r_int
id|context
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %0, [%1] %2&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|context
)paren
comma
l_string|&quot;r&quot;
(paren
id|APMMU_CTX_REG
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/* The AP1000+ message controller also needs to know&n;&t;   the current task&squot;s context. */
id|MSC_OUT
c_func
(paren
id|MSC_PID
comma
id|context
)paren
suffix:semicolon
)brace
DECL|function|apmmu_get_context
r_extern
id|__inline__
r_int
id|apmmu_get_context
c_func
(paren
r_void
)paren
(brace
r_register
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|APMMU_CTX_REG
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC_PGTAPMMU_H) */
eof
