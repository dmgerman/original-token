multiline_comment|/*&n; *  linux/fs/truncate.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
multiline_comment|/*&n; * Truncate has the most races in the whole filesystem: coding it is&n; * a pain in the a**. Especially as I don&squot;t do any locking...&n; *&n; * The code may look a bit weird, but that&squot;s just because I&squot;ve tried to&n; * handle things like file-size changes in a somewhat graceful manner.&n; * Anyway, truncating a file at the same time somebody else writes to it&n; * is likely to result in pretty weird behaviour...&n; *&n; * The new code handles normal truncates (size = 0) as well as the more&n; * general case (size = XXX). I hope.&n; */
DECL|function|trunc_direct
r_static
r_int
id|trunc_direct
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
DECL|macro|DIRECT_BLOCK
mdefine_line|#define DIRECT_BLOCK ((inode-&gt;i_size + 1023) &gt;&gt; 10)
id|repeat
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
id|DIRECT_BLOCK
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
OL
id|DIRECT_BLOCK
)paren
r_goto
id|repeat
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_data
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|result
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|minix_free_block
c_func
(paren
id|inode-&gt;i_dev
comma
id|inode-&gt;i_data
(braket
id|i
)braket
)paren
)paren
id|inode-&gt;i_data
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|trunc_indirect
r_static
r_int
id|trunc_indirect
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|offset
comma
r_int
r_int
op_star
id|p
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
op_star
id|ind
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
DECL|macro|INDIRECT_BLOCK
mdefine_line|#define INDIRECT_BLOCK (DIRECT_BLOCK-offset)
r_if
c_cond
(paren
op_star
id|p
)paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
op_star
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
l_int|0
suffix:semicolon
id|repeat
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
id|INDIRECT_BLOCK
suffix:semicolon
id|i
OL
l_int|512
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|INDIRECT_BLOCK
)paren
r_goto
id|repeat
suffix:semicolon
id|ind
op_assign
id|i
op_plus
(paren
r_int
r_int
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|ind
)paren
r_continue
suffix:semicolon
id|result
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|minix_free_block
c_func
(paren
id|inode-&gt;i_dev
comma
op_star
id|ind
)paren
)paren
op_star
id|ind
op_assign
l_int|0
suffix:semicolon
)brace
id|ind
op_assign
(paren
r_int
r_int
op_star
)paren
id|bh-&gt;b_data
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
l_int|512
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_star
(paren
id|ind
op_increment
)paren
)paren
r_break
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|512
)paren
(brace
id|result
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|minix_free_block
c_func
(paren
id|inode-&gt;i_dev
comma
op_star
id|p
)paren
)paren
op_star
id|p
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|trunc_dindirect
r_static
r_int
id|trunc_dindirect
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
op_star
id|dind
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
DECL|macro|DINDIRECT_BLOCK
mdefine_line|#define DINDIRECT_BLOCK ((DIRECT_BLOCK-(512+7))&gt;&gt;9)
r_if
c_cond
(paren
id|inode-&gt;i_data
(braket
l_int|8
)braket
)paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|inode-&gt;i_data
(braket
l_int|8
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
l_int|0
suffix:semicolon
id|repeat
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
id|DINDIRECT_BLOCK
suffix:semicolon
id|i
OL
l_int|512
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|DINDIRECT_BLOCK
)paren
r_goto
id|repeat
suffix:semicolon
id|dind
op_assign
id|i
op_plus
(paren
r_int
r_int
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|dind
)paren
r_continue
suffix:semicolon
id|result
op_or_assign
id|trunc_indirect
c_func
(paren
id|inode
comma
l_int|7
op_plus
l_int|512
op_plus
(paren
id|i
op_lshift
l_int|9
)paren
comma
id|dind
)paren
suffix:semicolon
)brace
id|dind
op_assign
(paren
r_int
r_int
op_star
)paren
id|bh-&gt;b_data
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
l_int|512
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_star
(paren
id|dind
op_increment
)paren
)paren
r_break
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|512
)paren
(brace
id|result
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|minix_free_block
c_func
(paren
id|inode-&gt;i_dev
comma
id|inode-&gt;i_data
(braket
l_int|8
)braket
)paren
)paren
id|inode-&gt;i_data
(braket
l_int|8
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|minix_truncate
r_void
id|minix_truncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|flag
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_data
(braket
l_int|7
)braket
op_amp
l_int|0xffff0000
)paren
id|printk
c_func
(paren
l_string|&quot;BAD! minix inode has 16 high bits set&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|flag
op_assign
id|trunc_direct
c_func
(paren
id|inode
)paren
suffix:semicolon
id|flag
op_or_assign
id|trunc_indirect
c_func
(paren
id|inode
comma
l_int|7
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|inode-&gt;i_data
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|flag
op_or_assign
id|trunc_dindirect
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|flag
)paren
r_break
suffix:semicolon
id|current-&gt;counter
op_assign
l_int|0
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Called when a inode is released. Note that this is different&n; * from minix_open: open gets called at every open, but release&n; * gets called only when /all/ the files are closed.&n; */
DECL|function|minix_release
r_void
id|minix_release
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
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;minix_release not implemented&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
