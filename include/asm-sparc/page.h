multiline_comment|/* page.h:  Various defines and such for MMU operations on the Sparc for&n;            the Linux kernel.&n;&n;   Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n;*/
macro_line|#ifndef _SPARC_PAGE_H
DECL|macro|_SPARC_PAGE_H
mdefine_line|#define _SPARC_PAGE_H
macro_line|#include &lt;asm/asi.h&gt;        /* for get/set segmap/pte routines */
macro_line|#include &lt;asm/contregs.h&gt;   /* for switch_to_context */
multiline_comment|/* The current va context is global and known, so all that is needed to&n; * do an invalidate is flush the VAC.&n; */
DECL|macro|invalidate
mdefine_line|#define invalidate() flush_vac_context()  /* how conveeeiiiiinnnient :&gt; */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT   12             /* This is the virtual page... */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT  18             /* This is the virtual segment */
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE    4096
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE   (1UL &lt;&lt; PGDIR_SHIFT)
macro_line|#ifdef __KERNEL__
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR      (8*sizeof(unsigned long))   /* better check this stuff */
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK         (~(PAGE_SIZE-1))
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK        (~(PGDIR_SIZE-1))
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)  (((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
DECL|macro|PGDIR_ALIGN
mdefine_line|#define PGDIR_ALIGN(addr) (((addr)+PGDIR_SIZE-1)&amp;PGDIR_MASK)
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK          (~(sizeof(void*)-1))
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2   2
multiline_comment|/* The rest is kind of funky because on the sparc, the offsets into the mmu &n; * entries are encoded in magic alternate address space tables. I will &n; * probably find some nifty inline assembly routines to do the equivalent. &n; * Much thought must go into this code.   (davem@caip.rutgers.edu)&n; */
DECL|macro|PAGE_DIR_OFFSET
mdefine_line|#define PAGE_DIR_OFFSET(base, address)   ((void *) 0)
DECL|macro|PAGE_PTR
mdefine_line|#define PAGE_PTR(address)                ((void *) 0)
DECL|macro|PTRS_PER_PAGE
mdefine_line|#define PTRS_PER_PAGE                    (64)  /* 64 pte&squot;s per phys_seg */
multiline_comment|/* Bitfields within a Sparc sun4c PTE (page table entry). */
DECL|macro|PTE_V
mdefine_line|#define PTE_V     0x80000000   /* valid bit */
DECL|macro|PTE_ACC
mdefine_line|#define PTE_ACC   0x60000000   /* access bits */
DECL|macro|PTE_W
mdefine_line|#define PTE_W     0x40000000   /* writable bit */
DECL|macro|PTE_P
mdefine_line|#define PTE_P     0x20000000   /* privileged page */
DECL|macro|PTE_NC
mdefine_line|#define PTE_NC    0x10000000   /* page is non-cacheable */
DECL|macro|PTE_TYP
mdefine_line|#define PTE_TYP   0x0c000000   /* page type field */
DECL|macro|PTE_RMEM
mdefine_line|#define PTE_RMEM  0x00000000   /* type == on board real memory */
DECL|macro|PTE_IO
mdefine_line|#define PTE_IO    0x04000000   /* type == i/o area */
DECL|macro|PTE_VME16
mdefine_line|#define PTE_VME16 0x08000000   /* type == 16-bit VME area */
DECL|macro|PTE_VME32
mdefine_line|#define PTE_VME32 0x0c000000   /* type == 32-bit VME area */
DECL|macro|PTE_R
mdefine_line|#define PTE_R     0x02000000   /* page has been referenced */
DECL|macro|PTE_M
mdefine_line|#define PTE_M     0x01000000   /* page has been modified */
DECL|macro|PTE_RESV
mdefine_line|#define PTE_RESV  0x00f80000   /* reserved bits */
DECL|macro|PTE_PHYPG
mdefine_line|#define PTE_PHYPG 0x0007ffff   /* phys pg number, sun4c only uses 16bits */
multiline_comment|/* termed a &squot;page table&squot; in the linux kernel, a segmap entry is obtained&n; * with the following macro&n; */
macro_line|#ifndef __ASSEMBLY__ /* for head.S */
DECL|function|get_segmap
r_extern
id|__inline__
r_int
r_int
id|get_segmap
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
l_string|&quot;lduha [%1] 0x3, %0&quot;
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
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
DECL|function|put_segmap
r_extern
id|__inline__
r_void
id|put_segmap
c_func
(paren
r_int
r_int
op_star
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
l_string|&quot;stha %1, [%0] 0x3&quot;
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
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|get_pte
r_extern
id|__inline__
r_int
r_int
id|get_pte
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
l_string|&quot;lda [%1] 0x4, %0&quot;
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
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
DECL|function|put_pte
r_extern
id|__inline__
r_void
id|put_pte
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
l_string|&quot;sta %1, [%0] 0x4&quot;
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
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|switch_to_context
r_extern
id|__inline__
r_void
id|switch_to_context
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
l_string|&quot;stba %0, [%1] 0x2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|context
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0x30000000
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|get_context
r_extern
id|__inline__
r_int
id|get_context
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
l_string|&quot;lduba [%1] 0x2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ctx
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0x30000000
)paren
)paren
suffix:semicolon
r_return
id|ctx
suffix:semicolon
)brace
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _SPARC_PAGE_H */
eof
