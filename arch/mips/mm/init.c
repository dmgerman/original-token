multiline_comment|/*&n; *  arch/mips/mm/init.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *  Ported to MIPS by Ralf Baechle&n; */
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
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/mipsconfig.h&gt;
r_extern
r_int
r_int
id|pg0
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* page table for 0-4MB for everybody */
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
multiline_comment|/*&n; * BAD_PAGE is the page that is used for page faults when linux&n; * is out-of-memory. Older versions of linux just did a&n; * do_exit(), but using this instead means there is less risk&n; * for a process dying in kernel mode, possibly leaving a inode&n; * unused etc..&n; *&n; * BAD_PAGETABLE is the accompanying page-table: it is initialized&n; * to point to BAD_PAGE entries.&n; *&n; * ZERO_PAGE is a special page that is used for zero-initialized&n; * data and COW.&n; */
DECL|function|__bad_pagetable
r_int
r_int
id|__bad_pagetable
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
id|empty_bad_page_table
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
r_int
r_int
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;tsw&bslash;t%2,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%1,%1,1&bslash;n&bslash;t&quot;
l_string|&quot;bne&bslash;t$0,%1,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,%0,1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|BAD_PAGE
op_plus
id|PAGE_TABLE
)paren
comma
l_string|&quot;0&quot;
(paren
(paren
r_int
)paren
id|empty_bad_page_table
)paren
comma
l_string|&quot;1&quot;
(paren
id|PTRS_PER_PAGE
)paren
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|empty_bad_page_table
suffix:semicolon
)brace
DECL|function|__bad_page
r_int
r_int
id|__bad_page
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
id|empty_bad_page
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
r_int
r_int
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;tsw&bslash;t$0,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%1,%1,1&bslash;n&bslash;t&quot;
l_string|&quot;bne&bslash;t$0,%1,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,%0,1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
(paren
r_int
)paren
id|empty_bad_page
)paren
comma
l_string|&quot;1&quot;
(paren
id|PTRS_PER_PAGE
)paren
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|empty_bad_page
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
r_extern
r_char
id|empty_zero_page
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
r_int
r_int
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;tsw&bslash;t$0,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%1,%1,1&bslash;n&bslash;t&quot;
l_string|&quot;bne&bslash;t$0,%1,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,%0,1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
(paren
r_int
)paren
id|empty_zero_page
)paren
comma
l_string|&quot;1&quot;
(paren
id|PTRS_PER_PAGE
)paren
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|empty_zero_page
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
multiline_comment|/*&n; * paging_init() sets up the page tables - note that the first 4MB are&n; * already mapped by head.S.&n; *&n; * This routines also unmaps the page at virtual kernel address 0, so&n; * that we can trap those pesky NULL-reference errors in the kernel.&n; */
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
r_int
op_star
id|pg_dir
suffix:semicolon
r_int
r_int
op_star
id|pg_table
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
id|start_mem
op_assign
id|PAGE_ALIGN
c_func
(paren
id|start_mem
)paren
suffix:semicolon
id|address
op_assign
l_int|0
suffix:semicolon
id|pg_dir
op_assign
id|swapper_pg_dir
suffix:semicolon
r_while
c_loop
(paren
id|address
OL
id|end_mem
)paren
(brace
id|tmp
op_assign
op_star
id|pg_dir
suffix:semicolon
id|tmp
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
id|tmp
op_assign
id|start_mem
suffix:semicolon
id|start_mem
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * also map it in at 0x00000000 for init&n;&t;&t; */
op_star
id|pg_dir
op_assign
id|tmp
op_or
id|PAGE_TABLE
suffix:semicolon
id|pg_dir
op_increment
suffix:semicolon
id|pg_table
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|tmp
op_amp
id|PAGE_MASK
)paren
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
id|PTRS_PER_PAGE
suffix:semicolon
id|tmp
op_increment
comma
id|pg_table
op_increment
)paren
(brace
r_if
c_cond
(paren
id|address
OL
id|end_mem
)paren
op_star
id|pg_table
op_assign
id|address
op_or
id|PAGE_SHARED
suffix:semicolon
r_else
op_star
id|pg_table
op_assign
l_int|0
suffix:semicolon
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
macro_line|#if KERNELBASE == KSEG0
id|cacheflush
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
r_int
id|tmp
suffix:semicolon
r_extern
r_int
id|etext
suffix:semicolon
id|end_mem
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|high_memory
op_assign
id|end_mem
suffix:semicolon
multiline_comment|/* mark usable pages in the mem_map[] */
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
id|high_memory
)paren
(brace
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|start_mem
)paren
)braket
op_assign
l_int|0
suffix:semicolon
id|start_mem
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SCSI
id|scsi_mem_init
c_func
(paren
id|high_memory
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SOUND
id|sound_mem_init
c_func
(paren
)paren
suffix:semicolon
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
id|high_memory
suffix:semicolon
id|tmp
op_add_assign
id|PAGE_SIZE
)paren
(brace
r_if
c_cond
(paren
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|tmp
)paren
)braket
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * We don&squot;t have any reserved pages on the&n;&t;&t;&t; * MIPS systems supported until now&n;&t;&t;&t; */
r_if
c_cond
(paren
l_int|0
)paren
id|reservedpages
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tmp
OL
(paren
(paren
r_int
r_int
)paren
op_amp
id|etext
op_minus
id|KERNELBASE
)paren
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
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|tmp
)paren
)braket
op_assign
l_int|1
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
l_string|&quot;Memory: %luk/%luk available (%dk kernel code, %dk reserved, %dk data)&bslash;n&quot;
comma
id|tmp
op_rshift
l_int|10
comma
id|high_memory
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
)paren
suffix:semicolon
id|invalidate
c_func
(paren
)paren
suffix:semicolon
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
