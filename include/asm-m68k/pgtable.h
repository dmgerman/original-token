macro_line|#ifndef _M68K_PGTABLE_H
DECL|macro|_M68K_PGTABLE_H
mdefine_line|#define _M68K_PGTABLE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
multiline_comment|/*&n; * This file contains the functions and defines necessary to modify and use&n; * the m68k page table tree.&n; */
macro_line|#include &lt;asm/virtconvert.h&gt;
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval)&t;&t;&t;&t;&t;&bslash;&n;&t;do{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*(pteptr) = (pteval);&t;&t;&t;&t;&bslash;&n;&t;} while(0)
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;22
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;25
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/*&n; * entries per page directory level: the m68k is configured as three-level,&n; * so we do have PMD level physically.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;1024
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;8
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;128
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE/PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
multiline_comment|/* Virtual address region for use by kernel_map() */
DECL|macro|KMAP_START
mdefine_line|#define&t;KMAP_START&t;0xd0000000
DECL|macro|KMAP_END
mdefine_line|#define&t;KMAP_END&t;0xf0000000
multiline_comment|/* Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET&t;(8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START (((unsigned long) high_memory + VMALLOC_OFFSET) &amp; ~(VMALLOC_OFFSET-1))
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END KMAP_START
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * Definitions for MMU descriptors&n; */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x001
DECL|macro|_PAGE_SHORT
mdefine_line|#define _PAGE_SHORT&t;0x002
DECL|macro|_PAGE_RONLY
mdefine_line|#define _PAGE_RONLY&t;0x004
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x008
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x010
DECL|macro|_PAGE_SUPER
mdefine_line|#define _PAGE_SUPER&t;0x080&t;/* 68040 supervisor only */
DECL|macro|_PAGE_FAKE_SUPER
mdefine_line|#define _PAGE_FAKE_SUPER 0x200&t;/* fake supervisor only on 680[23]0 */
DECL|macro|_PAGE_GLOBAL040
mdefine_line|#define _PAGE_GLOBAL040&t;0x400&t;/* 68040 global bit, used for kva descs */
DECL|macro|_PAGE_COW
mdefine_line|#define _PAGE_COW&t;0x800&t;/* implemented in software */
DECL|macro|_PAGE_NOCACHE030
mdefine_line|#define _PAGE_NOCACHE030 0x040&t;/* 68030 no-cache mode */
DECL|macro|_PAGE_NOCACHE
mdefine_line|#define _PAGE_NOCACHE&t;0x060&t;/* 68040 cache mode, non-serialized */
DECL|macro|_PAGE_NOCACHE_S
mdefine_line|#define _PAGE_NOCACHE_S&t;0x040&t;/* 68040 no-cache mode, serialized */
DECL|macro|_PAGE_CACHE040
mdefine_line|#define _PAGE_CACHE040&t;0x020&t;/* 68040 cache mode, cachable, copyback */
DECL|macro|_PAGE_CACHE040W
mdefine_line|#define _PAGE_CACHE040W&t;0x000&t;/* 68040 cache mode, cachable, write-through */
multiline_comment|/* Page protection values within PTE. */
DECL|macro|SUN3_PAGE_VALID
mdefine_line|#define SUN3_PAGE_VALID     (0x80000000)
DECL|macro|SUN3_PAGE_WRITEABLE
mdefine_line|#define SUN3_PAGE_WRITEABLE (0x40000000)
DECL|macro|SUN3_PAGE_SYSTEM
mdefine_line|#define SUN3_PAGE_SYSTEM    (0x20000000)
DECL|macro|SUN3_PAGE_NOCACHE
mdefine_line|#define SUN3_PAGE_NOCACHE   (0x10000000)
DECL|macro|SUN3_PAGE_ACCESSED
mdefine_line|#define SUN3_PAGE_ACCESSED  (0x02000000)
DECL|macro|SUN3_PAGE_MODIFIED
mdefine_line|#define SUN3_PAGE_MODIFIED  (0x01000000)
DECL|macro|_DESCTYPE_MASK
mdefine_line|#define _DESCTYPE_MASK&t;0x003
DECL|macro|_CACHEMASK040
mdefine_line|#define _CACHEMASK040&t;(~0x060)
DECL|macro|_TABLE_MASK
mdefine_line|#define _TABLE_MASK&t;(0xfffffe00)
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;(_PAGE_SHORT)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK  (PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY | _PAGE_NOCACHE)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* This is the cache mode to be used for pages containing page descriptors for&n; * processors &gt;= &squot;040. It is in pte_mknocache(), and the variable is defined&n; * and initialized in head.S */
r_extern
r_int
id|m68k_pgtable_cachemode
suffix:semicolon
multiline_comment|/* This is the cache mode for normal pages, for supervisor access on&n; * processors &gt;= &squot;040. It is used in pte_mkcache(), and the variable is&n; * defined and initialized in head.S */
macro_line|#if defined(CONFIG_060_WRITETHROUGH)
r_extern
r_int
id|m68k_supervisor_cachemode
suffix:semicolon
macro_line|#else
DECL|macro|m68k_supervisor_cachemode
mdefine_line|#define m68k_supervisor_cachemode _PAGE_CACHE040
macro_line|#endif
macro_line|#if defined(CPU_M68040_OR_M68060_ONLY)
DECL|macro|mm_cachebits
mdefine_line|#define mm_cachebits _PAGE_CACHE040
macro_line|#elif defined(CPU_M68020_OR_M68030_ONLY)
DECL|macro|mm_cachebits
mdefine_line|#define mm_cachebits 0
macro_line|#else
r_extern
r_int
r_int
id|mm_cachebits
suffix:semicolon
macro_line|#endif
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PRESENT | _PAGE_RONLY | _PAGE_ACCESSED | mm_cachebits)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED | mm_cachebits)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(_PAGE_PRESENT | _PAGE_RONLY | _PAGE_ACCESSED | mm_cachebits)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_PRESENT | _PAGE_RONLY | _PAGE_ACCESSED | mm_cachebits)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_PAGE_PRESENT | _PAGE_DIRTY | _PAGE_ACCESSED | mm_cachebits)
multiline_comment|/* Alternate definitions that are compile time constants, for&n;   initializing protection_map.  The cachebits are fixed later.  */
DECL|macro|PAGE_NONE_C
mdefine_line|#define PAGE_NONE_C&t;__pgprot(_PAGE_PRESENT | _PAGE_RONLY | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED_C
mdefine_line|#define PAGE_SHARED_C&t;__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED)
DECL|macro|PAGE_COPY_C
mdefine_line|#define PAGE_COPY_C&t;__pgprot(_PAGE_PRESENT | _PAGE_RONLY | _PAGE_ACCESSED)
DECL|macro|PAGE_READONLY_C
mdefine_line|#define PAGE_READONLY_C&t;__pgprot(_PAGE_PRESENT | _PAGE_RONLY | _PAGE_ACCESSED)
multiline_comment|/*&n; * The m68k can&squot;t do page protection for execute, and considers that the same are read.&n; * Also, write permissions imply read permissions. This is the closest we can get..&n; */
DECL|macro|__P000
mdefine_line|#define __P000&t;PAGE_NONE_C
DECL|macro|__P001
mdefine_line|#define __P001&t;PAGE_READONLY_C
DECL|macro|__P010
mdefine_line|#define __P010&t;PAGE_COPY_C
DECL|macro|__P011
mdefine_line|#define __P011&t;PAGE_COPY_C
DECL|macro|__P100
mdefine_line|#define __P100&t;PAGE_READONLY_C
DECL|macro|__P101
mdefine_line|#define __P101&t;PAGE_READONLY_C
DECL|macro|__P110
mdefine_line|#define __P110&t;PAGE_COPY_C
DECL|macro|__P111
mdefine_line|#define __P111&t;PAGE_COPY_C
DECL|macro|__S000
mdefine_line|#define __S000&t;PAGE_NONE_C
DECL|macro|__S001
mdefine_line|#define __S001&t;PAGE_READONLY_C
DECL|macro|__S010
mdefine_line|#define __S010&t;PAGE_SHARED_C
DECL|macro|__S011
mdefine_line|#define __S011&t;PAGE_SHARED_C
DECL|macro|__S100
mdefine_line|#define __S100&t;PAGE_READONLY_C
DECL|macro|__S101
mdefine_line|#define __S101&t;PAGE_READONLY_C
DECL|macro|__S110
mdefine_line|#define __S110&t;PAGE_SHARED_C
DECL|macro|__S111
mdefine_line|#define __S111&t;PAGE_SHARED_C
multiline_comment|/* zero page used for uninitialized stuff */
r_extern
r_int
r_int
id|empty_zero_page
suffix:semicolon
multiline_comment|/*&n; * BAD_PAGETABLE is used when we need a bogus page-table, while&n; * BAD_PAGE is used for a bogus page.&n; *&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
id|pte_t
id|__bad_page
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|pte_t
op_star
id|__bad_pagetable
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|BAD_PAGETABLE
mdefine_line|#define BAD_PAGETABLE __bad_pagetable()
DECL|macro|BAD_PAGE
mdefine_line|#define BAD_PAGE __bad_page()
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr)&t;(virt_to_page(empty_zero_page))
multiline_comment|/* number of bits that fit into a memory pointer */
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR&t;&t;&t;(8*sizeof(unsigned long))
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK&t;&t;&t;(~(sizeof(void*)-1))
multiline_comment|/* sizeof(void*)==1&lt;&lt;SIZEOF_PTR_LOG2 */
multiline_comment|/* 64-bit machines, beware!  SRB. */
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2&t;&t;&t;2
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|__mk_pte
mdefine_line|#define __mk_pte(page, pgprot) &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t __pte;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_val(__pte) = __pa((page) + pgprot_val(pgprot);&t;&t;&bslash;&n;&t;__pte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot) __mk_pte(page_address(page), (pgprot))
DECL|macro|mk_pte_phys
mdefine_line|#define mk_pte_phys(physpage, pgprot) &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t __pte;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_val(__pte) = (physpage) + pgprot_val(pgprot);&t;&t;&bslash;&n;&t;__pte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|function|pte_modify
r_extern
r_inline
id|pte_t
id|pte_modify
c_func
(paren
id|pte_t
id|pte
comma
id|pgprot_t
id|newprot
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_CHG_MASK
)paren
op_or
id|pgprot_val
c_func
(paren
id|newprot
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pmd_set
r_extern
r_inline
r_void
id|pmd_set
c_func
(paren
id|pmd_t
op_star
id|pmdp
comma
id|pte_t
op_star
id|ptep
)paren
(brace
r_int
r_int
id|ptbl
op_assign
id|virt_to_phys
c_func
(paren
id|ptep
)paren
op_or
id|_PAGE_TABLE
op_or
id|_PAGE_ACCESSED
suffix:semicolon
r_int
r_int
op_star
id|ptr
op_assign
id|pmdp-&gt;pmd
suffix:semicolon
r_int
id|i
op_assign
l_int|16
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|i
op_ge
l_int|0
)paren
(brace
op_star
id|ptr
op_increment
op_assign
id|ptbl
suffix:semicolon
id|ptbl
op_add_assign
(paren
r_sizeof
(paren
id|pte_t
)paren
op_star
id|PTRS_PER_PTE
op_div
l_int|16
)paren
suffix:semicolon
)brace
)brace
DECL|function|pgd_set
r_extern
r_inline
r_void
id|pgd_set
c_func
(paren
id|pgd_t
op_star
id|pgdp
comma
id|pmd_t
op_star
id|pmdp
)paren
(brace
id|pgd_val
c_func
(paren
op_star
id|pgdp
)paren
op_assign
id|_PAGE_TABLE
op_or
id|_PAGE_ACCESSED
op_or
id|__pa
c_func
(paren
id|pmdp
)paren
suffix:semicolon
)brace
DECL|macro|__pte_page
mdefine_line|#define __pte_page(pte) ((unsigned long)__va(pte_val(pte) &amp; PAGE_MASK))
DECL|macro|__pmd_page
mdefine_line|#define __pmd_page(pmd) ((unsigned long)__va(pmd_val(pmd) &amp; _TABLE_MASK))
DECL|macro|__pgd_page
mdefine_line|#define __pgd_page(pgd) ((unsigned long)__va(pgd_val(pgd) &amp; _TABLE_MASK))
DECL|macro|pte_none
mdefine_line|#define pte_none(pte)&t;&t;(!pte_val(pte))
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;(pte_val(pte) &amp; (_PAGE_PRESENT | _PAGE_FAKE_SUPER))
DECL|macro|pte_clear
mdefine_line|#define pte_clear(ptep)&t;&t;({ pte_val(*(ptep)) = 0; })
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd)&t;&t;(!pmd_val(pmd))
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd)&t;&t;((pmd_val(pmd) &amp; _DESCTYPE_MASK) != _PAGE_TABLE)
DECL|macro|pmd_present
mdefine_line|#define pmd_present(pmd)&t;(pmd_val(pmd) &amp; _PAGE_TABLE)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(pmdp) ({&t;&t;&t;&bslash;&n;&t;unsigned long *__ptr = pmdp-&gt;pmd;&t;&bslash;&n;&t;short __i = 16;&t;&t;&t;&t;&bslash;&n;&t;while (--__i &gt;= 0)&t;&t;&t;&bslash;&n;&t;&t;*__ptr++ = 0;&t;&t;&t;&bslash;&n;})
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd)&t;&t;(!pgd_val(pgd))
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;((pgd_val(pgd) &amp; _DESCTYPE_MASK) != _PAGE_TABLE)
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd)&t;(pgd_val(pgd) &amp; _PAGE_TABLE)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgdp)&t;&t;({ pgd_val(*pgdp) = 0; })
multiline_comment|/* Permanent address of a page. */
DECL|macro|page_address
mdefine_line|#define page_address(page)&t;((page)-&gt;virtual)
DECL|macro|__page_address
mdefine_line|#define __page_address(page)&t;(PAGE_OFFSET + (((page) - mem_map) &lt;&lt; PAGE_SHIFT))
DECL|macro|pte_page
mdefine_line|#define pte_page(pte)&t;&t;(mem_map+((__pte_page(pte) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT))
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %p(%08lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %p(%08lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %p(%08lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), pgd_val(e))
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|function|pte_read
r_extern
r_inline
r_int
id|pte_read
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pte_write
r_extern
r_inline
r_int
id|pte_write
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_RONLY
)paren
suffix:semicolon
)brace
DECL|function|pte_exec
r_extern
r_inline
r_int
id|pte_exec
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pte_dirty
r_extern
r_inline
r_int
id|pte_dirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_DIRTY
suffix:semicolon
)brace
DECL|function|pte_young
r_extern
r_inline
r_int
id|pte_young
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_ACCESSED
suffix:semicolon
)brace
DECL|function|pte_wrprotect
r_extern
r_inline
id|pte_t
id|pte_wrprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_RONLY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_rdprotect
r_extern
r_inline
id|pte_t
id|pte_rdprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_exprotect
r_extern
r_inline
id|pte_t
id|pte_exprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkclean
r_extern
r_inline
id|pte_t
id|pte_mkclean
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_DIRTY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkold
r_extern
r_inline
id|pte_t
id|pte_mkold
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_ACCESSED
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkwrite
r_extern
r_inline
id|pte_t
id|pte_mkwrite
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_RONLY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkread
r_extern
r_inline
id|pte_t
id|pte_mkread
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkexec
r_extern
r_inline
id|pte_t
id|pte_mkexec
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkdirty
r_extern
r_inline
id|pte_t
id|pte_mkdirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_DIRTY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkyoung
r_extern
r_inline
id|pte_t
id|pte_mkyoung
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_ACCESSED
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mknocache
r_extern
r_inline
id|pte_t
id|pte_mknocache
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_CACHEMASK040
)paren
op_or
id|m68k_pgtable_cachemode
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkcache
r_extern
r_inline
id|pte_t
id|pte_mkcache
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_CACHEMASK040
)paren
op_or
id|m68k_supervisor_cachemode
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|PAGE_DIR_OFFSET
mdefine_line|#define PAGE_DIR_OFFSET(tsk,address) pgd_offset((tsk),(address))
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address)&t;((address) &gt;&gt; PGDIR_SHIFT)
multiline_comment|/* to find an entry in a page-table-directory */
DECL|function|pgd_offset
r_extern
r_inline
id|pgd_t
op_star
id|pgd_offset
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_return
id|mm-&gt;pgd
op_plus
id|pgd_index
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
DECL|macro|swapper_pg_dir
mdefine_line|#define swapper_pg_dir kernel_pg_dir
r_extern
id|pgd_t
id|kernel_pg_dir
(braket
l_int|128
)braket
suffix:semicolon
DECL|function|pgd_offset_k
r_extern
r_inline
id|pgd_t
op_star
id|pgd_offset_k
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
id|kernel_pg_dir
op_plus
(paren
id|address
op_rshift
id|PGDIR_SHIFT
)paren
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|function|pmd_offset
r_extern
r_inline
id|pmd_t
op_star
id|pmd_offset
c_func
(paren
id|pgd_t
op_star
id|dir
comma
r_int
r_int
id|address
)paren
(brace
r_return
(paren
id|pmd_t
op_star
)paren
id|__pgd_page
c_func
(paren
op_star
id|dir
)paren
op_plus
(paren
(paren
id|address
op_rshift
id|PMD_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PMD
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|function|pte_offset
r_extern
r_inline
id|pte_t
op_star
id|pte_offset
c_func
(paren
id|pmd_t
op_star
id|pmdp
comma
r_int
r_int
id|address
)paren
(brace
r_return
(paren
id|pte_t
op_star
)paren
id|__pmd_page
c_func
(paren
op_star
id|pmdp
)paren
op_plus
(paren
(paren
id|address
op_rshift
id|PAGE_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PTE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate and free page tables. The xxx_kernel() versions are&n; * used to allocate a kernel page table - this turns on ASN bits&n; * if any.&n; */
multiline_comment|/* Prior to calling these routines, the page should have been flushed&n; * from both the cache and ATC, or the CPU might not notice that the&n; * cache setting for the page has been changed. -jskov&n; */
DECL|function|nocache_page
r_static
r_inline
r_void
id|nocache_page
(paren
r_int
r_int
id|vaddr
)paren
(brace
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
id|dir
op_assign
id|pgd_offset_k
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|vaddr
)paren
suffix:semicolon
id|ptep
op_assign
id|pte_offset
c_func
(paren
id|pmdp
comma
id|vaddr
)paren
suffix:semicolon
op_star
id|ptep
op_assign
id|pte_mknocache
c_func
(paren
op_star
id|ptep
)paren
suffix:semicolon
)brace
)brace
DECL|function|cache_page
r_static
r_inline
r_void
id|cache_page
(paren
r_int
r_int
id|vaddr
)paren
(brace
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
id|dir
op_assign
id|pgd_offset_k
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|vaddr
)paren
suffix:semicolon
id|ptep
op_assign
id|pte_offset
c_func
(paren
id|pmdp
comma
id|vaddr
)paren
suffix:semicolon
op_star
id|ptep
op_assign
id|pte_mkcache
c_func
(paren
op_star
id|ptep
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Check if the addr/len goes up to the end of a physical&n; * memory chunk.  Used for DMA functions.&n; */
macro_line|#ifdef CONFIG_SINGLE_MEMORY_CHUNK
multiline_comment|/*&n; * It makes no sense to consider whether we cross a memory boundary if&n; * we support just one physical chunk of memory.&n; */
DECL|function|mm_end_of_chunk
r_extern
r_inline
r_int
id|mm_end_of_chunk
(paren
r_int
r_int
id|addr
comma
r_int
id|len
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
r_int
id|mm_end_of_chunk
(paren
r_int
r_int
id|addr
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|kernel_set_cachemode
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|size
comma
r_int
id|cmode
)paren
suffix:semicolon
multiline_comment|/*&n; * The m68k doesn&squot;t have any external MMU info: the kernel page&n; * tables contain all the necessary information.&n; */
DECL|function|update_mmu_cache
r_extern
r_inline
r_void
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
id|pte
)paren
(brace
)brace
multiline_comment|/* Encode and de-code a swap entry (must be !pte_none(e) &amp;&amp; !pte_present(e)) */
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(x)&t;&t;&t;(((x).val &gt;&gt; 1) &amp; 0xff)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(x)&t;&t;&t;((x).val &gt;&gt; 10)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type, offset)&t;&t;((swp_entry_t) { ((type) &lt;&lt; 1) | ((offset) &lt;&lt; 10) })
DECL|macro|pte_to_swp_entry
mdefine_line|#define pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|swp_entry_to_pte
mdefine_line|#define swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|module_map
mdefine_line|#define module_map      vmalloc
DECL|macro|module_unmap
mdefine_line|#define module_unmap    vfree
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
DECL|macro|PageSkip
mdefine_line|#define PageSkip(page)&t;&t;(0)
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range remap_page_range
macro_line|#include &lt;asm-generic/pgtable.h&gt;
macro_line|#endif /* _M68K_PGTABLE_H */
eof
