multiline_comment|/*&n; *  linux/fs/fcntl.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/dnotify.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/poll.h&gt;
macro_line|#include &lt;asm/siginfo.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_int
id|sock_fcntl
(paren
r_struct
id|file
op_star
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|fcntl_setlease
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|file
op_star
id|filp
comma
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|fcntl_getlease
c_func
(paren
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
multiline_comment|/* Expand files.  Return &lt;0 on error; 0 nothing done; 1 files expanded,&n; * we may have blocked. &n; *&n; * Should be called with the files-&gt;file_lock spinlock held for write.&n; */
DECL|function|expand_files
r_static
r_int
id|expand_files
c_func
(paren
r_struct
id|files_struct
op_star
id|files
comma
r_int
id|nr
)paren
(brace
r_int
id|err
comma
id|expand
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef FDSET_DEBUG&t;
id|printk
(paren
id|KERN_ERR
id|__FUNCTION__
l_string|&quot; %d: nr = %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|nr
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|nr
op_ge
id|files-&gt;max_fdset
)paren
(brace
id|expand
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|expand_fdset
c_func
(paren
id|files
comma
id|nr
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr
op_ge
id|files-&gt;max_fds
)paren
(brace
id|expand
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|expand_fd_array
c_func
(paren
id|files
comma
id|nr
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|expand
suffix:semicolon
id|out
suffix:colon
macro_line|#ifdef FDSET_DEBUG&t;
r_if
c_cond
(paren
id|err
)paren
id|printk
(paren
id|KERN_ERR
id|__FUNCTION__
l_string|&quot; %d: return %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|err
)paren
suffix:semicolon
macro_line|#endif
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * locate_fd finds a free file descriptor in the open_fds fdset,&n; * expanding the fd arrays if necessary.  The files write lock will be&n; * held on exit to ensure that the fd can be entered atomically.&n; */
DECL|function|locate_fd
r_static
r_int
id|locate_fd
c_func
(paren
r_struct
id|files_struct
op_star
id|files
comma
r_struct
id|file
op_star
id|file
comma
r_int
id|orig_start
)paren
(brace
r_int
r_int
id|newfd
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|start
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
id|repeat
suffix:colon
multiline_comment|/*&n;&t; * Someone might have closed fd&squot;s in the range&n;&t; * orig_start..files-&gt;next_fd&n;&t; */
id|start
op_assign
id|orig_start
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
id|files-&gt;next_fd
)paren
id|start
op_assign
id|files-&gt;next_fd
suffix:semicolon
id|newfd
op_assign
id|start
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
id|files-&gt;max_fdset
)paren
(brace
id|newfd
op_assign
id|find_next_zero_bit
c_func
(paren
id|files-&gt;open_fds-&gt;fds_bits
comma
id|files-&gt;max_fdset
comma
id|start
)paren
suffix:semicolon
)brace
id|error
op_assign
op_minus
id|EMFILE
suffix:semicolon
r_if
c_cond
(paren
id|newfd
op_ge
id|current-&gt;rlim
(braket
id|RLIMIT_NOFILE
)braket
dot
id|rlim_cur
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|expand_files
c_func
(paren
id|files
comma
id|newfd
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
multiline_comment|/*&n;&t; * If we needed to expand the fs array we&n;&t; * might have blocked - try again.&n;&t; */
r_if
c_cond
(paren
id|error
)paren
r_goto
id|repeat
suffix:semicolon
r_if
c_cond
(paren
id|start
op_le
id|files-&gt;next_fd
)paren
id|files-&gt;next_fd
op_assign
id|newfd
op_plus
l_int|1
suffix:semicolon
id|error
op_assign
id|newfd
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|allocate_fd
r_static
r_inline
r_void
id|allocate_fd
c_func
(paren
r_struct
id|files_struct
op_star
id|files
comma
r_struct
id|file
op_star
id|file
comma
r_int
id|fd
)paren
(brace
id|FD_SET
c_func
(paren
id|fd
comma
id|files-&gt;open_fds
)paren
suffix:semicolon
id|FD_CLR
c_func
(paren
id|fd
comma
id|files-&gt;close_on_exec
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
id|fd_install
c_func
(paren
id|fd
comma
id|file
)paren
suffix:semicolon
)brace
DECL|function|dupfd
r_static
r_int
id|dupfd
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
id|start
)paren
(brace
r_struct
id|files_struct
op_star
id|files
op_assign
id|current-&gt;files
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|locate_fd
c_func
(paren
id|files
comma
id|file
comma
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|out_putf
suffix:semicolon
id|allocate_fd
c_func
(paren
id|files
comma
id|file
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|out_putf
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_dup2
id|asmlinkage
r_int
id|sys_dup2
c_func
(paren
r_int
r_int
id|oldfd
comma
r_int
r_int
id|newfd
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EBADF
suffix:semicolon
r_struct
id|file
op_star
id|file
comma
op_star
id|tofree
suffix:semicolon
r_struct
id|files_struct
op_star
id|files
op_assign
id|current-&gt;files
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|file
op_assign
id|fcheck
c_func
(paren
id|oldfd
)paren
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|err
op_assign
id|newfd
suffix:semicolon
r_if
c_cond
(paren
id|newfd
op_eq
id|oldfd
)paren
r_goto
id|out_unlock
suffix:semicolon
id|err
op_assign
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|newfd
op_ge
id|current-&gt;rlim
(braket
id|RLIMIT_NOFILE
)braket
dot
id|rlim_cur
)paren
r_goto
id|out_unlock
suffix:semicolon
id|get_file
c_func
(paren
id|file
)paren
suffix:semicolon
multiline_comment|/* We are now finished with oldfd */
id|err
op_assign
id|expand_files
c_func
(paren
id|files
comma
id|newfd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|out_fput
suffix:semicolon
multiline_comment|/* To avoid races with open() and dup(), we will mark the fd as&n;&t; * in-use in the open-file bitmap throughout the entire dup2()&n;&t; * process.  This is quite safe: do_close() uses the fd array&n;&t; * entry, not the bitmap, to decide what work needs to be&n;&t; * done.  --sct */
multiline_comment|/* Doesn&squot;t work. open() might be there first. --AV */
multiline_comment|/* Yes. It&squot;s a race. In user space. Nothing sane to do */
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
id|tofree
op_assign
id|files-&gt;fd
(braket
id|newfd
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tofree
op_logical_and
id|FD_ISSET
c_func
(paren
id|newfd
comma
id|files-&gt;open_fds
)paren
)paren
r_goto
id|out_fput
suffix:semicolon
id|files-&gt;fd
(braket
id|newfd
)braket
op_assign
id|file
suffix:semicolon
id|FD_SET
c_func
(paren
id|newfd
comma
id|files-&gt;open_fds
)paren
suffix:semicolon
id|FD_CLR
c_func
(paren
id|newfd
comma
id|files-&gt;close_on_exec
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tofree
)paren
id|filp_close
c_func
(paren
id|tofree
comma
id|files
)paren
suffix:semicolon
id|err
op_assign
id|newfd
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
id|out_unlock
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_fput
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|sys_dup
id|asmlinkage
r_int
id|sys_dup
c_func
(paren
r_int
r_int
id|fildes
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EBADF
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
id|fget
c_func
(paren
id|fildes
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
id|ret
op_assign
id|dupfd
c_func
(paren
id|file
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|macro|SETFL_MASK
mdefine_line|#define SETFL_MASK (O_APPEND | O_NONBLOCK | O_NDELAY | FASYNC)
DECL|function|setfl
r_static
r_int
id|setfl
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/*&n;&t; * In the case of an append-only file, O_APPEND&n;&t; * cannot be cleared&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|arg
op_amp
id|O_APPEND
)paren
op_logical_and
id|IS_APPEND
c_func
(paren
id|inode
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* Did FASYNC state change? */
r_if
c_cond
(paren
(paren
id|arg
op_xor
id|filp-&gt;f_flags
)paren
op_amp
id|FASYNC
)paren
(brace
r_if
c_cond
(paren
id|filp-&gt;f_op
op_logical_and
id|filp-&gt;f_op-&gt;fasync
)paren
(brace
id|error
op_assign
id|filp-&gt;f_op
op_member_access_from_pointer
id|fasync
c_func
(paren
id|fd
comma
id|filp
comma
(paren
id|arg
op_amp
id|FASYNC
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_return
id|error
suffix:semicolon
)brace
)brace
multiline_comment|/* required for strict SunOS emulation */
r_if
c_cond
(paren
id|O_NONBLOCK
op_ne
id|O_NDELAY
)paren
r_if
c_cond
(paren
id|arg
op_amp
id|O_NDELAY
)paren
id|arg
op_or_assign
id|O_NONBLOCK
suffix:semicolon
id|filp-&gt;f_flags
op_assign
(paren
id|arg
op_amp
id|SETFL_MASK
)paren
op_or
(paren
id|filp-&gt;f_flags
op_amp
op_complement
id|SETFL_MASK
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_fcntl
r_static
r_int
id|do_fcntl
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|F_DUPFD
suffix:colon
r_if
c_cond
(paren
id|arg
OL
id|NR_OPEN
)paren
(brace
id|get_file
c_func
(paren
id|filp
)paren
suffix:semicolon
id|err
op_assign
id|dupfd
c_func
(paren
id|filp
comma
id|arg
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|F_GETFD
suffix:colon
id|err
op_assign
id|get_close_on_exec
c_func
(paren
id|fd
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_SETFD
suffix:colon
id|err
op_assign
l_int|0
suffix:semicolon
id|set_close_on_exec
c_func
(paren
id|fd
comma
id|arg
op_amp
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_GETFL
suffix:colon
id|err
op_assign
id|filp-&gt;f_flags
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_SETFL
suffix:colon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|setfl
c_func
(paren
id|fd
comma
id|filp
comma
id|arg
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_GETLK
suffix:colon
id|err
op_assign
id|fcntl_getlk
c_func
(paren
id|fd
comma
(paren
r_struct
id|flock
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_SETLK
suffix:colon
r_case
id|F_SETLKW
suffix:colon
id|err
op_assign
id|fcntl_setlk
c_func
(paren
id|fd
comma
id|cmd
comma
(paren
r_struct
id|flock
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_GETOWN
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * XXX If f_owner is a process group, the&n;&t;&t;&t; * negative return value will get converted&n;&t;&t;&t; * into an error.  Oops.  If we keep the&n;&t;&t;&t; * current syscall conventions, the only way&n;&t;&t;&t; * to fix this will be in libc.&n;&t;&t;&t; */
id|err
op_assign
id|filp-&gt;f_owner.pid
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_SETOWN
suffix:colon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|filp-&gt;f_owner.pid
op_assign
id|arg
suffix:semicolon
id|filp-&gt;f_owner.uid
op_assign
id|current-&gt;uid
suffix:semicolon
id|filp-&gt;f_owner.euid
op_assign
id|current-&gt;euid
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|S_ISSOCK
(paren
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_mode
)paren
)paren
id|err
op_assign
id|sock_fcntl
(paren
id|filp
comma
id|F_SETOWN
comma
id|arg
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_GETSIG
suffix:colon
id|err
op_assign
id|filp-&gt;f_owner.signum
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_SETSIG
suffix:colon
multiline_comment|/* arg == 0 restores default behaviour. */
r_if
c_cond
(paren
id|arg
template_param
id|_NSIG
)paren
(brace
r_break
suffix:semicolon
)brace
id|err
op_assign
l_int|0
suffix:semicolon
id|filp-&gt;f_owner.signum
op_assign
id|arg
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_GETLEASE
suffix:colon
id|err
op_assign
id|fcntl_getlease
c_func
(paren
id|filp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_SETLEASE
suffix:colon
id|err
op_assign
id|fcntl_setlease
c_func
(paren
id|fd
comma
id|filp
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_NOTIFY
suffix:colon
id|err
op_assign
id|fcntl_dirnotify
c_func
(paren
id|fd
comma
id|filp
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* sockets need a few special fcntls. */
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|S_ISSOCK
(paren
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_mode
)paren
)paren
id|err
op_assign
id|sock_fcntl
(paren
id|filp
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|sys_fcntl
id|asmlinkage
r_int
id|sys_fcntl
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EBADF
suffix:semicolon
id|filp
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filp
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
id|do_fcntl
c_func
(paren
id|fd
comma
id|cmd
comma
id|arg
comma
id|filp
)paren
suffix:semicolon
id|fput
c_func
(paren
id|filp
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
macro_line|#if BITS_PER_LONG == 32
DECL|function|sys_fcntl64
id|asmlinkage
r_int
id|sys_fcntl64
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
op_minus
id|EBADF
suffix:semicolon
id|filp
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filp
)paren
r_goto
id|out
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|F_GETLK64
suffix:colon
id|err
op_assign
id|fcntl_getlk64
c_func
(paren
id|fd
comma
(paren
r_struct
id|flock64
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_SETLK64
suffix:colon
id|err
op_assign
id|fcntl_setlk64
c_func
(paren
id|fd
comma
id|cmd
comma
(paren
r_struct
id|flock64
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_SETLKW64
suffix:colon
id|err
op_assign
id|fcntl_setlk64
c_func
(paren
id|fd
comma
id|cmd
comma
(paren
r_struct
id|flock64
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
id|do_fcntl
c_func
(paren
id|fd
comma
id|cmd
comma
id|arg
comma
id|filp
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|fput
c_func
(paren
id|filp
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Table to convert sigio signal codes into poll band bitmaps */
DECL|variable|band_table
r_static
r_int
id|band_table
(braket
id|NSIGPOLL
)braket
op_assign
(brace
id|POLLIN
op_or
id|POLLRDNORM
comma
multiline_comment|/* POLL_IN */
id|POLLOUT
op_or
id|POLLWRNORM
op_or
id|POLLWRBAND
comma
multiline_comment|/* POLL_OUT */
id|POLLIN
op_or
id|POLLRDNORM
op_or
id|POLLMSG
comma
multiline_comment|/* POLL_MSG */
id|POLLERR
comma
multiline_comment|/* POLL_ERR */
id|POLLPRI
op_or
id|POLLRDBAND
comma
multiline_comment|/* POLL_PRI */
id|POLLHUP
op_or
id|POLLERR
multiline_comment|/* POLL_HUP */
)brace
suffix:semicolon
DECL|function|send_sigio_to_task
r_static
r_void
id|send_sigio_to_task
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|fown_struct
op_star
id|fown
comma
r_int
id|fd
comma
r_int
id|reason
)paren
(brace
r_if
c_cond
(paren
(paren
id|fown-&gt;euid
op_ne
l_int|0
)paren
op_logical_and
(paren
id|fown-&gt;euid
op_xor
id|p-&gt;suid
)paren
op_logical_and
(paren
id|fown-&gt;euid
op_xor
id|p-&gt;uid
)paren
op_logical_and
(paren
id|fown-&gt;uid
op_xor
id|p-&gt;suid
)paren
op_logical_and
(paren
id|fown-&gt;uid
op_xor
id|p-&gt;uid
)paren
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|fown-&gt;signum
)paren
(brace
id|siginfo_t
id|si
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Queue a rt signal with the appropriate fd as its&n;&t;&t;&t;   value.  We use SI_SIGIO as the source, not &n;&t;&t;&t;   SI_KERNEL, since kernel signals always get &n;&t;&t;&t;   delivered even if we can&squot;t queue.  Failure to&n;&t;&t;&t;   queue in this case _should_ be reported; we fall&n;&t;&t;&t;   back to SIGIO in that case. --sct */
id|si.si_signo
op_assign
id|fown-&gt;signum
suffix:semicolon
id|si.si_errno
op_assign
l_int|0
suffix:semicolon
id|si.si_code
op_assign
id|reason
op_amp
op_complement
id|__SI_MASK
suffix:semicolon
multiline_comment|/* Make sure we are called with one of the POLL_*&n;&t;&t;&t;   reasons, otherwise we could leak kernel stack into&n;&t;&t;&t;   userspace.  */
r_if
c_cond
(paren
(paren
id|reason
op_amp
id|__SI_MASK
)paren
op_ne
id|__SI_POLL
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reason
op_minus
id|POLL_IN
op_ge
id|NSIGPOLL
)paren
id|si.si_band
op_assign
op_complement
l_int|0L
suffix:semicolon
r_else
id|si.si_band
op_assign
id|band_table
(braket
id|reason
op_minus
id|POLL_IN
)braket
suffix:semicolon
id|si.si_fd
op_assign
id|fd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|send_sig_info
c_func
(paren
id|fown-&gt;signum
comma
op_amp
id|si
comma
id|p
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* fall-through: fall back on the old plain SIGIO signal */
r_case
l_int|0
suffix:colon
id|send_sig
c_func
(paren
id|SIGIO
comma
id|p
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|send_sigio
r_void
id|send_sigio
c_func
(paren
r_struct
id|fown_struct
op_star
id|fown
comma
r_int
id|fd
comma
r_int
id|band
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|pid
op_assign
id|fown-&gt;pid
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pid
OG
l_int|0
)paren
op_logical_and
(paren
id|p
op_assign
id|find_task_by_pid
c_func
(paren
id|pid
)paren
)paren
)paren
(brace
id|send_sigio_to_task
c_func
(paren
id|p
comma
id|fown
comma
id|fd
comma
id|band
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_int
id|match
op_assign
id|p-&gt;pid
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
id|match
op_assign
op_minus
id|p-&gt;pgrp
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_ne
id|match
)paren
r_continue
suffix:semicolon
id|send_sigio_to_task
c_func
(paren
id|p
comma
id|fown
comma
id|fd
comma
id|band
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
)brace
DECL|variable|fasync_lock
r_static
id|rwlock_t
id|fasync_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|fasync_cache
r_static
id|kmem_cache_t
op_star
id|fasync_cache
suffix:semicolon
multiline_comment|/*&n; * fasync_helper() is used by some character device drivers (mainly mice)&n; * to set up the fasync queue. It returns negative on error, 0 if it did&n; * no changes and positive if it added/deleted the entry.&n; */
DECL|function|fasync_helper
r_int
id|fasync_helper
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|filp
comma
r_int
id|on
comma
r_struct
id|fasync_struct
op_star
op_star
id|fapp
)paren
(brace
r_struct
id|fasync_struct
op_star
id|fa
comma
op_star
op_star
id|fp
suffix:semicolon
r_struct
id|fasync_struct
op_star
r_new
op_assign
l_int|NULL
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
(brace
r_new
op_assign
id|kmem_cache_alloc
c_func
(paren
id|fasync_cache
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|write_lock_irq
c_func
(paren
op_amp
id|fasync_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|fp
op_assign
id|fapp
suffix:semicolon
(paren
id|fa
op_assign
op_star
id|fp
)paren
op_ne
l_int|NULL
suffix:semicolon
id|fp
op_assign
op_amp
id|fa-&gt;fa_next
)paren
(brace
r_if
c_cond
(paren
id|fa-&gt;fa_file
op_eq
id|filp
)paren
(brace
r_if
c_cond
(paren
id|on
)paren
(brace
id|fa-&gt;fa_fd
op_assign
id|fd
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|fasync_cache
comma
r_new
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|fp
op_assign
id|fa-&gt;fa_next
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|fasync_cache
comma
id|fa
)paren
suffix:semicolon
id|result
op_assign
l_int|1
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|on
)paren
(brace
r_new
op_member_access_from_pointer
id|magic
op_assign
id|FASYNC_MAGIC
suffix:semicolon
r_new
op_member_access_from_pointer
id|fa_file
op_assign
id|filp
suffix:semicolon
r_new
op_member_access_from_pointer
id|fa_fd
op_assign
id|fd
suffix:semicolon
r_new
op_member_access_from_pointer
id|fa_next
op_assign
op_star
id|fapp
suffix:semicolon
op_star
id|fapp
op_assign
r_new
suffix:semicolon
id|result
op_assign
l_int|1
suffix:semicolon
)brace
id|out
suffix:colon
id|write_unlock_irq
c_func
(paren
op_amp
id|fasync_lock
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|__kill_fasync
r_void
id|__kill_fasync
c_func
(paren
r_struct
id|fasync_struct
op_star
id|fa
comma
r_int
id|sig
comma
r_int
id|band
)paren
(brace
r_while
c_loop
(paren
id|fa
)paren
(brace
r_struct
id|fown_struct
op_star
id|fown
suffix:semicolon
r_if
c_cond
(paren
id|fa-&gt;magic
op_ne
id|FASYNC_MAGIC
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;kill_fasync: bad magic number in &quot;
l_string|&quot;fasync_struct!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fown
op_assign
op_amp
id|fa-&gt;fa_file-&gt;f_owner
suffix:semicolon
multiline_comment|/* Don&squot;t send SIGURG to processes which have not set a&n;&t;&t;   queued signum: SIGURG has its own default signalling&n;&t;&t;   mechanism. */
r_if
c_cond
(paren
id|fown-&gt;pid
op_logical_and
op_logical_neg
(paren
id|sig
op_eq
id|SIGURG
op_logical_and
id|fown-&gt;signum
op_eq
l_int|0
)paren
)paren
id|send_sigio
c_func
(paren
id|fown
comma
id|fa-&gt;fa_fd
comma
id|band
)paren
suffix:semicolon
id|fa
op_assign
id|fa-&gt;fa_next
suffix:semicolon
)brace
)brace
DECL|function|kill_fasync
r_void
id|kill_fasync
c_func
(paren
r_struct
id|fasync_struct
op_star
op_star
id|fp
comma
r_int
id|sig
comma
r_int
id|band
)paren
(brace
id|read_lock
c_func
(paren
op_amp
id|fasync_lock
)paren
suffix:semicolon
id|__kill_fasync
c_func
(paren
op_star
id|fp
comma
id|sig
comma
id|band
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|fasync_lock
)paren
suffix:semicolon
)brace
DECL|function|fasync_init
r_static
r_int
id|__init
id|fasync_init
c_func
(paren
r_void
)paren
(brace
id|fasync_cache
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;fasync cache&quot;
comma
r_sizeof
(paren
r_struct
id|fasync_struct
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fasync_cache
)paren
id|panic
c_func
(paren
l_string|&quot;cannot create fasync slab cache&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|fasync_init
)paren
eof
