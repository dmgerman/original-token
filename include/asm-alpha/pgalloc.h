macro_line|#ifndef _ALPHA_PGALLOC_H
DECL|macro|_ALPHA_PGALLOC_H
mdefine_line|#define _ALPHA_PGALLOC_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Caches aren&squot;t brain-dead on the Alpha. */
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
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)&t;&t;do { } while (0)
multiline_comment|/*&n; * Use a few helper functions to hide the ugly broken ASN&n; * numbers on early Alphas (ev4 and ev45)&n; */
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__MMU_EXTERN_INLINE
mdefine_line|#define __MMU_EXTERN_INLINE
macro_line|#endif
id|__EXTERN_INLINE
r_void
DECL|function|ev4_flush_tlb_current
id|ev4_flush_tlb_current
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|tbiap
c_func
(paren
)paren
suffix:semicolon
)brace
id|__EXTERN_INLINE
r_void
DECL|function|ev4_flush_tlb_other
id|ev4_flush_tlb_other
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
)brace
r_extern
r_void
id|ev5_flush_tlb_current
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
id|__EXTERN_INLINE
r_void
DECL|function|ev5_flush_tlb_other
id|ev5_flush_tlb_other
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|mm-&gt;context
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Flush just one page in the current TLB set.&n; * We need to be very careful about the icache here, there&n; * is no way to invalidate a specific icache page..&n; */
id|__EXTERN_INLINE
r_void
DECL|function|ev4_flush_tlb_current_page
id|ev4_flush_tlb_current_page
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
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
id|tbi
c_func
(paren
l_int|2
op_plus
(paren
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
op_ne
l_int|0
)paren
comma
id|addr
)paren
suffix:semicolon
)brace
id|__EXTERN_INLINE
r_void
DECL|function|ev5_flush_tlb_current_page
id|ev5_flush_tlb_current_page
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
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
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
id|ev5_flush_tlb_current
c_func
(paren
id|mm
)paren
suffix:semicolon
r_else
id|tbi
c_func
(paren
l_int|2
comma
id|addr
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ALPHA_GENERIC
DECL|macro|flush_tlb_current
macro_line|# define flush_tlb_current&t;&t;alpha_mv.mv_flush_tlb_current
DECL|macro|flush_tlb_other
macro_line|# define flush_tlb_other&t;&t;alpha_mv.mv_flush_tlb_other
DECL|macro|flush_tlb_current_page
macro_line|# define flush_tlb_current_page&t;&t;alpha_mv.mv_flush_tlb_current_page
macro_line|#else
macro_line|# ifdef CONFIG_ALPHA_EV4
DECL|macro|flush_tlb_current
macro_line|#  define flush_tlb_current&t;&t;ev4_flush_tlb_current
DECL|macro|flush_tlb_other
macro_line|#  define flush_tlb_other&t;&t;ev4_flush_tlb_other
DECL|macro|flush_tlb_current_page
macro_line|#  define flush_tlb_current_page&t;ev4_flush_tlb_current_page
macro_line|# else
DECL|macro|flush_tlb_current
macro_line|#  define flush_tlb_current&t;&t;ev5_flush_tlb_current
DECL|macro|flush_tlb_other
macro_line|#  define flush_tlb_other&t;&t;ev5_flush_tlb_other
DECL|macro|flush_tlb_current_page
macro_line|#  define flush_tlb_current_page&t;ev5_flush_tlb_current_page
macro_line|# endif
macro_line|#endif
macro_line|#ifdef __MMU_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__MMU_EXTERN_INLINE
macro_line|#undef __MMU_EXTERN_INLINE
macro_line|#endif
multiline_comment|/*&n; * Flush current user mapping.&n; */
DECL|function|flush_tlb
r_static
r_inline
r_void
id|flush_tlb
c_func
(paren
r_void
)paren
(brace
id|flush_tlb_current
c_func
(paren
id|current-&gt;mm
)paren
suffix:semicolon
)brace
macro_line|#ifndef __SMP__
multiline_comment|/*&n; * Flush everything (kernel mapping may also have&n; * changed due to vmalloc/vfree)&n; */
DECL|function|flush_tlb_all
r_static
r_inline
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
(brace
id|tbia
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Flush a specified user mapping&n; */
DECL|function|flush_tlb_mm
r_static
r_inline
r_void
id|flush_tlb_mm
c_func
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
op_ne
id|current-&gt;mm
)paren
id|flush_tlb_other
c_func
(paren
id|mm
)paren
suffix:semicolon
r_else
id|flush_tlb_current
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Page-granular tlb flush.&n; *&n; * do a tbisd (type = 2) normally, and a tbis (type = 3)&n; * if it is an executable mapping.  We want to avoid the&n; * itlb flush, because that potentially also does a&n; * icache flush.&n; */
DECL|function|flush_tlb_page
r_static
r_inline
r_void
id|flush_tlb_page
c_func
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
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_ne
id|current-&gt;mm
)paren
id|flush_tlb_other
c_func
(paren
id|mm
)paren
suffix:semicolon
r_else
id|flush_tlb_current_page
c_func
(paren
id|mm
comma
id|vma
comma
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Flush a specified range of user mapping:  on the&n; * Alpha we flush the whole user tlb.&n; */
DECL|function|flush_tlb_range
r_static
r_inline
r_void
id|flush_tlb_range
c_func
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
id|flush_tlb_mm
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
macro_line|#else /* __SMP__ */
r_extern
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_range
c_func
(paren
r_struct
id|mm_struct
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif /* __SMP__ */
multiline_comment|/*      &n; * Allocate and free page tables. The xxx_kernel() versions are&n; * used to allocate a kernel page table - this turns on ASN bits&n; * if any.&n; */
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
macro_line|#else
macro_line|#include &lt;asm/smp.h&gt;
DECL|macro|quicklists
mdefine_line|#define quicklists cpu_data[smp_processor_id()]
macro_line|#endif
DECL|macro|pgd_quicklist
mdefine_line|#define pgd_quicklist (quicklists.pgd_cache)
DECL|macro|pmd_quicklist
mdefine_line|#define pmd_quicklist ((unsigned long *)0)
DECL|macro|pte_quicklist
mdefine_line|#define pte_quicklist (quicklists.pte_cache)
DECL|macro|pgtable_cache_size
mdefine_line|#define pgtable_cache_size (quicklists.pgtable_cache_sz)
DECL|function|get_pgd_slow
r_extern
id|__inline__
id|pgd_t
op_star
id|get_pgd_slow
c_func
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
comma
op_star
id|init
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|init
op_assign
id|pgd_offset
c_func
(paren
op_amp
id|init_mm
comma
l_int|0UL
)paren
suffix:semicolon
id|memset
(paren
id|ret
comma
l_int|0
comma
id|USER_PTRS_PER_PGD
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
id|memcpy
(paren
id|ret
op_plus
id|USER_PTRS_PER_PGD
comma
id|init
op_plus
id|USER_PTRS_PER_PGD
comma
(paren
id|PTRS_PER_PGD
op_minus
id|USER_PTRS_PER_PGD
)paren
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
id|pgd_val
c_func
(paren
id|ret
(braket
id|PTRS_PER_PGD
)braket
)paren
op_assign
id|pte_val
c_func
(paren
id|mk_pte
c_func
(paren
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|ret
)paren
comma
id|PAGE_KERNEL
)paren
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
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
id|ret
(braket
l_int|1
)braket
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
)brace
r_else
id|ret
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_pgd_slow
c_func
(paren
)paren
suffix:semicolon
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
id|pgtable_cache_size
op_increment
suffix:semicolon
)brace
DECL|function|free_pgd_slow
r_extern
id|__inline__
r_void
id|free_pgd_slow
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pgd
)paren
suffix:semicolon
)brace
r_extern
id|pmd_t
op_star
id|get_pmd_slow
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|address_premasked
)paren
suffix:semicolon
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
(paren
r_int
r_int
op_star
)paren
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
id|ret
(braket
l_int|1
)braket
suffix:semicolon
id|pgtable_cache_size
op_decrement
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
id|pte_quicklist
suffix:semicolon
id|pte_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|pmd
suffix:semicolon
id|pgtable_cache_size
op_increment
suffix:semicolon
)brace
DECL|function|free_pmd_slow
r_extern
id|__inline__
r_void
id|free_pmd_slow
c_func
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
c_func
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
(paren
r_int
r_int
op_star
)paren
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
id|ret
(braket
l_int|1
)braket
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
id|pgtable_cache_size
op_increment
suffix:semicolon
)brace
DECL|function|free_pte_slow
r_extern
id|__inline__
r_void
id|free_pte_slow
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pte
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__bad_pte
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
suffix:semicolon
r_extern
r_void
id|__bad_pmd
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
suffix:semicolon
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
DECL|macro|pgd_alloc
mdefine_line|#define pgd_alloc()&t;&t;get_pgd_fast()
DECL|function|pte_alloc
r_extern
r_inline
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
id|pmd_set
c_func
(paren
id|pmd
comma
id|page
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
id|__bad_pte
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
DECL|function|pmd_alloc
r_extern
r_inline
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
id|address
op_assign
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
id|page
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
id|page
)paren
r_return
id|get_pmd_slow
c_func
(paren
id|pgd
comma
id|address
)paren
suffix:semicolon
id|pgd_set
c_func
(paren
id|pgd
comma
id|page
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
id|pgd_bad
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|__bad_pmd
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
id|address
suffix:semicolon
)brace
DECL|macro|pte_alloc_kernel
mdefine_line|#define pte_alloc_kernel&t;pte_alloc
DECL|macro|pmd_alloc_kernel
mdefine_line|#define pmd_alloc_kernel&t;pmd_alloc
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
r_inline
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
id|pgd_t
op_star
id|pgd
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
op_star
(paren
r_int
r_int
op_star
)paren
id|pgd
)paren
id|pgd
(braket
(paren
id|address
op_rshift
id|PGDIR_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PAGE
op_minus
l_int|1
)paren
)braket
op_assign
id|entry
suffix:semicolon
)brace
macro_line|#endif /* _ALPHA_PGALLOC_H */
eof
