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
multiline_comment|/*&n; * A _lot_ of the kernel time is spent clearing pages, so&n; * do this as fast as we possibly can. Also, doing this&n; * as a separate inline function (rather than memset())&n; * results in clearer kernel profiles as we see _who_ is&n; * doing page clearing or copying.&n; */
DECL|function|clear_page
r_static
r_inline
r_void
id|clear_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|count
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.align 4&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;stq $31,0(%1)&bslash;n&bslash;t&quot;
l_string|&quot;stq $31,8(%1)&bslash;n&bslash;t&quot;
l_string|&quot;stq $31,16(%1)&bslash;n&bslash;t&quot;
l_string|&quot;stq $31,24(%1)&bslash;n&bslash;t&quot;
l_string|&quot;subq %0,1,%0&bslash;n&bslash;t&quot;
l_string|&quot;stq $31,32(%1)&bslash;n&bslash;t&quot;
l_string|&quot;stq $31,40(%1)&bslash;n&bslash;t&quot;
l_string|&quot;stq $31,48(%1)&bslash;n&bslash;t&quot;
l_string|&quot;stq $31,56(%1)&bslash;n&bslash;t&quot;
l_string|&quot;addq $1,64,$1&bslash;n&bslash;t&quot;
l_string|&quot;bne %0,1b&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|count
)paren
comma
l_string|&quot;=r&quot;
(paren
id|page
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|PAGE_SIZE
op_div
l_int|64
)paren
comma
l_string|&quot;1&quot;
(paren
id|page
)paren
)paren
suffix:semicolon
)brace
DECL|function|copy_page
r_static
r_inline
r_void
id|copy_page
c_func
(paren
r_int
r_int
id|to
comma
r_int
r_int
id|from
)paren
(brace
r_int
r_int
id|count
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.align 4&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;ldq $0,0(%1)&bslash;n&bslash;t&quot;
l_string|&quot;ldq $1,8(%1)&bslash;n&bslash;t&quot;
l_string|&quot;ldq $2,16(%1)&bslash;n&bslash;t&quot;
l_string|&quot;ldq $3,24(%1)&bslash;n&bslash;t&quot;
l_string|&quot;ldq $4,32(%1)&bslash;n&bslash;t&quot;
l_string|&quot;ldq $5,40(%1)&bslash;n&bslash;t&quot;
l_string|&quot;ldq $6,48(%1)&bslash;n&bslash;t&quot;
l_string|&quot;ldq $7,56(%1)&bslash;n&bslash;t&quot;
l_string|&quot;subq %0,1,%0&bslash;n&bslash;t&quot;
l_string|&quot;addq %1,64,%1&bslash;n&bslash;t&quot;
l_string|&quot;stq $0,0(%2)&bslash;n&bslash;t&quot;
l_string|&quot;stq $1,8(%2)&bslash;n&bslash;t&quot;
l_string|&quot;stq $2,16(%2)&bslash;n&bslash;t&quot;
l_string|&quot;stq $3,24(%2)&bslash;n&bslash;t&quot;
l_string|&quot;stq $4,32(%2)&bslash;n&bslash;t&quot;
l_string|&quot;stq $5,40(%2)&bslash;n&bslash;t&quot;
l_string|&quot;stq $6,48(%2)&bslash;n&bslash;t&quot;
l_string|&quot;stq $7,56(%2)&bslash;n&bslash;t&quot;
l_string|&quot;addq %2,64,%2&bslash;n&bslash;t&quot;
l_string|&quot;bne %0,1b&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|count
)paren
comma
l_string|&quot;=r&quot;
(paren
id|from
)paren
comma
l_string|&quot;=r&quot;
(paren
id|to
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|PAGE_SIZE
op_div
l_int|64
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
id|to
)paren
suffix:colon
l_string|&quot;$0&quot;
comma
l_string|&quot;$1&quot;
comma
l_string|&quot;$2&quot;
comma
l_string|&quot;$3&quot;
comma
l_string|&quot;$4&quot;
comma
l_string|&quot;$5&quot;
comma
l_string|&quot;$6&quot;
comma
l_string|&quot;$7&quot;
)paren
suffix:semicolon
)brace
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
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;0xFFFFFC0000000000UL
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;((unsigned long) (x) - PAGE_OFFSET)
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)((unsigned long) (x) + PAGE_OFFSET))
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr)&t;&t;(__pa(addr) &gt;&gt; PAGE_SHIFT)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ALPHA_PAGE_H */
eof
