macro_line|#ifndef _I386_PGTABLE_3LEVEL_H
DECL|macro|_I386_PGTABLE_3LEVEL_H
mdefine_line|#define _I386_PGTABLE_3LEVEL_H
multiline_comment|/*&n; * Intel Physical Address Extension (PAE) Mode - three-level page&n; * tables on PPro+ CPUs.&n; *&n; * Copyright (C) 1999 Ingo Molnar &lt;mingo@redhat.com&gt;&n; */
multiline_comment|/*&n; * PGDIR_SHIFT determines what a top-level page table entry can map&n; */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;30
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;4
multiline_comment|/*&n; * PMD_SHIFT determines the size of the area a middle-level&n; * page table can map&n; */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;21
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;512
multiline_comment|/*&n; * entries per page directory level&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;512
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %016Lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %016Lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %016Lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
multiline_comment|/*&n; * Subtle, in PAE mode we cannot have zeroes in the top level&n; * page directory, the CPU enforces this.&n; */
DECL|macro|pgd_none
mdefine_line|#define pgd_none(x)&t;(pgd_val(x) == 1ULL)
DECL|function|pgd_bad
r_extern
r_inline
r_int
id|pgd_bad
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pgd_present
r_extern
r_inline
r_int
id|pgd_present
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
op_logical_neg
id|pgd_none
c_func
(paren
id|pgd
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Pentium-II errata A13: in PAE mode we explicitly have to flush&n; * the TLB via cr3 if the top-level pgd is changed... This was one tough&n; * thing to find out - guess i should first read all the documentation&n; * next time around ;)&n; */
DECL|function|__pgd_clear
r_extern
r_inline
r_void
id|__pgd_clear
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|pgd_val
c_func
(paren
op_star
id|pgd
)paren
op_assign
l_int|1
suffix:semicolon
singleline_comment|// no zero allowed!
)brace
DECL|function|pgd_clear
r_extern
r_inline
r_void
id|pgd_clear
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|__pgd_clear
c_func
(paren
id|pgd
)paren
suffix:semicolon
id|__flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd) &bslash;&n;((unsigned long) __va(pgd_val(pgd) &amp; PAGE_MASK))
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir, address) ((pmd_t *) pgd_page(*(dir)) + &bslash;&n;&t;&t;&t;__pmd_offset(address))
DECL|function|get_pmd_slow
r_extern
id|__inline__
id|pmd_t
op_star
id|get_pmd_slow
c_func
(paren
r_void
)paren
(brace
id|pmd_t
op_star
id|ret
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
id|ret
)paren
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
r_return
id|ret
suffix:semicolon
)brace
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
id|pmd_quicklist
)paren
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
id|get_pmd_slow
c_func
(paren
)paren
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|pgd
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
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
id|page
op_assign
id|get_pmd_slow
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
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
id|pgd_val
c_func
(paren
op_star
id|pgd
)paren
op_assign
l_int|1
op_plus
id|__pa
c_func
(paren
id|page
)paren
suffix:semicolon
id|__flush_tlb
c_func
(paren
)paren
suffix:semicolon
r_return
id|page
op_plus
id|address
suffix:semicolon
)brace
r_else
id|free_pmd_fast
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_else
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
macro_line|#endif /* _I386_PGTABLE_3LEVEL_H */
eof
