multiline_comment|/*&n; *  linux/mm/page_io.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  Swap reorganised 29.12.95, &n; *  Asynchronous swapping added 30.12.95. Stephen Tweedie&n; *  Removed race in async swapping. 14.4.1996. Bruno Haible&n; */
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
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/swapctl.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/system.h&gt; /* for cli()/sti() */
macro_line|#include &lt;asm/segment.h&gt; /* for memcpy_to/fromfs */
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|variable|lock_queue
r_static
r_struct
id|wait_queue
op_star
id|lock_queue
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * Reads or writes a swap page.&n; * wait=1: start I/O and wait for completion. wait=0: start asynchronous I/O.&n; *&n; * Important prevention of race condition: The first thing we do is set a lock&n; * on this swap page, which lasts until I/O completes. This way a&n; * write_swap_page(entry) immediately followed by a read_swap_page(entry)&n; * on the same entry will first complete the write_swap_page(). Fortunately,&n; * not more than one write_swap_page() request can be pending per entry. So&n; * all races the caller must catch are: multiple read_swap_page() requests&n; * on the same entry.&n; */
DECL|function|rw_swap_page
r_void
id|rw_swap_page
c_func
(paren
r_int
id|rw
comma
r_int
r_int
id|entry
comma
r_char
op_star
id|buf
comma
r_int
id|wait
)paren
(brace
r_int
r_int
id|type
comma
id|offset
suffix:semicolon
r_struct
id|swap_info_struct
op_star
id|p
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|type
op_assign
id|SWP_TYPE
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ge
id|nr_swapfiles
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Internal error: bad swap-device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p
op_assign
op_amp
id|swap_info
(braket
id|type
)braket
suffix:semicolon
id|offset
op_assign
id|SWP_OFFSET
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|p-&gt;max
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;rw_swap_page: weirdness&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;swap_map
op_logical_and
op_logical_neg
id|p-&gt;swap_map
(braket
id|offset
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Hmm.. Trying to use unallocated swap (%08lx)&bslash;n&quot;
comma
id|entry
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p-&gt;flags
op_amp
id|SWP_USED
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to swap to unused swap-device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Make sure we are the only process doing I/O with this swap page. */
r_while
c_loop
(paren
id|set_bit
c_func
(paren
id|offset
comma
id|p-&gt;swap_lockmap
)paren
)paren
id|sleep_on
c_func
(paren
op_amp
id|lock_queue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|READ
)paren
id|kstat.pswpin
op_increment
suffix:semicolon
r_else
id|kstat.pswpout
op_increment
suffix:semicolon
id|page
op_assign
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|buf
)paren
suffix:semicolon
id|wait_on_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;swap_device
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|wait
)paren
(brace
id|page-&gt;count
op_increment
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_free_after
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_decr_after
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_swap_unlock_after
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|page-&gt;swap_unlock_entry
op_assign
id|entry
suffix:semicolon
id|nr_async_pages
op_increment
suffix:semicolon
)brace
id|ll_rw_page
c_func
(paren
id|rw
comma
id|p-&gt;swap_device
comma
id|offset
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|wait
)paren
r_return
suffix:semicolon
id|wait_on_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|p-&gt;swap_file
)paren
(brace
r_struct
id|inode
op_star
id|swapf
op_assign
id|p-&gt;swap_file
suffix:semicolon
r_int
r_int
id|zones
(braket
id|PAGE_SIZE
op_div
l_int|512
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|swapf-&gt;i_op-&gt;bmap
op_eq
l_int|NULL
op_logical_and
id|swapf-&gt;i_op-&gt;smap
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;With MsDOS, we use msdos_smap which return&n;&t;&t;&t;&t;a sector number (not a cluster or block number).&n;&t;&t;&t;&t;It is a patch to enable the UMSDOS project.&n;&t;&t;&t;&t;Other people are working on better solution.&n;&n;&t;&t;&t;&t;It sounds like ll_rw_swap_file defined&n;&t;&t;&t;&t;it operation size (sector size) based on&n;&t;&t;&t;&t;PAGE_SIZE and the number of block to read.&n;&t;&t;&t;&t;So using bmap or smap should work even if&n;&t;&t;&t;&t;smap will require more blocks.&n;&t;&t;&t;*/
r_int
id|j
suffix:semicolon
r_int
r_int
id|block
op_assign
id|offset
op_lshift
l_int|3
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|PAGE_SIZE
suffix:semicolon
id|i
op_increment
comma
id|j
op_add_assign
l_int|512
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|zones
(braket
id|i
)braket
op_assign
id|swapf-&gt;i_op
op_member_access_from_pointer
id|smap
c_func
(paren
id|swapf
comma
id|block
op_increment
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;rw_swap_page: bad swap file&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_int
id|j
suffix:semicolon
r_int
r_int
id|block
op_assign
id|offset
op_lshift
(paren
id|PAGE_SHIFT
op_minus
id|swapf-&gt;i_sb-&gt;s_blocksize_bits
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|PAGE_SIZE
suffix:semicolon
id|i
op_increment
comma
id|j
op_add_assign
id|swapf-&gt;i_sb-&gt;s_blocksize
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|zones
(braket
id|i
)braket
op_assign
id|bmap
c_func
(paren
id|swapf
comma
id|block
op_increment
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;rw_swap_page: bad swap file&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|ll_rw_swap_file
c_func
(paren
id|rw
comma
id|swapf-&gt;i_dev
comma
id|zones
comma
id|i
comma
id|buf
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;rw_swap_page: no swap file or device&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_logical_and
op_logical_neg
id|clear_bit
c_func
(paren
id|offset
comma
id|p-&gt;swap_lockmap
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;rw_swap_page: lock already cleared&bslash;n&quot;
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|lock_queue
)paren
suffix:semicolon
)brace
multiline_comment|/* This is run when asynchronous page I/O has completed. */
DECL|function|swap_after_unlock_page
r_void
id|swap_after_unlock_page
(paren
r_int
r_int
id|entry
)paren
(brace
r_int
r_int
id|type
comma
id|offset
suffix:semicolon
r_struct
id|swap_info_struct
op_star
id|p
suffix:semicolon
id|type
op_assign
id|SWP_TYPE
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ge
id|nr_swapfiles
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;swap_after_unlock_page: bad swap-device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p
op_assign
op_amp
id|swap_info
(braket
id|type
)braket
suffix:semicolon
id|offset
op_assign
id|SWP_OFFSET
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|p-&gt;max
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;swap_after_unlock_page: weirdness&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|clear_bit
c_func
(paren
id|offset
comma
id|p-&gt;swap_lockmap
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;swap_after_unlock_page: lock already cleared&bslash;n&quot;
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|lock_queue
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Swap partitions are now read via brw_page.  ll_rw_page is an&n; * asynchronous function now --- we must call wait_on_page afterwards&n; * if synchronous IO is required.  &n; */
DECL|function|ll_rw_page
r_void
id|ll_rw_page
c_func
(paren
r_int
id|rw
comma
id|kdev_t
id|dev
comma
r_int
r_int
id|page
comma
r_char
op_star
id|buffer
)paren
(brace
r_int
id|block
op_assign
id|page
suffix:semicolon
r_switch
c_cond
(paren
id|rw
)paren
(brace
r_case
id|READ
suffix:colon
r_break
suffix:semicolon
r_case
id|WRITE
suffix:colon
r_if
c_cond
(paren
id|is_read_only
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Can&squot;t page to read-only device %s&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;ll_rw_page: bad block dev cmd, must be R/W&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|set_bit
c_func
(paren
id|PG_locked
comma
op_amp
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|buffer
)paren
)braket
dot
id|flags
)paren
)paren
id|panic
(paren
l_string|&quot;ll_rw_page: page already locked&quot;
)paren
suffix:semicolon
id|brw_page
c_func
(paren
id|rw
comma
(paren
r_int
r_int
)paren
id|buffer
comma
id|dev
comma
op_amp
id|block
comma
id|PAGE_SIZE
comma
l_int|0
)paren
suffix:semicolon
)brace
eof
