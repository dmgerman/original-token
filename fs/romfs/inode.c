multiline_comment|/*&n; * ROMFS file system, Linux implementation&n; *&n; * Copyright (C) 1997  Janos Farkas &lt;chexum@shadow.banki.hu&gt;&n; *&n; * Using parts of the minix filesystem&n; * Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; * and parts of the affs filesystem additionally&n; * Copyright (C) 1993  Ray Burr&n; * Copyright (C) 1996  Hans-Joachim Widmaier&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Changes&n; *&t;&t;&t;&t;&t;Changed for 2.1.19 modules&n; *&t;Jan 1997&t;&t;&t;Initial release&n; *&t;Jun 1997&t;&t;&t;2.1.43+ changes&n; *&t;&t;&t;&t;&t;Proper page locking in readpage&n; *&t;&t;&t;&t;&t;Changed to work with 2.1.45+ fs&n; *&t;Jul 1997&t;&t;&t;Fixed follow_link&n; *&t;&t;&t;2.1.47&n; *&t;&t;&t;&t;&t;lookup shouldn&squot;t return -ENOENT&n; *&t;&t;&t;&t;&t;from Horst von Brand:&n; *&t;&t;&t;&t;&t;  fail on wrong checksum&n; *&t;&t;&t;&t;&t;  double unlock_super was possible&n; *&t;&t;&t;&t;&t;  correct namelen for statfs&n; *&t;&t;&t;&t;&t;spotted by Bill Hawes:&n; *&t;&t;&t;&t;&t;  readlink shouldn&squot;t iput()&n; */
multiline_comment|/* todo:&n; *&t;- see Documentation/filesystems/romfs.txt&n; *&t;- use malloced memory for file names?&n; *&t;- quicklist routines from fs/namei.c, get_page is possibly not&n; *&t;  intended to be used now&n; *&t;- considering write access...&n; *&t;- network (tftp) files?&n; *&t;- in the ancient times something leaked to made umounts&n; *&t;  impossible, but I&squot;ve not seen it in the last months&n; */
multiline_comment|/*&n; * Sorry about some optimizations and for some goto&squot;s.  I just wanted&n; * to squeeze some more bytes out of this code.. :)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/romfs_fs.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|min
r_static
r_int
r_inline
id|min
c_func
(paren
r_int
id|a
comma
r_int
id|b
)paren
(brace
r_return
id|a
OL
id|b
ques
c_cond
id|a
suffix:colon
id|b
suffix:semicolon
)brace
r_static
id|__s32
DECL|function|romfs_checksum
id|romfs_checksum
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|__s32
id|sum
comma
op_star
id|ptr
suffix:semicolon
id|sum
op_assign
l_int|0
suffix:semicolon
id|ptr
op_assign
id|data
suffix:semicolon
id|size
op_rshift_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
id|sum
op_add_assign
id|ntohl
c_func
(paren
op_star
id|ptr
op_increment
)paren
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
r_return
id|sum
suffix:semicolon
)brace
DECL|variable|romfs_ops
r_static
r_struct
id|super_operations
id|romfs_ops
suffix:semicolon
r_static
r_struct
id|super_block
op_star
DECL|function|romfs_read_super
id|romfs_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|s-&gt;s_dev
suffix:semicolon
r_struct
id|romfs_super_block
op_star
id|rsb
suffix:semicolon
r_int
id|sz
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
multiline_comment|/* I would parse the options here, but there are none.. :) */
id|lock_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|set_blocksize
c_func
(paren
id|dev
comma
id|ROMBSIZE
)paren
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
id|ROMBSIZE
suffix:semicolon
id|s-&gt;s_blocksize_bits
op_assign
id|ROMBSBITS
suffix:semicolon
id|bh
op_assign
id|bread
c_func
(paren
id|dev
comma
l_int|0
comma
id|ROMBSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
multiline_comment|/* XXX merge with other printk? */
id|printk
(paren
l_string|&quot;romfs: unable to read superblock&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|outnobh
suffix:semicolon
)brace
id|rsb
op_assign
(paren
r_struct
id|romfs_super_block
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|sz
op_assign
id|ntohl
c_func
(paren
id|rsb-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rsb-&gt;word0
op_ne
id|ROMSB_WORD0
op_logical_or
id|rsb-&gt;word1
op_ne
id|ROMSB_WORD1
op_logical_or
id|sz
OL
id|ROMFH_SIZE
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
(paren
l_string|&quot;VFS: Can&squot;t find a romfs filesystem on dev &quot;
l_string|&quot;%s.&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|romfs_checksum
c_func
(paren
id|rsb
comma
id|min
c_func
(paren
id|sz
comma
l_int|512
)paren
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;romfs: bad initial checksum on dev &quot;
l_string|&quot;%s.&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|s-&gt;s_magic
op_assign
id|ROMFS_MAGIC
suffix:semicolon
id|s-&gt;u.romfs_sb.s_maxsize
op_assign
id|sz
suffix:semicolon
id|s-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
multiline_comment|/* Find the start of the fs */
id|sz
op_assign
(paren
id|ROMFH_SIZE
op_plus
id|strnlen
c_func
(paren
id|rsb-&gt;name
comma
id|ROMFS_MAXFN
)paren
op_plus
l_int|1
op_plus
id|ROMFH_PAD
)paren
op_amp
id|ROMFH_MASK
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|romfs_ops
suffix:semicolon
id|s-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|iget
c_func
(paren
id|s
comma
id|sz
)paren
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;s_root
)paren
r_goto
id|outnobh
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
multiline_comment|/* Ehrhm; sorry.. :)  And thanks to Hans-Joachim Widmaier  :) */
r_if
c_cond
(paren
l_int|0
)paren
(brace
id|out
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|outnobh
suffix:colon
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|s
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|s
suffix:semicolon
)brace
multiline_comment|/* Nothing to do.. */
r_static
r_void
DECL|function|romfs_put_super
id|romfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* That&squot;s simple too. */
r_static
r_int
DECL|function|romfs_statfs
id|romfs_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|statfs
op_star
id|buf
comma
r_int
id|bufsize
)paren
(brace
r_struct
id|statfs
id|tmp
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
id|tmp.f_type
op_assign
id|ROMFS_MAGIC
suffix:semicolon
id|tmp.f_bsize
op_assign
id|ROMBSIZE
suffix:semicolon
id|tmp.f_blocks
op_assign
(paren
id|sb-&gt;u.romfs_sb.s_maxsize
op_plus
id|ROMBSIZE
op_minus
l_int|1
)paren
op_rshift
id|ROMBSBITS
suffix:semicolon
id|tmp.f_namelen
op_assign
id|ROMFS_MAXFN
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|tmp
comma
id|bufsize
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/* some helper routines */
r_static
r_int
DECL|function|romfs_strnlen
id|romfs_strnlen
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_int
id|avail
comma
id|maxsize
comma
id|res
suffix:semicolon
id|maxsize
op_assign
id|i-&gt;i_sb-&gt;u.romfs_sb.s_maxsize
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|maxsize
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* strnlen is almost always valid */
r_if
c_cond
(paren
id|count
OG
id|maxsize
op_logical_or
id|offset
op_plus
id|count
OG
id|maxsize
)paren
id|count
op_assign
id|maxsize
op_minus
id|offset
suffix:semicolon
id|bh
op_assign
id|bread
c_func
(paren
id|i-&gt;i_dev
comma
id|offset
op_rshift
id|ROMBSBITS
comma
id|ROMBSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* error */
id|avail
op_assign
id|ROMBSIZE
op_minus
(paren
id|offset
op_amp
id|ROMBMASK
)paren
suffix:semicolon
id|maxsize
op_assign
id|min
c_func
(paren
id|count
comma
id|avail
)paren
suffix:semicolon
id|res
op_assign
id|strnlen
c_func
(paren
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
id|offset
op_amp
id|ROMBMASK
)paren
comma
id|maxsize
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
id|res
OL
id|maxsize
)paren
r_return
id|res
suffix:semicolon
multiline_comment|/* found all of it */
r_while
c_loop
(paren
id|res
OL
id|count
)paren
(brace
id|offset
op_add_assign
id|maxsize
suffix:semicolon
id|bh
op_assign
id|bread
c_func
(paren
id|i-&gt;i_dev
comma
id|offset
op_rshift
id|ROMBSBITS
comma
id|ROMBSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|maxsize
op_assign
id|min
c_func
(paren
id|count
op_minus
id|res
comma
id|ROMBSIZE
)paren
suffix:semicolon
id|avail
op_assign
id|strnlen
c_func
(paren
id|bh-&gt;b_data
comma
id|maxsize
)paren
suffix:semicolon
id|res
op_add_assign
id|avail
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
id|avail
OL
id|maxsize
)paren
r_return
id|res
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
r_static
r_int
DECL|function|romfs_copyfrom
id|romfs_copyfrom
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_void
op_star
id|dest
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_int
id|avail
comma
id|maxsize
comma
id|res
suffix:semicolon
id|maxsize
op_assign
id|i-&gt;i_sb-&gt;u.romfs_sb.s_maxsize
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|maxsize
op_logical_or
id|count
OG
id|maxsize
op_logical_or
id|offset
op_plus
id|count
OG
id|maxsize
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|bh
op_assign
id|bread
c_func
(paren
id|i-&gt;i_dev
comma
id|offset
op_rshift
id|ROMBSBITS
comma
id|ROMBSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* error */
id|avail
op_assign
id|ROMBSIZE
op_minus
(paren
id|offset
op_amp
id|ROMBMASK
)paren
suffix:semicolon
id|maxsize
op_assign
id|min
c_func
(paren
id|count
comma
id|avail
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dest
comma
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
id|offset
op_amp
id|ROMBMASK
)paren
comma
id|maxsize
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|res
op_assign
id|maxsize
suffix:semicolon
multiline_comment|/* all of it */
r_while
c_loop
(paren
id|res
OL
id|count
)paren
(brace
id|offset
op_add_assign
id|maxsize
suffix:semicolon
id|dest
op_add_assign
id|maxsize
suffix:semicolon
id|bh
op_assign
id|bread
c_func
(paren
id|i-&gt;i_dev
comma
id|offset
op_rshift
id|ROMBSBITS
comma
id|ROMBSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|maxsize
op_assign
id|min
c_func
(paren
id|count
op_minus
id|res
comma
id|ROMBSIZE
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dest
comma
id|bh-&gt;b_data
comma
id|maxsize
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|res
op_add_assign
id|maxsize
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
r_static
r_int
DECL|function|romfs_readdir
id|romfs_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_struct
id|inode
op_star
id|i
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|romfs_inode
id|ri
suffix:semicolon
r_int
r_int
id|offset
comma
id|maxoff
suffix:semicolon
r_int
id|j
comma
id|ino
comma
id|nextfh
suffix:semicolon
r_int
id|stored
op_assign
l_int|0
suffix:semicolon
r_char
id|fsname
(braket
id|ROMFS_MAXFN
)braket
suffix:semicolon
multiline_comment|/* XXX dynamic? */
r_if
c_cond
(paren
op_logical_neg
id|i
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|i-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
id|maxoff
op_assign
id|i-&gt;i_sb-&gt;u.romfs_sb.s_maxsize
suffix:semicolon
id|offset
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|offset
)paren
(brace
id|offset
op_assign
id|i-&gt;i_ino
op_amp
id|ROMFH_MASK
suffix:semicolon
r_if
c_cond
(paren
id|romfs_copyfrom
c_func
(paren
id|i
comma
op_amp
id|ri
comma
id|offset
comma
id|ROMFH_SIZE
)paren
op_le
l_int|0
)paren
r_return
id|stored
suffix:semicolon
id|offset
op_assign
id|ntohl
c_func
(paren
id|ri.spec
)paren
op_amp
id|ROMFH_MASK
suffix:semicolon
)brace
multiline_comment|/* Not really failsafe, but we are read-only... */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|offset
op_logical_or
id|offset
op_ge
id|maxoff
)paren
(brace
id|offset
op_assign
l_int|0xffffffff
suffix:semicolon
id|filp-&gt;f_pos
op_assign
id|offset
suffix:semicolon
r_return
id|stored
suffix:semicolon
)brace
id|filp-&gt;f_pos
op_assign
id|offset
suffix:semicolon
multiline_comment|/* Fetch inode info */
r_if
c_cond
(paren
id|romfs_copyfrom
c_func
(paren
id|i
comma
op_amp
id|ri
comma
id|offset
comma
id|ROMFH_SIZE
)paren
op_le
l_int|0
)paren
r_return
id|stored
suffix:semicolon
id|j
op_assign
id|romfs_strnlen
c_func
(paren
id|i
comma
id|offset
op_plus
id|ROMFH_SIZE
comma
r_sizeof
(paren
id|fsname
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
l_int|0
)paren
r_return
id|stored
suffix:semicolon
id|fsname
(braket
id|j
)braket
op_assign
l_int|0
suffix:semicolon
id|romfs_copyfrom
c_func
(paren
id|i
comma
id|fsname
comma
id|offset
op_plus
id|ROMFH_SIZE
comma
id|j
)paren
suffix:semicolon
id|ino
op_assign
id|offset
suffix:semicolon
id|nextfh
op_assign
id|ntohl
c_func
(paren
id|ri.next
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nextfh
op_amp
id|ROMFH_TYPE
)paren
op_eq
id|ROMFH_HRD
)paren
id|ino
op_assign
id|ntohl
c_func
(paren
id|ri.spec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|fsname
comma
id|j
comma
id|offset
comma
id|ino
)paren
OL
l_int|0
)paren
(brace
r_return
id|stored
suffix:semicolon
)brace
id|stored
op_increment
suffix:semicolon
id|offset
op_assign
id|nextfh
op_amp
id|ROMFH_MASK
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|romfs_lookup
id|romfs_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_int
r_int
id|offset
comma
id|maxoff
suffix:semicolon
r_int
id|fslen
comma
id|res
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_char
id|fsname
(braket
id|ROMFS_MAXFN
)braket
suffix:semicolon
multiline_comment|/* XXX dynamic? */
r_struct
id|romfs_inode
id|ri
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* got from dentry */
r_int
id|len
suffix:semicolon
id|res
op_assign
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|dir-&gt;i_mode
)paren
)paren
r_goto
id|out
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* instead of ENOENT */
id|offset
op_assign
id|dir-&gt;i_ino
op_amp
id|ROMFH_MASK
suffix:semicolon
r_if
c_cond
(paren
id|romfs_copyfrom
c_func
(paren
id|dir
comma
op_amp
id|ri
comma
id|offset
comma
id|ROMFH_SIZE
)paren
op_le
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|maxoff
op_assign
id|dir-&gt;i_sb-&gt;u.romfs_sb.s_maxsize
suffix:semicolon
id|offset
op_assign
id|ntohl
c_func
(paren
id|ri.spec
)paren
op_amp
id|ROMFH_MASK
suffix:semicolon
multiline_comment|/* ok, now find the file, whose name is in &quot;dentry&quot;, in the&n;&t; * directory specified by &quot;dir&quot;.  */
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
id|len
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|offset
op_logical_or
id|offset
op_ge
id|maxoff
op_logical_or
id|romfs_copyfrom
c_func
(paren
id|dir
comma
op_amp
id|ri
comma
id|offset
comma
id|ROMFH_SIZE
)paren
op_le
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* try to match the first 16 bytes of name */
id|fslen
op_assign
id|romfs_strnlen
c_func
(paren
id|dir
comma
id|offset
op_plus
id|ROMFH_SIZE
comma
id|ROMFH_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|ROMFH_SIZE
)paren
(brace
r_if
c_cond
(paren
id|len
op_eq
id|fslen
)paren
(brace
multiline_comment|/* both are shorter, and same size */
id|romfs_copyfrom
c_func
(paren
id|dir
comma
id|fsname
comma
id|offset
op_plus
id|ROMFH_SIZE
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
(paren
id|name
comma
id|fsname
comma
id|len
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|fslen
op_ge
id|ROMFH_SIZE
)paren
(brace
multiline_comment|/* both are longer; XXX optimize max size */
id|fslen
op_assign
id|romfs_strnlen
c_func
(paren
id|dir
comma
id|offset
op_plus
id|ROMFH_SIZE
comma
r_sizeof
(paren
id|fsname
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
id|fslen
)paren
(brace
id|romfs_copyfrom
c_func
(paren
id|dir
comma
id|fsname
comma
id|offset
op_plus
id|ROMFH_SIZE
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|name
comma
id|fsname
comma
id|len
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* next entry */
id|offset
op_assign
id|ntohl
c_func
(paren
id|ri.next
)paren
op_amp
id|ROMFH_MASK
suffix:semicolon
)brace
multiline_comment|/* Hard link handling */
r_if
c_cond
(paren
(paren
id|ntohl
c_func
(paren
id|ri.next
)paren
op_amp
id|ROMFH_TYPE
)paren
op_eq
id|ROMFH_HRD
)paren
id|offset
op_assign
id|ntohl
c_func
(paren
id|ri.spec
)paren
op_amp
id|ROMFH_MASK
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inode
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_sb
comma
id|offset
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|res
op_assign
op_minus
id|EACCES
suffix:semicolon
)brace
r_else
(brace
id|d_add
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * Ok, we do readpage, to be able to execute programs.  Unfortunately,&n; * we can&squot;t use bmap, since we have looser alignments.&n; */
r_static
r_int
DECL|function|romfs_readpage
id|romfs_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
r_int
id|buf
suffix:semicolon
r_int
r_int
id|offset
comma
id|avail
comma
id|readlen
suffix:semicolon
r_int
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|page-&gt;count
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_locked
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|buf
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|PG_uptodate
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|PG_error
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|offset
op_assign
id|page-&gt;offset
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
id|inode-&gt;i_size
)paren
(brace
id|avail
op_assign
id|inode-&gt;i_size
op_minus
id|offset
suffix:semicolon
id|readlen
op_assign
id|min
c_func
(paren
id|avail
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|romfs_copyfrom
c_func
(paren
id|inode
comma
(paren
r_void
op_star
)paren
id|buf
comma
id|inode-&gt;u.romfs_i.i_dataoffset
op_plus
id|offset
comma
id|readlen
)paren
op_eq
id|readlen
)paren
(brace
r_if
c_cond
(paren
id|readlen
OL
id|PAGE_SIZE
)paren
(brace
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|buf
op_plus
id|readlen
)paren
comma
l_int|0
comma
id|PAGE_SIZE
op_minus
id|readlen
)paren
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|PG_uptodate
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|result
)paren
(brace
id|set_bit
c_func
(paren
id|PG_error
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|buf
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
id|PG_locked
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|page-&gt;wait
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
r_int
DECL|function|romfs_readlink
id|romfs_readlink
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|buffer
comma
r_int
id|len
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|mylen
suffix:semicolon
r_char
id|buf
(braket
id|ROMFS_MAXFN
)braket
suffix:semicolon
multiline_comment|/* XXX dynamic */
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
op_logical_neg
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|mylen
op_assign
op_minus
id|EBADF
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|mylen
op_assign
id|min
c_func
(paren
r_sizeof
(paren
id|buf
)paren
comma
id|inode-&gt;i_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|romfs_copyfrom
c_func
(paren
id|inode
comma
id|buf
comma
id|inode-&gt;u.romfs_i.i_dataoffset
comma
id|mylen
)paren
op_le
l_int|0
)paren
(brace
id|mylen
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|copy_to_user
c_func
(paren
id|buffer
comma
id|buf
comma
id|mylen
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|mylen
suffix:semicolon
)brace
DECL|function|romfs_follow_link
r_static
r_struct
id|dentry
op_star
id|romfs_follow_link
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|dentry
op_star
id|base
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_char
op_star
id|link
suffix:semicolon
r_int
id|len
comma
id|cnt
suffix:semicolon
id|len
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|dentry
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EAGAIN
)paren
suffix:semicolon
multiline_comment|/* correct? */
r_if
c_cond
(paren
op_logical_neg
(paren
id|link
op_assign
id|kmalloc
c_func
(paren
id|len
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_goto
id|outnobuf
suffix:semicolon
id|cnt
op_assign
id|romfs_copyfrom
c_func
(paren
id|inode
comma
id|link
comma
id|inode-&gt;u.romfs_i.i_dataoffset
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
id|cnt
)paren
(brace
id|dentry
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_else
id|link
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|dentry
op_assign
id|lookup_dentry
c_func
(paren
id|link
comma
id|base
comma
l_int|1
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
)paren
(brace
id|out
suffix:colon
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
id|outnobuf
suffix:colon
id|dput
c_func
(paren
id|base
)paren
suffix:semicolon
)brace
r_return
id|dentry
suffix:semicolon
)brace
multiline_comment|/* Mapping from our types to the kernel */
DECL|variable|romfs_file_operations
r_static
r_struct
id|file_operations
id|romfs_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|generic_file_read
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write - bad */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll - default */
l_int|NULL
comma
multiline_comment|/* ioctl */
id|generic_file_mmap
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* release */
l_int|NULL
comma
multiline_comment|/* fsync */
l_int|NULL
comma
multiline_comment|/* fasync */
l_int|NULL
comma
multiline_comment|/* check_media_change */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
DECL|variable|romfs_file_inode_operations
r_static
r_struct
id|inode_operations
id|romfs_file_inode_operations
op_assign
(brace
op_amp
id|romfs_file_operations
comma
l_int|NULL
comma
multiline_comment|/* create */
l_int|NULL
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
l_int|NULL
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
l_int|NULL
comma
multiline_comment|/* mkdir */
l_int|NULL
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
l_int|NULL
comma
multiline_comment|/* rename */
l_int|NULL
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* follow_link */
id|romfs_readpage
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* bmap -- not really */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
)brace
suffix:semicolon
DECL|variable|romfs_dir_operations
r_static
r_struct
id|file_operations
id|romfs_dir_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
l_int|NULL
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write - bad */
id|romfs_readdir
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll - default */
l_int|NULL
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* release */
l_int|NULL
comma
multiline_comment|/* fsync */
l_int|NULL
comma
multiline_comment|/* fasync */
l_int|NULL
comma
multiline_comment|/* check_media_change */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
multiline_comment|/* Merged dir/symlink op table.  readdir/lookup/readlink/follow_link&n; * will protect from type mismatch.&n; */
DECL|variable|romfs_dir_inode_operations
r_static
r_struct
id|inode_operations
id|romfs_dir_inode_operations
op_assign
(brace
op_amp
id|romfs_dir_operations
comma
l_int|NULL
comma
multiline_comment|/* create */
id|romfs_lookup
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
l_int|NULL
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
l_int|NULL
comma
multiline_comment|/* mkdir */
l_int|NULL
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
l_int|NULL
comma
multiline_comment|/* rename */
l_int|NULL
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
)brace
suffix:semicolon
DECL|variable|romfs_link_inode_operations
r_static
r_struct
id|inode_operations
id|romfs_link_inode_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* no file operations on symlinks */
l_int|NULL
comma
multiline_comment|/* create */
l_int|NULL
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
l_int|NULL
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
l_int|NULL
comma
multiline_comment|/* mkdir */
l_int|NULL
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
l_int|NULL
comma
multiline_comment|/* rename */
id|romfs_readlink
comma
multiline_comment|/* readlink */
id|romfs_follow_link
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
)brace
suffix:semicolon
DECL|variable|romfs_modemap
r_static
id|mode_t
id|romfs_modemap
(braket
)braket
op_assign
(brace
l_int|0
comma
id|S_IFDIR
comma
id|S_IFREG
comma
id|S_IFLNK
op_plus
l_int|0777
comma
id|S_IFBLK
comma
id|S_IFCHR
comma
id|S_IFSOCK
comma
id|S_IFIFO
)brace
suffix:semicolon
DECL|variable|romfs_inoops
r_static
r_struct
id|inode_operations
op_star
id|romfs_inoops
(braket
)braket
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* hardlink, handled elsewhere */
op_amp
id|romfs_dir_inode_operations
comma
op_amp
id|romfs_file_inode_operations
comma
op_amp
id|romfs_link_inode_operations
comma
op_amp
id|blkdev_inode_operations
comma
multiline_comment|/* standard handlers */
op_amp
id|chrdev_inode_operations
comma
l_int|NULL
comma
multiline_comment|/* socket */
l_int|NULL
comma
multiline_comment|/* fifo */
)brace
suffix:semicolon
r_static
r_void
DECL|function|romfs_read_inode
id|romfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|i
)paren
(brace
r_int
id|nextfh
comma
id|ino
suffix:semicolon
r_struct
id|romfs_inode
id|ri
suffix:semicolon
id|ino
op_assign
id|i-&gt;i_ino
op_amp
id|ROMFH_MASK
suffix:semicolon
id|i-&gt;i_op
op_assign
l_int|NULL
suffix:semicolon
id|i-&gt;i_mode
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Loop for finding the real hard link */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|romfs_copyfrom
c_func
(paren
id|i
comma
op_amp
id|ri
comma
id|ino
comma
id|ROMFH_SIZE
)paren
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;romfs: read error for inode 0x%x&bslash;n&quot;
comma
id|ino
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* XXX: do romfs_checksum here too (with name) */
id|nextfh
op_assign
id|ntohl
c_func
(paren
id|ri.next
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nextfh
op_amp
id|ROMFH_TYPE
)paren
op_ne
id|ROMFH_HRD
)paren
r_break
suffix:semicolon
id|ino
op_assign
id|ntohl
c_func
(paren
id|ri.spec
)paren
op_amp
id|ROMFH_MASK
suffix:semicolon
)brace
id|i-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Hard to decide.. */
id|i-&gt;i_size
op_assign
id|ntohl
c_func
(paren
id|ri.size
)paren
suffix:semicolon
id|i-&gt;i_mtime
op_assign
id|i-&gt;i_atime
op_assign
id|i-&gt;i_ctime
op_assign
l_int|0
suffix:semicolon
id|i-&gt;i_uid
op_assign
id|i-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
id|i-&gt;i_op
op_assign
id|romfs_inoops
(braket
id|nextfh
op_amp
id|ROMFH_TYPE
)braket
suffix:semicolon
multiline_comment|/* Precalculate the data offset */
id|ino
op_assign
id|romfs_strnlen
c_func
(paren
id|i
comma
id|ino
op_plus
id|ROMFH_SIZE
comma
id|ROMFS_MAXFN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_ge
l_int|0
)paren
id|ino
op_assign
(paren
(paren
id|ROMFH_SIZE
op_plus
id|ino
op_plus
l_int|1
op_plus
id|ROMFH_PAD
)paren
op_amp
id|ROMFH_MASK
)paren
suffix:semicolon
r_else
id|ino
op_assign
l_int|0
suffix:semicolon
id|i-&gt;u.romfs_i.i_metasize
op_assign
id|ino
suffix:semicolon
id|i-&gt;u.romfs_i.i_dataoffset
op_assign
id|ino
op_plus
(paren
id|i-&gt;i_ino
op_amp
id|ROMFH_MASK
)paren
suffix:semicolon
multiline_comment|/* Compute permissions */
id|ino
op_assign
id|S_IRUGO
op_or
id|S_IWUSR
suffix:semicolon
id|ino
op_or_assign
id|romfs_modemap
(braket
id|nextfh
op_amp
id|ROMFH_TYPE
)braket
suffix:semicolon
r_if
c_cond
(paren
id|nextfh
op_amp
id|ROMFH_EXEC
)paren
(brace
id|ino
op_or_assign
id|S_IXUGO
suffix:semicolon
)brace
id|i-&gt;i_mode
op_assign
id|ino
suffix:semicolon
r_if
c_cond
(paren
id|S_ISFIFO
c_func
(paren
id|ino
)paren
)paren
id|init_fifo
c_func
(paren
id|i
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|ino
)paren
)paren
id|i-&gt;i_size
op_assign
id|i-&gt;u.romfs_i.i_metasize
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISBLK
c_func
(paren
id|ino
)paren
op_logical_or
id|S_ISCHR
c_func
(paren
id|ino
)paren
)paren
(brace
id|i-&gt;i_mode
op_and_assign
op_complement
(paren
id|S_IRWXG
op_or
id|S_IRWXO
)paren
suffix:semicolon
id|ino
op_assign
id|ntohl
c_func
(paren
id|ri.spec
)paren
suffix:semicolon
id|i-&gt;i_rdev
op_assign
id|MKDEV
c_func
(paren
id|ino
op_rshift
l_int|16
comma
id|ino
op_amp
l_int|0xffff
)paren
suffix:semicolon
)brace
)brace
DECL|variable|romfs_ops
r_static
r_struct
id|super_operations
id|romfs_ops
op_assign
(brace
id|romfs_read_inode
comma
multiline_comment|/* read inode */
l_int|NULL
comma
multiline_comment|/* write inode */
l_int|NULL
comma
multiline_comment|/* put inode */
l_int|NULL
comma
multiline_comment|/* delete inode */
l_int|NULL
comma
multiline_comment|/* notify change */
id|romfs_put_super
comma
multiline_comment|/* put super */
l_int|NULL
comma
multiline_comment|/* write super */
id|romfs_statfs
comma
multiline_comment|/* statfs */
l_int|NULL
multiline_comment|/* remount */
)brace
suffix:semicolon
DECL|variable|romfs_fs_type
r_static
r_struct
id|file_system_type
id|romfs_fs_type
op_assign
(brace
l_string|&quot;romfs&quot;
comma
id|FS_REQUIRES_DEV
comma
id|romfs_read_super
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|init_romfs_fs
c_func
(paren
r_void
)paren
)paren
(brace
r_return
id|register_filesystem
c_func
(paren
op_amp
id|romfs_fs_type
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
multiline_comment|/* Yes, works even as a module... :) */
id|EXPORT_NO_SYMBOLS
suffix:semicolon
r_int
DECL|function|init_module
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|init_romfs_fs
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|cleanup_module
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|romfs_fs_type
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
