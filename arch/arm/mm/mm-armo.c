multiline_comment|/*&n; * arch/arm/mm/mm-armo.c&n; *&n; * Page table sludge for older ARM processor architectures.&n; *&n; * Copyright (C) 1998-1999 Russell King&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/arch/memory.h&gt;
macro_line|#include &quot;map.h&quot;
DECL|macro|MEMC_TABLE_SIZE
mdefine_line|#define MEMC_TABLE_SIZE (256*sizeof(unsigned long))
DECL|macro|PGD_TABLE_SIZE
mdefine_line|#define PGD_TABLE_SIZE&t;(PTRS_PER_PGD * BYTES_PER_PTR)
DECL|variable|page_nr
r_int
id|page_nr
suffix:semicolon
r_extern
r_int
r_int
id|get_page_2k
c_func
(paren
r_int
id|prio
)paren
suffix:semicolon
r_extern
r_void
id|free_page_2k
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
id|pte_t
op_star
id|get_bad_pte_table
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Allocate a page table.  Note that we place the MEMC&n; * table before the page directory.  This means we can&n; * easily get to both tightly-associated data structures&n; * with a single pointer.&n; *&n; * We actually only need 1152 bytes, 896 bytes is wasted.&n; * We could try to fit 7 PTEs into that slot somehow.&n; */
DECL|function|alloc_pgd_table
r_static
r_inline
r_void
op_star
id|alloc_pgd_table
c_func
(paren
r_int
id|priority
)paren
(brace
r_int
r_int
id|pg2k
suffix:semicolon
id|pg2k
op_assign
id|get_page_2k
c_func
(paren
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pg2k
)paren
id|pg2k
op_add_assign
id|MEMC_TABLE_SIZE
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|pg2k
suffix:semicolon
)brace
DECL|function|free_pgd_slow
r_void
id|free_pgd_slow
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
r_int
r_int
id|tbl
op_assign
(paren
r_int
r_int
)paren
id|pgd
suffix:semicolon
id|tbl
op_sub_assign
id|MEMC_TABLE_SIZE
suffix:semicolon
id|free_page_2k
c_func
(paren
id|tbl
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * FIXME: the following over-allocates by 1600%&n; */
DECL|function|alloc_pte_table
r_static
r_inline
r_void
op_star
id|alloc_pte_table
c_func
(paren
r_int
id|size
comma
r_int
id|prio
)paren
(brace
r_if
c_cond
(paren
id|size
op_ne
l_int|128
)paren
id|printk
c_func
(paren
l_string|&quot;invalid table size&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|get_page_2k
c_func
(paren
id|prio
)paren
suffix:semicolon
)brace
DECL|function|free_pte_slow
r_void
id|free_pte_slow
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
r_int
r_int
id|tbl
op_assign
(paren
r_int
r_int
)paren
id|pte
suffix:semicolon
id|free_page_2k
c_func
(paren
id|tbl
)paren
suffix:semicolon
)brace
DECL|function|get_pgd_slow
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
id|pgd
op_assign
(paren
id|pgd_t
op_star
)paren
id|alloc_pgd_table
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
id|pmd_t
op_star
id|new_pmd
suffix:semicolon
r_if
c_cond
(paren
id|pgd
)paren
(brace
id|pgd_t
op_star
id|init
op_assign
id|pgd_offset
c_func
(paren
op_amp
id|init_mm
comma
l_int|0
)paren
suffix:semicolon
id|memzero
c_func
(paren
id|pgd
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
c_func
(paren
id|pgd
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
multiline_comment|/*&n;&t;&t; * On ARM, first page must always be allocated&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|pmd_alloc
c_func
(paren
id|pgd
comma
l_int|0
)paren
)paren
r_goto
id|nomem
suffix:semicolon
r_else
(brace
id|pmd_t
op_star
id|old_pmd
op_assign
id|pmd_offset
c_func
(paren
id|init
comma
l_int|0
)paren
suffix:semicolon
id|new_pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_alloc
c_func
(paren
id|new_pmd
comma
l_int|0
)paren
)paren
r_goto
id|nomem_pmd
suffix:semicolon
r_else
(brace
id|pte_t
op_star
id|new_pte
op_assign
id|pte_offset
c_func
(paren
id|new_pmd
comma
l_int|0
)paren
suffix:semicolon
id|pte_t
op_star
id|old_pte
op_assign
id|pte_offset
c_func
(paren
id|old_pmd
comma
l_int|0
)paren
suffix:semicolon
id|set_pte
(paren
id|new_pte
comma
op_star
id|old_pte
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* update MEMC tables */
id|cpu_memc_update_all
c_func
(paren
id|pgd
)paren
suffix:semicolon
)brace
r_return
id|pgd
suffix:semicolon
id|nomem_pmd
suffix:colon
id|pmd_free
c_func
(paren
id|new_pmd
)paren
suffix:semicolon
id|nomem
suffix:colon
id|free_pgd_slow
c_func
(paren
id|pgd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|get_pte_slow
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
id|offset
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|alloc_pte_table
c_func
(paren
id|PTRS_PER_PTE
op_star
r_sizeof
(paren
id|pte_t
)paren
comma
id|GFP_KERNEL
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
r_if
c_cond
(paren
id|pte
)paren
(brace
id|memzero
c_func
(paren
id|pte
comma
id|PTRS_PER_PTE
op_star
r_sizeof
(paren
id|pte_t
)paren
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
id|pte
)paren
)paren
suffix:semicolon
r_return
id|pte
op_plus
id|offset
suffix:semicolon
)brace
id|set_pmd
c_func
(paren
id|pmd
comma
id|mk_user_pmd
c_func
(paren
id|get_bad_pte_table
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|free_pte_slow
c_func
(paren
id|pte
)paren
suffix:semicolon
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
multiline_comment|/*&n; * Calculate the size of the DMA, normal and highmem zones.&n; * On 26-bit ARMs, we don&squot;t have any real DMA or highmem,&n; * so we allocate the whole memory as being DMA-capable.&n; */
DECL|function|zonesize_init
r_void
id|__init
id|zonesize_init
c_func
(paren
r_int
r_int
op_star
id|zone_size
)paren
(brace
r_int
id|i
suffix:semicolon
id|zone_size
(braket
l_int|0
)braket
op_assign
id|max_low_pfn
suffix:semicolon
id|zone_size
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|zone_size
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This contains the code to setup the memory map on an ARM2/ARM250/ARM3&n; * machine. This is both processor &amp; architecture specific, and requires&n; * some more work to get it to fit into our separate processor and&n; * architecture structure.&n; */
DECL|function|pagetable_init
r_void
id|__init
id|pagetable_init
c_func
(paren
r_void
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
id|i
suffix:semicolon
id|page_nr
op_assign
id|max_low_pfn
suffix:semicolon
id|pte
op_assign
id|alloc_bootmem_low_pages
c_func
(paren
id|PTRS_PER_PTE
op_star
r_sizeof
(paren
id|pte_t
)paren
)paren
suffix:semicolon
id|pte
(braket
l_int|0
)braket
op_assign
id|mk_pte_phys
c_func
(paren
id|PAGE_OFFSET
op_plus
l_int|491520
comma
id|PAGE_READONLY
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd_offset
c_func
(paren
id|swapper_pg_dir
comma
l_int|0
)paren
comma
id|mk_kernel_pmd
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|PTRS_PER_PGD
suffix:semicolon
id|i
op_increment
)paren
id|pgd_val
c_func
(paren
id|swapper_pg_dir
(braket
id|i
)braket
)paren
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|create_memmap_holes
r_void
id|__init
id|create_memmap_holes
c_func
(paren
r_void
)paren
(brace
)brace
eof
