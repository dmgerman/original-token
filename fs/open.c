multiline_comment|/*&n; *  linux/fs/open.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;utime.h&gt;
macro_line|#include &lt;sys/vfs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|variable|chrdev_fops
r_struct
id|file_operations
op_star
id|chrdev_fops
(braket
id|MAX_CHRDEV
)braket
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|blkdev_fops
r_struct
id|file_operations
op_star
id|blkdev_fops
(braket
id|MAX_BLKDEV
)braket
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|sys_ustat
r_int
id|sys_ustat
c_func
(paren
r_int
id|dev
comma
r_struct
id|ustat
op_star
id|ubuf
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_statfs
r_int
id|sys_statfs
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|statfs
op_star
id|buf
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|verify_area
c_func
(paren
id|buf
comma
r_sizeof
(paren
r_struct
id|statfs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|namei
c_func
(paren
id|path
)paren
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
id|inode-&gt;i_sb-&gt;s_op-&gt;statfs
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
id|ENOSYS
suffix:semicolon
)brace
id|inode-&gt;i_sb-&gt;s_op
op_member_access_from_pointer
id|statfs
c_func
(paren
id|inode-&gt;i_sb
comma
id|buf
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
DECL|function|sys_fstatfs
r_int
id|sys_fstatfs
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|statfs
op_star
id|buf
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
id|verify_area
c_func
(paren
id|buf
comma
r_sizeof
(paren
r_struct
id|statfs
)paren
)paren
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
id|file
op_assign
id|current-&gt;filp
(braket
id|fd
)braket
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|file-&gt;f_inode
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
id|inode-&gt;i_sb-&gt;s_op-&gt;statfs
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
id|inode-&gt;i_sb-&gt;s_op
op_member_access_from_pointer
id|statfs
c_func
(paren
id|inode-&gt;i_sb
comma
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_truncate
r_int
id|sys_truncate
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_int
id|length
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|namei
c_func
(paren
id|path
)paren
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
op_logical_neg
id|permission
c_func
(paren
id|inode
comma
id|MAY_WRITE
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
id|inode-&gt;i_size
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_op
op_logical_and
id|inode-&gt;i_op-&gt;truncate
)paren
id|inode-&gt;i_op
op_member_access_from_pointer
id|truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
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
DECL|function|sys_ftruncate
r_int
id|sys_ftruncate
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|length
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|file
op_star
id|file
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
id|file
op_assign
id|current-&gt;filp
(braket
id|fd
)braket
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|file-&gt;f_inode
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
op_logical_neg
(paren
id|file-&gt;f_flags
op_amp
l_int|2
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_op
op_logical_and
id|inode-&gt;i_op-&gt;truncate
)paren
id|inode-&gt;i_op
op_member_access_from_pointer
id|truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* If times==NULL, set access and modification to current time,&n; * must be owner or have write permission.&n; * Else, update from *times, must be owner or super user.&n; */
DECL|function|sys_utime
r_int
id|sys_utime
c_func
(paren
r_char
op_star
id|filename
comma
r_struct
id|utimbuf
op_star
id|times
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|actime
comma
id|modtime
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|namei
c_func
(paren
id|filename
)paren
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|times
)paren
(brace
r_if
c_cond
(paren
(paren
id|current-&gt;euid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
op_logical_neg
id|suser
c_func
(paren
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
id|EPERM
suffix:semicolon
)brace
id|actime
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|times-&gt;actime
)paren
suffix:semicolon
id|modtime
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|times-&gt;modtime
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|current-&gt;euid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
op_logical_neg
id|permission
c_func
(paren
id|inode
comma
id|MAY_WRITE
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
id|actime
op_assign
id|modtime
op_assign
id|CURRENT_TIME
suffix:semicolon
)brace
id|inode-&gt;i_atime
op_assign
id|actime
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|modtime
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
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
multiline_comment|/*&n; * XXX should we use the real or effective uid?  BSD uses the real uid,&n; * so as to make this call useful to setuid programs.&n; */
DECL|function|sys_access
r_int
id|sys_access
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_int
id|mode
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|res
comma
id|i_mode
suffix:semicolon
id|mode
op_and_assign
l_int|0007
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|namei
c_func
(paren
id|filename
)paren
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|i_mode
op_assign
id|res
op_assign
id|inode-&gt;i_mode
op_amp
l_int|0777
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
id|current-&gt;uid
op_eq
id|inode-&gt;i_uid
)paren
id|res
op_rshift_assign
l_int|6
suffix:semicolon
r_else
r_if
c_cond
(paren
id|in_group_p
c_func
(paren
id|inode-&gt;i_gid
)paren
)paren
id|res
op_rshift_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_amp
l_int|0007
op_amp
id|mode
)paren
op_eq
id|mode
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * XXX we are doing this test last because we really should be&n;&t; * swapping the effective with the real user id (temporarily),&n;&t; * and then calling suser() routine.  If we do call the&n;&t; * suser() routine, it needs to be called last. &n;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
id|current-&gt;uid
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|mode
op_amp
l_int|1
)paren
op_logical_or
(paren
id|i_mode
op_amp
l_int|0111
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
DECL|function|sys_chdir
r_int
id|sys_chdir
c_func
(paren
r_const
r_char
op_star
id|filename
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|namei
c_func
(paren
id|filename
)paren
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
id|S_ISDIR
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
id|ENOTDIR
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|permission
c_func
(paren
id|inode
comma
id|MAY_EXEC
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
id|iput
c_func
(paren
id|current-&gt;pwd
)paren
suffix:semicolon
id|current-&gt;pwd
op_assign
id|inode
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|sys_chroot
r_int
id|sys_chroot
c_func
(paren
r_const
r_char
op_star
id|filename
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|namei
c_func
(paren
id|filename
)paren
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
id|S_ISDIR
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
id|ENOTDIR
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
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
id|EPERM
suffix:semicolon
)brace
id|iput
c_func
(paren
id|current-&gt;root
)paren
suffix:semicolon
id|current-&gt;root
op_assign
id|inode
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|sys_fchmod
r_int
id|sys_fchmod
c_func
(paren
r_int
r_int
id|fd
comma
id|mode_t
id|mode
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|file
op_star
id|file
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
id|file
op_assign
id|current-&gt;filp
(braket
id|fd
)braket
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|file-&gt;f_inode
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;euid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
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
id|inode-&gt;i_mode
op_assign
(paren
id|mode
op_amp
l_int|07777
)paren
op_or
(paren
id|inode-&gt;i_mode
op_amp
op_complement
l_int|07777
)paren
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_chmod
r_int
id|sys_chmod
c_func
(paren
r_const
r_char
op_star
id|filename
comma
id|mode_t
id|mode
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|namei
c_func
(paren
id|filename
)paren
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;euid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
op_logical_neg
id|suser
c_func
(paren
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
id|EPERM
suffix:semicolon
)brace
id|inode-&gt;i_mode
op_assign
(paren
id|mode
op_amp
l_int|07777
)paren
op_or
(paren
id|inode-&gt;i_mode
op_amp
op_complement
l_int|07777
)paren
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
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
DECL|function|sys_fchown
r_int
id|sys_fchown
c_func
(paren
r_int
r_int
id|fd
comma
id|uid_t
id|user
comma
id|gid_t
id|group
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|file
op_star
id|file
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
id|file
op_assign
id|current-&gt;filp
(braket
id|fd
)braket
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|file-&gt;f_inode
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;euid
op_eq
id|inode-&gt;i_uid
op_logical_and
id|user
op_eq
id|inode-&gt;i_uid
op_logical_and
(paren
id|in_group_p
c_func
(paren
id|group
)paren
op_logical_or
id|group
op_eq
id|inode-&gt;i_gid
)paren
)paren
op_logical_or
id|suser
c_func
(paren
)paren
)paren
(brace
id|inode-&gt;i_uid
op_assign
id|user
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|group
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
DECL|function|sys_chown
r_int
id|sys_chown
c_func
(paren
r_const
r_char
op_star
id|filename
comma
id|uid_t
id|user
comma
id|gid_t
id|group
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|lnamei
c_func
(paren
id|filename
)paren
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;euid
op_eq
id|inode-&gt;i_uid
op_logical_and
id|user
op_eq
id|inode-&gt;i_uid
op_logical_and
(paren
id|in_group_p
c_func
(paren
id|group
)paren
op_logical_or
id|group
op_eq
id|inode-&gt;i_gid
)paren
)paren
op_logical_or
id|suser
c_func
(paren
)paren
)paren
(brace
id|inode-&gt;i_uid
op_assign
id|user
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|group
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
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
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
DECL|function|sys_open
r_int
id|sys_open
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_int
id|flag
comma
r_int
id|mode
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|file
op_star
id|f
suffix:semicolon
r_int
id|i
comma
id|fd
suffix:semicolon
r_for
c_loop
(paren
id|fd
op_assign
l_int|0
suffix:semicolon
id|fd
OL
id|NR_OPEN
suffix:semicolon
id|fd
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;filp
(braket
id|fd
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
id|NR_OPEN
)paren
r_return
op_minus
id|EMFILE
suffix:semicolon
id|current-&gt;close_on_exec
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|fd
)paren
suffix:semicolon
id|f
op_assign
l_int|0
op_plus
id|file_table
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
comma
id|f
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|f-&gt;f_count
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|NR_FILE
)paren
r_return
op_minus
id|ENFILE
suffix:semicolon
(paren
id|current-&gt;filp
(braket
id|fd
)braket
op_assign
id|f
)paren
op_member_access_from_pointer
id|f_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_assign
id|open_namei
c_func
(paren
id|filename
comma
id|flag
comma
id|mode
comma
op_amp
id|inode
)paren
)paren
OL
l_int|0
)paren
(brace
id|current-&gt;filp
(braket
id|fd
)braket
op_assign
l_int|NULL
suffix:semicolon
id|f-&gt;f_count
op_assign
l_int|0
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
id|f-&gt;f_mode
op_assign
l_string|&quot;&bslash;001&bslash;002&bslash;003&bslash;000&quot;
(braket
id|flag
op_amp
id|O_ACCMODE
)braket
suffix:semicolon
id|f-&gt;f_flags
op_assign
id|flag
suffix:semicolon
id|f-&gt;f_count
op_assign
l_int|1
suffix:semicolon
id|f-&gt;f_inode
op_assign
id|inode
suffix:semicolon
id|f-&gt;f_pos
op_assign
l_int|0
suffix:semicolon
id|f-&gt;f_reada
op_assign
l_int|0
suffix:semicolon
id|f-&gt;f_op
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_op
)paren
id|f-&gt;f_op
op_assign
id|inode-&gt;i_op-&gt;default_file_ops
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;f_op
op_logical_and
id|f-&gt;f_op-&gt;open
)paren
r_if
c_cond
(paren
id|i
op_assign
id|f-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|f
)paren
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|f-&gt;f_count
op_assign
l_int|0
suffix:semicolon
id|current-&gt;filp
(braket
id|fd
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
r_return
(paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|sys_creat
r_int
id|sys_creat
c_func
(paren
r_const
r_char
op_star
id|pathname
comma
r_int
id|mode
)paren
(brace
r_return
id|sys_open
c_func
(paren
id|pathname
comma
id|O_CREAT
op_or
id|O_WRONLY
op_or
id|O_TRUNC
comma
id|mode
)paren
suffix:semicolon
)brace
DECL|function|sys_close
r_int
id|sys_close
c_func
(paren
r_int
r_int
id|fd
)paren
(brace
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
id|NR_OPEN
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|current-&gt;close_on_exec
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|filp
op_assign
id|current-&gt;filp
(braket
id|fd
)braket
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|current-&gt;filp
(braket
id|fd
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_count
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Close: file count is 0&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_count
OG
l_int|1
)paren
(brace
id|filp-&gt;f_count
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_op
op_logical_and
id|filp-&gt;f_op-&gt;release
)paren
id|filp-&gt;f_op
op_member_access_from_pointer
id|release
c_func
(paren
id|filp-&gt;f_inode
comma
id|filp
)paren
suffix:semicolon
id|iput
c_func
(paren
id|filp-&gt;f_inode
)paren
suffix:semicolon
id|filp-&gt;f_count
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
