multiline_comment|/* $Id: pgtsun4c.h,v 1.16 1995/11/25 02:32:28 davem Exp $&n; * pgtsun4c.h:  Sun4c specific pgtable.h defines and code.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_PGTSUN4C_H
DECL|macro|_SPARC_PGTSUN4C_H
mdefine_line|#define _SPARC_PGTSUN4C_H
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
mdefine_line|#define SUN4C_REAL_PGDIR_SHIFT  18
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
mdefine_line|#define SUN4C_VMALLOC_START   (0xfe100000)
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
DECL|macro|_SUN4C_PAGE_COW
mdefine_line|#define _SUN4C_PAGE_COW       0x00800000   /* COW page */
multiline_comment|/* Note that the &squot;non-cacheable&squot; bit is not set in any of these settings,&n; * you may want to turn it on for debugging the flushing of the virtual&n; * cache on the SUN4C MMU.&n; */
DECL|macro|_SUN4C_PAGE_CHG_MASK
mdefine_line|#define _SUN4C_PAGE_CHG_MASK  (0xffff | _SUN4C_PAGE_REF | _SUN4C_PAGE_DIRTY)
DECL|macro|SUN4C_PAGE_NONE
mdefine_line|#define SUN4C_PAGE_NONE     __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_PRIV | &bslash;&n;&t;&t;&t;&t;     _SUN4C_PAGE_REF)
DECL|macro|SUN4C_PAGE_SHARED
mdefine_line|#define SUN4C_PAGE_SHARED   __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_WRITE | &bslash;&n;&t;&t;&t;&t;     _SUN4C_PAGE_USER | _SUN4C_PAGE_REF)
DECL|macro|SUN4C_PAGE_COPY
mdefine_line|#define SUN4C_PAGE_COPY     __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_USER | &bslash;&n;&t;&t;&t;&t;     _SUN4C_PAGE_REF | _SUN4C_PAGE_COW)
DECL|macro|SUN4C_PAGE_READONLY
mdefine_line|#define SUN4C_PAGE_READONLY __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_USER | &bslash;&n;&t;&t;&t;&t;     _SUN4C_PAGE_REF)
DECL|macro|SUN4C_PAGE_KERNEL
mdefine_line|#define SUN4C_PAGE_KERNEL   __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_WRITE | &bslash;&n;&t;&t;&t;&t;     _SUN4C_PAGE_PRIV | _SUN4C_PAGE_DIRTY | &bslash;&n;&t;&t;&t;&t;     _SUN4C_PAGE_REF)
DECL|macro|SUN4C_PAGE_INVALID
mdefine_line|#define SUN4C_PAGE_INVALID  __pgprot(0)
DECL|struct|pseg_list
r_struct
id|pseg_list
(brace
DECL|member|next
r_struct
id|pseg_list
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|pseg_list
op_star
id|prev
suffix:semicolon
DECL|member|ctx_next
r_struct
id|pseg_list
op_star
id|ctx_next
suffix:semicolon
DECL|member|ctx_prev
r_struct
id|pseg_list
op_star
id|ctx_prev
suffix:semicolon
DECL|member|vaddr
r_int
r_int
id|vaddr
suffix:semicolon
multiline_comment|/* Where the pseg is mapped. */
DECL|member|context
r_int
r_char
id|context
suffix:semicolon
multiline_comment|/* The context in which it is mapped. */
DECL|member|pseg
r_int
r_char
id|pseg
suffix:semicolon
multiline_comment|/* The pseg itself. */
DECL|member|ref_cnt
r_int
id|ref_cnt
suffix:colon
l_int|21
comma
DECL|member|hardlock
id|hardlock
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_char
op_star
id|sun4c_lockarea
c_func
(paren
r_char
op_star
id|vaddr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|sun4c_unlockarea
c_func
(paren
r_char
op_star
id|vaddr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
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
macro_line|#endif /* !(_SPARC_PGTSUN4C_H) */
eof
