macro_line|#ifndef __ASM_SH_PAGE_H
DECL|macro|__ASM_SH_PAGE_H
mdefine_line|#define __ASM_SH_PAGE_H
multiline_comment|/*&n; * Copyright (C) 1999  Niibe Yutaka&n; */
multiline_comment|/*&n;   [ P0/U0 (virtual) ]&t;&t;0x00000000     &lt;------ User space&n;   [ P1 (fixed)   cached ]&t;0x80000000     &lt;------ Kernel space&n;   [ P2 (fixed)  non-cachable]&t;0xA0000000     &lt;------ Physical access&n;   [ P3 (virtual) cached]&t;0xC0000000     &lt;------ not used&n;   [ P4 control   ]&t;&t;0xE0000000&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;memset((void *)(page), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)&t;memcpy((void *)(to), (void *)(from), PAGE_SIZE)
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
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/*&n; * IF YOU CHANGE THIS, PLEASE ALSO CHANGE&n; *&n; *&t;arch/sh/vmlinux.lds.S&n; *&n; * which has the same constant encoded..&n; */
DECL|macro|__MEMORY_START
mdefine_line|#define __MEMORY_START&t;&t;CONFIG_MEMORY_START
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;(0x80000000)
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;((unsigned long)(x)-PAGE_OFFSET)
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)((unsigned long)(x)+PAGE_OFFSET))
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr)&t;&t;((__pa(addr)-__MEMORY_START) &gt;&gt; PAGE_SHIFT)
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
id|console_loglevel
suffix:semicolon
multiline_comment|/*&n; * Tell the user there is some problem.&n; */
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;asm volatile(&quot;nop&quot;); &bslash;&n;} while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { &bslash;&n;&t;BUG(); &bslash;&n;} while (0)
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_SH_PAGE_H */
eof
