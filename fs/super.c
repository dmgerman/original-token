multiline_comment|/*&n; *  linux/fs/super.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; * super.c contains code to handle the super-block tables.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/ext_fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
r_void
id|wait_for_keypress
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|fcntl_init_locks
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* set_bit uses setb, as gas doesn&squot;t recognize setc */
DECL|macro|set_bit
mdefine_line|#define set_bit(bitnr,addr) ({ &bslash;&n;register int __res __asm__(&quot;ax&quot;); &bslash;&n;__asm__(&quot;bt %2,%3;setb %%al&quot;:&quot;=a&quot; (__res):&quot;a&quot; (0),&quot;r&quot; (bitnr),&quot;m&quot; (*(addr))); &bslash;&n;__res; })
DECL|variable|super_block
r_struct
id|super_block
id|super_block
(braket
id|NR_SUPER
)braket
suffix:semicolon
multiline_comment|/* this is initialized in init/main.c */
DECL|variable|ROOT_DEV
id|dev_t
id|ROOT_DEV
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Move into include file later */
DECL|variable|file_systems
r_static
r_struct
id|file_system_type
id|file_systems
(braket
)braket
op_assign
(brace
(brace
id|minix_read_super
comma
l_string|&quot;minix&quot;
)brace
comma
(brace
id|ext_read_super
comma
l_string|&quot;ext&quot;
)brace
comma
(brace
id|msdos_read_super
comma
l_string|&quot;msdos&quot;
)brace
comma
(brace
id|proc_read_super
comma
l_string|&quot;proc&quot;
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
multiline_comment|/* end of include file */
DECL|function|get_fs_type
r_struct
id|file_system_type
op_star
id|get_fs_type
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_int
id|a
suffix:semicolon
r_for
c_loop
(paren
id|a
op_assign
l_int|0
suffix:semicolon
id|file_systems
(braket
id|a
)braket
dot
id|read_super
suffix:semicolon
id|a
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
id|file_systems
(braket
id|a
)braket
dot
id|name
)paren
)paren
r_return
op_amp
id|file_systems
(braket
id|a
)braket
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|__wait_on_super
r_void
id|__wait_on_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|add_wait_queue
c_func
(paren
op_amp
id|sb-&gt;s_wait
comma
op_amp
id|current-&gt;wait
)paren
suffix:semicolon
id|repeat
suffix:colon
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_lock
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|sb-&gt;s_wait
comma
op_amp
id|current-&gt;wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
)brace
DECL|function|sync_supers
r_void
id|sync_supers
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_for
c_loop
(paren
id|sb
op_assign
id|super_block
op_plus
l_int|0
suffix:semicolon
id|sb
OL
id|super_block
op_plus
id|NR_SUPER
suffix:semicolon
id|sb
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_dev
)paren
r_continue
suffix:semicolon
id|wait_on_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_dev
op_logical_or
op_logical_neg
id|sb-&gt;s_dirt
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_logical_and
(paren
id|dev
op_ne
id|sb-&gt;s_dev
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_op
op_logical_and
id|sb-&gt;s_op-&gt;write_super
)paren
id|sb-&gt;s_op
op_member_access_from_pointer
id|write_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
)brace
DECL|function|get_super
r_static
r_struct
id|super_block
op_star
id|get_super
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_struct
id|super_block
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|NULL
suffix:semicolon
id|s
op_assign
l_int|0
op_plus
id|super_block
suffix:semicolon
r_while
c_loop
(paren
id|s
OL
id|NR_SUPER
op_plus
id|super_block
)paren
r_if
c_cond
(paren
id|s-&gt;s_dev
op_eq
id|dev
)paren
(brace
id|wait_on_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_dev
op_eq
id|dev
)paren
r_return
id|s
suffix:semicolon
id|s
op_assign
l_int|0
op_plus
id|super_block
suffix:semicolon
)brace
r_else
id|s
op_increment
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|put_super
r_void
id|put_super
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
id|ROOT_DEV
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;root diskette changed: prepare for armageddon&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb
op_assign
id|get_super
c_func
(paren
id|dev
)paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_covered
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Mounted disk changed - tssk, tssk&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sb-&gt;s_op
op_logical_and
id|sb-&gt;s_op-&gt;put_super
)paren
id|sb-&gt;s_op
op_member_access_from_pointer
id|put_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
DECL|function|read_super
r_static
r_struct
id|super_block
op_star
id|read_super
c_func
(paren
id|dev_t
id|dev
comma
r_char
op_star
id|name
comma
r_int
id|flags
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|super_block
op_star
id|s
suffix:semicolon
r_struct
id|file_system_type
op_star
id|type
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|NULL
suffix:semicolon
id|check_disk_change
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
op_assign
id|get_super
c_func
(paren
id|dev
)paren
)paren
r_return
id|s
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|type
op_assign
id|get_fs_type
c_func
(paren
id|name
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;get fs type failed %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|s
op_assign
l_int|0
op_plus
id|super_block
suffix:semicolon
suffix:semicolon
id|s
op_increment
)paren
(brace
r_if
c_cond
(paren
id|s
op_ge
id|NR_SUPER
op_plus
id|super_block
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;s_dev
)paren
r_break
suffix:semicolon
)brace
id|s-&gt;s_dev
op_assign
id|dev
suffix:semicolon
id|s-&gt;s_flags
op_assign
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|type
op_member_access_from_pointer
id|read_super
c_func
(paren
id|s
comma
id|data
)paren
)paren
(brace
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|s-&gt;s_dev
op_assign
id|dev
suffix:semicolon
id|s-&gt;s_covered
op_assign
l_int|NULL
suffix:semicolon
id|s-&gt;s_rd_only
op_assign
l_int|0
suffix:semicolon
id|s-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|function|do_umount
r_static
r_int
id|do_umount
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
id|ROOT_DEV
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb
op_assign
id|get_super
c_func
(paren
id|dev
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|sb-&gt;s_covered
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_covered-&gt;i_mount
)paren
id|printk
c_func
(paren
l_string|&quot;Mounted inode has i_mount=0&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fs_may_umount
c_func
(paren
id|dev
comma
id|sb-&gt;s_mounted
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|sb-&gt;s_covered-&gt;i_mount
op_assign
l_int|0
suffix:semicolon
id|iput
c_func
(paren
id|sb-&gt;s_covered
)paren
suffix:semicolon
id|sb-&gt;s_covered
op_assign
l_int|NULL
suffix:semicolon
id|iput
c_func
(paren
id|sb-&gt;s_mounted
)paren
suffix:semicolon
id|sb-&gt;s_mounted
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_op
op_logical_and
id|sb-&gt;s_op-&gt;write_super
op_logical_and
id|sb-&gt;s_dirt
)paren
id|sb-&gt;s_op-&gt;write_super
(paren
id|sb
)paren
suffix:semicolon
id|put_super
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_umount
r_int
id|sys_umount
c_func
(paren
r_char
op_star
id|dev_name
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|dev
comma
id|retval
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|retval
op_assign
id|namei
c_func
(paren
id|dev_name
comma
op_amp
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|dev
op_assign
id|inode-&gt;i_rdev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
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
id|ENOTBLK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_NODEV
c_func
(paren
id|inode
)paren
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
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|dev
)paren
op_ge
id|MAX_BLKDEV
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
id|ENODEV
suffix:semicolon
)brace
id|retval
op_assign
id|do_umount
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|blkdev_fops
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
op_logical_and
id|blkdev_fops
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
op_member_access_from_pointer
id|release
)paren
id|blkdev_fops
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
op_member_access_from_pointer
id|release
c_func
(paren
id|inode
comma
l_int|NULL
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|sync_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * do_mount() does the actual mounting after sys_mount has done the ugly&n; * parameter parsing. When enough time has gone by, and everything uses the&n; * new mount() parameters, sys_mount() can then be cleaned up.&n; *&n; * We cannot mount a filesystem if it has active, used, or dirty inodes.&n; * We also have to flush all inode-data for this device, as the new mount&n; * might need new info.&n; */
DECL|function|do_mount
r_static
r_int
id|do_mount
c_func
(paren
id|dev_t
id|dev
comma
r_const
r_char
op_star
id|dir
comma
r_char
op_star
id|type
comma
r_int
id|flags
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|inode
op_star
id|dir_i
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|namei
c_func
(paren
id|dir
comma
op_amp
id|dir_i
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
id|dir_i-&gt;i_count
op_ne
l_int|1
op_logical_or
id|dir_i-&gt;i_mount
)paren
(brace
id|iput
c_func
(paren
id|dir_i
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|dir_i-&gt;i_mode
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir_i
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|fs_may_mount
c_func
(paren
id|dev
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir_i
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|sb
op_assign
id|read_super
c_func
(paren
id|dev
comma
id|type
comma
id|flags
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
op_logical_or
id|sb-&gt;s_covered
)paren
(brace
id|iput
c_func
(paren
id|dir_i
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|sb-&gt;s_flags
op_assign
id|flags
suffix:semicolon
id|sb-&gt;s_covered
op_assign
id|dir_i
suffix:semicolon
id|dir_i-&gt;i_mount
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* we don&squot;t iput(dir_i) - see umount */
)brace
multiline_comment|/*&n; * Flags is a 16-bit value that allows up to 16 non-fs dependent flags to&n; * be given to the mount() call (ie: read-only, no-dev, no-suid etc).&n; *&n; * data is a (void *) that can point to any structure up to 4095 bytes, which&n; * can contain arbitrary fs-dependent information (or be NULL).&n; *&n; * NOTE! As old versions of mount() didn&squot;t use this setup, the flags has to have&n; * a special 16-bit magic number in the hight word: 0xC0ED. If this magic word&n; * isn&squot;t present, the flags and data info isn&squot;t used, as the syscall assumes we&n; * are talking to an older version that didn&squot;t understand them.&n; */
DECL|function|sys_mount
r_int
id|sys_mount
c_func
(paren
r_char
op_star
id|dev_name
comma
r_char
op_star
id|dir_name
comma
r_char
op_star
id|type
comma
r_int
r_int
id|new_flags
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
r_int
id|dev
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_char
id|tmp
(braket
l_int|100
)braket
comma
op_star
id|t
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|page
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_assign
id|namei
c_func
(paren
id|dev_name
comma
op_amp
id|inode
)paren
)paren
r_return
id|retval
suffix:semicolon
id|dev
op_assign
id|inode-&gt;i_rdev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
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
id|ENOTBLK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_NODEV
c_func
(paren
id|inode
)paren
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
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|dev
)paren
op_ge
id|MAX_BLKDEV
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
id|ENODEV
suffix:semicolon
)brace
id|fops
op_assign
id|blkdev_fops
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|fops
op_logical_and
id|fops-&gt;open
)paren
(brace
r_if
c_cond
(paren
id|retval
op_assign
id|fops
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
l_int|NULL
)paren
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|new_flags
op_amp
l_int|0xffff0000
)paren
op_eq
l_int|0xC0ED0000
)paren
(brace
id|flags
op_assign
id|new_flags
op_amp
l_int|0xffff
suffix:semicolon
r_if
c_cond
(paren
id|data
op_logical_and
(paren
r_int
r_int
)paren
id|data
OL
id|TASK_SIZE
)paren
id|page
op_assign
id|get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|page
)paren
(brace
id|i
op_assign
id|TASK_SIZE
op_minus
(paren
r_int
r_int
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|i
template_param
l_int|4095
)paren
id|i
op_assign
l_int|4095
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
(paren
r_void
op_star
)paren
id|page
comma
id|data
comma
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|100
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmp
(braket
id|i
)braket
op_assign
id|get_fs_byte
c_func
(paren
id|type
op_increment
)paren
)paren
)paren
r_break
suffix:semicolon
id|t
op_assign
id|tmp
suffix:semicolon
)brace
r_else
id|t
op_assign
l_string|&quot;minix&quot;
suffix:semicolon
id|retval
op_assign
id|do_mount
c_func
(paren
id|dev
comma
id|dir_name
comma
id|t
comma
id|flags
comma
(paren
r_void
op_star
)paren
id|page
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_logical_and
id|fops
op_logical_and
id|fops-&gt;release
)paren
id|fops
op_member_access_from_pointer
id|release
c_func
(paren
id|inode
comma
l_int|NULL
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|mount_root
r_void
id|mount_root
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|file_system_type
op_star
id|fs_type
op_assign
id|file_systems
suffix:semicolon
r_struct
id|super_block
op_star
id|p
suffix:semicolon
r_struct
id|inode
op_star
id|mi
suffix:semicolon
r_if
c_cond
(paren
l_int|32
op_ne
r_sizeof
(paren
r_struct
id|minix_inode
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;bad i-node size&quot;
)paren
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
id|NR_FILE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|file_table
(braket
id|i
)braket
dot
id|f_count
op_assign
l_int|0
suffix:semicolon
)brace
id|fcntl_init_locks
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|ROOT_DEV
)paren
op_eq
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Insert root floppy and press ENTER&quot;
)paren
suffix:semicolon
id|wait_for_keypress
c_func
(paren
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|super_block
(braket
l_int|0
)braket
suffix:semicolon
id|p
OL
op_amp
id|super_block
(braket
id|NR_SUPER
)braket
suffix:semicolon
id|p
op_increment
)paren
(brace
id|p-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|p-&gt;s_blocksize
op_assign
l_int|0
suffix:semicolon
id|p-&gt;s_lock
op_assign
l_int|0
suffix:semicolon
id|p-&gt;s_wait
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;s_mounted
op_assign
id|p-&gt;s_covered
op_assign
l_int|NULL
suffix:semicolon
)brace
r_while
c_loop
(paren
id|fs_type-&gt;read_super
op_logical_and
id|fs_type-&gt;name
)paren
(brace
id|p
op_assign
id|read_super
c_func
(paren
id|ROOT_DEV
comma
id|fs_type-&gt;name
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
id|mi
op_assign
id|p-&gt;s_mounted
suffix:semicolon
id|mi-&gt;i_count
op_add_assign
l_int|3
suffix:semicolon
multiline_comment|/* NOTE! it is logically used 4 times, not 1 */
id|p-&gt;s_covered
op_assign
id|mi
suffix:semicolon
id|p-&gt;s_flags
op_assign
l_int|0
suffix:semicolon
id|current-&gt;pwd
op_assign
id|mi
suffix:semicolon
id|current-&gt;root
op_assign
id|mi
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fs_type
op_increment
suffix:semicolon
)brace
id|panic
c_func
(paren
l_string|&quot;Unable to mount root&quot;
)paren
suffix:semicolon
)brace
eof
