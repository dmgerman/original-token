multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 - 2000 by Ralf Baechle&n; * Copyright (C) 2000 Silicon Graphics, Inc.&n; *&n; * TODO:  Implement the compatibility syscalls.&n; *        Don&squot;t waste that much memory for empty entries in the syscall&n; *        table.&n; */
DECL|macro|CONF_PRINT_SYSCALLS
macro_line|#undef CONF_PRINT_SYSCALLS
DECL|macro|CONF_DEBUG_IRIX
macro_line|#undef CONF_DEBUG_IRIX
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/branch.h&gt;
macro_line|#include &lt;asm/offset.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &lt;asm/stackframe.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
id|asmlinkage
r_void
id|syscall_trace
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|syscall_t
r_typedef
id|asmlinkage
r_int
(paren
op_star
id|syscall_t
)paren
(paren
r_void
op_star
id|a0
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_int
(paren
op_star
id|do_syscalls
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|syscall_t
id|fun
comma
r_int
id|narg
)paren
suffix:semicolon
r_extern
id|syscall_t
id|sys_call_table
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|sys_narg_table
(braket
)braket
suffix:semicolon
DECL|function|sys_pipe
id|asmlinkage
r_int
id|sys_pipe
c_func
(paren
r_struct
id|pt_regs
id|regs
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
comma
id|res
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
id|error
)paren
(brace
id|res
op_assign
id|error
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|regs.regs
(braket
l_int|3
)braket
op_assign
id|fd
(braket
l_int|1
)braket
suffix:semicolon
id|res
op_assign
id|fd
(braket
l_int|0
)braket
suffix:semicolon
id|out
suffix:colon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* common code for old and new mmaps */
r_static
r_inline
r_int
DECL|function|do_mmap2
id|do_mmap2
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|prot
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|fd
comma
r_int
r_int
id|pgoff
)paren
(brace
r_int
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
id|flags
op_and_assign
op_complement
(paren
id|MAP_EXECUTABLE
op_or
id|MAP_DENYWRITE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MAP_ANONYMOUS
)paren
)paren
(brace
id|file
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
id|file
)paren
r_goto
id|out
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|error
op_assign
id|do_mmap_pgoff
c_func
(paren
id|file
comma
id|addr
comma
id|len
comma
id|prot
comma
id|flags
comma
id|pgoff
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|old_mmap
id|asmlinkage
r_int
r_int
id|old_mmap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|len
comma
r_int
id|prot
comma
r_int
id|flags
comma
r_int
id|fd
comma
id|off_t
id|offset
)paren
(brace
r_return
id|do_mmap2
c_func
(paren
id|addr
comma
id|len
comma
id|prot
comma
id|flags
comma
id|fd
comma
id|offset
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_mmap2
id|sys_mmap2
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|prot
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|fd
comma
r_int
r_int
id|pgoff
)paren
(brace
r_return
id|do_mmap2
c_func
(paren
id|addr
comma
id|len
comma
id|prot
comma
id|flags
comma
id|fd
comma
id|pgoff
)paren
suffix:semicolon
)brace
DECL|function|sys_fork
id|asmlinkage
r_int
id|sys_fork
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_int
id|res
suffix:semicolon
id|save_static
c_func
(paren
op_amp
id|regs
)paren
suffix:semicolon
id|res
op_assign
id|do_fork
c_func
(paren
id|SIGCHLD
comma
id|regs.regs
(braket
l_int|29
)braket
comma
op_amp
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|sys_clone
id|asmlinkage
r_int
id|sys_clone
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_int
r_int
id|clone_flags
suffix:semicolon
r_int
r_int
id|newsp
suffix:semicolon
r_int
id|res
suffix:semicolon
id|save_static
c_func
(paren
op_amp
id|regs
)paren
suffix:semicolon
id|clone_flags
op_assign
id|regs.regs
(braket
l_int|4
)braket
suffix:semicolon
id|newsp
op_assign
id|regs.regs
(braket
l_int|5
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newsp
)paren
id|newsp
op_assign
id|regs.regs
(braket
l_int|29
)braket
suffix:semicolon
id|res
op_assign
id|do_fork
c_func
(paren
id|clone_flags
comma
id|newsp
comma
op_amp
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_execve() executes a new program.&n; */
DECL|function|sys_execve
id|asmlinkage
r_int
id|sys_execve
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_int
id|error
suffix:semicolon
r_char
op_star
id|filename
suffix:semicolon
id|filename
op_assign
id|getname
c_func
(paren
(paren
r_char
op_star
)paren
(paren
r_int
)paren
id|regs.regs
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|filename
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|do_execve
c_func
(paren
id|filename
comma
(paren
r_char
op_star
op_star
)paren
(paren
r_int
)paren
id|regs.regs
(braket
l_int|5
)braket
comma
(paren
r_char
op_star
op_star
)paren
(paren
r_int
)paren
id|regs.regs
(braket
l_int|6
)braket
comma
op_amp
id|regs
)paren
suffix:semicolon
id|putname
c_func
(paren
id|filename
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Compacrapability ...&n; */
DECL|function|sys_uname
id|asmlinkage
r_int
id|sys_uname
c_func
(paren
r_struct
id|old_utsname
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
id|name
op_logical_and
op_logical_neg
id|copy_to_user
c_func
(paren
id|name
comma
op_amp
id|system_utsname
comma
r_sizeof
(paren
op_star
id|name
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/*&n; * Compacrapability ...&n; */
DECL|function|sys_olduname
id|asmlinkage
r_int
id|sys_olduname
c_func
(paren
r_struct
id|oldold_utsname
op_star
id|name
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|name
comma
r_sizeof
(paren
r_struct
id|oldold_utsname
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|error
op_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;sysname
comma
op_amp
id|system_utsname.sysname
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;sysname
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;nodename
comma
op_amp
id|system_utsname.nodename
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;nodename
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;release
comma
op_amp
id|system_utsname.release
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;release
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;version
comma
op_amp
id|system_utsname.version
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;version
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;machine
comma
op_amp
id|system_utsname.machine
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;machine
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_assign
id|error
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Do the indirect syscall syscall.&n; * Don&squot;t care about kernel locking; the actual syscall will do it.&n; *&n; * XXX This is borken.&n; */
DECL|function|sys_syscall
id|asmlinkage
r_int
id|sys_syscall
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
id|syscall_t
id|syscall
suffix:semicolon
r_int
r_int
id|syscallnr
op_assign
id|regs.regs
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_int
id|a0
comma
id|a1
comma
id|a2
comma
id|a3
comma
id|a4
comma
id|a5
comma
id|a6
suffix:semicolon
r_int
id|nargs
comma
id|errno
suffix:semicolon
r_if
c_cond
(paren
id|syscallnr
OG
id|__NR_Linux
op_plus
id|__NR_Linux_syscalls
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
id|syscall
op_assign
id|sys_call_table
(braket
id|syscallnr
)braket
suffix:semicolon
id|nargs
op_assign
id|sys_narg_table
(braket
id|syscallnr
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Prevent stack overflow by recursive&n;&t; * syscall(__NR_syscall, __NR_syscall,...);&n;&t; */
r_if
c_cond
(paren
id|syscall
op_eq
(paren
id|syscall_t
)paren
id|sys_syscall
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|syscall
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nargs
OG
l_int|3
)paren
(brace
r_int
r_int
id|usp
op_assign
id|regs.regs
(braket
l_int|29
)braket
suffix:semicolon
r_int
r_int
op_star
id|sp
op_assign
(paren
r_int
r_int
op_star
)paren
id|usp
suffix:semicolon
r_if
c_cond
(paren
id|usp
op_amp
l_int|3
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unaligned usp -EFAULT&bslash;n&quot;
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|errno
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
(paren
id|usp
op_plus
l_int|16
)paren
comma
(paren
id|nargs
op_minus
l_int|3
)paren
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
id|errno
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|nargs
)paren
(brace
r_case
l_int|7
suffix:colon
id|a3
op_assign
id|sp
(braket
l_int|4
)braket
suffix:semicolon
id|a4
op_assign
id|sp
(braket
l_int|5
)braket
suffix:semicolon
id|a5
op_assign
id|sp
(braket
l_int|6
)braket
suffix:semicolon
id|a6
op_assign
id|sp
(braket
l_int|7
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|a3
op_assign
id|sp
(braket
l_int|4
)braket
suffix:semicolon
id|a4
op_assign
id|sp
(braket
l_int|5
)braket
suffix:semicolon
id|a5
op_assign
id|sp
(braket
l_int|6
)braket
suffix:semicolon
id|a6
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|a3
op_assign
id|sp
(braket
l_int|4
)braket
suffix:semicolon
id|a4
op_assign
id|sp
(braket
l_int|5
)braket
suffix:semicolon
id|a5
op_assign
id|a6
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|a3
op_assign
id|sp
(braket
l_int|4
)braket
suffix:semicolon
id|a4
op_assign
id|a5
op_assign
id|a6
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|a3
op_assign
id|a4
op_assign
id|a5
op_assign
id|a6
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|a3
op_assign
id|a4
op_assign
id|a5
op_assign
id|a6
op_assign
l_int|0
suffix:semicolon
)brace
id|a0
op_assign
id|regs.regs
(braket
l_int|5
)braket
suffix:semicolon
id|a1
op_assign
id|regs.regs
(braket
l_int|6
)braket
suffix:semicolon
id|a2
op_assign
id|regs.regs
(braket
l_int|7
)braket
suffix:semicolon
r_if
c_cond
(paren
id|nargs
op_eq
l_int|0
)paren
(brace
id|a0
op_assign
(paren
r_int
r_int
)paren
op_amp
id|regs
suffix:semicolon
)brace
r_return
id|syscall
c_func
(paren
(paren
r_void
op_star
)paren
id|a0
comma
id|a1
comma
id|a2
comma
id|a3
comma
id|a4
comma
id|a5
comma
id|a6
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If we ever come here the user sp is bad.  Zap the process right away.&n; * Due to the bad stack signaling wouldn&squot;t work.&n; * XXX kernel locking???&n; */
DECL|function|bad_stack
id|asmlinkage
r_void
id|bad_stack
c_func
(paren
r_void
)paren
(brace
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Build the string table for the builtin &quot;poor man&squot;s strace&quot;.&n; */
macro_line|#ifdef CONF_PRINT_SYSCALLS
DECL|macro|SYS
mdefine_line|#define SYS(fun, narg) #fun,
DECL|variable|sfnames
r_static
r_char
op_star
id|sfnames
(braket
)braket
op_assign
(brace
macro_line|#include &quot;syscalls.h&quot;
)brace
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_BINFMT_IRIX) &amp;&amp; defined(CONF_DEBUG_IRIX)
DECL|macro|SYS
mdefine_line|#define SYS(fun, narg) #fun,
DECL|variable|irix_sys_names
r_static
r_char
op_star
id|irix_sys_names
(braket
)braket
op_assign
(brace
macro_line|#include &quot;irix5sys.h&quot;
)brace
suffix:semicolon
macro_line|#endif
eof
