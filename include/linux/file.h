multiline_comment|/*&n; * Wrapper functions for accessing the file_struct fd array.&n; */
macro_line|#ifndef __LINUX_FILE_H
DECL|macro|__LINUX_FILE_H
mdefine_line|#define __LINUX_FILE_H
r_extern
r_void
id|FASTCALL
c_func
(paren
id|fput
c_func
(paren
r_struct
id|file
op_star
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|file
op_star
id|FASTCALL
c_func
(paren
id|fget
c_func
(paren
r_int
r_int
id|fd
)paren
)paren
suffix:semicolon
DECL|function|get_close_on_exec
r_static
r_inline
r_int
id|get_close_on_exec
c_func
(paren
r_int
r_int
id|fd
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
id|res
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
id|res
op_assign
id|FD_ISSET
c_func
(paren
id|fd
comma
id|files-&gt;close_on_exec
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|set_close_on_exec
r_static
r_inline
r_void
id|set_close_on_exec
c_func
(paren
r_int
r_int
id|fd
comma
r_int
id|flag
)paren
(brace
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
id|flag
)paren
id|FD_SET
c_func
(paren
id|fd
comma
id|files-&gt;close_on_exec
)paren
suffix:semicolon
r_else
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
)brace
DECL|function|fcheck_files
r_static
r_inline
r_struct
id|file
op_star
id|fcheck_files
c_func
(paren
r_struct
id|files_struct
op_star
id|files
comma
r_int
r_int
id|fd
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
id|files-&gt;max_fds
)paren
id|file
op_assign
id|files-&gt;fd
(braket
id|fd
)braket
suffix:semicolon
r_return
id|file
suffix:semicolon
)brace
multiline_comment|/*&n; * Check whether the specified fd has an open file.&n; */
DECL|function|fcheck
r_static
r_inline
r_struct
id|file
op_star
id|fcheck
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
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|files_struct
op_star
id|files
op_assign
id|current-&gt;files
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
id|files-&gt;max_fds
)paren
id|file
op_assign
id|files-&gt;fd
(braket
id|fd
)braket
suffix:semicolon
r_return
id|file
suffix:semicolon
)brace
r_extern
r_void
id|put_filp
c_func
(paren
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|get_unused_fd
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|__put_unused_fd
r_static
r_inline
r_void
id|__put_unused_fd
c_func
(paren
r_struct
id|files_struct
op_star
id|files
comma
r_int
r_int
id|fd
)paren
(brace
id|FD_CLR
c_func
(paren
id|fd
comma
id|files-&gt;open_fds
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
id|files-&gt;next_fd
)paren
id|files-&gt;next_fd
op_assign
id|fd
suffix:semicolon
)brace
DECL|function|put_unused_fd
r_static
r_inline
r_void
id|put_unused_fd
c_func
(paren
r_int
r_int
id|fd
)paren
(brace
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
id|__put_unused_fd
c_func
(paren
id|files
comma
id|fd
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Install a file pointer in the fd array.  &n; *&n; * The VFS is full of places where we drop the files lock between&n; * setting the open_fds bitmap and installing the file in the file&n; * array.  At any such point, we are vulnerable to a dup2() race&n; * installing a file in the array before us.  We need to detect this and&n; * fput() the struct file we are about to overwrite in this case.&n; *&n; * It should never happen - if we allow dup2() do it, _really_ bad things&n; * will follow.&n; */
DECL|function|fd_install
r_static
r_inline
r_void
id|fd_install
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|file
op_star
id|file
)paren
(brace
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
id|files-&gt;fd
(braket
id|fd
)braket
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|files-&gt;fd
(braket
id|fd
)braket
op_assign
id|file
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
)brace
r_void
id|put_files_struct
c_func
(paren
r_struct
id|files_struct
op_star
id|fs
)paren
suffix:semicolon
macro_line|#endif /* __LINUX_FILE_H */
eof
