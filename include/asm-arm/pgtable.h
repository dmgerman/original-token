multiline_comment|/*&n; * linux/include/asm-arm/pgtable.h&n; */
macro_line|#ifndef _ASMARM_PGTABLE_H
DECL|macro|_ASMARM_PGTABLE_H
mdefine_line|#define _ASMARM_PGTABLE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/arch/memory.h&gt;
macro_line|#include &lt;asm/proc-fns.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * PMD_SHIFT determines the size of the area a second-level page table can map&n; * PGDIR_SHIFT determines what a third-level page table entry can map&n; */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;&t;20
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;&t;20
DECL|macro|LIBRARY_TEXT_START
mdefine_line|#define LIBRARY_TEXT_START&t;0x0c000000
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|__pte_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_void
id|__pmd_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_void
id|__pgd_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(pte)&t;&t;__pte_error(__FILE__, __LINE__, pte_val(pte))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(pmd)&t;&t;__pmd_error(__FILE__, __LINE__, pmd_val(pmd))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(pgd)&t;&t;__pgd_error(__FILE__, __LINE__, pgd_val(pgd))
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;&t;(~(PMD_SIZE-1))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;&t;(~(PGDIR_SIZE-1))
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE/PGDIR_SIZE)
multiline_comment|/*&n; * The table below defines the page protection levels that we insert into our&n; * Linux page table version.  These get translated into the best that the&n; * architecture can perform.  Note that on most ARM hardware:&n; *  1) We cannot do execute protection&n; *  2) If we could do execute protection, then read is implied&n; *  3) write implies read permissions&n; */
DECL|macro|__P000
mdefine_line|#define __P000  PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001  PAGE_READONLY
DECL|macro|__P010
mdefine_line|#define __P010  PAGE_COPY
DECL|macro|__P011
mdefine_line|#define __P011  PAGE_COPY
DECL|macro|__P100
mdefine_line|#define __P100  PAGE_READONLY
DECL|macro|__P101
mdefine_line|#define __P101  PAGE_READONLY
DECL|macro|__P110
mdefine_line|#define __P110  PAGE_COPY
DECL|macro|__P111
mdefine_line|#define __P111  PAGE_COPY
DECL|macro|__S000
mdefine_line|#define __S000  PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001  PAGE_READONLY
DECL|macro|__S010
mdefine_line|#define __S010  PAGE_SHARED
DECL|macro|__S011
mdefine_line|#define __S011  PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100  PAGE_READONLY
DECL|macro|__S101
mdefine_line|#define __S101  PAGE_READONLY
DECL|macro|__S110
mdefine_line|#define __S110  PAGE_SHARED
DECL|macro|__S111
mdefine_line|#define __S111  PAGE_SHARED
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
DECL|variable|empty_zero_page
r_struct
id|page
op_star
id|empty_zero_page
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr)&t;(empty_zero_page)
multiline_comment|/*&n; * Handling allocation failures during page table setup.&n; */
r_extern
r_void
id|__handle_bad_pmd
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
suffix:semicolon
r_extern
r_void
id|__handle_bad_pmd_kernel
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
suffix:semicolon
DECL|macro|pte_none
mdefine_line|#define pte_none(pte)&t;&t;(!pte_val(pte))
DECL|macro|pte_clear
mdefine_line|#define pte_clear(ptep)&t;&t;set_pte((ptep), __pte(0))
DECL|macro|pte_pagenr
mdefine_line|#define pte_pagenr(pte)&t;&t;((unsigned long)(((pte_val(pte) - PHYS_OFFSET) &gt;&gt; PAGE_SHIFT)))
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd)&t;&t;(!pmd_val(pmd))
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(pmdp)&t;&t;set_pmd(pmdp, __pmd(0))
multiline_comment|/*&n; * Permanent address of a page.&n; */
DECL|macro|page_address
mdefine_line|#define page_address(page)&t;(PAGE_OFFSET + (((page) - mem_map) &lt;&lt; PAGE_SHIFT))
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x)&t;&t;((x) &gt;&gt; (20 - PAGE_SHIFT))
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;(mem_map + pte_pagenr(x))
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd)&t;&t;(0)
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;(0)
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd)&t;(1)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgdp)
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|function|mk_pte_phys
r_extern
id|__inline__
id|pte_t
id|mk_pte_phys
c_func
(paren
r_int
r_int
id|physpage
comma
id|pgprot_t
id|pgprot
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
id|physpage
op_or
id|pgprot_val
c_func
(paren
id|pgprot
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|mk_pte
r_extern
id|__inline__
id|pte_t
id|mk_pte
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|pgprot_t
id|pgprot
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|PHYS_OFFSET
op_plus
(paren
(paren
id|page
op_minus
id|mem_map
)paren
op_lshift
id|PAGE_SHIFT
)paren
)paren
op_or
id|pgprot_val
c_func
(paren
id|pgprot
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|page_pte_prot
mdefine_line|#define page_pte_prot(page,prot)&t;mk_pte(page, prot)
DECL|macro|page_pte
mdefine_line|#define page_pte(page)&t;&t;mk_pte(page, __pgprot(0))
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|__pgd_offset
mdefine_line|#define __pgd_offset(addr)&t;((addr) &gt;&gt; PGDIR_SHIFT)
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, addr)&t;((mm)-&gt;pgd+__pgd_offset(addr))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(addr)&t;pgd_offset(&amp;init_mm, addr)
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir, addr)&t;((pmd_t *)(dir))
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|__pte_offset
mdefine_line|#define __pte_offset(addr)&t;(((addr) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset
mdefine_line|#define pte_offset(dir, addr)&t;((pte_t *)pmd_page(*(dir)) + __pte_offset(addr))
multiline_comment|/*&n; * Get the cache handling stuff now.&n; */
macro_line|#include &lt;asm/proc/cache.h&gt;
multiline_comment|/*&n; * Page table cache stuff&n; */
macro_line|#ifndef CONFIG_NO_PGT_CACHE
macro_line|#ifdef __SMP__
macro_line|#error Pgtable caches have to be per-CPU, so that no locking is needed.
macro_line|#endif&t;/* __SMP__ */
DECL|struct|pgtable_cache_struct
r_extern
r_struct
id|pgtable_cache_struct
(brace
DECL|member|pgd_cache
r_int
r_int
op_star
id|pgd_cache
suffix:semicolon
DECL|member|pte_cache
r_int
r_int
op_star
id|pte_cache
suffix:semicolon
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
)brace
id|quicklists
suffix:semicolon
DECL|macro|pgd_quicklist
mdefine_line|#define pgd_quicklist&t;&t;(quicklists.pgd_cache)
DECL|macro|pmd_quicklist
mdefine_line|#define pmd_quicklist&t;&t;((unsigned long *)0)
DECL|macro|pte_quicklist
mdefine_line|#define pte_quicklist&t;&t;(quicklists.pte_cache)
DECL|macro|pgtable_cache_size
mdefine_line|#define pgtable_cache_size&t;(quicklists.pgtable_cache_sz)
multiline_comment|/* used for quicklists */
DECL|macro|__pgd_next
mdefine_line|#define __pgd_next(pgd) (((unsigned long *)pgd)[1])
DECL|macro|__pte_next
mdefine_line|#define __pte_next(pte)&t;(((unsigned long *)pte)[0])
DECL|function|get_pgd_fast
r_extern
id|__inline__
id|pgd_t
op_star
id|get_pgd_fast
c_func
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|pgd_quicklist
)paren
op_ne
l_int|NULL
)paren
(brace
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|__pgd_next
c_func
(paren
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|1
)braket
op_assign
id|ret
(braket
l_int|2
)braket
suffix:semicolon
id|clean_cache_area
c_func
(paren
id|ret
op_plus
l_int|1
comma
l_int|4
)paren
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
)brace
r_return
(paren
id|pgd_t
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|free_pgd_fast
r_extern
id|__inline__
r_void
id|free_pgd_fast
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|__pgd_next
c_func
(paren
id|pgd
)paren
op_assign
(paren
r_int
r_int
)paren
id|pgd_quicklist
suffix:semicolon
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|pgd
suffix:semicolon
id|pgtable_cache_size
op_increment
suffix:semicolon
)brace
multiline_comment|/* We don&squot;t use pmd cache, so this is a dummy routine */
DECL|macro|get_pmd_fast
mdefine_line|#define get_pmd_fast()&t;&t;((pmd_t *)0)
DECL|function|free_pmd_fast
r_extern
id|__inline__
r_void
id|free_pmd_fast
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
)brace
DECL|function|get_pte_fast
r_extern
id|__inline__
id|pte_t
op_star
id|get_pte_fast
c_func
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|pte_quicklist
)paren
op_ne
l_int|NULL
)paren
(brace
id|pte_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|__pte_next
c_func
(paren
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
id|ret
(braket
l_int|1
)braket
suffix:semicolon
id|clean_cache_area
c_func
(paren
id|ret
comma
l_int|4
)paren
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
)brace
r_return
(paren
id|pte_t
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|free_pte_fast
r_extern
id|__inline__
r_void
id|free_pte_fast
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
id|__pte_next
c_func
(paren
id|pte
)paren
op_assign
(paren
r_int
r_int
)paren
id|pte_quicklist
suffix:semicolon
id|pte_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|pte
suffix:semicolon
id|pgtable_cache_size
op_increment
suffix:semicolon
)brace
macro_line|#else&t;/* CONFIG_NO_PGT_CACHE */
DECL|macro|pgd_quicklist
mdefine_line|#define pgd_quicklist&t;&t;((unsigned long *)0)
DECL|macro|pmd_quicklist
mdefine_line|#define pmd_quicklist&t;&t;((unsigned long *)0)
DECL|macro|pte_quicklist
mdefine_line|#define pte_quicklist&t;&t;((unsigned long *)0)
DECL|macro|get_pgd_fast
mdefine_line|#define get_pgd_fast()&t;&t;((pgd_t *)0)
DECL|macro|get_pmd_fast
mdefine_line|#define get_pmd_fast()&t;&t;((pmd_t *)0)
DECL|macro|get_pte_fast
mdefine_line|#define get_pte_fast()&t;&t;((pte_t *)0)
DECL|macro|free_pgd_fast
mdefine_line|#define free_pgd_fast(pgd)&t;free_pgd_slow(pgd)
DECL|macro|free_pmd_fast
mdefine_line|#define free_pmd_fast(pmd)&t;free_pmd_slow(pmd)
DECL|macro|free_pte_fast
mdefine_line|#define free_pte_fast(pte)&t;free_pte_slow(pte)
macro_line|#endif&t;/* CONFIG_NO_PGT_CACHE */
r_extern
id|pgd_t
op_star
id|get_pgd_slow
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|free_pgd_slow
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
suffix:semicolon
DECL|macro|free_pmd_slow
mdefine_line|#define free_pmd_slow(pmd)&t;do { } while (0)
r_extern
id|pte_t
op_star
id|get_pte_kernel_slow
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|addr_preadjusted
)paren
suffix:semicolon
r_extern
id|pte_t
op_star
id|get_pte_slow
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|addr_preadjusted
)paren
suffix:semicolon
r_extern
r_void
id|free_pte_slow
c_func
(paren
id|pte_t
op_star
id|pte
)paren
suffix:semicolon
macro_line|#include &lt;asm/proc/pgtable.h&gt;
DECL|function|pte_modify
r_extern
id|__inline__
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
multiline_comment|/*&n; * Allocate and free page tables. The xxx_kernel() versions are&n; * used to allocate a kernel page table - this turns on ASN bits&n; * if any.&n; */
DECL|macro|pte_free_kernel
mdefine_line|#define pte_free_kernel(pte)&t;free_pte_fast(pte)
DECL|macro|pte_free
mdefine_line|#define pte_free(pte)&t;&t;free_pte_fast(pte)
macro_line|#ifndef pte_alloc_kernel
DECL|function|pte_alloc_kernel
r_extern
id|__inline__
id|pte_t
op_star
id|pte_alloc_kernel
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
)paren
(brace
id|address
op_assign
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
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pte_t
op_star
id|page
op_assign
(paren
id|pte_t
op_star
)paren
id|get_pte_fast
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
id|get_pte_kernel_slow
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
id|mk_kernel_pmd
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
r_return
id|page
op_plus
id|address
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|__handle_bad_pmd_kernel
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
id|pte_t
op_star
)paren
id|pmd_page
c_func
(paren
op_star
id|pmd
)paren
op_plus
id|address
suffix:semicolon
)brace
macro_line|#endif
DECL|function|pte_alloc
r_extern
id|__inline__
id|pte_t
op_star
id|pte_alloc
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
)paren
(brace
id|address
op_assign
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
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pte_t
op_star
id|page
op_assign
(paren
id|pte_t
op_star
)paren
id|get_pte_fast
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
id|get_pte_slow
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
id|mk_user_pmd
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
r_return
id|page
op_plus
id|address
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|__handle_bad_pmd
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
id|pte_t
op_star
)paren
id|pmd_page
c_func
(paren
op_star
id|pmd
)paren
op_plus
id|address
suffix:semicolon
)brace
DECL|macro|pmd_free_kernel
mdefine_line|#define pmd_free_kernel&t;&t;pmd_free
DECL|macro|pmd_free
mdefine_line|#define pmd_free(pmd)&t;&t;do { } while (0)
DECL|macro|pmd_alloc_kernel
mdefine_line|#define pmd_alloc_kernel&t;pmd_alloc
DECL|function|pmd_alloc
r_extern
id|__inline__
id|pmd_t
op_star
id|pmd_alloc
c_func
(paren
id|pgd_t
op_star
id|pgd
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
id|pgd
suffix:semicolon
)brace
DECL|macro|pgd_free
mdefine_line|#define pgd_free(pgd)&t;&t;free_pgd_fast(pgd)
DECL|function|pgd_alloc
r_extern
id|__inline__
id|pgd_t
op_star
id|pgd_alloc
c_func
(paren
r_void
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pgd
op_assign
id|get_pgd_fast
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd
)paren
id|pgd
op_assign
id|get_pgd_slow
c_func
(paren
)paren
suffix:semicolon
r_return
id|pgd
suffix:semicolon
)brace
r_extern
r_int
id|do_check_pgt_cache
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
DECL|function|set_pgdir
r_extern
id|__inline__
r_void
id|set_pgdir
c_func
(paren
r_int
r_int
id|address
comma
id|pgd_t
id|entry
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;mm
)paren
r_continue
suffix:semicolon
op_star
id|pgd_offset
c_func
(paren
id|p-&gt;mm
comma
id|address
)paren
op_assign
id|entry
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_NO_PGT_CACHE
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
r_for
c_loop
(paren
id|pgd
op_assign
(paren
id|pgd_t
op_star
)paren
id|pgd_quicklist
suffix:semicolon
id|pgd
suffix:semicolon
id|pgd
op_assign
(paren
id|pgd_t
op_star
)paren
id|__pgd_next
c_func
(paren
id|pgd
)paren
)paren
id|pgd
(braket
id|address
op_rshift
id|PGDIR_SHIFT
)braket
op_assign
id|entry
suffix:semicolon
)brace
macro_line|#endif
)brace
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
DECL|macro|update_mmu_cache
mdefine_line|#define update_mmu_cache(vma,address,pte)
multiline_comment|/*&n; * We support up to 32GB of swap on 4k machines&n; */
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(entry)&t;&t;(((pte_val(entry)) &gt;&gt; 2) &amp; 0x7f)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(entry)&t;((pte_val(entry)) &gt;&gt; 9)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type,offset)&t;__pte((((type) &lt;&lt; 2) | ((offset) &lt;&lt; 9)))
DECL|macro|module_map
mdefine_line|#define module_map&t;&t;vmalloc
DECL|macro|module_unmap
mdefine_line|#define module_unmap&t;&t;vfree
multiline_comment|/*&n; * We rely on GCC optimising this code away for&n; * architectures which it doesn&squot;t apply to.  Note&n; * that `addr&squot; is checked against PAGE_OFFSET and&n; * end_mem by the calling code.&n; */
DECL|macro|__kern_valid_idx
mdefine_line|#define __kern_valid_idx(a)&t;(((a) - PAGE_OFFSET) &gt;&gt; 20)
DECL|function|__kern_valid_addr
r_extern
id|__inline__
r_int
id|__kern_valid_addr
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_extern
r_int
r_int
op_star
id|valid_addr_bitmap
suffix:semicolon
r_int
r_int
id|idx
op_assign
id|__kern_valid_idx
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
id|test_bit
c_func
(paren
id|idx
comma
id|valid_addr_bitmap
)paren
suffix:semicolon
)brace
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
DECL|macro|PageSkip
mdefine_line|#define PageSkip(page)&t;&t;(machine_is_riscpc() &amp;&amp; test_bit(PG_skip, &amp;(page)-&gt;flags))
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(!machine_is_riscpc() || __kern_valid_addr(addr))
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range&t;remap_page_range
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASMARM_PGTABLE_H */
eof
