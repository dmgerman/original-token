multiline_comment|/*&n; *  linux/fs/proc/link.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  /proc link-file handling code&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
r_static
r_int
id|proc_readlink
c_func
(paren
r_struct
id|dentry
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_struct
id|dentry
op_star
id|proc_follow_link
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * links can&squot;t do much...&n; */
DECL|variable|proc_fd_link_operations
r_static
r_struct
id|file_operations
id|proc_fd_link_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
l_int|NULL
comma
multiline_comment|/* read - bad */
l_int|NULL
comma
multiline_comment|/* write - bad */
l_int|NULL
comma
multiline_comment|/* readdir - bad */
l_int|NULL
comma
multiline_comment|/* poll - default */
l_int|NULL
comma
multiline_comment|/* ioctl - default */
l_int|NULL
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* very special open code */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* can&squot;t fsync */
)brace
suffix:semicolon
DECL|variable|proc_link_inode_operations
r_struct
id|inode_operations
id|proc_link_inode_operations
op_assign
(brace
op_amp
id|proc_fd_link_operations
comma
multiline_comment|/* file-operations */
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
id|proc_readlink
comma
multiline_comment|/* readlink */
id|proc_follow_link
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
id|proc_permission
multiline_comment|/* permission */
)brace
suffix:semicolon
DECL|function|proc_follow_link
r_static
r_struct
id|dentry
op_star
id|proc_follow_link
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
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_struct
id|dentry
op_star
id|result
suffix:semicolon
r_int
id|ino
comma
id|pid
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/* We don&squot;t need a base pointer in the /proc filesystem */
id|dput
c_func
(paren
id|base
)paren
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
id|result
op_assign
id|ERR_PTR
c_func
(paren
id|error
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
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|pid
op_assign
id|ino
op_rshift
l_int|16
suffix:semicolon
id|ino
op_and_assign
l_int|0x0000ffff
suffix:semicolon
id|result
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENOENT
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|p
op_assign
id|find_task_by_pid
c_func
(paren
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|out_unlock
suffix:semicolon
r_switch
c_cond
(paren
id|ino
)paren
(brace
r_case
id|PROC_PID_CWD
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;fs
op_logical_or
op_logical_neg
id|p-&gt;fs-&gt;pwd
)paren
r_goto
id|out_unlock
suffix:semicolon
id|result
op_assign
id|p-&gt;fs-&gt;pwd
suffix:semicolon
r_goto
id|out_dget
suffix:semicolon
r_case
id|PROC_PID_ROOT
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;fs
op_logical_or
op_logical_neg
id|p-&gt;fs-&gt;root
)paren
r_goto
id|out_unlock
suffix:semicolon
id|result
op_assign
id|p-&gt;fs-&gt;root
suffix:semicolon
r_goto
id|out_dget
suffix:semicolon
r_case
id|PROC_PID_EXE
suffix:colon
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;mm
)paren
r_goto
id|out_unlock
suffix:semicolon
id|vma
op_assign
id|p-&gt;mm-&gt;mmap
suffix:semicolon
r_while
c_loop
(paren
id|vma
)paren
(brace
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXECUTABLE
)paren
op_logical_and
id|vma-&gt;vm_file
)paren
(brace
id|result
op_assign
id|vma-&gt;vm_file-&gt;f_dentry
suffix:semicolon
r_goto
id|out_dget
suffix:semicolon
)brace
id|vma
op_assign
id|vma-&gt;vm_next
suffix:semicolon
)brace
r_goto
id|out_unlock
suffix:semicolon
)brace
r_default
suffix:colon
(brace
)brace
r_switch
c_cond
(paren
id|ino
op_rshift
l_int|8
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_case
id|PROC_PID_FD_DIR
suffix:colon
id|ino
op_and_assign
l_int|0xff
suffix:semicolon
id|file
op_assign
id|fcheck_task
c_func
(paren
id|p
comma
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
op_logical_or
op_logical_neg
id|file-&gt;f_dentry
)paren
r_goto
id|out_unlock
suffix:semicolon
id|result
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_goto
id|out_dget
suffix:semicolon
)brace
)brace
id|out_dget
suffix:colon
id|result
op_assign
id|dget
c_func
(paren
id|result
)paren
suffix:semicolon
id|out_unlock
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * This pretty-prints the pathname of a dentry,&n; * clarifying sockets etc.&n; */
DECL|function|do_proc_readlink
r_static
r_int
id|do_proc_readlink
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
id|buflen
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_char
op_star
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
comma
op_star
id|path
comma
op_star
id|pattern
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/* Check for special dentries.. */
id|pattern
op_assign
l_int|NULL
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_logical_and
id|dentry-&gt;d_parent
op_eq
id|dentry
)paren
(brace
r_if
c_cond
(paren
id|S_ISSOCK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|pattern
op_assign
l_string|&quot;socket:[%lu]&quot;
suffix:semicolon
r_if
c_cond
(paren
id|S_ISFIFO
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|pattern
op_assign
l_string|&quot;pipe:[%lu]&quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pattern
)paren
(brace
id|len
op_assign
id|sprintf
c_func
(paren
id|tmp
comma
id|pattern
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|path
op_assign
id|tmp
suffix:semicolon
)brace
r_else
(brace
id|path
op_assign
id|d_path
c_func
(paren
id|dentry
comma
id|tmp
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|len
op_assign
id|tmp
op_plus
id|PAGE_SIZE
op_minus
id|path
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OL
id|buflen
)paren
id|buflen
op_assign
id|len
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|copy_to_user
c_func
(paren
id|buffer
comma
id|path
comma
id|buflen
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|tmp
)paren
suffix:semicolon
r_return
id|buflen
suffix:semicolon
)brace
DECL|function|proc_readlink
r_static
r_int
id|proc_readlink
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
id|buflen
)paren
(brace
r_int
id|error
suffix:semicolon
id|dentry
op_assign
id|proc_follow_link
c_func
(paren
id|dentry
comma
l_int|NULL
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
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|dentry
)paren
(brace
id|error
op_assign
id|do_proc_readlink
c_func
(paren
id|dentry
comma
id|buffer
comma
id|buflen
)paren
suffix:semicolon
)brace
)brace
r_return
id|error
suffix:semicolon
)brace
eof
