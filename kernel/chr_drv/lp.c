multiline_comment|/*&n; $Header: /usr/src/linux/kernel/chr_drv/lp.c,v 1.9 1992/01/06 16:11:19&n;  james_r_wiegand Exp james_r_wiegand $&n;*/
multiline_comment|/*&n; * Edited by Linus - cleaner interface etc. Still not using interrupts, so&n; * it eats more resources than necessary, but it was easy to code this way...&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/lp.h&gt;
DECL|function|lp_reset
r_static
r_int
id|lp_reset
c_func
(paren
r_int
id|minor
)paren
(brace
r_int
id|testvalue
suffix:semicolon
multiline_comment|/* reset value */
id|outb
c_func
(paren
l_int|0
comma
id|LP_B
c_func
(paren
id|minor
)paren
op_plus
l_int|2
)paren
suffix:semicolon
r_for
c_loop
(paren
id|testvalue
op_assign
l_int|0
suffix:semicolon
id|testvalue
OL
id|LP_DELAY
suffix:semicolon
id|testvalue
op_increment
)paren
suffix:semicolon
id|outb
c_func
(paren
id|LP_PSELECP
op_or
id|LP_PINITP
comma
id|LP_B
c_func
(paren
id|minor
)paren
op_plus
l_int|2
)paren
suffix:semicolon
r_return
id|LP_S
c_func
(paren
id|minor
)paren
suffix:semicolon
)brace
DECL|function|lp_char
r_static
r_int
id|lp_char
c_func
(paren
r_char
id|lpchar
comma
r_int
id|minor
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|count
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
id|lpchar
comma
id|LP_B
c_func
(paren
id|minor
)paren
)paren
suffix:semicolon
r_do
(brace
id|retval
op_assign
id|LP_S
c_func
(paren
id|minor
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|retval
op_amp
id|LP_PBUSY
)paren
op_logical_and
id|count
OL
id|LP_TIMEOUT
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_eq
id|LP_TIMEOUT
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lp%d timeout&bslash;n&bslash;r&quot;
comma
id|minor
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* control port pr_table[0]+2 take strobe high */
id|outb
c_func
(paren
(paren
id|LP_PSELECP
op_or
id|LP_PINITP
op_or
id|LP_PSTROBE
)paren
comma
(paren
id|LP_B
c_func
(paren
id|minor
)paren
op_plus
l_int|2
)paren
)paren
suffix:semicolon
multiline_comment|/* take strobe low */
id|outb
c_func
(paren
(paren
id|LP_PSELECP
op_or
id|LP_PINITP
)paren
comma
(paren
id|LP_B
c_func
(paren
id|minor
)paren
op_plus
l_int|2
)paren
)paren
suffix:semicolon
multiline_comment|/* get something meaningful for return value */
r_return
id|LP_S
c_func
(paren
id|minor
)paren
suffix:semicolon
)brace
DECL|function|lp_write
r_static
r_int
id|lp_write
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
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|retval
suffix:semicolon
r_int
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_char
id|c
comma
op_star
id|temp
op_assign
id|buf
suffix:semicolon
id|temp
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|c
op_assign
id|get_fs_byte
c_func
(paren
id|temp
op_increment
)paren
suffix:semicolon
id|retval
op_assign
id|lp_char
c_func
(paren
id|c
comma
id|minor
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_amp
id|LP_POUTPA
)paren
(brace
id|LP_F
c_func
(paren
id|minor
)paren
op_or_assign
id|LP_NOPA
suffix:semicolon
r_return
id|temp
op_minus
id|buf
ques
c_cond
id|temp
op_minus
id|buf
suffix:colon
op_minus
id|ENOSPC
suffix:semicolon
)brace
r_else
id|LP_F
c_func
(paren
id|minor
)paren
op_and_assign
op_complement
id|LP_NOPA
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|retval
op_amp
id|LP_PSELECD
)paren
)paren
(brace
id|LP_F
c_func
(paren
id|minor
)paren
op_and_assign
op_complement
id|LP_SELEC
suffix:semicolon
r_return
id|temp
op_minus
id|buf
ques
c_cond
id|temp
op_minus
id|buf
suffix:colon
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
id|LP_F
c_func
(paren
id|minor
)paren
op_and_assign
op_complement
id|LP_SELEC
suffix:semicolon
multiline_comment|/* not offline or out of paper. on fire? */
r_if
c_cond
(paren
op_logical_neg
(paren
id|retval
op_amp
id|LP_PERRORP
)paren
)paren
(brace
id|LP_F
c_func
(paren
id|minor
)paren
op_or_assign
id|LP_ERR
suffix:semicolon
r_return
id|temp
op_minus
id|buf
ques
c_cond
id|temp
op_minus
id|buf
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
r_else
id|LP_F
c_func
(paren
id|minor
)paren
op_and_assign
op_complement
id|LP_SELEC
suffix:semicolon
)brace
r_return
id|temp
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|lp_read
r_static
r_int
id|lp_read
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
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|lp_lseek
r_static
r_int
id|lp_lseek
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
id|off_t
id|offset
comma
r_int
id|origin
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|lp_open
r_static
r_int
id|lp_open
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
)paren
(brace
r_int
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_ge
id|LP_NO
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
(paren
id|LP_F
c_func
(paren
id|minor
)paren
op_amp
id|LP_EXIST
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|LP_F
c_func
(paren
id|minor
)paren
op_amp
id|LP_BUSY
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|LP_F
c_func
(paren
id|minor
)paren
op_or_assign
id|LP_BUSY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lp_release
r_static
r_void
id|lp_release
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
)paren
(brace
r_int
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|LP_F
c_func
(paren
id|minor
)paren
op_and_assign
op_complement
id|LP_BUSY
suffix:semicolon
)brace
DECL|variable|lp_fops
r_static
r_struct
id|file_operations
id|lp_fops
op_assign
(brace
id|lp_lseek
comma
id|lp_read
comma
id|lp_write
comma
l_int|NULL
comma
multiline_comment|/* lp_readdir */
l_int|NULL
comma
multiline_comment|/* lp_select */
l_int|NULL
comma
multiline_comment|/* lp_ioctl */
l_int|NULL
comma
multiline_comment|/* lp_mmap */
id|lp_open
comma
id|lp_release
)brace
suffix:semicolon
DECL|function|lp_init
r_int
id|lp_init
c_func
(paren
r_int
id|kmem_start
)paren
(brace
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|testvalue
op_assign
l_int|0
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
id|chrdev_fops
(braket
l_int|6
)braket
op_assign
op_amp
id|lp_fops
suffix:semicolon
multiline_comment|/* take on all known port values */
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
suffix:semicolon
id|offset
OL
id|LP_NO
suffix:semicolon
id|offset
op_increment
)paren
(brace
multiline_comment|/* write to port &amp; read back to check */
id|outb
c_func
(paren
id|LP_DUMMY
comma
id|LP_B
c_func
(paren
id|offset
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|testvalue
op_assign
l_int|0
suffix:semicolon
id|testvalue
OL
id|LP_DELAY
suffix:semicolon
id|testvalue
op_increment
)paren
suffix:semicolon
id|testvalue
op_assign
id|inb
c_func
(paren
id|LP_B
c_func
(paren
id|offset
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|testvalue
op_ne
l_int|255
)paren
(brace
id|LP_F
c_func
(paren
id|offset
)paren
op_or_assign
id|LP_EXIST
suffix:semicolon
id|lp_reset
c_func
(paren
id|offset
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;lp_init: lp%d exists (%d)&bslash;n&quot;
comma
id|offset
comma
id|testvalue
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;lp_init: no lp devices found&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|kmem_start
suffix:semicolon
)brace
eof
