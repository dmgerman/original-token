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
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/jazzdma.h&gt;
macro_line|#include &lt;asm/vector.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
r_extern
r_void
id|deskstation_tyne_dma_init
c_func
(paren
r_void
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
r_char
id|empty_zero_page
(braket
id|PAGE_SIZE
)braket
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
r_extern
r_char
id|empty_bad_page_table
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
r_int
r_int
id|dummy1
comma
id|dummy2
suffix:semicolon
id|page
op_assign
(paren
(paren
r_int
r_int
)paren
id|empty_bad_page_table
)paren
op_plus
(paren
id|PT_OFFSET
op_minus
id|PAGE_OFFSET
)paren
suffix:semicolon
macro_line|#if __mips__ &gt;= 3
multiline_comment|/*&n;         * Use 64bit code even for Linux/MIPS 32bit on R4000&n;         */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;
l_string|&quot;dsll32&bslash;t$1,%2,0&bslash;n&bslash;t&quot;
l_string|&quot;dsrl32&bslash;t%2,$1,0&bslash;n&bslash;t&quot;
l_string|&quot;or&bslash;t%2,$1&bslash;n&quot;
l_string|&quot;1:&bslash;tsd&bslash;t%2,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%1,1&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%1,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,8&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips0&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dummy1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|pte_val
c_func
(paren
id|BAD_PAGE
)paren
)paren
comma
l_string|&quot;0&quot;
(paren
id|page
)paren
comma
l_string|&quot;1&quot;
(paren
id|PAGE_SIZE
op_div
l_int|8
)paren
)paren
suffix:semicolon
macro_line|#else
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&quot;
l_string|&quot;1:&bslash;tsw&bslash;t%2,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%1,1&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%1,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,4&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dummy1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|pte_val
c_func
(paren
id|BAD_PAGE
)paren
)paren
comma
l_string|&quot;0&quot;
(paren
id|page
)paren
comma
l_string|&quot;1&quot;
(paren
id|PAGE_SIZE
op_div
l_int|4
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
id|pte_t
op_star
)paren
id|page
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__zeropage
id|__zeropage
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|dummy1
comma
id|dummy2
suffix:semicolon
macro_line|#ifdef __R4000__
multiline_comment|/*&n;         * Use 64bit code even for Linux/MIPS 32bit on R4000&n;         */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips3&bslash;n&quot;
l_string|&quot;1:&bslash;tsd&bslash;t$0,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%1,1&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%1,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,8&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips0&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dummy1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy2
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|page
)paren
comma
l_string|&quot;1&quot;
(paren
id|PAGE_SIZE
op_div
l_int|8
)paren
)paren
suffix:semicolon
macro_line|#else
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&quot;
l_string|&quot;1:&bslash;tsw&bslash;t$0,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%1,1&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%1,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,4&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dummy1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy2
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|page
)paren
comma
l_string|&quot;1&quot;
(paren
id|PAGE_SIZE
op_div
l_int|4
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_inline
r_void
DECL|function|zeropage
id|zeropage
c_func
(paren
r_int
r_int
id|page
)paren
(brace
id|sys_cacheflush
c_func
(paren
(paren
r_void
op_star
)paren
id|page
comma
id|PAGE_SIZE
comma
id|BCACHE
)paren
suffix:semicolon
id|sync_mem
c_func
(paren
)paren
suffix:semicolon
id|__zeropage
c_func
(paren
id|page
op_plus
(paren
id|PT_OFFSET
op_minus
id|PAGE_OFFSET
)paren
)paren
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
r_extern
r_char
id|empty_bad_page
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
r_int
r_int
id|page
op_assign
(paren
r_int
r_int
)paren
id|empty_bad_page
suffix:semicolon
id|zeropage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|pte_mkdirty
c_func
(paren
id|mk_pte
c_func
(paren
id|page
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
r_int
r_int
id|page
op_assign
(paren
r_int
r_int
)paren
id|empty_zero_page
suffix:semicolon
id|zeropage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
multiline_comment|/*&n; * This is horribly inefficient ...&n; */
DECL|function|__copy_page
r_void
id|__copy_page
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|to
)paren
(brace
multiline_comment|/*&n;&t; * Now copy page from uncached KSEG1 to KSEG0.  The copy destination&n;&t; * is in KSEG0 so that we keep stupid L2 caches happy.&n;&t; */
r_if
c_cond
(paren
id|from
op_eq
(paren
r_int
r_int
)paren
id|empty_zero_page
)paren
(brace
multiline_comment|/*&n;&t;&t; * The page copied most is the COW empty_zero_page.  Since we&n;&t;&t; * know it&squot;s contents we can avoid the writeback reading of&n;&t;&t; * the page.  Speeds up the standard case alot.&n;&t;&t; */
id|__zeropage
c_func
(paren
id|to
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Force writeback of old page to memory.  We don&squot;t know the&n;&t;&t; * virtual address, so we have to flush the entire cache ...&n;&t;&t; */
id|sys_cacheflush
c_func
(paren
l_int|0
comma
op_complement
l_int|0
comma
id|DCACHE
)paren
suffix:semicolon
id|sync_mem
c_func
(paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|to
comma
(paren
r_void
op_star
)paren
(paren
id|from
op_plus
(paren
id|PT_OFFSET
op_minus
id|PAGE_OFFSET
)paren
)paren
comma
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now writeback the page again if colour has changed.&n;&t; * Actually this does a Hit_Writeback, but due to an artifact in&n;&t; * the R4xx0 implementation this should be slightly faster.&n;&t; * Then sweep chipset controlled secondary caches and the ICACHE.&n;&t; */
r_if
c_cond
(paren
id|page_colour
c_func
(paren
id|from
)paren
op_ne
id|page_colour
c_func
(paren
id|to
)paren
)paren
id|sys_cacheflush
c_func
(paren
l_int|0
comma
op_complement
l_int|0
comma
id|DCACHE
)paren
suffix:semicolon
id|sys_cacheflush
c_func
(paren
l_int|0
comma
op_complement
l_int|0
comma
id|ICACHE
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
(paren
id|high_memory
op_minus
id|PAGE_OFFSET
)paren
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
dot
id|reserved
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
id|pgd_init
c_func
(paren
(paren
r_int
r_int
)paren
id|swapper_pg_dir
op_minus
(paren
id|PT_OFFSET
op_minus
id|PAGE_OFFSET
)paren
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
macro_line|#ifdef CONFIG_MIPS_JAZZ
id|start_mem
op_assign
id|vdma_init
c_func
(paren
id|start_mem
comma
id|end_mem
)paren
suffix:semicolon
macro_line|#endif
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
id|tmp
op_assign
id|start_mem
suffix:semicolon
r_while
c_loop
(paren
id|tmp
OL
id|high_memory
)paren
(brace
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|tmp
)paren
)braket
dot
id|reserved
op_assign
l_int|0
suffix:semicolon
id|tmp
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DESKSTATION_TYNE
id|deskstation_tyne_dma_init
c_func
(paren
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
id|PAGE_OFFSET
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
dot
id|reserved
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
r_if
c_cond
(paren
id|tmp
OL
id|start_mem
)paren
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
dot
id|count
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
l_string|&quot;Memory: %luk/%luk available (%dk kernel code, %dk data)&bslash;n&quot;
comma
id|tmp
op_rshift
l_int|10
comma
(paren
id|high_memory
op_minus
id|PAGE_OFFSET
)paren
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
dot
id|reserved
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
r_return
suffix:semicolon
)brace
eof
