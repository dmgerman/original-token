multiline_comment|/* $Id: pgalloc.h,v 1.13 2000/11/06 06:59:04 davem Exp $ */
macro_line|#ifndef _SPARC64_PGALLOC_H
DECL|macro|_SPARC64_PGALLOC_H
mdefine_line|#define _SPARC64_PGALLOC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* Cache and TLB flush operations. */
multiline_comment|/* These are the same regardless of whether this is an SMP kernel or not. */
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(__mm) &bslash;&n;&t;do { if ((__mm) == current-&gt;mm) flushw_user(); } while(0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(mm, start, end) &bslash;&n;&t;flush_cache_mm(mm)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, page) &bslash;&n;&t;flush_cache_mm((vma)-&gt;vm_mm)
multiline_comment|/* These operations are unnecessary on the SpitFire since D-CACHE is write-through. */
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)&t;&t;do { } while (0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;&t;do { } while (0)
r_extern
r_void
id|__flush_dcache_page
c_func
(paren
r_void
op_star
id|addr
comma
r_int
id|flush_icache
)paren
suffix:semicolon
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page) &bslash;&n;do {&t;if ((page)-&gt;mapping &amp;&amp; !(page)-&gt;mapping-&gt;i_mmap &amp;&amp; !(page)-&gt;mapping-&gt;i_mmap_shared) &bslash;&n;&t;&t;set_bit(PG_dcache_dirty, &amp;(page)-&gt;flags); &bslash;&n;&t;else &bslash;&n;&t;&t;__flush_dcache_page((page)-&gt;virtual, &bslash;&n;&t;&t;&t;&t;    (page)-&gt;mapping != NULL); &bslash;&n;} while(0)
r_extern
r_void
id|__flush_dcache_range
c_func
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
r_extern
r_void
id|__flush_cache_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__flush_tlb_mm
c_func
(paren
r_int
r_int
id|context
comma
r_int
r_int
id|r
)paren
suffix:semicolon
r_extern
r_void
id|__flush_tlb_range
c_func
(paren
r_int
r_int
id|context
comma
r_int
r_int
id|start
comma
r_int
r_int
id|r
comma
r_int
r_int
id|end
comma
r_int
r_int
id|pgsz
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|__flush_tlb_page
c_func
(paren
r_int
r_int
id|context
comma
r_int
r_int
id|page
comma
r_int
r_int
id|r
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;__flush_cache_all()
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;__flush_tlb_all()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(__mm) &bslash;&n;do { if(CTX_VALID((__mm)-&gt;context)) &bslash;&n;&t;__flush_tlb_mm(CTX_HWBITS((__mm)-&gt;context), SECONDARY_CONTEXT); &bslash;&n;} while(0)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(__mm, start, end) &bslash;&n;do { if(CTX_VALID((__mm)-&gt;context)) { &bslash;&n;&t;unsigned long __start = (start)&amp;PAGE_MASK; &bslash;&n;&t;unsigned long __end = (end)&amp;PAGE_MASK; &bslash;&n;&t;__flush_tlb_range(CTX_HWBITS((__mm)-&gt;context), __start, &bslash;&n;&t;&t;&t;  SECONDARY_CONTEXT, __end, PAGE_SIZE, &bslash;&n;&t;&t;&t;  (__end - __start)); &bslash;&n;     } &bslash;&n;} while(0)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma, page) &bslash;&n;do { struct mm_struct *__mm = (vma)-&gt;vm_mm; &bslash;&n;     if(CTX_VALID(__mm-&gt;context)) &bslash;&n;&t;__flush_tlb_page(CTX_HWBITS(__mm-&gt;context), (page)&amp;PAGE_MASK, &bslash;&n;&t;&t;&t; SECONDARY_CONTEXT); &bslash;&n;} while(0)
macro_line|#else /* CONFIG_SMP */
r_extern
r_void
id|smp_flush_cache_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|smp_flush_tlb_range
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
suffix:semicolon
r_extern
r_void
id|smp_flush_tlb_page
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|page
)paren
suffix:semicolon
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;smp_flush_cache_all()
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;smp_flush_tlb_all()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm)&t;smp_flush_tlb_mm(mm)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(mm, start, end) &bslash;&n;&t;smp_flush_tlb_range(mm, start, end)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma, page) &bslash;&n;&t;smp_flush_tlb_page((vma)-&gt;vm_mm, page)
macro_line|#endif /* ! CONFIG_SMP */
multiline_comment|/* This will change for Cheetah and later chips. */
DECL|macro|VPTE_BASE
mdefine_line|#define VPTE_BASE&t;0xfffffffe00000000
DECL|function|flush_tlb_pgtables
r_extern
id|__inline__
r_void
id|flush_tlb_pgtables
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
multiline_comment|/* Note the signed type.  */
r_int
id|s
op_assign
id|start
comma
id|e
op_assign
id|end
suffix:semicolon
r_if
c_cond
(paren
id|s
OG
id|e
)paren
multiline_comment|/* Nobody should call us with start below VM hole and end above.&n;&t;&t;   See if it is really true.  */
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* Currently free_pgtables guarantees this.  */
id|s
op_and_assign
id|PMD_MASK
suffix:semicolon
id|e
op_assign
(paren
id|e
op_plus
id|PMD_SIZE
op_minus
l_int|1
)paren
op_amp
id|PMD_MASK
suffix:semicolon
macro_line|#endif
id|flush_tlb_range
c_func
(paren
id|mm
comma
id|VPTE_BASE
op_plus
(paren
id|s
op_rshift
(paren
id|PAGE_SHIFT
op_minus
l_int|3
)paren
)paren
comma
id|VPTE_BASE
op_plus
(paren
id|e
op_rshift
(paren
id|PAGE_SHIFT
op_minus
l_int|3
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Page table allocation/freeing. */
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* Sliiiicck */
DECL|macro|pgt_quicklists
mdefine_line|#define pgt_quicklists&t;cpu_data[smp_processor_id()]
macro_line|#else
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
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|pgcache_size
r_int
r_int
id|pgcache_size
suffix:semicolon
DECL|member|pgdcache_size
r_int
r_int
id|pgdcache_size
suffix:semicolon
)brace
id|pgt_quicklists
suffix:semicolon
macro_line|#endif
DECL|macro|pgd_quicklist
mdefine_line|#define pgd_quicklist&t;&t;(pgt_quicklists.pgd_cache)
DECL|macro|pmd_quicklist
mdefine_line|#define pmd_quicklist&t;&t;((unsigned long *)0)
DECL|macro|pte_quicklist
mdefine_line|#define pte_quicklist&t;&t;(pgt_quicklists.pte_cache)
DECL|macro|pgtable_cache_size
mdefine_line|#define pgtable_cache_size&t;(pgt_quicklists.pgcache_size)
DECL|macro|pgd_cache_size
mdefine_line|#define pgd_cache_size&t;&t;(pgt_quicklists.pgdcache_size)
macro_line|#ifndef CONFIG_SMP
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
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|pgd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;pprev_hash
)paren
(brace
(paren
r_int
r_int
op_star
)paren
id|page-&gt;next_hash
op_assign
id|pgd_quicklist
suffix:semicolon
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|page
suffix:semicolon
)brace
(paren
r_int
r_int
)paren
id|page-&gt;pprev_hash
op_or_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|pgd
op_amp
(paren
id|PAGE_SIZE
op_div
l_int|2
)paren
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|1
)paren
suffix:semicolon
id|pgd_cache_size
op_increment
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
r_struct
id|page
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
r_struct
id|page
op_star
)paren
id|pgd_quicklist
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
r_int
id|mask
op_assign
(paren
r_int
r_int
)paren
id|ret-&gt;pprev_hash
suffix:semicolon
r_int
r_int
id|off
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
l_int|1
)paren
id|mask
op_and_assign
op_complement
l_int|1
suffix:semicolon
r_else
(brace
id|off
op_assign
id|PAGE_SIZE
op_div
l_int|2
suffix:semicolon
id|mask
op_and_assign
op_complement
l_int|2
suffix:semicolon
)brace
(paren
r_int
r_int
)paren
id|ret-&gt;pprev_hash
op_assign
id|mask
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mask
)paren
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|ret-&gt;next_hash
suffix:semicolon
id|ret
op_assign
(paren
r_struct
id|page
op_star
)paren
(paren
id|__page_address
c_func
(paren
id|ret
)paren
op_plus
id|off
)paren
suffix:semicolon
id|pgd_cache_size
op_decrement
suffix:semicolon
)brace
r_else
(brace
r_struct
id|page
op_star
id|page
op_assign
id|alloc_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|ret
op_assign
(paren
r_struct
id|page
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|clear_page
c_func
(paren
id|ret
)paren
suffix:semicolon
(paren
r_int
r_int
)paren
id|page-&gt;pprev_hash
op_assign
l_int|2
suffix:semicolon
(paren
r_int
r_int
op_star
)paren
id|page-&gt;next_hash
op_assign
id|pgd_quicklist
suffix:semicolon
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|page
suffix:semicolon
id|pgd_cache_size
op_increment
suffix:semicolon
)brace
)brace
r_return
(paren
id|pgd_t
op_star
)paren
id|ret
suffix:semicolon
)brace
macro_line|#else /* CONFIG_SMP */
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
l_int|0
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
(paren
r_int
r_int
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
(brace
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
id|pgd_t
op_star
)paren
id|ret
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
macro_line|#endif /* CONFIG_SMP */
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
r_int
id|color
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pte_quicklist
(braket
id|color
)braket
op_eq
l_int|NULL
)paren
id|color
op_assign
l_int|1
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
(braket
id|color
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|pte_quicklist
(braket
id|color
)braket
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
r_int
r_int
id|color
suffix:semicolon
id|color
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|pmd
op_rshift
id|PAGE_SHIFT
)paren
op_amp
l_int|0x1UL
)paren
suffix:semicolon
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
(braket
id|color
)braket
suffix:semicolon
id|pte_quicklist
(braket
id|color
)braket
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
comma
r_int
r_int
id|color
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
r_int
r_int
id|color
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
(braket
id|color
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|pte_quicklist
(braket
id|color
)braket
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
r_int
r_int
id|color
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|pte
op_rshift
id|PAGE_SHIFT
)paren
op_amp
l_int|0x1
)paren
suffix:semicolon
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
(braket
id|color
)braket
suffix:semicolon
id|pte_quicklist
(braket
id|color
)braket
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
multiline_comment|/* Be careful, address can be just about anything... */
r_int
r_int
id|color
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|pmd
)paren
op_rshift
l_int|2UL
)paren
op_amp
l_int|0x1UL
suffix:semicolon
id|pte_t
op_star
id|page
op_assign
id|get_pte_fast
c_func
(paren
id|color
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
comma
id|color
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
id|REAL_PTRS_PER_PMD
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
mdefine_line|#define pte_alloc_kernel(pmd, addr)&t;pte_alloc(pmd, addr)
DECL|macro|pmd_alloc_kernel
mdefine_line|#define pmd_alloc_kernel(pgd, addr)&t;pmd_alloc(pgd, addr)
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
macro_line|#endif /* _SPARC64_PGALLOC_H */
eof
