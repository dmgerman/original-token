multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/fs/devpts/inode.c&n; *&n; *  Copyright 1998 H. Peter Anvin -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;devpts_i.h&quot;
DECL|variable|devpts_mnt
r_static
r_struct
id|vfsmount
op_star
id|devpts_mnt
suffix:semicolon
DECL|function|devpts_put_super
r_static
r_void
id|devpts_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|devpts_sb_info
op_star
id|sbi
op_assign
id|SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|i
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
id|sbi-&gt;max_ptys
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|inode
op_assign
id|sbi-&gt;inodes
(braket
id|i
)braket
)paren
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
op_ne
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;devpts_put_super: badness: entry %d count %d&bslash;n&quot;
comma
id|i
comma
id|atomic_read
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|sbi-&gt;inodes
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sbi
)paren
suffix:semicolon
)brace
r_static
r_int
id|devpts_statfs
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
)paren
suffix:semicolon
r_static
r_int
id|devpts_remount
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
op_star
id|flags
comma
r_char
op_star
id|data
)paren
suffix:semicolon
DECL|variable|devpts_sops
r_static
r_struct
id|super_operations
id|devpts_sops
op_assign
(brace
id|put_super
suffix:colon
id|devpts_put_super
comma
id|statfs
suffix:colon
id|devpts_statfs
comma
id|remount_fs
suffix:colon
id|devpts_remount
comma
)brace
suffix:semicolon
DECL|function|devpts_parse_options
r_static
r_int
id|devpts_parse_options
c_func
(paren
r_char
op_star
id|options
comma
r_struct
id|devpts_sb_info
op_star
id|sbi
)paren
(brace
r_int
id|setuid
op_assign
l_int|0
suffix:semicolon
r_int
id|setgid
op_assign
l_int|0
suffix:semicolon
id|uid_t
id|uid
op_assign
l_int|0
suffix:semicolon
id|gid_t
id|gid
op_assign
l_int|0
suffix:semicolon
id|umode_t
id|mode
op_assign
l_int|0600
suffix:semicolon
r_char
op_star
id|this_char
comma
op_star
id|value
suffix:semicolon
id|this_char
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|options
)paren
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
r_for
c_loop
(paren
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
id|setuid
op_assign
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
id|setgid
op_assign
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
l_string|&quot;mode&quot;
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
id|mode
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|8
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
r_return
l_int|1
suffix:semicolon
)brace
id|sbi-&gt;setuid
op_assign
id|setuid
suffix:semicolon
id|sbi-&gt;setgid
op_assign
id|setgid
suffix:semicolon
id|sbi-&gt;uid
op_assign
id|uid
suffix:semicolon
id|sbi-&gt;gid
op_assign
id|gid
suffix:semicolon
id|sbi-&gt;mode
op_assign
id|mode
op_amp
op_complement
id|S_IFMT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|devpts_remount
r_static
r_int
id|devpts_remount
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
op_star
id|flags
comma
r_char
op_star
id|data
)paren
(brace
r_struct
id|devpts_sb_info
op_star
id|sbi
op_assign
id|sb-&gt;u.generic_sbp
suffix:semicolon
r_int
id|res
op_assign
id|devpts_parse_options
c_func
(paren
id|data
comma
id|sbi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;devpts: called with bogus options&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|devpts_read_super
r_struct
id|super_block
op_star
id|devpts_read_super
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
id|inode
suffix:semicolon
r_struct
id|devpts_sb_info
op_star
id|sbi
suffix:semicolon
id|sbi
op_assign
(paren
r_struct
id|devpts_sb_info
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|devpts_sb_info
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
id|fail
suffix:semicolon
id|sbi-&gt;magic
op_assign
id|DEVPTS_SBI_MAGIC
suffix:semicolon
id|sbi-&gt;max_ptys
op_assign
id|unix98_max_ptys
suffix:semicolon
id|sbi-&gt;inodes
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|inode
op_star
)paren
op_star
id|sbi-&gt;max_ptys
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi-&gt;inodes
)paren
r_goto
id|fail_free
suffix:semicolon
id|memset
c_func
(paren
id|sbi-&gt;inodes
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|inode
op_star
)paren
op_star
id|sbi-&gt;max_ptys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devpts_parse_options
c_func
(paren
id|data
comma
id|sbi
)paren
op_logical_and
op_logical_neg
id|silent
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;devpts: called with bogus options&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_free
suffix:semicolon
)brace
id|inode
op_assign
id|new_inode
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|fail_free
suffix:semicolon
id|inode-&gt;i_ino
op_assign
l_int|1
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
id|inode-&gt;i_uid
op_assign
id|inode-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
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
id|devpts_root_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|devpts_root_operations
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
id|s-&gt;u.generic_sbp
op_assign
(paren
r_void
op_star
)paren
id|sbi
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
id|DEVPTS_SUPER_MAGIC
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|devpts_sops
suffix:semicolon
id|s-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_root
)paren
r_return
id|s
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;devpts: get root dentry failed&bslash;n&quot;
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
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
id|fail
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|devpts_statfs
r_static
r_int
id|devpts_statfs
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
)paren
(brace
id|buf-&gt;f_type
op_assign
id|DEVPTS_SUPER_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
l_int|1024
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|NAME_MAX
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|DECLARE_FSTYPE
c_func
(paren
id|devpts_fs_type
comma
l_string|&quot;devpts&quot;
comma
id|devpts_read_super
comma
id|FS_SINGLE
)paren
suffix:semicolon
DECL|function|devpts_pty_new
r_void
id|devpts_pty_new
c_func
(paren
r_int
id|number
comma
id|kdev_t
id|device
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|devpts_mnt-&gt;mnt_sb
suffix:semicolon
r_struct
id|devpts_sb_info
op_star
id|sbi
op_assign
id|SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;inodes
(braket
id|number
)braket
)paren
r_return
suffix:semicolon
multiline_comment|/* Already registered, this does happen */
id|inode
op_assign
id|new_inode
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|number
op_plus
l_int|2
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
l_int|1024
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|sbi-&gt;setuid
ques
c_cond
id|sbi-&gt;uid
suffix:colon
id|current-&gt;fsuid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|sbi-&gt;setgid
ques
c_cond
id|sbi-&gt;gid
suffix:colon
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|init_special_inode
c_func
(paren
id|inode
comma
id|S_IFCHR
op_or
id|sbi-&gt;mode
comma
id|kdev_t_to_nr
c_func
(paren
id|device
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;inodes
(braket
id|number
)braket
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sbi-&gt;inodes
(braket
id|number
)braket
op_assign
id|inode
suffix:semicolon
)brace
DECL|function|devpts_pty_kill
r_void
id|devpts_pty_kill
c_func
(paren
r_int
id|number
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|devpts_mnt-&gt;mnt_sb
suffix:semicolon
r_struct
id|devpts_sb_info
op_star
id|sbi
op_assign
id|SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|sbi-&gt;inodes
(braket
id|number
)braket
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
id|sbi-&gt;inodes
(braket
id|number
)braket
op_assign
l_int|NULL
suffix:semicolon
id|inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
DECL|function|init_devpts_fs
r_int
id|__init
id|init_devpts_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|devpts_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|devpts_mnt
op_assign
id|kern_mount
c_func
(paren
op_amp
id|devpts_fs_type
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|devpts_mnt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|devpts_mnt
)paren
)paren
id|err
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
id|init_devpts_fs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|devpts_upcall_new
op_assign
id|devpts_pty_new
suffix:semicolon
id|devpts_upcall_kill
op_assign
id|devpts_pty_kill
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|devpts_upcall_new
op_assign
l_int|NULL
suffix:semicolon
id|devpts_upcall_kill
op_assign
l_int|NULL
suffix:semicolon
id|unregister_filesystem
c_func
(paren
op_amp
id|devpts_fs_type
)paren
suffix:semicolon
id|kern_umount
c_func
(paren
id|devpts_mnt
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
