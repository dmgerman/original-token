multiline_comment|/*&n; *  linux/mm/vmscan.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  Swap reorganised 29.12.95, Stephen Tweedie.&n; *  kswapd added: 7.1.96  sct&n; *  Removed kswapd_ctl limits, and swap out as many pages as needed&n; *  to bring the system back to freepages.high: 2.4.97, Rik van Riel.&n; *  Version: $Id: vmscan.c,v 1.5 1998/02/23 22:14:28 sct Exp $&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/swapctl.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/dcache.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/* &n; * When are we next due for a page scan? &n; */
DECL|variable|next_swap_jiffies
r_static
r_int
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
r_struct
id|wait_queue
op_star
id|kswapd_wait
op_assign
l_int|NULL
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
id|gfp_mask
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
id|page_map
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* &n;&t; * Deal with page aging.  There are several special cases to&n;&t; * consider:&n;&t; * &n;&t; * Page has been accessed, but is swap cached.  If the page is&n;&t; * getting sufficiently &quot;interesting&quot; --- its age is getting&n;&t; * high --- then if we are sufficiently short of free swap&n;&t; * pages, then delete the swap cache.  We can only do this if&n;&t; * the swap page&squot;s reference count is one: ie. there are no&n;&t; * other references to it beyond the swap cache (as there must&n;&t; * still be PTEs pointing to it if count &gt; 1).&n;&t; * &n;&t; * If the page has NOT been touched, and its age reaches zero,&n;&t; * then we are swapping it out:&n;&t; *&n;&t; *   If there is already a swap cache page for this page, then&n;&t; *   another process has already allocated swap space, so just&n;&t; *   dereference the physical page and copy in the swap entry&n;&t; *   from the swap cache.  &n;&t; * &n;&t; * Note, we rely on all pages read in from swap either having&n;&t; * the swap cache flag set, OR being marked writable in the pte,&n;&t; * but NEVER BOTH.  (It IS legal to be neither cached nor dirty,&n;&t; * however.)&n;&t; *&n;&t; * -- Stephen Tweedie 1998 */
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|page_map
)paren
)paren
(brace
r_if
c_cond
(paren
id|pte_write
c_func
(paren
id|pte
)paren
)paren
(brace
r_struct
id|page
op_star
id|found
suffix:semicolon
id|printk
(paren
l_string|&quot;VM: Found a writable swap-cached page!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Try to diagnose the problem ... */
id|found
op_assign
id|find_page
c_func
(paren
op_amp
id|swapper_inode
comma
id|page_map-&gt;offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;page=%p@%08lx, found=%p, count=%d&bslash;n&quot;
comma
id|page_map
comma
id|page_map-&gt;offset
comma
id|found
comma
id|atomic_read
c_func
(paren
op_amp
id|found-&gt;count
)paren
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|found
)paren
suffix:semicolon
)brace
r_else
id|printk
(paren
l_string|&quot;Spurious, page not in cache&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
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
multiline_comment|/* &n;&t;&t; * We should test here to see if we want to recover any&n;&t;&t; * swap cache page here.  We do this if the page seeing&n;&t;&t; * enough activity, AND we are sufficiently low on swap&n;&t;&t; *&n;&t;&t; * We need to track both the number of available swap&n;&t;&t; * pages and the total number present before we can do&n;&t;&t; * this...  &n;&t;&t; */
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
multiline_comment|/*&n;&t;&t;&t; * This is a dirty, swappable page.  First of all,&n;&t;&t;&t; * get a suitable swap entry for it, and make sure&n;&t;&t;&t; * we have the swap cache set up to associate the&n;&t;&t;&t; * page with that swap entry.&n;&t;&t;&t; */
id|entry
op_assign
id|in_swap_cache
c_func
(paren
id|page_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
(brace
id|entry
op_assign
id|get_swap_page
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* No swap space left */
)brace
id|vma-&gt;vm_mm-&gt;rss
op_decrement
suffix:semicolon
id|tsk-&gt;nswap
op_increment
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
id|swap_duplicate
c_func
(paren
id|entry
)paren
suffix:semicolon
multiline_comment|/* Now to write back the page.  We have two&n;&t;&t;&t; * cases: if the page is already part of the&n;&t;&t;&t; * swap cache, then it is already on disk.  Just&n;&t;&t;&t; * free the page and return (we release the swap&n;&t;&t;&t; * cache on the last accessor too).&n;&t;&t;&t; *&n;&t;&t;&t; * If we have made a new swap entry, then we&n;&t;&t;&t; * start the write out to disk.  If the page is&n;&t;&t;&t; * shared, however, we still need to keep the&n;&t;&t;&t; * copy in memory, so we add it to the swap&n;&t;&t;&t; * cache. */
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|page_map
)paren
)paren
(brace
id|free_page_and_swap_cache
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
(paren
id|atomic_read
c_func
(paren
op_amp
id|page_map-&gt;count
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
id|add_to_swap_cache
c_func
(paren
id|page_map
comma
id|entry
)paren
suffix:semicolon
multiline_comment|/* We checked we were unlocked way up above, and we&n;&t;&t;&t;   have been careful not to stall until here */
id|set_bit
c_func
(paren
id|PG_locked
comma
op_amp
id|page_map-&gt;flags
)paren
suffix:semicolon
multiline_comment|/* OK, do a physical write to swap.  */
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
(paren
id|gfp_mask
op_amp
id|__GFP_WAIT
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Now we can free the current physical page.  We also&n;&t;&t; * free up the swap cache if this is the last use of the&n;&t;&t; * page.  Note that there is a race here: the page may&n;&t;&t; * still be shared COW by another process, but that&n;&t;&t; * process may exit while we are writing out the page&n;&t;&t; * asynchronously.  That&squot;s no problem, shrink_mmap() can&n;&t;&t; * correctly clean up the occassional unshared page&n;&t;&t; * which gets left behind in the swap cache. */
id|free_page_and_swap_cache
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
multiline_comment|/* The page was _not_ dirty, but still has a zero age.  It must&n;&t; * already be uptodate on disk.  If it is in the swap cache,&n;&t; * then we can just unlink the page now.  Remove the swap cache&n;&t; * too if this is the last user.  */
r_if
c_cond
(paren
(paren
id|entry
op_assign
id|in_swap_cache
c_func
(paren
id|page_map
)paren
)paren
)paren
(brace
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
id|swap_duplicate
c_func
(paren
id|entry
)paren
suffix:semicolon
id|free_page_and_swap_cache
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
(paren
id|atomic_read
c_func
(paren
op_amp
id|page_map-&gt;count
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * A clean page to be discarded?  Must be mmap()ed from&n;&t; * somewhere.  Unlink the pte, and tell the filemap code to&n;&t; * discard any cached backing page if this is the last user.&n;&t; */
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|page_map
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;VM: How can this page _still_ be cached?&quot;
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
id|page_map
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|page_map
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
id|gfp_mask
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
id|p-&gt;swap_address
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
(brace
id|p-&gt;swap_address
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|p-&gt;swap_address
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
comma
op_star
id|pbest
suffix:semicolon
r_int
id|counter
comma
id|assign
comma
id|max_cnt
suffix:semicolon
multiline_comment|/* &n;&t; * We make one or two passes through the task list, indexed by &n;&t; * assign = {0, 1}:&n;&t; *   Pass 1: select the swappable task with maximal swap_cnt.&n;&t; *   Pass 2: assign new swap_cnt values, then select as above.&n;&t; * With this approach, there&squot;s no need to remember the last task&n;&t; * swapped out.  If the swap-out fails, we clear swap_cnt so the &n;&t; * task won&squot;t be selected again until all others have been tried.&n;&t; */
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
id|assign
op_assign
l_int|0
suffix:semicolon
id|max_cnt
op_assign
l_int|0
suffix:semicolon
id|pbest
op_assign
l_int|NULL
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
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;swappable
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;mm-&gt;rss
op_le
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|assign
)paren
(brace
multiline_comment|/* &n;&t;&t;&t;&t; * If we didn&squot;t select a task on pass 1, &n;&t;&t;&t;&t; * assign each task a new swap_cnt.&n;&t;&t;&t;&t; * Normalise the number of pages swapped&n;&t;&t;&t;&t; * by multiplying by (RSS / 1MB)&n;&t;&t;&t;&t; */
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
id|p-&gt;swap_cnt
OG
id|max_cnt
)paren
(brace
id|max_cnt
op_assign
id|p-&gt;swap_cnt
suffix:semicolon
id|pbest
op_assign
id|p
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
id|pbest
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
id|pbest-&gt;swap_cnt
op_decrement
suffix:semicolon
r_switch
c_cond
(paren
id|swap_out_process
c_func
(paren
id|pbest
comma
id|gfp_mask
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Clear swap_cnt so we don&squot;t look at this task&n;&t;&t;&t; * again until we&squot;ve tried all of the others.&n;&t;&t;&t; * (We didn&squot;t block, so the task is still here.)&n;&t;&t;&t; */
id|pbest-&gt;swap_cnt
op_assign
l_int|0
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
suffix:semicolon
)brace
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We are much more aggressive about trying to swap out than we used&n; * to be.  This works out OK, because we now do proper aging on page&n; * contents. &n; */
DECL|function|do_try_to_free_page
r_static
r_int
id|do_try_to_free_page
c_func
(paren
r_int
id|gfp_mask
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
multiline_comment|/* Always trim SLAB caches when memory gets low. */
id|kmem_cache_reap
c_func
(paren
id|gfp_mask
)paren
suffix:semicolon
multiline_comment|/* We try harder if we are waiting .. */
id|stop
op_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|gfp_mask
op_amp
id|__GFP_WAIT
)paren
id|stop
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|buffermem
op_rshift
id|PAGE_SHIFT
)paren
op_star
l_int|100
OG
id|buffer_mem.borrow_percent
op_star
id|num_physpages
)paren
op_logical_or
(paren
id|page_cache_size
op_star
l_int|100
OG
id|page_cache.borrow_percent
op_star
id|num_physpages
)paren
)paren
id|shrink_mmap
c_func
(paren
id|i
comma
id|gfp_mask
)paren
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
id|gfp_mask
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
id|shm_swap
c_func
(paren
id|i
comma
id|gfp_mask
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
id|swap_out
c_func
(paren
id|i
comma
id|gfp_mask
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|state
op_assign
l_int|3
suffix:semicolon
r_case
l_int|3
suffix:colon
id|shrink_dcache_memory
c_func
(paren
id|i
comma
id|gfp_mask
)paren
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
multiline_comment|/*&n; * Before we start the kernel thread, print out the &n; * kswapd initialization message (otherwise the init message &n; * may be printed in the middle of another driver&squot;s init &n; * message).  It looks very bad when that happens.&n; */
DECL|function|kswapd_setup
r_void
id|kswapd_setup
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|revision
op_assign
l_string|&quot;$Revision: 1.5 $&quot;
comma
op_star
id|s
comma
op_star
id|e
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
l_string|&quot;Starting kswapd v%.*s&bslash;n&quot;
comma
id|i
comma
id|s
)paren
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
r_struct
id|wait_queue
id|wait
op_assign
(brace
id|current
comma
l_int|NULL
)brace
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
id|sigfillset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
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
id|current-&gt;rt_priority
op_assign
l_int|32
suffix:semicolon
multiline_comment|/* Fixme --- we need to standardise our&n;&t;&t;&t;&t;    namings for POSIX.4 realtime scheduling&n;&t;&t;&t;&t;    priorities.  */
id|init_swap_timer
c_func
(paren
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|kswapd_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|tries
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|flush_signals
c_func
(paren
id|current
)paren
suffix:semicolon
id|run_task_queue
c_func
(paren
op_amp
id|tq_disk
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|swapstats.wakeups
op_increment
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Do the background pageout: be&n;&t;&t; * more aggressive if we&squot;re really&n;&t;&t; * low on free memory.&n;&t;&t; *&n;&t;&t; * We try page_daemon.tries_base times, divided by&n;&t;&t; * an &squot;urgency factor&squot;. In practice this will mean&n;&t;&t; * a value of pager_daemon.tries_base / 8 or 4 = 64&n;&t;&t; * or 128 pages at a time.&n;&t;&t; * This gives us 64 (or 128) * 4k * 4 (times/sec) =&n;&t;&t; * 1 (or 2) MB/s swapping bandwidth in low-priority&n;&t;&t; * background paging. This number rises to 8 MB/s&n;&t;&t; * when the priority is highest (but then we&squot;ll be&n;&t;&t; * woken up more often and the rate will be even&n;&t;&t; * higher).&n;&t;&t; */
id|tries
op_assign
id|pager_daemon.tries_base
suffix:semicolon
id|tries
op_rshift_assign
l_int|4
op_star
id|free_memory_available
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|do_try_to_free_page
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Syncing large chunks is faster than swapping&n;&t;&t;&t; * synchronously (less head movement). -- Rik.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|nr_async_pages
)paren
op_ge
id|pager_daemon.swap_cluster
)paren
id|run_task_queue
c_func
(paren
op_amp
id|tq_disk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_memory_available
c_func
(paren
)paren
OG
l_int|1
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|tries
OG
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* As if we could ever get here - maybe we want to make this killable */
id|remove_wait_queue
c_func
(paren
op_amp
id|kswapd_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We need to make the locks finer granularity, but right&n; * now we need this so that we can do page allocations&n; * without holding the kernel lock etc.&n; *&n; * The &quot;PF_MEMALLOC&quot; flag protects us against recursion:&n; * if we need more memory as part of a swap-out effort we&n; * will just silently return &quot;success&quot; to tell the page&n; * allocator to accept the allocation.&n; */
DECL|function|try_to_free_pages
r_int
id|try_to_free_pages
c_func
(paren
r_int
r_int
id|gfp_mask
comma
r_int
id|count
)paren
(brace
r_int
id|retval
op_assign
l_int|1
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_MEMALLOC
)paren
(brace
id|current-&gt;flags
op_or_assign
id|PF_MEMALLOC
suffix:semicolon
r_do
(brace
id|retval
op_assign
id|do_try_to_free_page
c_func
(paren
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
r_break
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
suffix:semicolon
id|current-&gt;flags
op_and_assign
id|PF_MEMALLOC
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
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
r_int
id|now
comma
id|want
suffix:semicolon
r_int
id|want_wakeup
op_assign
l_int|0
suffix:semicolon
id|want
op_assign
id|next_swap_jiffies
suffix:semicolon
id|now
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/*&n;&t; * Examine the memory queues. Mark memory low&n;&t; * if there is nothing available in the three&n;&t; * highest queues.&n;&t; *&n;&t; * Schedule for wakeup if there isn&squot;t lots&n;&t; * of free memory.&n;&t; */
r_switch
c_cond
(paren
id|free_memory_available
c_func
(paren
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
id|want
op_assign
id|now
suffix:semicolon
multiline_comment|/* Fall through */
r_case
l_int|1
suffix:colon
id|want_wakeup
op_assign
l_int|1
suffix:semicolon
r_default
suffix:colon
(brace
)brace
)brace
r_if
c_cond
(paren
(paren
r_int
)paren
(paren
id|now
op_minus
id|want
)paren
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|want_wakeup
op_logical_or
(paren
id|num_physpages
op_star
id|buffer_mem.max_percent
)paren
OL
(paren
id|buffermem
op_rshift
id|PAGE_SHIFT
)paren
op_star
l_int|100
op_logical_or
(paren
id|num_physpages
op_star
id|page_cache.max_percent
OL
id|page_cache_size
op_star
l_int|100
)paren
)paren
(brace
multiline_comment|/* Set the next wake-up time */
id|next_swap_jiffies
op_assign
id|now
op_plus
id|swapout_interval
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|kswapd_wait
)paren
suffix:semicolon
)brace
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
