multiline_comment|/*&n; *  linux/mm/vmscan.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  Swap reorganised 29.12.95, Stephen Tweedie.&n; *  kswapd added: 7.1.96  sct&n; *  Removed kswapd_ctl limits, and swap out as many pages as needed&n; *  to bring the system back to free_pages_high: 2.4.97, Rik van Riel.&n; *  Version: $Id: vmscan.c,v 1.23 1997/04/12 04:31:05 davem Exp $&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/swapctl.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/system.h&gt; /* for cli()/sti() */
macro_line|#include &lt;asm/uaccess.h&gt; /* for copy_to/from_user */
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/* &n; * When are we next due for a page scan? &n; */
DECL|variable|next_swap_jiffies
r_static
r_int
id|next_swap_jiffies
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &n; * How often do we do a pageout scan during normal conditions?&n; * Default is four times a second.&n; */
DECL|variable|swapout_interval
r_int
id|swapout_interval
op_assign
id|HZ
op_div
l_int|4
suffix:semicolon
multiline_comment|/* &n; * The wait queue for waking up the pageout daemon:&n; */
DECL|variable|kswapd_wait
r_static
r_struct
id|wait_queue
op_star
id|kswapd_wait
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* &n; * We avoid doing a reschedule if the pageout daemon is already awake;&n; */
DECL|variable|kswapd_awake
r_static
r_int
id|kswapd_awake
op_assign
l_int|0
suffix:semicolon
r_static
r_void
id|init_swap_timer
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * The swap-out functions return 1 if they successfully&n; * threw something out, and we got a free page. It returns&n; * zero if it couldn&squot;t do anything, and any other value&n; * indicates it decreased rss, but the page was shared.&n; *&n; * NOTE! If it sleeps, it *must* return 1 to make sure we&n; * don&squot;t continue with the swap-out. Otherwise we may be&n; * using a process that no longer actually exists (it might&n; * have died while we slept).&n; */
DECL|function|try_to_swap_out
r_static
r_inline
r_int
id|try_to_swap_out
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
op_star
id|page_table
comma
r_int
id|dma
comma
r_int
id|wait
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
r_int
r_int
id|entry
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
r_struct
id|page
op_star
id|page_map
suffix:semicolon
id|pte
op_assign
op_star
id|page_table
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
id|pte
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|page
op_assign
id|pte_page
c_func
(paren
id|pte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MAP_NR
c_func
(paren
id|page
)paren
op_ge
id|max_mapnr
)paren
r_return
l_int|0
suffix:semicolon
id|page_map
op_assign
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|page_map
)paren
op_logical_or
id|PageLocked
c_func
(paren
id|page_map
)paren
op_logical_or
(paren
id|dma
op_logical_and
op_logical_neg
id|PageDMA
c_func
(paren
id|page_map
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Deal with page aging.  Pages age from being unused; they&n;&t; * rejuvenate on being accessed.  Only swap old pages (age==0&n;&t; * is oldest). */
r_if
c_cond
(paren
(paren
id|pte_dirty
c_func
(paren
id|pte
)paren
op_logical_and
id|delete_from_swap_cache
c_func
(paren
id|MAP_NR
c_func
(paren
id|page
)paren
)paren
)paren
op_logical_or
id|pte_young
c_func
(paren
id|pte
)paren
)paren
(brace
id|set_pte
c_func
(paren
id|page_table
comma
id|pte_mkold
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
id|touch_page
c_func
(paren
id|page_map
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|age_page
c_func
(paren
id|page_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page_map-&gt;age
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pte_dirty
c_func
(paren
id|pte
)paren
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_ops
op_logical_and
id|vma-&gt;vm_ops-&gt;swapout
)paren
(brace
id|pid_t
id|pid
op_assign
id|tsk-&gt;pid
suffix:semicolon
id|vma-&gt;vm_mm-&gt;rss
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_ops
op_member_access_from_pointer
id|swapout
c_func
(paren
id|vma
comma
id|address
op_minus
id|vma-&gt;vm_start
op_plus
id|vma-&gt;vm_offset
comma
id|page_table
)paren
)paren
id|kill_proc
c_func
(paren
id|pid
comma
id|SIGBUS
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|page_map-&gt;count
)paren
op_ne
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|entry
op_assign
id|get_swap_page
c_func
(paren
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|vma-&gt;vm_mm-&gt;rss
op_decrement
suffix:semicolon
id|flush_cache_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|page_table
comma
id|__pte
c_func
(paren
id|entry
)paren
)paren
suffix:semicolon
id|flush_tlb_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
id|tsk-&gt;nswap
op_increment
suffix:semicolon
id|rw_swap_page
c_func
(paren
id|WRITE
comma
id|entry
comma
(paren
r_char
op_star
)paren
id|page
comma
id|wait
)paren
suffix:semicolon
)brace
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* we slept: the process may not exist any more */
)brace
r_if
c_cond
(paren
(paren
id|entry
op_assign
id|find_in_swap_cache
c_func
(paren
id|MAP_NR
c_func
(paren
id|page
)paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|page_map-&gt;count
)paren
op_ne
l_int|1
)paren
(brace
id|set_pte
c_func
(paren
id|page_table
comma
id|pte_mkdirty
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Aiee.. duplicated cached swap-cache entry&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|vma-&gt;vm_mm-&gt;rss
op_decrement
suffix:semicolon
id|flush_cache_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|page_table
comma
id|__pte
c_func
(paren
id|entry
)paren
)paren
suffix:semicolon
id|flush_tlb_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|vma-&gt;vm_mm-&gt;rss
op_decrement
suffix:semicolon
id|flush_cache_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
id|pte_clear
c_func
(paren
id|page_table
)paren
suffix:semicolon
id|flush_tlb_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
id|entry
op_assign
id|page_unuse
c_func
(paren
id|page
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
multiline_comment|/*&n; * A new implementation of swap_out().  We do not swap complete processes,&n; * but only a small number of blocks, before we continue with the next&n; * process.  The number of blocks actually swapped is determined on the&n; * number of page faults, that this process actually had in the last time,&n; * so we won&squot;t swap heavily used processes all the time ...&n; *&n; * Note: the priority argument is a hint on much CPU to waste with the&n; *       swap block search, not a hint, of how much blocks to swap with&n; *       each process.&n; *&n; * (C) 1993 Kai Petzke, wpp@marie.physik.tu-berlin.de&n; */
DECL|function|swap_out_pmd
r_static
r_inline
r_int
id|swap_out_pmd
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
id|pmd_t
op_star
id|dir
comma
r_int
r_int
id|address
comma
r_int
r_int
id|end
comma
r_int
id|dma
comma
r_int
id|wait
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
r_int
id|pmd_end
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|dir
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|dir
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;swap_out_pmd: bad pmd (%08lx)&bslash;n&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|dir
)paren
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pte
op_assign
id|pte_offset
c_func
(paren
id|dir
comma
id|address
)paren
suffix:semicolon
id|pmd_end
op_assign
(paren
id|address
op_plus
id|PMD_SIZE
)paren
op_amp
id|PMD_MASK
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|pmd_end
)paren
id|end
op_assign
id|pmd_end
suffix:semicolon
r_do
(brace
r_int
id|result
suffix:semicolon
id|tsk-&gt;swap_address
op_assign
id|address
op_plus
id|PAGE_SIZE
suffix:semicolon
id|result
op_assign
id|try_to_swap_out
c_func
(paren
id|tsk
comma
id|vma
comma
id|address
comma
id|pte
comma
id|dma
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|pte
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
OL
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|swap_out_pgd
r_static
r_inline
r_int
id|swap_out_pgd
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
id|pgd_t
op_star
id|dir
comma
r_int
r_int
id|address
comma
r_int
r_int
id|end
comma
r_int
id|dma
comma
r_int
id|wait
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
r_int
id|pgd_end
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|dir
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|dir
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;swap_out_pgd: bad pgd (%08lx)&bslash;n&quot;
comma
id|pgd_val
c_func
(paren
op_star
id|dir
)paren
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|address
)paren
suffix:semicolon
id|pgd_end
op_assign
(paren
id|address
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|pgd_end
)paren
id|end
op_assign
id|pgd_end
suffix:semicolon
r_do
(brace
r_int
id|result
op_assign
id|swap_out_pmd
c_func
(paren
id|tsk
comma
id|vma
comma
id|pmd
comma
id|address
comma
id|end
comma
id|dma
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PMD_SIZE
)paren
op_amp
id|PMD_MASK
suffix:semicolon
id|pmd
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
OL
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|swap_out_vma
r_static
r_int
id|swap_out_vma
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
id|pgd_t
op_star
id|pgdir
comma
r_int
r_int
id|start
comma
r_int
id|dma
comma
r_int
id|wait
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
multiline_comment|/* Don&squot;t swap out areas like shared memory which have their&n;&t;    own separate swapping mechanism or areas which are locked down */
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
(paren
id|VM_SHM
op_or
id|VM_LOCKED
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|end
op_assign
id|vma-&gt;vm_end
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
r_int
id|result
op_assign
id|swap_out_pgd
c_func
(paren
id|tsk
comma
id|vma
comma
id|pgdir
comma
id|start
comma
id|end
comma
id|dma
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
id|start
op_assign
(paren
id|start
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
id|pgdir
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|swap_out_process
r_static
r_int
id|swap_out_process
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_int
id|dma
comma
r_int
id|wait
)paren
(brace
r_int
r_int
id|address
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
multiline_comment|/*&n;&t; * Go through process&squot; page directory.&n;&t; */
id|address
op_assign
id|p-&gt;swap_address
suffix:semicolon
id|p-&gt;swap_address
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Find the proper vm-area&n;&t; */
id|vma
op_assign
id|find_vma
c_func
(paren
id|p-&gt;mm
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|address
OL
id|vma-&gt;vm_start
)paren
id|address
op_assign
id|vma-&gt;vm_start
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|result
op_assign
id|swap_out_vma
c_func
(paren
id|p
comma
id|vma
comma
id|pgd_offset
c_func
(paren
id|p-&gt;mm
comma
id|address
)paren
comma
id|address
comma
id|dma
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
)paren
r_break
suffix:semicolon
id|address
op_assign
id|vma-&gt;vm_start
suffix:semicolon
)brace
id|p-&gt;swap_address
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|swap_out
r_static
r_int
id|swap_out
c_func
(paren
r_int
r_int
id|priority
comma
r_int
id|dma
comma
r_int
id|wait
)paren
(brace
r_static
r_int
id|swap_task
suffix:semicolon
r_int
id|loop
comma
id|counter
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|counter
op_assign
(paren
(paren
id|PAGEOUT_WEIGHT
op_star
id|nr_tasks
)paren
op_rshift
l_int|10
)paren
op_rshift
id|priority
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|counter
op_ge
l_int|0
suffix:semicolon
id|counter
op_decrement
)paren
(brace
multiline_comment|/*&n;&t;&t; * Check that swap_task is suitable for swapping.  If not, look for&n;&t;&t; * the next suitable process.&n;&t;&t; */
id|loop
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|swap_task
op_ge
id|NR_TASKS
)paren
(brace
id|swap_task
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|loop
)paren
multiline_comment|/* all processes are unswappable or already swapped out */
r_return
l_int|0
suffix:semicolon
id|loop
op_assign
l_int|1
suffix:semicolon
)brace
id|p
op_assign
id|task
(braket
id|swap_task
)braket
suffix:semicolon
r_if
c_cond
(paren
id|p
op_logical_and
id|p-&gt;swappable
op_logical_and
id|p-&gt;mm-&gt;rss
)paren
r_break
suffix:semicolon
id|swap_task
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Determine the number of pages to swap from this process.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;swap_cnt
)paren
(brace
multiline_comment|/* Normalise the number of pages swapped by&n;&t;&t;&t;   multiplying by (RSS / 1MB) */
id|p-&gt;swap_cnt
op_assign
id|AGE_CLUSTER_SIZE
c_func
(paren
id|p-&gt;mm-&gt;rss
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|p-&gt;swap_cnt
)paren
id|swap_task
op_increment
suffix:semicolon
r_switch
c_cond
(paren
id|swap_out_process
c_func
(paren
id|p
comma
id|dma
comma
id|wait
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|p-&gt;swap_cnt
)paren
id|swap_task
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We are much more aggressive about trying to swap out than we used&n; * to be.  This works out OK, because we now do proper aging on page&n; * contents. &n; */
DECL|function|try_to_free_page
r_int
id|try_to_free_page
c_func
(paren
r_int
id|priority
comma
r_int
id|dma
comma
r_int
id|wait
)paren
(brace
r_static
r_int
id|state
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|6
suffix:semicolon
r_int
id|stop
suffix:semicolon
multiline_comment|/* we don&squot;t try as hard if we&squot;re not waiting.. */
id|stop
op_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
id|stop
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|state
)paren
(brace
r_do
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|shrink_mmap
c_func
(paren
id|i
comma
id|dma
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|state
op_assign
l_int|1
suffix:semicolon
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|kmem_cache_reap
c_func
(paren
id|i
comma
id|dma
comma
id|wait
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|state
op_assign
l_int|2
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|shm_swap
c_func
(paren
id|i
comma
id|dma
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|state
op_assign
l_int|3
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|swap_out
c_func
(paren
id|i
comma
id|dma
comma
id|wait
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|state
op_assign
l_int|0
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|i
op_minus
id|stop
)paren
op_ge
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The background pageout daemon.&n; * Started as a kernel thread from the init process.&n; */
DECL|function|kswapd
r_int
id|kswapd
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|revision
op_assign
l_string|&quot;$Revision: 1.23 $&quot;
comma
op_star
id|s
comma
op_star
id|e
suffix:semicolon
id|current-&gt;session
op_assign
l_int|1
suffix:semicolon
id|current-&gt;pgrp
op_assign
l_int|1
suffix:semicolon
id|sprintf
c_func
(paren
id|current-&gt;comm
comma
l_string|&quot;kswapd&quot;
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
op_complement
l_int|0UL
suffix:semicolon
multiline_comment|/*&n;&t; *&t;As a kernel thread we want to tamper with system buffers&n;&t; *&t;and other internals and thus be subject to the SMP locking&n;&t; *&t;rules. (On a uniprocessor box this does nothing).&n;&t; */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Give kswapd a realtime priority. */
id|current-&gt;policy
op_assign
id|SCHED_FIFO
suffix:semicolon
id|current-&gt;priority
op_assign
l_int|32
suffix:semicolon
multiline_comment|/* Fixme --- we need to standardise our&n;&t;&t;&t;&t;    namings for POSIX.4 realtime scheduling&n;&t;&t;&t;&t;    priorities.  */
id|init_swap_timer
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|s
op_assign
id|strchr
c_func
(paren
id|revision
comma
l_char|&squot;:&squot;
)paren
)paren
op_logical_and
(paren
id|e
op_assign
id|strchr
c_func
(paren
id|s
comma
l_char|&squot;$&squot;
)paren
)paren
)paren
id|s
op_increment
comma
id|i
op_assign
id|e
op_minus
id|s
suffix:semicolon
r_else
id|s
op_assign
id|revision
comma
id|i
op_assign
op_minus
l_int|1
suffix:semicolon
id|printk
(paren
l_string|&quot;Started kswapd v%.*s&bslash;n&quot;
comma
id|i
comma
id|s
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|kswapd_awake
op_assign
l_int|0
suffix:semicolon
id|current-&gt;signal
op_assign
l_int|0
suffix:semicolon
id|run_task_queue
c_func
(paren
op_amp
id|tq_disk
)paren
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|kswapd_wait
)paren
suffix:semicolon
id|kswapd_awake
op_assign
l_int|1
suffix:semicolon
id|swapstats.wakeups
op_increment
suffix:semicolon
multiline_comment|/* Do the background pageout: &n;&t;&t; * We now only swap out as many pages as needed.&n;&t;&t; * When we are truly low on memory, we swap out&n;&t;&t; * synchronously (WAIT == 1).  -- Rik.&n;&t;&t; */
r_while
c_loop
(paren
id|nr_free_pages
OL
id|min_free_pages
)paren
(brace
id|try_to_free_page
c_func
(paren
id|GFP_KERNEL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|nr_free_pages
op_plus
id|atomic_read
c_func
(paren
op_amp
id|nr_async_pages
)paren
)paren
OL
id|free_pages_low
)paren
(brace
id|try_to_free_page
c_func
(paren
id|GFP_KERNEL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|nr_free_pages
op_plus
id|atomic_read
c_func
(paren
op_amp
id|nr_async_pages
)paren
)paren
OL
id|free_pages_high
)paren
(brace
id|try_to_free_page
c_func
(paren
id|GFP_KERNEL
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* &n; * The swap_tick function gets called on every clock tick.&n; */
DECL|function|swap_tick
r_void
id|swap_tick
c_func
(paren
r_void
)paren
(brace
r_int
id|want_wakeup
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|last_wakeup_low
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nr_free_pages
op_plus
id|atomic_read
c_func
(paren
op_amp
id|nr_async_pages
)paren
)paren
OL
id|free_pages_low
)paren
(brace
r_if
c_cond
(paren
id|last_wakeup_low
)paren
id|want_wakeup
op_assign
id|jiffies
op_ge
id|next_swap_jiffies
suffix:semicolon
r_else
id|last_wakeup_low
op_assign
id|want_wakeup
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
(paren
id|nr_free_pages
op_plus
id|atomic_read
c_func
(paren
op_amp
id|nr_async_pages
)paren
)paren
OL
id|free_pages_high
)paren
op_logical_and
id|jiffies
op_ge
id|next_swap_jiffies
)paren
(brace
id|last_wakeup_low
op_assign
l_int|0
suffix:semicolon
id|want_wakeup
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|want_wakeup
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|kswapd_awake
)paren
(brace
id|wake_up
c_func
(paren
op_amp
id|kswapd_wait
)paren
suffix:semicolon
id|need_resched
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* low on memory, we need to start swapping soon */
r_if
c_cond
(paren
id|last_wakeup_low
)paren
(brace
id|next_swap_jiffies
op_assign
id|jiffies
suffix:semicolon
)brace
r_else
id|next_swap_jiffies
op_assign
id|jiffies
op_plus
id|swapout_interval
suffix:semicolon
)brace
id|timer_active
op_or_assign
(paren
l_int|1
op_lshift
id|SWAP_TIMER
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * Initialise the swap timer&n; */
DECL|function|init_swap_timer
r_void
id|init_swap_timer
c_func
(paren
r_void
)paren
(brace
id|timer_table
(braket
id|SWAP_TIMER
)braket
dot
id|expires
op_assign
l_int|0
suffix:semicolon
id|timer_table
(braket
id|SWAP_TIMER
)braket
dot
id|fn
op_assign
id|swap_tick
suffix:semicolon
id|timer_active
op_or_assign
(paren
l_int|1
op_lshift
id|SWAP_TIMER
)paren
suffix:semicolon
)brace
eof
