multiline_comment|/*&n; *  linux/arch/alpha/mm/init.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; */
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
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
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
id|show_net_buffers
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * BAD_PAGE is the page that is used for page faults when linux&n; * is out-of-memory. Older versions of linux just did a&n; * do_exit(), but using this instead means there is less risk&n; * for a process dying in kernel mode, possibly leaving an inode&n; * unused etc..&n; *&n; * BAD_PAGETABLE is the accompanying page-table: it is initialized&n; * to point to BAD_PAGE entries.&n; *&n; * ZERO_PAGE is a special page that is used for zero-initialized&n; * data and COW.&n; */
DECL|function|__bad_pagetable
id|pmd_t
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
id|pmd_t
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
DECL|function|load_PCB
r_static
r_void
id|load_PCB
c_func
(paren
r_struct
id|thread_struct
op_star
id|pcb
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stq $30,0(%0)&bslash;n&bslash;t&quot;
l_string|&quot;bis %0,%0,$16&bslash;n&bslash;t&quot;
l_string|&quot;call_pal %1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|pcb
)paren
comma
l_string|&quot;i&quot;
(paren
id|PAL_swpctx
)paren
suffix:colon
l_string|&quot;$0&quot;
comma
l_string|&quot;$1&quot;
comma
l_string|&quot;$16&quot;
comma
l_string|&quot;$22&quot;
comma
l_string|&quot;$23&quot;
comma
l_string|&quot;$24&quot;
comma
l_string|&quot;$25&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * paging_init() sets up the page tables: in the alpha version this actually&n; * unmaps the bootup page table (as we&squot;re now in KSEG, so we don&squot;t need it).&n; */
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
id|i
suffix:semicolon
r_int
r_int
id|newptbr
suffix:semicolon
r_struct
id|memclust_struct
op_star
id|cluster
suffix:semicolon
r_struct
id|memdesc_struct
op_star
id|memdesc
suffix:semicolon
multiline_comment|/* initialize mem_map[] */
id|start_mem
op_assign
id|free_area_init
c_func
(paren
id|start_mem
comma
id|end_mem
)paren
suffix:semicolon
multiline_comment|/* find free clusters, update mem_map[] accordingly */
id|memdesc
op_assign
(paren
r_struct
id|memdesc_struct
op_star
)paren
(paren
id|INIT_HWRPB-&gt;mddt_offset
op_plus
(paren
r_int
r_int
)paren
id|INIT_HWRPB
)paren
suffix:semicolon
id|cluster
op_assign
id|memdesc-&gt;cluster
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|memdesc-&gt;numclusters
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
comma
id|cluster
op_increment
)paren
(brace
r_int
r_int
id|pfn
comma
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|cluster-&gt;usage
op_amp
l_int|1
)paren
r_continue
suffix:semicolon
id|pfn
op_assign
id|cluster-&gt;start_pfn
suffix:semicolon
id|nr
op_assign
id|cluster-&gt;numpages
suffix:semicolon
multiline_comment|/* non-volatile memory. We might want to mark this for later */
r_if
c_cond
(paren
id|cluster-&gt;usage
op_amp
l_int|2
)paren
r_continue
suffix:semicolon
r_while
c_loop
(paren
id|nr
op_decrement
)paren
id|clear_bit
c_func
(paren
id|PG_reserved
comma
op_amp
id|mem_map
(braket
id|pfn
op_increment
)braket
dot
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* unmap the console stuff: we don&squot;t need it, and we don&squot;t want it */
multiline_comment|/* Also set up the real kernel PCB while we&squot;re at it.. */
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
id|memset
c_func
(paren
id|swapper_pg_dir
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|newptbr
op_assign
(paren
(paren
r_int
r_int
)paren
id|swapper_pg_dir
op_minus
id|PAGE_OFFSET
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|pgd_val
c_func
(paren
id|swapper_pg_dir
(braket
l_int|1023
)braket
)paren
op_assign
(paren
id|newptbr
op_lshift
l_int|32
)paren
op_or
id|pgprot_val
c_func
(paren
id|PAGE_KERNEL
)paren
suffix:semicolon
id|init_task.tss.ptbr
op_assign
id|newptbr
suffix:semicolon
id|init_task.tss.pal_flags
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* set FEN, clear everything else */
id|init_task.tss.flags
op_assign
l_int|0
suffix:semicolon
id|init_task.kernel_stack_page
op_assign
id|INIT_STACK
suffix:semicolon
id|load_PCB
c_func
(paren
op_amp
id|init_task.tss
)paren
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
r_return
id|start_mem
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
r_int
id|tmp
suffix:semicolon
id|end_mem
op_and_assign
id|PAGE_MASK
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
multiline_comment|/*&n;&t; * Mark the pages used by the kernel as reserved..&n;&t; */
id|tmp
op_assign
id|KERNEL_START
suffix:semicolon
r_while
c_loop
(paren
id|tmp
OL
id|start_mem
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
id|tmp
)paren
)braket
dot
id|flags
)paren
suffix:semicolon
id|tmp
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_for
c_loop
(paren
id|tmp
op_assign
id|PAGE_OFFSET
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
id|tmp
op_ge
id|MAX_DMA_ADDRESS
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
r_continue
suffix:semicolon
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
id|free_page
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
id|tmp
op_assign
id|nr_free_pages
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Memory: %luk available&bslash;n&quot;
comma
id|tmp
op_rshift
l_int|10
)paren
suffix:semicolon
r_return
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
