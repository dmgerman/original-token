multiline_comment|/*&n; *  linux/mm/swap.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; */
multiline_comment|/*&n; * This file should contain most things doing the swapping from/to disk.&n; * Started 18.12.91&n; *&n; * Swap aging added 23.2.95, Stephen Tweedie.&n; */
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
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/system.h&gt; /* for cli()/sti() */
macro_line|#include &lt;asm/segment.h&gt; /* for memcpy_to/fromfs */
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*&n; * We identify three levels of free memory.  We never let free mem&n; * fall below the min_free_pages except for atomic allocations.  We&n; * start background swapping if we fall below free_pages_high free&n; * pages, and we begin intensive swapping below free_pages_low.&n; *&n; * Keep these three variables contiguous for sysctl(2).  &n; */
DECL|variable|min_free_pages
r_int
id|min_free_pages
op_assign
l_int|20
suffix:semicolon
DECL|variable|free_pages_low
r_int
id|free_pages_low
op_assign
l_int|30
suffix:semicolon
DECL|variable|free_pages_high
r_int
id|free_pages_high
op_assign
l_int|40
suffix:semicolon
multiline_comment|/* We track the number of pages currently being asynchronously swapped&n;   out, so that we don&squot;t try to swap TOO many pages out at once */
DECL|variable|nr_async_pages
r_int
id|nr_async_pages
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Constants for the page aging mechanism: the maximum age (actually,&n; * the maximum &quot;youthfulness&quot;); the quanta by which pages rejuvinate&n; * and age; and the initial age for new pages. &n; */
DECL|variable|swap_control
id|swap_control_t
id|swap_control
op_assign
(brace
l_int|20
comma
l_int|3
comma
l_int|1
comma
l_int|3
comma
multiline_comment|/* Page aging */
l_int|10
comma
l_int|2
comma
l_int|2
comma
l_int|4
comma
multiline_comment|/* Buffer aging */
l_int|32
comma
l_int|4
comma
multiline_comment|/* Aging cluster */
l_int|8192
comma
l_int|8192
comma
multiline_comment|/* Pageout and bufferout weights */
op_minus
l_int|200
comma
multiline_comment|/* Buffer grace */
l_int|1
comma
l_int|1
comma
multiline_comment|/* Buffs/pages to free */
id|RCL_ROUND_ROBIN
multiline_comment|/* Balancing policy */
)brace
suffix:semicolon
DECL|variable|swapstats
id|swapstat_t
id|swapstats
op_assign
(brace
l_int|0
)brace
suffix:semicolon
multiline_comment|/* General swap control */
multiline_comment|/* Parse the kernel command line &quot;swap=&quot; option at load time: */
DECL|function|swap_setup
r_void
id|swap_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
r_int
op_star
id|swap_vars
(braket
l_int|8
)braket
op_assign
(brace
op_amp
id|MAX_PAGE_AGE
comma
op_amp
id|PAGE_ADVANCE
comma
op_amp
id|PAGE_DECLINE
comma
op_amp
id|PAGE_INITIAL_AGE
comma
op_amp
id|AGE_CLUSTER_FRACT
comma
op_amp
id|AGE_CLUSTER_MIN
comma
op_amp
id|PAGEOUT_WEIGHT
comma
op_amp
id|BUFFEROUT_WEIGHT
)brace
suffix:semicolon
r_int
id|i
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
id|ints
(braket
l_int|0
)braket
op_logical_and
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ints
(braket
id|i
op_plus
l_int|1
)braket
)paren
op_star
(paren
id|swap_vars
(braket
id|i
)braket
)paren
op_assign
id|ints
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/* Parse the kernel command line &quot;buff=&quot; option at load time: */
DECL|function|buff_setup
r_void
id|buff_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
r_int
op_star
id|buff_vars
(braket
l_int|6
)braket
op_assign
(brace
op_amp
id|MAX_BUFF_AGE
comma
op_amp
id|BUFF_ADVANCE
comma
op_amp
id|BUFF_DECLINE
comma
op_amp
id|BUFF_INITIAL_AGE
comma
op_amp
id|BUFFEROUT_WEIGHT
comma
op_amp
id|BUFFERMEM_GRACE
)brace
suffix:semicolon
r_int
id|i
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
id|ints
(braket
l_int|0
)braket
op_logical_and
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ints
(braket
id|i
op_plus
l_int|1
)braket
)paren
op_star
(paren
id|buff_vars
(braket
id|i
)braket
)paren
op_assign
id|ints
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
)brace
)brace
eof
