multiline_comment|/* $Id: page.h,v 1.30 1996/10/27 08:55:30 davem Exp $&n; * page.h:  Various defines and such for MMU operations on the Sparc for&n; *          the Linux kernel.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_PAGE_H
DECL|macro|_SPARC_PAGE_H
mdefine_line|#define _SPARC_PAGE_H
macro_line|#include &lt;asm/head.h&gt;       /* for KERNBASE */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT   12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE    (1 &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK    (~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;memset((void *)(page), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)&t;memcpy((void *)(to), (void *)(from), PAGE_SIZE)
r_extern
r_int
r_int
id|page_offset
suffix:semicolon
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET  (page_offset)
multiline_comment|/* translate between physical and virtual addresses */
r_extern
r_int
r_int
(paren
op_star
id|mmu_v2p
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
(paren
op_star
id|mmu_p2v
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|__pa
mdefine_line|#define __pa(x)    mmu_v2p(x)
DECL|macro|__va
mdefine_line|#define __va(x)    mmu_p2v(x)
multiline_comment|/* The following structure is used to hold the physical&n; * memory configuration of the machine.  This is filled in&n; * probe_memory() and is later used by mem_init() to set up&n; * mem_map[].  We statically allocate SPARC_PHYS_BANKS of&n; * these structs, this is arbitrary.  The entry after the&n; * last valid one has num_bytes==0.&n; */
DECL|struct|sparc_phys_banks
r_struct
id|sparc_phys_banks
(brace
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|num_bytes
r_int
r_int
id|num_bytes
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SPARC_PHYS_BANKS
mdefine_line|#define SPARC_PHYS_BANKS 32
r_extern
r_struct
id|sparc_phys_banks
id|sp_banks
(braket
id|SPARC_PHYS_BANKS
)braket
suffix:semicolon
multiline_comment|/* Cache alias structure.  Entry is valid if context != -1. */
DECL|struct|cache_palias
r_struct
id|cache_palias
(brace
DECL|member|vaddr
r_int
r_int
id|vaddr
suffix:semicolon
DECL|member|context
r_int
id|context
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|cache_palias
op_star
id|sparc_aliases
suffix:semicolon
multiline_comment|/* passing structs on the Sparc slow us down tremendously... */
multiline_comment|/* #define STRICT_MM_TYPECHECKS */
macro_line|#ifdef STRICT_MM_TYPECHECKS
multiline_comment|/*&n; * These are used to make use of C type-checking..&n; */
DECL|member|pte
DECL|typedef|pte_t
r_typedef
r_struct
(brace
r_int
r_int
id|pte
suffix:semicolon
)brace
id|pte_t
suffix:semicolon
DECL|member|iopte
DECL|typedef|iopte_t
r_typedef
r_struct
(brace
r_int
r_int
id|iopte
suffix:semicolon
)brace
id|iopte_t
suffix:semicolon
DECL|member|pmd
DECL|typedef|pmd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pmd
suffix:semicolon
)brace
id|pmd_t
suffix:semicolon
DECL|member|pgd
DECL|typedef|pgd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgd
suffix:semicolon
)brace
id|pgd_t
suffix:semicolon
DECL|member|ctxd
DECL|typedef|ctxd_t
r_typedef
r_struct
(brace
r_int
r_int
id|ctxd
suffix:semicolon
)brace
id|ctxd_t
suffix:semicolon
DECL|member|pgprot
DECL|typedef|pgprot_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgprot
suffix:semicolon
)brace
id|pgprot_t
suffix:semicolon
DECL|member|iopgprot
DECL|typedef|iopgprot_t
r_typedef
r_struct
(brace
r_int
r_int
id|iopgprot
suffix:semicolon
)brace
id|iopgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;((x).pte)
DECL|macro|iopte_val
mdefine_line|#define iopte_val(x)&t;((x).iopte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)      ((x).pmd)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|ctxd_val
mdefine_line|#define ctxd_val(x)&t;((x).ctxd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|iopgprot_val
mdefine_line|#define iopgprot_val(x)&t;((x).iopgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;((pte_t) { (x) } )
DECL|macro|__iopte
mdefine_line|#define __iopte(x)&t;((iopte_t) { (x) } )
DECL|macro|__pmd
mdefine_line|#define __pmd(x)        ((pmd_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;((pgd_t) { (x) } )
DECL|macro|__ctxd
mdefine_line|#define __ctxd(x)&t;((ctxd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
DECL|macro|__iopgprot
mdefine_line|#define __iopgprot(x)&t;((iopgprot_t) { (x) } )
macro_line|#else
multiline_comment|/*&n; * .. while these make it easier on the compiler&n; */
DECL|typedef|pte_t
r_typedef
r_int
r_int
id|pte_t
suffix:semicolon
DECL|typedef|iopte_t
r_typedef
r_int
r_int
id|iopte_t
suffix:semicolon
DECL|typedef|pmd_t
r_typedef
r_int
r_int
id|pmd_t
suffix:semicolon
DECL|typedef|pgd_t
r_typedef
r_int
r_int
id|pgd_t
suffix:semicolon
DECL|typedef|ctxd_t
r_typedef
r_int
r_int
id|ctxd_t
suffix:semicolon
DECL|typedef|pgprot_t
r_typedef
r_int
r_int
id|pgprot_t
suffix:semicolon
DECL|typedef|iopgprot_t
r_typedef
r_int
r_int
id|iopgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;(x)
DECL|macro|iopte_val
mdefine_line|#define iopte_val(x)&t;(x)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)      (x)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;(x)
DECL|macro|ctxd_val
mdefine_line|#define ctxd_val(x)&t;(x)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;(x)
DECL|macro|iopgprot_val
mdefine_line|#define iopgprot_val(x)&t;(x)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;(x)
DECL|macro|__iopte
mdefine_line|#define __iopte(x)&t;(x)
DECL|macro|__pmd
mdefine_line|#define __pmd(x)        (x)
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;(x)
DECL|macro|__ctxd
mdefine_line|#define __ctxd(x)&t;(x)
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;(x)
DECL|macro|__iopgprot
mdefine_line|#define __iopgprot(x)&t;(x)
macro_line|#endif
r_extern
r_int
r_int
id|sparc_unmapped_base
suffix:semicolon
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(sparc_unmapped_base)
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)  (((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/* Now, to allow for very large physical memory configurations we&n; * place the page pool both above the kernel and below the kernel.&n; */
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr) ((((unsigned long) (addr)) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT)
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _SPARC_PAGE_H */
eof
