multiline_comment|/*&n; *  linux/mm/swap.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
multiline_comment|/*&n; * This file should contain most things doing the swapping from/to disk.&n; * Started 18.12.91&n; */
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
DECL|macro|SWAP_BITS
mdefine_line|#define SWAP_BITS (4096&lt;&lt;3)
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
DECL|variable|swap_bitmap
r_static
r_char
op_star
id|swap_bitmap
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|swap_device
r_int
r_int
id|swap_device
op_assign
l_int|0
suffix:semicolon
DECL|variable|swap_file
r_struct
id|inode
op_star
id|swap_file
op_assign
l_int|NULL
suffix:semicolon
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
r_int
r_int
id|zones
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|swap_device
)paren
(brace
id|ll_rw_page
c_func
(paren
id|rw
comma
id|swap_device
comma
id|nr
comma
id|buf
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|swap_file
)paren
(brace
id|nr
op_lshift_assign
l_int|2
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
id|swap_file
comma
id|nr
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
id|swap_file-&gt;i_dev
comma
id|zones
comma
l_int|4
comma
id|buf
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;ll_swap_page: no swap file or device&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We never page the pages in task[0] - kernel memory.&n; * We page all other pages.&n; */
DECL|macro|FIRST_VM_PAGE
mdefine_line|#define FIRST_VM_PAGE (TASK_SIZE&gt;&gt;12)
DECL|macro|LAST_VM_PAGE
mdefine_line|#define LAST_VM_PAGE (1024*1024)
DECL|macro|VM_PAGES
mdefine_line|#define VM_PAGES (LAST_VM_PAGE - FIRST_VM_PAGE)
DECL|function|get_swap_page
r_static
r_int
id|get_swap_page
c_func
(paren
r_void
)paren
(brace
r_int
id|nr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|swap_bitmap
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|nr
op_assign
l_int|1
suffix:semicolon
id|nr
OL
id|SWAP_BITS
suffix:semicolon
id|nr
op_increment
)paren
r_if
c_cond
(paren
id|clrbit
c_func
(paren
id|swap_bitmap
comma
id|nr
)paren
)paren
r_return
id|nr
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|swap_free
r_void
id|swap_free
c_func
(paren
r_int
id|swap_nr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|swap_nr
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|swap_bitmap
op_logical_and
id|swap_nr
OL
id|SWAP_BITS
)paren
r_if
c_cond
(paren
op_logical_neg
id|setbit
c_func
(paren
id|swap_bitmap
comma
id|swap_nr
)paren
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;swap_free: swap-space bitmap bad&bslash;n&quot;
)paren
suffix:semicolon
r_return
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
id|swap_nr
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|swap_bitmap
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to swap in without swap bit-map&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|1
op_amp
op_star
id|table_ptr
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
id|swap_nr
op_assign
op_star
id|table_ptr
op_rshift
l_int|1
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
id|get_free_page
c_func
(paren
)paren
)paren
)paren
id|oom
c_func
(paren
)paren
suffix:semicolon
id|read_swap_page
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
r_if
c_cond
(paren
id|setbit
c_func
(paren
id|swap_bitmap
comma
id|swap_nr
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;swapping in multiply from same page&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
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
)brace
DECL|function|try_to_swap_out
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
op_minus
id|LOW_MEM
OG
id|PAGING_MEMORY
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
suffix:semicolon
)brace
multiline_comment|/*&n; * Go through the page tables, searching for a user page that&n; * we can swap out.&n; *&n; * Here it&squot;s easy to add a check for tasks that may not be swapped out:&n; * loadable device drivers or similar. Just add an entry to the task-struct&n; * and check it at the same time you check for the existence of the task.&n; * The code assumes tasks are page-table aligned, but so do other parts&n; * of the memory manager...&n; */
DECL|function|swap_out
r_int
id|swap_out
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|dir_entry
op_assign
l_int|1024
suffix:semicolon
r_static
r_int
id|page_entry
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|counter
op_assign
id|VM_PAGES
suffix:semicolon
r_int
id|pg_table
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|check_dir
suffix:colon
r_if
c_cond
(paren
id|counter
OL
l_int|0
)paren
r_goto
id|no_swap
suffix:semicolon
r_if
c_cond
(paren
id|dir_entry
op_ge
l_int|1024
)paren
id|dir_entry
op_assign
id|FIRST_VM_PAGE
op_rshift
l_int|10
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|task
(braket
id|dir_entry
op_rshift
l_int|4
)braket
)paren
)paren
(brace
id|counter
op_sub_assign
l_int|1024
suffix:semicolon
id|dir_entry
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
(paren
id|pg_table
op_assign
id|pg_dir
(braket
id|dir_entry
)braket
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|pg_table
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bad page-table at pg_dir[%d]: %08x&bslash;n&bslash;r&quot;
comma
id|dir_entry
comma
id|pg_table
)paren
suffix:semicolon
id|pg_dir
(braket
id|dir_entry
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|counter
op_sub_assign
l_int|1024
suffix:semicolon
id|dir_entry
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
id|counter
OL
l_int|0
)paren
r_goto
id|no_swap
suffix:semicolon
id|counter
op_decrement
suffix:semicolon
id|page_entry
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|page_entry
op_ge
l_int|1024
)paren
(brace
id|page_entry
op_assign
op_minus
l_int|1
suffix:semicolon
id|dir_entry
op_increment
suffix:semicolon
r_goto
id|check_dir
suffix:semicolon
)brace
r_if
c_cond
(paren
id|try_to_swap_out
c_func
(paren
id|page_entry
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
id|p-&gt;rss
op_decrement
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_goto
id|check_table
suffix:semicolon
id|no_swap
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Out of swap-memory&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Get physical address of first (actually last :-) free page, and mark it&n; * used. If no free pages left, return 0.&n; */
DECL|function|get_free_page
r_int
r_int
id|get_free_page
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
id|repeat
suffix:colon
id|__asm__
c_func
(paren
l_string|&quot;std ; repne ; scasb&bslash;n&bslash;t&quot;
l_string|&quot;jne 1f&bslash;n&bslash;t&quot;
l_string|&quot;movb $1,1(%%edi)&bslash;n&bslash;t&quot;
l_string|&quot;sall $12,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;addl %2,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;movl %%ecx,%%edx&bslash;n&bslash;t&quot;
l_string|&quot;movl $1024,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;leal 4092(%%edx),%%edi&bslash;n&bslash;t&quot;
l_string|&quot;rep ; stosl&bslash;n&bslash;t&quot;
l_string|&quot;movl %%edx,%%eax&bslash;n&quot;
l_string|&quot;1:&bslash;tcld&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;i&quot;
(paren
id|LOW_MEM
)paren
comma
l_string|&quot;c&quot;
(paren
id|PAGING_PAGES
)paren
comma
l_string|&quot;D&quot;
(paren
id|mem_map
op_plus
id|PAGING_PAGES
op_minus
l_int|1
)paren
suffix:colon
l_string|&quot;di&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ge
id|HIGH_MEMORY
)paren
r_goto
id|repeat
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_logical_and
id|result
OL
id|LOW_MEM
)paren
op_logical_or
(paren
id|result
op_amp
l_int|0xfff
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;weird result: %08x&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|result
op_logical_and
id|swap_out
c_func
(paren
)paren
)paren
r_goto
id|repeat
suffix:semicolon
r_return
id|result
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
id|inode
op_star
id|swap_inode
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|swap_inode
op_assign
id|namei
c_func
(paren
id|specialfile
)paren
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|swap_file
op_logical_or
id|swap_device
op_logical_or
id|swap_bitmap
)paren
(brace
id|iput
c_func
(paren
id|swap_inode
)paren
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
id|swap_device
op_assign
id|swap_inode-&gt;i_rdev
suffix:semicolon
id|iput
c_func
(paren
id|swap_inode
)paren
suffix:semicolon
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
id|swap_file
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|swap_bitmap
op_assign
(paren
r_char
op_star
)paren
id|get_free_page
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|swap_bitmap
)paren
(brace
id|iput
c_func
(paren
id|swap_file
)paren
suffix:semicolon
id|swap_device
op_assign
l_int|0
suffix:semicolon
id|swap_file
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Unable to start swapping: out of memory :-)&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|read_swap_page
c_func
(paren
l_int|0
comma
id|swap_bitmap
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
id|swap_bitmap
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
id|swap_bitmap
)paren
suffix:semicolon
id|iput
c_func
(paren
id|swap_file
)paren
suffix:semicolon
id|swap_device
op_assign
l_int|0
suffix:semicolon
id|swap_file
op_assign
l_int|NULL
suffix:semicolon
id|swap_bitmap
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|swap_bitmap
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
id|swap_bitmap
comma
id|i
)paren
)paren
id|j
op_increment
suffix:semicolon
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
id|swap_bitmap
)paren
suffix:semicolon
id|iput
c_func
(paren
id|swap_file
)paren
suffix:semicolon
id|swap_device
op_assign
l_int|0
suffix:semicolon
id|swap_file
op_assign
l_int|NULL
suffix:semicolon
id|swap_bitmap
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Adding Swap: %d pages (%d bytes) swap-space&bslash;n&bslash;r&quot;
comma
id|j
comma
id|j
op_star
l_int|4096
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
