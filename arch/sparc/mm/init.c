multiline_comment|/*  $Id: init.c,v 1.42 1996/10/27 08:36:44 davem Exp $&n; *  linux/arch/sparc/mm/init.c&n; *&n; *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *  Copyright (C) 1995 Eddie C. Dost (ecd@skynet.be)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/vac-ops.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/vaddrs.h&gt;
r_extern
r_void
id|show_net_buffers
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|sp_banks
r_struct
id|sparc_phys_banks
id|sp_banks
(braket
id|SPARC_PHYS_BANKS
)braket
suffix:semicolon
DECL|variable|sparc_unmapped_base
r_int
r_int
id|sparc_unmapped_base
suffix:semicolon
multiline_comment|/*&n; * BAD_PAGE is the page that is used for page faults when linux&n; * is out-of-memory. Older versions of linux just did a&n; * do_exit(), but using this instead means there is less risk&n; * for a process dying in kernel mode, possibly leaving an inode&n; * unused etc..&n; *&n; * BAD_PAGETABLE is the accompanying page-table: it is initialized&n; * to point to BAD_PAGE entries.&n; *&n; * ZERO_PAGE is a special page that is used for zero-initialized&n; * data and COW.&n; */
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
id|EMPTY_PGT
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
id|EMPTY_PGT
suffix:semicolon
)brace
DECL|function|__bad_page
id|pte_t
id|__bad_page
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
id|EMPTY_PGE
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
(paren
r_int
r_int
)paren
id|EMPTY_PGE
comma
id|PAGE_SHARED
)paren
)paren
suffix:semicolon
)brace
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
id|mem_map
(braket
id|i
)braket
dot
id|count
)paren
id|free
op_increment
suffix:semicolon
r_else
id|shared
op_add_assign
id|mem_map
(braket
id|i
)braket
dot
id|count
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
r_extern
id|pgprot_t
id|protection_map
(braket
l_int|16
)braket
suffix:semicolon
DECL|function|sparc_context_init
r_int
r_int
id|sparc_context_init
c_func
(paren
r_int
r_int
id|start_mem
comma
r_int
id|numctx
)paren
(brace
r_int
id|ctx
suffix:semicolon
id|ctx_list_pool
op_assign
(paren
r_struct
id|ctx_list
op_star
)paren
id|start_mem
suffix:semicolon
id|start_mem
op_add_assign
(paren
id|numctx
op_star
r_sizeof
(paren
r_struct
id|ctx_list
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ctx
op_assign
l_int|0
suffix:semicolon
id|ctx
OL
id|numctx
suffix:semicolon
id|ctx
op_increment
)paren
(brace
r_struct
id|ctx_list
op_star
id|clist
suffix:semicolon
id|clist
op_assign
(paren
id|ctx_list_pool
op_plus
id|ctx
)paren
suffix:semicolon
id|clist-&gt;ctx_number
op_assign
id|ctx
suffix:semicolon
id|clist-&gt;ctx_mm
op_assign
l_int|0
suffix:semicolon
)brace
id|ctx_free.next
op_assign
id|ctx_free.prev
op_assign
op_amp
id|ctx_free
suffix:semicolon
id|ctx_used.next
op_assign
id|ctx_used.prev
op_assign
op_amp
id|ctx_used
suffix:semicolon
r_for
c_loop
(paren
id|ctx
op_assign
l_int|0
suffix:semicolon
id|ctx
OL
id|numctx
suffix:semicolon
id|ctx
op_increment
)paren
(brace
id|add_to_free_ctxlist
c_func
(paren
id|ctx_list_pool
op_plus
id|ctx
)paren
suffix:semicolon
)brace
r_return
id|start_mem
suffix:semicolon
)brace
multiline_comment|/*&n; * paging_init() sets up the page tables: We call the MMU specific&n; * init routine based upon the Sun model type on the Sparc.&n; *&n; */
r_extern
r_int
r_int
id|sun4c_paging_init
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
r_int
r_int
id|srmmu_paging_init
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
r_int
r_int
id|device_scan
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
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
r_switch
c_cond
(paren
id|sparc_cpu_model
)paren
(brace
r_case
id|sun4c
suffix:colon
r_case
id|sun4e
suffix:colon
id|start_mem
op_assign
id|sun4c_paging_init
c_func
(paren
id|start_mem
comma
id|end_mem
)paren
suffix:semicolon
id|sparc_unmapped_base
op_assign
l_int|0xe0000000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sun4m
suffix:colon
r_case
id|sun4d
suffix:colon
id|start_mem
op_assign
id|srmmu_paging_init
c_func
(paren
id|start_mem
comma
id|end_mem
)paren
suffix:semicolon
id|sparc_unmapped_base
op_assign
l_int|0x50000000
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot;paging_init: Cannot init paging on this Sparc&bslash;n&quot;
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;paging_init: sparc_cpu_model = %d&bslash;n&quot;
comma
id|sparc_cpu_model
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;paging_init: Halting...&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Initialize the protection map with non-constant, MMU dependent values. */
id|protection_map
(braket
l_int|0
)braket
op_assign
id|PAGE_NONE
suffix:semicolon
id|protection_map
(braket
l_int|1
)braket
op_assign
id|PAGE_READONLY
suffix:semicolon
id|protection_map
(braket
l_int|2
)braket
op_assign
id|PAGE_COPY
suffix:semicolon
id|protection_map
(braket
l_int|3
)braket
op_assign
id|PAGE_COPY
suffix:semicolon
id|protection_map
(braket
l_int|4
)braket
op_assign
id|PAGE_READONLY
suffix:semicolon
id|protection_map
(braket
l_int|5
)braket
op_assign
id|PAGE_READONLY
suffix:semicolon
id|protection_map
(braket
l_int|6
)braket
op_assign
id|PAGE_COPY
suffix:semicolon
id|protection_map
(braket
l_int|7
)braket
op_assign
id|PAGE_COPY
suffix:semicolon
id|protection_map
(braket
l_int|8
)braket
op_assign
id|PAGE_NONE
suffix:semicolon
id|protection_map
(braket
l_int|9
)braket
op_assign
id|PAGE_READONLY
suffix:semicolon
id|protection_map
(braket
l_int|10
)braket
op_assign
id|PAGE_SHARED
suffix:semicolon
id|protection_map
(braket
l_int|11
)braket
op_assign
id|PAGE_SHARED
suffix:semicolon
id|protection_map
(braket
l_int|12
)braket
op_assign
id|PAGE_READONLY
suffix:semicolon
id|protection_map
(braket
l_int|13
)braket
op_assign
id|PAGE_READONLY
suffix:semicolon
id|protection_map
(braket
l_int|14
)braket
op_assign
id|PAGE_SHARED
suffix:semicolon
id|protection_map
(braket
l_int|15
)braket
op_assign
id|PAGE_SHARED
suffix:semicolon
r_return
id|device_scan
c_func
(paren
id|start_mem
)paren
suffix:semicolon
)brace
DECL|variable|sparc_aliases
r_struct
id|cache_palias
op_star
id|sparc_aliases
suffix:semicolon
r_extern
r_int
id|min_free_pages
suffix:semicolon
r_extern
r_int
id|free_pages_low
suffix:semicolon
r_extern
r_int
id|free_pages_high
suffix:semicolon
r_extern
r_void
id|srmmu_frob_mem_map
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|variable|physmem_mapped_contig
r_int
id|physmem_mapped_contig
op_assign
l_int|1
suffix:semicolon
DECL|function|taint_real_pages
r_static
r_void
id|taint_real_pages
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
r_int
id|addr
comma
id|tmp2
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|physmem_mapped_contig
)paren
(brace
r_for
c_loop
(paren
id|addr
op_assign
id|PAGE_OFFSET
suffix:semicolon
id|addr
OL
id|end_mem
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
)paren
(brace
r_if
c_cond
(paren
id|addr
op_ge
id|KERNBASE
op_logical_and
id|addr
OL
id|start_mem
)paren
(brace
id|addr
op_assign
id|start_mem
suffix:semicolon
)brace
r_for
c_loop
(paren
id|tmp2
op_assign
l_int|0
suffix:semicolon
id|sp_banks
(braket
id|tmp2
)braket
dot
id|num_bytes
op_ne
l_int|0
suffix:semicolon
id|tmp2
op_increment
)paren
(brace
r_int
r_int
id|phys_addr
op_assign
(paren
id|addr
op_minus
id|PAGE_OFFSET
)paren
suffix:semicolon
r_int
r_int
id|base
op_assign
id|sp_banks
(braket
id|tmp2
)braket
dot
id|base_addr
suffix:semicolon
r_int
r_int
id|limit
op_assign
id|base
op_plus
id|sp_banks
(braket
id|tmp2
)braket
dot
id|num_bytes
suffix:semicolon
r_if
c_cond
(paren
(paren
id|phys_addr
op_ge
id|base
)paren
op_logical_and
(paren
id|phys_addr
OL
id|limit
)paren
op_logical_and
(paren
(paren
id|phys_addr
op_plus
id|PAGE_SIZE
)paren
OL
id|limit
)paren
)paren
(brace
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|addr
)paren
)braket
dot
id|flags
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|PG_reserved
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|sparc_cpu_model
op_eq
id|sun4m
)paren
op_logical_or
(paren
id|sparc_cpu_model
op_eq
id|sun4d
)paren
)paren
(brace
id|srmmu_frob_mem_map
c_func
(paren
id|start_mem
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|addr
op_assign
id|start_mem
suffix:semicolon
id|addr
OL
id|end_mem
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|addr
)paren
)braket
dot
id|flags
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|PG_reserved
)paren
suffix:semicolon
)brace
)brace
)brace
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
id|tmp2
comma
id|addr
suffix:semicolon
r_extern
r_char
id|etext
suffix:semicolon
multiline_comment|/* Saves us work later. */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|ZERO_PAGE
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|end_mem
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|max_mapnr
op_assign
id|MAP_NR
c_func
(paren
id|end_mem
)paren
suffix:semicolon
id|high_memory
op_assign
(paren
r_void
op_star
)paren
id|end_mem
suffix:semicolon
id|start_mem
op_assign
id|PAGE_ALIGN
c_func
(paren
id|start_mem
)paren
suffix:semicolon
id|addr
op_assign
id|KERNBASE
suffix:semicolon
r_while
c_loop
(paren
id|addr
OL
id|start_mem
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|initrd_below_start_ok
op_logical_and
id|addr
op_ge
id|initrd_start
op_logical_and
id|addr
OL
id|initrd_end
)paren
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|addr
)paren
)braket
dot
id|flags
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|PG_reserved
)paren
suffix:semicolon
r_else
macro_line|#endif&t;
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|addr
)paren
)braket
dot
id|flags
op_or_assign
(paren
l_int|1
op_lshift
id|PG_reserved
)paren
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|taint_real_pages
c_func
(paren
id|start_mem
comma
id|end_mem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|PAGE_OFFSET
suffix:semicolon
id|addr
OL
id|end_mem
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
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
id|MAP_NR
c_func
(paren
id|addr
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|addr
OL
(paren
r_int
r_int
)paren
op_amp
id|etext
)paren
op_logical_and
(paren
id|addr
op_ge
id|KERNBASE
)paren
)paren
id|codepages
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|addr
OL
id|start_mem
)paren
op_logical_and
(paren
id|addr
op_ge
id|KERNBASE
)paren
)paren
(brace
id|datapages
op_increment
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|addr
)paren
)braket
dot
id|count
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
op_logical_neg
id|initrd_start
op_logical_or
(paren
id|addr
OL
id|initrd_start
op_logical_or
id|addr
op_ge
id|initrd_end
)paren
)paren
macro_line|#endif
id|free_page
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
id|tmp2
op_assign
id|nr_free_pages
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Memory: %luk available (%dk kernel code, %dk data) [%08lx,%08lx]&bslash;n&quot;
comma
id|tmp2
op_rshift
l_int|10
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
comma
id|PAGE_OFFSET
comma
id|end_mem
)paren
suffix:semicolon
id|min_free_pages
op_assign
id|nr_free_pages
op_rshift
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|min_free_pages
OL
l_int|16
)paren
(brace
id|min_free_pages
op_assign
l_int|16
suffix:semicolon
)brace
id|free_pages_low
op_assign
id|min_free_pages
op_plus
(paren
id|min_free_pages
op_rshift
l_int|1
)paren
suffix:semicolon
id|free_pages_high
op_assign
id|min_free_pages
op_plus
id|min_free_pages
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
r_int
id|i
suffix:semicolon
id|i
op_assign
id|MAP_NR
c_func
(paren
id|high_memory
)paren
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
id|mem_map
(braket
id|i
)braket
dot
id|count
)paren
r_continue
suffix:semicolon
id|val-&gt;sharedram
op_add_assign
id|mem_map
(braket
id|i
)braket
dot
id|count
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
)brace
eof
