multiline_comment|/*&n; * linux/arch/i386/kernel/sys_i386.c&n; *&n; * This file contains various random system calls that&n; * have a non-standard calling sequence on the Linux/i386&n; * platform.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sem.h&gt;
macro_line|#include &lt;linux/msg.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
multiline_comment|/*&n; * Perform the select(nd, in, out, ex, tv) system call.&n; * Linux/i386 didn&squot;t use to be able to handle 5 system call&n; * parameters, so the old select used a memory block for&n; * parameter passing..&n; */
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
DECL|function|old_select
id|asmlinkage
r_int
id|old_select
c_func
(paren
r_int
r_int
op_star
id|buffer
)paren
(brace
r_int
id|n
suffix:semicolon
id|fd_set
op_star
id|inp
suffix:semicolon
id|fd_set
op_star
id|outp
suffix:semicolon
id|fd_set
op_star
id|exp
suffix:semicolon
r_struct
id|timeval
op_star
id|tvp
suffix:semicolon
id|n
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|buffer
comma
l_int|5
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
)paren
r_return
id|n
suffix:semicolon
id|n
op_assign
id|get_user
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|inp
op_assign
(paren
id|fd_set
op_star
)paren
id|get_user
c_func
(paren
id|buffer
op_plus
l_int|1
)paren
suffix:semicolon
id|outp
op_assign
(paren
id|fd_set
op_star
)paren
id|get_user
c_func
(paren
id|buffer
op_plus
l_int|2
)paren
suffix:semicolon
id|exp
op_assign
(paren
id|fd_set
op_star
)paren
id|get_user
c_func
(paren
id|buffer
op_plus
l_int|3
)paren
suffix:semicolon
id|tvp
op_assign
(paren
r_struct
id|timeval
op_star
)paren
id|get_user
c_func
(paren
id|buffer
op_plus
l_int|4
)paren
suffix:semicolon
r_return
id|sys_select
c_func
(paren
id|n
comma
id|inp
comma
id|outp
comma
id|exp
comma
id|tvp
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
r_int
id|err
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
(paren
id|err
op_assign
id|verify_area
(paren
id|VERIFY_READ
comma
id|ptr
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|fourth.__pad
op_assign
(paren
r_void
op_star
)paren
id|get_fs_long
c_func
(paren
id|ptr
)paren
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
r_int
id|err
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
(paren
id|err
op_assign
id|verify_area
(paren
id|VERIFY_READ
comma
id|ptr
comma
r_sizeof
(paren
id|tmp
)paren
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|memcpy_fromfs
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
r_if
c_cond
(paren
(paren
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
id|ulong
op_star
)paren
id|third
comma
r_sizeof
(paren
id|ulong
)paren
)paren
)paren
)paren
r_return
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
id|put_fs_long
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
r_return
l_int|0
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
