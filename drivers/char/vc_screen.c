multiline_comment|/*&n; * linux/drivers/char/vc_screen.c&n; *&n; * Provide access to virtual console memory.&n; * /dev/vcs0: the screen as it is being viewed right now (possibly scrolled)&n; * /dev/vcsN: the screen of /dev/ttyN (1 &lt;= N &lt;= 63)&n; *            [minor: N]&n; *&n; * /dev/vcsaN: idem, but including attributes, and prefixed with&n; *&t;the 4 bytes lines,columns,x,y (as screendump used to give)&n; *            [minor: N+128]&n; *&n; * This replaces screendump and part of selection, so that the system&n; * administrator can control access using file system permissions.&n; *&n; * aeb@cwi.nl - efter Friedas begravelse - 950211&n; *&n; * machek@k332.feld.cvut.cz - modified not to send characters to wrong console&n; *&t; - fixed some fatal off-by-one bugs (0-- no longer == -1 -&gt; looping and looping and looping...)&n; *&t; - making it shorter - scr_readw are macros which expand in PRETTY long code&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/console_struct.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
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
r_int
DECL|function|func_scr_readw
id|func_scr_readw
c_func
(paren
r_int
r_int
op_star
id|org
)paren
(brace
r_return
id|scr_readw
c_func
(paren
id|org
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|func_scr_writew
id|func_scr_writew
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
op_star
id|org
)paren
(brace
id|scr_writew
c_func
(paren
id|val
comma
id|org
)paren
suffix:semicolon
)brace
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
r_int
r_int
id|vcs_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
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
DECL|macro|RETURN
mdefine_line|#define RETURN( x ) { enable_bh( CONSOLE_BH ); return x; }
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
id|p
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
id|read
suffix:semicolon
r_char
op_star
id|buf0
suffix:semicolon
r_int
r_int
op_star
id|org
op_assign
l_int|NULL
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
id|disable_bh
c_func
(paren
id|CONSOLE_BH
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
id|RETURN
c_func
(paren
op_minus
id|ENXIO
)paren
suffix:semicolon
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
id|p
template_param
id|size
)paren
id|RETURN
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|size
op_minus
id|p
)paren
id|count
op_assign
id|size
op_minus
id|p
suffix:semicolon
id|buf0
op_assign
id|buf
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
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
)paren
id|put_user
c_func
(paren
id|func_scr_readw
c_func
(paren
id|org
op_increment
)paren
op_amp
l_int|0xff
comma
id|buf
op_increment
)paren
suffix:semicolon
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
id|header
(braket
l_int|0
)braket
op_assign
(paren
r_char
)paren
id|video_num_lines
suffix:semicolon
id|header
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
id|count
op_decrement
suffix:semicolon
id|put_user
c_func
(paren
id|header
(braket
id|p
op_increment
)braket
comma
id|buf
op_increment
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
(brace
id|p
op_sub_assign
id|HEADER_SIZE
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
id|count
OG
l_int|0
)paren
macro_line|#ifdef __BIG_ENDIAN
(brace
id|count
op_decrement
suffix:semicolon
id|put_user
c_func
(paren
id|func_scr_readw
c_func
(paren
id|org
op_increment
)paren
op_amp
l_int|0xff
comma
id|buf
op_increment
)paren
suffix:semicolon
)brace
macro_line|#else
(brace
id|count
op_decrement
suffix:semicolon
id|put_user
c_func
(paren
id|func_scr_readw
c_func
(paren
id|org
op_increment
)paren
op_rshift
l_int|8
comma
id|buf
op_increment
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_while
c_loop
(paren
id|count
OG
l_int|1
)paren
(brace
id|put_user
c_func
(paren
id|func_scr_readw
c_func
(paren
id|org
op_increment
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|buf
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
macro_line|#ifdef __BIG_ENDIAN
id|put_user
c_func
(paren
id|func_scr_readw
c_func
(paren
id|org
)paren
op_rshift
l_int|8
comma
id|buf
op_increment
)paren
suffix:semicolon
macro_line|#else
id|put_user
c_func
(paren
id|func_scr_readw
c_func
(paren
id|org
)paren
op_amp
l_int|0xff
comma
id|buf
op_increment
)paren
suffix:semicolon
macro_line|#endif
)brace
id|read
op_assign
id|buf
op_minus
id|buf0
suffix:semicolon
op_star
id|ppos
op_add_assign
id|read
suffix:semicolon
id|RETURN
c_func
(paren
id|read
)paren
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
id|p
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
r_const
r_char
op_star
id|buf0
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
id|disable_bh
c_func
(paren
id|CONSOLE_BH
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
id|RETURN
c_func
(paren
op_minus
id|ENXIO
)paren
suffix:semicolon
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
id|p
template_param
id|size
)paren
id|RETURN
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|size
op_minus
id|p
)paren
id|count
op_assign
id|size
op_minus
id|p
suffix:semicolon
id|buf0
op_assign
id|buf
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
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|get_user
c_func
(paren
id|c
comma
(paren
r_const
r_int
r_char
op_star
)paren
id|buf
op_increment
)paren
suffix:semicolon
id|func_scr_writew
c_func
(paren
(paren
id|func_scr_readw
c_func
(paren
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
id|count
op_decrement
suffix:semicolon
id|get_user
c_func
(paren
id|header
(braket
id|p
op_increment
)braket
comma
id|buf
op_increment
)paren
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
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
(brace
id|p
op_sub_assign
id|HEADER_SIZE
suffix:semicolon
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
id|count
OG
l_int|0
)paren
(brace
r_char
id|c
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|get_user
c_func
(paren
id|c
comma
id|buf
op_increment
)paren
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
id|func_scr_writew
c_func
(paren
id|c
op_or
(paren
id|func_scr_readw
c_func
(paren
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
id|func_scr_writew
c_func
(paren
(paren
id|c
op_lshift
l_int|8
)paren
op_or
(paren
id|func_scr_readw
c_func
(paren
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
)brace
)brace
r_while
c_loop
(paren
id|count
OG
l_int|1
)paren
(brace
r_int
r_int
id|w
suffix:semicolon
id|get_user
c_func
(paren
id|w
comma
(paren
r_const
r_int
r_int
op_star
)paren
id|buf
)paren
suffix:semicolon
id|func_scr_writew
c_func
(paren
id|w
comma
id|org
op_increment
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
id|get_user
c_func
(paren
id|c
comma
(paren
r_const
r_int
r_char
op_star
)paren
id|buf
op_increment
)paren
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
id|func_scr_writew
c_func
(paren
(paren
id|func_scr_readw
c_func
(paren
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
id|func_scr_writew
c_func
(paren
(paren
id|func_scr_readw
c_func
(paren
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
id|written
op_assign
id|buf
op_minus
id|buf0
suffix:semicolon
op_star
id|ppos
op_add_assign
id|written
suffix:semicolon
id|RETURN
c_func
(paren
id|written
)paren
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
id|vcs_lseek
comma
multiline_comment|/* lseek */
id|vcs_read
comma
multiline_comment|/* read */
id|vcs_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll */
l_int|NULL
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|vcs_open
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* release */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|vcs_init
c_func
(paren
r_void
)paren
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|register_chrdev
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
r_return
id|error
suffix:semicolon
)brace
eof
