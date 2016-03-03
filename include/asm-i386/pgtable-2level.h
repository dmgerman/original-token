macro_line|#ifndef _I386_PGTABLE_2LEVEL_H
DECL|macro|_I386_PGTABLE_2LEVEL_H
mdefine_line|#define _I386_PGTABLE_2LEVEL_H
multiline_comment|/*&n; * traditional i386 two-level paging structure:&n; */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;22
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;1024
multiline_comment|/*&n; * the i386 is two-level, so we don&squot;t really have any&n; * PMD directory physically.&n; */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;22
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;1
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;1024
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %08lx.&bslash;n&quot;, __FILE__, __LINE__, (e).pte_low)
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
DECL|function|pgd_none
r_extern
r_inline
r_int
id|pgd_none
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
l_int|1
suffix:semicolon
)brace
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(xp)&t;&t;&t;&t;do { } while (0)
multiline_comment|/*&n; * Certain architectures need to do special things when PTEs&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval) (*(pteptr) = pteval)
multiline_comment|/*&n; * (pmds are folded into pgds so this doesnt get actually called,&n; * but the define is needed for a generic inline function.)&n; */
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdptr, pmdval) (*(pmdptr) = pmdval)
DECL|macro|set_pgd
mdefine_line|#define set_pgd(pgdptr, pgdval) (*(pgdptr) = pgdval)
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd) &bslash;&n;((unsigned long) __va(pgd_val(pgd) &amp; PAGE_MASK))
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
id|dir
suffix:semicolon
)brace
DECL|macro|ptep_get_and_clear
mdefine_line|#define ptep_get_and_clear(xp)&t;__pte(xchg(&amp;(xp)-&gt;pte_low, 0))
DECL|macro|pte_same
mdefine_line|#define pte_same(a, b)&t;&t;((a).pte_low == (b).pte_low)
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;(mem_map+((unsigned long)(((x).pte_low &gt;&gt; PAGE_SHIFT))))
DECL|macro|pte_none
mdefine_line|#define pte_none(x)&t;&t;(!(x).pte_low)
DECL|macro|__mk_pte
mdefine_line|#define __mk_pte(page_nr,pgprot) __pte(((page_nr) &lt;&lt; PAGE_SHIFT) | pgprot_val(pgprot))
macro_line|#endif /* _I386_PGTABLE_2LEVEL_H */
eof
