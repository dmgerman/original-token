multiline_comment|/*&n; *  linux/mm/swap_state.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *  Swap reorganised 29.12.95, Stephen Tweedie&n; *&n; *  Rewritten to use page cache, (C) 1998 Stephen Tweedie&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/swapctl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|variable|swapper_space
r_struct
id|address_space
id|swapper_space
op_assign
(brace
(brace
multiline_comment|/* pages&t;*/
op_amp
id|swapper_space.pages
comma
multiline_comment|/*        .next */
op_amp
id|swapper_space.pages
multiline_comment|/*&t;  .prev */
)brace
comma
l_int|0
multiline_comment|/* nrpages&t;*/
)brace
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
DECL|variable|swap_cache_add_total
r_int
r_int
id|swap_cache_add_total
op_assign
l_int|0
suffix:semicolon
DECL|variable|swap_cache_del_total
r_int
r_int
id|swap_cache_del_total
op_assign
l_int|0
suffix:semicolon
DECL|variable|swap_cache_find_total
r_int
r_int
id|swap_cache_find_total
op_assign
l_int|0
suffix:semicolon
DECL|variable|swap_cache_find_success
r_int
r_int
id|swap_cache_find_success
op_assign
l_int|0
suffix:semicolon
DECL|function|show_swap_cache_info
r_void
id|show_swap_cache_info
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Swap cache: add %ld, delete %ld, find %ld/%ld&bslash;n&quot;
comma
id|swap_cache_add_total
comma
id|swap_cache_del_total
comma
id|swap_cache_find_success
comma
id|swap_cache_find_total
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|add_to_swap_cache
r_void
id|add_to_swap_cache
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|swp_entry_t
id|entry
)paren
(brace
macro_line|#ifdef SWAP_CACHE_INFO
id|swap_cache_add_total
op_increment
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|PageTestandSetSwapCache
c_func
(paren
id|page
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;mapping
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|add_to_page_cache
c_func
(paren
id|page
comma
op_amp
id|swapper_space
comma
id|entry.val
)paren
suffix:semicolon
)brace
DECL|function|remove_from_swap_cache
r_static
r_inline
r_void
id|remove_from_swap_cache
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
r_if
c_cond
(paren
id|mapping
op_ne
op_amp
id|swapper_space
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageSwapCache
c_func
(paren
id|page
)paren
op_logical_or
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
id|PAGE_BUG
c_func
(paren
id|page
)paren
suffix:semicolon
id|PageClearSwapCache
c_func
(paren
id|page
)paren
suffix:semicolon
id|remove_inode_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This must be called only on pages that have&n; * been verified to be in the swap cache.&n; */
DECL|function|__delete_from_swap_cache
r_void
id|__delete_from_swap_cache
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|swp_entry_t
id|entry
suffix:semicolon
id|entry.val
op_assign
id|page-&gt;index
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
id|swap_cache_del_total
op_increment
suffix:semicolon
macro_line|#endif
id|remove_from_swap_cache
c_func
(paren
id|page
)paren
suffix:semicolon
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This will never put the page into the free list, the caller has&n; * a reference on the page.&n; */
DECL|function|delete_from_swap_cache_nolock
r_void
id|delete_from_swap_cache_nolock
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block_flushpage
c_func
(paren
id|page
comma
l_int|0
)paren
)paren
id|lru_cache_del
c_func
(paren
id|page
)paren
suffix:semicolon
id|__delete_from_swap_cache
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This must be called only on pages that have&n; * been verified to be in the swap cache and locked.&n; */
DECL|function|delete_from_swap_cache
r_void
id|delete_from_swap_cache
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|delete_from_swap_cache_nolock
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * Perform a free_page(), also freeing any swap cache associated with&n; * this page if it is the last user of the page. Can not do a lock_page,&n; * as we are holding the page_table_lock spinlock.&n; */
DECL|function|free_page_and_swap_cache
r_void
id|free_page_and_swap_cache
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
multiline_comment|/* &n;&t; * If we are the only user, then try to free up the swap cache. &n;&t; */
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|page
)paren
op_logical_and
op_logical_neg
id|TryLockPage
c_func
(paren
id|page
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_page_shared
c_func
(paren
id|page
)paren
)paren
(brace
id|delete_from_swap_cache_nolock
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|ClearPageSwapEntry
c_func
(paren
id|page
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Lookup a swap entry in the swap cache. A found page will be returned&n; * unlocked and with its refcount incremented - we rely on the kernel&n; * lock getting page table operations atomic even if we drop the page&n; * lock before returning.&n; */
DECL|function|lookup_swap_cache
r_struct
id|page
op_star
id|lookup_swap_cache
c_func
(paren
id|swp_entry_t
id|entry
)paren
(brace
r_struct
id|page
op_star
id|found
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
id|swap_cache_find_total
op_increment
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t; * Right now the pagecache is 32-bit only.  But it&squot;s a 32 bit index. =)&n;&t;&t; */
id|repeat
suffix:colon
id|found
op_assign
id|find_lock_page
c_func
(paren
op_amp
id|swapper_space
comma
id|entry.val
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Though the &quot;found&quot; page was in the swap cache an instant&n;&t;&t; * earlier, it might have been removed by shrink_mmap etc.&n;&t;&t; * Re search ... Since find_lock_page grabs a reference on&n;&t;&t; * the page, it can not be reused for anything else, namely&n;&t;&t; * it can not be associated with another swaphandle, so it&n;&t;&t; * is enough to check whether the page is still in the scache.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|PageSwapCache
c_func
(paren
id|found
)paren
)paren
(brace
id|UnlockPage
c_func
(paren
id|found
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|found
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found-&gt;mapping
op_ne
op_amp
id|swapper_space
)paren
r_goto
id|out_bad
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
id|swap_cache_find_success
op_increment
suffix:semicolon
macro_line|#endif
id|UnlockPage
c_func
(paren
id|found
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
id|out_bad
suffix:colon
id|printk
(paren
id|KERN_ERR
l_string|&quot;VM: Found a non-swapper swap page!&bslash;n&quot;
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|found
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|found
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * Locate a page of swap in physical memory, reserving swap cache space&n; * and reading the disk if it is not already cached.  If wait==0, we are&n; * only doing readahead, so don&squot;t worry if the page is already locked.&n; *&n; * A failure return means that either the page allocation failed or that&n; * the swap entry is no longer in use.&n; */
DECL|function|read_swap_cache_async
r_struct
id|page
op_star
id|read_swap_cache_async
c_func
(paren
id|swp_entry_t
id|entry
comma
r_int
id|wait
)paren
(brace
r_struct
id|page
op_star
id|found_page
op_assign
l_int|0
comma
op_star
id|new_page
suffix:semicolon
r_int
r_int
id|new_page_addr
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure the swap entry is still in use.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|swap_duplicate
c_func
(paren
id|entry
)paren
)paren
multiline_comment|/* Account for the swap cache */
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Look for the page in the swap cache.&n;&t; */
id|found_page
op_assign
id|lookup_swap_cache
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found_page
)paren
r_goto
id|out_free_swap
suffix:semicolon
id|new_page_addr
op_assign
id|__get_free_page
c_func
(paren
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_page_addr
)paren
r_goto
id|out_free_swap
suffix:semicolon
multiline_comment|/* Out of memory */
id|new_page
op_assign
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|new_page_addr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check the swap cache again, in case we stalled above.&n;&t; */
id|found_page
op_assign
id|lookup_swap_cache
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found_page
)paren
r_goto
id|out_free_page
suffix:semicolon
multiline_comment|/* &n;&t; * Add it to the swap cache and read its contents.&n;&t; */
id|add_to_swap_cache
c_func
(paren
id|new_page
comma
id|entry
)paren
suffix:semicolon
id|rw_swap_page
c_func
(paren
id|READ
comma
id|new_page
comma
id|wait
)paren
suffix:semicolon
r_return
id|new_page
suffix:semicolon
id|out_free_page
suffix:colon
id|__free_page
c_func
(paren
id|new_page
)paren
suffix:semicolon
id|out_free_swap
suffix:colon
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|found_page
suffix:semicolon
)brace
eof
