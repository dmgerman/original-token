multiline_comment|/*&n; *&t;linux/mm/filemap.c&n; *&n; * Copyright (C) 1994, 1995  Linus Torvalds&n; */
multiline_comment|/*&n; * This file handles the generic file mmap semantics used by&n; * most &quot;normal&quot; filesystems (but you don&squot;t /have/ to use this:&n; * the NFS filesystem does this differently, for example)&n; */
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*&n; * Shared mappings implemented 30.11.1994. It&squot;s not fully working yet,&n; * though.&n; *&n; * Shared mappings now work. 15.8.1995  Bruno.&n; */
DECL|variable|page_cache_size
r_int
r_int
id|page_cache_size
op_assign
l_int|0
suffix:semicolon
DECL|variable|page_hash_table
r_struct
id|page
op_star
id|page_hash_table
(braket
id|PAGE_HASH_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n; * Simple routines for both non-shared and shared mappings.&n; */
DECL|function|invalidate_inode_pages
r_void
id|invalidate_inode_pages
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|start
)paren
(brace
r_struct
id|page
op_star
op_star
id|p
op_assign
op_amp
id|inode-&gt;i_pages
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_while
c_loop
(paren
(paren
id|page
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
r_int
id|offset
op_assign
id|page-&gt;offset
suffix:semicolon
multiline_comment|/* page wholly truncated - free it */
r_if
c_cond
(paren
id|offset
op_ge
id|start
)paren
(brace
id|inode-&gt;i_nrpages
op_decrement
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|p
op_assign
id|page-&gt;next
)paren
op_ne
l_int|NULL
)paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|prev
op_assign
id|page-&gt;prev
suffix:semicolon
id|page-&gt;dirty
op_assign
l_int|0
suffix:semicolon
id|page-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|page-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|remove_page_from_hash_queue
c_func
(paren
id|page
)paren
suffix:semicolon
id|page-&gt;inode
op_assign
l_int|NULL
suffix:semicolon
id|free_page
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|p
op_assign
op_amp
id|page-&gt;next
suffix:semicolon
id|offset
op_assign
id|start
op_minus
id|offset
suffix:semicolon
multiline_comment|/* partial truncate, clear end of page */
r_if
c_cond
(paren
id|offset
OL
id|PAGE_SIZE
)paren
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|offset
op_plus
id|page_address
c_func
(paren
id|page
)paren
)paren
comma
l_int|0
comma
id|PAGE_SIZE
op_minus
id|offset
)paren
suffix:semicolon
)brace
)brace
DECL|function|shrink_mmap
r_int
id|shrink_mmap
c_func
(paren
r_int
id|priority
comma
r_int
r_int
id|limit
)paren
(brace
r_static
r_int
id|clock
op_assign
l_int|0
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
id|limit
OG
id|high_memory
)paren
id|limit
op_assign
id|high_memory
suffix:semicolon
id|limit
op_assign
id|MAP_NR
c_func
(paren
id|limit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clock
op_ge
id|limit
)paren
id|clock
op_assign
l_int|0
suffix:semicolon
id|priority
op_assign
(paren
id|limit
op_lshift
l_int|2
)paren
op_rshift
id|priority
suffix:semicolon
id|page
op_assign
id|mem_map
op_plus
id|clock
suffix:semicolon
r_while
c_loop
(paren
id|priority
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|page-&gt;inode
)paren
(brace
r_int
id|age
op_assign
id|page-&gt;age
suffix:semicolon
multiline_comment|/* if the page is shared, we juvenate it */
r_if
c_cond
(paren
id|page-&gt;count
op_ne
l_int|1
)paren
id|age
op_or_assign
id|PAGE_AGE_VALUE
op_lshift
l_int|1
suffix:semicolon
id|page-&gt;age
op_assign
id|age
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|age
op_le
id|PAGE_AGE_VALUE
op_div
l_int|2
)paren
(brace
id|remove_page_from_hash_queue
c_func
(paren
id|page
)paren
suffix:semicolon
id|remove_page_from_inode_queue
c_func
(paren
id|page
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|page
op_increment
suffix:semicolon
id|clock
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|clock
op_ge
id|limit
)paren
(brace
id|clock
op_assign
l_int|0
suffix:semicolon
id|page
op_assign
id|mem_map
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called from try_to_swap_out() when we try to egt rid of some&n; * pages..  If we&squot;re unmapping the last occurrence of this page, we also&n; * free it from the page hash-queues etc, as we don&squot;t want to keep it&n; * in-core unnecessarily.&n; */
DECL|function|page_unuse
r_int
r_int
id|page_unuse
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_struct
id|page
op_star
id|p
op_assign
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|page
)paren
suffix:semicolon
r_int
id|count
op_assign
id|p-&gt;count
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ne
l_int|2
)paren
r_return
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;inode
)paren
r_return
id|count
suffix:semicolon
id|remove_page_from_hash_queue
c_func
(paren
id|p
)paren
suffix:semicolon
id|remove_page_from_inode_queue
c_func
(paren
id|p
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
multiline_comment|/*&n; * Update a page cache copy, when we&squot;re doing a &quot;write()&quot; system call&n; * See also &quot;update_vm_cache()&quot;.&n; */
DECL|function|update_vm_cache
r_void
id|update_vm_cache
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|pos
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|page
op_assign
id|find_page
c_func
(paren
id|inode
comma
id|pos
op_amp
id|PAGE_MASK
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
id|addr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;uptodate
)paren
id|sleep_on
c_func
(paren
op_amp
id|page-&gt;wait
)paren
suffix:semicolon
id|addr
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
(paren
id|pos
op_amp
op_complement
id|PAGE_MASK
)paren
op_plus
id|addr
)paren
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Find a cached page and wait for it to become up-to-date, return&n; * the page address.&n; *&n; * If no cached page can be found, create one using the supplied&n; * new page instead (and return zero to indicate that we used the&n; * supplied page in doing so).&n; */
DECL|function|fill_page
r_static
r_int
r_int
id|fill_page
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|newpage
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|page
op_assign
id|find_page
c_func
(paren
id|inode
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;uptodate
)paren
id|sleep_on
c_func
(paren
op_amp
id|page-&gt;wait
)paren
suffix:semicolon
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|page
op_assign
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|newpage
)paren
suffix:semicolon
id|page-&gt;count
op_increment
suffix:semicolon
id|page-&gt;uptodate
op_assign
l_int|0
suffix:semicolon
id|page-&gt;error
op_assign
l_int|0
suffix:semicolon
id|page-&gt;offset
op_assign
id|offset
suffix:semicolon
id|add_page_to_inode_queue
c_func
(paren
id|inode
comma
id|page
)paren
suffix:semicolon
id|add_page_to_hash_queue
c_func
(paren
id|inode
comma
id|page
)paren
suffix:semicolon
id|inode-&gt;i_op
op_member_access_from_pointer
id|readpage
c_func
(paren
id|inode
comma
id|page
)paren
suffix:semicolon
id|page-&gt;uptodate
op_assign
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|page-&gt;wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to read ahead in the file. &quot;page_cache&quot; is a potentially free page&n; * that we could use for the cache (if it is 0 we can try to create one,&n; * this is all overlapped with the IO on the previous page finishing anyway)&n; */
DECL|function|try_to_read_ahead
r_static
r_int
r_int
id|try_to_read_ahead
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|page_cache
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|page_cache
)paren
id|page_cache
op_assign
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
id|offset
op_assign
(paren
id|offset
op_plus
id|PAGE_SIZE
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
multiline_comment|/*&n;&t; * read-ahead is not implemented yet, but this is&n;&t; * where we should start..&n;&t; */
r_return
id|page_cache
suffix:semicolon
)brace
multiline_comment|/*&n; * This is a generic file read routine, and uses the&n; * inode-&gt;i_op-&gt;readpage() function for the actual low-level&n; * stuff.&n; */
DECL|function|generic_file_read
r_int
id|generic_file_read
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|read
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|pos
suffix:semicolon
r_int
r_int
id|page_cache
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|pos
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_do
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
r_int
id|offset
comma
id|addr
comma
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|inode-&gt;i_size
)paren
r_break
suffix:semicolon
id|offset
op_assign
id|pos
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|nr
op_assign
id|PAGE_SIZE
op_minus
id|offset
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Try to find the data in the page cache..&n;&t;&t; */
id|page
op_assign
id|find_page
c_func
(paren
id|inode
comma
id|pos
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
r_goto
id|found_page
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Ok, it wasn&squot;t cached, so we need to create a new&n;&t;&t; * page..&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|page_cache
)paren
(brace
id|page_cache
op_assign
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page_cache
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|read
)paren
id|read
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * That could have slept, so we need to check again..&n;&t;&t; */
r_if
c_cond
(paren
id|pos
op_ge
id|inode-&gt;i_size
)paren
r_break
suffix:semicolon
id|page
op_assign
id|find_page
c_func
(paren
id|inode
comma
id|pos
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
r_goto
id|found_page
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Ok, add the new page to the hash-queues...&n;&t;&t; */
id|page
op_assign
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|page_cache
)paren
suffix:semicolon
id|page_cache
op_assign
l_int|0
suffix:semicolon
id|page-&gt;count
op_increment
suffix:semicolon
id|page-&gt;uptodate
op_assign
l_int|0
suffix:semicolon
id|page-&gt;error
op_assign
l_int|0
suffix:semicolon
id|page-&gt;offset
op_assign
id|pos
op_amp
id|PAGE_MASK
suffix:semicolon
id|add_page_to_inode_queue
c_func
(paren
id|inode
comma
id|page
)paren
suffix:semicolon
id|add_page_to_hash_queue
c_func
(paren
id|inode
comma
id|page
)paren
suffix:semicolon
multiline_comment|/* &n;&t;&t; * And start IO on it..&n;&t;&t; * (this should be asynchronous, but currently isn&squot;t)&n;&t;&t; */
id|inode-&gt;i_op
op_member_access_from_pointer
id|readpage
c_func
(paren
id|inode
comma
id|page
)paren
suffix:semicolon
id|found_page
suffix:colon
id|addr
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
OG
id|count
)paren
id|nr
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;uptodate
)paren
(brace
id|page_cache
op_assign
id|try_to_read_ahead
c_func
(paren
id|inode
comma
id|offset
comma
id|page_cache
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;uptodate
)paren
id|sleep_on
c_func
(paren
op_amp
id|page-&gt;wait
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr
OG
id|inode-&gt;i_size
op_minus
id|pos
)paren
id|nr
op_assign
id|inode-&gt;i_size
op_minus
id|pos
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|buf
comma
(paren
r_void
op_star
)paren
(paren
id|addr
op_plus
id|offset
)paren
comma
id|nr
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|addr
)paren
suffix:semicolon
id|buf
op_add_assign
id|nr
suffix:semicolon
id|pos
op_add_assign
id|nr
suffix:semicolon
id|read
op_add_assign
id|nr
suffix:semicolon
id|count
op_sub_assign
id|nr
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
suffix:semicolon
id|filp-&gt;f_pos
op_assign
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|page_cache
)paren
id|free_page
c_func
(paren
id|page_cache
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
(brace
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|read
suffix:semicolon
)brace
multiline_comment|/*&n; * Semantics for shared and private memory areas are different past the end&n; * of the file. A shared mapping past the last page of the file is an error&n; * and results in a SIBGUS, while a private mapping just maps in a zero page.&n; */
DECL|function|filemap_nopage
r_static
r_int
r_int
id|filemap_nopage
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
id|address
comma
r_int
r_int
id|page
comma
r_int
id|no_share
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|area-&gt;vm_inode
suffix:semicolon
r_int
r_int
id|new_page
suffix:semicolon
id|offset
op_assign
(paren
id|address
op_amp
id|PAGE_MASK
)paren
op_minus
id|area-&gt;vm_start
op_plus
id|area-&gt;vm_offset
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|inode-&gt;i_size
op_logical_and
(paren
id|area-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
op_logical_and
id|area-&gt;vm_mm
op_eq
id|current-&gt;mm
)paren
id|send_sig
c_func
(paren
id|SIGBUS
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|new_page
op_assign
id|fill_page
c_func
(paren
id|inode
comma
id|offset
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_page
)paren
(brace
r_if
c_cond
(paren
id|no_share
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|page
comma
(paren
r_void
op_star
)paren
id|new_page
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|new_page
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|new_page
suffix:semicolon
)brace
r_if
c_cond
(paren
id|no_share
)paren
(brace
id|new_page
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
id|new_page
)paren
(brace
id|oom
c_func
(paren
id|current
)paren
suffix:semicolon
id|new_page
op_assign
id|pte_page
c_func
(paren
id|BAD_PAGE
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|new_page
comma
(paren
r_void
op_star
)paren
id|page
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|page
op_assign
id|new_page
suffix:semicolon
)brace
r_return
id|page
suffix:semicolon
)brace
multiline_comment|/*&n; * Tries to write a shared mapped page to its backing store. May return -EIO&n; * if the disk is full.&n; */
DECL|function|filemap_write_page
r_static
r_int
id|filemap_write_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|page
)paren
(brace
r_int
id|old_fs
suffix:semicolon
r_int
r_int
id|size
comma
id|result
suffix:semicolon
r_struct
id|file
id|file
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|bh
op_assign
id|buffer_pages
(braket
id|MAP_NR
c_func
(paren
id|page
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
multiline_comment|/* whee.. just mark the buffer heads dirty */
r_struct
id|buffer_head
op_star
id|tmp
op_assign
id|bh
suffix:semicolon
r_do
(brace
id|mark_buffer_dirty
c_func
(paren
id|tmp
comma
l_int|0
)paren
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;b_this_page
suffix:semicolon
)brace
r_while
c_loop
(paren
id|tmp
op_ne
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|inode
op_assign
id|vma-&gt;vm_inode
suffix:semicolon
id|file.f_op
op_assign
id|inode-&gt;i_op-&gt;default_file_ops
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file.f_op-&gt;write
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|size
op_assign
id|offset
op_plus
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/* refuse to extend file size.. */
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|size
OG
id|inode-&gt;i_size
)paren
id|size
op_assign
id|inode-&gt;i_size
suffix:semicolon
multiline_comment|/* Ho humm.. We should have tested for this earlier */
r_if
c_cond
(paren
id|size
OL
id|offset
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|size
op_sub_assign
id|offset
suffix:semicolon
id|file.f_mode
op_assign
l_int|3
suffix:semicolon
id|file.f_flags
op_assign
l_int|0
suffix:semicolon
id|file.f_count
op_assign
l_int|1
suffix:semicolon
id|file.f_inode
op_assign
id|inode
suffix:semicolon
id|file.f_pos
op_assign
id|offset
suffix:semicolon
id|file.f_reada
op_assign
l_int|0
suffix:semicolon
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|result
op_assign
id|file.f_op
op_member_access_from_pointer
id|write
c_func
(paren
id|inode
comma
op_amp
id|file
comma
(paren
r_const
r_char
op_star
)paren
id|page
comma
id|size
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|size
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Swapping to a shared file: while we&squot;re busy writing out the page&n; * (and the page still exists in memory), we save the page information&n; * in the page table, so that &quot;filemap_swapin()&quot; can re-use the page&n; * immediately if it is called while we&squot;re busy swapping it out..&n; *&n; * Once we&squot;ve written it all out, we mark the page entry &quot;empty&quot;, which&n; * will result in a normal page-in (instead of a swap-in) from the now&n; * up-to-date disk file.&n; */
DECL|function|filemap_swapout
r_int
id|filemap_swapout
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|offset
comma
id|pte_t
op_star
id|page_table
)paren
(brace
r_int
id|error
suffix:semicolon
r_int
r_int
id|page
op_assign
id|pte_page
c_func
(paren
op_star
id|page_table
)paren
suffix:semicolon
r_int
r_int
id|entry
op_assign
id|SWP_ENTRY
c_func
(paren
id|SHM_SWP_TYPE
comma
id|MAP_NR
c_func
(paren
id|page
)paren
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
multiline_comment|/* Yuck, perhaps a slightly modified swapout parameter set? */
id|invalidate_page
c_func
(paren
id|vma
comma
(paren
id|offset
op_plus
id|vma-&gt;vm_start
op_minus
id|vma-&gt;vm_offset
)paren
)paren
suffix:semicolon
id|error
op_assign
id|filemap_write_page
c_func
(paren
id|vma
comma
id|offset
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
op_star
id|page_table
)paren
op_eq
id|entry
)paren
id|pte_clear
c_func
(paren
id|page_table
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * filemap_swapin() is called only if we have something in the page&n; * tables that is non-zero (but not present), which we know to be the&n; * page index of a page that is busy being swapped out (see above).&n; * So we just use it directly..&n; */
DECL|function|filemap_swapin
r_static
id|pte_t
id|filemap_swapin
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|entry
)paren
(brace
r_int
r_int
id|page
op_assign
id|SWP_OFFSET
c_func
(paren
id|entry
)paren
suffix:semicolon
id|mem_map
(braket
id|page
)braket
dot
id|count
op_increment
suffix:semicolon
id|page
op_assign
(paren
id|page
op_lshift
id|PAGE_SHIFT
)paren
op_plus
id|PAGE_OFFSET
suffix:semicolon
r_return
id|mk_pte
c_func
(paren
id|page
comma
id|vma-&gt;vm_page_prot
)paren
suffix:semicolon
)brace
DECL|function|filemap_sync_pte
r_static
r_inline
r_int
id|filemap_sync_pte
c_func
(paren
id|pte_t
op_star
id|ptep
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
r_int
r_int
id|flags
)paren
(brace
id|pte_t
id|pte
op_assign
op_star
id|ptep
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MS_INVALIDATE
)paren
)paren
(brace
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
r_return
l_int|0
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|pte_mkclean
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
id|invalidate_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
id|page
op_assign
id|pte_page
c_func
(paren
id|pte
)paren
suffix:semicolon
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|page
)paren
)braket
dot
id|count
op_increment
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|pte_none
c_func
(paren
id|pte
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|pte_clear
c_func
(paren
id|ptep
)paren
suffix:semicolon
id|invalidate_page
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
op_logical_neg
id|pte_present
c_func
(paren
id|pte
)paren
)paren
(brace
id|swap_free
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
op_logical_neg
id|pte_dirty
c_func
(paren
id|pte
)paren
op_logical_or
id|flags
op_eq
id|MS_INVALIDATE
)paren
(brace
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|error
op_assign
id|filemap_write_page
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
id|error
suffix:semicolon
)brace
DECL|function|filemap_sync_pte_range
r_static
r_inline
r_int
id|filemap_sync_pte_range
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|flags
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
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
id|pmd
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;filemap_sync_pte_range: bad pmd (%08lx)&bslash;n&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd
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
id|pmd
comma
id|address
)paren
suffix:semicolon
id|offset
op_add_assign
id|address
op_amp
id|PMD_MASK
suffix:semicolon
id|address
op_and_assign
op_complement
id|PMD_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PMD_SIZE
)paren
id|end
op_assign
id|PMD_SIZE
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|error
op_or_assign
id|filemap_sync_pte
c_func
(paren
id|pte
comma
id|vma
comma
id|address
op_plus
id|offset
comma
id|flags
)paren
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
id|error
suffix:semicolon
)brace
DECL|function|filemap_sync_pmd_range
r_static
r_inline
r_int
id|filemap_sync_pmd_range
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|flags
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
r_int
id|offset
comma
id|end
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgd
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
id|pgd
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;filemap_sync_pmd_range: bad pgd (%08lx)&bslash;n&quot;
comma
id|pgd_val
c_func
(paren
op_star
id|pgd
)paren
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|pgd
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
id|pgd
comma
id|address
)paren
suffix:semicolon
id|offset
op_assign
id|address
op_amp
id|PMD_MASK
suffix:semicolon
id|address
op_and_assign
op_complement
id|PMD_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PGDIR_SIZE
)paren
id|end
op_assign
id|PGDIR_SIZE
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|error
op_or_assign
id|filemap_sync_pte_range
c_func
(paren
id|pmd
comma
id|address
comma
id|end
op_minus
id|address
comma
id|vma
comma
id|offset
comma
id|flags
)paren
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
id|error
suffix:semicolon
)brace
DECL|function|filemap_sync
r_static
r_int
id|filemap_sync
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
id|size
comma
r_int
r_int
id|flags
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
r_int
r_int
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|dir
op_assign
id|pgd_offset
c_func
(paren
id|current-&gt;mm
comma
id|address
)paren
suffix:semicolon
r_while
c_loop
(paren
id|address
OL
id|end
)paren
(brace
id|error
op_or_assign
id|filemap_sync_pmd_range
c_func
(paren
id|dir
comma
id|address
comma
id|end
op_minus
id|address
comma
id|vma
comma
id|flags
)paren
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
id|dir
op_increment
suffix:semicolon
)brace
id|invalidate_range
c_func
(paren
id|vma-&gt;vm_mm
comma
id|end
op_minus
id|size
comma
id|end
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * This handles (potentially partial) area unmaps..&n; */
DECL|function|filemap_unmap
r_static
r_void
id|filemap_unmap
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|start
comma
r_int
id|len
)paren
(brace
id|filemap_sync
c_func
(paren
id|vma
comma
id|start
comma
id|len
comma
id|MS_ASYNC
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Shared mappings need to be able to do the right thing at&n; * close/unmap/sync. They will also use the private file as&n; * backing-store for swapping..&n; */
DECL|variable|file_shared_mmap
r_static
r_struct
id|vm_operations_struct
id|file_shared_mmap
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* no special open */
l_int|NULL
comma
multiline_comment|/* no special close */
id|filemap_unmap
comma
multiline_comment|/* unmap - we need to sync the pages */
l_int|NULL
comma
multiline_comment|/* no special protect */
id|filemap_sync
comma
multiline_comment|/* sync */
l_int|NULL
comma
multiline_comment|/* advise */
id|filemap_nopage
comma
multiline_comment|/* nopage */
l_int|NULL
comma
multiline_comment|/* wppage */
id|filemap_swapout
comma
multiline_comment|/* swapout */
id|filemap_swapin
comma
multiline_comment|/* swapin */
)brace
suffix:semicolon
multiline_comment|/*&n; * Private mappings just need to be able to load in the map.&n; *&n; * (This is actually used for shared mappings as well, if we&n; * know they can&squot;t ever get write permissions..)&n; */
DECL|variable|file_private_mmap
r_static
r_struct
id|vm_operations_struct
id|file_private_mmap
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* close */
l_int|NULL
comma
multiline_comment|/* unmap */
l_int|NULL
comma
multiline_comment|/* protect */
l_int|NULL
comma
multiline_comment|/* sync */
l_int|NULL
comma
multiline_comment|/* advise */
id|filemap_nopage
comma
multiline_comment|/* nopage */
l_int|NULL
comma
multiline_comment|/* wppage */
l_int|NULL
comma
multiline_comment|/* swapout */
l_int|NULL
comma
multiline_comment|/* swapin */
)brace
suffix:semicolon
multiline_comment|/* This is used for a general mmap of a disk file */
DECL|function|generic_mmap
r_int
id|generic_mmap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|vm_operations_struct
op_star
id|ops
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
op_logical_and
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_MAYWRITE
)paren
)paren
(brace
id|ops
op_assign
op_amp
id|file_shared_mmap
suffix:semicolon
multiline_comment|/* share_page() can only guarantee proper page sharing if&n;&t;&t; * the offsets are all page aligned. */
r_if
c_cond
(paren
id|vma-&gt;vm_offset
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
id|ops
op_assign
op_amp
id|file_private_mmap
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_offset
op_amp
(paren
id|inode-&gt;i_sb-&gt;s_blocksize
op_minus
l_int|1
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_sb
op_logical_or
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_op
op_logical_or
op_logical_neg
id|inode-&gt;i_op-&gt;readpage
)paren
r_return
op_minus
id|ENOEXEC
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
(brace
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
id|vma-&gt;vm_inode
op_assign
id|inode
suffix:semicolon
id|inode-&gt;i_count
op_increment
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
id|ops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The msync() system call.&n; */
DECL|function|msync_interval
r_static
r_int
id|msync_interval
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|vma-&gt;vm_inode
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_ops-&gt;sync
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|vma-&gt;vm_ops
op_member_access_from_pointer
id|sync
c_func
(paren
id|vma
comma
id|start
comma
id|end
op_minus
id|start
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MS_SYNC
)paren
r_return
id|file_fsync
c_func
(paren
id|vma-&gt;vm_inode
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_msync
id|asmlinkage
r_int
id|sys_msync
c_func
(paren
r_int
r_int
id|start
comma
r_int
id|len
comma
r_int
id|flags
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
id|unmapped_error
comma
id|error
suffix:semicolon
r_if
c_cond
(paren
id|start
op_amp
op_complement
id|PAGE_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|len
op_assign
(paren
id|len
op_plus
op_complement
id|PAGE_MASK
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|end
OL
id|start
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
op_complement
(paren
id|MS_ASYNC
op_or
id|MS_INVALIDATE
op_or
id|MS_SYNC
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|end
op_eq
id|start
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If the interval [start,end) covers some unmapped address ranges,&n;&t; * just ignore them, but return -EFAULT at the end.&n;&t; */
id|vma
op_assign
id|find_vma
c_func
(paren
id|current
comma
id|start
)paren
suffix:semicolon
id|unmapped_error
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
multiline_comment|/* Still start &lt; end. */
r_if
c_cond
(paren
op_logical_neg
id|vma
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* Here start &lt; vma-&gt;vm_end. */
r_if
c_cond
(paren
id|start
OL
id|vma-&gt;vm_start
)paren
(brace
id|unmapped_error
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|start
op_assign
id|vma-&gt;vm_start
suffix:semicolon
)brace
multiline_comment|/* Here vma-&gt;vm_start &lt;= start &lt; vma-&gt;vm_end. */
r_if
c_cond
(paren
id|end
op_le
id|vma-&gt;vm_end
)paren
(brace
r_if
c_cond
(paren
id|start
OL
id|end
)paren
(brace
id|error
op_assign
id|msync_interval
c_func
(paren
id|vma
comma
id|start
comma
id|end
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
)brace
r_return
id|unmapped_error
suffix:semicolon
)brace
multiline_comment|/* Here vma-&gt;vm_start &lt;= start &lt; vma-&gt;vm_end &lt; end. */
id|error
op_assign
id|msync_interval
c_func
(paren
id|vma
comma
id|start
comma
id|vma-&gt;vm_end
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|start
op_assign
id|vma-&gt;vm_end
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
suffix:semicolon
)brace
)brace
eof
