multiline_comment|/*&n; * linux/drivers/char/vc_screen.c&n; *&n; * Provide access to virtual console memory.&n; * /dev/vcs0: the screen as it is being viewed right now (possibly scrolled)&n; * /dev/vcsN: the screen of /dev/ttyN (1 &lt;= N &lt;= 63)&n; *            [minor: N]&n; *&n; * /dev/vcsaN: idem, but including attributes, and prefixed with&n; *&t;the 4 bytes lines,columns,x,y (as screendump used to give).&n; *&t;Attribute/character pair is in native endianity.&n; *            [minor: N+128]&n; *&n; * This replaces screendump and part of selection, so that the system&n; * administrator can control access using file system permissions.&n; *&n; * aeb@cwi.nl - efter Friedas begravelse - 950211&n; *&n; * machek@k332.feld.cvut.cz - modified not to send characters to wrong console&n; *&t; - fixed some fatal off-by-one bugs (0-- no longer == -1 -&gt; looping and looping and looping...)&n; *&t; - making it shorter - scr_readw are macros which expand in PRETTY long code&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/console_struct.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;linux/kbd_kern.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|attr
macro_line|#undef attr
DECL|macro|org
macro_line|#undef org
DECL|macro|addr
macro_line|#undef addr
DECL|macro|HEADER_SIZE
mdefine_line|#define HEADER_SIZE&t;4
r_static
r_int
DECL|function|vcs_size
id|vcs_size
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|size
suffix:semicolon
r_int
id|currcons
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_amp
l_int|127
suffix:semicolon
r_if
c_cond
(paren
id|currcons
op_eq
l_int|0
)paren
id|currcons
op_assign
id|fg_console
suffix:semicolon
r_else
id|currcons
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vc_cons_allocated
c_func
(paren
id|currcons
)paren
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|size
op_assign
id|video_num_lines
op_star
id|video_num_columns
suffix:semicolon
r_if
c_cond
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_amp
l_int|128
)paren
id|size
op_assign
l_int|2
op_star
id|size
op_plus
id|HEADER_SIZE
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|vcs_lseek
r_static
id|loff_t
id|vcs_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|orig
)paren
(brace
r_int
id|size
op_assign
id|vcs_size
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|orig
)paren
(brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
l_int|2
suffix:colon
id|offset
op_add_assign
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|offset
op_add_assign
id|file-&gt;f_pos
suffix:semicolon
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
template_param
id|size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
r_return
id|file-&gt;f_pos
suffix:semicolon
)brace
multiline_comment|/* We share this temporary buffer with the console write code&n; * so that we can easily avoid touching user space while holding the&n; * console spinlock.&n; */
r_extern
r_char
id|con_buf
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
DECL|macro|CON_BUF_SIZE
mdefine_line|#define CON_BUF_SIZE&t;PAGE_SIZE
r_extern
r_struct
id|semaphore
id|con_buf_sem
suffix:semicolon
r_static
id|ssize_t
DECL|function|vcs_read
id|vcs_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
r_int
id|currcons
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
r_int
id|viewed
comma
id|attr
comma
id|read
suffix:semicolon
r_int
id|col
comma
id|maxcol
suffix:semicolon
r_int
r_int
op_star
id|org
op_assign
l_int|NULL
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
id|down
c_func
(paren
op_amp
id|con_buf_sem
)paren
suffix:semicolon
multiline_comment|/* Select the proper current console and verify&n;&t; * sanity of the situation under the console lock.&n;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|console_lock
)paren
suffix:semicolon
id|attr
op_assign
(paren
id|currcons
op_amp
l_int|128
)paren
suffix:semicolon
id|currcons
op_assign
(paren
id|currcons
op_amp
l_int|127
)paren
suffix:semicolon
r_if
c_cond
(paren
id|currcons
op_eq
l_int|0
)paren
(brace
id|currcons
op_assign
id|fg_console
suffix:semicolon
id|viewed
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|currcons
op_decrement
suffix:semicolon
id|viewed
op_assign
l_int|0
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vc_cons_allocated
c_func
(paren
id|currcons
)paren
)paren
r_goto
id|unlock_out
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_goto
id|unlock_out
suffix:semicolon
id|read
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
r_char
op_star
id|con_buf0
comma
op_star
id|con_buf_start
suffix:semicolon
r_int
id|this_round
comma
id|size
suffix:semicolon
id|ssize_t
id|orig_count
suffix:semicolon
r_int
id|p
op_assign
id|pos
suffix:semicolon
multiline_comment|/* Check whether we are above size each round,&n;&t;&t; * as copy_to_user at the end of this loop&n;&t;&t; * could sleep.&n;&t;&t; */
id|size
op_assign
id|vcs_size
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|size
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|size
op_minus
id|pos
)paren
id|count
op_assign
id|size
op_minus
id|pos
suffix:semicolon
id|this_round
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|this_round
OG
id|CON_BUF_SIZE
)paren
id|this_round
op_assign
id|CON_BUF_SIZE
suffix:semicolon
multiline_comment|/* Perform the whole read into the local con_buf.&n;&t;&t; * Then we can drop the console spinlock and safely&n;&t;&t; * attempt to move it to userspace.&n;&t;&t; */
id|con_buf_start
op_assign
id|con_buf0
op_assign
id|con_buf
suffix:semicolon
id|orig_count
op_assign
id|this_round
suffix:semicolon
id|maxcol
op_assign
id|video_num_columns
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr
)paren
(brace
id|org
op_assign
id|screen_pos
c_func
(paren
id|currcons
comma
id|p
comma
id|viewed
)paren
suffix:semicolon
id|col
op_assign
id|p
op_mod
id|maxcol
suffix:semicolon
id|p
op_add_assign
id|maxcol
op_minus
id|col
suffix:semicolon
r_while
c_loop
(paren
id|this_round
op_decrement
OG
l_int|0
)paren
(brace
op_star
id|con_buf0
op_increment
op_assign
(paren
id|vcs_scr_readw
c_func
(paren
id|currcons
comma
id|org
op_increment
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|col
op_eq
id|maxcol
)paren
(brace
id|org
op_assign
id|screen_pos
c_func
(paren
id|currcons
comma
id|p
comma
id|viewed
)paren
suffix:semicolon
id|col
op_assign
l_int|0
suffix:semicolon
id|p
op_add_assign
id|maxcol
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|p
OL
id|HEADER_SIZE
)paren
(brace
r_int
id|tmp_count
suffix:semicolon
id|con_buf0
(braket
l_int|0
)braket
op_assign
(paren
r_char
)paren
id|video_num_lines
suffix:semicolon
id|con_buf0
(braket
l_int|1
)braket
op_assign
(paren
r_char
)paren
id|video_num_columns
suffix:semicolon
id|getconsxy
c_func
(paren
id|currcons
comma
id|con_buf0
op_plus
l_int|2
)paren
suffix:semicolon
id|tmp_count
op_assign
id|HEADER_SIZE
op_minus
id|p
suffix:semicolon
r_if
c_cond
(paren
id|tmp_count
OG
id|this_round
)paren
id|tmp_count
op_assign
id|this_round
suffix:semicolon
multiline_comment|/* Advance state pointers and move on. */
id|this_round
op_sub_assign
id|tmp_count
suffix:semicolon
id|con_buf_start
op_add_assign
id|p
suffix:semicolon
id|orig_count
op_sub_assign
id|p
suffix:semicolon
id|p
op_add_assign
id|tmp_count
suffix:semicolon
id|con_buf0
op_assign
id|con_buf
op_plus
id|p
suffix:semicolon
)brace
id|p
op_sub_assign
id|HEADER_SIZE
suffix:semicolon
id|col
op_assign
(paren
id|p
op_div
l_int|2
)paren
op_mod
id|maxcol
suffix:semicolon
r_if
c_cond
(paren
id|this_round
OG
l_int|0
)paren
(brace
r_char
id|tmp_byte
suffix:semicolon
id|org
op_assign
id|screen_pos
c_func
(paren
id|currcons
comma
id|p
op_div
l_int|2
comma
id|viewed
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_amp
l_int|1
)paren
op_logical_and
id|this_round
OG
l_int|0
)paren
(brace
macro_line|#ifdef __BIG_ENDIAN
id|tmp_byte
op_assign
id|vcs_scr_readw
c_func
(paren
id|currcons
comma
id|org
op_increment
)paren
op_amp
l_int|0xff
suffix:semicolon
macro_line|#else
id|tmp_byte
op_assign
id|vcs_scr_readw
c_func
(paren
id|currcons
comma
id|org
op_increment
)paren
op_rshift
l_int|8
suffix:semicolon
macro_line|#endif
op_star
id|con_buf0
op_increment
op_assign
id|tmp_byte
suffix:semicolon
id|this_round
op_decrement
suffix:semicolon
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|col
op_eq
id|maxcol
)paren
(brace
id|org
op_assign
id|screen_pos
c_func
(paren
id|currcons
comma
id|p
op_div
l_int|2
comma
id|viewed
)paren
suffix:semicolon
id|col
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|p
op_div_assign
l_int|2
suffix:semicolon
id|p
op_add_assign
id|maxcol
op_minus
id|col
suffix:semicolon
)brace
r_if
c_cond
(paren
id|this_round
OG
l_int|1
)paren
(brace
r_int
id|tmp_count
op_assign
id|this_round
suffix:semicolon
r_int
r_int
op_star
id|tmp_buf
op_assign
(paren
r_int
r_int
op_star
)paren
id|con_buf0
suffix:semicolon
r_while
c_loop
(paren
id|tmp_count
OG
l_int|1
)paren
(brace
op_star
id|tmp_buf
op_increment
op_assign
id|vcs_scr_readw
c_func
(paren
id|currcons
comma
id|org
op_increment
)paren
suffix:semicolon
id|tmp_count
op_sub_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|col
op_eq
id|maxcol
)paren
(brace
id|org
op_assign
id|screen_pos
c_func
(paren
id|currcons
comma
id|p
comma
id|viewed
)paren
suffix:semicolon
id|col
op_assign
l_int|0
suffix:semicolon
id|p
op_add_assign
id|maxcol
suffix:semicolon
)brace
)brace
multiline_comment|/* Advance pointers, and move on. */
id|this_round
op_assign
id|tmp_count
suffix:semicolon
id|con_buf0
op_assign
(paren
r_char
op_star
)paren
id|tmp_buf
suffix:semicolon
)brace
r_if
c_cond
(paren
id|this_round
OG
l_int|0
)paren
(brace
r_char
id|tmp_byte
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
id|tmp_byte
op_assign
id|vcs_scr_readw
c_func
(paren
id|currcons
comma
id|org
)paren
op_rshift
l_int|8
suffix:semicolon
macro_line|#else
id|tmp_byte
op_assign
id|vcs_scr_readw
c_func
(paren
id|currcons
comma
id|org
)paren
op_amp
l_int|0xff
suffix:semicolon
macro_line|#endif
op_star
id|con_buf0
op_increment
op_assign
id|tmp_byte
suffix:semicolon
)brace
)brace
multiline_comment|/* Finally, temporarily drop the console lock and push&n;&t;&t; * all the data to userspace from our temporary buffer.&n;&t;&t; */
id|spin_unlock_irq
c_func
(paren
op_amp
id|console_lock
)paren
suffix:semicolon
id|ret
op_assign
id|copy_to_user
c_func
(paren
id|buf
comma
id|con_buf_start
comma
id|orig_count
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|console_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|read
op_add_assign
(paren
id|orig_count
op_minus
id|ret
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|buf
op_add_assign
id|orig_count
suffix:semicolon
id|pos
op_add_assign
id|orig_count
suffix:semicolon
id|read
op_add_assign
id|orig_count
suffix:semicolon
id|count
op_sub_assign
id|orig_count
suffix:semicolon
)brace
op_star
id|ppos
op_add_assign
id|read
suffix:semicolon
r_if
c_cond
(paren
id|read
)paren
id|ret
op_assign
id|read
suffix:semicolon
id|unlock_out
suffix:colon
id|spin_unlock_irq
c_func
(paren
op_amp
id|console_lock
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|con_buf_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|vcs_write
id|vcs_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
r_int
id|currcons
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
r_int
id|viewed
comma
id|attr
comma
id|size
comma
id|written
suffix:semicolon
r_char
op_star
id|con_buf0
suffix:semicolon
r_int
id|col
comma
id|maxcol
suffix:semicolon
id|u16
op_star
id|org0
op_assign
l_int|NULL
comma
op_star
id|org
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|down
c_func
(paren
op_amp
id|con_buf_sem
)paren
suffix:semicolon
multiline_comment|/* Select the proper current console and verify&n;&t; * sanity of the situation under the console lock.&n;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|console_lock
)paren
suffix:semicolon
id|attr
op_assign
(paren
id|currcons
op_amp
l_int|128
)paren
suffix:semicolon
id|currcons
op_assign
(paren
id|currcons
op_amp
l_int|127
)paren
suffix:semicolon
r_if
c_cond
(paren
id|currcons
op_eq
l_int|0
)paren
(brace
id|currcons
op_assign
id|fg_console
suffix:semicolon
id|viewed
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|currcons
op_decrement
suffix:semicolon
id|viewed
op_assign
l_int|0
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vc_cons_allocated
c_func
(paren
id|currcons
)paren
)paren
r_goto
id|unlock_out
suffix:semicolon
id|size
op_assign
id|vcs_size
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|pos
template_param
id|size
)paren
r_goto
id|unlock_out
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|size
op_minus
id|pos
)paren
id|count
op_assign
id|size
op_minus
id|pos
suffix:semicolon
id|written
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
r_int
id|this_round
op_assign
id|count
suffix:semicolon
r_int
id|orig_count
suffix:semicolon
r_int
id|p
suffix:semicolon
r_if
c_cond
(paren
id|this_round
OG
id|CON_BUF_SIZE
)paren
id|this_round
op_assign
id|CON_BUF_SIZE
suffix:semicolon
multiline_comment|/* Temporarily drop the console lock so that we can read&n;&t;&t; * in the write data from userspace safely.&n;&t;&t; */
id|spin_unlock_irq
c_func
(paren
op_amp
id|console_lock
)paren
suffix:semicolon
id|ret
op_assign
id|copy_from_user
c_func
(paren
id|con_buf
comma
id|buf
comma
id|this_round
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|console_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|this_round
op_sub_assign
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|this_round
)paren
(brace
multiline_comment|/* Abort loop if no data were copied. Otherwise&n;&t;&t;&t;&t; * fail with -EFAULT.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|written
)paren
r_break
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|unlock_out
suffix:semicolon
)brace
)brace
multiline_comment|/* The vcs_size might have changed while we slept to grab&n;&t;&t; * the user buffer, so recheck.&n;&t;&t; * Return data written up to now on failure.&n;&t;&t; */
id|size
op_assign
id|vcs_size
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|size
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|this_round
OG
id|size
op_minus
id|pos
)paren
id|this_round
op_assign
id|size
op_minus
id|pos
suffix:semicolon
multiline_comment|/* OK, now actually push the write to the console&n;&t;&t; * under the lock using the local kernel buffer.&n;&t;&t; */
id|con_buf0
op_assign
id|con_buf
suffix:semicolon
id|orig_count
op_assign
id|this_round
suffix:semicolon
id|maxcol
op_assign
id|video_num_columns
suffix:semicolon
id|p
op_assign
id|pos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr
)paren
(brace
id|org0
op_assign
id|org
op_assign
id|screen_pos
c_func
(paren
id|currcons
comma
id|p
comma
id|viewed
)paren
suffix:semicolon
id|col
op_assign
id|p
op_mod
id|maxcol
suffix:semicolon
id|p
op_add_assign
id|maxcol
op_minus
id|col
suffix:semicolon
r_while
c_loop
(paren
id|this_round
OG
l_int|0
)paren
(brace
r_int
r_char
id|c
op_assign
op_star
id|con_buf0
op_increment
suffix:semicolon
id|this_round
op_decrement
suffix:semicolon
id|vcs_scr_writew
c_func
(paren
id|currcons
comma
(paren
id|vcs_scr_readw
c_func
(paren
id|currcons
comma
id|org
)paren
op_amp
l_int|0xff00
)paren
op_or
id|c
comma
id|org
)paren
suffix:semicolon
id|org
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|col
op_eq
id|maxcol
)paren
(brace
id|org
op_assign
id|screen_pos
c_func
(paren
id|currcons
comma
id|p
comma
id|viewed
)paren
suffix:semicolon
id|col
op_assign
l_int|0
suffix:semicolon
id|p
op_add_assign
id|maxcol
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|p
OL
id|HEADER_SIZE
)paren
(brace
r_char
id|header
(braket
id|HEADER_SIZE
)braket
suffix:semicolon
id|getconsxy
c_func
(paren
id|currcons
comma
id|header
op_plus
l_int|2
)paren
suffix:semicolon
r_while
c_loop
(paren
id|p
template_param
l_int|0
)paren
(brace
id|this_round
op_decrement
suffix:semicolon
id|header
(braket
id|p
op_increment
)braket
op_assign
op_star
id|con_buf0
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|viewed
)paren
id|putconsxy
c_func
(paren
id|currcons
comma
id|header
op_plus
l_int|2
)paren
suffix:semicolon
)brace
id|p
op_sub_assign
id|HEADER_SIZE
suffix:semicolon
id|col
op_assign
(paren
id|p
op_div
l_int|2
)paren
op_mod
id|maxcol
suffix:semicolon
r_if
c_cond
(paren
id|this_round
OG
l_int|0
)paren
(brace
id|org0
op_assign
id|org
op_assign
id|screen_pos
c_func
(paren
id|currcons
comma
id|p
op_div
l_int|2
comma
id|viewed
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_amp
l_int|1
)paren
op_logical_and
id|this_round
OG
l_int|0
)paren
(brace
r_char
id|c
suffix:semicolon
id|this_round
op_decrement
suffix:semicolon
id|c
op_assign
op_star
id|con_buf0
op_increment
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
id|vcs_scr_writew
c_func
(paren
id|currcons
comma
id|c
op_or
(paren
id|vcs_scr_readw
c_func
(paren
id|currcons
comma
id|org
)paren
op_amp
l_int|0xff00
)paren
comma
id|org
)paren
suffix:semicolon
macro_line|#else
id|vcs_scr_writew
c_func
(paren
id|currcons
comma
(paren
id|c
op_lshift
l_int|8
)paren
op_or
(paren
id|vcs_scr_readw
c_func
(paren
id|currcons
comma
id|org
)paren
op_amp
l_int|0xff
)paren
comma
id|org
)paren
suffix:semicolon
macro_line|#endif
id|org
op_increment
suffix:semicolon
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|col
op_eq
id|maxcol
)paren
(brace
id|org
op_assign
id|screen_pos
c_func
(paren
id|currcons
comma
id|p
op_div
l_int|2
comma
id|viewed
)paren
suffix:semicolon
id|col
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|p
op_div_assign
l_int|2
suffix:semicolon
id|p
op_add_assign
id|maxcol
op_minus
id|col
suffix:semicolon
)brace
r_while
c_loop
(paren
id|this_round
OG
l_int|1
)paren
(brace
r_int
r_int
id|w
suffix:semicolon
id|w
op_assign
op_star
(paren
(paren
r_const
r_int
r_int
op_star
)paren
id|con_buf0
)paren
suffix:semicolon
id|vcs_scr_writew
c_func
(paren
id|currcons
comma
id|w
comma
id|org
op_increment
)paren
suffix:semicolon
id|con_buf0
op_add_assign
l_int|2
suffix:semicolon
id|this_round
op_sub_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|col
op_eq
id|maxcol
)paren
(brace
id|org
op_assign
id|screen_pos
c_func
(paren
id|currcons
comma
id|p
comma
id|viewed
)paren
suffix:semicolon
id|col
op_assign
l_int|0
suffix:semicolon
id|p
op_add_assign
id|maxcol
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|this_round
OG
l_int|0
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
id|c
op_assign
op_star
id|con_buf0
op_increment
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
id|vcs_scr_writew
c_func
(paren
id|currcons
comma
(paren
id|vcs_scr_readw
c_func
(paren
id|currcons
comma
id|org
)paren
op_amp
l_int|0xff
)paren
op_or
(paren
id|c
op_lshift
l_int|8
)paren
comma
id|org
)paren
suffix:semicolon
macro_line|#else
id|vcs_scr_writew
c_func
(paren
id|currcons
comma
(paren
id|vcs_scr_readw
c_func
(paren
id|currcons
comma
id|org
)paren
op_amp
l_int|0xff00
)paren
op_or
id|c
comma
id|org
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
id|count
op_sub_assign
id|orig_count
suffix:semicolon
id|written
op_add_assign
id|orig_count
suffix:semicolon
id|buf
op_add_assign
id|orig_count
suffix:semicolon
id|pos
op_add_assign
id|orig_count
suffix:semicolon
r_if
c_cond
(paren
id|org0
)paren
id|update_region
c_func
(paren
id|currcons
comma
(paren
r_int
r_int
)paren
(paren
id|org0
)paren
comma
id|org
op_minus
id|org0
)paren
suffix:semicolon
)brace
op_star
id|ppos
op_add_assign
id|written
suffix:semicolon
id|ret
op_assign
id|written
suffix:semicolon
id|unlock_out
suffix:colon
id|spin_unlock_irq
c_func
(paren
op_amp
id|console_lock
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|con_buf_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|vcs_open
id|vcs_open
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
r_int
r_int
id|currcons
op_assign
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_amp
l_int|127
)paren
suffix:semicolon
r_if
c_cond
(paren
id|currcons
op_logical_and
op_logical_neg
id|vc_cons_allocated
c_func
(paren
id|currcons
op_minus
l_int|1
)paren
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|vcs_fops
r_static
r_struct
id|file_operations
id|vcs_fops
op_assign
(brace
id|llseek
suffix:colon
id|vcs_lseek
comma
id|read
suffix:colon
id|vcs_read
comma
id|write
suffix:colon
id|vcs_write
comma
id|open
suffix:colon
id|vcs_open
comma
)brace
suffix:semicolon
DECL|variable|devfs_handle
r_static
id|devfs_handle_t
id|devfs_handle
op_assign
l_int|NULL
suffix:semicolon
DECL|function|vcs_make_devfs
r_void
id|vcs_make_devfs
(paren
r_int
r_int
id|index
comma
r_int
id|unregister
)paren
(brace
macro_line|#ifdef CONFIG_DEVFS_FS
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
id|sprintf
(paren
id|name
comma
l_string|&quot;a%u&quot;
comma
id|index
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unregister
)paren
(brace
id|devfs_unregister
(paren
id|devfs_find_handle
(paren
id|devfs_handle
comma
id|name
op_plus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|DEVFS_SPECIAL_CHR
comma
l_int|0
)paren
)paren
suffix:semicolon
id|devfs_unregister
(paren
id|devfs_find_handle
(paren
id|devfs_handle
comma
id|name
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|DEVFS_SPECIAL_CHR
comma
l_int|0
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|devfs_register
(paren
id|devfs_handle
comma
id|name
op_plus
l_int|1
comma
l_int|0
comma
id|DEVFS_FL_DEFAULT
comma
id|VCS_MAJOR
comma
id|index
op_plus
l_int|1
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
l_int|0
comma
l_int|0
comma
op_amp
id|vcs_fops
comma
l_int|NULL
)paren
suffix:semicolon
id|devfs_register
(paren
id|devfs_handle
comma
id|name
comma
l_int|0
comma
id|DEVFS_FL_DEFAULT
comma
id|VCS_MAJOR
comma
id|index
op_plus
l_int|129
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
l_int|0
comma
l_int|0
comma
op_amp
id|vcs_fops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_DEVFS_FS */
)brace
DECL|function|vcs_init
r_int
id|__init
id|vcs_init
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|devfs_register_chrdev
c_func
(paren
id|VCS_MAJOR
comma
l_string|&quot;vcs&quot;
comma
op_amp
id|vcs_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|printk
c_func
(paren
l_string|&quot;unable to get major %d for vcs device&quot;
comma
id|VCS_MAJOR
)paren
suffix:semicolon
id|devfs_handle
op_assign
id|devfs_mk_dir
(paren
l_int|NULL
comma
l_string|&quot;vcc&quot;
comma
l_int|3
comma
l_int|NULL
)paren
suffix:semicolon
id|devfs_register
(paren
id|devfs_handle
comma
l_string|&quot;0&quot;
comma
l_int|1
comma
id|DEVFS_FL_DEFAULT
comma
id|VCS_MAJOR
comma
l_int|0
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
l_int|0
comma
l_int|0
comma
op_amp
id|vcs_fops
comma
l_int|NULL
)paren
suffix:semicolon
id|devfs_register
(paren
id|devfs_handle
comma
l_string|&quot;a&quot;
comma
l_int|1
comma
id|DEVFS_FL_DEFAULT
comma
id|VCS_MAJOR
comma
l_int|128
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
l_int|0
comma
l_int|0
comma
op_amp
id|vcs_fops
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
