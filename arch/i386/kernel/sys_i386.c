multiline_comment|/*&n; * linux/arch/i386/kernel/sys_i386.c&n; *&n; * This file contains various random system calls that&n; * have a non-standard calling sequence on the Linux/i386&n; * platform.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sem.h&gt;
macro_line|#include &lt;linux/msg.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ipc.h&gt;
multiline_comment|/*&n; * sys_pipe() is the normal C calling standard for creating&n; * a pipe. It&squot;s not the way unix traditionally does this, though.&n; */
DECL|function|sys_pipe
id|asmlinkage
r_int
id|sys_pipe
c_func
(paren
r_int
r_int
op_star
id|fildes
)paren
(brace
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|do_pipe
c_func
(paren
id|fd
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
id|copy_to_user
c_func
(paren
id|fildes
comma
id|fd
comma
l_int|2
op_star
r_sizeof
(paren
r_int
)paren
)paren
)paren
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Perform the select(nd, in, out, ex, tv) and mmap() system&n; * calls. Linux/i386 didn&squot;t use to be able to handle more than&n; * 4 system call parameters, so these system calls used a memory&n; * block for parameter passing..&n; */
DECL|struct|mmap_arg_struct
r_struct
id|mmap_arg_struct
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|prot
r_int
r_int
id|prot
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|fd
r_int
r_int
id|fd
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
)brace
suffix:semicolon
DECL|function|old_mmap
id|asmlinkage
r_int
id|old_mmap
c_func
(paren
r_struct
id|mmap_arg_struct
op_star
id|arg
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|mmap_arg_struct
id|a
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|a
comma
id|arg
comma
r_sizeof
(paren
id|a
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|a.flags
op_amp
id|MAP_ANONYMOUS
)paren
)paren
(brace
r_if
c_cond
(paren
id|a.fd
op_ge
id|NR_OPEN
op_logical_or
op_logical_neg
(paren
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|a.fd
)braket
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
id|a.flags
op_and_assign
op_complement
(paren
id|MAP_EXECUTABLE
op_or
id|MAP_DENYWRITE
)paren
suffix:semicolon
id|error
op_assign
id|do_mmap
c_func
(paren
id|file
comma
id|a.addr
comma
id|a.len
comma
id|a.prot
comma
id|a.flags
comma
id|a.offset
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_extern
id|asmlinkage
r_int
id|sys_select
c_func
(paren
r_int
comma
id|fd_set
op_star
comma
id|fd_set
op_star
comma
id|fd_set
op_star
comma
r_struct
id|timeval
op_star
)paren
suffix:semicolon
DECL|struct|sel_arg_struct
r_struct
id|sel_arg_struct
(brace
DECL|member|n
r_int
r_int
id|n
suffix:semicolon
DECL|member|inp
DECL|member|outp
DECL|member|exp
id|fd_set
op_star
id|inp
comma
op_star
id|outp
comma
op_star
id|exp
suffix:semicolon
DECL|member|tvp
r_struct
id|timeval
op_star
id|tvp
suffix:semicolon
)brace
suffix:semicolon
DECL|function|old_select
id|asmlinkage
r_int
id|old_select
c_func
(paren
r_struct
id|sel_arg_struct
op_star
id|arg
)paren
(brace
r_struct
id|sel_arg_struct
id|a
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|a
comma
id|arg
comma
r_sizeof
(paren
id|a
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sys_select
c_func
(paren
id|a.n
comma
id|a.inp
comma
id|a.outp
comma
id|a.exp
comma
id|a.tvp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_ipc() is the de-multiplexer for the SysV IPC calls..&n; *&n; * This is really horribly ugly.&n; */
DECL|function|sys_ipc
id|asmlinkage
r_int
id|sys_ipc
(paren
id|uint
id|call
comma
r_int
id|first
comma
r_int
id|second
comma
r_int
id|third
comma
r_void
op_star
id|ptr
comma
r_int
id|fifth
)paren
(brace
r_int
id|version
suffix:semicolon
id|version
op_assign
id|call
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* hack for backward compatibility */
id|call
op_and_assign
l_int|0xffff
suffix:semicolon
r_if
c_cond
(paren
id|call
op_le
id|SEMCTL
)paren
r_switch
c_cond
(paren
id|call
)paren
(brace
r_case
id|SEMOP
suffix:colon
r_return
id|sys_semop
(paren
id|first
comma
(paren
r_struct
id|sembuf
op_star
)paren
id|ptr
comma
id|second
)paren
suffix:semicolon
r_case
id|SEMGET
suffix:colon
r_return
id|sys_semget
(paren
id|first
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_case
id|SEMCTL
suffix:colon
(brace
r_union
id|semun
id|fourth
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|fourth.__pad
comma
(paren
r_void
op_star
op_star
)paren
id|ptr
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sys_semctl
(paren
id|first
comma
id|second
comma
id|third
comma
id|fourth
)paren
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|call
op_le
id|MSGCTL
)paren
r_switch
c_cond
(paren
id|call
)paren
(brace
r_case
id|MSGSND
suffix:colon
r_return
id|sys_msgsnd
(paren
id|first
comma
(paren
r_struct
id|msgbuf
op_star
)paren
id|ptr
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_case
id|MSGRCV
suffix:colon
r_switch
c_cond
(paren
id|version
)paren
(brace
r_case
l_int|0
suffix:colon
(brace
r_struct
id|ipc_kludge
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|tmp
comma
(paren
r_struct
id|ipc_kludge
op_star
)paren
id|ptr
comma
r_sizeof
(paren
id|tmp
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sys_msgrcv
(paren
id|first
comma
id|tmp.msgp
comma
id|second
comma
id|tmp.msgtyp
comma
id|third
)paren
suffix:semicolon
)brace
r_case
l_int|1
suffix:colon
r_default
suffix:colon
r_return
id|sys_msgrcv
(paren
id|first
comma
(paren
r_struct
id|msgbuf
op_star
)paren
id|ptr
comma
id|second
comma
id|fifth
comma
id|third
)paren
suffix:semicolon
)brace
r_case
id|MSGGET
suffix:colon
r_return
id|sys_msgget
(paren
(paren
id|key_t
)paren
id|first
comma
id|second
)paren
suffix:semicolon
r_case
id|MSGCTL
suffix:colon
r_return
id|sys_msgctl
(paren
id|first
comma
id|second
comma
(paren
r_struct
id|msqid_ds
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|call
op_le
id|SHMCTL
)paren
r_switch
c_cond
(paren
id|call
)paren
(brace
r_case
id|SHMAT
suffix:colon
r_switch
c_cond
(paren
id|version
)paren
(brace
r_case
l_int|0
suffix:colon
r_default
suffix:colon
(brace
)brace
(brace
id|ulong
id|raddr
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|sys_shmat
(paren
id|first
comma
(paren
r_char
op_star
)paren
id|ptr
comma
id|second
comma
op_amp
id|raddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_return
id|put_user
(paren
id|raddr
comma
(paren
id|ulong
op_star
)paren
id|third
)paren
suffix:semicolon
)brace
r_case
l_int|1
suffix:colon
multiline_comment|/* iBCS2 emulator entry point */
r_if
c_cond
(paren
id|get_fs
c_func
(paren
)paren
op_ne
id|get_ds
c_func
(paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|sys_shmat
(paren
id|first
comma
(paren
r_char
op_star
)paren
id|ptr
comma
id|second
comma
(paren
id|ulong
op_star
)paren
id|third
)paren
suffix:semicolon
)brace
r_case
id|SHMDT
suffix:colon
r_return
id|sys_shmdt
(paren
(paren
r_char
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_case
id|SHMGET
suffix:colon
r_return
id|sys_shmget
(paren
id|first
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_case
id|SHMCTL
suffix:colon
r_return
id|sys_shmctl
(paren
id|first
comma
id|second
comma
(paren
r_struct
id|shmid_ds
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
