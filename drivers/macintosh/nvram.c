multiline_comment|/*&n; * /dev/nvram driver for Power Macintosh.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/nvram.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|NVRAM_SIZE
mdefine_line|#define NVRAM_SIZE&t;8192
DECL|function|nvram_llseek
r_static
r_int
r_int
id|nvram_llseek
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
id|origin
)paren
(brace
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|1
suffix:colon
id|offset
op_add_assign
id|file-&gt;f_pos
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|offset
op_add_assign
id|NVRAM_SIZE
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
OL
l_int|0
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
DECL|function|read_nvram
r_static
r_int
id|read_nvram
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
r_int
id|count
)paren
(brace
r_int
r_int
id|i
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_char
op_star
id|p
op_assign
id|buf
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|count
OG
l_int|0
op_logical_and
id|i
OL
id|NVRAM_SIZE
suffix:semicolon
op_increment
id|i
comma
op_increment
id|p
comma
op_decrement
id|count
)paren
id|put_user
c_func
(paren
id|nvram_read_byte
c_func
(paren
id|i
)paren
comma
id|p
)paren
suffix:semicolon
id|file-&gt;f_pos
op_assign
id|i
suffix:semicolon
r_return
id|p
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|write_nvram
r_static
r_int
id|write_nvram
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
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
id|i
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_const
r_char
op_star
id|p
op_assign
id|buf
suffix:semicolon
r_char
id|c
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|count
OG
l_int|0
op_logical_and
id|i
OL
id|NVRAM_SIZE
suffix:semicolon
op_increment
id|i
comma
op_increment
id|p
comma
op_decrement
id|count
)paren
(brace
id|get_user
c_func
(paren
id|c
comma
id|p
)paren
suffix:semicolon
id|nvram_write_byte
c_func
(paren
id|i
comma
id|c
)paren
suffix:semicolon
)brace
id|file-&gt;f_pos
op_assign
id|i
suffix:semicolon
r_return
id|p
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|nvram_open
r_static
r_int
id|nvram_open
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|nvram_fops
r_struct
id|file_operations
id|nvram_fops
op_assign
(brace
id|nvram_llseek
comma
id|read_nvram
comma
id|write_nvram
comma
l_int|NULL
comma
multiline_comment|/* nvram_readdir */
l_int|NULL
comma
multiline_comment|/* nvram_select */
l_int|NULL
comma
multiline_comment|/* nvram_ioctl */
l_int|NULL
comma
multiline_comment|/* nvram_mmap */
id|nvram_open
comma
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|nvram_dev
r_static
r_struct
id|miscdevice
id|nvram_dev
op_assign
(brace
id|NVRAM_MINOR
comma
l_string|&quot;nvram&quot;
comma
op_amp
id|nvram_fops
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|nvram_init
c_func
(paren
r_void
)paren
)paren
(brace
id|misc_register
c_func
(paren
op_amp
id|nvram_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
