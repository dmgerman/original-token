multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/fs/autofs/inode.c&n; *&n; *  Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &quot;autofs_i.h&quot;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
DECL|function|ino_lnkfree
r_static
r_void
id|ino_lnkfree
c_func
(paren
r_struct
id|autofs_info
op_star
id|ino
)paren
(brace
r_if
c_cond
(paren
id|ino-&gt;u.symlink
)paren
(brace
id|kfree
c_func
(paren
id|ino-&gt;u.symlink
)paren
suffix:semicolon
id|ino-&gt;u.symlink
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|autofs4_init_ino
r_struct
id|autofs_info
op_star
id|autofs4_init_ino
c_func
(paren
r_struct
id|autofs_info
op_star
id|ino
comma
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
id|mode_t
id|mode
)paren
(brace
r_int
id|reinit
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_eq
l_int|NULL
)paren
(brace
id|reinit
op_assign
l_int|0
suffix:semicolon
id|ino
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ino
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ino
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|ino-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|ino-&gt;ino
op_assign
id|sbi-&gt;next_ino
op_increment
suffix:semicolon
id|ino-&gt;mode
op_assign
id|mode
suffix:semicolon
id|ino-&gt;inode
op_assign
l_int|NULL
suffix:semicolon
id|ino-&gt;dentry
op_assign
l_int|NULL
suffix:semicolon
id|ino-&gt;size
op_assign
l_int|0
suffix:semicolon
id|ino-&gt;last_used
op_assign
id|jiffies
suffix:semicolon
id|ino-&gt;sbi
op_assign
id|sbi
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|ino-&gt;ino_hash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reinit
op_logical_and
id|ino-&gt;free
)paren
(paren
id|ino-&gt;free
)paren
(paren
id|ino
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ino-&gt;u
comma
l_int|0
comma
r_sizeof
(paren
id|ino-&gt;u
)paren
)paren
suffix:semicolon
id|ino-&gt;free
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|mode
)paren
)paren
id|ino-&gt;free
op_assign
id|ino_lnkfree
suffix:semicolon
r_return
id|ino
suffix:semicolon
)brace
DECL|function|autofs4_free_ino
r_void
id|autofs4_free_ino
c_func
(paren
r_struct
id|autofs_info
op_star
id|ino
)paren
(brace
id|autofs4_ihash_delete
c_func
(paren
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ino-&gt;dentry
)paren
(brace
id|ino-&gt;dentry-&gt;d_fsdata
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ino-&gt;dentry-&gt;d_inode
)paren
id|dput
c_func
(paren
id|ino-&gt;dentry
)paren
suffix:semicolon
id|ino-&gt;dentry
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ino-&gt;free
)paren
(paren
id|ino-&gt;free
)paren
(paren
id|ino
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ino
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Dummy functions - do we ever actually want to do&n; * something here?&n; */
DECL|function|autofs4_put_inode
r_static
r_void
id|autofs4_put_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
)brace
DECL|function|autofs4_clear_inode
r_static
r_void
id|autofs4_clear_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
)brace
DECL|function|autofs4_put_super
r_static
r_void
id|autofs4_put_super
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
id|autofs4_sbi
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb-&gt;u.generic_sbp
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi-&gt;catatonic
)paren
id|autofs4_catatonic_mode
c_func
(paren
id|sbi
)paren
suffix:semicolon
multiline_comment|/* Free wait queues, close pipe */
id|kfree
c_func
(paren
id|sbi
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
DECL|function|autofs4_umount_begin
r_static
r_void
id|autofs4_umount_begin
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
id|autofs4_sbi
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi-&gt;catatonic
)paren
id|autofs4_catatonic_mode
c_func
(paren
id|sbi
)paren
suffix:semicolon
)brace
r_static
r_int
id|autofs4_statfs
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
id|autofs4_read_inode
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
id|autofs4_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
DECL|variable|autofs4_sops
r_static
r_struct
id|super_operations
id|autofs4_sops
op_assign
(brace
id|read_inode
suffix:colon
id|autofs4_read_inode
comma
id|write_inode
suffix:colon
id|autofs4_write_inode
comma
id|put_inode
suffix:colon
id|autofs4_put_inode
comma
id|clear_inode
suffix:colon
id|autofs4_clear_inode
comma
id|put_super
suffix:colon
id|autofs4_put_super
comma
id|statfs
suffix:colon
id|autofs4_statfs
comma
id|umount_begin
suffix:colon
id|autofs4_umount_begin
comma
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
id|AUTOFS_MAX_PROTO_VERSION
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
DECL|function|autofs4_mkroot
r_static
r_struct
id|autofs_info
op_star
id|autofs4_mkroot
c_func
(paren
r_struct
id|autofs_sb_info
op_star
id|sbi
)paren
(brace
r_struct
id|autofs_info
op_star
id|ino
suffix:semicolon
id|ino
op_assign
id|autofs4_init_ino
c_func
(paren
l_int|NULL
comma
id|sbi
comma
id|S_IFDIR
op_or
l_int|0755
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
)paren
r_return
l_int|NULL
suffix:semicolon
id|ino-&gt;ino
op_assign
id|AUTOFS_ROOT_INO
suffix:semicolon
r_return
id|ino
suffix:semicolon
)brace
DECL|function|autofs4_read_super
r_struct
id|super_block
op_star
id|autofs4_read_super
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
op_star
id|sbi
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
id|memset
c_func
(paren
id|sbi
comma
l_int|0
comma
r_sizeof
(paren
op_star
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
id|sbi-&gt;sb
op_assign
id|s
suffix:semicolon
id|sbi-&gt;version
op_assign
l_int|0
suffix:semicolon
id|autofs4_init_ihash
c_func
(paren
op_amp
id|sbi-&gt;ihash
)paren
suffix:semicolon
id|sbi-&gt;queues
op_assign
l_int|NULL
suffix:semicolon
id|sbi-&gt;next_ino
op_assign
id|AUTOFS_FIRST_INO
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
id|autofs4_sops
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
id|autofs4_ihash_insert
c_func
(paren
op_amp
id|sbi-&gt;ihash
comma
id|autofs4_mkroot
c_func
(paren
id|sbi
)paren
)paren
suffix:semicolon
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
id|maxproto
template_param
id|AUTOFS_MAX_PROTO_VERSION
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;autofs: kernel does not match daemon version &quot;
l_string|&quot;daemon (%d, %d) kernel (%d, %d)&bslash;n&quot;
comma
id|minproto
comma
id|maxproto
comma
id|AUTOFS_MIN_PROTO_VERSION
comma
id|AUTOFS_MAX_PROTO_VERSION
)paren
suffix:semicolon
r_goto
id|fail_dput
suffix:semicolon
)brace
id|sbi-&gt;version
op_assign
id|maxproto
OG
id|AUTOFS_MAX_PROTO_VERSION
ques
c_cond
id|AUTOFS_MAX_PROTO_VERSION
suffix:colon
id|maxproto
suffix:semicolon
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
DECL|function|autofs4_statfs
r_static
r_int
id|autofs4_statfs
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
DECL|function|autofs4_read_inode
r_static
r_void
id|autofs4_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|autofs_sb_info
op_star
id|sbi
op_assign
id|autofs4_sbi
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|autofs_info
op_star
id|inf
suffix:semicolon
id|inf
op_assign
id|autofs4_ihash_find
c_func
(paren
op_amp
id|sbi-&gt;ihash
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inf
op_eq
l_int|NULL
op_logical_or
id|inf-&gt;inode
op_ne
l_int|NULL
)paren
r_return
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|inf-&gt;mode
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|inf-&gt;size
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;s_root
)paren
(brace
id|inode-&gt;i_uid
op_assign
id|inode-&gt;i_sb-&gt;s_root-&gt;d_inode-&gt;i_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|inode-&gt;i_sb-&gt;s_root-&gt;d_inode-&gt;i_gid
suffix:semicolon
)brace
r_else
(brace
id|inode-&gt;i_uid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
)brace
id|inf-&gt;inode
op_assign
id|inode
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inf-&gt;mode
)paren
)paren
(brace
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|AUTOFS_ROOT_INO
)paren
id|inode-&gt;i_op
op_assign
op_amp
id|autofs4_root_inode_operations
suffix:semicolon
r_else
id|inode-&gt;i_op
op_assign
op_amp
id|autofs4_dir_inode_operations
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inf-&gt;mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|autofs4_symlink_inode_operations
suffix:semicolon
)brace
)brace
DECL|function|autofs4_write_inode
r_static
r_void
id|autofs4_write_inode
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
