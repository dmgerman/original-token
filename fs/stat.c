multiline_comment|/*&n; *  linux/fs/stat.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#if !defined(__alpha__) &amp;&amp; !defined(__sparc__)
multiline_comment|/*&n; * For backward compatibility?  Maybe this should be moved&n; * into arch/i386 instead?&n; */
DECL|function|cp_old_stat
r_static
r_void
id|cp_old_stat
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|__old_kernel_stat
op_star
id|statbuf
)paren
(brace
r_struct
id|__old_kernel_stat
id|tmp
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;VFS: Warning: %s using old stat() call. Recompile your binary.&bslash;n&quot;
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|tmp.st_dev
op_assign
id|kdev_t_to_nr
c_func
(paren
id|inode-&gt;i_dev
)paren
suffix:semicolon
id|tmp.st_ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|tmp.st_mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|tmp.st_nlink
op_assign
id|inode-&gt;i_nlink
suffix:semicolon
id|tmp.st_uid
op_assign
id|inode-&gt;i_uid
suffix:semicolon
id|tmp.st_gid
op_assign
id|inode-&gt;i_gid
suffix:semicolon
id|tmp.st_rdev
op_assign
id|kdev_t_to_nr
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|tmp.st_size
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_pipe
)paren
id|tmp.st_size
op_assign
id|PIPE_SIZE
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
id|tmp.st_atime
op_assign
id|inode-&gt;i_atime
suffix:semicolon
id|tmp.st_mtime
op_assign
id|inode-&gt;i_mtime
suffix:semicolon
id|tmp.st_ctime
op_assign
id|inode-&gt;i_ctime
suffix:semicolon
id|copy_to_user
c_func
(paren
id|statbuf
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|cp_new_stat
r_static
r_void
id|cp_new_stat
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|stat
op_star
id|statbuf
)paren
(brace
r_struct
id|stat
id|tmp
suffix:semicolon
r_int
r_int
id|blocks
comma
id|indirect
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tmp
comma
l_int|0
comma
r_sizeof
(paren
id|tmp
)paren
)paren
suffix:semicolon
id|tmp.st_dev
op_assign
id|kdev_t_to_nr
c_func
(paren
id|inode-&gt;i_dev
)paren
suffix:semicolon
id|tmp.st_ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|tmp.st_mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|tmp.st_nlink
op_assign
id|inode-&gt;i_nlink
suffix:semicolon
id|tmp.st_uid
op_assign
id|inode-&gt;i_uid
suffix:semicolon
id|tmp.st_gid
op_assign
id|inode-&gt;i_gid
suffix:semicolon
id|tmp.st_rdev
op_assign
id|kdev_t_to_nr
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|tmp.st_size
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_pipe
)paren
id|tmp.st_size
op_assign
id|PIPE_SIZE
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
id|tmp.st_atime
op_assign
id|inode-&gt;i_atime
suffix:semicolon
id|tmp.st_mtime
op_assign
id|inode-&gt;i_mtime
suffix:semicolon
id|tmp.st_ctime
op_assign
id|inode-&gt;i_ctime
suffix:semicolon
multiline_comment|/*&n; * st_blocks and st_blksize are approximated with a simple algorithm if&n; * they aren&squot;t supported directly by the filesystem. The minix and msdos&n; * filesystems don&squot;t keep track of blocks, so they would either have to&n; * be counted explicitly (by delving into the file itself), or by using&n; * this simple algorithm to get a reasonable (although not 100% accurate)&n; * value.&n; */
multiline_comment|/*&n; * Use minix fs values for the number of direct and indirect blocks.  The&n; * count is now exact for the minix fs except that it counts zero blocks.&n; * Everything is in BLOCK_SIZE&squot;d units until the assignment to&n; * tmp.st_blksize.&n; */
DECL|macro|D_B
mdefine_line|#define D_B   7
DECL|macro|I_B
mdefine_line|#define I_B   (BLOCK_SIZE / sizeof(unsigned short))
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_blksize
)paren
(brace
id|blocks
op_assign
(paren
id|tmp.st_size
op_plus
id|BLOCK_SIZE
op_minus
l_int|1
)paren
op_div
id|BLOCK_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|blocks
OG
id|D_B
)paren
(brace
id|indirect
op_assign
(paren
id|blocks
op_minus
id|D_B
op_plus
id|I_B
op_minus
l_int|1
)paren
op_div
id|I_B
suffix:semicolon
id|blocks
op_add_assign
id|indirect
suffix:semicolon
r_if
c_cond
(paren
id|indirect
OG
l_int|1
)paren
(brace
id|indirect
op_assign
(paren
id|indirect
op_minus
l_int|1
op_plus
id|I_B
op_minus
l_int|1
)paren
op_div
id|I_B
suffix:semicolon
id|blocks
op_add_assign
id|indirect
suffix:semicolon
r_if
c_cond
(paren
id|indirect
OG
l_int|1
)paren
id|blocks
op_increment
suffix:semicolon
)brace
)brace
id|tmp.st_blocks
op_assign
(paren
id|BLOCK_SIZE
op_div
l_int|512
)paren
op_star
id|blocks
suffix:semicolon
id|tmp.st_blksize
op_assign
id|BLOCK_SIZE
suffix:semicolon
)brace
r_else
(brace
id|tmp.st_blocks
op_assign
id|inode-&gt;i_blocks
suffix:semicolon
id|tmp.st_blksize
op_assign
id|inode-&gt;i_blksize
suffix:semicolon
)brace
id|copy_to_user
c_func
(paren
id|statbuf
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
macro_line|#if !defined(__alpha__) &amp;&amp; !defined(__sparc__)
multiline_comment|/*&n; * For backward compatibility?  Maybe this should be moved&n; * into arch/i386 instead?&n; */
DECL|function|sys_stat
id|asmlinkage
r_int
id|sys_stat
c_func
(paren
r_char
op_star
id|filename
comma
r_struct
id|__old_kernel_stat
op_star
id|statbuf
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|statbuf
comma
r_sizeof
(paren
op_star
id|statbuf
)paren
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
id|error
op_assign
id|namei
c_func
(paren
id|filename
comma
op_amp
id|inode
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
id|cp_old_stat
c_func
(paren
id|inode
comma
id|statbuf
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|sys_newstat
id|asmlinkage
r_int
id|sys_newstat
c_func
(paren
r_char
op_star
id|filename
comma
r_struct
id|stat
op_star
id|statbuf
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|statbuf
comma
r_sizeof
(paren
op_star
id|statbuf
)paren
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
id|error
op_assign
id|namei
c_func
(paren
id|filename
comma
op_amp
id|inode
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
id|cp_new_stat
c_func
(paren
id|inode
comma
id|statbuf
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if !defined(__alpha__) &amp;&amp; !defined(__sparc__)
multiline_comment|/*&n; * For backward compatibility?  Maybe this should be moved&n; * into arch/i386 instead?&n; */
DECL|function|sys_lstat
id|asmlinkage
r_int
id|sys_lstat
c_func
(paren
r_char
op_star
id|filename
comma
r_struct
id|__old_kernel_stat
op_star
id|statbuf
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|statbuf
comma
r_sizeof
(paren
op_star
id|statbuf
)paren
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
id|error
op_assign
id|lnamei
c_func
(paren
id|filename
comma
op_amp
id|inode
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
id|cp_old_stat
c_func
(paren
id|inode
comma
id|statbuf
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|sys_newlstat
id|asmlinkage
r_int
id|sys_newlstat
c_func
(paren
r_char
op_star
id|filename
comma
r_struct
id|stat
op_star
id|statbuf
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|statbuf
comma
r_sizeof
(paren
op_star
id|statbuf
)paren
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
id|error
op_assign
id|lnamei
c_func
(paren
id|filename
comma
op_amp
id|inode
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
id|cp_new_stat
c_func
(paren
id|inode
comma
id|statbuf
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if !defined(__alpha__) &amp;&amp; !defined(__sparc__)
multiline_comment|/*&n; * For backward compatibility?  Maybe this should be moved&n; * into arch/i386 instead?&n; */
DECL|function|sys_fstat
id|asmlinkage
r_int
id|sys_fstat
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|__old_kernel_stat
op_star
id|statbuf
)paren
(brace
r_struct
id|file
op_star
id|f
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|statbuf
comma
r_sizeof
(paren
op_star
id|statbuf
)paren
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
id|fd
op_ge
id|NR_OPEN
op_logical_or
op_logical_neg
(paren
id|f
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
op_logical_or
op_logical_neg
(paren
id|inode
op_assign
id|f-&gt;f_inode
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
id|cp_old_stat
c_func
(paren
id|inode
comma
id|statbuf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|sys_newfstat
id|asmlinkage
r_int
id|sys_newfstat
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|stat
op_star
id|statbuf
)paren
(brace
r_struct
id|file
op_star
id|f
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|statbuf
comma
r_sizeof
(paren
op_star
id|statbuf
)paren
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
id|fd
op_ge
id|NR_OPEN
op_logical_or
op_logical_neg
(paren
id|f
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
op_logical_or
op_logical_neg
(paren
id|inode
op_assign
id|f-&gt;f_inode
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
id|cp_new_stat
c_func
(paren
id|inode
comma
id|statbuf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_readlink
id|asmlinkage
r_int
id|sys_readlink
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_char
op_star
id|buf
comma
r_int
id|bufsiz
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|bufsiz
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|bufsiz
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
id|error
op_assign
id|lnamei
c_func
(paren
id|path
comma
op_amp
id|inode
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
op_logical_neg
id|inode-&gt;i_op
op_logical_or
op_logical_neg
id|inode-&gt;i_op-&gt;readlink
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|inode-&gt;i_op
op_member_access_from_pointer
id|readlink
c_func
(paren
id|inode
comma
id|buf
comma
id|bufsiz
)paren
suffix:semicolon
)brace
eof
