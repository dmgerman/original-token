multiline_comment|/*&n; *  linux/arch/m68k/mm/init.c&n; *&n; *  Copyright (C) 1995  Hamish Macdonald&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_RAM
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
r_extern
r_void
id|die_if_kernel
c_func
(paren
r_char
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|init_kpointer_table
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|show_net_buffers
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * BAD_PAGE is the page that is used for page faults when linux&n; * is out-of-memory. Older versions of linux just did a&n; * do_exit(), but using this instead means there is less risk&n; * for a process dying in kernel mode, possibly leaving an inode&n; * unused etc..&n; *&n; * BAD_PAGETABLE is the accompanying page-table: it is initialized&n; * to point to BAD_PAGE entries.&n; *&n; * ZERO_PAGE is a special page that is used for zero-initialized&n; * data and COW.&n; */
DECL|variable|empty_bad_page_table
r_static
r_int
r_int
id|empty_bad_page_table
suffix:semicolon
DECL|function|__bad_pagetable
id|pte_t
op_star
id|__bad_pagetable
c_func
(paren
r_void
)paren
(brace
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|empty_bad_page_table
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_return
(paren
id|pte_t
op_star
)paren
id|empty_bad_page_table
suffix:semicolon
)brace
DECL|variable|empty_bad_page
r_static
r_int
r_int
id|empty_bad_page
suffix:semicolon
DECL|function|__bad_page
id|pte_t
id|__bad_page
c_func
(paren
r_void
)paren
(brace
id|memset
(paren
(paren
r_void
op_star
)paren
id|empty_bad_page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_return
id|pte_mkdirty
c_func
(paren
id|mk_pte
c_func
(paren
id|empty_bad_page
comma
id|PAGE_SHARED
)paren
)paren
suffix:semicolon
)brace
DECL|variable|empty_zero_page
r_int
r_int
id|empty_zero_page
suffix:semicolon
DECL|function|show_mem
r_void
id|show_mem
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_int
id|free
op_assign
l_int|0
comma
id|total
op_assign
l_int|0
comma
id|reserved
op_assign
l_int|0
comma
id|nonshared
op_assign
l_int|0
comma
id|shared
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nMem-info:&bslash;n&quot;
)paren
suffix:semicolon
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Free swap:       %6dkB&bslash;n&quot;
comma
id|nr_swap_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
id|i
op_assign
id|max_mapnr
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
(brace
id|total
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|mem_map
op_plus
id|i
)paren
)paren
id|reserved
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|mem_map
(braket
id|i
)braket
dot
id|count
)paren
)paren
id|free
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|mem_map
(braket
id|i
)braket
dot
id|count
)paren
op_eq
l_int|1
)paren
id|nonshared
op_increment
suffix:semicolon
r_else
id|shared
op_add_assign
id|atomic_read
c_func
(paren
op_amp
id|mem_map
(braket
id|i
)braket
dot
id|count
)paren
op_minus
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%d pages of RAM&bslash;n&quot;
comma
id|total
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d free pages&bslash;n&quot;
comma
id|free
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d reserved pages&bslash;n&quot;
comma
id|reserved
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages nonshared&bslash;n&quot;
comma
id|nonshared
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages shared&bslash;n&quot;
comma
id|shared
)paren
suffix:semicolon
id|show_buffers
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET
id|show_net_buffers
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifndef mm_cachebits
multiline_comment|/*&n; * Bits to add to page descriptors for &quot;normal&quot; caching mode.&n; * For 68020/030 this is 0.&n; * For 68040, this is _PAGE_CACHE040 (cachable, copyback)&n; */
DECL|variable|mm_cachebits
r_int
r_int
id|mm_cachebits
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
DECL|function|kernel_page_table
id|pte_t
op_star
id|kernel_page_table
(paren
r_int
r_int
op_star
id|memavailp
)paren
(brace
id|pte_t
op_star
id|ptablep
suffix:semicolon
r_if
c_cond
(paren
id|memavailp
)paren
(brace
id|ptablep
op_assign
(paren
id|pte_t
op_star
)paren
op_star
id|memavailp
suffix:semicolon
op_star
id|memavailp
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_else
id|ptablep
op_assign
(paren
id|pte_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
id|nocache_page
(paren
(paren
r_int
r_int
)paren
id|ptablep
)paren
suffix:semicolon
r_return
id|ptablep
suffix:semicolon
)brace
DECL|function|map_chunk
r_static
r_int
r_int
id|map_chunk
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
comma
r_int
r_int
op_star
id|memavailp
)paren
(brace
DECL|macro|ONEMEG
mdefine_line|#define ONEMEG&t;(1024*1024)
DECL|macro|L3TREESIZE
mdefine_line|#define L3TREESIZE (256*1024)
r_static
r_int
r_int
id|mem_mapped
op_assign
l_int|0
suffix:semicolon
r_static
r_int
r_int
id|virtaddr
op_assign
l_int|0
suffix:semicolon
r_static
id|pte_t
op_star
id|ktablep
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
op_star
id|kpointerp
suffix:semicolon
r_int
r_int
id|physaddr
suffix:semicolon
r_extern
id|pte_t
op_star
id|kpt
suffix:semicolon
r_int
id|pindex
suffix:semicolon
multiline_comment|/* index into pointer table */
id|pgd_t
op_star
id|page_dir
op_assign
id|pgd_offset_k
(paren
id|virtaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd_present
(paren
op_star
id|page_dir
)paren
)paren
(brace
multiline_comment|/* we need a new pointer table */
id|kpointerp
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_kpointer_table
(paren
)paren
suffix:semicolon
id|pgd_set
(paren
id|page_dir
comma
(paren
id|pmd_t
op_star
)paren
id|kpointerp
)paren
suffix:semicolon
id|memset
(paren
id|kpointerp
comma
l_int|0
comma
id|PTRS_PER_PMD
op_star
r_sizeof
(paren
id|pmd_t
)paren
)paren
suffix:semicolon
)brace
r_else
id|kpointerp
op_assign
(paren
r_int
r_int
op_star
)paren
id|pgd_page
(paren
op_star
id|page_dir
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * pindex is the offset into the pointer table for the&n;&t; * descriptors for the current virtual address being mapped.&n;&t; */
id|pindex
op_assign
(paren
id|virtaddr
op_rshift
l_int|18
)paren
op_amp
l_int|0x7f
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;mm=%ld, kernel_pg_dir=%p, kpointerp=%p, pindex=%d&bslash;n&quot;
comma
id|mem_mapped
comma
id|kernel_pg_dir
comma
id|kpointerp
comma
id|pindex
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * if this is running on an &squot;040, we already allocated a page&n;&t; * table for the first 4M.  The address is stored in kpt by&n;&t; * arch/head.S&n;&t; *&n;&t; */
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
op_logical_and
id|mem_mapped
op_eq
l_int|0
)paren
id|ktablep
op_assign
id|kpt
suffix:semicolon
r_for
c_loop
(paren
id|physaddr
op_assign
id|addr
suffix:semicolon
id|physaddr
OL
id|addr
op_plus
id|size
suffix:semicolon
id|mem_mapped
op_add_assign
id|L3TREESIZE
comma
id|virtaddr
op_add_assign
id|L3TREESIZE
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;pa=%#lx va=%#lx &quot;
comma
id|physaddr
comma
id|virtaddr
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|pindex
OG
l_int|127
op_logical_and
id|mem_mapped
op_ge
l_int|32
op_star
id|ONEMEG
)paren
(brace
multiline_comment|/* we need a new pointer table every 32M */
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;[new pointer]&quot;
)paren
suffix:semicolon
macro_line|#endif
id|kpointerp
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_kpointer_table
(paren
)paren
suffix:semicolon
id|pgd_set
c_func
(paren
id|pgd_offset_k
c_func
(paren
id|virtaddr
)paren
comma
(paren
id|pmd_t
op_star
)paren
id|kpointerp
)paren
suffix:semicolon
id|pindex
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|ktable
suffix:semicolon
multiline_comment|/* Don&squot;t map the first 4 MB again. The pagetables&n;&t;&t;&t; * for this range have already been initialized&n;&t;&t;&t; * in boot/head.S. Otherwise the pages used for&n;&t;&t;&t; * tables would be reinitialized to copyback mode.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|mem_mapped
OL
l_int|4
op_star
id|ONEMEG
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;Already initialized&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|physaddr
op_add_assign
id|L3TREESIZE
suffix:semicolon
id|pindex
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;[setup table]&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;&t;&t; * 68040, use page tables pointed to by the&n;&t;&t;&t; * kernel pointer table.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|pindex
op_amp
l_int|15
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Need new page table every 4M on the &squot;040 */
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;[new table]&quot;
)paren
suffix:semicolon
macro_line|#endif
id|ktablep
op_assign
id|kernel_page_table
(paren
id|memavailp
)paren
suffix:semicolon
)brace
id|ktable
op_assign
id|VTOP
c_func
(paren
id|ktablep
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * initialize section of the page table mapping&n;&t;&t;&t; * this 256K portion.&n;&t;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|64
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pte_val
c_func
(paren
id|ktablep
(braket
id|i
)braket
)paren
op_assign
id|physaddr
op_or
id|_PAGE_PRESENT
op_or
id|_PAGE_CACHE040
op_or
id|_PAGE_GLOBAL040
op_or
id|_PAGE_ACCESSED
suffix:semicolon
id|physaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|ktablep
op_add_assign
l_int|64
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * make the kernel pointer table point to the&n;&t;&t;&t; * kernel page table.  Each entries point to a&n;&t;&t;&t; * 64 entry section of the page table.&n;&t;&t;&t; */
id|kpointerp
(braket
id|pindex
op_increment
)braket
op_assign
id|ktable
op_or
id|_PAGE_TABLE
op_or
id|_PAGE_ACCESSED
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * 68030, use early termination page descriptors.&n;&t;&t;&t; * Each one points to 64 pages (256K).&n;&t;&t;&t; */
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;[early term] &quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|virtaddr
op_eq
l_int|0UL
)paren
(brace
multiline_comment|/* map the first 256K using a 64 entry&n;&t;&t;&t;&t; * 3rd level page table.&n;&t;&t;&t;&t; * UNMAP the first entry to trap&n;&t;&t;&t;&t; * zero page (NULL pointer) references&n;&t;&t;&t;&t; */
r_int
id|i
suffix:semicolon
r_int
r_int
op_star
id|tbl
suffix:semicolon
id|tbl
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_kpointer_table
c_func
(paren
)paren
suffix:semicolon
id|kpointerp
(braket
id|pindex
op_increment
)braket
op_assign
id|VTOP
c_func
(paren
id|tbl
)paren
op_or
id|_PAGE_TABLE
op_or
id|_PAGE_ACCESSED
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
l_int|64
suffix:semicolon
id|i
op_increment
comma
id|physaddr
op_add_assign
id|PAGE_SIZE
)paren
id|tbl
(braket
id|i
)braket
op_assign
id|physaddr
op_or
id|_PAGE_PRESENT
op_or
id|_PAGE_ACCESSED
suffix:semicolon
multiline_comment|/* unmap the zero page */
id|tbl
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* not the first 256K */
id|kpointerp
(braket
id|pindex
op_increment
)braket
op_assign
id|physaddr
op_or
id|_PAGE_PRESENT
op_or
id|_PAGE_ACCESSED
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;%lx=%lx &quot;
comma
id|VTOP
c_func
(paren
op_amp
id|kpointerp
(braket
id|pindex
op_minus
l_int|1
)braket
)paren
comma
id|kpointerp
(braket
id|pindex
op_minus
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#endif
id|physaddr
op_add_assign
l_int|64
op_star
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
id|mem_mapped
suffix:semicolon
)brace
r_extern
r_int
r_int
id|free_area_init
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
multiline_comment|/*&n; * paging_init() continues the virtual memory environment setup which&n; * was begun by the code in arch/head.S.&n; * The parameters are pointers to where to stick the starting and ending&n; * addresses  of available kernel virtual memory.&n; */
DECL|function|paging_init
r_int
r_int
id|paging_init
c_func
(paren
r_int
r_int
id|start_mem
comma
r_int
r_int
id|end_mem
)paren
(brace
r_int
id|chunk
suffix:semicolon
r_int
r_int
id|mem_avail
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* pointer to page table for kernel stacks */
r_extern
r_int
r_int
id|availmem
suffix:semicolon
macro_line|#ifdef DEBUG
(brace
r_extern
id|pte_t
op_star
id|kpt
suffix:semicolon
id|printk
(paren
l_string|&quot;start of paging_init (%p, %p, %lx, %lx, %lx)&bslash;n&quot;
comma
id|kernel_pg_dir
comma
id|kpt
comma
id|availmem
comma
id|start_mem
comma
id|end_mem
)paren
suffix:semicolon
)brace
macro_line|#endif
id|init_kpointer_table
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Fix the cache mode in the page descriptors for the 680[46]0.  */
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
r_int
id|i
suffix:semicolon
macro_line|#ifndef mm_cachebits
id|mm_cachebits
op_assign
id|_PAGE_CACHE040
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|pgprot_val
c_func
(paren
id|protection_map
(braket
id|i
)braket
)paren
op_or_assign
id|_PAGE_CACHE040
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Map the physical memory available into the kernel virtual&n;&t; * address space.  It may allocate some memory for page&n;&t; * tables and thus modify availmem.&n;&t; */
r_for
c_loop
(paren
id|chunk
op_assign
l_int|0
suffix:semicolon
id|chunk
OL
id|m68k_num_memory
suffix:semicolon
id|chunk
op_increment
)paren
(brace
id|mem_avail
op_assign
id|map_chunk
(paren
id|m68k_memory
(braket
id|chunk
)braket
dot
id|addr
comma
id|m68k_memory
(braket
id|chunk
)braket
dot
id|size
comma
op_amp
id|availmem
)paren
suffix:semicolon
)brace
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;memory available is %ldKB&bslash;n&quot;
comma
id|mem_avail
op_rshift
l_int|10
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * virtual address after end of kernel&n;&t; * &quot;availmem&quot; is setup by the code in head.S.&n;&t; */
id|start_mem
op_assign
id|availmem
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;start_mem is %#lx&bslash;nvirtual_end is %#lx&bslash;n&quot;
comma
id|start_mem
comma
id|end_mem
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * initialize the bad page table and bad page to point&n;&t; * to a couple of allocated pages&n;&t; */
id|empty_bad_page_table
op_assign
id|start_mem
suffix:semicolon
id|start_mem
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|empty_bad_page
op_assign
id|start_mem
suffix:semicolon
id|start_mem
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|empty_zero_page
op_assign
id|start_mem
suffix:semicolon
id|start_mem
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|empty_zero_page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* &n;&t; * allocate the &quot;swapper&quot; page directory and&n;&t; * record in task 0 (swapper) tss &n;&t; */
id|swapper_pg_dir
op_assign
(paren
id|pgd_t
op_star
)paren
id|get_kpointer_table
c_func
(paren
)paren
suffix:semicolon
id|init_mm.pgd
op_assign
id|swapper_pg_dir
suffix:semicolon
macro_line|#endif
id|memset
(paren
id|swapper_pg_dir
comma
l_int|0
comma
r_sizeof
(paren
id|pgd_t
)paren
op_star
id|PTRS_PER_PGD
)paren
suffix:semicolon
multiline_comment|/* setup CPU root pointer for swapper task */
id|task
(braket
l_int|0
)braket
op_member_access_from_pointer
id|tss.crp
(braket
l_int|0
)braket
op_assign
l_int|0x80000000
op_or
id|_PAGE_TABLE
suffix:semicolon
id|task
(braket
l_int|0
)braket
op_member_access_from_pointer
id|tss.crp
(braket
l_int|1
)braket
op_assign
id|VTOP
(paren
id|swapper_pg_dir
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;task 0 pagedir at %p virt, %#lx phys&bslash;n&quot;
comma
id|swapper_pg_dir
comma
id|task
(braket
l_int|0
)braket
op_member_access_from_pointer
id|tss.crp
(braket
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
id|asm
id|__volatile__
(paren
l_string|&quot;.chip 68040&bslash;n&bslash;t&quot;
l_string|&quot;movec %0,%%urp&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|task
(braket
l_int|0
)braket
op_member_access_from_pointer
id|tss.crp
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
r_else
id|asm
id|__volatile__
(paren
l_string|&quot;.chip 68030&bslash;n&bslash;t&quot;
l_string|&quot;pmove %0,%%crp&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;m&quot;
(paren
id|task
(braket
l_int|0
)braket
op_member_access_from_pointer
id|tss.crp
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;set crp&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Set up SFC/DFC registers (user data space)&n;&t; */
id|set_fs
(paren
id|USER_DS
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;before free_area_init&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|free_area_init
(paren
id|start_mem
comma
id|end_mem
)paren
suffix:semicolon
)brace
DECL|function|mem_init
r_void
id|mem_init
c_func
(paren
r_int
r_int
id|start_mem
comma
r_int
r_int
id|end_mem
)paren
(brace
r_int
id|codepages
op_assign
l_int|0
suffix:semicolon
r_int
id|datapages
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_extern
r_int
id|_etext
suffix:semicolon
id|end_mem
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|high_memory
op_assign
(paren
r_void
op_star
)paren
id|end_mem
suffix:semicolon
id|max_mapnr
op_assign
id|num_physpages
op_assign
id|MAP_NR
c_func
(paren
id|end_mem
)paren
suffix:semicolon
id|start_mem
op_assign
id|PAGE_ALIGN
c_func
(paren
id|start_mem
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start_mem
OL
id|end_mem
)paren
(brace
id|clear_bit
c_func
(paren
id|PG_reserved
comma
op_amp
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|start_mem
)paren
)braket
dot
id|flags
)paren
suffix:semicolon
id|start_mem
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ATARI
r_if
c_cond
(paren
id|MACH_IS_ATARI
)paren
(brace
multiline_comment|/* If the page with physical address 0 isn&squot;t the first kernel&n;&t;&t; * code page, it has to be reserved because the first 2 KB of&n;&t;&t; * ST-Ram can only be accessed from supervisor mode by&n;&t;&t; * hardware.&n;&t;&t; */
r_int
r_int
id|virt0
op_assign
id|PTOV
c_func
(paren
l_int|0
)paren
comma
id|adr
suffix:semicolon
r_extern
r_int
r_int
id|rsvd_stram_beg
comma
id|rsvd_stram_end
suffix:semicolon
r_if
c_cond
(paren
id|virt0
op_ne
l_int|0
)paren
(brace
id|set_bit
c_func
(paren
id|PG_reserved
comma
op_amp
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|virt0
)paren
)braket
dot
id|flags
)paren
suffix:semicolon
multiline_comment|/* Also, reserve all pages that have been marked by&n;&t;&t;&t; * stram_alloc() (e.g. for the screen memory). (This may&n;&t;&t;&t; * treat the first ST-Ram page a second time, but that&n;&t;&t;&t; * doesn&squot;t hurt...) */
id|rsvd_stram_end
op_add_assign
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
id|rsvd_stram_end
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|rsvd_stram_beg
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_for
c_loop
(paren
id|adr
op_assign
id|rsvd_stram_beg
suffix:semicolon
id|adr
OL
id|rsvd_stram_end
suffix:semicolon
id|adr
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|set_bit
c_func
(paren
id|PG_reserved
comma
op_amp
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|adr
)paren
)braket
dot
id|flags
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|end_mem
suffix:semicolon
id|tmp
op_add_assign
id|PAGE_SIZE
)paren
(brace
r_if
c_cond
(paren
id|VTOP
(paren
id|tmp
)paren
op_ge
id|mach_max_dma_address
)paren
id|clear_bit
c_func
(paren
id|PG_DMA
comma
op_amp
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|tmp
)paren
)braket
dot
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|tmp
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|tmp
OL
(paren
r_int
r_int
)paren
op_amp
id|_etext
)paren
id|codepages
op_increment
suffix:semicolon
r_else
id|datapages
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|atomic_set
c_func
(paren
op_amp
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|tmp
)paren
)braket
dot
id|count
comma
l_int|1
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
op_logical_neg
id|initrd_start
op_logical_or
(paren
id|tmp
OL
(paren
id|initrd_start
op_amp
id|PAGE_MASK
)paren
op_logical_or
id|tmp
op_ge
id|initrd_end
)paren
)paren
macro_line|#endif
id|free_page
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Memory: %luk/%luk available (%dk kernel code, %dk data)&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|nr_free_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|max_mapnr
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|codepages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|datapages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
)brace
DECL|function|free_initmem
r_void
id|free_initmem
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* To be written */
)brace
DECL|function|si_meminfo
r_void
id|si_meminfo
c_func
(paren
r_struct
id|sysinfo
op_star
id|val
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|i
op_assign
id|max_mapnr
suffix:semicolon
id|val-&gt;totalram
op_assign
l_int|0
suffix:semicolon
id|val-&gt;sharedram
op_assign
l_int|0
suffix:semicolon
id|val-&gt;freeram
op_assign
id|nr_free_pages
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|val-&gt;bufferram
op_assign
id|buffermem
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|mem_map
op_plus
id|i
)paren
)paren
r_continue
suffix:semicolon
id|val-&gt;totalram
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|mem_map
(braket
id|i
)braket
dot
id|count
)paren
)paren
r_continue
suffix:semicolon
id|val-&gt;sharedram
op_add_assign
id|atomic_read
c_func
(paren
op_amp
id|mem_map
(braket
id|i
)braket
dot
id|count
)paren
op_minus
l_int|1
suffix:semicolon
)brace
id|val-&gt;totalram
op_lshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|val-&gt;sharedram
op_lshift_assign
id|PAGE_SHIFT
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
