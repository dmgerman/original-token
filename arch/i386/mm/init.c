multiline_comment|/*&n; *  linux/arch/i386/mm/init.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *&n; *  Support of BIGMEM added by Gerhard Wichert, Siemens AG, July 1999&n; */
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
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/e820.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
DECL|variable|highstart_pfn
DECL|variable|highend_pfn
r_int
r_int
id|highstart_pfn
comma
id|highend_pfn
suffix:semicolon
DECL|variable|totalram_pages
r_static
r_int
r_int
id|totalram_pages
op_assign
l_int|0
suffix:semicolon
DECL|variable|totalhigh_pages
r_static
r_int
r_int
id|totalhigh_pages
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * BAD_PAGE is the page that is used for page faults when linux&n; * is out-of-memory. Older versions of linux just did a&n; * do_exit(), but using this instead means there is less risk&n; * for a process dying in kernel mode, possibly leaving an inode&n; * unused etc..&n; *&n; * BAD_PAGETABLE is the accompanying page-table: it is initialized&n; * to point to BAD_PAGE entries.&n; *&n; * ZERO_PAGE is a special page that is used for zero-initialized&n; * data and COW.&n; */
multiline_comment|/*&n; * These are allocated in head.S so that we get proper page alignment.&n; * If you change the size of these then change head.S as well.&n; */
r_extern
r_char
id|empty_bad_page
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
macro_line|#if CONFIG_X86_PAE
r_extern
id|pmd_t
id|empty_bad_pmd_table
(braket
id|PTRS_PER_PMD
)braket
suffix:semicolon
macro_line|#endif
r_extern
id|pte_t
id|empty_bad_pte_table
(braket
id|PTRS_PER_PTE
)braket
suffix:semicolon
multiline_comment|/*&n; * We init them before every return and make them writable-shared.&n; * This guarantees we get out of the kernel in some more or less sane&n; * way.&n; */
macro_line|#if CONFIG_X86_PAE
DECL|function|get_bad_pmd_table
r_static
id|pmd_t
op_star
id|get_bad_pmd_table
c_func
(paren
r_void
)paren
(brace
id|pmd_t
id|v
suffix:semicolon
r_int
id|i
suffix:semicolon
id|set_pmd
c_func
(paren
op_amp
id|v
comma
id|__pmd
c_func
(paren
id|_PAGE_TABLE
op_plus
id|__pa
c_func
(paren
id|empty_bad_pte_table
)paren
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
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|pmd_t
)paren
suffix:semicolon
id|i
op_increment
)paren
id|empty_bad_pmd_table
(braket
id|i
)braket
op_assign
id|v
suffix:semicolon
r_return
id|empty_bad_pmd_table
suffix:semicolon
)brace
macro_line|#endif
DECL|function|get_bad_pte_table
r_static
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
id|mk_pte_phys
c_func
(paren
id|__pa
c_func
(paren
id|empty_bad_page
)paren
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
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|pte_t
)paren
suffix:semicolon
id|i
op_increment
)paren
id|empty_bad_pte_table
(braket
id|i
)braket
op_assign
id|v
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
id|set_pmd
c_func
(paren
id|pmd
comma
id|__pmd
c_func
(paren
id|_PAGE_TABLE
op_plus
id|__pa
c_func
(paren
id|get_bad_pte_table
c_func
(paren
)paren
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
id|set_pmd
c_func
(paren
id|pmd
comma
id|__pmd
c_func
(paren
id|_KERNPG_TABLE
op_plus
id|__pa
c_func
(paren
id|get_bad_pte_table
c_func
(paren
)paren
)paren
)paren
)paren
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
id|__get_free_page
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
id|clear_page
c_func
(paren
id|pte
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
id|__pmd
c_func
(paren
id|_KERNPG_TABLE
op_plus
id|__pa
c_func
(paren
id|pte
)paren
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
id|__pmd
c_func
(paren
id|_KERNPG_TABLE
op_plus
id|__pa
c_func
(paren
id|get_bad_pte_table
c_func
(paren
)paren
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
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
r_int
r_int
id|pte
suffix:semicolon
id|pte
op_assign
(paren
r_int
r_int
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
id|clear_page
c_func
(paren
(paren
r_void
op_star
)paren
id|pte
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
id|__pmd
c_func
(paren
id|_PAGE_TABLE
op_plus
id|__pa
c_func
(paren
id|pte
)paren
)paren
)paren
suffix:semicolon
r_return
(paren
id|pte_t
op_star
)paren
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
id|__pmd
c_func
(paren
id|_PAGE_TABLE
op_plus
id|__pa
c_func
(paren
id|get_bad_pte_table
c_func
(paren
)paren
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|free_page
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
comma
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
comma
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
comma
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
multiline_comment|/*&n; * NOTE: pagetable_init alloc all the fixmap pagetables contiguous on the&n; * physical space so we can cache the place of the first one and move&n; * around without checking the pgd every time.&n; */
macro_line|#if CONFIG_HIGHMEM
DECL|variable|kmap_pte
id|pte_t
op_star
id|kmap_pte
suffix:semicolon
DECL|variable|kmap_prot
id|pgprot_t
id|kmap_prot
suffix:semicolon
DECL|macro|kmap_get_fixmap_pte
mdefine_line|#define kmap_get_fixmap_pte(vaddr)&t;&t;&t;&t;&t;&bslash;&n;&t;pte_offset(pmd_offset(pgd_offset_k(vaddr), (vaddr)), (vaddr))
DECL|function|kmap_init
r_void
id|__init
id|kmap_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|kmap_vstart
suffix:semicolon
multiline_comment|/* cache the first kmap pte */
id|kmap_vstart
op_assign
id|__fix_to_virt
c_func
(paren
id|FIX_KMAP_BEGIN
)paren
suffix:semicolon
id|kmap_pte
op_assign
id|kmap_get_fixmap_pte
c_func
(paren
id|kmap_vstart
)paren
suffix:semicolon
id|kmap_prot
op_assign
id|PAGE_KERNEL
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_HIGHMEM */
DECL|function|show_mem
r_void
id|show_mem
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
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
r_int
id|highmem
op_assign
l_int|0
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
id|PageHighMem
c_func
(paren
id|mem_map
op_plus
id|i
)paren
)paren
id|highmem
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
id|PageSwapCache
c_func
(paren
id|mem_map
op_plus
id|i
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
id|mem_map
op_plus
id|i
)paren
)paren
id|free
op_increment
suffix:semicolon
r_else
id|shared
op_add_assign
id|page_count
c_func
(paren
id|mem_map
op_plus
id|i
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
l_string|&quot;%d pages of HIGHMEM&bslash;n&quot;
comma
id|highmem
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
id|printk
c_func
(paren
l_string|&quot;%ld pages in page table cache&bslash;n&quot;
comma
id|pgtable_cache_size
)paren
suffix:semicolon
id|show_buffers
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* References to section boundaries */
r_extern
r_char
id|_text
comma
id|_etext
comma
id|_edata
comma
id|__bss_start
comma
id|_end
suffix:semicolon
r_extern
r_char
id|__init_begin
comma
id|__init_end
suffix:semicolon
DECL|function|set_pte_phys
r_static
r_inline
r_void
id|set_pte_phys
(paren
r_int
r_int
id|vaddr
comma
r_int
r_int
id|phys
comma
id|pgprot_t
id|flags
)paren
(brace
id|pgprot_t
id|prot
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
id|pgd
op_assign
id|swapper_pg_dir
op_plus
id|__pgd_offset
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|vaddr
)paren
suffix:semicolon
id|pte
op_assign
id|pte_offset
c_func
(paren
id|pmd
comma
id|vaddr
)paren
suffix:semicolon
id|pgprot_val
c_func
(paren
id|prot
)paren
op_assign
id|pgprot_val
c_func
(paren
id|PAGE_KERNEL
)paren
op_or
id|pgprot_val
c_func
(paren
id|flags
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|pte
comma
id|mk_pte_phys
c_func
(paren
id|phys
comma
id|prot
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * It&squot;s enough to flush this one mapping.&n;&t; * (PGE mappings get flushed as well)&n;&t; */
id|__flush_tlb_one
c_func
(paren
id|vaddr
)paren
suffix:semicolon
)brace
DECL|function|__set_fixmap
r_void
id|__set_fixmap
(paren
r_enum
id|fixed_addresses
id|idx
comma
r_int
r_int
id|phys
comma
id|pgprot_t
id|flags
)paren
(brace
r_int
r_int
id|address
op_assign
id|__fix_to_virt
c_func
(paren
id|idx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|__end_of_fixed_addresses
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Invalid __set_fixmap&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|set_pte_phys
c_func
(paren
id|address
comma
id|phys
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|fixrange_init
r_static
r_void
id|__init
id|fixrange_init
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
id|pgd_t
op_star
id|pgd_base
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|i
op_assign
id|__pgd_offset
c_func
(paren
id|start
)paren
suffix:semicolon
id|j
op_assign
id|__pmd_offset
c_func
(paren
id|start
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_base
op_plus
id|i
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|i
OL
id|PTRS_PER_PGD
)paren
op_logical_and
(paren
id|start
op_ne
id|end
)paren
suffix:semicolon
id|pgd
op_increment
comma
id|i
op_increment
)paren
(brace
macro_line|#if CONFIG_X86_PAE
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
id|pmd
op_assign
(paren
id|pmd_t
op_star
)paren
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|set_pgd
c_func
(paren
id|pgd
comma
id|__pgd
c_func
(paren
id|__pa
c_func
(paren
id|pmd
)paren
op_plus
l_int|0x1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd
op_ne
id|pmd_offset
c_func
(paren
id|pgd
comma
id|start
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|start
)paren
suffix:semicolon
macro_line|#else
id|pmd
op_assign
(paren
id|pmd_t
op_star
)paren
id|pgd
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
suffix:semicolon
(paren
id|j
OL
id|PTRS_PER_PMD
)paren
op_logical_and
id|start
suffix:semicolon
id|pmd
op_increment
comma
id|j
op_increment
)paren
(brace
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
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
id|__pmd
c_func
(paren
id|_KERNPG_TABLE
op_plus
id|__pa
c_func
(paren
id|pte
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
op_ne
id|pte_offset
c_func
(paren
id|pmd
comma
l_int|0
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|start
op_add_assign
id|PMD_SIZE
suffix:semicolon
)brace
id|j
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|pagetable_init
r_static
r_void
id|__init
id|pagetable_init
c_func
(paren
r_void
)paren
(brace
id|pgd_t
op_star
id|pgd
comma
op_star
id|pgd_base
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|k
suffix:semicolon
r_int
r_int
id|vaddr
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|max_low_pfn
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
id|pgd_base
op_assign
id|swapper_pg_dir
suffix:semicolon
id|vaddr
op_assign
id|PAGE_OFFSET
suffix:semicolon
id|i
op_assign
id|__pgd_offset
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_base
op_plus
id|i
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|i
OL
id|PTRS_PER_PGD
)paren
op_logical_and
(paren
id|vaddr
op_le
id|end
)paren
suffix:semicolon
id|pgd
op_increment
comma
id|i
op_increment
)paren
(brace
id|vaddr
op_assign
id|i
op_star
id|PGDIR_SIZE
suffix:semicolon
macro_line|#if CONFIG_X86_PAE
id|pmd
op_assign
(paren
id|pmd_t
op_star
)paren
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|set_pgd
c_func
(paren
id|pgd
comma
id|__pgd
c_func
(paren
id|__pa
c_func
(paren
id|pmd
)paren
op_plus
l_int|0x1
)paren
)paren
suffix:semicolon
macro_line|#else
id|pmd
op_assign
(paren
id|pmd_t
op_star
)paren
id|pgd
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|pmd
op_ne
id|pmd_offset
c_func
(paren
id|pgd
comma
l_int|0
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
(paren
id|j
OL
id|PTRS_PER_PMD
)paren
op_logical_and
(paren
id|vaddr
op_le
id|end
)paren
suffix:semicolon
id|pmd
op_increment
comma
id|j
op_increment
)paren
(brace
id|vaddr
op_assign
id|i
op_star
id|PGDIR_SIZE
op_plus
id|j
op_star
id|PMD_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_pse
)paren
(brace
r_int
r_int
id|__pe
suffix:semicolon
id|set_in_cr4
c_func
(paren
id|X86_CR4_PSE
)paren
suffix:semicolon
id|boot_cpu_data.wp_works_ok
op_assign
l_int|1
suffix:semicolon
id|__pe
op_assign
id|_KERNPG_TABLE
op_plus
id|_PAGE_PSE
op_plus
id|__pa
c_func
(paren
id|vaddr
)paren
suffix:semicolon
multiline_comment|/* Make it &quot;global&quot; too if supported */
r_if
c_cond
(paren
id|cpu_has_pge
)paren
(brace
id|set_in_cr4
c_func
(paren
id|X86_CR4_PGE
)paren
suffix:semicolon
id|__pe
op_add_assign
id|_PAGE_GLOBAL
suffix:semicolon
)brace
id|set_pmd
c_func
(paren
id|pmd
comma
id|__pmd
c_func
(paren
id|__pe
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
id|__pmd
c_func
(paren
id|_KERNPG_TABLE
op_plus
id|__pa
c_func
(paren
id|pte
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
op_ne
id|pte_offset
c_func
(paren
id|pmd
comma
l_int|0
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
(paren
id|k
OL
id|PTRS_PER_PTE
)paren
op_logical_and
(paren
id|vaddr
op_le
id|end
)paren
suffix:semicolon
id|pte
op_increment
comma
id|k
op_increment
)paren
(brace
id|vaddr
op_assign
id|i
op_star
id|PGDIR_SIZE
op_plus
id|j
op_star
id|PMD_SIZE
op_plus
id|k
op_star
id|PAGE_SIZE
suffix:semicolon
op_star
id|pte
op_assign
id|mk_pte_phys
c_func
(paren
id|__pa
c_func
(paren
id|vaddr
)paren
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;&t; * Fixed mappings, only the page table structure has to be&n;&t; * created - mappings will be set by set_fixmap():&n;&t; */
id|vaddr
op_assign
id|__fix_to_virt
c_func
(paren
id|__end_of_fixed_addresses
op_minus
l_int|1
)paren
op_amp
id|PMD_MASK
suffix:semicolon
id|fixrange_init
c_func
(paren
id|vaddr
comma
l_int|0
comma
id|pgd_base
)paren
suffix:semicolon
macro_line|#if CONFIG_HIGHMEM
multiline_comment|/*&n;&t; * Permanent kmaps:&n;&t; */
id|vaddr
op_assign
id|PKMAP_BASE
suffix:semicolon
id|fixrange_init
c_func
(paren
id|vaddr
comma
id|vaddr
op_plus
id|PAGE_SIZE
op_star
id|LAST_PKMAP
comma
id|pgd_base
)paren
suffix:semicolon
id|pgd
op_assign
id|swapper_pg_dir
op_plus
id|__pgd_offset
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|vaddr
)paren
suffix:semicolon
id|pte
op_assign
id|pte_offset
c_func
(paren
id|pmd
comma
id|vaddr
)paren
suffix:semicolon
id|pkmap_page_table
op_assign
id|pte
suffix:semicolon
macro_line|#endif
macro_line|#if CONFIG_X86_PAE
multiline_comment|/*&n;&t; * Add low memory identity-mappings - SMP needs it when&n;&t; * starting up on an AP from real-mode. In the non-PAE&n;&t; * case we already have these mappings through head.S.&n;&t; * All user-space mappings are explicitly cleared after&n;&t; * SMP startup.&n;&t; */
id|pgd_base
(braket
l_int|0
)braket
op_assign
id|pgd_base
(braket
id|USER_PTRS_PER_PGD
)braket
suffix:semicolon
macro_line|#endif
)brace
DECL|function|zap_low_mappings
r_void
id|__init
id|zap_low_mappings
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Zap initial low-memory mappings.&n;&t; *&n;&t; * Note that &quot;pgd_clear()&quot; doesn&squot;t do it for&n;&t; * us in this case, because pgd_clear() is a&n;&t; * no-op in the 2-level case (pmd_clear() is&n;&t; * the thing that clears the page-tables in&n;&t; * that case).&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|USER_PTRS_PER_PGD
suffix:semicolon
id|i
op_increment
)paren
macro_line|#if CONFIG_X86_PAE
id|pgd_clear
c_func
(paren
id|swapper_pg_dir
op_plus
id|i
)paren
suffix:semicolon
macro_line|#else
id|set_pgd
c_func
(paren
id|swapper_pg_dir
op_plus
id|i
comma
id|__pgd
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#endif
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * paging_init() sets up the page tables - note that the first 4MB are&n; * already mapped by head.S.&n; *&n; * This routines also unmaps the page at virtual kernel address 0, so&n; * that we can trap those pesky NULL-reference errors in the kernel.&n; */
DECL|function|paging_init
r_void
id|__init
id|paging_init
c_func
(paren
r_void
)paren
(brace
id|pagetable_init
c_func
(paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%ecx,%%cr3&bslash;n&quot;
op_scope_resolution
l_string|&quot;c&quot;
(paren
id|__pa
c_func
(paren
id|swapper_pg_dir
)paren
)paren
)paren
suffix:semicolon
macro_line|#if CONFIG_X86_PAE
multiline_comment|/*&n;&t; * We will bail out later - printk doesnt work right now so&n;&t; * the user would just see a hanging kernel.&n;&t; */
r_if
c_cond
(paren
id|cpu_has_pae
)paren
id|set_in_cr4
c_func
(paren
id|X86_CR4_PAE
)paren
suffix:semicolon
macro_line|#endif
id|__flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
id|init_apic_mappings
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HIGHMEM
id|kmap_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
(brace
r_int
r_int
id|zones_size
(braket
id|MAX_NR_ZONES
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
r_int
id|max_dma
comma
id|high
comma
id|low
suffix:semicolon
id|max_dma
op_assign
id|virt_to_phys
c_func
(paren
(paren
r_char
op_star
)paren
id|MAX_DMA_ADDRESS
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|low
op_assign
id|max_low_pfn
suffix:semicolon
id|high
op_assign
id|highend_pfn
suffix:semicolon
r_if
c_cond
(paren
id|low
OL
id|max_dma
)paren
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|low
suffix:semicolon
r_else
(brace
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|max_dma
suffix:semicolon
id|zones_size
(braket
id|ZONE_NORMAL
)braket
op_assign
id|low
op_minus
id|max_dma
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
id|zones_size
(braket
id|ZONE_HIGHMEM
)braket
op_assign
id|high
op_minus
id|low
suffix:semicolon
macro_line|#endif
)brace
id|free_area_init
c_func
(paren
id|zones_size
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Test if the WP bit works in supervisor mode. It isn&squot;t supported on 386&squot;s&n; * and also on some strange 486&squot;s (NexGen etc.). All 586+&squot;s are OK. The jumps&n; * before and after the test are here to work-around some nasty CPU bugs.&n; */
DECL|function|test_wp_bit
r_void
id|__init
id|test_wp_bit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n; * Ok, all PAE-capable CPUs are definitely handling the WP bit right.&n; */
r_const
r_int
r_int
id|vaddr
op_assign
id|PAGE_OFFSET
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
comma
id|old_pte
suffix:semicolon
r_char
id|tmp_reg
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Checking if this processor honours the WP bit even in supervisor mode... &quot;
)paren
suffix:semicolon
id|pgd
op_assign
id|swapper_pg_dir
op_plus
id|__pgd_offset
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|vaddr
)paren
suffix:semicolon
id|pte
op_assign
id|pte_offset
c_func
(paren
id|pmd
comma
id|vaddr
)paren
suffix:semicolon
id|old_pte
op_assign
op_star
id|pte
suffix:semicolon
op_star
id|pte
op_assign
id|mk_pte_phys
c_func
(paren
l_int|0
comma
id|PAGE_READONLY
)paren
suffix:semicolon
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;jmp 1f; 1:&bslash;n&quot;
l_string|&quot;movb %0,%1&bslash;n&quot;
l_string|&quot;movb %1,%0&bslash;n&quot;
l_string|&quot;jmp 1f; 1:&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|vaddr
)paren
comma
l_string|&quot;=q&quot;
(paren
id|tmp_reg
)paren
suffix:colon
multiline_comment|/* no inputs */
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
op_star
id|pte
op_assign
id|old_pte
suffix:semicolon
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|boot_cpu_data.wp_works_ok
OL
l_int|0
)paren
(brace
id|boot_cpu_data.wp_works_ok
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;No.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_WP_WORKS_OK
id|panic
c_func
(paren
l_string|&quot;This kernel doesn&squot;t support CPU&squot;s with broken WP. Recompile it for a 386!&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;.&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|page_is_ram
r_static
r_inline
r_int
id|page_is_ram
(paren
r_int
r_int
id|pagenr
)paren
(brace
r_int
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
id|e820.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|addr
comma
id|end
suffix:semicolon
r_if
c_cond
(paren
id|e820.map
(braket
id|i
)braket
dot
id|type
op_ne
id|E820_RAM
)paren
multiline_comment|/* not usable memory */
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;!!!FIXME!!! Some BIOSen report areas as RAM that&n;&t;&t; *&t;are not. Notably the 640-&gt;1Mb area. We need a sanity&n;&t;&t; *&t;check here.&n;&t;&t; */
id|addr
op_assign
(paren
id|e820.map
(braket
id|i
)braket
dot
id|addr
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|end
op_assign
(paren
id|e820.map
(braket
id|i
)braket
dot
id|addr
op_plus
id|e820.map
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
(paren
id|pagenr
op_ge
id|addr
)paren
op_logical_and
(paren
id|pagenr
OL
id|end
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
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
id|codesize
comma
id|reservedpages
comma
id|datasize
comma
id|initsize
suffix:semicolon
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem_map
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
id|highmem_start_page
op_assign
id|mem_map
op_plus
id|highstart_pfn
suffix:semicolon
multiline_comment|/* cache the highmem_mapnr */
id|highmem_mapnr
op_assign
id|highstart_pfn
suffix:semicolon
id|max_mapnr
op_assign
id|num_physpages
op_assign
id|highend_pfn
suffix:semicolon
macro_line|#else
id|max_mapnr
op_assign
id|num_physpages
op_assign
id|max_low_pfn
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* clear the zero-page */
id|memset
c_func
(paren
id|empty_zero_page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* this will put all low memory onto the freelists */
id|totalram_pages
op_add_assign
id|free_all_bootmem
c_func
(paren
)paren
suffix:semicolon
id|reservedpages
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|max_low_pfn
suffix:semicolon
id|tmp
op_increment
)paren
multiline_comment|/*&n;&t;&t; * Only count reserved RAM pages&n;&t;&t; */
r_if
c_cond
(paren
id|page_is_ram
c_func
(paren
id|tmp
)paren
op_logical_and
id|PageReserved
c_func
(paren
id|mem_map
op_plus
id|tmp
)paren
)paren
id|reservedpages
op_increment
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
r_for
c_loop
(paren
id|tmp
op_assign
id|highstart_pfn
suffix:semicolon
id|tmp
OL
id|highend_pfn
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|mem_map
op_plus
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page_is_ram
c_func
(paren
id|tmp
)paren
)paren
(brace
id|SetPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|ClearPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_highmem
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|page-&gt;count
comma
l_int|1
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|totalhigh_pages
op_increment
suffix:semicolon
)brace
id|totalram_pages
op_add_assign
id|totalhigh_pages
suffix:semicolon
macro_line|#endif
id|codesize
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_etext
op_minus
(paren
r_int
r_int
)paren
op_amp
id|_text
suffix:semicolon
id|datasize
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_edata
op_minus
(paren
r_int
r_int
)paren
op_amp
id|_etext
suffix:semicolon
id|initsize
op_assign
(paren
r_int
r_int
)paren
op_amp
id|__init_end
op_minus
(paren
r_int
r_int
)paren
op_amp
id|__init_begin
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Memory: %luk/%luk available (%dk kernel code, %dk reserved, %dk data, %dk init, %ldk highmem)&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|nr_free_pages
c_func
(paren
)paren
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
id|codesize
op_rshift
l_int|10
comma
id|reservedpages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|datasize
op_rshift
l_int|10
comma
id|initsize
op_rshift
l_int|10
comma
(paren
r_int
r_int
)paren
(paren
id|totalhigh_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
)paren
suffix:semicolon
macro_line|#if CONFIG_X86_PAE
r_if
c_cond
(paren
op_logical_neg
id|cpu_has_pae
)paren
id|panic
c_func
(paren
l_string|&quot;cannot execute a PAE-enabled kernel on a PAE-less CPU!&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|boot_cpu_data.wp_works_ok
OL
l_int|0
)paren
id|test_wp_bit
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Subtle. SMP is doing it&squot;s boot stuff late (because it has to&n;&t; * fork idle threads) - but it also needs low mappings for the&n;&t; * protected-mode entry to work. We zap these entries only after&n;&t; * the WP-bit has been tested.&n;&t; */
macro_line|#ifndef CONFIG_SMP
id|zap_low_mappings
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|free_initmem
r_void
id|free_initmem
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|__init_begin
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|addr
OL
(paren
r_int
r_int
)paren
(paren
op_amp
id|__init_end
)paren
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
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
id|addr
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|addr
)paren
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
id|printk
(paren
l_string|&quot;Freeing unused kernel memory: %dk freed&bslash;n&quot;
comma
(paren
op_amp
id|__init_end
op_minus
op_amp
id|__init_begin
)paren
op_rshift
l_int|10
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
DECL|function|free_initrd_mem
r_void
id|free_initrd_mem
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
(brace
r_for
c_loop
(paren
suffix:semicolon
id|start
OL
id|end
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
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
id|start
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|start
)paren
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|start
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;Freeing initrd memory: %ldk freed&bslash;n&quot;
comma
(paren
id|end
op_minus
id|start
)paren
op_rshift
l_int|10
)paren
suffix:semicolon
)brace
macro_line|#endif
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
c_func
(paren
)paren
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
id|totalhigh_pages
suffix:semicolon
id|val-&gt;freehigh
op_assign
id|nr_free_highpages
c_func
(paren
)paren
suffix:semicolon
id|val-&gt;mem_unit
op_assign
id|PAGE_SIZE
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
