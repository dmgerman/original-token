multiline_comment|/*&n; *  linux/mm/vmscan.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  Swap reorganised 29.12.95, Stephen Tweedie.&n; *  kswapd added: 7.1.96  sct&n; *  Removed kswapd_ctl limits, and swap out as many pages as needed&n; *  to bring the system back to freepages.high: 2.4.97, Rik van Riel.&n; *  Version: $Id: vmscan.c,v 1.5 1998/02/23 22:14:28 sct Exp $&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/swapctl.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*&n; * The swap-out functions return 1 if they successfully&n; * threw something out, and we got a free page. It returns&n; * zero if it couldn&squot;t do anything, and any other value&n; * indicates it decreased rss, but the page was shared.&n; *&n; * NOTE! If it sleeps, it *must* return 1 to make sure we&n; * don&squot;t continue with the swap-out. Otherwise we may be&n; * using a process that no longer actually exists (it might&n; * have died while we slept).&n; */
DECL|function|try_to_swap_out
r_static
r_int
id|try_to_swap_out
c_func
(paren
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
id|gfp_mask
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|swp_entry_t
id|entry
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
(paren
op_star
id|swapout
)paren
(paren
r_struct
id|page
op_star
comma
r_struct
id|file
op_star
)paren
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
r_goto
id|out_failed
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
id|page
op_minus
id|mem_map
op_ge
id|max_mapnr
)paren
r_goto
id|out_failed
suffix:semicolon
multiline_comment|/* Don&squot;t look at this pte if it&squot;s been accessed recently. */
r_if
c_cond
(paren
id|pte_young
c_func
(paren
id|pte
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Transfer the &quot;accessed&quot; bit from the page&n;&t;&t; * tables to the global page map.&n;&t;&t; */
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
id|set_bit
c_func
(paren
id|PG_referenced
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
r_goto
id|out_failed
suffix:semicolon
)brace
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|page
)paren
op_logical_or
id|PageLocked
c_func
(paren
id|page
)paren
op_logical_or
(paren
(paren
id|gfp_mask
op_amp
id|__GFP_DMA
)paren
op_logical_and
op_logical_neg
id|PageDMA
c_func
(paren
id|page
)paren
)paren
op_logical_or
(paren
op_logical_neg
(paren
id|gfp_mask
op_amp
id|__GFP_HIGHMEM
)paren
op_logical_and
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
)paren
r_goto
id|out_failed
suffix:semicolon
multiline_comment|/*&n;&t; * Is the page already in the swap cache? If so, then&n;&t; * we can just drop our reference to it without doing&n;&t; * any IO - it&squot;s already up-to-date on disk.&n;&t; *&n;&t; * Return 0, as we didn&squot;t actually free any real&n;&t; * memory, and we should just continue our scan.&n;&t; */
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|page
)paren
)paren
(brace
id|entry.val
op_assign
id|page-&gt;pg_offset
suffix:semicolon
id|swap_duplicate
c_func
(paren
id|entry
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|page_table
comma
id|swp_entry_to_pte
c_func
(paren
id|entry
)paren
)paren
suffix:semicolon
id|drop_pte
suffix:colon
id|vma-&gt;vm_mm-&gt;rss
op_decrement
suffix:semicolon
id|flush_tlb_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|out_failed
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Is it a clean page? Then it must be recoverable&n;&t; * by just paging it in again, and we can just drop&n;&t; * it..&n;&t; *&n;&t; * However, this won&squot;t actually free any real&n;&t; * memory, as the page will just be in the page cache&n;&t; * somewhere, and as such we should just continue&n;&t; * our scan.&n;&t; *&n;&t; * Basically, this just makes it possible for us to do&n;&t; * some real work in the future in &quot;shrink_mmap()&quot;.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|pte_dirty
c_func
(paren
id|pte
)paren
)paren
(brace
id|pte_clear
c_func
(paren
id|page_table
)paren
suffix:semicolon
r_goto
id|drop_pte
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Don&squot;t go down into the swap-out stuff if&n;&t; * we cannot do I/O! Avoid recursing on FS&n;&t; * locks etc.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|gfp_mask
op_amp
id|__GFP_IO
)paren
)paren
r_goto
id|out_failed
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, it&squot;s really dirty. That means that&n;&t; * we should either create a new swap cache&n;&t; * entry for it, or we should write it back&n;&t; * to its own backing store.&n;&t; *&n;&t; * Note that in neither case do we actually&n;&t; * know that we make a page available, but&n;&t; * as we potentially sleep we can no longer&n;&t; * continue scanning, so we migth as well&n;&t; * assume we free&squot;d something.&n;&t; *&n;&t; * NOTE NOTE NOTE! This should just set a&n;&t; * dirty bit in &squot;page&squot;, and just drop the&n;&t; * pte. All the hard work would be done by&n;&t; * shrink_mmap().&n;&t; *&n;&t; * That would get rid of a lot of problems.&n;&t; */
id|flush_cache_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_ops
op_logical_and
(paren
id|swapout
op_assign
id|vma-&gt;vm_ops-&gt;swapout
)paren
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
id|vma-&gt;vm_file
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
id|get_file
c_func
(paren
id|file
)paren
suffix:semicolon
id|pte_clear
c_func
(paren
id|page_table
)paren
suffix:semicolon
id|vma-&gt;vm_mm-&gt;rss
op_decrement
suffix:semicolon
id|flush_tlb_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
id|vmlist_access_unlock
c_func
(paren
id|vma-&gt;vm_mm
)paren
suffix:semicolon
id|error
op_assign
id|swapout
c_func
(paren
id|page
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
r_goto
id|out_free_success
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This is a dirty, swappable page.  First of all,&n;&t; * get a suitable swap entry for it, and make sure&n;&t; * we have the swap cache set up to associate the&n;&t; * page with that swap entry.&n;&t; */
id|entry
op_assign
id|acquire_swap_entry
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry.val
)paren
r_goto
id|out_failed
suffix:semicolon
multiline_comment|/* No swap space left */
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
id|prepare_highmem_swapout
c_func
(paren
id|page
)paren
)paren
)paren
r_goto
id|out_swap_free
suffix:semicolon
id|vma-&gt;vm_mm-&gt;rss
op_decrement
suffix:semicolon
id|set_pte
c_func
(paren
id|page_table
comma
id|swp_entry_to_pte
c_func
(paren
id|entry
)paren
)paren
suffix:semicolon
id|vmlist_access_unlock
c_func
(paren
id|vma-&gt;vm_mm
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
id|swap_duplicate
c_func
(paren
id|entry
)paren
suffix:semicolon
multiline_comment|/* One for the process, one for the swap cache */
multiline_comment|/* This will also lock the page */
id|add_to_swap_cache
c_func
(paren
id|page
comma
id|entry
)paren
suffix:semicolon
multiline_comment|/* OK, do a physical asynchronous write to swap.  */
id|rw_swap_page
c_func
(paren
id|WRITE
comma
id|page
comma
l_int|0
)paren
suffix:semicolon
id|out_free_success
suffix:colon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|out_swap_free
suffix:colon
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
id|out_failed
suffix:colon
r_return
l_int|0
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
id|gfp_mask
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
id|pmd_ERROR
c_func
(paren
op_star
id|dir
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
id|vma-&gt;vm_mm-&gt;swap_address
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
id|vma
comma
id|address
comma
id|pte
comma
id|gfp_mask
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
op_logical_and
(paren
id|address
OL
id|end
)paren
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
id|gfp_mask
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
id|pgd_ERROR
c_func
(paren
op_star
id|dir
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
id|pgd_end
op_logical_and
(paren
id|end
OG
id|pgd_end
)paren
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
id|vma
comma
id|pmd
comma
id|address
comma
id|end
comma
id|gfp_mask
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
op_logical_and
(paren
id|address
OL
id|end
)paren
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
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|gfp_mask
)paren
(brace
id|pgd_t
op_star
id|pgdir
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
multiline_comment|/* Don&squot;t swap out areas which are locked down */
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_LOCKED
)paren
r_return
l_int|0
suffix:semicolon
id|pgdir
op_assign
id|pgd_offset
c_func
(paren
id|vma-&gt;vm_mm
comma
id|address
)paren
suffix:semicolon
id|end
op_assign
id|vma-&gt;vm_end
suffix:semicolon
r_if
c_cond
(paren
id|address
op_ge
id|end
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
r_int
id|result
op_assign
id|swap_out_pgd
c_func
(paren
id|vma
comma
id|pgdir
comma
id|address
comma
id|end
comma
id|gfp_mask
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
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
id|pgdir
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
op_logical_and
(paren
id|address
OL
id|end
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|swap_out_mm
r_static
r_int
id|swap_out_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
id|gfp_mask
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
id|mm-&gt;swap_address
suffix:semicolon
multiline_comment|/*&n;&t; * Find the proper vm-area after freezing the vma chain &n;&t; * and ptes.&n;&t; */
id|vmlist_access_lock
c_func
(paren
id|mm
)paren
suffix:semicolon
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma
)paren
(brace
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
id|vma
comma
id|address
comma
id|gfp_mask
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
)brace
id|vmlist_access_unlock
c_func
(paren
id|mm
)paren
suffix:semicolon
multiline_comment|/* We didn&squot;t find anything for the process */
id|mm-&gt;swap_cnt
op_assign
l_int|0
suffix:semicolon
id|mm-&gt;swap_address
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Select the task with maximal swap_cnt and try to swap out a page.&n; * N.B. This function returns only 0 or 1.  Return values != 1 from&n; * the lower level routines result in continued processing.&n; */
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
id|gfp_mask
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|counter
suffix:semicolon
r_int
id|__ret
op_assign
l_int|0
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * We make one or two passes through the task list, indexed by &n;&t; * assign = {0, 1}:&n;&t; *   Pass 1: select the swappable task with maximal RSS that has&n;&t; *         not yet been swapped out. &n;&t; *   Pass 2: re-assign rss swap_cnt values, then select as above.&n;&t; *&n;&t; * With this approach, there&squot;s no need to remember the last task&n;&t; * swapped out.  If the swap-out fails, we clear swap_cnt so the &n;&t; * task won&squot;t be selected again until all others have been tried.&n;&t; *&n;&t; * Think of swap_cnt as a &quot;shadow rss&quot; - it tells us which process&n;&t; * we want to page out (always try largest first).&n;&t; */
id|counter
op_assign
id|nr_threads
op_div
(paren
id|priority
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|counter
OL
l_int|1
)paren
id|counter
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|counter
OG
id|nr_threads
)paren
id|counter
op_assign
id|nr_threads
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
r_int
id|assign
op_assign
l_int|0
suffix:semicolon
r_int
id|max_cnt
op_assign
l_int|0
suffix:semicolon
r_struct
id|mm_struct
op_star
id|best
op_assign
l_int|NULL
suffix:semicolon
r_int
id|pid
op_assign
l_int|0
suffix:semicolon
id|select
suffix:colon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|p
op_assign
id|init_task.next_task
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|p
op_ne
op_amp
id|init_task
suffix:semicolon
id|p
op_assign
id|p-&gt;next_task
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|p-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;swappable
op_logical_or
op_logical_neg
id|mm
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|mm-&gt;rss
op_le
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/* Refresh swap_cnt? */
r_if
c_cond
(paren
id|assign
)paren
id|mm-&gt;swap_cnt
op_assign
id|mm-&gt;rss
suffix:semicolon
r_if
c_cond
(paren
id|mm-&gt;swap_cnt
OG
id|max_cnt
)paren
(brace
id|max_cnt
op_assign
id|mm-&gt;swap_cnt
suffix:semicolon
id|best
op_assign
id|mm
suffix:semicolon
id|pid
op_assign
id|p-&gt;pid
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|best
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|assign
)paren
(brace
id|assign
op_assign
l_int|1
suffix:semicolon
r_goto
id|select
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
r_else
(brace
r_int
id|ret
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|best-&gt;mm_count
)paren
suffix:semicolon
id|ret
op_assign
id|swap_out_mm
c_func
(paren
id|best
comma
id|gfp_mask
)paren
suffix:semicolon
id|mmdrop
c_func
(paren
id|best
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
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
id|__ret
op_assign
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|__ret
suffix:semicolon
)brace
multiline_comment|/*&n; * We need to make the locks finer granularity, but right&n; * now we need this so that we can do page allocations&n; * without holding the kernel lock etc.&n; *&n; * We want to try to free &quot;count&quot; pages, and we need to &n; * cluster them so that we get good swap-out behaviour. See&n; * the &quot;free_memory()&quot; macro for details.&n; */
DECL|function|do_try_to_free_pages
r_static
r_int
id|do_try_to_free_pages
c_func
(paren
r_int
r_int
id|gfp_mask
)paren
(brace
r_int
id|priority
suffix:semicolon
r_int
id|count
op_assign
id|SWAP_CLUSTER_MAX
suffix:semicolon
multiline_comment|/* Always trim SLAB caches when memory gets low. */
id|kmem_cache_reap
c_func
(paren
id|gfp_mask
)paren
suffix:semicolon
id|priority
op_assign
l_int|6
suffix:semicolon
r_do
(brace
r_while
c_loop
(paren
id|shrink_mmap
c_func
(paren
id|priority
comma
id|gfp_mask
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|count
)paren
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/* don&squot;t be too light against the d/i cache since&n;&t;&t;   shrink_mmap() almost never fail when there&squot;s&n;&t;&t;   really plenty of memory free. */
id|count
op_sub_assign
id|shrink_dcache_memory
c_func
(paren
id|priority
comma
id|gfp_mask
)paren
suffix:semicolon
id|count
op_sub_assign
id|shrink_icache_memory
c_func
(paren
id|priority
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|0
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* Try to get rid of some shared memory pages.. */
r_if
c_cond
(paren
id|gfp_mask
op_amp
id|__GFP_IO
)paren
(brace
r_while
c_loop
(paren
id|shm_swap
c_func
(paren
id|priority
comma
id|gfp_mask
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|count
)paren
r_goto
id|done
suffix:semicolon
)brace
)brace
multiline_comment|/* Then, try to page stuff out.. */
r_while
c_loop
(paren
id|swap_out
c_func
(paren
id|priority
comma
id|gfp_mask
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|count
)paren
r_goto
id|done
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_decrement
id|priority
op_ge
l_int|0
)paren
suffix:semicolon
id|done
suffix:colon
r_return
id|priority
op_ge
l_int|0
suffix:semicolon
)brace
DECL|variable|kswapd_process
r_static
r_struct
id|task_struct
op_star
id|kswapd_process
suffix:semicolon
multiline_comment|/*&n; * The background pageout daemon, started as a kernel thread&n; * from the init process. &n; *&n; * This basically executes once a second, trickling out pages&n; * so that we have _some_ free memory available even if there&n; * is no other activity that frees anything up. This is needed&n; * for things like routing etc, where we otherwise might have&n; * all activity going on in asynchronous contexts that cannot&n; * page things out.&n; *&n; * If there are applications that are active memory-allocators&n; * (most normal use), this basically shouldn&squot;t matter.&n; */
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
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|kswapd_process
op_assign
id|tsk
suffix:semicolon
id|tsk-&gt;session
op_assign
l_int|1
suffix:semicolon
id|tsk-&gt;pgrp
op_assign
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|tsk-&gt;comm
comma
l_string|&quot;kswapd&quot;
)paren
suffix:semicolon
id|sigfillset
c_func
(paren
op_amp
id|tsk-&gt;blocked
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tell the memory management that we&squot;re a &quot;memory allocator&quot;,&n;&t; * and that if we need more memory we should get access to it&n;&t; * regardless (see &quot;__get_free_pages()&quot;). &quot;kswapd&quot; should&n;&t; * never get caught in the normal page freeing logic.&n;&t; *&n;&t; * (Kswapd normally doesn&squot;t need memory anyway, but sometimes&n;&t; * you need a small amount of memory in order to be able to&n;&t; * page out something else, and this flag essentially protects&n;&t; * us from recursively trying to free more memory as we&squot;re&n;&t; * trying to free the first piece of memory in the first place).&n;&t; */
id|tsk-&gt;flags
op_or_assign
id|PF_MEMALLOC
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t; * Wake up once a second to see if we need to make&n;&t;&t; * more memory available.&n;&t;&t; *&n;&t;&t; * If we actually get into a low-memory situation,&n;&t;&t; * the processes needing more memory will wake us&n;&t;&t; * up on a more timely basis.&n;&t;&t; */
r_do
(brace
multiline_comment|/* kswapd is critical to provide GFP_ATOMIC&n;&t;&t;&t;   allocations (not GFP_HIGHMEM ones). */
r_if
c_cond
(paren
id|nr_free_pages
op_minus
id|nr_free_highpages
op_ge
id|freepages.high
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|do_try_to_free_pages
c_func
(paren
id|GFP_KSWAPD
)paren
)paren
r_break
suffix:semicolon
id|run_task_queue
c_func
(paren
op_amp
id|tq_disk
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|tsk-&gt;need_resched
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Called by non-kswapd processes when they want more&n; * memory.&n; *&n; * In a perfect world, this should just wake up kswapd&n; * and return. We don&squot;t actually want to swap stuff out&n; * from user processes, because the locking issues are&n; * nasty to the extreme (file write locks, and MM locking)&n; *&n; * One option might be to let kswapd do all the page-out&n; * and VM page table scanning that needs locking, and this&n; * process thread could do just the mmap shrink stage that&n; * can be done by just dropping cached pages without having&n; * any deadlock issues.&n; */
DECL|function|try_to_free_pages
r_int
id|try_to_free_pages
c_func
(paren
r_int
r_int
id|gfp_mask
)paren
(brace
r_int
id|retval
op_assign
l_int|1
suffix:semicolon
id|wake_up_process
c_func
(paren
id|kswapd_process
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gfp_mask
op_amp
id|__GFP_WAIT
)paren
id|retval
op_assign
id|do_try_to_free_pages
c_func
(paren
id|gfp_mask
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|kswapd_init
r_static
r_int
id|__init
id|kswapd_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Starting kswapd v1.6&bslash;n&quot;
)paren
suffix:semicolon
id|swap_setup
c_func
(paren
)paren
suffix:semicolon
id|kernel_thread
c_func
(paren
id|kswapd
comma
l_int|NULL
comma
id|CLONE_FS
op_or
id|CLONE_FILES
op_or
id|CLONE_SIGHAND
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|kswapd_init
)paren
eof
