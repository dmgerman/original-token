multiline_comment|/*&n; *  linux/fs/proc/inode.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/limits.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|proc_put_inode
r_static
r_void
id|proc_put_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
macro_line|#ifdef CONFIG_SUN_OPENPROMFS_MODULE
r_if
c_cond
(paren
(paren
id|inode-&gt;i_ino
op_ge
id|PROC_OPENPROM_FIRST
)paren
op_logical_and
(paren
id|inode-&gt;i_ino
OL
id|PROC_OPENPROM_FIRST
op_plus
id|PROC_NOPENPROM
)paren
op_logical_and
id|proc_openprom_use
)paren
(paren
op_star
id|proc_openprom_use
)paren
(paren
id|inode
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif&t;
r_if
c_cond
(paren
id|inode-&gt;i_nlink
)paren
r_return
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|proc_put_super
r_static
r_void
id|proc_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
DECL|variable|proc_sops
r_static
r_struct
id|super_operations
id|proc_sops
op_assign
(brace
id|proc_read_inode
comma
l_int|NULL
comma
id|proc_write_inode
comma
id|proc_put_inode
comma
id|proc_put_super
comma
l_int|NULL
comma
id|proc_statfs
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
id|uid_t
op_star
id|uid
comma
id|gid_t
op_star
id|gid
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
l_int|0
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
l_int|0
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
l_int|0
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
l_int|0
suffix:semicolon
)brace
r_else
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|proc_get_inode
r_struct
id|inode
op_star
id|proc_get_inode
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_int
id|ino
comma
r_struct
id|proc_dir_entry
op_star
id|de
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|iget
c_func
(paren
id|s
comma
id|ino
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SUN_OPENPROMFS_MODULE
r_if
c_cond
(paren
(paren
id|inode-&gt;i_ino
op_ge
id|PROC_OPENPROM_FIRST
)paren
op_logical_and
(paren
id|inode-&gt;i_ino
OL
id|PROC_OPENPROM_FIRST
op_plus
id|PROC_NOPENPROM
)paren
op_logical_and
id|proc_openprom_use
)paren
(paren
op_star
id|proc_openprom_use
)paren
(paren
id|inode
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif&t;
r_if
c_cond
(paren
id|inode
op_logical_and
id|inode-&gt;i_sb
op_eq
id|s
)paren
(brace
id|inode-&gt;u.generic_ip
op_assign
(paren
r_void
op_star
)paren
id|de
suffix:semicolon
r_if
c_cond
(paren
id|de
)paren
(brace
r_if
c_cond
(paren
id|de-&gt;mode
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|de-&gt;mode
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|de-&gt;uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|de-&gt;gid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;size
)paren
id|inode-&gt;i_size
op_assign
id|de-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;ops
)paren
id|inode-&gt;i_op
op_assign
id|de-&gt;ops
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;nlink
)paren
id|inode-&gt;i_nlink
op_assign
id|de-&gt;nlink
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;fill_inode
)paren
id|de
op_member_access_from_pointer
id|fill_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
r_return
id|inode
suffix:semicolon
)brace
DECL|function|proc_read_super
r_struct
id|super_block
op_star
id|proc_read_super
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
id|proc_root_init
c_func
(paren
)paren
suffix:semicolon
id|lock_super
c_func
(paren
id|s
)paren
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
id|PROC_SUPER_MAGIC
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|proc_sops
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|s-&gt;s_mounted
op_assign
id|proc_get_inode
c_func
(paren
id|s
comma
id|PROC_ROOT_INO
comma
op_amp
id|proc_root
)paren
)paren
)paren
(brace
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;get root inode failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|parse_options
c_func
(paren
id|data
comma
op_amp
id|s-&gt;s_mounted-&gt;i_uid
comma
op_amp
id|s-&gt;s_mounted-&gt;i_gid
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|function|proc_statfs
r_void
id|proc_statfs
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
id|PROC_SUPER_MAGIC
suffix:semicolon
id|tmp.f_bsize
op_assign
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_int
)paren
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
suffix:semicolon
)brace
DECL|function|proc_read_inode
r_void
id|proc_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
r_int
id|ino
comma
id|pid
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|i
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
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_ge
id|PROC_OPENPROM_FIRST
op_logical_and
id|ino
OL
id|PROC_OPENPROM_FIRST
op_plus
id|PROC_NOPENPROM
)paren
r_return
suffix:semicolon
id|inode-&gt;i_op
op_assign
l_int|NULL
suffix:semicolon
id|inode-&gt;i_mode
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_uid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|pid
op_assign
id|ino
op_rshift
l_int|16
suffix:semicolon
id|p
op_assign
id|task
(braket
l_int|0
)braket
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
id|NR_TASKS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|p
op_assign
id|task
(braket
id|i
)braket
)paren
op_logical_and
(paren
id|p-&gt;pid
op_eq
id|pid
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
id|i
op_ge
id|NR_TASKS
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_eq
id|PROC_ROOT_INO
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|NR_TASKS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
)paren
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
r_switch
c_cond
(paren
id|ino
)paren
(brace
r_case
id|PROC_KMSG
suffix:colon
id|inode-&gt;i_mode
op_assign
id|S_IFREG
op_or
id|S_IRUSR
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_kmsg_inode_operations
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROC_NET
suffix:colon
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROC_SCSI
suffix:colon
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_scsi_inode_operations
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROC_KCORE
suffix:colon
id|inode-&gt;i_mode
op_assign
id|S_IFREG
op_or
id|S_IRUSR
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_kcore_inode_operations
suffix:semicolon
id|inode-&gt;i_size
op_assign
(paren
id|MAP_NR
c_func
(paren
id|high_memory
)paren
op_lshift
id|PAGE_SHIFT
)paren
op_plus
id|PAGE_SIZE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROC_PROFILE
suffix:colon
id|inode-&gt;i_mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_profile_inode_operations
suffix:semicolon
id|inode-&gt;i_size
op_assign
(paren
l_int|1
op_plus
id|prof_len
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|inode-&gt;i_mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_array_inode_operations
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|ino
op_and_assign
l_int|0x0000ffff
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_eq
id|PROC_PID_INO
op_logical_or
id|p-&gt;dumpable
)paren
(brace
id|inode-&gt;i_uid
op_assign
id|p-&gt;euid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|p-&gt;egid
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ino
)paren
(brace
r_case
id|PROC_PID_INO
suffix:colon
id|inode-&gt;i_nlink
op_assign
l_int|4
suffix:semicolon
r_return
suffix:semicolon
r_case
id|PROC_PID_MEM
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_mem_inode_operations
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFREG
op_or
id|S_IRUSR
op_or
id|S_IWUSR
suffix:semicolon
r_return
suffix:semicolon
r_case
id|PROC_PID_CWD
suffix:colon
r_case
id|PROC_PID_ROOT
suffix:colon
r_case
id|PROC_PID_EXE
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_link_inode_operations
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|64
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFLNK
op_or
id|S_IRWXU
suffix:semicolon
r_return
suffix:semicolon
r_case
id|PROC_PID_FD
suffix:colon
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
id|S_IRUSR
op_or
id|S_IXUSR
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_fd_inode_operations
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
r_return
suffix:semicolon
r_case
id|PROC_PID_ENVIRON
suffix:colon
id|inode-&gt;i_mode
op_assign
id|S_IFREG
op_or
id|S_IRUSR
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_array_inode_operations
suffix:semicolon
r_return
suffix:semicolon
r_case
id|PROC_PID_CMDLINE
suffix:colon
r_case
id|PROC_PID_STATUS
suffix:colon
r_case
id|PROC_PID_STAT
suffix:colon
r_case
id|PROC_PID_STATM
suffix:colon
id|inode-&gt;i_mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_array_inode_operations
suffix:semicolon
r_return
suffix:semicolon
r_case
id|PROC_PID_MAPS
suffix:colon
id|inode-&gt;i_mode
op_assign
id|S_IFIFO
op_or
id|S_IRUGO
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_arraylong_inode_operations
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ino
op_rshift
l_int|8
)paren
(brace
r_case
id|PROC_PID_FD_DIR
suffix:colon
id|ino
op_and_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_ge
id|NR_OPEN
op_logical_or
op_logical_neg
id|p-&gt;files-&gt;fd
(braket
id|ino
)braket
)paren
r_return
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_link_inode_operations
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|64
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFLNK
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;files-&gt;fd
(braket
id|ino
)braket
op_member_access_from_pointer
id|f_mode
op_amp
l_int|1
)paren
id|inode-&gt;i_mode
op_or_assign
id|S_IRUSR
op_or
id|S_IXUSR
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;files-&gt;fd
(braket
id|ino
)braket
op_member_access_from_pointer
id|f_mode
op_amp
l_int|2
)paren
id|inode-&gt;i_mode
op_or_assign
id|S_IWUSR
op_or
id|S_IXUSR
suffix:semicolon
r_return
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|proc_write_inode
r_void
id|proc_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_dirt
op_assign
l_int|0
suffix:semicolon
)brace
eof
