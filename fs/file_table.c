multiline_comment|/*&n; *  linux/fs/file_table.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/*&n; * first_file points to a doubly linked list of all file structures in&n; *            the system.&n; * nr_files   holds the length of this list.&n; */
DECL|variable|first_file
r_struct
id|file
op_star
id|first_file
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|nr_files
r_int
id|nr_files
op_assign
l_int|0
suffix:semicolon
DECL|variable|max_files
r_int
id|max_files
op_assign
id|NR_FILE
suffix:semicolon
multiline_comment|/*&n; * Insert a new file structure at the head of the list of available ones.&n; */
DECL|function|insert_file_free
r_static
r_inline
r_void
id|insert_file_free
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
id|file-&gt;f_count
op_assign
l_int|0
suffix:semicolon
id|file-&gt;f_next
op_assign
id|first_file
suffix:semicolon
id|file-&gt;f_prev
op_assign
id|first_file-&gt;f_prev
suffix:semicolon
id|file-&gt;f_next-&gt;f_prev
op_assign
id|file
suffix:semicolon
id|file-&gt;f_prev-&gt;f_next
op_assign
id|file
suffix:semicolon
id|first_file
op_assign
id|file
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove a file structure from the list of available ones.&n; */
DECL|function|remove_file_free
r_static
r_inline
r_void
id|remove_file_free
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
id|first_file
op_eq
id|file
)paren
id|first_file
op_assign
id|first_file-&gt;f_next
suffix:semicolon
id|file-&gt;f_next-&gt;f_prev
op_assign
id|file-&gt;f_prev
suffix:semicolon
id|file-&gt;f_prev-&gt;f_next
op_assign
id|file-&gt;f_next
suffix:semicolon
id|file-&gt;f_next
op_assign
id|file-&gt;f_prev
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Insert a file structure at the end of the list of available ones.&n; */
DECL|function|put_last_free
r_static
r_inline
r_void
id|put_last_free
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
id|file-&gt;f_prev
op_assign
id|first_file-&gt;f_prev
suffix:semicolon
id|file-&gt;f_prev-&gt;f_next
op_assign
id|file
suffix:semicolon
id|file-&gt;f_next
op_assign
id|first_file
suffix:semicolon
id|file-&gt;f_next-&gt;f_prev
op_assign
id|file
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate a new memory page for file structures and&n; * insert the new structures into the global list.&n; * Returns 0, if there is no more memory, 1 otherwise.&n; */
DECL|function|grow_files
r_static
r_int
id|grow_files
c_func
(paren
r_void
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * We don&squot;t have to clear the page because we only look into&n;&t; * f_count, f_prev and f_next and they get initialized in&n;&t; * insert_file_free.  The rest of the file structure is cleared&n;&t; * by get_empty_filp before it is returned.&n;&t; */
id|file
op_assign
(paren
r_struct
id|file
op_star
)paren
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
id|file
)paren
r_return
l_int|0
suffix:semicolon
id|nr_files
op_add_assign
id|i
op_assign
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_struct
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|first_file
)paren
id|file-&gt;f_count
op_assign
l_int|0
comma
id|file-&gt;f_next
op_assign
id|file-&gt;f_prev
op_assign
id|first_file
op_assign
id|file
op_increment
comma
id|i
op_decrement
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
suffix:semicolon
id|i
op_decrement
)paren
id|insert_file_free
c_func
(paren
id|file
op_increment
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|file_table_init
r_int
r_int
id|file_table_init
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_return
id|start
suffix:semicolon
)brace
multiline_comment|/*&n; * Find an unused file structure and return a pointer to it.&n; * Returns NULL, if there are no more free file structures or&n; * we run out of memory.&n; */
DECL|function|get_empty_filp
r_struct
id|file
op_star
id|get_empty_filp
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|file
op_star
id|f
suffix:semicolon
multiline_comment|/* if the return is taken, we are in deep trouble */
r_if
c_cond
(paren
op_logical_neg
id|first_file
op_logical_and
op_logical_neg
id|grow_files
c_func
(paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_do
(brace
r_for
c_loop
(paren
id|f
op_assign
id|first_file
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr_files
suffix:semicolon
id|i
op_increment
comma
id|f
op_assign
id|f-&gt;f_next
)paren
r_if
c_cond
(paren
op_logical_neg
id|f-&gt;f_count
)paren
(brace
id|remove_file_free
c_func
(paren
id|f
)paren
suffix:semicolon
id|memset
c_func
(paren
id|f
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|f
)paren
)paren
suffix:semicolon
id|put_last_free
c_func
(paren
id|f
)paren
suffix:semicolon
id|f-&gt;f_count
op_assign
l_int|1
suffix:semicolon
id|f-&gt;f_version
op_assign
op_increment
id|event
suffix:semicolon
r_return
id|f
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|nr_files
OL
id|max_files
op_logical_and
id|grow_files
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_QUOTA
DECL|function|add_dquot_ref
r_void
id|add_dquot_ref
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|type
)paren
(brace
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_int
id|cnt
suffix:semicolon
r_for
c_loop
(paren
id|filp
op_assign
id|first_file
comma
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|nr_files
suffix:semicolon
id|cnt
op_increment
comma
id|filp
op_assign
id|filp-&gt;f_next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|filp-&gt;f_count
op_logical_or
op_logical_neg
id|filp-&gt;f_inode
op_logical_or
id|filp-&gt;f_inode-&gt;i_dev
op_ne
id|dev
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_WRITE
op_logical_and
id|filp-&gt;f_inode-&gt;i_sb-&gt;dq_op
)paren
(brace
id|filp-&gt;f_inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|initialize
c_func
(paren
id|filp-&gt;f_inode
comma
id|type
)paren
suffix:semicolon
id|filp-&gt;f_inode-&gt;i_flags
op_or_assign
id|S_WRITE
suffix:semicolon
)brace
)brace
)brace
DECL|function|reset_dquot_ptrs
r_void
id|reset_dquot_ptrs
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|type
)paren
(brace
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_int
id|cnt
suffix:semicolon
r_for
c_loop
(paren
id|filp
op_assign
id|first_file
comma
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|nr_files
suffix:semicolon
id|cnt
op_increment
comma
id|filp
op_assign
id|filp-&gt;f_next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|filp-&gt;f_count
op_logical_or
op_logical_neg
id|filp-&gt;f_inode
op_logical_or
id|filp-&gt;f_inode-&gt;i_dev
op_ne
id|dev
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|IS_WRITABLE
c_func
(paren
id|filp-&gt;f_inode
)paren
)paren
(brace
id|filp-&gt;f_inode-&gt;i_dquot
(braket
id|type
)braket
op_assign
id|NODQUOT
suffix:semicolon
id|filp-&gt;f_inode-&gt;i_flags
op_and_assign
op_complement
id|S_WRITE
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
eof
