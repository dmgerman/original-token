macro_line|#ifndef __ASM_MIPS_PAGE_H
DECL|macro|__ASM_MIPS_PAGE_H
mdefine_line|#define __ASM_MIPS_PAGE_H
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
DECL|macro|STRICT_MM_TYPECHECKS
mdefine_line|#define STRICT_MM_TYPECHECKS
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
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
mdefine_line|#define pte_val(x)&t;((x).pte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;((x).pmd)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;((pte_t) { (x) } )
DECL|macro|__pme
mdefine_line|#define __pme(x)&t;((pme_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;((pgd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
macro_line|#else /* !defined (STRICT_MM_TYPECHECKS) */
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
mdefine_line|#define pte_val(x)&t;(x)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;(x)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;(x)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;(x)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;(x)
DECL|macro|__pmd
mdefine_line|#define __pmd(x)&t;(x)
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;(x)
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;(x)
macro_line|#endif /* !defined (STRICT_MM_TYPECHECKS) */
multiline_comment|/*&n; * We need a special version of copy_page that can handle virtual caches.&n; * While we&squot;re at tweaking with caches we can use that to make it even&n; * faster.  The R10000 accelerated caching mode will further accelerate it.&n; */
r_extern
r_void
id|__copy_page
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|to
)paren
suffix:semicolon
DECL|macro|copy_page
mdefine_line|#define copy_page(from,to) __copy_page((unsigned long)from, (unsigned long)to)
macro_line|#endif /* __LANGUAGE_ASSEMBLY__ */
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/* This handles the memory map */
macro_line|#if __mips == 3
multiline_comment|/*&n; * We handle pages at XKPHYS + 0x1800000000000000 (cachable, noncoherent)&n; * Pagetables are at  XKPHYS + 0x1000000000000000 (uncached)&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;0x9800000000000000UL
DECL|macro|PT_OFFSET
mdefine_line|#define PT_OFFSET&t;0x9000000000000000UL
DECL|macro|MAP_MASK
mdefine_line|#define MAP_MASK        0x07ffffffffffffffUL
macro_line|#else
multiline_comment|/*&n; * We handle pages at KSEG0 (cachable, noncoherent)&n; * Pagetables are at  KSEG1 (uncached)&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;0x80000000
DECL|macro|PT_OFFSET
mdefine_line|#define PT_OFFSET&t;0xa0000000
DECL|macro|MAP_MASK
mdefine_line|#define MAP_MASK        0x1fffffff
macro_line|#endif
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr)&t;((((unsigned long)(addr)) &amp; MAP_MASK) &gt;&gt; PAGE_SHIFT)
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
r_extern
r_int
r_int
id|page_colour_mask
suffix:semicolon
r_extern
r_inline
r_int
r_int
DECL|function|page_colour
id|page_colour
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_return
id|page
op_amp
id|page_colour_mask
suffix:semicolon
)brace
macro_line|#endif /* defined (__LANGUAGE_ASSEMBLY__) */
macro_line|#endif /* defined (__KERNEL__) */
macro_line|#endif /* __ASM_MIPS_PAGE_H */
eof
