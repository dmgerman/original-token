multiline_comment|/* $Id: pgtsun4c.h,v 1.27 1996/10/30 06:01:32 davem Exp $&n; * pgtsun4c.h:  Sun4c specific pgtable.h defines and code.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_PGTSUN4C_H
DECL|macro|_SPARC_PGTSUN4C_H
mdefine_line|#define _SPARC_PGTSUN4C_H
macro_line|#include &lt;asm/contregs.h&gt;
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|SUN4C_PMD_SHIFT
mdefine_line|#define SUN4C_PMD_SHIFT       22
DECL|macro|SUN4C_PMD_SIZE
mdefine_line|#define SUN4C_PMD_SIZE        (1UL &lt;&lt; SUN4C_PMD_SHIFT)
DECL|macro|SUN4C_PMD_MASK
mdefine_line|#define SUN4C_PMD_MASK        (~(SUN4C_PMD_SIZE-1))
DECL|macro|SUN4C_PMD_ALIGN
mdefine_line|#define SUN4C_PMD_ALIGN(addr) (((addr)+SUN4C_PMD_SIZE-1)&amp;SUN4C_PMD_MASK)
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|SUN4C_PGDIR_SHIFT
mdefine_line|#define SUN4C_PGDIR_SHIFT       22
DECL|macro|SUN4C_PGDIR_SIZE
mdefine_line|#define SUN4C_PGDIR_SIZE        (1UL &lt;&lt; SUN4C_PGDIR_SHIFT)
DECL|macro|SUN4C_PGDIR_MASK
mdefine_line|#define SUN4C_PGDIR_MASK        (~(SUN4C_PGDIR_SIZE-1))
DECL|macro|SUN4C_PGDIR_ALIGN
mdefine_line|#define SUN4C_PGDIR_ALIGN(addr) (((addr)+SUN4C_PGDIR_SIZE-1)&amp;SUN4C_PGDIR_MASK)
multiline_comment|/* To represent how the sun4c mmu really lays things out. */
DECL|macro|SUN4C_REAL_PGDIR_SHIFT
mdefine_line|#define SUN4C_REAL_PGDIR_SHIFT       18
DECL|macro|SUN4C_REAL_PGDIR_SIZE
mdefine_line|#define SUN4C_REAL_PGDIR_SIZE        (1UL &lt;&lt; SUN4C_REAL_PGDIR_SHIFT)
DECL|macro|SUN4C_REAL_PGDIR_MASK
mdefine_line|#define SUN4C_REAL_PGDIR_MASK        (~(SUN4C_REAL_PGDIR_SIZE-1))
DECL|macro|SUN4C_REAL_PGDIR_ALIGN
mdefine_line|#define SUN4C_REAL_PGDIR_ALIGN(addr) (((addr)+SUN4C_REAL_PGDIR_SIZE-1)&amp;SUN4C_REAL_PGDIR_MASK)
multiline_comment|/*&n; * To be efficient, and not have to worry about allocating such&n; * a huge pgd, we make the kernel sun4c tables each hold 1024&n; * entries and the pgd similarly just like the i386 tables.&n; */
DECL|macro|SUN4C_PTRS_PER_PTE
mdefine_line|#define SUN4C_PTRS_PER_PTE    1024
DECL|macro|SUN4C_PTRS_PER_PMD
mdefine_line|#define SUN4C_PTRS_PER_PMD    1
DECL|macro|SUN4C_PTRS_PER_PGD
mdefine_line|#define SUN4C_PTRS_PER_PGD    1024
multiline_comment|/* On the sun4c the physical ram limit is 128MB.  We set up our I/O&n; * translations at KERNBASE + 128MB for 1MB, then we begin the VMALLOC&n; * area, makes sense.  This works out to the value below.&n; */
DECL|macro|SUN4C_VMALLOC_START
mdefine_line|#define SUN4C_VMALLOC_START   (0xfe300000)
multiline_comment|/*&n; * Sparc SUN4C pte fields.&n; */
DECL|macro|_SUN4C_PAGE_VALID
mdefine_line|#define _SUN4C_PAGE_VALID     0x80000000   /* valid page */
DECL|macro|_SUN4C_PAGE_WRITE
mdefine_line|#define _SUN4C_PAGE_WRITE     0x40000000   /* can be written to */
DECL|macro|_SUN4C_PAGE_PRIV
mdefine_line|#define _SUN4C_PAGE_PRIV      0x20000000   /* bit to signify privileged page */
DECL|macro|_SUN4C_PAGE_USER
mdefine_line|#define _SUN4C_PAGE_USER      0x00000000   /* User page */
DECL|macro|_SUN4C_PAGE_NOCACHE
mdefine_line|#define _SUN4C_PAGE_NOCACHE   0x10000000   /* non-cacheable page */
DECL|macro|_SUN4C_PAGE_IO
mdefine_line|#define _SUN4C_PAGE_IO        0x04000000   /* I/O page */
DECL|macro|_SUN4C_PAGE_REF
mdefine_line|#define _SUN4C_PAGE_REF       0x02000000   /* Page has been accessed/referenced */
DECL|macro|_SUN4C_PAGE_DIRTY
mdefine_line|#define _SUN4C_PAGE_DIRTY     0x01000000   /* Page has been modified, is dirty */
DECL|macro|_SUN4C_PAGE_PRESENT
mdefine_line|#define _SUN4C_PAGE_PRESENT   0x00400000   /* present (known) page */
DECL|macro|_SUN4C_PAGE_CHG_MASK
mdefine_line|#define _SUN4C_PAGE_CHG_MASK  (0xffff | _SUN4C_PAGE_REF | _SUN4C_PAGE_DIRTY)
DECL|macro|SUN4C_PAGE_NONE
mdefine_line|#define SUN4C_PAGE_NONE     __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_PRIV | &bslash;&n;&t;&t;&t;&t;     _SUN4C_PAGE_REF)
DECL|macro|SUN4C_PAGE_SHARED
mdefine_line|#define SUN4C_PAGE_SHARED   __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_WRITE | &bslash;&n;&t;&t;&t;&t;     _SUN4C_PAGE_USER | _SUN4C_PAGE_REF)
DECL|macro|SUN4C_PAGE_COPY
mdefine_line|#define SUN4C_PAGE_COPY     __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_USER | &bslash;&n;&t;&t;&t;&t;     _SUN4C_PAGE_REF)
DECL|macro|SUN4C_PAGE_READONLY
mdefine_line|#define SUN4C_PAGE_READONLY __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_USER | &bslash;&n;&t;&t;&t;&t;     _SUN4C_PAGE_REF)
DECL|macro|SUN4C_PAGE_KERNEL
mdefine_line|#define SUN4C_PAGE_KERNEL   __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_WRITE | &bslash;&n;&t;&t;&t;&t;     _SUN4C_PAGE_PRIV | _SUN4C_PAGE_DIRTY | &bslash;&n;&t;&t;&t;&t;     _SUN4C_PAGE_REF | _SUN4C_PAGE_NOCACHE)
DECL|function|sun4c_get_synchronous_error
r_extern
id|__inline__
r_int
r_int
id|sun4c_get_synchronous_error
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|sync_err
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sync_err
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|AC_SYNC_ERR
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_CONTROL
)paren
)paren
suffix:semicolon
r_return
id|sync_err
suffix:semicolon
)brace
DECL|function|sun4c_get_synchronous_address
r_extern
id|__inline__
r_int
r_int
id|sun4c_get_synchronous_address
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|sync_addr
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sync_addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|AC_SYNC_VA
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_CONTROL
)paren
)paren
suffix:semicolon
r_return
id|sync_addr
suffix:semicolon
)brace
multiline_comment|/* SUN4C pte, segmap, and context manipulation */
DECL|function|sun4c_get_segmap
r_extern
id|__inline__
r_int
r_int
id|sun4c_get_segmap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_register
r_int
r_int
id|entry
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;tlduba [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|entry
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_SEGMAP
)paren
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
DECL|function|sun4c_put_segmap
r_extern
id|__inline__
r_void
id|sun4c_put_segmap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|entry
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;tstba %1, [%0] %2&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|entry
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_SEGMAP
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|sun4c_get_pte
r_extern
id|__inline__
r_int
r_int
id|sun4c_get_pte
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_register
r_int
r_int
id|entry
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;tlda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|entry
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PTE
)paren
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
DECL|function|sun4c_put_pte
r_extern
id|__inline__
r_void
id|sun4c_put_pte
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|entry
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;tsta %1, [%0] %2&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|entry
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PTE
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|sun4c_get_context
r_extern
id|__inline__
r_int
id|sun4c_get_context
c_func
(paren
r_void
)paren
(brace
r_register
r_int
id|ctx
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;tlduba [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ctx
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|AC_CONTEXT
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_CONTROL
)paren
)paren
suffix:semicolon
r_return
id|ctx
suffix:semicolon
)brace
DECL|function|sun4c_set_context
r_extern
id|__inline__
r_int
id|sun4c_set_context
c_func
(paren
r_int
id|ctx
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;tstba %0, [%1] %2&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|ctx
)paren
comma
l_string|&quot;r&quot;
(paren
id|AC_CONTEXT
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_CONTROL
)paren
)paren
suffix:semicolon
r_return
id|ctx
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC_PGTSUN4C_H) */
eof
