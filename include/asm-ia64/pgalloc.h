macro_line|#ifndef _ASM_IA64_PGALLOC_H
DECL|macro|_ASM_IA64_PGALLOC_H
mdefine_line|#define _ASM_IA64_PGALLOC_H
multiline_comment|/*&n; * This file contains the functions and defines necessary to allocate&n; * page tables.&n; *&n; * This hopefully works with any (fixed) ia-64 page-size, as defined&n; * in &lt;asm/page.h&gt; (currently 8192).&n; *&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 2000, Goutham Rao &lt;goutham.rao@intel.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * Very stupidly, we used to get new pgd&squot;s and pmd&squot;s, init their contents&n; * to point to the NULL versions of the next level page table, later on&n; * completely re-init them the same way, then free them up.  This wasted&n; * a lot of work and caused unnecessary memory traffic.  How broken...&n; * We fix this by caching them.&n; */
DECL|macro|pgd_quicklist
mdefine_line|#define pgd_quicklist&t;&t;(my_cpu_data.pgd_quick)
DECL|macro|pmd_quicklist
mdefine_line|#define pmd_quicklist&t;&t;(my_cpu_data.pmd_quick)
DECL|macro|pte_quicklist
mdefine_line|#define pte_quicklist&t;&t;(my_cpu_data.pte_quick)
DECL|macro|pgtable_cache_size
mdefine_line|#define pgtable_cache_size&t;(my_cpu_data.pgtable_cache_sz)
r_static
id|__inline__
id|pgd_t
op_star
DECL|function|get_pgd_slow
id|get_pgd_slow
(paren
r_void
)paren
(brace
id|pgd_t
op_star
id|ret
op_assign
(paren
id|pgd_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|clear_page
c_func
(paren
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
id|__inline__
id|pgd_t
op_star
DECL|function|get_pgd_fast
id|get_pgd_fast
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|ret
op_assign
id|pgd_quicklist
suffix:semicolon
r_if
c_cond
(paren
id|ret
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
(paren
op_star
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
op_decrement
id|pgtable_cache_size
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
r_static
id|__inline__
id|pgd_t
op_star
DECL|function|pgd_alloc
id|pgd_alloc
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
r_static
id|__inline__
r_void
DECL|function|free_pgd_fast
id|free_pgd_fast
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
op_star
(paren
r_int
r_int
op_star
)paren
id|pgd
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
op_increment
id|pgtable_cache_size
suffix:semicolon
)brace
r_static
id|__inline__
id|pmd_t
op_star
DECL|function|get_pmd_slow
id|get_pmd_slow
(paren
r_void
)paren
(brace
id|pmd_t
op_star
id|pmd
op_assign
(paren
id|pmd_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd
)paren
id|clear_page
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
id|pmd
suffix:semicolon
)brace
r_static
id|__inline__
id|pmd_t
op_star
DECL|function|get_pmd_fast
id|get_pmd_fast
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|ret
op_assign
(paren
r_int
r_int
op_star
)paren
id|pmd_quicklist
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|NULL
)paren
(brace
id|pmd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
op_star
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
op_decrement
id|pgtable_cache_size
suffix:semicolon
)brace
r_return
(paren
id|pmd_t
op_star
)paren
id|ret
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|free_pmd_fast
id|free_pmd_fast
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
op_star
(paren
r_int
r_int
op_star
)paren
id|pmd
op_assign
(paren
r_int
r_int
)paren
id|pmd_quicklist
suffix:semicolon
id|pmd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|pmd
suffix:semicolon
op_increment
id|pgtable_cache_size
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|free_pmd_slow
id|free_pmd_slow
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pmd
)paren
suffix:semicolon
)brace
r_extern
id|pte_t
op_star
id|get_pte_slow
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address_preadjusted
)paren
suffix:semicolon
r_static
id|__inline__
id|pte_t
op_star
DECL|function|get_pte_fast
id|get_pte_fast
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|ret
op_assign
(paren
r_int
r_int
op_star
)paren
id|pte_quicklist
suffix:semicolon
r_if
c_cond
(paren
id|ret
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
(paren
op_star
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
op_decrement
id|pgtable_cache_size
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
r_static
id|__inline__
r_void
DECL|function|free_pte_fast
id|free_pte_fast
(paren
id|pte_t
op_star
id|pte
)paren
(brace
op_star
(paren
r_int
r_int
op_star
)paren
id|pte
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
op_increment
id|pgtable_cache_size
suffix:semicolon
)brace
DECL|macro|pte_free_kernel
mdefine_line|#define pte_free_kernel(pte)&t;free_pte_fast(pte)
DECL|macro|pte_free
mdefine_line|#define pte_free(pte)&t;&t;free_pte_fast(pte)
DECL|macro|pmd_free_kernel
mdefine_line|#define pmd_free_kernel(pmd)&t;free_pmd_fast(pmd)
DECL|macro|pmd_free
mdefine_line|#define pmd_free(pmd)&t;&t;free_pmd_fast(pmd)
DECL|macro|pgd_free
mdefine_line|#define pgd_free(pgd)&t;&t;free_pgd_fast(pgd)
r_extern
r_void
id|__handle_bad_pgd
(paren
id|pgd_t
op_star
id|pgd
)paren
suffix:semicolon
r_extern
r_void
id|__handle_bad_pmd
(paren
id|pmd_t
op_star
id|pmd
)paren
suffix:semicolon
r_static
id|__inline__
id|pte_t
op_star
DECL|function|pte_alloc
id|pte_alloc
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|vmaddr
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
id|offset
op_assign
(paren
id|vmaddr
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
id|pte_page
op_assign
id|get_pte_fast
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_page
)paren
r_return
id|get_pte_slow
c_func
(paren
id|pmd
comma
id|offset
)paren
suffix:semicolon
id|pmd_set
c_func
(paren
id|pmd
comma
id|pte_page
)paren
suffix:semicolon
r_return
id|pte_page
op_plus
id|offset
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
id|offset
suffix:semicolon
)brace
r_static
id|__inline__
id|pmd_t
op_star
DECL|function|pmd_alloc
id|pmd_alloc
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|vmaddr
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
id|offset
op_assign
(paren
id|vmaddr
op_rshift
id|PMD_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PMD
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|pmd_t
op_star
id|pmd_page
op_assign
id|get_pmd_fast
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_page
)paren
id|pmd_page
op_assign
id|get_pmd_slow
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_page
)paren
(brace
id|pgd_set
c_func
(paren
id|pgd
comma
id|pmd_page
)paren
suffix:semicolon
r_return
id|pmd_page
op_plus
id|offset
suffix:semicolon
)brace
r_else
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|__handle_bad_pgd
c_func
(paren
id|pgd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
id|pmd_t
op_star
)paren
id|pgd_page
c_func
(paren
op_star
id|pgd
)paren
op_plus
id|offset
suffix:semicolon
)brace
DECL|macro|pte_alloc_kernel
mdefine_line|#define pte_alloc_kernel(pmd, addr)&t;pte_alloc(pmd, addr)
DECL|macro|pmd_alloc_kernel
mdefine_line|#define pmd_alloc_kernel(pgd, addr)&t;pmd_alloc(pgd, addr)
r_extern
r_int
id|do_check_pgt_cache
(paren
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Now for some TLB flushing routines.  This is the kind of stuff that&n; * can be very expensive, so try to avoid them whenever possible.&n; */
multiline_comment|/*&n; * Flush everything (kernel mapping may also have changed due to&n; * vmalloc/vfree).&n; */
r_extern
r_void
id|__flush_tlb_all
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|smp_flush_tlb_all
(paren
r_void
)paren
suffix:semicolon
DECL|macro|flush_tlb_all
macro_line|# define flush_tlb_all()&t;smp_flush_tlb_all()
macro_line|#else
DECL|macro|flush_tlb_all
macro_line|# define flush_tlb_all()&t;__flush_tlb_all()
macro_line|#endif
multiline_comment|/*&n; * Serialize usage of ptc.g:&n; */
r_extern
id|spinlock_t
id|ptcg_lock
suffix:semicolon
multiline_comment|/*&n; * Flush a specified user mapping&n; */
r_static
id|__inline__
r_void
DECL|function|flush_tlb_mm
id|flush_tlb_mm
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|mm
)paren
(brace
id|mm-&gt;context
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;active_mm
)paren
(brace
multiline_comment|/* This is called, e.g., as a result of exec().  */
id|get_new_mmu_context
c_func
(paren
id|mm
)paren
suffix:semicolon
id|reload_context
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
)brace
)brace
r_extern
r_void
id|flush_tlb_range
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
multiline_comment|/*&n; * Page-granular tlb flush.&n; */
r_static
id|__inline__
r_void
DECL|function|flush_tlb_page
id|flush_tlb_page
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
)paren
(brace
macro_line|#ifdef CONFIG_SMP
id|flush_tlb_range
c_func
(paren
id|vma-&gt;vm_mm
comma
(paren
id|addr
op_amp
id|PAGE_MASK
)paren
comma
(paren
id|addr
op_amp
id|PAGE_MASK
)paren
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_eq
id|current-&gt;active_mm
)paren
id|asm
r_volatile
(paren
l_string|&quot;ptc.l %0,%1&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|PAGE_SHIFT
op_lshift
l_int|2
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Flush the TLB entries mapping the virtually mapped linear page&n; * table corresponding to address range [START-END).&n; */
r_static
r_inline
r_void
DECL|function|flush_tlb_pgtables
id|flush_tlb_pgtables
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_if
c_cond
(paren
id|rgn_index
c_func
(paren
id|start
)paren
op_ne
id|rgn_index
c_func
(paren
id|end
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;flush_tlb_pgtables: can&squot;t flush across regions!!&bslash;n&quot;
)paren
suffix:semicolon
id|flush_tlb_range
c_func
(paren
id|mm
comma
id|ia64_thash
c_func
(paren
id|start
)paren
comma
id|ia64_thash
c_func
(paren
id|end
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Now for some cache flushing routines.  This is the kind of stuff&n; * that can be very expensive, so try to avoid them whenever possible.&n; */
multiline_comment|/* Caches aren&squot;t brain-dead on the IA-64. */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(mm, start, end)&t;do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, vmaddr)&t;&t;do { } while (0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;&t;do { } while (0)
r_extern
r_void
id|flush_icache_range
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|flush_dcache_page
id|flush_dcache_page
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|clear_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|clear_user_page
id|clear_user_page
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|vaddr
comma
r_struct
id|page
op_star
id|page
)paren
(brace
id|clear_page
c_func
(paren
id|addr
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|copy_user_page
id|copy_user_page
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
comma
r_int
r_int
id|vaddr
comma
r_struct
id|page
op_star
id|page
)paren
(brace
id|copy_page
c_func
(paren
id|to
comma
id|from
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * IA-64 doesn&squot;t have any external MMU info: the page tables contain all the necessary&n; * information.  However, we use this macro to take care of any (delayed) i-cache flushing&n; * that may be necessary.&n; */
r_static
r_inline
r_void
DECL|function|update_mmu_cache
id|update_mmu_cache
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
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_exec
c_func
(paren
id|pte
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* not an executable page... */
id|page
op_assign
id|pte_page
c_func
(paren
id|pte
)paren
suffix:semicolon
id|address
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* i-cache is already coherent with d-cache */
id|flush_icache_range
c_func
(paren
id|address
comma
id|address
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
multiline_comment|/* mark page as clean */
)brace
macro_line|#endif /* _ASM_IA64_PGALLOC_H */
eof
