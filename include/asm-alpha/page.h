macro_line|#ifndef _ALPHA_PAGE_H
DECL|macro|_ALPHA_PAGE_H
mdefine_line|#define _ALPHA_PAGE_H
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;13
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
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
mdefine_line|#define pte_val(x)&t;((x).pte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;((x).pmd)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;((pte_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;((pgd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
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
mdefine_line|#define pte_val(x)&t;(x)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;(x)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;(x)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;(x)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;(x)
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;(x)
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;(x)
macro_line|#endif
DECL|macro|invalidate_all
mdefine_line|#define invalidate_all() &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;lda $16,-2($31)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.long 51&quot; &bslash;&n;&t;: : :&quot;$1&quot;, &quot;$16&quot;, &quot;$17&quot;, &quot;$22&quot;,&quot;$23&quot;,&quot;$24&quot;,&quot;$25&quot;)
DECL|macro|invalidate
mdefine_line|#define invalidate() &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;lda $16,-1($31)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.long 51&quot; &bslash;&n;&t;: : :&quot;$1&quot;, &quot;$16&quot;, &quot;$17&quot;, &quot;$22&quot;,&quot;$23&quot;,&quot;$24&quot;,&quot;$25&quot;)
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval) ((*(pteptr)) = (pteval))
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;0xFFFFFC0000000000
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr)&t;&t;((((unsigned long) (addr)) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ALPHA_PAGE_H */
eof
