multiline_comment|/*&n; *  linux/arch/arm/mm/mm-armv.c&n; *&n; *  Page table sludge for ARM v3 and v4 processor architectures.&n; *&n; *  Copyright (C) 1998-1999 Russell King&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &quot;map.h&quot;
DECL|variable|valid_addr_bitmap
r_int
r_int
op_star
id|valid_addr_bitmap
suffix:semicolon
r_extern
r_int
r_int
id|get_page_2k
c_func
(paren
r_int
id|priority
)paren
suffix:semicolon
r_extern
r_void
id|free_page_2k
c_func
(paren
r_int
r_int
id|page
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
multiline_comment|/*&n; * need to get a 16k page for level 1&n; */
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
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
l_int|2
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
id|pgd_offset_k
c_func
(paren
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
id|clean_cache_area
c_func
(paren
id|pgd
comma
id|PTRS_PER_PGD
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
c_func
(paren
id|new_pte
comma
op_star
id|old_pte
)paren
suffix:semicolon
)brace
)brace
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
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|pgd
comma
l_int|2
)paren
suffix:semicolon
r_return
l_int|NULL
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
r_if
c_cond
(paren
id|pgd
)paren
(brace
multiline_comment|/* can pgd be NULL? */
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
multiline_comment|/* pgd is always present and good */
id|pmd
op_assign
(paren
id|pmd_t
op_star
)paren
id|pgd
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
r_goto
id|free
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
id|pmd_ERROR
c_func
(paren
op_star
id|pmd
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_goto
id|free
suffix:semicolon
)brace
id|pte
op_assign
id|pte_offset
c_func
(paren
id|pmd
comma
l_int|0
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd
)paren
suffix:semicolon
id|pte_free
c_func
(paren
id|pte
)paren
suffix:semicolon
id|pmd_free
c_func
(paren
id|pmd
)paren
suffix:semicolon
)brace
id|free
suffix:colon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|pgd
comma
l_int|2
)paren
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
id|get_page_2k
c_func
(paren
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
l_int|2
op_star
id|PTRS_PER_PTE
op_star
r_sizeof
(paren
id|pte_t
)paren
)paren
suffix:semicolon
id|clean_cache_area
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
id|pte
op_add_assign
id|PTRS_PER_PTE
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
id|free_page_2k
c_func
(paren
(paren
r_int
r_int
)paren
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
DECL|function|get_pte_kernel_slow
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
id|get_page_2k
c_func
(paren
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
l_int|2
op_star
id|PTRS_PER_PTE
op_star
r_sizeof
(paren
id|pte_t
)paren
)paren
suffix:semicolon
id|clean_cache_area
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
id|pte
op_add_assign
id|PTRS_PER_PTE
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
id|mk_kernel_pmd
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
id|mk_kernel_pmd
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
id|free_page_2k
c_func
(paren
(paren
r_int
r_int
)paren
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
id|offset
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
id|free_page_2k
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|pte
op_minus
id|PTRS_PER_PTE
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create a SECTION PGD between VIRT and PHYS in domain&n; * DOMAIN with protection PROT&n; */
r_static
r_inline
r_void
DECL|function|alloc_init_section
id|alloc_init_section
c_func
(paren
r_int
r_int
id|virt
comma
r_int
r_int
id|phys
comma
r_int
id|prot
)paren
(brace
id|pmd_t
id|pmd
suffix:semicolon
id|pmd_val
c_func
(paren
id|pmd
)paren
op_assign
id|phys
op_or
id|prot
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd_offset
c_func
(paren
id|pgd_offset_k
c_func
(paren
id|virt
)paren
comma
id|virt
)paren
comma
id|pmd
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a PAGE mapping between VIRT and PHYS in domain&n; * DOMAIN with protection PROT.  Note that due to the&n; * way we map the PTEs, we must allocate two PTE_SIZE&squot;d&n; * blocks - one for the Linux pte table, and one for&n; * the hardware pte table.&n; */
r_static
r_inline
r_void
DECL|function|alloc_init_page
id|alloc_init_page
c_func
(paren
r_int
r_int
id|virt
comma
r_int
r_int
id|phys
comma
r_int
id|domain
comma
r_int
id|prot
)paren
(brace
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|pgd_offset_k
c_func
(paren
id|virt
)paren
comma
id|virt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmdp
)paren
)paren
(brace
id|pte_t
op_star
id|ptep
op_assign
id|alloc_bootmem_low_pages
c_func
(paren
l_int|2
op_star
id|PTRS_PER_PTE
op_star
r_sizeof
(paren
id|pte_t
)paren
)paren
suffix:semicolon
id|ptep
op_add_assign
id|PTRS_PER_PTE
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmdp
comma
id|__mk_pmd
c_func
(paren
id|ptep
comma
id|PMD_TYPE_TABLE
op_or
id|PMD_DOMAIN
c_func
(paren
id|domain
)paren
)paren
)paren
suffix:semicolon
)brace
id|ptep
op_assign
id|pte_offset
c_func
(paren
id|pmdp
comma
id|virt
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|mk_pte_phys
c_func
(paren
id|phys
comma
id|__pgprot
c_func
(paren
id|prot
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear any PGD mapping.  On a two-level page table system,&n; * the clearance is done by the middle-level functions (pmd)&n; * rather than the top-level (pgd) functions.&n; */
DECL|function|free_init_section
r_static
r_inline
r_void
id|free_init_section
c_func
(paren
r_int
r_int
id|virt
)paren
(brace
id|pmd_clear
c_func
(paren
id|pmd_offset
c_func
(paren
id|pgd_offset_k
c_func
(paren
id|virt
)paren
comma
id|virt
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create the page directory entries and any necessary&n; * page tables for the mapping specified by `md&squot;.  We&n; * are able to cope here with varying sizes and address&n; * offsets, and we take full advantage of sections.&n; */
DECL|function|create_mapping
r_static
r_void
id|__init
id|create_mapping
c_func
(paren
r_struct
id|map_desc
op_star
id|md
)paren
(brace
r_int
r_int
id|virt
comma
id|length
suffix:semicolon
r_int
id|prot_sect
comma
id|prot_pte
suffix:semicolon
r_int
id|off
suffix:semicolon
id|prot_pte
op_assign
id|L_PTE_PRESENT
op_or
id|L_PTE_YOUNG
op_or
id|L_PTE_DIRTY
op_or
(paren
id|md-&gt;prot_read
ques
c_cond
id|L_PTE_USER
suffix:colon
l_int|0
)paren
op_or
(paren
id|md-&gt;prot_write
ques
c_cond
id|L_PTE_WRITE
suffix:colon
l_int|0
)paren
op_or
(paren
id|md-&gt;cacheable
ques
c_cond
id|L_PTE_CACHEABLE
suffix:colon
l_int|0
)paren
op_or
(paren
id|md-&gt;bufferable
ques
c_cond
id|L_PTE_BUFFERABLE
suffix:colon
l_int|0
)paren
suffix:semicolon
id|prot_sect
op_assign
id|PMD_TYPE_SECT
op_or
id|PMD_DOMAIN
c_func
(paren
id|md-&gt;domain
)paren
op_or
(paren
id|md-&gt;prot_read
ques
c_cond
id|PMD_SECT_AP_READ
suffix:colon
l_int|0
)paren
op_or
(paren
id|md-&gt;prot_write
ques
c_cond
id|PMD_SECT_AP_WRITE
suffix:colon
l_int|0
)paren
op_or
(paren
id|md-&gt;cacheable
ques
c_cond
id|PMD_SECT_CACHEABLE
suffix:colon
l_int|0
)paren
op_or
(paren
id|md-&gt;bufferable
ques
c_cond
id|PMD_SECT_BUFFERABLE
suffix:colon
l_int|0
)paren
suffix:semicolon
id|virt
op_assign
id|md
op_member_access_from_pointer
r_virtual
suffix:semicolon
id|off
op_assign
id|md-&gt;physical
op_minus
id|virt
suffix:semicolon
id|length
op_assign
id|md-&gt;length
suffix:semicolon
r_while
c_loop
(paren
(paren
id|virt
op_amp
l_int|1048575
op_logical_or
(paren
id|virt
op_plus
id|off
)paren
op_amp
l_int|1048575
)paren
op_logical_and
id|length
op_ge
id|PAGE_SIZE
)paren
(brace
id|alloc_init_page
c_func
(paren
id|virt
comma
id|virt
op_plus
id|off
comma
id|md-&gt;domain
comma
id|prot_pte
)paren
suffix:semicolon
id|virt
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|length
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
op_ge
id|PGDIR_SIZE
)paren
(brace
id|alloc_init_section
c_func
(paren
id|virt
comma
id|virt
op_plus
id|off
comma
id|prot_sect
)paren
suffix:semicolon
id|virt
op_add_assign
id|PGDIR_SIZE
suffix:semicolon
id|length
op_sub_assign
id|PGDIR_SIZE
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
op_ge
id|PAGE_SIZE
)paren
(brace
id|alloc_init_page
c_func
(paren
id|virt
comma
id|virt
op_plus
id|off
comma
id|md-&gt;domain
comma
id|prot_pte
)paren
suffix:semicolon
id|virt
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|length
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Initial boot-time mapping.  This covers just the zero page, kernel and&n; * the flush area.  NB: it must be sorted by virtual address, and no&n; * virtual address overlaps.&n; *  init_map[2..4] are for architectures with banked memory.&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|init_map
(braket
)braket
id|__initdata
op_assign
(brace
(brace
l_int|0
comma
l_int|0
comma
id|PAGE_SIZE
comma
id|DOMAIN_USER
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
)brace
comma
multiline_comment|/* zero page     */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|DOMAIN_KERNEL
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
comma
multiline_comment|/* kernel memory */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|DOMAIN_KERNEL
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
comma
multiline_comment|/* (4 banks)&t;  */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|DOMAIN_KERNEL
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|DOMAIN_KERNEL
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
id|PGDIR_SIZE
comma
id|DOMAIN_KERNEL
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
)brace
comma
multiline_comment|/* cache flush 1 */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|DOMAIN_KERNEL
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
)brace
multiline_comment|/* cache flush 2 */
)brace
suffix:semicolon
DECL|macro|NR_INIT_MAPS
mdefine_line|#define NR_INIT_MAPS (sizeof(init_map) / sizeof(init_map[0]))
multiline_comment|/*&n; * Calculate the size of the DMA, normal and highmem zones.&n; * On ARM, we don&squot;t have any problems with DMA, so all memory&n; * is allocated to the DMA zone.  We also don&squot;t have any&n; * highmem either.&n; */
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
l_int|0
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|meminfo.nr_banks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|meminfo.bank
(braket
id|i
)braket
dot
id|size
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
id|end
op_assign
(paren
id|meminfo.bank
(braket
id|i
)braket
dot
id|start
op_plus
id|meminfo.bank
(braket
id|i
)braket
dot
id|size
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|zone_size
(braket
l_int|0
)braket
)paren
id|zone_size
(braket
l_int|0
)braket
op_assign
id|end
suffix:semicolon
)brace
)brace
)brace
DECL|function|pagetable_init
r_void
id|__init
id|pagetable_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|address
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Setup the above mappings&n;&t; */
id|init_map
(braket
l_int|0
)braket
dot
id|physical
op_assign
id|PHYS_OFFSET
suffix:semicolon
id|init_map
(braket
l_int|5
)braket
dot
id|physical
op_assign
id|FLUSH_BASE_PHYS
suffix:semicolon
id|init_map
(braket
l_int|5
)braket
dot
r_virtual
op_assign
id|FLUSH_BASE
suffix:semicolon
macro_line|#ifdef FLUSH_BASE_MINICACHE
id|init_map
(braket
l_int|6
)braket
dot
id|physical
op_assign
id|FLUSH_BASE_PHYS
op_plus
id|PGDIR_SIZE
suffix:semicolon
id|init_map
(braket
l_int|6
)braket
dot
r_virtual
op_assign
id|FLUSH_BASE_MINICACHE
suffix:semicolon
id|init_map
(braket
l_int|6
)braket
dot
id|length
op_assign
id|PGDIR_SIZE
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|meminfo.nr_banks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|init_map
(braket
id|i
op_plus
l_int|1
)braket
dot
id|physical
op_assign
id|PHYS_OFFSET
op_plus
id|meminfo.bank
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|init_map
(braket
id|i
op_plus
l_int|1
)braket
dot
r_virtual
op_assign
id|PAGE_OFFSET
op_plus
id|meminfo.bank
(braket
id|i
)braket
dot
id|start
suffix:semicolon
id|init_map
(braket
id|i
op_plus
l_int|1
)braket
dot
id|length
op_assign
id|meminfo.bank
(braket
id|i
)braket
dot
id|size
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Go through the initial mappings, but clear out any&n;&t; * pgdir entries that are not in the description.&n;&t; */
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|address
OL
id|init_map
(braket
id|i
)braket
dot
r_virtual
op_logical_or
id|i
op_eq
id|NR_INIT_MAPS
)paren
(brace
id|free_init_section
c_func
(paren
id|address
)paren
suffix:semicolon
id|address
op_add_assign
id|PGDIR_SIZE
suffix:semicolon
)brace
r_else
(brace
id|create_mapping
c_func
(paren
id|init_map
op_plus
id|i
)paren
suffix:semicolon
id|address
op_assign
id|init_map
(braket
id|i
)braket
dot
r_virtual
op_plus
id|init_map
(braket
id|i
)braket
dot
id|length
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PGDIR_SIZE
op_minus
l_int|1
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
r_do
(brace
id|i
op_add_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|init_map
(braket
id|i
)braket
dot
id|length
op_eq
l_int|0
op_logical_and
id|i
OL
id|NR_INIT_MAPS
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|address
op_ne
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Create the architecture specific mappings&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|io_desc_size
suffix:semicolon
id|i
op_increment
)paren
id|create_mapping
c_func
(paren
id|io_desc
op_plus
id|i
)paren
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The mem_map array can get very big.  Mark the end of the valid mem_map&n; * banks with PG_skip, and setup the address validity bitmap.&n; */
DECL|function|create_memmap_holes
r_void
id|__init
id|create_memmap_holes
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start_pfn
comma
id|end_pfn
op_assign
op_minus
l_int|1
suffix:semicolon
r_struct
id|page
op_star
id|pg
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|sz
comma
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|meminfo.nr_banks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|meminfo.bank
(braket
id|i
)braket
dot
id|size
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|start_pfn
op_assign
id|meminfo.bank
(braket
id|i
)braket
dot
id|start
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/*&n;&t;&t; * subtle here - if we have a full bank, then&n;&t;&t; * start_pfn == end_pfn, and we don&squot;t want to&n;&t;&t; * set PG_skip, or next_hash&n;&t;&t; */
r_if
c_cond
(paren
id|pg
op_logical_and
id|start_pfn
op_ne
id|end_pfn
)paren
(brace
id|set_bit
c_func
(paren
id|PG_skip
comma
op_amp
id|pg-&gt;flags
)paren
suffix:semicolon
id|pg-&gt;next_hash
op_assign
id|mem_map
op_plus
id|start_pfn
suffix:semicolon
id|start_pfn
op_assign
id|PAGE_ALIGN
c_func
(paren
id|__pa
c_func
(paren
id|pg
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|end_pfn
op_assign
id|__pa
c_func
(paren
id|pg-&gt;next_hash
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|end_pfn
op_ne
id|start_pfn
)paren
id|free_bootmem
c_func
(paren
id|start_pfn
comma
id|end_pfn
op_minus
id|start_pfn
)paren
suffix:semicolon
id|pg
op_assign
l_int|NULL
suffix:semicolon
)brace
id|end_pfn
op_assign
(paren
id|meminfo.bank
(braket
id|i
)braket
dot
id|start
op_plus
id|meminfo.bank
(braket
id|i
)braket
dot
id|size
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|end_pfn
op_ne
id|meminfo.end
op_rshift
id|PAGE_SHIFT
)paren
id|pg
op_assign
id|mem_map
op_plus
id|end_pfn
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pg
)paren
(brace
id|set_bit
c_func
(paren
id|PG_skip
comma
op_amp
id|pg-&gt;flags
)paren
suffix:semicolon
id|pg-&gt;next_hash
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
eof
