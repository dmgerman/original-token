multiline_comment|/*&n; *  linux/mm/swap_state.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *  Swap reorganised 29.12.95, Stephen Tweedie&n; */
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
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/system.h&gt; /* for cli()/sti() */
macro_line|#include &lt;asm/uaccess.h&gt; /* for cop_to/from_user */
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#ifdef SWAP_CACHE_INFO
DECL|variable|swap_cache_add_total
r_int
r_int
id|swap_cache_add_total
op_assign
l_int|0
suffix:semicolon
DECL|variable|swap_cache_add_success
r_int
r_int
id|swap_cache_add_success
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
DECL|variable|swap_cache_del_success
r_int
r_int
id|swap_cache_del_success
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
l_string|&quot;Swap cache: add %ld/%ld, delete %ld/%ld, find %ld/%ld&bslash;n&quot;
comma
id|swap_cache_add_total
comma
id|swap_cache_add_success
comma
id|swap_cache_del_total
comma
id|swap_cache_del_success
comma
id|swap_cache_find_total
comma
id|swap_cache_find_success
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|add_to_swap_cache
r_int
id|add_to_swap_cache
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|entry
)paren
(brace
r_struct
id|swap_info_struct
op_star
id|p
op_assign
op_amp
id|swap_info
(braket
id|SWP_TYPE
c_func
(paren
id|entry
)paren
)braket
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
id|swap_cache_add_total
op_increment
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|p-&gt;flags
op_amp
id|SWP_WRITEOK
)paren
op_eq
id|SWP_WRITEOK
)paren
(brace
id|page-&gt;pg_swap_entry
op_assign
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|PageTestandSetSwapCache
c_func
(paren
id|page
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;swap_cache: replacing non-empty entry&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
id|swap_cache_add_success
op_increment
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|swap_duplicate
r_void
id|swap_duplicate
c_func
(paren
r_int
r_int
id|entry
)paren
(brace
r_struct
id|swap_info_struct
op_star
id|p
suffix:semicolon
r_int
r_int
id|offset
comma
id|type
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_return
suffix:semicolon
id|offset
op_assign
id|SWP_OFFSET
c_func
(paren
id|entry
)paren
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
op_amp
id|SHM_SWP_TYPE
)paren
r_return
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
l_string|&quot;Trying to duplicate nonexistent swap-page&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p
op_assign
id|type
op_plus
id|swap_info
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
l_string|&quot;swap_duplicate: weirdness&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
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
l_string|&quot;swap_duplicate: trying to duplicate unused page&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p-&gt;swap_map
(braket
id|offset
)braket
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
