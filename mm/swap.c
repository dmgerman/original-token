multiline_comment|/*&n; *  linux/mm/swap.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; * This file should contain most things doing the swapping from/to disk.&n; * Started 18.12.91&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;asm/system.h&gt; /* for cli()/sti() */
DECL|macro|MAX_SWAPFILES
mdefine_line|#define MAX_SWAPFILES 8
DECL|macro|SWP_USED
mdefine_line|#define SWP_USED&t;1
DECL|macro|SWP_WRITEOK
mdefine_line|#define SWP_WRITEOK&t;3
DECL|variable|nr_swapfiles
r_static
r_int
id|nr_swapfiles
op_assign
l_int|0
suffix:semicolon
DECL|variable|lock_queue
r_static
r_struct
id|wait_queue
op_star
id|lock_queue
op_assign
l_int|NULL
suffix:semicolon
DECL|struct|swap_info_struct
r_static
r_struct
id|swap_info_struct
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|swap_file
r_struct
id|inode
op_star
id|swap_file
suffix:semicolon
DECL|member|swap_device
r_int
r_int
id|swap_device
suffix:semicolon
DECL|member|swap_map
r_int
r_char
op_star
id|swap_map
suffix:semicolon
DECL|member|swap_lockmap
r_char
op_star
id|swap_lockmap
suffix:semicolon
DECL|member|lowest_bit
r_int
id|lowest_bit
suffix:semicolon
DECL|member|highest_bit
r_int
id|highest_bit
suffix:semicolon
DECL|variable|swap_info
)brace
id|swap_info
(braket
id|MAX_SWAPFILES
)braket
suffix:semicolon
r_extern
r_int
r_int
id|free_page_list
suffix:semicolon
multiline_comment|/*&n; * The following are used to make sure we don&squot;t thrash too much...&n; * NOTE!! NR_LAST_FREE_PAGES must be a power of 2...&n; */
DECL|macro|NR_LAST_FREE_PAGES
mdefine_line|#define NR_LAST_FREE_PAGES 32
DECL|variable|last_free_pages
r_static
r_int
r_int
id|last_free_pages
(braket
id|NR_LAST_FREE_PAGES
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|macro|SWAP_BITS
mdefine_line|#define SWAP_BITS 4096
DECL|macro|bitop
mdefine_line|#define bitop(name,op) &bslash;&n;static inline int name(char * addr,unsigned int nr) &bslash;&n;{ &bslash;&n;int __res; &bslash;&n;__asm__ __volatile__(&quot;bt&quot; op &quot; %1,%2; adcl $0,%0&quot; &bslash;&n;:&quot;=g&quot; (__res) &bslash;&n;:&quot;r&quot; (nr),&quot;m&quot; (*(addr)),&quot;0&quot; (0)); &bslash;&n;return __res; &bslash;&n;}
id|bitop
c_func
(paren
id|bit
comma
l_string|&quot;&quot;
)paren
id|bitop
c_func
(paren
id|setbit
comma
l_string|&quot;s&quot;
)paren
id|bitop
c_func
(paren
id|clrbit
comma
l_string|&quot;r&quot;
)paren
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
id|nr
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|swap_info_struct
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nr
op_rshift
l_int|24
)paren
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
id|swap_info
op_plus
(paren
id|nr
op_rshift
l_int|24
)paren
suffix:semicolon
id|nr
op_and_assign
l_int|0x00ffffff
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_ge
id|SWAP_BITS
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
r_while
c_loop
(paren
id|setbit
c_func
(paren
id|p-&gt;swap_lockmap
comma
id|nr
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
id|p-&gt;swap_device
)paren
(brace
id|ll_rw_page
c_func
(paren
id|rw
comma
id|p-&gt;swap_device
comma
id|nr
comma
id|buf
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
r_int
r_int
id|zones
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_int
id|block
op_assign
id|nr
op_lshift
l_int|2
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
l_int|4
suffix:semicolon
id|i
op_increment
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
id|p-&gt;swap_file
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
id|ll_rw_swap_file
c_func
(paren
id|rw
comma
id|p-&gt;swap_file-&gt;i_dev
comma
id|zones
comma
l_int|4
comma
id|buf
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;re_swap_page: no swap file or device&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clrbit
c_func
(paren
id|p-&gt;swap_lockmap
comma
id|nr
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
DECL|function|get_swap_page
r_static
r_int
r_int
id|get_swap_page
c_func
(paren
r_void
)paren
(brace
r_struct
id|swap_info_struct
op_star
id|p
suffix:semicolon
r_int
r_int
id|block_nr
comma
id|swap_nr
suffix:semicolon
id|p
op_assign
id|swap_info
suffix:semicolon
r_for
c_loop
(paren
id|swap_nr
op_assign
l_int|0
suffix:semicolon
id|swap_nr
OL
id|nr_swapfiles
suffix:semicolon
id|swap_nr
op_increment
comma
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|p-&gt;flags
op_amp
id|SWP_WRITEOK
)paren
op_ne
id|SWP_WRITEOK
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|block_nr
op_assign
id|p-&gt;lowest_bit
suffix:semicolon
id|block_nr
op_le
id|p-&gt;highest_bit
suffix:semicolon
id|block_nr
op_increment
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;swap_map
(braket
id|block_nr
)braket
)paren
r_continue
suffix:semicolon
id|p-&gt;swap_map
(braket
id|block_nr
)braket
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|block_nr
op_eq
id|p-&gt;highest_bit
)paren
id|p-&gt;highest_bit
op_decrement
suffix:semicolon
id|p-&gt;lowest_bit
op_assign
id|block_nr
suffix:semicolon
r_return
id|block_nr
op_plus
(paren
id|swap_nr
op_lshift
l_int|24
)paren
suffix:semicolon
)brace
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
id|nr
)paren
(brace
r_struct
id|swap_info_struct
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nr
op_rshift
l_int|24
)paren
op_ge
id|nr_swapfiles
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free nonexistent swap-page&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p
op_assign
(paren
id|nr
op_rshift
l_int|24
)paren
op_plus
id|swap_info
suffix:semicolon
id|nr
op_and_assign
l_int|0x00ffffff
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_ge
id|SWAP_BITS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;swap_free: weirness&bslash;n&quot;
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
id|nr
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
id|nr
)braket
op_increment
suffix:semicolon
)brace
DECL|function|swap_free
r_void
id|swap_free
c_func
(paren
r_int
r_int
id|nr
)paren
(brace
r_struct
id|swap_info_struct
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nr
op_rshift
l_int|24
)paren
op_ge
id|nr_swapfiles
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free nonexistent swap-page&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p
op_assign
(paren
id|nr
op_rshift
l_int|24
)paren
op_plus
id|swap_info
suffix:semicolon
id|nr
op_and_assign
l_int|0x00ffffff
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_ge
id|SWAP_BITS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;swap_free: weirness&bslash;n&quot;
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
l_string|&quot;Trying to free swap from unused swap-device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|setbit
c_func
(paren
id|p-&gt;swap_lockmap
comma
id|nr
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
id|nr
OL
id|p-&gt;lowest_bit
)paren
id|p-&gt;lowest_bit
op_assign
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|nr
OG
id|p-&gt;highest_bit
)paren
id|p-&gt;highest_bit
op_assign
id|nr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;swap_map
(braket
id|nr
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;swap_free: swap-space map bad (page %d)&bslash;n&quot;
comma
id|nr
)paren
suffix:semicolon
r_else
id|p-&gt;swap_map
(braket
id|nr
)braket
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clrbit
c_func
(paren
id|p-&gt;swap_lockmap
comma
id|nr
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;swap_free: lock already cleared&bslash;n&quot;
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
DECL|function|swap_in
r_void
id|swap_in
c_func
(paren
r_int
r_int
op_star
id|table_ptr
)paren
(brace
r_int
r_int
id|swap_nr
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
id|swap_nr
op_assign
op_star
id|table_ptr
suffix:semicolon
r_if
c_cond
(paren
l_int|1
op_amp
id|swap_nr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;trying to swap in present page&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|swap_nr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No swap page in swap_in&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|page
op_assign
id|get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
(brace
id|oom
c_func
(paren
id|current
)paren
suffix:semicolon
id|page
op_assign
id|BAD_PAGE
suffix:semicolon
)brace
r_else
id|read_swap_page
c_func
(paren
id|swap_nr
op_rshift
l_int|1
comma
(paren
r_char
op_star
)paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|table_ptr
op_ne
id|swap_nr
)paren
(brace
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
op_star
id|table_ptr
op_assign
id|page
op_or
(paren
id|PAGE_DIRTY
op_or
l_int|7
)paren
suffix:semicolon
id|swap_free
c_func
(paren
id|swap_nr
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|try_to_swap_out
r_static
r_int
id|try_to_swap_out
c_func
(paren
r_int
r_int
op_star
id|table_ptr
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
r_int
r_int
id|swap_nr
suffix:semicolon
id|page
op_assign
op_star
id|table_ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|PAGE_PRESENT
op_amp
id|page
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|page
op_ge
id|high_memory
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;try_to_swap_out: bad page (%08x)&bslash;n&quot;
comma
id|page
)paren
suffix:semicolon
op_star
id|table_ptr
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
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|page
)paren
)braket
op_amp
id|MAP_PAGE_RESERVED
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|PAGE_ACCESSED
op_amp
id|page
)paren
(brace
op_star
id|table_ptr
op_and_assign
op_complement
id|PAGE_ACCESSED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_LAST_FREE_PAGES
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|last_free_pages
(braket
id|i
)braket
op_eq
(paren
id|page
op_amp
l_int|0xfffff000
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|PAGE_DIRTY
op_amp
id|page
)paren
(brace
id|page
op_and_assign
l_int|0xfffff000
suffix:semicolon
r_if
c_cond
(paren
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|page
)paren
)braket
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
id|swap_nr
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
op_star
id|table_ptr
op_assign
id|swap_nr
op_lshift
l_int|1
suffix:semicolon
id|invalidate
c_func
(paren
)paren
suffix:semicolon
id|write_swap_page
c_func
(paren
id|swap_nr
comma
(paren
r_char
op_star
)paren
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
l_int|1
suffix:semicolon
)brace
id|page
op_and_assign
l_int|0xfffff000
suffix:semicolon
op_star
id|table_ptr
op_assign
l_int|0
suffix:semicolon
id|invalidate
c_func
(paren
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
op_plus
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|page
)paren
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_idle() does nothing much: it just searches for likely candidates for&n; * swapping out or forgetting about. This speeds up the search when we&n; * actually have to swap.&n; */
DECL|function|sys_idle
r_int
id|sys_idle
c_func
(paren
r_void
)paren
(brace
id|need_resched
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Go through the page tables, searching for a user page that&n; * we can swap out.&n; * &n; * We now check that the process is swappable (normally only &squot;init&squot;&n; * is un-swappable), allowing high-priority processes which cannot be&n; * swapped out (things like user-level device drivers (Not implemented)).&n; */
DECL|function|swap_out
r_static
r_int
id|swap_out
c_func
(paren
r_int
r_int
id|priority
)paren
(brace
r_static
r_int
id|swap_task
op_assign
l_int|1
suffix:semicolon
r_static
r_int
id|swap_table
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|swap_page
op_assign
l_int|0
suffix:semicolon
r_int
id|counter
op_assign
id|NR_TASKS
op_star
l_int|8
suffix:semicolon
r_int
id|pg_table
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|counter
op_rshift_assign
id|priority
suffix:semicolon
id|check_task
suffix:colon
r_if
c_cond
(paren
id|counter
op_decrement
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
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
r_goto
id|check_task
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
op_logical_neg
id|p
op_logical_or
op_logical_neg
id|p-&gt;swappable
)paren
(brace
id|swap_task
op_increment
suffix:semicolon
r_goto
id|check_task
suffix:semicolon
)brace
id|check_dir
suffix:colon
r_if
c_cond
(paren
id|swap_table
op_ge
l_int|1024
)paren
(brace
id|swap_table
op_assign
l_int|0
suffix:semicolon
id|swap_task
op_increment
suffix:semicolon
r_goto
id|check_task
suffix:semicolon
)brace
id|pg_table
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|p-&gt;tss.cr3
)paren
(braket
id|swap_table
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pg_table
op_ge
id|high_memory
op_logical_or
(paren
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|pg_table
)paren
)braket
op_amp
id|MAP_PAGE_RESERVED
)paren
)paren
(brace
id|swap_table
op_increment
suffix:semicolon
r_goto
id|check_dir
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
l_int|1
op_amp
id|pg_table
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bad page-table at pg_dir[%d]: %08x&bslash;n&bslash;r&quot;
comma
id|swap_table
comma
id|pg_table
)paren
suffix:semicolon
(paren
(paren
r_int
r_int
op_star
)paren
id|p-&gt;tss.cr3
)paren
(braket
id|swap_table
)braket
op_assign
l_int|0
suffix:semicolon
id|swap_table
op_increment
suffix:semicolon
r_goto
id|check_dir
suffix:semicolon
)brace
id|pg_table
op_and_assign
l_int|0xfffff000
suffix:semicolon
id|check_table
suffix:colon
r_if
c_cond
(paren
id|swap_page
op_ge
l_int|1024
)paren
(brace
id|swap_page
op_assign
l_int|0
suffix:semicolon
id|swap_table
op_increment
suffix:semicolon
r_goto
id|check_dir
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|try_to_swap_out
c_func
(paren
id|swap_page
op_plus
(paren
r_int
r_int
op_star
)paren
id|pg_table
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|p-&gt;rss
op_decrement
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
id|p-&gt;rss
op_decrement
suffix:semicolon
)brace
id|swap_page
op_increment
suffix:semicolon
r_goto
id|check_table
suffix:semicolon
)brace
DECL|function|try_to_free_page
r_static
r_int
id|try_to_free_page
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
l_int|6
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|shrink_buffers
c_func
(paren
id|i
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|swap_out
c_func
(paren
id|i
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that this must be atomic, or bad things will happen when&n; * pages are requested in interrupts (as malloc can do). Thus the&n; * cli/sti&squot;s.&n; */
DECL|function|add_mem_queue
r_static
r_inline
r_void
id|add_mem_queue
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
op_star
id|queue
)paren
(brace
id|addr
op_and_assign
l_int|0xfffff000
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|addr
op_assign
op_star
id|queue
suffix:semicolon
op_star
id|queue
op_assign
id|addr
suffix:semicolon
)brace
multiline_comment|/*&n; * Free_page() adds the page to the free lists. This is optimized for&n; * fast normal cases (no error jumps taken normally).&n; *&n; * The way to optimize jumps for gcc-2.2.2 is to:&n; *  - select the &quot;normal&quot; case and put it inside the if () { XXX }&n; *  - no else-statements if you can avoid them&n; *&n; * With the above two rules, you get a straight-line execution path&n; * for the normal case, giving better asm-code.&n; */
DECL|function|free_page
r_void
id|free_page
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|addr
OL
id|high_memory
)paren
(brace
r_int
r_int
op_star
id|map
op_assign
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|map
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|map
op_amp
id|MAP_PAGE_RESERVED
)paren
)paren
(brace
r_int
r_int
id|flag
suffix:semicolon
id|save_flags
c_func
(paren
id|flag
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
op_star
id|map
)paren
(brace
r_if
c_cond
(paren
id|nr_secondary_pages
OL
id|MAX_SECONDARY_PAGES
)paren
(brace
id|add_mem_queue
c_func
(paren
id|addr
comma
op_amp
id|secondary_page_list
)paren
suffix:semicolon
id|nr_secondary_pages
op_increment
suffix:semicolon
id|restore_flags
c_func
(paren
id|flag
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|add_mem_queue
c_func
(paren
id|addr
comma
op_amp
id|free_page_list
)paren
suffix:semicolon
id|nr_free_pages
op_increment
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flag
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Trying to free free memory (%08x): memory probabably corrupted&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Trying to free nonexistent page %08x&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * This is one ugly macro, but it simplifies checking, and makes&n; * this speed-critical place reasonably fast, especially as we have&n; * to do things with the interrupt flag etc.&n; *&n; * Note that this #define is heavily optimized to give fast code&n; * for the normal case - the if-statements are ordered so that gcc-2.2.2&n; * will make *no* jumps for the normal code. Don&squot;t touch unless you&n; * know what you are doing.&n; */
DECL|macro|REMOVE_FROM_MEM_QUEUE
mdefine_line|#define REMOVE_FROM_MEM_QUEUE(queue,nr) &bslash;&n;&t;cli(); &bslash;&n;&t;if (result = queue) { &bslash;&n;&t;&t;if (!(result &amp; 0xfff) &amp;&amp; result &lt; high_memory) { &bslash;&n;&t;&t;&t;queue = *(unsigned long *) result; &bslash;&n;&t;&t;&t;if (!mem_map[MAP_NR(result)]) { &bslash;&n;&t;&t;&t;&t;mem_map[MAP_NR(result)] = 1; &bslash;&n;&t;&t;&t;&t;nr--; &bslash;&n;last_free_pages[index = (index + 1) &amp; (NR_LAST_FREE_PAGES - 1)] = result; &bslash;&n;&t;&t;&t;&t;restore_flags(flag); &bslash;&n;&t;&t;&t;&t;__asm__ __volatile__(&quot;cld ; rep ; stosl&quot; &bslash;&n;&t;&t;&t;&t;&t;::&quot;a&quot; (0),&quot;c&quot; (1024),&quot;D&quot; (result) &bslash;&n;&t;&t;&t;&t;&t;:&quot;di&quot;,&quot;cx&quot;); &bslash;&n;&t;&t;&t;&t;return result; &bslash;&n;&t;&t;&t;} &bslash;&n;&t;&t;&t;printk(&quot;Free page %08x has mem_map = %d&bslash;n&quot;, &bslash;&n;&t;&t;&t;&t;result,mem_map[MAP_NR(result)]); &bslash;&n;&t;&t;} else &bslash;&n;&t;&t;&t;printk(&quot;Result = 0x%08x - memory map destroyed&bslash;n&quot;, result); &bslash;&n;&t;&t;queue = 0; &bslash;&n;&t;&t;nr = 0; &bslash;&n;&t;} else if (nr) { &bslash;&n;&t;&t;printk(#nr &quot; is %d, but &quot; #queue &quot; is empty&bslash;n&quot;,nr); &bslash;&n;&t;&t;nr = 0; &bslash;&n;&t;} &bslash;&n;&t;restore_flags(flag)
multiline_comment|/*&n; * Get physical address of first (actually last :-) free page, and mark it&n; * used. If no free pages left, return 0.&n; *&n; * Note that this is one of the most heavily called functions in the kernel,&n; * so it&squot;s a bit timing-critical (especially as we have to disable interrupts&n; * in it). See the above macro which does most of the work, and which is&n; * optimized for a fast normal path of execution.&n; */
DECL|function|get_free_page
r_int
r_int
id|get_free_page
c_func
(paren
r_int
id|priority
)paren
(brace
r_int
r_int
id|result
comma
id|flag
suffix:semicolon
r_static
r_int
r_int
id|index
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* this routine can be called at interrupt time via&n;&t;   malloc.  We want to make sure that the critical&n;&t;   sections of code have interrupts disabled. -RAB&n;&t;   Is this code reentrant? */
id|save_flags
c_func
(paren
id|flag
)paren
suffix:semicolon
id|repeat
suffix:colon
id|REMOVE_FROM_MEM_QUEUE
c_func
(paren
id|free_page_list
comma
id|nr_free_pages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priority
op_eq
id|GFP_BUFFER
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|priority
op_ne
id|GFP_ATOMIC
)paren
r_if
c_cond
(paren
id|try_to_free_page
c_func
(paren
)paren
)paren
r_goto
id|repeat
suffix:semicolon
id|REMOVE_FROM_MEM_QUEUE
c_func
(paren
id|secondary_page_list
comma
id|nr_secondary_pages
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Trying to stop swapping from a file is fraught with races, so&n; * we repeat quite a bit here when we have to pause. swapoff()&n; * isn&squot;t exactly timing-critical, so who cares?&n; *&n; * Note the &squot;&gt;&gt; 25&squot; instead of &squot;&gt;&gt; 24&squot; when checking against&n; * swap_nr: remember that the low bit in a page-address is used&n; * for the PAGE_PRESENT bit, and is not part of the swap address.&n; */
DECL|function|try_to_unuse
r_static
r_int
id|try_to_unuse
c_func
(paren
r_int
r_int
id|swap_nr
)paren
(brace
r_int
id|nr
comma
id|pgt
comma
id|pg
suffix:semicolon
r_int
r_int
id|page
comma
op_star
id|ppage
suffix:semicolon
r_int
r_int
id|tmp
op_assign
l_int|0
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|nr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * When we have to sleep, we restart the whole algorithm from the same&n; * task we stopped in. That at least rids us of all races.&n; */
id|repeat
suffix:colon
r_for
c_loop
(paren
suffix:semicolon
id|nr
OL
id|NR_TASKS
suffix:semicolon
id|nr
op_increment
)paren
(brace
id|p
op_assign
id|task
(braket
id|nr
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|pgt
op_assign
l_int|0
suffix:semicolon
id|pgt
OL
l_int|1024
suffix:semicolon
id|pgt
op_increment
)paren
(brace
id|ppage
op_assign
id|pgt
op_plus
(paren
(paren
r_int
r_int
op_star
)paren
id|p-&gt;tss.cr3
)paren
suffix:semicolon
id|page
op_assign
op_star
id|ppage
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_amp
id|PAGE_PRESENT
)paren
op_logical_or
(paren
id|page
op_ge
id|high_memory
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;try_to_unuse: bad page directory (%d,%d:%08x)&bslash;n&quot;
comma
id|nr
comma
id|pgt
comma
id|page
)paren
suffix:semicolon
op_star
id|ppage
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|page
)paren
)braket
op_amp
id|MAP_PAGE_RESERVED
)paren
r_continue
suffix:semicolon
id|ppage
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|page
op_amp
l_int|0xfffff000
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pg
op_assign
l_int|0
suffix:semicolon
id|pg
OL
l_int|1024
suffix:semicolon
id|pg
op_increment
comma
id|ppage
op_increment
)paren
(brace
id|page
op_assign
op_star
id|ppage
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|page
op_amp
id|PAGE_PRESENT
)paren
(brace
r_if
c_cond
(paren
id|page
op_ge
id|high_memory
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;try_to_unuse: bad page table (%d,%d,%d:%08x)&bslash;n&quot;
comma
id|nr
comma
id|pgt
comma
id|pg
comma
id|page
)paren
suffix:semicolon
op_star
id|ppage
op_assign
l_int|0
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|page
op_rshift
l_int|25
)paren
op_ne
id|swap_nr
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
id|tmp
op_assign
id|get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|read_swap_page
c_func
(paren
id|page
op_rshift
l_int|1
comma
(paren
r_char
op_star
)paren
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ppage
op_eq
id|page
)paren
(brace
op_star
id|ppage
op_assign
id|tmp
op_or
(paren
id|PAGE_DIRTY
op_or
l_int|7
)paren
suffix:semicolon
op_increment
id|p-&gt;rss
suffix:semicolon
id|swap_free
c_func
(paren
id|page
op_rshift
l_int|1
)paren
suffix:semicolon
id|tmp
op_assign
l_int|0
suffix:semicolon
)brace
r_goto
id|repeat
suffix:semicolon
)brace
)brace
)brace
id|free_page
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_swapoff
r_int
id|sys_swapoff
c_func
(paren
r_const
r_char
op_star
id|specialfile
)paren
(brace
r_struct
id|swap_info_struct
op_star
id|p
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
r_int
id|swap_nr
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|i
op_assign
id|namei
c_func
(paren
id|specialfile
comma
op_amp
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|p
op_assign
id|swap_info
suffix:semicolon
r_for
c_loop
(paren
id|swap_nr
op_assign
l_int|0
suffix:semicolon
id|swap_nr
OL
id|nr_swapfiles
suffix:semicolon
id|swap_nr
op_increment
comma
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|p-&gt;flags
op_amp
id|SWP_WRITEOK
)paren
op_ne
id|SWP_WRITEOK
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;swap_file
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;swap_file
op_eq
id|inode
)paren
r_break
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;swap_device
op_eq
id|inode-&gt;i_rdev
)paren
r_break
suffix:semicolon
)brace
)brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|swap_nr
op_ge
id|nr_swapfiles
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|p-&gt;flags
op_assign
id|SWP_USED
suffix:semicolon
id|i
op_assign
id|try_to_unuse
c_func
(paren
id|swap_nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
(brace
id|p-&gt;flags
op_assign
id|SWP_WRITEOK
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
id|iput
c_func
(paren
id|p-&gt;swap_file
)paren
suffix:semicolon
id|p-&gt;swap_file
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;swap_device
op_assign
l_int|0
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
)paren
id|p-&gt;swap_map
)paren
suffix:semicolon
id|p-&gt;swap_map
op_assign
l_int|NULL
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
)paren
id|p-&gt;swap_lockmap
)paren
suffix:semicolon
id|p-&gt;swap_lockmap
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Written 01/25/92 by Simmule Turner, heavily changed by Linus.&n; *&n; * The swapon system call&n; */
DECL|function|sys_swapon
r_int
id|sys_swapon
c_func
(paren
r_const
r_char
op_star
id|specialfile
)paren
(brace
r_struct
id|swap_info_struct
op_star
id|p
suffix:semicolon
r_struct
id|inode
op_star
id|swap_inode
suffix:semicolon
r_int
r_int
id|swap_nr
suffix:semicolon
r_char
op_star
id|tmp
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|p
op_assign
id|swap_info
suffix:semicolon
r_for
c_loop
(paren
id|swap_nr
op_assign
l_int|0
suffix:semicolon
id|swap_nr
OL
id|nr_swapfiles
suffix:semicolon
id|swap_nr
op_increment
comma
id|p
op_increment
)paren
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
r_break
suffix:semicolon
r_if
c_cond
(paren
id|swap_nr
op_ge
id|MAX_SWAPFILES
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|swap_nr
op_ge
id|nr_swapfiles
)paren
id|nr_swapfiles
op_assign
id|swap_nr
op_plus
l_int|1
suffix:semicolon
id|p-&gt;flags
op_assign
id|SWP_USED
suffix:semicolon
id|p-&gt;swap_file
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;swap_device
op_assign
l_int|0
suffix:semicolon
id|p-&gt;swap_map
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;swap_lockmap
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;lowest_bit
op_assign
l_int|0
suffix:semicolon
id|p-&gt;highest_bit
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
id|namei
c_func
(paren
id|specialfile
comma
op_amp
id|swap_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
(brace
id|p-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|swap_inode-&gt;i_count
op_ne
l_int|1
)paren
(brace
id|iput
c_func
(paren
id|swap_inode
)paren
suffix:semicolon
id|p-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISBLK
c_func
(paren
id|swap_inode-&gt;i_mode
)paren
)paren
(brace
id|p-&gt;swap_device
op_assign
id|swap_inode-&gt;i_rdev
suffix:semicolon
id|iput
c_func
(paren
id|swap_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;swap_device
)paren
(brace
id|p-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr_swapfiles
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
id|swap_nr
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;swap_device
op_eq
id|swap_info
(braket
id|i
)braket
dot
id|swap_device
)paren
(brace
id|p-&gt;swap_device
op_assign
l_int|0
suffix:semicolon
id|p-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|swap_inode-&gt;i_mode
)paren
)paren
id|p-&gt;swap_file
op_assign
id|swap_inode
suffix:semicolon
r_else
(brace
id|iput
c_func
(paren
id|swap_inode
)paren
suffix:semicolon
id|p-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|get_free_page
c_func
(paren
id|GFP_USER
)paren
suffix:semicolon
id|p-&gt;swap_lockmap
op_assign
(paren
r_char
op_star
)paren
id|get_free_page
c_func
(paren
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
op_logical_or
op_logical_neg
id|p-&gt;swap_lockmap
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to start swapping: out of memory :-)&bslash;n&quot;
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
)paren
id|tmp
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
)paren
id|p-&gt;swap_lockmap
)paren
suffix:semicolon
id|iput
c_func
(paren
id|p-&gt;swap_file
)paren
suffix:semicolon
id|p-&gt;swap_device
op_assign
l_int|0
suffix:semicolon
id|p-&gt;swap_file
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;swap_map
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;swap_lockmap
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|read_swap_page
c_func
(paren
id|swap_nr
op_lshift
l_int|24
comma
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
l_string|&quot;SWAP-SPACE&quot;
comma
id|tmp
op_plus
l_int|4086
comma
l_int|10
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to find swap-space signature&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
)paren
id|tmp
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
)paren
id|p-&gt;swap_lockmap
)paren
suffix:semicolon
id|iput
c_func
(paren
id|p-&gt;swap_file
)paren
suffix:semicolon
id|p-&gt;swap_device
op_assign
l_int|0
suffix:semicolon
id|p-&gt;swap_file
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;swap_map
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;swap_lockmap
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|tmp
op_plus
l_int|4086
comma
l_int|0
comma
l_int|10
)paren
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
id|p-&gt;lowest_bit
op_assign
l_int|0
suffix:semicolon
id|p-&gt;highest_bit
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|SWAP_BITS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|bit
c_func
(paren
id|tmp
comma
id|i
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;lowest_bit
)paren
id|p-&gt;lowest_bit
op_assign
id|i
suffix:semicolon
id|p-&gt;highest_bit
op_assign
id|i
suffix:semicolon
id|j
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|j
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Empty swap-file&bslash;n&quot;
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
)paren
id|tmp
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
)paren
id|p-&gt;swap_lockmap
)paren
suffix:semicolon
id|iput
c_func
(paren
id|p-&gt;swap_file
)paren
suffix:semicolon
id|p-&gt;swap_device
op_assign
l_int|0
suffix:semicolon
id|p-&gt;swap_file
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;swap_map
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;swap_lockmap
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|i
op_assign
id|SWAP_BITS
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
r_if
c_cond
(paren
id|bit
c_func
(paren
id|tmp
comma
id|i
)paren
)paren
id|tmp
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_else
id|tmp
(braket
id|i
)braket
op_assign
l_int|128
suffix:semicolon
id|tmp
(braket
l_int|0
)braket
op_assign
l_int|128
suffix:semicolon
id|p-&gt;swap_map
op_assign
id|tmp
suffix:semicolon
id|p-&gt;flags
op_assign
id|SWP_WRITEOK
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Adding Swap: %dk swap-space&bslash;n&bslash;r&quot;
comma
id|j
op_lshift
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
