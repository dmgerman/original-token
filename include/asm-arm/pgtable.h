macro_line|#ifndef _ASMARM_PGTABLE_H
DECL|macro|_ASMARM_PGTABLE_H
mdefine_line|#define _ASMARM_PGTABLE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/arch/memory.h&gt;&t;&t;/* For TASK_SIZE */
macro_line|#include &lt;asm/proc-fns.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/proc/cache.h&gt;
DECL|macro|LIBRARY_TEXT_START
mdefine_line|#define LIBRARY_TEXT_START&t;0x0c000000
DECL|macro|TEST_VERIFY_AREA
macro_line|#undef TEST_VERIFY_AREA
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
r_extern
r_int
r_int
op_star
id|empty_zero_page
suffix:semicolon
DECL|macro|BAD_PAGETABLE
mdefine_line|#define BAD_PAGETABLE&t;&t;__bad_pagetable()
DECL|macro|BAD_PAGE
mdefine_line|#define BAD_PAGE&t;&t;__bad_page()
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr)&t;((unsigned long) empty_zero_page)
multiline_comment|/* number of bits that fit into a memory pointer */
DECL|macro|BYTES_PER_PTR
mdefine_line|#define BYTES_PER_PTR&t;&t;(sizeof(unsigned long))
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR&t;&t;(8*BYTES_PER_PTR)
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK&t;&t;(~(sizeof(void*)-1))
multiline_comment|/* sizeof(void*)==1&lt;&lt;SIZEOF_PTR_LOG2 */
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2&t;&t;2
multiline_comment|/* to find an entry in a page-table */
DECL|macro|PAGE_PTR
mdefine_line|#define PAGE_PTR(address) &bslash;&n;&t;((unsigned long)(address)&gt;&gt;(PAGE_SHIFT-SIZEOF_PTR_LOG2)&amp;PTR_MASK&amp;~PAGE_MASK)
r_extern
r_void
id|__bad_pmd
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
suffix:semicolon
r_extern
r_void
id|__bad_pmd_kernel
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
suffix:semicolon
multiline_comment|/*&n; * Page table cache stuff&n; */
macro_line|#ifndef CONFIG_NO_PGT_CACHE
macro_line|#ifndef __SMP__
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
macro_line|#else&t;/* __SMP__ */
macro_line|#error Pgtable caches have to be per-CPU, so that no locking is needed.
macro_line|#endif&t;/* __SMP__ */
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
multiline_comment|/* We don&squot;t use pmd cache, so this is a dummy routine */
DECL|function|get_pmd_fast
r_extern
id|__inline__
id|pmd_t
op_star
id|get_pmd_fast
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|pmd_t
op_star
)paren
l_int|0
suffix:semicolon
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
DECL|macro|get_pgd_fast
mdefine_line|#define get_pgd_fast()&t;&t;(NULL)
DECL|macro|get_pmd_fast
mdefine_line|#define get_pmd_fast()&t;&t;(NULL)
DECL|macro|get_pte_fast
mdefine_line|#define get_pte_fast()&t;&t;(NULL)
DECL|macro|free_pgd_fast
mdefine_line|#define free_pgd_fast(pgd)&t;free_pgd_slow(pgd)
DECL|macro|free_pmd_fast
mdefine_line|#define free_pmd_fast(pmd)&t;free_pmd_slow(pmd)
DECL|macro|free_pte_fast
mdefine_line|#define free_pte_fast(pte)&t;free_pte_slow(pte)
macro_line|#endif&t;/* CONFIG_NO_PGT_CACHE */
macro_line|#include &lt;asm/proc/pgtable.h&gt;
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
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(entry)&t;&t;(((entry) &gt;&gt; 2) &amp; 0x7f)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(entry)&t;((entry) &gt;&gt; 9)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type,offset)&t;(((type) &lt;&lt; 2) | ((offset) &lt;&lt; 9))
DECL|macro|module_map
mdefine_line|#define module_map&t;&t;vmalloc
DECL|macro|module_unmap
mdefine_line|#define module_unmap&t;&t;vfree
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
macro_line|#endif /* _ASMARM_PGTABLE_H */
eof
