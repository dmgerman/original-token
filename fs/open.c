multiline_comment|/*&n; *  linux/fs/open.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/vfs.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/utime.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
DECL|function|sys_statfs
id|asmlinkage
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
id|dentry
op_star
id|dentry
suffix:semicolon
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dentry
op_assign
id|namei
c_func
(paren
id|path
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|error
op_assign
op_minus
id|ENOSYS
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;s_op-&gt;statfs
)paren
id|error
op_assign
id|inode-&gt;i_sb-&gt;s_op
op_member_access_from_pointer
id|statfs
c_func
(paren
id|inode-&gt;i_sb
comma
id|buf
comma
r_sizeof
(paren
r_struct
id|statfs
)paren
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_fstatfs
id|asmlinkage
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
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
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
id|error
)paren
r_goto
id|out
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
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
)paren
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|dentry
op_assign
id|file-&gt;f_dentry
)paren
)paren
id|error
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|dentry-&gt;d_inode
)paren
)paren
id|error
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_sb
)paren
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_sb-&gt;s_op-&gt;statfs
)paren
id|error
op_assign
op_minus
id|ENOSYS
suffix:semicolon
r_else
id|inode-&gt;i_sb-&gt;s_op
op_member_access_from_pointer
id|statfs
c_func
(paren
id|inode-&gt;i_sb
comma
id|buf
comma
r_sizeof
(paren
r_struct
id|statfs
)paren
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|do_truncate
r_int
id|do_truncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|length
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|iattr
id|newattrs
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|newattrs.ia_size
op_assign
id|length
suffix:semicolon
id|newattrs.ia_valid
op_assign
id|ATTR_SIZE
op_or
id|ATTR_CTIME
suffix:semicolon
id|error
op_assign
id|notify_change
c_func
(paren
id|inode
comma
op_amp
id|newattrs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
multiline_comment|/* truncate virtual mappings of this file */
id|vmtruncate
c_func
(paren
id|inode
comma
id|length
)paren
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
)brace
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_truncate
id|asmlinkage
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
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dentry
op_assign
id|namei
c_func
(paren
id|path
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_goto
id|dput_and_out
suffix:semicolon
id|error
op_assign
id|permission
c_func
(paren
id|inode
comma
id|MAY_WRITE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|dput_and_out
suffix:semicolon
id|error
op_assign
op_minus
id|EROFS
suffix:semicolon
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
r_goto
id|dput_and_out
suffix:semicolon
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|IS_IMMUTABLE
c_func
(paren
id|inode
)paren
op_logical_or
id|IS_APPEND
c_func
(paren
id|inode
)paren
)paren
r_goto
id|dput_and_out
suffix:semicolon
id|error
op_assign
id|get_write_access
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|dput_and_out
suffix:semicolon
id|error
op_assign
id|locks_verify_area
c_func
(paren
id|FLOCK_VERIFY_WRITE
comma
id|inode
comma
l_int|NULL
comma
id|length
OL
id|inode-&gt;i_size
ques
c_cond
id|length
suffix:colon
id|inode-&gt;i_size
comma
id|abs
c_func
(paren
id|inode-&gt;i_size
op_minus
id|length
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_sb
op_logical_and
id|inode-&gt;i_sb-&gt;dq_op
)paren
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|initialize
c_func
(paren
id|inode
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|error
op_assign
id|do_truncate
c_func
(paren
id|inode
comma
id|length
)paren
suffix:semicolon
)brace
id|put_write_access
c_func
(paren
id|inode
)paren
suffix:semicolon
id|dput_and_out
suffix:colon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_ftruncate
id|asmlinkage
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
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
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
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
)paren
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|dentry
op_assign
id|file-&gt;f_dentry
)paren
)paren
id|error
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|dentry-&gt;d_inode
)paren
)paren
id|error
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_else
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
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
)paren
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
r_else
r_if
c_cond
(paren
id|IS_IMMUTABLE
c_func
(paren
id|inode
)paren
op_logical_or
id|IS_APPEND
c_func
(paren
id|inode
)paren
)paren
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
r_else
(brace
id|error
op_assign
id|locks_verify_area
c_func
(paren
id|FLOCK_VERIFY_WRITE
comma
id|inode
comma
id|file
comma
id|length
OL
id|inode-&gt;i_size
ques
c_cond
id|length
suffix:colon
id|inode-&gt;i_size
comma
id|abs
c_func
(paren
id|inode-&gt;i_size
op_minus
id|length
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|do_truncate
c_func
(paren
id|inode
comma
id|length
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
macro_line|#ifndef __alpha__
multiline_comment|/*&n; * sys_utime() can be implemented in user-level using sys_utimes().&n; * Is this for backwards compatibility?  If so, why not move it&n; * into the appropriate arch directory (for those architectures that&n; * need it).&n; */
multiline_comment|/* If times==NULL, set access and modification to current time,&n; * must be owner or have write permission.&n; * Else, update from *times, must be owner or super user.&n; */
DECL|function|sys_utime
id|asmlinkage
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
r_int
id|error
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|iattr
id|newattrs
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dentry
op_assign
id|namei
c_func
(paren
id|filename
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|error
op_assign
op_minus
id|EROFS
suffix:semicolon
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
r_goto
id|dput_and_out
suffix:semicolon
multiline_comment|/* Don&squot;t worry, the checks are done in inode_change_ok() */
id|newattrs.ia_valid
op_assign
id|ATTR_CTIME
op_or
id|ATTR_MTIME
op_or
id|ATTR_ATIME
suffix:semicolon
r_if
c_cond
(paren
id|times
)paren
(brace
id|error
op_assign
id|get_user
c_func
(paren
id|newattrs.ia_atime
comma
op_amp
id|times-&gt;actime
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|get_user
c_func
(paren
id|newattrs.ia_mtime
comma
op_amp
id|times-&gt;modtime
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|dput_and_out
suffix:semicolon
id|newattrs.ia_valid
op_or_assign
id|ATTR_ATIME_SET
op_or
id|ATTR_MTIME_SET
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
op_logical_and
(paren
id|error
op_assign
id|permission
c_func
(paren
id|inode
comma
id|MAY_WRITE
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|dput_and_out
suffix:semicolon
)brace
id|error
op_assign
id|notify_change
c_func
(paren
id|inode
comma
op_amp
id|newattrs
)paren
suffix:semicolon
id|dput_and_out
suffix:colon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* If times==NULL, set access and modification to current time,&n; * must be owner or have write permission.&n; * Else, update from *times, must be owner or super user.&n; */
DECL|function|sys_utimes
id|asmlinkage
r_int
id|sys_utimes
c_func
(paren
r_char
op_star
id|filename
comma
r_struct
id|timeval
op_star
id|utimes
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|iattr
id|newattrs
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dentry
op_assign
id|namei
c_func
(paren
id|filename
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|error
op_assign
op_minus
id|EROFS
suffix:semicolon
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
r_goto
id|dput_and_out
suffix:semicolon
multiline_comment|/* Don&squot;t worry, the checks are done in inode_change_ok() */
id|newattrs.ia_valid
op_assign
id|ATTR_CTIME
op_or
id|ATTR_MTIME
op_or
id|ATTR_ATIME
suffix:semicolon
r_if
c_cond
(paren
id|utimes
)paren
(brace
r_struct
id|timeval
id|times
(braket
l_int|2
)braket
suffix:semicolon
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|times
comma
id|utimes
comma
r_sizeof
(paren
id|times
)paren
)paren
)paren
r_goto
id|dput_and_out
suffix:semicolon
id|newattrs.ia_atime
op_assign
id|times
(braket
l_int|0
)braket
dot
id|tv_sec
suffix:semicolon
id|newattrs.ia_mtime
op_assign
id|times
(braket
l_int|1
)braket
dot
id|tv_sec
suffix:semicolon
id|newattrs.ia_valid
op_or_assign
id|ATTR_ATIME_SET
op_or
id|ATTR_MTIME_SET
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|permission
c_func
(paren
id|inode
comma
id|MAY_WRITE
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|dput_and_out
suffix:semicolon
)brace
id|error
op_assign
id|notify_change
c_func
(paren
id|inode
comma
op_amp
id|newattrs
)paren
suffix:semicolon
id|dput_and_out
suffix:colon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * access() needs to use the real uid/gid, not the effective uid/gid.&n; * We do this by temporarily setting fsuid/fsgid to the wanted values&n; */
DECL|function|sys_access
id|asmlinkage
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
id|dentry
op_star
id|dentry
suffix:semicolon
r_int
id|old_fsuid
comma
id|old_fsgid
suffix:semicolon
r_int
id|res
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_ne
(paren
id|mode
op_amp
id|S_IRWXO
)paren
)paren
multiline_comment|/* where&squot;s F_OK, X_OK, W_OK, R_OK? */
r_goto
id|out
suffix:semicolon
id|old_fsuid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|old_fsgid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|current-&gt;fsuid
op_assign
id|current-&gt;uid
suffix:semicolon
id|current-&gt;fsgid
op_assign
id|current-&gt;gid
suffix:semicolon
id|dentry
op_assign
id|namei
c_func
(paren
id|filename
)paren
suffix:semicolon
id|res
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
(brace
id|res
op_assign
id|permission
c_func
(paren
id|dentry-&gt;d_inode
comma
id|mode
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
id|current-&gt;fsuid
op_assign
id|old_fsuid
suffix:semicolon
id|current-&gt;fsgid
op_assign
id|old_fsgid
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|sys_chdir
id|asmlinkage
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
r_int
id|error
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
comma
op_star
id|tmp
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dentry
op_assign
id|namei
c_func
(paren
id|filename
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|error
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
id|dput_and_out
suffix:semicolon
id|error
op_assign
id|permission
c_func
(paren
id|inode
comma
id|MAY_EXEC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|dput_and_out
suffix:semicolon
multiline_comment|/* exchange dentries */
id|tmp
op_assign
id|current-&gt;fs-&gt;pwd
suffix:semicolon
id|current-&gt;fs-&gt;pwd
op_assign
id|dentry
suffix:semicolon
id|dentry
op_assign
id|tmp
suffix:semicolon
id|dput_and_out
suffix:colon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_fchdir
id|asmlinkage
r_int
id|sys_fchdir
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
id|file
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EBADF
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
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dentry
op_assign
id|file-&gt;f_dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|dentry-&gt;d_inode
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
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
id|out
suffix:semicolon
id|error
op_assign
id|permission
c_func
(paren
id|inode
comma
id|MAY_EXEC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
(brace
r_struct
id|dentry
op_star
id|tmp
suffix:semicolon
id|tmp
op_assign
id|current-&gt;fs-&gt;pwd
suffix:semicolon
id|current-&gt;fs-&gt;pwd
op_assign
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|dput
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_chroot
id|asmlinkage
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
r_int
id|error
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
comma
op_star
id|tmp
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dentry
op_assign
id|namei
c_func
(paren
id|filename
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|error
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
id|dput_and_out
suffix:semicolon
id|error
op_assign
id|permission
c_func
(paren
id|inode
comma
id|MAY_EXEC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|dput_and_out
suffix:semicolon
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fsuser
c_func
(paren
)paren
)paren
r_goto
id|dput_and_out
suffix:semicolon
multiline_comment|/* exchange dentries */
id|tmp
op_assign
id|current-&gt;fs-&gt;root
suffix:semicolon
id|current-&gt;fs-&gt;root
op_assign
id|dentry
suffix:semicolon
id|dentry
op_assign
id|tmp
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
id|dput_and_out
suffix:colon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_fchmod
id|asmlinkage
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
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|iattr
id|newattrs
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EBADF
suffix:semicolon
id|lock_kernel
c_func
(paren
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
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dentry
op_assign
id|file-&gt;f_dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|dentry-&gt;d_inode
)paren
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|EROFS
suffix:semicolon
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|IS_IMMUTABLE
c_func
(paren
id|inode
)paren
op_logical_or
id|IS_APPEND
c_func
(paren
id|inode
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
(paren
id|mode_t
)paren
op_minus
l_int|1
)paren
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|newattrs.ia_mode
op_assign
(paren
id|mode
op_amp
id|S_IALLUGO
)paren
op_or
(paren
id|inode-&gt;i_mode
op_amp
op_complement
id|S_IALLUGO
)paren
suffix:semicolon
id|newattrs.ia_valid
op_assign
id|ATTR_MODE
op_or
id|ATTR_CTIME
suffix:semicolon
id|err
op_assign
id|notify_change
c_func
(paren
id|inode
comma
op_amp
id|newattrs
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|sys_chmod
id|asmlinkage
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
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|iattr
id|newattrs
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dentry
op_assign
id|namei
c_func
(paren
id|filename
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|error
op_assign
op_minus
id|EROFS
suffix:semicolon
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
r_goto
id|dput_and_out
suffix:semicolon
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|IS_IMMUTABLE
c_func
(paren
id|inode
)paren
op_logical_or
id|IS_APPEND
c_func
(paren
id|inode
)paren
)paren
r_goto
id|dput_and_out
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
(paren
id|mode_t
)paren
op_minus
l_int|1
)paren
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|newattrs.ia_mode
op_assign
(paren
id|mode
op_amp
id|S_IALLUGO
)paren
op_or
(paren
id|inode-&gt;i_mode
op_amp
op_complement
id|S_IALLUGO
)paren
suffix:semicolon
id|newattrs.ia_valid
op_assign
id|ATTR_MODE
op_or
id|ATTR_CTIME
suffix:semicolon
id|error
op_assign
id|notify_change
c_func
(paren
id|inode
comma
op_amp
id|newattrs
)paren
suffix:semicolon
id|dput_and_out
suffix:colon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|chown_common
r_static
r_int
id|chown_common
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
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
id|iattr
id|newattrs
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
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
id|dentry-&gt;d_inode
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;chown_common: NULL inode&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|error
op_assign
op_minus
id|EROFS
suffix:semicolon
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|IS_IMMUTABLE
c_func
(paren
id|inode
)paren
op_logical_or
id|IS_APPEND
c_func
(paren
id|inode
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|user
op_eq
(paren
id|uid_t
)paren
op_minus
l_int|1
)paren
id|user
op_assign
id|inode-&gt;i_uid
suffix:semicolon
r_if
c_cond
(paren
id|group
op_eq
(paren
id|gid_t
)paren
op_minus
l_int|1
)paren
id|group
op_assign
id|inode-&gt;i_gid
suffix:semicolon
id|newattrs.ia_mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|newattrs.ia_uid
op_assign
id|user
suffix:semicolon
id|newattrs.ia_gid
op_assign
id|group
suffix:semicolon
id|newattrs.ia_valid
op_assign
id|ATTR_UID
op_or
id|ATTR_GID
op_or
id|ATTR_CTIME
suffix:semicolon
multiline_comment|/*&n;&t; * If the owner has been changed, remove the setuid bit&n;&t; */
r_if
c_cond
(paren
id|inode-&gt;i_mode
op_amp
id|S_ISUID
)paren
(brace
id|newattrs.ia_mode
op_and_assign
op_complement
id|S_ISUID
suffix:semicolon
id|newattrs.ia_valid
op_or_assign
id|ATTR_MODE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If the group has been changed, remove the setgid bit&n;&t; *&n;&t; * Don&squot;t remove the setgid bit if no group execute bit.&n;&t; * This is a file marked for mandatory locking.&n;&t; */
r_if
c_cond
(paren
(paren
(paren
id|inode-&gt;i_mode
op_amp
(paren
id|S_ISGID
op_or
id|S_IXGRP
)paren
)paren
op_eq
(paren
id|S_ISGID
op_or
id|S_IXGRP
)paren
)paren
)paren
(brace
id|newattrs.ia_mode
op_and_assign
op_complement
id|S_ISGID
suffix:semicolon
id|newattrs.ia_valid
op_or_assign
id|ATTR_MODE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_sb
op_logical_and
id|inode-&gt;i_sb-&gt;dq_op
)paren
(brace
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|initialize
c_func
(paren
id|inode
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EDQUOT
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|transfer
c_func
(paren
id|inode
comma
op_amp
id|newattrs
comma
l_int|0
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|notify_change
c_func
(paren
id|inode
comma
op_amp
id|newattrs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|transfer
c_func
(paren
id|inode
comma
op_amp
id|newattrs
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|error
op_assign
id|notify_change
c_func
(paren
id|inode
comma
op_amp
id|newattrs
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_chown
id|asmlinkage
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
id|dentry
op_star
id|dentry
suffix:semicolon
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dentry
op_assign
id|lnamei
c_func
(paren
id|filename
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
(brace
id|error
op_assign
id|chown_common
c_func
(paren
id|dentry
comma
id|user
comma
id|group
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_fchown
id|asmlinkage
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
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
id|lock_kernel
c_func
(paren
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
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dentry
op_assign
id|file-&gt;f_dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|chown_common
c_func
(paren
id|dentry
comma
id|user
comma
id|group
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that while the flag value (low two bits) for sys_open means:&n; *&t;00 - read-only&n; *&t;01 - write-only&n; *&t;10 - read-write&n; *&t;11 - special&n; * it is changed into&n; *&t;00 - no permissions needed&n; *&t;01 - read-permission&n; *&t;10 - write-permission&n; *&t;11 - read-write&n; * for the internal routines (ie open_namei()/follow_link() etc). 00 is&n; * used by symlinks.&n; */
DECL|function|do_open
r_static
r_int
id|do_open
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_int
id|flags
comma
r_int
id|mode
comma
r_int
id|fd
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|file
op_star
id|f
suffix:semicolon
r_int
id|flag
comma
id|error
suffix:semicolon
id|f
op_assign
id|get_empty_filp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
r_return
op_minus
id|ENFILE
suffix:semicolon
id|f-&gt;f_flags
op_assign
id|flag
op_assign
id|flags
suffix:semicolon
id|f-&gt;f_mode
op_assign
(paren
id|flag
op_plus
l_int|1
)paren
op_amp
id|O_ACCMODE
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;f_mode
)paren
id|flag
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|flag
op_amp
id|O_TRUNC
)paren
id|flag
op_or_assign
l_int|2
suffix:semicolon
id|dentry
op_assign
id|open_namei
c_func
(paren
id|filename
comma
id|flag
comma
id|mode
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|cleanup_file
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
(brace
id|error
op_assign
id|get_write_access
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|cleanup_dentry
suffix:semicolon
)brace
id|f-&gt;f_dentry
op_assign
id|dentry
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
(brace
id|error
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
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|cleanup_all
suffix:semicolon
)brace
id|f-&gt;f_flags
op_and_assign
op_complement
(paren
id|O_CREAT
op_or
id|O_EXCL
op_or
id|O_NOCTTY
op_or
id|O_TRUNC
)paren
suffix:semicolon
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
op_assign
id|f
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|cleanup_all
suffix:colon
r_if
c_cond
(paren
id|f-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
id|put_write_access
c_func
(paren
id|inode
)paren
suffix:semicolon
id|cleanup_dentry
suffix:colon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|cleanup_file
suffix:colon
id|put_filp
c_func
(paren
id|f
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Find an empty file descriptor entry, and mark it busy&n; */
DECL|function|get_unused_fd
r_int
id|get_unused_fd
c_func
(paren
r_void
)paren
(brace
r_int
id|fd
suffix:semicolon
r_struct
id|files_struct
op_star
id|files
op_assign
id|current-&gt;files
suffix:semicolon
id|fd
op_assign
id|find_first_zero_bit
c_func
(paren
op_amp
id|files-&gt;open_fds
comma
id|NR_OPEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
id|current-&gt;rlim
(braket
id|RLIMIT_NOFILE
)braket
dot
id|rlim_cur
)paren
(brace
id|FD_SET
c_func
(paren
id|fd
comma
op_amp
id|files-&gt;open_fds
)paren
suffix:semicolon
id|FD_CLR
c_func
(paren
id|fd
comma
op_amp
id|files-&gt;close_on_exec
)paren
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
r_return
op_minus
id|EMFILE
suffix:semicolon
)brace
DECL|function|put_unused_fd
r_inline
r_void
id|put_unused_fd
c_func
(paren
r_int
id|fd
)paren
(brace
id|FD_CLR
c_func
(paren
id|fd
comma
op_amp
id|current-&gt;files-&gt;open_fds
)paren
suffix:semicolon
)brace
DECL|function|sys_open
id|asmlinkage
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
id|flags
comma
r_int
id|mode
)paren
(brace
r_char
op_star
id|tmp
suffix:semicolon
r_int
id|fd
comma
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|error
op_assign
id|get_unused_fd
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|fd
op_assign
id|error
suffix:semicolon
id|tmp
op_assign
id|getname
c_func
(paren
id|filename
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|tmp
)paren
)paren
(brace
id|error
op_assign
id|do_open
c_func
(paren
id|tmp
comma
id|flags
comma
id|mode
comma
id|fd
)paren
suffix:semicolon
id|putname
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|error
op_assign
id|fd
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|put_unused_fd
c_func
(paren
id|fd
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
macro_line|#ifndef __alpha__
multiline_comment|/*&n; * For backward compatibility?  Maybe this should be moved&n; * into arch/i386 instead?&n; */
DECL|function|sys_creat
id|asmlinkage
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
r_int
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
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
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
DECL|function|__fput
r_int
id|__fput
c_func
(paren
r_struct
id|file
op_star
id|filp
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|filp-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_op
op_logical_and
id|filp-&gt;f_op-&gt;release
)paren
id|error
op_assign
id|filp-&gt;f_op
op_member_access_from_pointer
id|release
c_func
(paren
id|inode
comma
id|filp
)paren
suffix:semicolon
id|filp-&gt;f_dentry
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
id|put_write_access
c_func
(paren
id|inode
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|close_fp
r_int
id|close_fp
c_func
(paren
r_struct
id|file
op_star
id|filp
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
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
l_string|&quot;VFS: Close: file count is 0&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|dentry
op_assign
id|filp-&gt;f_dentry
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
id|locks_remove_locks
c_func
(paren
id|current
comma
id|filp
)paren
suffix:semicolon
r_return
id|fput
c_func
(paren
id|filp
)paren
suffix:semicolon
)brace
DECL|function|sys_close
id|asmlinkage
r_int
id|sys_close
c_func
(paren
r_int
r_int
id|fd
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_struct
id|files_struct
op_star
id|files
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|files
op_assign
id|current-&gt;files
suffix:semicolon
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
id|NR_OPEN
op_logical_and
(paren
id|filp
op_assign
id|files-&gt;fd
(braket
id|fd
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|put_unused_fd
c_func
(paren
id|fd
)paren
suffix:semicolon
id|FD_CLR
c_func
(paren
id|fd
comma
op_amp
id|files-&gt;close_on_exec
)paren
suffix:semicolon
id|files-&gt;fd
(braket
id|fd
)braket
op_assign
l_int|NULL
suffix:semicolon
id|error
op_assign
id|close_fp
c_func
(paren
id|filp
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine simulates a hangup on the tty, to arrange that users&n; * are given clean terminals at login time.&n; */
DECL|function|sys_vhangup
id|asmlinkage
r_int
id|sys_vhangup
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
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
r_goto
id|out
suffix:semicolon
multiline_comment|/* If there is a controlling tty, hang it up */
r_if
c_cond
(paren
id|current-&gt;tty
)paren
id|tty_vhangup
c_func
(paren
id|current-&gt;tty
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
