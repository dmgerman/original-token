multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/fs/autofs/inode.c&n; *&n; *  Copyright 1997 Transmeta Corporation -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &quot;autofs_i.h&quot;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/*&n; * Dummy functions - do we ever actually want to do&n; * something here?&n; */
DECL|function|autofs_put_inode
r_static
r_void
id|autofs_put_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
)brace
DECL|function|autofs_delete_inode
r_static
r_void
id|autofs_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|autofs_put_super
r_static
r_void
id|autofs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|autofs_sb_info
op_star
id|sbi
op_assign
(paren
r_struct
id|autofs_sb_info
op_star
)paren
id|sb-&gt;u.generic_sbp
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi-&gt;catatonic
)paren
id|autofs_catatonic_mode
c_func
(paren
id|sbi
)paren
suffix:semicolon
multiline_comment|/* Free wait queues, close pipe */
id|autofs_hash_nuke
c_func
(paren
op_amp
id|sbi-&gt;dirhash
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|AUTOFS_MAX_SYMLINKS
suffix:semicolon
id|n
op_increment
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|n
comma
id|sbi-&gt;symlink_bitmap
)paren
)paren
id|kfree
c_func
(paren
id|sbi-&gt;symlink
(braket
id|n
)braket
dot
id|data
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|sb-&gt;u.generic_sbp
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs: shutting down&bslash;n&quot;
)paren
)paren
suffix:semicolon
macro_line|#ifdef MODULE
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
r_static
r_int
id|autofs_statfs
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
id|bufsiz
)paren
suffix:semicolon
r_static
r_void
id|autofs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_static
r_void
id|autofs_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
DECL|variable|autofs_sops
r_static
r_struct
id|super_operations
id|autofs_sops
op_assign
(brace
id|autofs_read_inode
comma
id|autofs_write_inode
comma
id|autofs_put_inode
comma
id|autofs_delete_inode
comma
l_int|NULL
comma
multiline_comment|/* notify_change */
id|autofs_put_super
comma
l_int|NULL
comma
multiline_comment|/* write_super */
id|autofs_statfs
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|parse_options
r_static
r_int
id|parse_options
c_func
(paren
r_char
op_star
id|options
comma
r_int
op_star
id|pipefd
comma
id|uid_t
op_star
id|uid
comma
id|gid_t
op_star
id|gid
comma
id|pid_t
op_star
id|pgrp
comma
r_int
op_star
id|minproto
comma
r_int
op_star
id|maxproto
)paren
(brace
r_char
op_star
id|this_char
comma
op_star
id|value
suffix:semicolon
op_star
id|uid
op_assign
id|current-&gt;uid
suffix:semicolon
op_star
id|gid
op_assign
id|current-&gt;gid
suffix:semicolon
op_star
id|pgrp
op_assign
id|current-&gt;pgrp
suffix:semicolon
op_star
id|minproto
op_assign
op_star
id|maxproto
op_assign
id|AUTOFS_PROTO_VERSION
suffix:semicolon
op_star
id|pipefd
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|this_char
op_assign
id|strtok
c_func
(paren
id|options
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
id|this_char
suffix:semicolon
id|this_char
op_assign
id|strtok
c_func
(paren
l_int|NULL
comma
l_string|&quot;,&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|value
op_assign
id|strchr
c_func
(paren
id|this_char
comma
l_char|&squot;=&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
op_star
id|value
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;fd&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|pipefd
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;uid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|uid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;gid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|gid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;pgrp&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|pgrp
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;minproto&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|minproto
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;maxproto&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|maxproto
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
r_return
(paren
op_star
id|pipefd
OL
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|autofs_read_super
r_struct
id|super_block
op_star
id|autofs_read_super
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
id|inode
op_star
id|root_inode
suffix:semicolon
r_struct
id|dentry
op_star
id|root
suffix:semicolon
r_struct
id|file
op_star
id|pipe
suffix:semicolon
r_int
id|pipefd
suffix:semicolon
r_struct
id|autofs_sb_info
op_star
id|sbi
suffix:semicolon
r_int
id|minproto
comma
id|maxproto
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|lock_super
c_func
(paren
id|s
)paren
suffix:semicolon
multiline_comment|/* Super block already completed? */
r_if
c_cond
(paren
id|s-&gt;s_root
)paren
r_goto
id|out_unlock
suffix:semicolon
id|sbi
op_assign
(paren
r_struct
id|autofs_sb_info
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|autofs_sb_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi
)paren
r_goto
id|fail_unlock
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs: starting up, sbi = %p&bslash;n&quot;
comma
id|sbi
)paren
)paren
suffix:semicolon
id|s-&gt;u.generic_sbp
op_assign
id|sbi
suffix:semicolon
id|sbi-&gt;magic
op_assign
id|AUTOFS_SBI_MAGIC
suffix:semicolon
id|sbi-&gt;catatonic
op_assign
l_int|0
suffix:semicolon
id|sbi-&gt;exp_timeout
op_assign
l_int|0
suffix:semicolon
id|sbi-&gt;oz_pgrp
op_assign
id|current-&gt;pgrp
suffix:semicolon
id|autofs_initialize_hash
c_func
(paren
op_amp
id|sbi-&gt;dirhash
)paren
suffix:semicolon
id|sbi-&gt;queues
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|sbi-&gt;symlink_bitmap
comma
l_int|0
comma
r_sizeof
(paren
id|u32
)paren
op_star
id|AUTOFS_SYMLINK_BITMAP_LEN
)paren
suffix:semicolon
id|sbi-&gt;next_dir_ino
op_assign
id|AUTOFS_FIRST_DIR_INO
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
l_int|1024
suffix:semicolon
id|s-&gt;s_blocksize_bits
op_assign
l_int|10
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|AUTOFS_SUPER_MAGIC
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|autofs_sops
suffix:semicolon
id|s-&gt;s_root
op_assign
l_int|NULL
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
multiline_comment|/* shouldn&squot;t we keep it locked a while longer? */
multiline_comment|/*&n;&t; * Get the root inode and dentry, but defer checking for errors.&n;&t; */
id|root_inode
op_assign
id|iget
c_func
(paren
id|s
comma
id|AUTOFS_ROOT_INO
)paren
suffix:semicolon
id|root
op_assign
id|d_alloc_root
c_func
(paren
id|root_inode
comma
l_int|NULL
)paren
suffix:semicolon
id|pipe
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Check whether somebody else completed the super block.&n;&t; */
r_if
c_cond
(paren
id|s-&gt;s_root
)paren
r_goto
id|out_dput
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root
)paren
r_goto
id|fail_iput
suffix:semicolon
multiline_comment|/* Can this call block? */
r_if
c_cond
(paren
id|parse_options
c_func
(paren
id|data
comma
op_amp
id|pipefd
comma
op_amp
id|root_inode-&gt;i_uid
comma
op_amp
id|root_inode-&gt;i_gid
comma
op_amp
id|sbi-&gt;oz_pgrp
comma
op_amp
id|minproto
comma
op_amp
id|maxproto
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;autofs: called with bogus options&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_dput
suffix:semicolon
)brace
multiline_comment|/* Couldn&squot;t this be tested earlier? */
r_if
c_cond
(paren
id|minproto
OG
id|AUTOFS_PROTO_VERSION
op_logical_or
id|maxproto
OL
id|AUTOFS_PROTO_VERSION
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;autofs: kernel does not match daemon version&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_dput
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs: pipe fd = %d, pgrp = %u&bslash;n&quot;
comma
id|pipefd
comma
id|sbi-&gt;oz_pgrp
)paren
)paren
suffix:semicolon
id|pipe
op_assign
id|fget
c_func
(paren
id|pipefd
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check whether somebody else completed the super block.&n;&t; */
r_if
c_cond
(paren
id|s-&gt;s_root
)paren
r_goto
id|out_fput
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pipe
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;autofs: could not open pipe file descriptor&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_dput
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pipe-&gt;f_op
op_logical_or
op_logical_neg
id|pipe-&gt;f_op-&gt;write
)paren
r_goto
id|fail_fput
suffix:semicolon
id|sbi-&gt;pipe
op_assign
id|pipe
suffix:semicolon
multiline_comment|/*&n;&t; * Success! Install the root dentry now to indicate completion.&n;&t; */
id|s-&gt;s_root
op_assign
id|root
suffix:semicolon
r_return
id|s
suffix:semicolon
multiline_comment|/*&n;&t; * Success ... somebody else completed the super block for us. &n;&t; */
id|out_unlock
suffix:colon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_goto
id|out_dec
suffix:semicolon
id|out_fput
suffix:colon
r_if
c_cond
(paren
id|pipe
)paren
id|fput
c_func
(paren
id|pipe
)paren
suffix:semicolon
id|out_dput
suffix:colon
r_if
c_cond
(paren
id|root
)paren
id|dput
c_func
(paren
id|root
)paren
suffix:semicolon
r_else
id|iput
c_func
(paren
id|root_inode
)paren
suffix:semicolon
id|out_dec
suffix:colon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|s
suffix:semicolon
multiline_comment|/*&n;&t; * Failure ... clear the s_dev slot and clean up.&n;&t; */
id|fail_fput
suffix:colon
id|printk
c_func
(paren
l_string|&quot;autofs: pipe file descriptor does not contain proper ops&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * fput() can block, so we clear the super block first.&n;&t; */
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|fput
c_func
(paren
id|pipe
)paren
suffix:semicolon
multiline_comment|/* fall through */
id|fail_dput
suffix:colon
multiline_comment|/*&n;&t; * dput() can block, so we clear the super block first.&n;&t; */
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|dput
c_func
(paren
id|root
)paren
suffix:semicolon
r_goto
id|fail_free
suffix:semicolon
id|fail_iput
suffix:colon
id|printk
c_func
(paren
l_string|&quot;autofs: get root dentry failed&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * iput() can block, so we clear the super block first.&n;&t; */
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|iput
c_func
(paren
id|root_inode
)paren
suffix:semicolon
id|fail_free
suffix:colon
id|kfree
c_func
(paren
id|sbi
)paren
suffix:semicolon
r_goto
id|fail_dec
suffix:semicolon
id|fail_unlock
suffix:colon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|fail_dec
suffix:colon
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|autofs_statfs
r_static
r_int
id|autofs_statfs
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
id|bufsiz
)paren
(brace
r_struct
id|statfs
id|tmp
suffix:semicolon
id|tmp.f_type
op_assign
id|AUTOFS_SUPER_MAGIC
suffix:semicolon
id|tmp.f_bsize
op_assign
l_int|1024
suffix:semicolon
id|tmp.f_blocks
op_assign
l_int|0
suffix:semicolon
id|tmp.f_bfree
op_assign
l_int|0
suffix:semicolon
id|tmp.f_bavail
op_assign
l_int|0
suffix:semicolon
id|tmp.f_files
op_assign
l_int|0
suffix:semicolon
id|tmp.f_ffree
op_assign
l_int|0
suffix:semicolon
id|tmp.f_namelen
op_assign
id|NAME_MAX
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
id|bufsiz
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|autofs_read_inode
r_static
r_void
id|autofs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|ino_t
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
r_struct
id|autofs_sb_info
op_star
id|sbi
op_assign
(paren
r_struct
id|autofs_sb_info
op_star
)paren
id|inode-&gt;i_sb-&gt;u.generic_sbp
suffix:semicolon
id|inode-&gt;i_op
op_assign
l_int|NULL
suffix:semicolon
id|inode-&gt;i_mode
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
l_int|1024
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_eq
id|AUTOFS_ROOT_INO
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
op_or
id|S_IWUSR
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|autofs_root_inode_operations
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|inode-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Changed in read_super */
r_return
suffix:semicolon
)brace
id|inode-&gt;i_uid
op_assign
id|inode-&gt;i_sb-&gt;s_root-&gt;d_inode-&gt;i_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|inode-&gt;i_sb-&gt;s_root-&gt;d_inode-&gt;i_gid
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_ge
id|AUTOFS_FIRST_SYMLINK
op_logical_and
id|ino
OL
id|AUTOFS_FIRST_DIR_INO
)paren
(brace
multiline_comment|/* Symlink inode - should be in symlink list */
r_struct
id|autofs_symlink
op_star
id|sl
suffix:semicolon
id|n
op_assign
id|ino
op_minus
id|AUTOFS_FIRST_SYMLINK
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
id|AUTOFS_MAX_SYMLINKS
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|n
comma
id|sbi-&gt;symlink_bitmap
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;autofs: Looking for bad symlink inode 0x%08x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|ino
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|inode-&gt;i_op
op_assign
op_amp
id|autofs_symlink_inode_operations
suffix:semicolon
id|sl
op_assign
op_amp
id|sbi-&gt;symlink
(braket
id|n
)braket
suffix:semicolon
id|inode-&gt;u.generic_ip
op_assign
id|sl
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFLNK
op_or
id|S_IRWXUGO
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|sl-&gt;mtime
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|sl-&gt;len
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* All non-root directory inodes look the same */
id|inode-&gt;i_op
op_assign
op_amp
id|autofs_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
suffix:semicolon
)brace
)brace
DECL|function|autofs_write_inode
r_static
r_void
id|autofs_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
)brace
eof
