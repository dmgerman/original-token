macro_line|#ifndef _ASM_IA64_PAGE_H
DECL|macro|_ASM_IA64_PAGE_H
mdefine_line|#define _ASM_IA64_PAGE_H
multiline_comment|/*&n; * Pagetable related stuff.&n; *&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/*&n; * PAGE_SHIFT determines the actual kernel page size.&n; */
macro_line|#if defined(CONFIG_IA64_PAGE_SIZE_4KB)
DECL|macro|PAGE_SHIFT
macro_line|# define PAGE_SHIFT&t;12
macro_line|#elif defined(CONFIG_IA64_PAGE_SIZE_8KB)
DECL|macro|PAGE_SHIFT
macro_line|# define PAGE_SHIFT&t;13
macro_line|#elif defined(CONFIG_IA64_PAGE_SIZE_16KB)
DECL|macro|PAGE_SHIFT
macro_line|# define PAGE_SHIFT&t;14
macro_line|#elif defined(CONFIG_IA64_PAGE_SIZE_64KB)
DECL|macro|PAGE_SHIFT
macro_line|# define PAGE_SHIFT&t;16
macro_line|#else
macro_line|# error Unsupported page size!
macro_line|#endif
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;&t;(__IA64_UL_CONST(1) &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;&t;(~(PAGE_SIZE - 1))
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr) + PAGE_SIZE - 1) &amp; PAGE_MASK)
macro_line|#ifdef __ASSEMBLY__
DECL|macro|__pa
macro_line|# define __pa(x)&t;&t;((x) - PAGE_OFFSET)
DECL|macro|__va
macro_line|# define __va(x)&t;&t;((x) + PAGE_OFFSET)
macro_line|#else /* !__ASSEMBLY */
macro_line|# ifdef __KERNEL__
DECL|macro|STRICT_MM_TYPECHECKS
macro_line|#  define STRICT_MM_TYPECHECKS
r_extern
r_void
id|clear_page
(paren
r_void
op_star
id|page
)paren
suffix:semicolon
r_extern
r_void
id|copy_page
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
)paren
suffix:semicolon
macro_line|#  ifdef STRICT_MM_TYPECHECKS
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
macro_line|#  else /* !STRICT_MM_TYPECHECKS */
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
macro_line|#  endif /* !STRICT_MM_TYPECHECKS */
multiline_comment|/*&n; * Note: the MAP_NR() macro can&squot;t use __pa() because MAP_NR(X) MUST&n; * map to something &gt;= max_mapnr if X is outside the identity mapped&n; * kernel space.&n; */
multiline_comment|/*&n; * The dense variant can be used as long as the size of memory holes isn&squot;t&n; * very big.&n; */
DECL|macro|MAP_NR_DENSE
mdefine_line|#define MAP_NR_DENSE(addr)&t;(((unsigned long) (addr) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT)
multiline_comment|/*&n; * This variant works well for the SGI SN1 architecture (which does have huge&n; * holes in the memory address space).&n; */
DECL|macro|MAP_NR_SN1
mdefine_line|#define MAP_NR_SN1(addr)&t;(((unsigned long) (addr) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT)
macro_line|#ifdef CONFIG_IA64_GENERIC
DECL|macro|MAP_NR
macro_line|# define MAP_NR(addr)&t;platform_map_nr(addr)
macro_line|#elif defined (CONFIG_IA64_SN_SN1_SIM)
DECL|macro|MAP_NR
macro_line|# define MAP_NR(addr)&t;MAP_NR_SN1(addr)
macro_line|#else
DECL|macro|MAP_NR
macro_line|# define MAP_NR(addr)&t;MAP_NR_DENSE(addr)
macro_line|#endif
macro_line|# endif /* __KERNEL__ */
DECL|union|ia64_va
r_typedef
r_union
id|ia64_va
(brace
r_struct
(brace
DECL|member|off
r_int
r_int
id|off
suffix:colon
l_int|61
suffix:semicolon
multiline_comment|/* intra-region offset */
DECL|member|reg
r_int
r_int
id|reg
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* region number */
DECL|member|f
)brace
id|f
suffix:semicolon
DECL|member|l
r_int
r_int
id|l
suffix:semicolon
DECL|member|p
r_void
op_star
id|p
suffix:semicolon
DECL|typedef|ia64_va
)brace
id|ia64_va
suffix:semicolon
multiline_comment|/*&n; * Note: These macros depend on the fact that PAGE_OFFSET has all&n; * region bits set to 1 and all other bits set to zero.  They are&n; * expressed in this way to ensure they result in a single &quot;dep&quot;&n; * instruction.&n; */
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;({ia64_va _v; _v.l = (long) (x); _v.f.reg = 0; _v.l;})
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;({ia64_va _v; _v.l = (long) (x); _v.f.reg = -1; _v.p;})
DECL|macro|BUG
mdefine_line|#define BUG() do { printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); *(int *)0=0; } while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { BUG(); } while (0)
macro_line|#endif /* !ASSEMBLY */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;0xe000000000000000
macro_line|#endif /* _ASM_IA64_PAGE_H */
eof
