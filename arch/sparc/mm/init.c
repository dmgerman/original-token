multiline_comment|/*&n; *  linux/arch/sparc/mm/init.c&n; *&n; *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
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
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/vac-ops.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
r_extern
r_void
id|scsi_mem_init
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|sound_mem_init
c_func
(paren
r_void
)paren
suffix:semicolon
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
r_extern
r_int
id|map_the_prom
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|invalid_segment
comma
id|num_segmaps
comma
id|num_contexts
suffix:semicolon
multiline_comment|/*&n; * BAD_PAGE is the page that is used for page faults when linux&n; * is out-of-memory. Older versions of linux just did a&n; * do_exit(), but using this instead means there is less risk&n; * for a process dying in kernel mode, possibly leaving a inode&n; * unused etc..&n; *&n; * BAD_PAGETABLE is the accompanying page-table: it is initialized&n; * to point to BAD_PAGE entries.&n; *&n; * ZERO_PAGE is a special page that is used for zero-initialized&n; * data and COW.&n; */
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
DECL|function|__zero_page
r_int
r_int
id|__zero_page
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
id|ZERO_PGE
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_return
id|ZERO_PGE
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
id|high_memory
op_rshift
id|PAGE_SHIFT
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
id|mem_map
(braket
id|i
)braket
op_amp
id|MAP_PAGE_RESERVED
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
multiline_comment|/*&n; * paging_init() sets up the page tables: in the alpha version this actually&n; * unmaps the bootup page table (as we&squot;re now in KSEG, so we don&squot;t need it).&n; *&n; * The bootup sequence put the virtual page table into high memory: that&n; * means that we can change the L1 page table by just using VL1p below.&n; */
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
id|pg_segmap
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|i
comma
id|a
comma
id|b
comma
id|mask
op_assign
l_int|0
suffix:semicolon
r_register
r_int
id|num_segs
comma
id|num_ctx
suffix:semicolon
r_register
r_char
op_star
id|c
suffix:semicolon
id|num_segs
op_assign
id|num_segmaps
suffix:semicolon
id|num_ctx
op_assign
id|num_contexts
suffix:semicolon
id|num_segs
op_sub_assign
l_int|1
suffix:semicolon
id|invalid_segment
op_assign
id|num_segs
suffix:semicolon
multiline_comment|/* On the sparc we first need to allocate the segmaps for the&n; * PROM&squot;s virtual space, and make those segmaps unusable. We&n; * map the PROM in ALL contexts therefore the break key and the&n; * sync command work no matter what state you took the machine&n; * out of&n; */
id|printk
c_func
(paren
l_string|&quot;mapping the prom...&bslash;n&quot;
)paren
suffix:semicolon
id|num_segs
op_assign
id|map_the_prom
c_func
(paren
id|num_segs
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
multiline_comment|/* ok, allocate the kernel pages, map them in all contexts&n;&t; * (with help from the prom), and lock them. Isn&squot;t the sparc&n;&t; * fun kiddies? TODO&n;&t; */
id|b
op_assign
id|PGDIR_ALIGN
c_func
(paren
id|start_mem
)paren
op_rshift
l_int|18
suffix:semicolon
id|c
op_assign
(paren
r_char
op_star
)paren
l_int|0x0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;mapping kernel in all contexts...&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|a
op_assign
l_int|0
suffix:semicolon
id|a
OL
id|b
suffix:semicolon
id|a
op_increment
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_contexts
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* map the kernel virt_addrs */
(paren
op_star
(paren
id|romvec-&gt;pv_setctxt
)paren
)paren
(paren
id|i
comma
(paren
r_char
op_star
)paren
id|c
comma
id|a
)paren
suffix:semicolon
)brace
id|c
op_add_assign
l_int|0x40000
suffix:semicolon
)brace
multiline_comment|/* Ok, since now mapped in all contexts, we can free up&n;&t; * context zero to be used amongst user processes.&n;&t; */
multiline_comment|/* free context 0 here TODO */
multiline_comment|/* invalidate all user pages and initialize the pte struct &n;&t; * for userland. TODO&n;&t; */
multiline_comment|/* Make the kernel text unwritable and cacheable, the prom&n;&t; * loaded out text as writable, only sneaky sunos kernels need&n;&t; * self-modifying code.&n;&t; */
id|a
op_assign
(paren
r_int
r_int
)paren
id|etext
suffix:semicolon
id|mask
op_assign
op_complement
(paren
id|PTE_NC
op_or
id|PTE_W
)paren
suffix:semicolon
multiline_comment|/* make cacheable + not writable */
id|printk
c_func
(paren
l_string|&quot;changing kernel text perms...&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* must do for every segment since kernel uses all contexts&n;&t; * and unlike some sun kernels I know of, we can&squot;t hard wire&n;&t; * context 0 just for the kernel, that is unnecessary.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|b
op_assign
id|PAGE_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
id|trapbase
)paren
suffix:semicolon
id|switch_to_context
c_func
(paren
id|i
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|b
OL
id|a
suffix:semicolon
id|b
op_add_assign
l_int|4096
)paren
(brace
id|put_pte
c_func
(paren
id|b
comma
(paren
id|get_pte
c_func
(paren
id|b
)paren
op_amp
id|mask
)paren
)paren
suffix:semicolon
)brace
)brace
id|invalidate
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* flush the virtual address cache */
id|printk
c_func
(paren
l_string|&quot;&bslash;nCurrently in context - &quot;
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
id|num_contexts
suffix:semicolon
id|i
op_increment
)paren
(brace
id|switch_to_context
c_func
(paren
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d &quot;
comma
(paren
r_int
)paren
id|i
)paren
suffix:semicolon
)brace
id|switch_to_context
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* invalidate all user segmaps for virt addrs 0-KERNBASE */
multiline_comment|/* WRONG, now I just let the kernel sit in low addresses only&n;         * from 0 -- end_kernel just like i386-linux. This will make&n;         * mem-code a bit easier to cope with.&n;&t; */
id|printk
c_func
(paren
l_string|&quot;&bslash;ninvalidating user segmaps&bslash;n&quot;
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|switch_to_context
c_func
(paren
id|i
)paren
suffix:semicolon
id|a
op_assign
(paren
(paren
r_int
r_int
)paren
op_amp
id|end
)paren
suffix:semicolon
r_for
c_loop
(paren
id|a
op_add_assign
l_int|524288
comma
id|pg_segmap
op_assign
l_int|0
suffix:semicolon
op_increment
id|pg_segmap
op_le
l_int|3584
suffix:semicolon
id|a
op_add_assign
(paren
l_int|1
op_lshift
l_int|18
)paren
)paren
(brace
id|put_segmap
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|a
comma
(paren
id|invalid_segment
op_amp
l_int|0x7f
)paren
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;wheee! have I sold out yet?&bslash;n&quot;
)paren
suffix:semicolon
id|invalidate
c_func
(paren
)paren
suffix:semicolon
r_return
id|free_area_init
c_func
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
r_return
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
id|high_memory
op_rshift
id|PAGE_SHIFT
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
id|mem_map
(braket
id|i
)braket
op_amp
id|MAP_PAGE_RESERVED
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
)paren
r_continue
suffix:semicolon
id|val-&gt;sharedram
op_add_assign
id|mem_map
(braket
id|i
)braket
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
