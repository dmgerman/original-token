multiline_comment|/*&n; *  linux/arch/arm/mm/init.c&n; *&n; *  Copyright (C) 1995-1999 Russell King&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/swapctl.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &quot;map.h&quot;
DECL|variable|totalram_pages
r_static
r_int
r_int
id|totalram_pages
suffix:semicolon
DECL|variable|swapper_pg_dir
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
r_extern
r_void
id|show_net_buffers
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * empty_bad_page is the page that is used for page faults when&n; * linux is out-of-memory. Older versions of linux just did a&n; * do_exit(), but using this instead means there is less risk&n; * for a process dying in kernel mode, possibly leaving a inode&n; * unused etc..&n; *&n; * empty_bad_pte_table is the accompanying page-table: it is&n; * initialized to point to BAD_PAGE entries.&n; *&n; * empty_zero_page is a special page that is used for&n; * zero-initialized data and COW.&n; */
DECL|variable|empty_zero_page
r_struct
id|page
op_star
id|empty_zero_page
suffix:semicolon
DECL|variable|empty_bad_page
r_struct
id|page
op_star
id|empty_bad_page
suffix:semicolon
DECL|variable|empty_bad_pte_table
id|pte_t
op_star
id|empty_bad_pte_table
suffix:semicolon
DECL|function|get_bad_pte_table
id|pte_t
op_star
id|get_bad_pte_table
c_func
(paren
r_void
)paren
(brace
id|pte_t
id|v
suffix:semicolon
r_int
id|i
suffix:semicolon
id|v
op_assign
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PTRS_PER_PTE
suffix:semicolon
id|i
op_increment
)paren
id|set_pte
c_func
(paren
id|empty_bad_pte_table
op_plus
id|i
comma
id|v
)paren
suffix:semicolon
r_return
id|empty_bad_pte_table
suffix:semicolon
)brace
DECL|function|__handle_bad_pmd
r_void
id|__handle_bad_pmd
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|pmd_ERROR
c_func
(paren
op_star
id|pmd
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_ERRORS
id|__backtrace
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
)brace
DECL|function|__handle_bad_pmd_kernel
r_void
id|__handle_bad_pmd_kernel
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|pmd_ERROR
c_func
(paren
op_star
id|pmd
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_ERRORS
id|__backtrace
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
)brace
macro_line|#ifndef CONFIG_NO_PGT_CACHE
DECL|variable|quicklists
r_struct
id|pgtable_cache_struct
id|quicklists
suffix:semicolon
DECL|function|do_check_pgt_cache
r_int
id|do_check_pgt_cache
c_func
(paren
r_int
id|low
comma
r_int
id|high
)paren
(brace
r_int
id|freed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pgtable_cache_size
OG
id|high
)paren
(brace
r_do
(brace
r_if
c_cond
(paren
id|pgd_quicklist
)paren
(brace
id|free_pgd_slow
c_func
(paren
id|get_pgd_fast
c_func
(paren
)paren
)paren
suffix:semicolon
id|freed
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pmd_quicklist
)paren
(brace
id|free_pmd_slow
c_func
(paren
id|get_pmd_fast
c_func
(paren
)paren
)paren
suffix:semicolon
id|freed
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pte_quicklist
)paren
(brace
id|free_pte_slow
c_func
(paren
id|get_pte_fast
c_func
(paren
)paren
)paren
suffix:semicolon
id|freed
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|pgtable_cache_size
OG
id|low
)paren
(brace
suffix:semicolon
)brace
)brace
r_return
id|freed
suffix:semicolon
)brace
macro_line|#else
DECL|function|do_check_pgt_cache
r_int
id|do_check_pgt_cache
c_func
(paren
r_int
id|low
comma
r_int
id|high
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|show_mem
r_void
id|show_mem
c_func
(paren
r_void
)paren
(brace
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
suffix:semicolon
r_int
id|shared
op_assign
l_int|0
comma
id|cached
op_assign
l_int|0
suffix:semicolon
r_struct
id|page
op_star
id|page
comma
op_star
id|end
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Mem-info:&bslash;n&quot;
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
id|page
op_assign
id|mem_map
suffix:semicolon
id|end
op_assign
id|mem_map
op_plus
id|max_mapnr
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|PageSkip
c_func
(paren
id|page
)paren
)paren
(brace
id|page
op_assign
id|page-&gt;next_hash
suffix:semicolon
r_if
c_cond
(paren
id|page
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
)brace
id|total
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|page
)paren
)paren
id|reserved
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|page
)paren
)paren
id|cached
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|page_count
c_func
(paren
id|page
)paren
)paren
id|free
op_increment
suffix:semicolon
r_else
id|shared
op_add_assign
id|atomic_read
c_func
(paren
op_amp
id|page-&gt;count
)paren
op_minus
l_int|1
suffix:semicolon
id|page
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|page
OL
id|end
)paren
suffix:semicolon
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
l_string|&quot;%d pages shared&bslash;n&quot;
comma
id|shared
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages swap cached&bslash;n&quot;
comma
id|cached
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_NO_PGT_CACHE
id|printk
c_func
(paren
l_string|&quot;%ld page tables cached&bslash;n&quot;
comma
id|pgtable_cache_size
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/*&n; * paging_init() sets up the page tables...&n; */
DECL|function|paging_init
r_void
id|__init
id|paging_init
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|zero_page
comma
op_star
id|bad_page
comma
op_star
id|bad_table
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_32
DECL|macro|TABLE_OFFSET
mdefine_line|#define TABLE_OFFSET&t;(PTRS_PER_PTE)
macro_line|#else
mdefine_line|#define TABLE_OFFSET&t;0
macro_line|#endif
DECL|macro|TABLE_SIZE
mdefine_line|#define TABLE_SIZE&t;((TABLE_OFFSET + PTRS_PER_PTE) * sizeof(void *))
multiline_comment|/*&n;&t; * allocate what we need for the bad pages&n;&t; */
id|zero_page
op_assign
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|bad_page
op_assign
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|bad_table
op_assign
id|alloc_bootmem_low_pages
c_func
(paren
id|TABLE_SIZE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * initialise the page tables&n;&t; */
id|pagetable_init
c_func
(paren
)paren
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
id|free_area_init
c_func
(paren
id|max_low_pfn
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * finish off the bad pages once&n;&t; * the mem_map is initialised&n;&t; */
id|memzero
c_func
(paren
id|zero_page
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|memzero
c_func
(paren
id|bad_page
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|empty_zero_page
op_assign
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|zero_page
)paren
suffix:semicolon
id|empty_bad_page
op_assign
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|bad_page
)paren
suffix:semicolon
id|empty_bad_pte_table
op_assign
(paren
(paren
id|pte_t
op_star
)paren
id|bad_table
)paren
op_plus
id|TABLE_OFFSET
suffix:semicolon
)brace
DECL|function|free_unused_mem_map
r_static
r_inline
r_void
id|free_unused_mem_map
c_func
(paren
r_void
)paren
(brace
r_struct
id|page
op_star
id|page
comma
op_star
id|end
suffix:semicolon
id|end
op_assign
id|mem_map
op_plus
id|max_mapnr
suffix:semicolon
r_for
c_loop
(paren
id|page
op_assign
id|mem_map
suffix:semicolon
id|page
OL
id|end
suffix:semicolon
id|page
op_increment
)paren
(brace
r_int
r_int
id|low
comma
id|high
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageSkip
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
id|low
op_assign
id|PAGE_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|page
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;next_hash
OL
id|page
)paren
id|high
op_assign
(paren
(paren
r_int
r_int
)paren
id|end
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
r_else
id|high
op_assign
(paren
(paren
r_int
r_int
)paren
id|page-&gt;next_hash
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
r_while
c_loop
(paren
id|low
OL
id|high
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|low
)paren
)paren
suffix:semicolon
id|low
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * mem_init() marks the free areas in the mem_map and tells us how much&n; * memory is free.  This is done after various parts of the system have&n; * claimed their memory after the kernel image.&n; */
DECL|function|mem_init
r_void
id|__init
id|mem_init
c_func
(paren
r_void
)paren
(brace
r_int
id|codepages
op_assign
l_int|0
suffix:semicolon
r_int
id|reservedpages
op_assign
l_int|0
suffix:semicolon
r_int
id|datapages
op_assign
l_int|0
suffix:semicolon
r_int
id|initpages
op_assign
l_int|0
comma
id|i
comma
id|min_nr
suffix:semicolon
id|max_mapnr
op_assign
id|max_low_pfn
suffix:semicolon
id|high_memory
op_assign
(paren
r_void
op_star
)paren
id|__va
c_func
(paren
id|max_low_pfn
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_32
multiline_comment|/*&n;&t; * We may have non-contiguous memory.  Setup the PageSkip stuff,&n;&t; * and mark the areas of mem_map which can be freed&n;&t; */
r_if
c_cond
(paren
id|meminfo.nr_banks
op_ne
l_int|1
)paren
id|create_memmap_holes
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* this will put all unused low memory onto the freelists */
id|totalram_pages
op_add_assign
id|free_all_bootmem
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Since our memory may not be contiguous, calculate the&n;&t; * real number of pages we have in this system&n;&t; */
id|num_physpages
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
id|num_physpages
op_add_assign
id|meminfo.bank
(braket
id|i
)braket
dot
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|printk
(paren
l_string|&quot;Memory: %luk/%luM available (%dk code, %dk reserved, %dk data, %dk init)&bslash;n&quot;
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
id|num_physpages
op_rshift
(paren
l_int|20
op_minus
id|PAGE_SHIFT
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
id|reservedpages
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
comma
id|initpages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Correct freepages watermarks&n;&t; */
id|i
op_assign
id|nr_free_pages
op_rshift
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|PAGE_SIZE
OL
l_int|32768
)paren
id|min_nr
op_assign
l_int|10
suffix:semicolon
r_else
id|min_nr
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|min_nr
)paren
id|i
op_assign
id|min_nr
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|256
)paren
id|i
op_assign
l_int|256
suffix:semicolon
id|freepages.min
op_assign
id|i
suffix:semicolon
id|freepages.low
op_assign
id|i
op_star
l_int|2
suffix:semicolon
id|freepages.high
op_assign
id|i
op_star
l_int|3
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_26
r_if
c_cond
(paren
id|max_mapnr
op_le
l_int|128
)paren
(brace
r_extern
r_int
id|sysctl_overcommit_memory
suffix:semicolon
multiline_comment|/* On a machine this small we won&squot;t get anywhere without&n;&t;&t;   overcommit, so turn it on by default.  */
id|sysctl_overcommit_memory
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|free_area
r_static
r_inline
r_void
id|free_area
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|end
comma
r_char
op_star
id|s
)paren
(brace
r_int
r_int
id|size
op_assign
(paren
id|end
op_minus
id|addr
)paren
op_rshift
l_int|10
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
comma
id|page
op_increment
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|page
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|addr
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
)paren
id|printk
c_func
(paren
l_string|&quot; %dk %s&quot;
comma
id|size
comma
id|s
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
r_extern
r_char
id|__init_begin
comma
id|__init_end
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Freeing unused kernel memory:&quot;
)paren
suffix:semicolon
id|free_area
c_func
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|__init_begin
)paren
comma
(paren
r_int
r_int
)paren
(paren
op_amp
id|__init_end
)paren
comma
l_string|&quot;init&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FOOTBRIDGE
(brace
r_extern
r_int
id|__netwinder_begin
comma
id|__netwinder_end
comma
id|__ebsa285_begin
comma
id|__ebsa285_end
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|machine_is_netwinder
c_func
(paren
)paren
)paren
id|free_area
c_func
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|__netwinder_begin
)paren
comma
(paren
r_int
r_int
)paren
(paren
op_amp
id|__netwinder_end
)paren
comma
l_string|&quot;netwinder&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|machine_is_ebsa285
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|machine_is_cats
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|machine_is_co285
c_func
(paren
)paren
)paren
id|free_area
c_func
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ebsa285_begin
)paren
comma
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ebsa285_end
)paren
comma
l_string|&quot;ebsa285/cats&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
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
id|val-&gt;totalram
op_assign
id|totalram_pages
suffix:semicolon
id|val-&gt;sharedram
op_assign
l_int|0
suffix:semicolon
id|val-&gt;freeram
op_assign
id|nr_free_pages
suffix:semicolon
id|val-&gt;bufferram
op_assign
id|atomic_read
c_func
(paren
op_amp
id|buffermem_pages
)paren
suffix:semicolon
id|val-&gt;totalhigh
op_assign
l_int|0
suffix:semicolon
id|val-&gt;freehigh
op_assign
l_int|0
suffix:semicolon
id|val-&gt;mem_unit
op_assign
id|PAGE_SIZE
suffix:semicolon
)brace
eof
