multiline_comment|/*&n; * arch/arm/mm/mm-arc.c&n; *&n; * Extra MM routines for the Archimedes architecture&n; *&n; * Copyright (C) 1998 Russell King&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|variable|phys_screen_end
r_int
r_int
id|phys_screen_end
suffix:semicolon
multiline_comment|/*&n; * This routine needs more work to make it dynamically release/allocate mem!&n; */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
r_int
id|map_screen_mem
c_func
(paren
r_int
r_int
id|log_start
comma
r_int
r_int
id|kmem
comma
r_int
id|update
)paren
)paren
(brace
r_static
r_int
id|updated
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|updated
)paren
r_return
l_int|0
suffix:semicolon
id|updated
op_assign
id|update
suffix:semicolon
r_if
c_cond
(paren
id|update
)paren
(brace
r_int
r_int
id|address
op_assign
id|log_start
comma
id|offset
suffix:semicolon
id|pgd_t
op_star
id|pgdp
suffix:semicolon
id|kmem
op_assign
(paren
id|kmem
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
suffix:semicolon
id|pgdp
op_assign
id|pgd_offset
(paren
op_amp
id|init_mm
comma
id|address
)paren
suffix:semicolon
multiline_comment|/* +31 */
id|offset
op_assign
id|SCREEN_START
suffix:semicolon
r_while
c_loop
(paren
id|address
OL
id|SCREEN1_END
)paren
(brace
r_int
r_int
id|addr_pmd
comma
id|end_pmd
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
multiline_comment|/* if (pgd_none (*pgdp)) alloc pmd */
id|pmdp
op_assign
id|pmd_offset
(paren
id|pgdp
comma
id|address
)paren
suffix:semicolon
multiline_comment|/* +0 */
id|addr_pmd
op_assign
id|address
op_amp
op_complement
id|PGDIR_MASK
suffix:semicolon
multiline_comment|/* 088000 */
id|end_pmd
op_assign
id|addr_pmd
op_plus
id|SCREEN1_END
op_minus
id|address
suffix:semicolon
multiline_comment|/* 100000 */
r_if
c_cond
(paren
id|end_pmd
OG
id|PGDIR_SIZE
)paren
id|end_pmd
op_assign
id|PGDIR_SIZE
suffix:semicolon
r_do
(brace
r_int
r_int
id|addr_pte
comma
id|end_pte
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
(paren
op_star
id|pmdp
)paren
)paren
(brace
id|pte_t
op_star
id|new_pte
op_assign
(paren
id|pte_t
op_star
)paren
id|kmem
suffix:semicolon
id|kmem
op_add_assign
id|PTRS_PER_PTE
op_star
id|BYTES_PER_PTR
suffix:semicolon
id|memzero
(paren
id|new_pte
comma
id|PTRS_PER_PTE
op_star
id|BYTES_PER_PTR
)paren
suffix:semicolon
id|set_pmd
(paren
id|pmdp
comma
id|mk_pmd
c_func
(paren
id|new_pte
)paren
)paren
suffix:semicolon
)brace
id|ptep
op_assign
id|pte_offset
(paren
id|pmdp
comma
id|addr_pmd
)paren
suffix:semicolon
multiline_comment|/* +11 */
id|addr_pte
op_assign
id|addr_pmd
op_amp
op_complement
id|PMD_MASK
suffix:semicolon
multiline_comment|/* 088000 */
id|end_pte
op_assign
id|addr_pte
op_plus
id|end_pmd
op_minus
id|addr_pmd
suffix:semicolon
multiline_comment|/* 100000 */
r_if
c_cond
(paren
id|end_pte
OG
id|PMD_SIZE
)paren
id|end_pte
op_assign
id|PMD_SIZE
suffix:semicolon
r_do
(brace
id|set_pte
(paren
id|ptep
comma
id|mk_pte
c_func
(paren
id|offset
comma
id|PAGE_KERNEL
)paren
)paren
suffix:semicolon
id|addr_pte
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|offset
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|ptep
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|addr_pte
OL
id|end_pte
)paren
suffix:semicolon
id|pmdp
op_increment
suffix:semicolon
id|addr_pmd
op_assign
(paren
id|addr_pmd
op_plus
id|PMD_SIZE
)paren
op_amp
id|PMD_MASK
suffix:semicolon
)brace
r_while
c_loop
(paren
id|addr_pmd
OL
id|end_pmd
)paren
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
id|pgdp
op_increment
suffix:semicolon
)brace
id|phys_screen_end
op_assign
id|offset
suffix:semicolon
id|flush_tlb_all
(paren
)paren
suffix:semicolon
id|update_memc_all
(paren
)paren
suffix:semicolon
)brace
r_return
id|kmem
suffix:semicolon
)brace
eof
