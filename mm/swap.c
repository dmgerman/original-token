multiline_comment|/*&n; *  linux/mm/swap.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; */
multiline_comment|/*&n; * This file contains the default values for the opereation of the&n; * Linux VM subsystem. Fine-tuning documentation can be found in&n; * linux/Documentation/sysctl/vm.txt.&n; * Started 18.12.91&n; * Swap aging added 23.2.95, Stephen Tweedie.&n; * Buffermem limits added 12.3.98, Rik van Riel.&n; */
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
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/system.h&gt; /* for cli()/sti() */
macro_line|#include &lt;asm/uaccess.h&gt; /* for copy_to/from_user */
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*&n; * We identify three levels of free memory.  We never let free mem&n; * fall below the freepages.min except for atomic allocations.  We&n; * start background swapping if we fall below freepages.high free&n; * pages, and we begin intensive swapping below freepages.low.&n; *&n; * These values are there to keep GCC from complaining. Actual&n; * initialization is done in mm/page_alloc.c or arch/sparc(64)/mm/init.c.&n; */
DECL|variable|freepages
id|freepages_t
id|freepages
op_assign
(brace
l_int|48
comma
multiline_comment|/* freepages.min */
l_int|96
comma
multiline_comment|/* freepages.low */
l_int|144
multiline_comment|/* freepages.high */
)brace
suffix:semicolon
multiline_comment|/* We track the number of pages currently being asynchronously swapped&n;   out, so that we don&squot;t try to swap TOO many pages out at once */
DECL|variable|nr_async_pages
id|atomic_t
id|nr_async_pages
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n; * Constants for the page aging mechanism: the maximum age (actually,&n; * the maximum &quot;youthfulness&quot;); the quanta by which pages rejuvenate&n; * and age; and the initial age for new pages. &n; *&n; * The &quot;pageout_weight&quot; is strictly a fixedpoint number with the&n; * ten low bits being the fraction (ie 8192 really means &quot;8.0&quot;).&n; */
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
l_int|32
comma
l_int|4
comma
multiline_comment|/* Aging cluster */
l_int|8192
comma
multiline_comment|/* sc_pageout_weight aka PAGEOUT_WEIGHT */
l_int|8192
comma
multiline_comment|/* sc_bufferout_weight aka BUFFEROUT_WEIGHT */
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
DECL|variable|buffer_mem
id|buffer_mem_t
id|buffer_mem
op_assign
(brace
l_int|5
comma
multiline_comment|/* minimum percent buffer */
l_int|25
comma
multiline_comment|/* borrow percent buffer */
l_int|60
multiline_comment|/* maximum percent buffer */
)brace
suffix:semicolon
DECL|variable|page_cache
id|buffer_mem_t
id|page_cache
op_assign
(brace
l_int|5
comma
multiline_comment|/* minimum percent page cache */
l_int|30
comma
multiline_comment|/* borrow percent page cache */
l_int|75
multiline_comment|/* maximum */
)brace
suffix:semicolon
DECL|variable|pager_daemon
id|pager_daemon_t
id|pager_daemon
op_assign
(brace
l_int|512
comma
multiline_comment|/* base number for calculating the number of tries */
id|SWAP_CLUSTER_MAX
comma
multiline_comment|/* minimum number of tries */
id|SWAP_CLUSTER_MAX
comma
multiline_comment|/* do swap I/O in clusters of this size */
)brace
suffix:semicolon
eof
