macro_line|#ifndef _M68K_PAGE_H
DECL|macro|_M68K_PAGE_H
mdefine_line|#define _M68K_PAGE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/setup.h&gt;
DECL|macro|STRICT_MM_TYPECHECKS
mdefine_line|#define STRICT_MM_TYPECHECKS
DECL|macro|get_user_page
mdefine_line|#define get_user_page(vaddr)&t;__get_free_page(GFP_KERNEL)
DECL|macro|free_user_page
mdefine_line|#define free_user_page(page, addr)&t;free_page(addr)
multiline_comment|/*&n; * We don&squot;t need to check for alignment etc.&n; */
macro_line|#ifdef CPU_M68040_OR_M68060_ONLY
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
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;.chip 68040&bslash;n&bslash;t&quot;
l_string|&quot;move16 %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;move16 %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&bslash;n&bslash;t&quot;
l_string|&quot;dbra  %2,1b&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|to
)paren
comma
l_string|&quot;=a&quot;
(paren
id|from
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;2&quot;
(paren
id|PAGE_SIZE
op_div
l_int|32
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
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
id|data
comma
id|sp
comma
id|tmp
suffix:semicolon
id|sp
op_assign
id|page
suffix:semicolon
id|data
op_assign
l_int|0
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|page
)paren
)paren
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|page
)paren
)paren
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|page
)paren
)paren
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|page
)paren
)paren
op_increment
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;.chip 68040&bslash;n&bslash;t&quot;
l_string|&quot;move16 %2@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&bslash;n&bslash;t&quot;
l_string|&quot;subqw  #8,%2&bslash;n&bslash;t&quot;
l_string|&quot;subqw  #8,%2&bslash;n&bslash;t&quot;
l_string|&quot;dbra   %1,1b&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|page
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|sp
)paren
comma
l_string|&quot;0&quot;
(paren
id|page
)paren
comma
l_string|&quot;1&quot;
(paren
(paren
id|PAGE_SIZE
op_minus
l_int|16
)paren
op_div
l_int|16
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;memset((void *)(page), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)&t;memcpy((void *)(to), (void *)(from), PAGE_SIZE)
macro_line|#endif
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
(braket
l_int|16
)braket
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
mdefine_line|#define pmd_val(x)&t;((&amp;x)-&gt;pmd[0])
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;((pte_t) { (x) } )
DECL|macro|__pmd
mdefine_line|#define __pmd(x)&t;((pmd_t) { (x) } )
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
DECL|member|pmd
DECL|typedef|pmd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pmd
(braket
l_int|16
)braket
suffix:semicolon
)brace
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
mdefine_line|#define pmd_val(x)&t;((&amp;x)-&gt;pmd[0])
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;(x)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;(x)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;(x)
DECL|macro|__pmd
mdefine_line|#define __pmd(x)&t;((pmd_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;(x)
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;(x)
macro_line|#endif
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/* This handles the memory map.. */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;0
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;((unsigned long)(x)-PAGE_OFFSET)
multiline_comment|/*&n; * A hacky workaround for the problems with mmap() of frame buffer&n; * memory in the lower 16MB physical memoryspace.&n; *&n; * This is a short term solution, we will have to deal properly&n; * with this in 2.3.x.&n; */
DECL|function|__va
r_extern
r_inline
r_void
op_star
id|__va
c_func
(paren
r_int
r_int
id|physaddr
)paren
(brace
macro_line|#ifdef CONFIG_AMIGA
r_if
c_cond
(paren
id|MACH_IS_AMIGA
op_logical_and
(paren
id|physaddr
OL
l_int|16
op_star
l_int|1024
op_star
l_int|1024
)paren
)paren
r_return
(paren
r_void
op_star
)paren
l_int|0xffffffff
suffix:semicolon
r_else
macro_line|#endif
r_return
(paren
r_void
op_star
)paren
(paren
id|physaddr
op_plus
id|PAGE_OFFSET
)paren
suffix:semicolon
)brace
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr)&t;&t;(__pa(addr) &gt;&gt; PAGE_SHIFT)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _M68K_PAGE_H */
eof
