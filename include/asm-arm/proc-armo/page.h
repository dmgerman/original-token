multiline_comment|/*&n; * linux/include/asm-arm/proc-armo/page.h&n; *&n; * Copyright (C) 1995, 1996 Russell King&n; */
macro_line|#ifndef __ASM_PROC_PAGE_H
DECL|macro|__ASM_PROC_PAGE_H
mdefine_line|#define __ASM_PROC_PAGE_H
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;15
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE       (1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK       (~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
DECL|macro|STRICT_MM_TYPECHECKS
mdefine_line|#define STRICT_MM_TYPECHECKS
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
DECL|macro|pte_val
mdefine_line|#define pte_val(x)      ((x).pte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)      ((x).pmd)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)      ((x).pgd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)   ((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)        ((pte_t) { (x) } )
DECL|macro|__pmd
mdefine_line|#define __pmd(x)        ((pmd_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)        ((pgd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)     ((pgprot_t) { (x) } )
macro_line|#else
multiline_comment|/*&n; * .. while these make it easier on the compiler&n; */
DECL|typedef|pte_t
r_typedef
r_int
r_int
id|pte_t
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
DECL|typedef|pgprot_t
r_typedef
r_int
r_int
id|pgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)      (x)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)      (x)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)      (x)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)   (x)
DECL|macro|__pte
mdefine_line|#define __pte(x)        (x)
DECL|macro|__pmd
mdefine_line|#define __pmd(x)        (x)
DECL|macro|__pgd
mdefine_line|#define __pgd(x)        (x)
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)     (x)
macro_line|#endif
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/* This handles the memory map.. */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;0x02000000
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr)&t;&t;(((unsigned long)(addr) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_PROC_PAGE_H */
eof
