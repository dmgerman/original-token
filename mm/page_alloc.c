multiline_comment|/*&n; *  linux/mm/page_alloc.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *  Swap reorganised 29.12.95, Stephen Tweedie&n; *  Support of BIGMEM added by Gerhard Wichert, Siemens AG, July 1999&n; *  Reshaped it to be a zoned allocator, Ingo Molnar, Red Hat, 1999&n; *  Discontiguous memory support, Kanoj Sarcar, SGI, Nov 1999&n; *  Zone balancing, Kanoj Sarcar, SGI, Jan 2000&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/swapctl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
multiline_comment|/* Use NUMNODES instead of numnodes for better code inside kernel APIs */
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|NUMNODES
mdefine_line|#define NUMNODES 1
macro_line|#else
DECL|macro|NUMNODES
mdefine_line|#define NUMNODES numnodes
macro_line|#endif
DECL|variable|nr_swap_pages
r_int
id|nr_swap_pages
suffix:semicolon
DECL|variable|nr_lru_pages
r_int
id|nr_lru_pages
suffix:semicolon
DECL|variable|pgdat_list
id|pg_data_t
op_star
id|pgdat_list
suffix:semicolon
DECL|variable|zone_names
r_static
r_char
op_star
id|zone_names
(braket
id|MAX_NR_ZONES
)braket
op_assign
(brace
l_string|&quot;DMA&quot;
comma
l_string|&quot;Normal&quot;
comma
l_string|&quot;HighMem&quot;
)brace
suffix:semicolon
DECL|variable|zone_balance_ratio
r_static
r_int
id|zone_balance_ratio
(braket
id|MAX_NR_ZONES
)braket
op_assign
(brace
l_int|128
comma
l_int|128
comma
l_int|128
comma
)brace
suffix:semicolon
DECL|variable|zone_balance_min
r_static
r_int
id|zone_balance_min
(braket
id|MAX_NR_ZONES
)braket
op_assign
(brace
l_int|10
comma
l_int|10
comma
l_int|10
comma
)brace
suffix:semicolon
DECL|variable|zone_balance_max
r_static
r_int
id|zone_balance_max
(braket
id|MAX_NR_ZONES
)braket
op_assign
(brace
l_int|255
comma
l_int|255
comma
l_int|255
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Free_page() adds the page to the free lists. This is optimized for&n; * fast normal cases (no error jumps taken normally).&n; *&n; * The way to optimize jumps for gcc-2.2.2 is to:&n; *  - select the &quot;normal&quot; case and put it inside the if () { XXX }&n; *  - no else-statements if you can avoid them&n; *&n; * With the above two rules, you get a straight-line execution path&n; * for the normal case, giving better asm-code.&n; */
DECL|macro|memlist_init
mdefine_line|#define memlist_init(x) INIT_LIST_HEAD(x)
DECL|macro|memlist_add_head
mdefine_line|#define memlist_add_head list_add
DECL|macro|memlist_add_tail
mdefine_line|#define memlist_add_tail list_add_tail
DECL|macro|memlist_del
mdefine_line|#define memlist_del list_del
DECL|macro|memlist_entry
mdefine_line|#define memlist_entry list_entry
DECL|macro|memlist_next
mdefine_line|#define memlist_next(x) ((x)-&gt;next)
DECL|macro|memlist_prev
mdefine_line|#define memlist_prev(x) ((x)-&gt;prev)
multiline_comment|/*&n; * Temporary debugging check.&n; */
DECL|macro|BAD_RANGE
mdefine_line|#define BAD_RANGE(zone,x) (((zone) != (x)-&gt;zone) || (((x)-mem_map) &lt; (zone)-&gt;offset) || (((x)-mem_map) &gt;= (zone)-&gt;offset+(zone)-&gt;size))
multiline_comment|/*&n; * Buddy system. Hairy. You really aren&squot;t expected to understand this&n; *&n; * Hint: -mask = 1+~mask&n; */
r_static
r_void
id|FASTCALL
c_func
(paren
id|__free_pages_ok
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|order
)paren
)paren
suffix:semicolon
DECL|function|__free_pages_ok
r_static
r_void
id|__free_pages_ok
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|order
)paren
(brace
r_int
r_int
id|index
comma
id|page_idx
comma
id|mask
comma
id|flags
suffix:semicolon
id|free_area_t
op_star
id|area
suffix:semicolon
r_struct
id|page
op_star
id|base
suffix:semicolon
id|zone_t
op_star
id|zone
suffix:semicolon
multiline_comment|/*&n;&t; * Subtle. We do not want to test this in the inlined part of&n;&t; * __free_page() - it&squot;s a rare condition and just increases&n;&t; * cache footprint unnecesserily. So we do an &squot;incorrect&squot;&n;&t; * decrement on page-&gt;count for reserved pages, but this part&n;&t; * makes it safe.&n;&t; */
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|page
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;buffers
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
r_if
c_cond
(paren
id|page
op_minus
id|mem_map
op_ge
id|max_mapnr
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageSwapCache
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
id|PageDecrAfter
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
id|PageDirty
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
id|zone
op_assign
id|page-&gt;zone
suffix:semicolon
id|mask
op_assign
(paren
op_complement
l_int|0UL
)paren
op_lshift
id|order
suffix:semicolon
id|base
op_assign
id|mem_map
op_plus
id|zone-&gt;offset
suffix:semicolon
id|page_idx
op_assign
id|page
op_minus
id|base
suffix:semicolon
r_if
c_cond
(paren
id|page_idx
op_amp
op_complement
id|mask
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|index
op_assign
id|page_idx
op_rshift
(paren
l_int|1
op_plus
id|order
)paren
suffix:semicolon
id|area
op_assign
id|zone-&gt;free_area
op_plus
id|order
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|zone-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|zone-&gt;free_pages
op_sub_assign
id|mask
suffix:semicolon
r_while
c_loop
(paren
id|mask
op_plus
(paren
l_int|1
op_lshift
(paren
id|MAX_ORDER
op_minus
l_int|1
)paren
)paren
)paren
(brace
r_struct
id|page
op_star
id|buddy1
comma
op_star
id|buddy2
suffix:semicolon
r_if
c_cond
(paren
id|area
op_ge
id|zone-&gt;free_area
op_plus
id|MAX_ORDER
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
id|test_and_change_bit
c_func
(paren
id|index
comma
id|area-&gt;map
)paren
)paren
multiline_comment|/*&n;&t;&t;&t; * the buddy page is still allocated.&n;&t;&t;&t; */
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Move the buddy up one level.&n;&t;&t; */
id|buddy1
op_assign
id|base
op_plus
(paren
id|page_idx
op_xor
op_minus
id|mask
)paren
suffix:semicolon
id|buddy2
op_assign
id|base
op_plus
id|page_idx
suffix:semicolon
r_if
c_cond
(paren
id|BAD_RANGE
c_func
(paren
id|zone
comma
id|buddy1
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
id|BAD_RANGE
c_func
(paren
id|zone
comma
id|buddy2
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|memlist_del
c_func
(paren
op_amp
id|buddy1-&gt;list
)paren
suffix:semicolon
id|mask
op_lshift_assign
l_int|1
suffix:semicolon
id|area
op_increment
suffix:semicolon
id|index
op_rshift_assign
l_int|1
suffix:semicolon
id|page_idx
op_and_assign
id|mask
suffix:semicolon
)brace
id|memlist_add_head
c_func
(paren
op_amp
(paren
id|base
op_plus
id|page_idx
)paren
op_member_access_from_pointer
id|list
comma
op_amp
id|area-&gt;free_list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|zone-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zone-&gt;free_pages
OG
id|zone-&gt;pages_high
)paren
(brace
id|zone-&gt;zone_wake_kswapd
op_assign
l_int|0
suffix:semicolon
id|zone-&gt;low_on_memory
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|macro|MARK_USED
mdefine_line|#define MARK_USED(index, order, area) &bslash;&n;&t;change_bit((index) &gt;&gt; (1+(order)), (area)-&gt;map)
DECL|function|expand
r_static
r_inline
r_struct
id|page
op_star
id|expand
(paren
id|zone_t
op_star
id|zone
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|index
comma
r_int
id|low
comma
r_int
id|high
comma
id|free_area_t
op_star
id|area
)paren
(brace
r_int
r_int
id|size
op_assign
l_int|1
op_lshift
id|high
suffix:semicolon
r_while
c_loop
(paren
id|high
OG
id|low
)paren
(brace
r_if
c_cond
(paren
id|BAD_RANGE
c_func
(paren
id|zone
comma
id|page
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|area
op_decrement
suffix:semicolon
id|high
op_decrement
suffix:semicolon
id|size
op_rshift_assign
l_int|1
suffix:semicolon
id|memlist_add_head
c_func
(paren
op_amp
(paren
id|page
)paren
op_member_access_from_pointer
id|list
comma
op_amp
(paren
id|area
)paren
op_member_access_from_pointer
id|free_list
)paren
suffix:semicolon
id|MARK_USED
c_func
(paren
id|index
comma
id|high
comma
id|area
)paren
suffix:semicolon
id|index
op_add_assign
id|size
suffix:semicolon
id|page
op_add_assign
id|size
suffix:semicolon
)brace
r_if
c_cond
(paren
id|BAD_RANGE
c_func
(paren
id|zone
comma
id|page
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
r_static
id|FASTCALL
c_func
(paren
r_struct
id|page
op_star
id|rmqueue
c_func
(paren
id|zone_t
op_star
id|zone
comma
r_int
r_int
id|order
)paren
)paren
suffix:semicolon
DECL|function|rmqueue
r_static
r_struct
id|page
op_star
id|rmqueue
c_func
(paren
id|zone_t
op_star
id|zone
comma
r_int
r_int
id|order
)paren
(brace
id|free_area_t
op_star
id|area
op_assign
id|zone-&gt;free_area
op_plus
id|order
suffix:semicolon
r_int
r_int
id|curr_order
op_assign
id|order
suffix:semicolon
r_struct
id|list_head
op_star
id|head
comma
op_star
id|curr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|zone-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_do
(brace
id|head
op_assign
op_amp
id|area-&gt;free_list
suffix:semicolon
id|curr
op_assign
id|memlist_next
c_func
(paren
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curr
op_ne
id|head
)paren
(brace
r_int
r_int
id|index
suffix:semicolon
id|page
op_assign
id|memlist_entry
c_func
(paren
id|curr
comma
r_struct
id|page
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BAD_RANGE
c_func
(paren
id|zone
comma
id|page
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|memlist_del
c_func
(paren
id|curr
)paren
suffix:semicolon
id|index
op_assign
(paren
id|page
op_minus
id|mem_map
)paren
op_minus
id|zone-&gt;offset
suffix:semicolon
id|MARK_USED
c_func
(paren
id|index
comma
id|curr_order
comma
id|area
)paren
suffix:semicolon
id|zone-&gt;free_pages
op_sub_assign
l_int|1
op_lshift
id|order
suffix:semicolon
id|page
op_assign
id|expand
c_func
(paren
id|zone
comma
id|page
comma
id|index
comma
id|order
comma
id|curr_order
comma
id|area
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|zone-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|page
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BAD_RANGE
c_func
(paren
id|zone
comma
id|page
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
id|curr_order
op_increment
suffix:semicolon
id|area
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|curr_order
OL
id|MAX_ORDER
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|zone-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the &squot;heart&squot; of the zoned buddy allocator:&n; */
DECL|function|__alloc_pages
r_struct
id|page
op_star
id|__alloc_pages
c_func
(paren
id|zonelist_t
op_star
id|zonelist
comma
r_int
r_int
id|order
)paren
(brace
id|zone_t
op_star
op_star
id|zone
suffix:semicolon
r_extern
id|wait_queue_head_t
id|kswapd_wait
suffix:semicolon
multiline_comment|/*&n;&t; * (If anyone calls gfp from interrupts nonatomically then it&n;&t; * will sooner or later tripped up by a schedule().)&n;&t; *&n;&t; * We are falling back to lower-level zones if allocation&n;&t; * in a higher zone fails.&n;&t; */
id|zone
op_assign
id|zonelist-&gt;zones
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|zone_t
op_star
id|z
op_assign
op_star
(paren
id|zone
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|z
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|z-&gt;size
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Are we supposed to free memory? Don&squot;t make it worse.. */
r_if
c_cond
(paren
op_logical_neg
id|z-&gt;zone_wake_kswapd
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|rmqueue
c_func
(paren
id|z
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z-&gt;free_pages
OL
id|z-&gt;pages_low
)paren
(brace
id|z-&gt;zone_wake_kswapd
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|kswapd_wait
)paren
)paren
id|wake_up_interruptible
c_func
(paren
op_amp
id|kswapd_wait
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|page
)paren
r_return
id|page
suffix:semicolon
)brace
)brace
multiline_comment|/* Three possibilities to get here&n;&t; * - Previous alloc_pages resulted in last zone set to have&n;&t; *   zone_wake_kswapd and start it. kswapd has not been able&n;&t; *   to release enough pages so that one zone does not have&n;&t; *   zone_wake_kswapd set.&n;&t; * - Different sets of zones (zonelist)&n;&t; *   previous did not have all zones with zone_wake_kswapd but&n;&t; *   this one has... should kswapd be woken up? it will run once.&n;&t; * - SMP race, kswapd went to sleep slightly after it as running&n;&t; *   in &squot;if (waitqueue_active(...))&squot; above.&n;&t; * + anyway the test is very cheap to do...&n;&t; */
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|kswapd_wait
)paren
)paren
id|wake_up_interruptible
c_func
(paren
op_amp
id|kswapd_wait
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, we don&squot;t have any zones that don&squot;t need some&n;&t; * balancing.. See if we have any that aren&squot;t critical..&n;&t; */
id|zone
op_assign
id|zonelist-&gt;zones
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|zone_t
op_star
id|z
op_assign
op_star
(paren
id|zone
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|z
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|z-&gt;low_on_memory
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|rmqueue
c_func
(paren
id|z
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z-&gt;free_pages
OL
id|z-&gt;pages_min
)paren
id|z-&gt;low_on_memory
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
r_return
id|page
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Uhhuh. All the zones have been critical, which means that&n;&t; * we&squot;d better do some synchronous swap-out. kswapd has not&n;&t; * been able to cope..&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;flags
op_amp
id|PF_MEMALLOC
)paren
)paren
(brace
r_int
id|gfp_mask
op_assign
id|zonelist-&gt;gfp_mask
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_to_free_pages
c_func
(paren
id|gfp_mask
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|gfp_mask
op_amp
id|__GFP_HIGH
)paren
)paren
r_goto
id|fail
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Final phase: allocate anything we can!&n;&t; */
id|zone
op_assign
id|zonelist-&gt;zones
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|zone_t
op_star
id|z
op_assign
op_star
(paren
id|zone
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|z
)paren
r_break
suffix:semicolon
id|page
op_assign
id|rmqueue
c_func
(paren
id|z
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
r_return
id|page
suffix:semicolon
)brace
id|fail
suffix:colon
multiline_comment|/* No luck.. */
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Common helper functions.&n; */
DECL|function|__get_free_pages
r_int
r_int
id|__get_free_pages
c_func
(paren
r_int
id|gfp_mask
comma
r_int
r_int
id|order
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|page
op_assign
id|alloc_pages
c_func
(paren
id|gfp_mask
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|get_zeroed_page
r_int
r_int
id|get_zeroed_page
c_func
(paren
r_int
id|gfp_mask
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|page
op_assign
id|alloc_pages
c_func
(paren
id|gfp_mask
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
r_int
r_int
id|address
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|clear_page
c_func
(paren
(paren
r_void
op_star
)paren
id|address
)paren
suffix:semicolon
r_return
id|address
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__free_pages
r_void
id|__free_pages
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|order
)paren
(brace
r_if
c_cond
(paren
id|put_page_testzero
c_func
(paren
id|page
)paren
)paren
id|__free_pages_ok
c_func
(paren
id|page
comma
id|order
)paren
suffix:semicolon
)brace
DECL|function|free_pages
r_void
id|free_pages
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|order
)paren
(brace
r_int
r_int
id|map_nr
suffix:semicolon
macro_line|#ifdef CONFIG_DISCONTIGMEM
r_if
c_cond
(paren
id|addr
op_eq
l_int|0
)paren
r_return
suffix:semicolon
macro_line|#endif
id|map_nr
op_assign
id|MAP_NR
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map_nr
OL
id|max_mapnr
)paren
id|__free_pages
c_func
(paren
id|mem_map
op_plus
id|map_nr
comma
id|order
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Total amount of free (allocatable) RAM:&n; */
DECL|function|nr_free_pages
r_int
r_int
id|nr_free_pages
(paren
r_void
)paren
(brace
r_int
r_int
id|sum
suffix:semicolon
id|zone_t
op_star
id|zone
suffix:semicolon
r_int
id|i
suffix:semicolon
id|sum
op_assign
l_int|0
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
id|NUMNODES
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|zone
op_assign
id|NODE_DATA
c_func
(paren
id|i
)paren
op_member_access_from_pointer
id|node_zones
suffix:semicolon
id|zone
OL
id|NODE_DATA
c_func
(paren
id|i
)paren
op_member_access_from_pointer
id|node_zones
op_plus
id|MAX_NR_ZONES
suffix:semicolon
id|zone
op_increment
)paren
id|sum
op_add_assign
id|zone-&gt;free_pages
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; * Amount of free RAM allocatable as buffer memory:&n; */
DECL|function|nr_free_buffer_pages
r_int
r_int
id|nr_free_buffer_pages
(paren
r_void
)paren
(brace
r_int
r_int
id|sum
suffix:semicolon
id|zone_t
op_star
id|zone
suffix:semicolon
r_int
id|i
suffix:semicolon
id|sum
op_assign
id|nr_lru_pages
op_div
l_int|3
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
id|NUMNODES
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|zone
op_assign
id|NODE_DATA
c_func
(paren
id|i
)paren
op_member_access_from_pointer
id|node_zones
suffix:semicolon
id|zone
op_le
id|NODE_DATA
c_func
(paren
id|i
)paren
op_member_access_from_pointer
id|node_zones
op_plus
id|ZONE_NORMAL
suffix:semicolon
id|zone
op_increment
)paren
id|sum
op_add_assign
id|zone-&gt;free_pages
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
macro_line|#if CONFIG_HIGHMEM
DECL|function|nr_free_highpages
r_int
r_int
id|nr_free_highpages
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|pages
op_assign
l_int|0
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
id|NUMNODES
suffix:semicolon
id|i
op_increment
)paren
id|pages
op_add_assign
id|NODE_DATA
c_func
(paren
id|i
)paren
op_member_access_from_pointer
id|node_zones
(braket
id|ZONE_HIGHMEM
)braket
dot
id|free_pages
suffix:semicolon
r_return
id|pages
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Show free area list (used inside shift_scroll-lock stuff)&n; * We also calculate the percentage fragmentation. We do this by counting the&n; * memory on each free list with the exception of the first item on the list.&n; */
DECL|function|show_free_areas_core
r_void
id|show_free_areas_core
c_func
(paren
r_int
id|nid
)paren
(brace
r_int
r_int
id|order
suffix:semicolon
r_int
id|type
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Free pages:      %6dkB (%6dkB HighMem)&bslash;n&quot;
comma
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
id|nr_free_highpages
c_func
(paren
)paren
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;( Free: %d, lru_cache: %d (%d %d %d) )&bslash;n&quot;
comma
id|nr_free_pages
c_func
(paren
)paren
comma
id|nr_lru_pages
comma
id|freepages.min
comma
id|freepages.low
comma
id|freepages.high
)paren
suffix:semicolon
r_for
c_loop
(paren
id|type
op_assign
l_int|0
suffix:semicolon
id|type
OL
id|MAX_NR_ZONES
suffix:semicolon
id|type
op_increment
)paren
(brace
r_struct
id|list_head
op_star
id|head
comma
op_star
id|curr
suffix:semicolon
id|zone_t
op_star
id|zone
op_assign
id|NODE_DATA
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|node_zones
op_plus
id|type
suffix:semicolon
r_int
r_int
id|nr
comma
id|total
comma
id|flags
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  %s: &quot;
comma
id|zone-&gt;name
)paren
suffix:semicolon
id|total
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|zone-&gt;size
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|zone-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|order
op_assign
l_int|0
suffix:semicolon
id|order
OL
id|MAX_ORDER
suffix:semicolon
id|order
op_increment
)paren
(brace
id|head
op_assign
op_amp
(paren
id|zone-&gt;free_area
op_plus
id|order
)paren
op_member_access_from_pointer
id|free_list
suffix:semicolon
id|curr
op_assign
id|head
suffix:semicolon
id|nr
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|curr
op_assign
id|memlist_next
c_func
(paren
id|curr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curr
op_eq
id|head
)paren
r_break
suffix:semicolon
id|nr
op_increment
suffix:semicolon
)brace
id|total
op_add_assign
id|nr
op_star
(paren
l_int|1
op_lshift
id|order
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%lu*%lukB &quot;
comma
id|nr
comma
(paren
id|PAGE_SIZE
op_rshift
l_int|10
)paren
op_lshift
id|order
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|zone-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;= %lukB)&bslash;n&quot;
comma
id|total
op_star
(paren
id|PAGE_SIZE
op_rshift
l_int|10
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef SWAP_CACHE_INFO
id|show_swap_cache_info
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;
)brace
DECL|function|show_free_areas
r_void
id|show_free_areas
c_func
(paren
r_void
)paren
(brace
id|show_free_areas_core
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Builds allocation fallback zone lists.&n; */
DECL|function|build_zonelists
r_static
r_inline
r_void
id|build_zonelists
c_func
(paren
id|pg_data_t
op_star
id|pgdat
)paren
(brace
r_int
id|i
comma
id|j
comma
id|k
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
id|NR_GFPINDEX
suffix:semicolon
id|i
op_increment
)paren
(brace
id|zonelist_t
op_star
id|zonelist
suffix:semicolon
id|zone_t
op_star
id|zone
suffix:semicolon
id|zonelist
op_assign
id|pgdat-&gt;node_zonelists
op_plus
id|i
suffix:semicolon
id|memset
c_func
(paren
id|zonelist
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|zonelist
)paren
)paren
suffix:semicolon
id|zonelist-&gt;gfp_mask
op_assign
id|i
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
id|k
op_assign
id|ZONE_NORMAL
suffix:semicolon
r_if
c_cond
(paren
id|i
op_amp
id|__GFP_HIGHMEM
)paren
id|k
op_assign
id|ZONE_HIGHMEM
suffix:semicolon
r_if
c_cond
(paren
id|i
op_amp
id|__GFP_DMA
)paren
id|k
op_assign
id|ZONE_DMA
suffix:semicolon
r_switch
c_cond
(paren
id|k
)paren
(brace
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * fallthrough:&n;&t;&t;&t; */
r_case
id|ZONE_HIGHMEM
suffix:colon
id|zone
op_assign
id|pgdat-&gt;node_zones
op_plus
id|ZONE_HIGHMEM
suffix:semicolon
r_if
c_cond
(paren
id|zone-&gt;size
)paren
(brace
macro_line|#ifndef CONFIG_HIGHMEM
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|zonelist-&gt;zones
(braket
id|j
op_increment
)braket
op_assign
id|zone
suffix:semicolon
)brace
r_case
id|ZONE_NORMAL
suffix:colon
id|zone
op_assign
id|pgdat-&gt;node_zones
op_plus
id|ZONE_NORMAL
suffix:semicolon
r_if
c_cond
(paren
id|zone-&gt;size
)paren
id|zonelist-&gt;zones
(braket
id|j
op_increment
)braket
op_assign
id|zone
suffix:semicolon
r_case
id|ZONE_DMA
suffix:colon
id|zone
op_assign
id|pgdat-&gt;node_zones
op_plus
id|ZONE_DMA
suffix:semicolon
r_if
c_cond
(paren
id|zone-&gt;size
)paren
id|zonelist-&gt;zones
(braket
id|j
op_increment
)braket
op_assign
id|zone
suffix:semicolon
)brace
id|zonelist-&gt;zones
(braket
id|j
op_increment
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|macro|LONG_ALIGN
mdefine_line|#define LONG_ALIGN(x) (((x)+(sizeof(long))-1)&amp;~((sizeof(long))-1))
multiline_comment|/*&n; * Set up the zone data structures:&n; *   - mark all pages reserved&n; *   - mark all memory queues empty&n; *   - clear the memory bitmaps&n; */
DECL|function|free_area_init_core
r_void
id|__init
id|free_area_init_core
c_func
(paren
r_int
id|nid
comma
id|pg_data_t
op_star
id|pgdat
comma
r_struct
id|page
op_star
op_star
id|gmap
comma
r_int
r_int
op_star
id|zones_size
comma
r_int
r_int
id|zone_start_paddr
comma
r_int
r_int
op_star
id|zholes_size
)paren
(brace
r_struct
id|page
op_star
id|p
comma
op_star
id|lmem_map
suffix:semicolon
r_int
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_int
id|map_size
suffix:semicolon
r_int
r_int
id|totalpages
comma
id|offset
comma
id|realtotalpages
suffix:semicolon
r_int
r_int
id|cumulative
op_assign
l_int|0
suffix:semicolon
id|pgdat-&gt;node_next
op_assign
id|pgdat_list
suffix:semicolon
id|pgdat_list
op_assign
id|pgdat
suffix:semicolon
id|totalpages
op_assign
l_int|0
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
id|MAX_NR_ZONES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|size
op_assign
id|zones_size
(braket
id|i
)braket
suffix:semicolon
id|totalpages
op_add_assign
id|size
suffix:semicolon
)brace
id|realtotalpages
op_assign
id|totalpages
suffix:semicolon
r_if
c_cond
(paren
id|zholes_size
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_NR_ZONES
suffix:semicolon
id|i
op_increment
)paren
id|realtotalpages
op_sub_assign
id|zholes_size
(braket
id|i
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;On node %d totalpages: %lu&bslash;n&quot;
comma
id|nid
comma
id|realtotalpages
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Select nr of pages we try to keep free for important stuff&n;&t; * with a minimum of 10 pages and a maximum of 256 pages, so&n;&t; * that we don&squot;t waste too much memory on large systems.&n;&t; * This is fairly arbitrary, but based on some behaviour&n;&t; * analysis.&n;&t; */
id|i
op_assign
id|realtotalpages
op_rshift
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|10
)paren
id|i
op_assign
l_int|10
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|256
)paren
id|i
op_assign
l_int|256
suffix:semicolon
id|freepages.min
op_add_assign
id|i
suffix:semicolon
id|freepages.low
op_add_assign
id|i
op_star
l_int|2
suffix:semicolon
id|freepages.high
op_add_assign
id|i
op_star
l_int|3
suffix:semicolon
id|memlist_init
c_func
(paren
op_amp
id|lru_cache
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Some architectures (with lots of mem and discontinous memory&n;&t; * maps) have to search for a good mem_map area:&n;&t; * For discontigmem, the conceptual mem map array starts from &n;&t; * PAGE_OFFSET, we need to align the actual array onto a mem map &n;&t; * boundary, so that MAP_NR works.&n;&t; */
id|map_size
op_assign
(paren
id|totalpages
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|page
)paren
suffix:semicolon
id|lmem_map
op_assign
(paren
r_struct
id|page
op_star
)paren
id|alloc_bootmem_node
c_func
(paren
id|nid
comma
id|map_size
)paren
suffix:semicolon
id|lmem_map
op_assign
(paren
r_struct
id|page
op_star
)paren
(paren
id|PAGE_OFFSET
op_plus
id|MAP_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
id|lmem_map
op_minus
id|PAGE_OFFSET
)paren
)paren
suffix:semicolon
op_star
id|gmap
op_assign
id|pgdat-&gt;node_mem_map
op_assign
id|lmem_map
suffix:semicolon
id|pgdat-&gt;node_size
op_assign
id|totalpages
suffix:semicolon
id|pgdat-&gt;node_start_paddr
op_assign
id|zone_start_paddr
suffix:semicolon
id|pgdat-&gt;node_start_mapnr
op_assign
(paren
id|lmem_map
op_minus
id|mem_map
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initially all pages are reserved - free ones are freed&n;&t; * up by free_all_bootmem() once the early boot process is&n;&t; * done.&n;&t; */
r_for
c_loop
(paren
id|p
op_assign
id|lmem_map
suffix:semicolon
id|p
OL
id|lmem_map
op_plus
id|totalpages
suffix:semicolon
id|p
op_increment
)paren
(brace
id|set_page_count
c_func
(paren
id|p
comma
l_int|0
)paren
suffix:semicolon
id|SetPageReserved
c_func
(paren
id|p
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|p-&gt;wait
)paren
suffix:semicolon
id|memlist_init
c_func
(paren
op_amp
id|p-&gt;list
)paren
suffix:semicolon
)brace
id|offset
op_assign
id|lmem_map
op_minus
id|mem_map
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|MAX_NR_ZONES
suffix:semicolon
id|j
op_increment
)paren
(brace
id|zone_t
op_star
id|zone
op_assign
id|pgdat-&gt;node_zones
op_plus
id|j
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
id|size
comma
id|realsize
suffix:semicolon
id|realsize
op_assign
id|size
op_assign
id|zones_size
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
id|zholes_size
)paren
id|realsize
op_sub_assign
id|zholes_size
(braket
id|j
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;zone(%lu): %lu pages.&bslash;n&quot;
comma
id|j
comma
id|size
)paren
suffix:semicolon
id|zone-&gt;size
op_assign
id|size
suffix:semicolon
id|zone-&gt;name
op_assign
id|zone_names
(braket
id|j
)braket
suffix:semicolon
id|zone-&gt;lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|zone-&gt;zone_pgdat
op_assign
id|pgdat
suffix:semicolon
id|zone-&gt;free_pages
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_continue
suffix:semicolon
id|zone-&gt;offset
op_assign
id|offset
suffix:semicolon
id|cumulative
op_add_assign
id|size
suffix:semicolon
id|mask
op_assign
(paren
id|realsize
op_div
id|zone_balance_ratio
(braket
id|j
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
OL
id|zone_balance_min
(braket
id|j
)braket
)paren
id|mask
op_assign
id|zone_balance_min
(braket
id|j
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|mask
OG
id|zone_balance_max
(braket
id|j
)braket
)paren
id|mask
op_assign
id|zone_balance_max
(braket
id|j
)braket
suffix:semicolon
id|zone-&gt;pages_min
op_assign
id|mask
suffix:semicolon
id|zone-&gt;pages_low
op_assign
id|mask
op_star
l_int|2
suffix:semicolon
id|zone-&gt;pages_high
op_assign
id|mask
op_star
l_int|3
suffix:semicolon
id|zone-&gt;low_on_memory
op_assign
l_int|0
suffix:semicolon
id|zone-&gt;zone_wake_kswapd
op_assign
l_int|0
suffix:semicolon
id|zone-&gt;zone_mem_map
op_assign
id|mem_map
op_plus
id|offset
suffix:semicolon
id|zone-&gt;zone_start_mapnr
op_assign
id|offset
suffix:semicolon
id|zone-&gt;zone_start_paddr
op_assign
id|zone_start_paddr
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
id|size
suffix:semicolon
id|i
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
id|offset
op_plus
id|i
suffix:semicolon
id|page-&gt;zone
op_assign
id|zone
suffix:semicolon
r_if
c_cond
(paren
id|j
op_ne
id|ZONE_HIGHMEM
)paren
(brace
id|page
op_member_access_from_pointer
r_virtual
op_assign
(paren
r_int
r_int
)paren
(paren
id|__va
c_func
(paren
id|zone_start_paddr
)paren
)paren
suffix:semicolon
id|zone_start_paddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
id|offset
op_add_assign
id|size
suffix:semicolon
id|mask
op_assign
op_minus
l_int|1
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
id|MAX_ORDER
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|bitmap_size
suffix:semicolon
id|memlist_init
c_func
(paren
op_amp
id|zone-&gt;free_area
(braket
id|i
)braket
dot
id|free_list
)paren
suffix:semicolon
id|mask
op_add_assign
id|mask
suffix:semicolon
id|size
op_assign
(paren
id|size
op_plus
op_complement
id|mask
)paren
op_amp
id|mask
suffix:semicolon
id|bitmap_size
op_assign
id|size
op_rshift
id|i
suffix:semicolon
id|bitmap_size
op_assign
(paren
id|bitmap_size
op_plus
l_int|7
)paren
op_rshift
l_int|3
suffix:semicolon
id|bitmap_size
op_assign
id|LONG_ALIGN
c_func
(paren
id|bitmap_size
)paren
suffix:semicolon
id|zone-&gt;free_area
(braket
id|i
)braket
dot
id|map
op_assign
(paren
r_int
r_int
op_star
)paren
id|alloc_bootmem_node
c_func
(paren
id|nid
comma
id|bitmap_size
)paren
suffix:semicolon
)brace
)brace
id|build_zonelists
c_func
(paren
id|pgdat
)paren
suffix:semicolon
)brace
DECL|function|free_area_init
r_void
id|__init
id|free_area_init
c_func
(paren
r_int
r_int
op_star
id|zones_size
)paren
(brace
id|free_area_init_core
c_func
(paren
l_int|0
comma
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
op_amp
id|mem_map
comma
id|zones_size
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|setup_mem_frac
r_static
r_int
id|__init
id|setup_mem_frac
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|j
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|zone_balance_ratio
(braket
id|j
op_increment
)braket
)paren
op_eq
l_int|2
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;setup_mem_frac: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|MAX_NR_ZONES
suffix:semicolon
id|j
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%d  &quot;
comma
id|zone_balance_ratio
(braket
id|j
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;memfrac=&quot;
comma
id|setup_mem_frac
)paren
suffix:semicolon
eof
