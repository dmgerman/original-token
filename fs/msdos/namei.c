multiline_comment|/*&n; *  linux/fs/msdos/namei.c&n; *&n; *  Written 1992 by Werner Almesberger&n; */
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
multiline_comment|/* MS-DOS &quot;device special files&quot; */
DECL|variable|reserved_names
r_static
r_char
op_star
id|reserved_names
(braket
)braket
op_assign
(brace
l_string|&quot;CON     &quot;
comma
l_string|&quot;PRN     &quot;
comma
l_string|&quot;NUL     &quot;
comma
l_string|&quot;AUX     &quot;
comma
l_string|&quot;LPT1    &quot;
comma
l_string|&quot;LPT2    &quot;
comma
l_string|&quot;LPT3    &quot;
comma
l_string|&quot;LPT4    &quot;
comma
l_string|&quot;COM1    &quot;
comma
l_string|&quot;COM2    &quot;
comma
l_string|&quot;COM3    &quot;
comma
l_string|&quot;COM4    &quot;
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/* Formats an MS-DOS file name. Rejects invalid names. */
DECL|function|msdos_format_name
r_static
r_int
id|msdos_format_name
c_func
(paren
r_char
id|conv
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_char
op_star
id|res
)paren
(brace
r_char
op_star
id|walk
comma
op_star
op_star
id|reserved
suffix:semicolon
r_char
id|c
suffix:semicolon
r_int
id|space
suffix:semicolon
r_if
c_cond
(paren
id|get_fs_byte
c_func
(paren
id|name
)paren
op_eq
id|DELETED_FLAG
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_fs_byte
c_func
(paren
id|name
)paren
op_eq
l_char|&squot;.&squot;
op_logical_and
(paren
id|len
op_eq
l_int|1
op_logical_or
(paren
id|len
op_eq
l_int|2
op_logical_and
id|get_fs_byte
c_func
(paren
id|name
op_plus
l_int|1
)paren
op_eq
l_char|&squot;.&squot;
)paren
)paren
)paren
(brace
id|memset
c_func
(paren
id|res
op_plus
l_int|1
comma
l_char|&squot; &squot;
comma
l_int|10
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
op_star
id|res
op_increment
op_assign
l_char|&squot;.&squot;
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|space
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* to make GCC happy */
id|c
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|res
suffix:semicolon
id|len
op_logical_and
id|walk
op_minus
id|res
OL
l_int|8
suffix:semicolon
id|walk
op_increment
)paren
(brace
id|c
op_assign
id|get_fs_byte
c_func
(paren
id|name
op_increment
)paren
suffix:semicolon
id|len
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot; &squot;
op_logical_and
id|conv
op_ne
l_char|&squot;r&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;Z&squot;
)paren
(brace
r_if
c_cond
(paren
id|conv
op_ne
l_char|&squot;r&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|c
op_add_assign
l_int|32
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
OL
l_char|&squot; &squot;
op_logical_or
id|c
op_eq
l_char|&squot;:&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;.&squot;
)paren
r_break
suffix:semicolon
id|space
op_assign
id|c
op_eq
l_char|&squot; &squot;
suffix:semicolon
op_star
id|walk
op_assign
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;z&squot;
ques
c_cond
id|c
op_minus
l_int|32
suffix:colon
id|c
suffix:semicolon
)brace
r_if
c_cond
(paren
id|space
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|conv
op_eq
l_char|&squot;s&squot;
op_logical_and
id|len
op_logical_and
id|c
op_ne
l_char|&squot;.&squot;
)paren
(brace
id|c
op_assign
id|get_fs_byte
c_func
(paren
id|name
op_increment
)paren
suffix:semicolon
id|len
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;.&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_while
c_loop
(paren
id|c
op_ne
l_char|&squot;.&squot;
op_logical_and
id|len
op_decrement
)paren
id|c
op_assign
id|get_fs_byte
c_func
(paren
id|name
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|walk
op_eq
id|res
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;.&squot;
)paren
(brace
r_while
c_loop
(paren
id|walk
op_minus
id|res
OL
l_int|8
)paren
op_star
id|walk
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
op_logical_and
id|walk
op_minus
id|res
OL
id|MSDOS_NAME
)paren
(brace
id|c
op_assign
id|get_fs_byte
c_func
(paren
id|name
op_increment
)paren
suffix:semicolon
id|len
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot; &squot;
op_logical_and
id|conv
op_ne
l_char|&squot;r&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|c
OL
l_char|&squot; &squot;
op_logical_or
id|c
op_eq
l_char|&squot;:&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
op_logical_or
id|c
op_eq
l_char|&squot;.&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;Z&squot;
)paren
(brace
r_if
c_cond
(paren
id|conv
op_ne
l_char|&squot;r&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|c
op_add_assign
l_int|32
suffix:semicolon
)brace
id|space
op_assign
id|c
op_eq
l_char|&squot; &squot;
suffix:semicolon
op_star
id|walk
op_increment
op_assign
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;z&squot;
ques
c_cond
id|c
op_minus
l_int|32
suffix:colon
id|c
suffix:semicolon
)brace
r_if
c_cond
(paren
id|space
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|conv
op_eq
l_char|&squot;s&squot;
op_logical_and
id|len
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_while
c_loop
(paren
id|walk
op_minus
id|res
OL
id|MSDOS_NAME
)paren
op_star
id|walk
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_for
c_loop
(paren
id|reserved
op_assign
id|reserved_names
suffix:semicolon
op_star
id|reserved
suffix:semicolon
id|reserved
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|res
comma
op_star
id|reserved
comma
l_int|8
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Locates a directory entry. */
DECL|function|msdos_find
r_static
r_int
id|msdos_find
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|de
comma
r_int
op_star
id|ino
)paren
(brace
r_char
id|msdos_name
(braket
id|MSDOS_NAME
)braket
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|msdos_format_name
c_func
(paren
id|MSDOS_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|name_check
comma
id|name
comma
id|len
comma
id|msdos_name
)paren
)paren
OL
l_int|0
)paren
r_return
id|res
suffix:semicolon
r_return
id|msdos_scan
c_func
(paren
id|dir
comma
id|msdos_name
comma
id|bh
comma
id|de
comma
id|ino
)paren
suffix:semicolon
)brace
DECL|function|msdos_lookup
r_int
id|msdos_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_struct
id|inode
op_star
op_star
id|result
)paren
(brace
r_int
id|ino
comma
id|res
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|inode
op_star
id|next
suffix:semicolon
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|dir-&gt;i_mode
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_eq
l_int|1
op_logical_and
id|get_fs_byte
c_func
(paren
id|name
)paren
op_eq
l_char|&squot;.&squot;
)paren
(brace
op_star
id|result
op_assign
id|dir
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_eq
l_int|2
op_logical_and
id|get_fs_byte
c_func
(paren
id|name
)paren
op_eq
l_char|&squot;.&squot;
op_logical_and
id|get_fs_byte
c_func
(paren
id|name
op_plus
l_int|1
)paren
op_eq
l_char|&squot;.&squot;
)paren
(brace
id|ino
op_assign
id|msdos_parent_ino
c_func
(paren
id|dir
comma
l_int|0
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ino
OL
l_int|0
)paren
r_return
id|ino
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|result
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_dev
comma
id|ino
)paren
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|res
op_assign
id|msdos_find
c_func
(paren
id|dir
comma
id|name
comma
id|len
comma
op_amp
id|bh
comma
op_amp
id|de
comma
op_amp
id|ino
)paren
)paren
OL
l_int|0
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bh
)paren
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* printk(&quot;lookup: ino=%d&bslash;r&bslash;n&quot;,ino); */
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|result
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_dev
comma
id|ino
)paren
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_star
id|result
)paren
op_member_access_from_pointer
id|i_data
(braket
id|D_BUSY
)braket
)paren
(brace
multiline_comment|/* mkdir in progress */
id|iput
c_func
(paren
op_star
id|result
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
op_star
id|result
)paren
op_member_access_from_pointer
id|i_data
(braket
id|D_OLD
)braket
)paren
(brace
id|next
op_assign
(paren
r_struct
id|inode
op_star
)paren
(paren
(paren
op_star
id|result
)paren
op_member_access_from_pointer
id|i_data
(braket
id|D_OLD
)braket
)paren
suffix:semicolon
id|iput
c_func
(paren
op_star
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|result
op_assign
id|iget
c_func
(paren
id|next-&gt;i_dev
comma
id|next-&gt;i_ino
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;msdos_lookup: Can&squot;t happen&quot;
)paren
suffix:semicolon
)brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Creates a directory entry (name is already formatted). */
DECL|function|msdos_create_entry
r_static
r_int
id|msdos_create_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_char
op_star
id|name
comma
r_int
id|is_dir
comma
r_struct
id|inode
op_star
op_star
id|result
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|de
suffix:semicolon
r_int
id|res
comma
id|ino
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|msdos_scan
c_func
(paren
id|dir
comma
l_int|NULL
comma
op_amp
id|bh
comma
op_amp
id|de
comma
op_amp
id|ino
)paren
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|dir-&gt;i_ino
op_eq
id|MSDOS_ROOT_INO
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|msdos_add_cluster
c_func
(paren
id|dir
)paren
)paren
OL
l_int|0
)paren
r_return
id|res
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|msdos_scan
c_func
(paren
id|dir
comma
l_int|NULL
comma
op_amp
id|bh
comma
op_amp
id|de
comma
op_amp
id|ino
)paren
)paren
OL
l_int|0
)paren
r_return
id|res
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|de-&gt;name
comma
id|name
comma
id|MSDOS_NAME
)paren
suffix:semicolon
id|de-&gt;attr
op_assign
id|is_dir
ques
c_cond
id|ATTR_DIR
suffix:colon
id|ATTR_ARCH
suffix:semicolon
id|de-&gt;start
op_assign
l_int|0
suffix:semicolon
id|date_unix2dos
c_func
(paren
id|CURRENT_TIME
comma
op_amp
id|de-&gt;time
comma
op_amp
id|de-&gt;date
)paren
suffix:semicolon
id|de-&gt;size
op_assign
l_int|0
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|result
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_dev
comma
id|ino
)paren
)paren
id|msdos_read_inode
c_func
(paren
op_star
id|result
)paren
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
op_logical_neg
op_star
id|result
)paren
r_return
op_minus
id|EIO
suffix:semicolon
(paren
op_star
id|result
)paren
op_member_access_from_pointer
id|i_mtime
op_assign
(paren
op_star
id|result
)paren
op_member_access_from_pointer
id|i_atime
op_assign
(paren
op_star
id|result
)paren
op_member_access_from_pointer
id|i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
(paren
op_star
id|result
)paren
op_member_access_from_pointer
id|i_dirt
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|msdos_create
r_int
id|msdos_create
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
id|mode
comma
r_struct
id|inode
op_star
op_star
id|result
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|de
suffix:semicolon
r_char
id|msdos_name
(braket
id|MSDOS_NAME
)braket
suffix:semicolon
r_int
id|ino
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|msdos_format_name
c_func
(paren
id|MSDOS_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|name_check
comma
id|name
comma
id|len
comma
id|msdos_name
)paren
)paren
OL
l_int|0
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|lock_creation
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msdos_scan
c_func
(paren
id|dir
comma
id|msdos_name
comma
op_amp
id|bh
comma
op_amp
id|de
comma
op_amp
id|ino
)paren
op_ge
l_int|0
)paren
(brace
id|unlock_creation
c_func
(paren
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
id|res
op_assign
id|msdos_create_entry
c_func
(paren
id|dir
comma
id|msdos_name
comma
id|S_ISDIR
c_func
(paren
id|mode
)paren
comma
id|result
)paren
suffix:semicolon
id|unlock_creation
c_func
(paren
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|msdos_mkdir
r_int
id|msdos_mkdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
id|mode
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|inode
op_star
id|inode
comma
op_star
id|dot
suffix:semicolon
r_char
id|msdos_name
(braket
id|MSDOS_NAME
)braket
suffix:semicolon
r_int
id|ino
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|msdos_format_name
c_func
(paren
id|MSDOS_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|name_check
comma
id|name
comma
id|len
comma
id|msdos_name
)paren
)paren
OL
l_int|0
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|lock_creation
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msdos_scan
c_func
(paren
id|dir
comma
id|msdos_name
comma
op_amp
id|bh
comma
op_amp
id|de
comma
op_amp
id|ino
)paren
op_ge
l_int|0
)paren
(brace
id|unlock_creation
c_func
(paren
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|res
op_assign
id|msdos_create_entry
c_func
(paren
id|dir
comma
id|msdos_name
comma
l_int|1
comma
op_amp
id|inode
)paren
)paren
OL
l_int|0
)paren
(brace
id|unlock_creation
c_func
(paren
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|inode-&gt;i_data
(braket
id|D_BUSY
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* prevent lookups */
r_if
c_cond
(paren
(paren
id|res
op_assign
id|msdos_add_cluster
c_func
(paren
id|inode
)paren
)paren
OL
l_int|0
)paren
r_goto
id|mkdir_error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|msdos_create_entry
c_func
(paren
id|inode
comma
id|MSDOS_DOT
comma
l_int|1
comma
op_amp
id|dot
)paren
)paren
OL
l_int|0
)paren
r_goto
id|mkdir_error
suffix:semicolon
id|dot-&gt;i_size
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|dot-&gt;i_data
(braket
id|D_START
)braket
op_assign
id|inode-&gt;i_data
(braket
id|D_START
)braket
suffix:semicolon
id|dot-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|iput
c_func
(paren
id|dot
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|msdos_create_entry
c_func
(paren
id|inode
comma
id|MSDOS_DOTDOT
comma
l_int|1
comma
op_amp
id|dot
)paren
)paren
OL
l_int|0
)paren
r_goto
id|mkdir_error
suffix:semicolon
id|unlock_creation
c_func
(paren
)paren
suffix:semicolon
id|dot-&gt;i_size
op_assign
id|dir-&gt;i_size
suffix:semicolon
id|dot-&gt;i_data
(braket
id|D_START
)braket
op_assign
id|dir-&gt;i_data
(braket
id|D_START
)braket
suffix:semicolon
id|dot-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_data
(braket
id|D_BUSY
)braket
op_assign
l_int|0
suffix:semicolon
id|iput
c_func
(paren
id|dot
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|mkdir_error
suffix:colon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msdos_rmdir
c_func
(paren
id|dir
comma
id|name
comma
id|len
)paren
OL
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;rmdir in mkdir failed&quot;
)paren
suffix:semicolon
id|unlock_creation
c_func
(paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|msdos_rmdir
r_int
id|msdos_rmdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_int
id|res
comma
id|ino
comma
id|pos
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|dbh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|de
comma
op_star
id|dde
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|inode
op_assign
l_int|NULL
suffix:semicolon
id|res
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|1
op_logical_and
id|get_fs_byte
c_func
(paren
id|name
)paren
op_eq
l_char|&squot;.&squot;
)paren
r_goto
id|rmdir_done
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|msdos_find
c_func
(paren
id|dir
comma
id|name
comma
id|len
comma
op_amp
id|bh
comma
op_amp
id|de
comma
op_amp
id|ino
)paren
)paren
OL
l_int|0
)paren
r_goto
id|rmdir_done
suffix:semicolon
id|res
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_dev
comma
id|ino
)paren
)paren
)paren
r_goto
id|rmdir_done
suffix:semicolon
id|res
op_assign
op_minus
id|ENOTDIR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_goto
id|rmdir_done
suffix:semicolon
id|res
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_dev
op_ne
id|inode-&gt;i_dev
op_logical_or
id|dir
op_eq
id|inode
)paren
r_goto
id|rmdir_done
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_count
OG
l_int|1
)paren
r_goto
id|rmdir_done
suffix:semicolon
id|res
op_assign
op_minus
id|ENOTEMPTY
suffix:semicolon
id|pos
op_assign
l_int|0
suffix:semicolon
id|dbh
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|msdos_get_entry
c_func
(paren
id|inode
comma
op_amp
id|pos
comma
op_amp
id|dbh
comma
op_amp
id|dde
)paren
OG
op_minus
l_int|1
)paren
r_if
c_cond
(paren
id|dde-&gt;name
(braket
l_int|0
)braket
op_logical_and
(paren
(paren
r_int
r_char
op_star
)paren
id|dde-&gt;name
)paren
(braket
l_int|0
)braket
op_ne
id|DELETED_FLAG
op_logical_and
id|strncmp
c_func
(paren
id|dde-&gt;name
comma
id|MSDOS_DOT
comma
id|MSDOS_NAME
)paren
op_logical_and
id|strncmp
c_func
(paren
id|dde-&gt;name
comma
id|MSDOS_DOTDOT
comma
id|MSDOS_NAME
)paren
)paren
r_goto
id|rmdir_done
suffix:semicolon
r_if
c_cond
(paren
id|dbh
)paren
id|brelse
c_func
(paren
id|dbh
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
id|dir-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|de-&gt;name
(braket
l_int|0
)braket
op_assign
id|DELETED_FLAG
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
id|rmdir_done
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|msdos_unlink
r_int
id|msdos_unlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_int
id|res
comma
id|ino
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|msdos_find
c_func
(paren
id|dir
comma
id|name
comma
id|len
comma
op_amp
id|bh
comma
op_amp
id|de
comma
op_amp
id|ino
)paren
)paren
OL
l_int|0
)paren
r_goto
id|unlink_done
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_dev
comma
id|ino
)paren
)paren
)paren
(brace
id|res
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|unlink_done
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|res
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|unlink_done
suffix:semicolon
)brace
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_data
(braket
id|D_BUSY
)braket
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|de-&gt;name
(braket
l_int|0
)braket
op_assign
id|DELETED_FLAG
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|unlink_done
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|rename_same_dir
r_static
r_int
id|rename_same_dir
c_func
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_char
op_star
id|old_name
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_char
op_star
id|new_name
comma
r_struct
id|buffer_head
op_star
id|old_bh
comma
r_struct
id|msdos_dir_entry
op_star
id|old_de
comma
r_int
id|old_ino
)paren
(brace
r_struct
id|buffer_head
op_star
id|new_bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|new_de
suffix:semicolon
r_struct
id|inode
op_star
id|new_inode
comma
op_star
id|old_inode
suffix:semicolon
r_int
id|new_ino
suffix:semicolon
r_int
id|exists
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|old_name
comma
id|new_name
comma
id|MSDOS_NAME
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|exists
op_assign
id|msdos_scan
c_func
(paren
id|new_dir
comma
id|new_name
comma
op_amp
id|new_bh
comma
op_amp
id|new_de
comma
op_amp
id|new_ino
)paren
op_ge
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
r_int
r_char
op_star
)paren
id|old_de-&gt;name
op_eq
id|DELETED_FLAG
)paren
(brace
r_if
c_cond
(paren
id|exists
)paren
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|exists
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|new_inode
op_assign
id|iget
c_func
(paren
id|new_dir-&gt;i_dev
comma
id|new_ino
)paren
)paren
)paren
(brace
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|new_inode-&gt;i_mode
)paren
)paren
(brace
id|iput
c_func
(paren
id|new_inode
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|new_inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|new_inode-&gt;i_data
(braket
id|D_BUSY
)braket
op_assign
l_int|1
suffix:semicolon
id|new_inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|new_de-&gt;name
(braket
l_int|0
)braket
op_assign
id|DELETED_FLAG
suffix:semicolon
id|new_bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|iput
c_func
(paren
id|new_inode
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|old_de-&gt;name
comma
id|new_name
comma
id|MSDOS_NAME
)paren
suffix:semicolon
id|old_bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|old_dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|conversion
op_eq
l_char|&squot;a&squot;
)paren
multiline_comment|/* update binary info */
r_if
c_cond
(paren
id|old_inode
op_assign
id|iget
c_func
(paren
id|old_dir-&gt;i_dev
comma
id|old_ino
)paren
)paren
(brace
id|msdos_read_inode
c_func
(paren
id|old_inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|old_inode
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rename_diff_dir
r_static
r_int
id|rename_diff_dir
c_func
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_char
op_star
id|old_name
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_char
op_star
id|new_name
comma
r_struct
id|buffer_head
op_star
id|old_bh
comma
r_struct
id|msdos_dir_entry
op_star
id|old_de
comma
r_int
id|old_ino
)paren
(brace
r_struct
id|buffer_head
op_star
id|new_bh
comma
op_star
id|free_bh
comma
op_star
id|dotdot_bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|new_de
comma
op_star
id|free_de
comma
op_star
id|dotdot_de
suffix:semicolon
r_struct
id|inode
op_star
id|old_inode
comma
op_star
id|new_inode
comma
op_star
id|free_inode
comma
op_star
id|dotdot_inode
comma
op_star
id|walk
suffix:semicolon
r_int
id|new_ino
comma
id|free_ino
comma
id|dotdot_ino
suffix:semicolon
r_int
id|error
comma
id|exists
comma
id|ino
suffix:semicolon
r_if
c_cond
(paren
id|old_dir-&gt;i_dev
op_ne
id|new_dir-&gt;i_dev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|old_ino
op_eq
id|new_dir-&gt;i_ino
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|walk
op_assign
id|iget
c_func
(paren
id|new_dir-&gt;i_dev
comma
id|new_dir-&gt;i_ino
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_while
c_loop
(paren
id|walk-&gt;i_ino
op_ne
id|MSDOS_ROOT_INO
)paren
(brace
id|ino
op_assign
id|msdos_parent_ino
c_func
(paren
id|walk
comma
l_int|1
)paren
suffix:semicolon
id|iput
c_func
(paren
id|walk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ino
OL
l_int|0
)paren
r_return
id|ino
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_eq
id|old_ino
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|walk
op_assign
id|iget
c_func
(paren
id|new_dir-&gt;i_dev
comma
id|ino
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|iput
c_func
(paren
id|walk
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|msdos_scan
c_func
(paren
id|new_dir
comma
l_int|NULL
comma
op_amp
id|free_bh
comma
op_amp
id|free_de
comma
op_amp
id|free_ino
)paren
)paren
OL
l_int|0
)paren
r_return
id|error
suffix:semicolon
id|exists
op_assign
id|msdos_scan
c_func
(paren
id|new_dir
comma
id|new_name
comma
op_amp
id|new_bh
comma
op_amp
id|new_de
comma
op_amp
id|new_ino
)paren
op_ge
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|old_inode
op_assign
id|iget
c_func
(paren
id|old_dir-&gt;i_dev
comma
id|old_ino
)paren
)paren
)paren
(brace
id|brelse
c_func
(paren
id|free_bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exists
)paren
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
(paren
r_int
r_char
op_star
)paren
id|old_de-&gt;name
op_eq
id|DELETED_FLAG
)paren
(brace
id|iput
c_func
(paren
id|old_inode
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|free_bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exists
)paren
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|new_inode
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* to make GCC happy */
r_if
c_cond
(paren
id|exists
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|new_inode
op_assign
id|iget
c_func
(paren
id|new_dir-&gt;i_dev
comma
id|new_ino
)paren
)paren
)paren
(brace
id|iput
c_func
(paren
id|old_inode
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|new_inode-&gt;i_mode
)paren
)paren
(brace
id|iput
c_func
(paren
id|new_inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|old_inode
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|new_inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|new_inode-&gt;i_data
(braket
id|D_BUSY
)braket
op_assign
l_int|1
suffix:semicolon
id|new_inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|new_de-&gt;name
(braket
l_int|0
)braket
op_assign
id|DELETED_FLAG
suffix:semicolon
id|new_bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|free_de
comma
id|old_de
comma
r_sizeof
(paren
r_struct
id|msdos_dir_entry
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|free_de-&gt;name
comma
id|new_name
comma
id|MSDOS_NAME
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|free_inode
op_assign
id|iget
c_func
(paren
id|new_dir-&gt;i_dev
comma
id|free_ino
)paren
)paren
)paren
(brace
id|free_de-&gt;name
(braket
l_int|0
)braket
op_assign
id|DELETED_FLAG
suffix:semicolon
multiline_comment|/*  Don&squot;t mark free_bh as dirty. Both states are supposed to be equivalent. */
id|brelse
c_func
(paren
id|free_bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exists
)paren
(brace
id|iput
c_func
(paren
id|new_inode
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|msdos_read_inode
c_func
(paren
id|free_inode
)paren
suffix:semicolon
id|old_inode-&gt;i_data
(braket
id|D_BUSY
)braket
op_assign
l_int|1
suffix:semicolon
id|old_inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|old_de-&gt;name
(braket
l_int|0
)braket
op_assign
id|DELETED_FLAG
suffix:semicolon
id|old_bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|free_bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exists
)paren
id|iput
c_func
(paren
id|free_inode
)paren
suffix:semicolon
r_else
(brace
id|new_inode-&gt;i_data
(braket
id|D_DEPEND
)braket
op_assign
(paren
r_int
)paren
id|free_inode
suffix:semicolon
id|free_inode-&gt;i_data
(braket
id|D_OLD
)braket
op_assign
(paren
r_int
)paren
id|new_inode
suffix:semicolon
multiline_comment|/* free_inode is put when putting new_inode */
id|iput
c_func
(paren
id|new_inode
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|old_inode-&gt;i_mode
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|msdos_scan
c_func
(paren
id|old_inode
comma
id|MSDOS_DOTDOT
comma
op_amp
id|dotdot_bh
comma
op_amp
id|dotdot_de
comma
op_amp
id|dotdot_ino
)paren
)paren
OL
l_int|0
)paren
r_goto
id|rename_done
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dotdot_inode
op_assign
id|iget
c_func
(paren
id|old_inode-&gt;i_dev
comma
id|dotdot_ino
)paren
)paren
)paren
(brace
id|brelse
c_func
(paren
id|dotdot_bh
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|rename_done
suffix:semicolon
)brace
id|dotdot_de-&gt;start
op_assign
id|dotdot_inode-&gt;i_data
(braket
id|D_START
)braket
op_assign
id|new_dir-&gt;i_data
(braket
id|D_START
)braket
suffix:semicolon
id|dotdot_inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|dotdot_bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|iput
c_func
(paren
id|dotdot_inode
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|dotdot_bh
)paren
suffix:semicolon
)brace
id|error
op_assign
l_int|0
suffix:semicolon
id|rename_done
suffix:colon
id|brelse
c_func
(paren
id|free_bh
)paren
suffix:semicolon
id|iput
c_func
(paren
id|old_inode
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|msdos_rename
r_int
id|msdos_rename
c_func
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_const
r_char
op_star
id|old_name
comma
r_int
id|old_len
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_const
r_char
op_star
id|new_name
comma
r_int
id|new_len
)paren
(brace
r_char
id|old_msdos_name
(braket
id|MSDOS_NAME
)braket
comma
id|new_msdos_name
(braket
id|MSDOS_NAME
)braket
suffix:semicolon
r_struct
id|buffer_head
op_star
id|old_bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|old_de
suffix:semicolon
r_int
id|old_ino
comma
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|msdos_format_name
c_func
(paren
id|MSDOS_SB
c_func
(paren
id|old_dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|name_check
comma
id|old_name
comma
id|old_len
comma
id|old_msdos_name
)paren
)paren
OL
l_int|0
)paren
r_goto
id|rename_done
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|msdos_format_name
c_func
(paren
id|MSDOS_SB
c_func
(paren
id|new_dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|name_check
comma
id|new_name
comma
id|new_len
comma
id|new_msdos_name
)paren
)paren
OL
l_int|0
)paren
r_goto
id|rename_done
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|msdos_scan
c_func
(paren
id|old_dir
comma
id|old_msdos_name
comma
op_amp
id|old_bh
comma
op_amp
id|old_de
comma
op_amp
id|old_ino
)paren
)paren
OL
l_int|0
)paren
r_goto
id|rename_done
suffix:semicolon
id|lock_creation
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old_dir
op_eq
id|new_dir
)paren
id|error
op_assign
id|rename_same_dir
c_func
(paren
id|old_dir
comma
id|old_msdos_name
comma
id|new_dir
comma
id|new_msdos_name
comma
id|old_bh
comma
id|old_de
comma
id|old_ino
)paren
suffix:semicolon
r_else
id|error
op_assign
id|rename_diff_dir
c_func
(paren
id|old_dir
comma
id|old_msdos_name
comma
id|new_dir
comma
id|new_msdos_name
comma
id|old_bh
comma
id|old_de
comma
id|old_ino
)paren
suffix:semicolon
id|unlock_creation
c_func
(paren
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|old_bh
)paren
suffix:semicolon
id|rename_done
suffix:colon
id|iput
c_func
(paren
id|old_dir
)paren
suffix:semicolon
id|iput
c_func
(paren
id|new_dir
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
