multiline_comment|/*&n; *  linux/fs/binfmt_aout.c&n; *&n; *  Copyright (C) 1991, 1992, 1996  Linus Torvalds&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
r_static
r_int
id|load_aout_binary
c_func
(paren
r_struct
id|linux_binprm
op_star
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_int
id|load_aout_library
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
r_static
r_int
id|aout_core_dump
c_func
(paren
r_int
id|signr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_struct
id|user
op_star
)paren
suffix:semicolon
DECL|variable|aout_format
r_static
r_struct
id|linux_binfmt
id|aout_format
op_assign
(brace
macro_line|#ifndef MODULE
l_int|NULL
comma
l_int|NULL
comma
id|load_aout_binary
comma
id|load_aout_library
comma
id|aout_core_dump
macro_line|#else
l_int|NULL
comma
op_amp
id|__this_module
comma
id|load_aout_binary
comma
id|load_aout_library
comma
id|aout_core_dump
macro_line|#endif
)brace
suffix:semicolon
DECL|function|set_brk
r_static
r_void
id|set_brk
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
id|start
op_assign
id|PAGE_ALIGN
c_func
(paren
id|start
)paren
suffix:semicolon
id|end
op_assign
id|PAGE_ALIGN
c_func
(paren
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
op_le
id|start
)paren
r_return
suffix:semicolon
id|do_mmap
c_func
(paren
l_int|NULL
comma
id|start
comma
id|end
op_minus
id|start
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the only things you should do on a core-file: use only these&n; * macros to write out all the necessary info.&n; */
DECL|macro|DUMP_WRITE
mdefine_line|#define DUMP_WRITE(addr,nr) &bslash;&n;while (file.f_op-&gt;write(&amp;file,(char *)(addr),(nr),&amp;file.f_pos) != (nr)) goto close_coredump
DECL|macro|DUMP_SEEK
mdefine_line|#define DUMP_SEEK(offset) &bslash;&n;if (file.f_op-&gt;llseek) { &bslash;&n;&t;if (file.f_op-&gt;llseek(&amp;file,(offset),0) != (offset)) &bslash;&n; &t;&t;goto close_coredump; &bslash;&n;} else file.f_pos = (offset)
multiline_comment|/*&n; * Routine writes a core dump image in the current directory.&n; * Currently only a stub-function.&n; *&n; * Note that setuid/setgid files won&squot;t make a core-dump if the uid/gid&n; * changed due to the set[u|g]id. It&squot;s enforced by the &quot;current-&gt;dumpable&quot;&n; * field, which also makes sure the core-dumps won&squot;t be recursive if the&n; * dumping of the process results in another error..&n; */
r_static
r_inline
r_int
DECL|function|do_aout_core_dump
id|do_aout_core_dump
c_func
(paren
r_int
id|signr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|file
id|file
suffix:semicolon
id|mm_segment_t
id|fs
suffix:semicolon
r_int
id|has_dumped
op_assign
l_int|0
suffix:semicolon
r_char
id|corefile
(braket
l_int|6
op_plus
r_sizeof
(paren
id|current-&gt;comm
)paren
)braket
suffix:semicolon
r_int
r_int
id|dump_start
comma
id|dump_size
suffix:semicolon
r_struct
id|user
id|dump
suffix:semicolon
macro_line|#if defined(__alpha__)
DECL|macro|START_DATA
macro_line|#       define START_DATA(u)&t;(u.start_data)
macro_line|#elif defined(__sparc__)
macro_line|#       define START_DATA(u)    (u.u_tsize)
macro_line|#elif defined(__i386__) || defined(__mc68000__)
macro_line|#       define START_DATA(u)&t;(u.u_tsize &lt;&lt; PAGE_SHIFT)
macro_line|#endif
macro_line|#ifdef __sparc__
DECL|macro|START_STACK
macro_line|#       define START_STACK(u)   ((regs-&gt;u_regs[UREG_FP]) &amp; ~(PAGE_SIZE - 1))
macro_line|#else
macro_line|#       define START_STACK(u)   (u.start_stack)
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;dumpable
op_logical_or
id|current-&gt;mm-&gt;count
op_ne
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|current-&gt;dumpable
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* See if we have enough room to write the upage.  */
r_if
c_cond
(paren
id|current-&gt;rlim
(braket
id|RLIMIT_CORE
)braket
dot
id|rlim_cur
OL
id|PAGE_SIZE
)paren
r_return
l_int|0
suffix:semicolon
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|corefile
comma
l_string|&quot;core.&quot;
comma
l_int|5
)paren
suffix:semicolon
macro_line|#if 0
id|memcpy
c_func
(paren
id|corefile
op_plus
l_int|5
comma
id|current-&gt;comm
comma
r_sizeof
(paren
id|current-&gt;comm
)paren
)paren
suffix:semicolon
macro_line|#else
id|corefile
(braket
l_int|4
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
macro_line|#endif
id|dentry
op_assign
id|open_namei
c_func
(paren
id|corefile
comma
id|O_CREAT
op_or
l_int|2
op_or
id|O_TRUNC
comma
l_int|0600
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
(brace
id|dentry
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|end_coredump
suffix:semicolon
)brace
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_goto
id|end_coredump
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_op
op_logical_or
op_logical_neg
id|inode-&gt;i_op-&gt;default_file_ops
)paren
r_goto
id|end_coredump
suffix:semicolon
r_if
c_cond
(paren
id|get_write_access
c_func
(paren
id|inode
)paren
)paren
r_goto
id|end_coredump
suffix:semicolon
r_if
c_cond
(paren
id|init_private_file
c_func
(paren
op_amp
id|file
comma
id|dentry
comma
l_int|3
)paren
)paren
r_goto
id|end_coredump_write
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file.f_op-&gt;write
)paren
r_goto
id|close_coredump
suffix:semicolon
id|has_dumped
op_assign
l_int|1
suffix:semicolon
id|current-&gt;flags
op_or_assign
id|PF_DUMPCORE
suffix:semicolon
id|strncpy
c_func
(paren
id|dump.u_comm
comma
id|current-&gt;comm
comma
r_sizeof
(paren
id|current-&gt;comm
)paren
)paren
suffix:semicolon
macro_line|#ifndef __sparc__
id|dump.u_ar0
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|dump.regs
)paren
)paren
op_minus
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|dump
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
id|dump.signal
op_assign
id|signr
suffix:semicolon
id|dump_thread
c_func
(paren
id|regs
comma
op_amp
id|dump
)paren
suffix:semicolon
multiline_comment|/* If the size of the dump file exceeds the rlimit, then see what would happen&n;   if we wrote the stack, but not the data area.  */
macro_line|#ifdef __sparc__
r_if
c_cond
(paren
(paren
id|dump.u_dsize
op_plus
id|dump.u_ssize
)paren
OG
id|current-&gt;rlim
(braket
id|RLIMIT_CORE
)braket
dot
id|rlim_cur
)paren
id|dump.u_dsize
op_assign
l_int|0
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
(paren
id|dump.u_dsize
op_plus
id|dump.u_ssize
op_plus
l_int|1
)paren
op_star
id|PAGE_SIZE
OG
id|current-&gt;rlim
(braket
id|RLIMIT_CORE
)braket
dot
id|rlim_cur
)paren
id|dump.u_dsize
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* Make sure we have enough room to write the stack and data areas. */
macro_line|#ifdef __sparc__
r_if
c_cond
(paren
(paren
id|dump.u_ssize
)paren
OG
id|current-&gt;rlim
(braket
id|RLIMIT_CORE
)braket
dot
id|rlim_cur
)paren
id|dump.u_ssize
op_assign
l_int|0
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
(paren
id|dump.u_ssize
op_plus
l_int|1
)paren
op_star
id|PAGE_SIZE
OG
id|current-&gt;rlim
(braket
id|RLIMIT_CORE
)braket
dot
id|rlim_cur
)paren
id|dump.u_ssize
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* make sure we actually have a data and stack area to dump */
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
macro_line|#ifdef __sparc__
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|START_DATA
c_func
(paren
id|dump
)paren
comma
id|dump.u_dsize
)paren
)paren
id|dump.u_dsize
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|START_STACK
c_func
(paren
id|dump
)paren
comma
id|dump.u_ssize
)paren
)paren
id|dump.u_ssize
op_assign
l_int|0
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|START_DATA
c_func
(paren
id|dump
)paren
comma
id|dump.u_dsize
op_lshift
id|PAGE_SHIFT
)paren
)paren
id|dump.u_dsize
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|START_STACK
c_func
(paren
id|dump
)paren
comma
id|dump.u_ssize
op_lshift
id|PAGE_SHIFT
)paren
)paren
id|dump.u_ssize
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
multiline_comment|/* struct user */
id|DUMP_WRITE
c_func
(paren
op_amp
id|dump
comma
r_sizeof
(paren
id|dump
)paren
)paren
suffix:semicolon
multiline_comment|/* Now dump all of the user data.  Include malloced stuff as well */
macro_line|#ifndef __sparc__
id|DUMP_SEEK
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* now we start writing out the user space info */
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
multiline_comment|/* Dump the data area */
r_if
c_cond
(paren
id|dump.u_dsize
op_ne
l_int|0
)paren
(brace
id|dump_start
op_assign
id|START_DATA
c_func
(paren
id|dump
)paren
suffix:semicolon
macro_line|#ifdef __sparc__
id|dump_size
op_assign
id|dump.u_dsize
suffix:semicolon
macro_line|#else
id|dump_size
op_assign
id|dump.u_dsize
op_lshift
id|PAGE_SHIFT
suffix:semicolon
macro_line|#endif
id|DUMP_WRITE
c_func
(paren
id|dump_start
comma
id|dump_size
)paren
suffix:semicolon
)brace
multiline_comment|/* Now prepare to dump the stack area */
r_if
c_cond
(paren
id|dump.u_ssize
op_ne
l_int|0
)paren
(brace
id|dump_start
op_assign
id|START_STACK
c_func
(paren
id|dump
)paren
suffix:semicolon
macro_line|#ifdef __sparc__
id|dump_size
op_assign
id|dump.u_ssize
suffix:semicolon
macro_line|#else
id|dump_size
op_assign
id|dump.u_ssize
op_lshift
id|PAGE_SHIFT
suffix:semicolon
macro_line|#endif
id|DUMP_WRITE
c_func
(paren
id|dump_start
comma
id|dump_size
)paren
suffix:semicolon
)brace
multiline_comment|/* Finally dump the task struct.  Not be used by gdb, but could be useful */
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|DUMP_WRITE
c_func
(paren
id|current
comma
r_sizeof
(paren
op_star
id|current
)paren
)paren
suffix:semicolon
id|close_coredump
suffix:colon
r_if
c_cond
(paren
id|file.f_op-&gt;release
)paren
id|file.f_op
op_member_access_from_pointer
id|release
c_func
(paren
id|inode
comma
op_amp
id|file
)paren
suffix:semicolon
id|end_coredump_write
suffix:colon
id|put_write_access
c_func
(paren
id|inode
)paren
suffix:semicolon
id|end_coredump
suffix:colon
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
id|has_dumped
suffix:semicolon
)brace
r_static
r_int
DECL|function|aout_core_dump
id|aout_core_dump
c_func
(paren
r_int
id|signr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|retval
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|retval
op_assign
id|do_aout_core_dump
c_func
(paren
id|signr
comma
id|regs
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * create_aout_tables() parses the env- and arg-strings in new user&n; * memory and creates the pointer tables from them, and puts their&n; * addresses on the &quot;stack&quot;, returning the new stack pointer value.&n; */
DECL|function|create_aout_tables
r_static
r_int
r_int
op_star
id|create_aout_tables
c_func
(paren
r_char
op_star
id|p
comma
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
r_char
op_star
op_star
id|argv
comma
op_star
op_star
id|envp
suffix:semicolon
r_int
r_int
op_star
id|sp
suffix:semicolon
r_int
id|argc
op_assign
id|bprm-&gt;argc
suffix:semicolon
r_int
id|envc
op_assign
id|bprm-&gt;envc
suffix:semicolon
id|sp
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
(paren
op_minus
(paren
r_int
r_int
)paren
r_sizeof
(paren
r_char
op_star
)paren
)paren
op_amp
(paren
r_int
r_int
)paren
id|p
)paren
suffix:semicolon
macro_line|#ifdef __sparc__
multiline_comment|/* This imposes the proper stack alignment for a new process. */
id|sp
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|sp
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|envc
op_plus
id|argc
op_plus
l_int|3
)paren
op_amp
l_int|1
)paren
op_decrement
id|sp
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __alpha__
multiline_comment|/* whee.. test-programs are so much fun. */
id|put_user
c_func
(paren
l_int|0
comma
op_decrement
id|sp
)paren
suffix:semicolon
id|put_user
c_func
(paren
l_int|0
comma
op_decrement
id|sp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bprm-&gt;loader
)paren
(brace
id|put_user
c_func
(paren
l_int|0
comma
op_decrement
id|sp
)paren
suffix:semicolon
id|put_user
c_func
(paren
l_int|0x3eb
comma
op_decrement
id|sp
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|bprm-&gt;loader
comma
op_decrement
id|sp
)paren
suffix:semicolon
id|put_user
c_func
(paren
l_int|0x3ea
comma
op_decrement
id|sp
)paren
suffix:semicolon
)brace
id|put_user
c_func
(paren
id|bprm-&gt;exec
comma
op_decrement
id|sp
)paren
suffix:semicolon
id|put_user
c_func
(paren
l_int|0x3e9
comma
op_decrement
id|sp
)paren
suffix:semicolon
macro_line|#endif
id|sp
op_sub_assign
id|envc
op_plus
l_int|1
suffix:semicolon
id|envp
op_assign
(paren
r_char
op_star
op_star
)paren
id|sp
suffix:semicolon
id|sp
op_sub_assign
id|argc
op_plus
l_int|1
suffix:semicolon
id|argv
op_assign
(paren
r_char
op_star
op_star
)paren
id|sp
suffix:semicolon
macro_line|#if defined(__i386__) || defined(__mc68000__)
id|put_user
c_func
(paren
(paren
r_int
r_int
)paren
id|envp
comma
op_decrement
id|sp
)paren
suffix:semicolon
id|put_user
c_func
(paren
(paren
r_int
r_int
)paren
id|argv
comma
op_decrement
id|sp
)paren
suffix:semicolon
macro_line|#endif
id|put_user
c_func
(paren
id|argc
comma
op_decrement
id|sp
)paren
suffix:semicolon
id|current-&gt;mm-&gt;arg_start
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
r_while
c_loop
(paren
id|argc
op_decrement
OG
l_int|0
)paren
(brace
r_char
id|c
suffix:semicolon
id|put_user
c_func
(paren
id|p
comma
id|argv
op_increment
)paren
suffix:semicolon
r_do
(brace
id|get_user
c_func
(paren
id|c
comma
id|p
op_increment
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|c
)paren
suffix:semicolon
)brace
id|put_user
c_func
(paren
l_int|NULL
comma
id|argv
)paren
suffix:semicolon
id|current-&gt;mm-&gt;arg_end
op_assign
id|current-&gt;mm-&gt;env_start
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
r_while
c_loop
(paren
id|envc
op_decrement
OG
l_int|0
)paren
(brace
r_char
id|c
suffix:semicolon
id|put_user
c_func
(paren
id|p
comma
id|envp
op_increment
)paren
suffix:semicolon
r_do
(brace
id|get_user
c_func
(paren
id|c
comma
id|p
op_increment
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|c
)paren
suffix:semicolon
)brace
id|put_user
c_func
(paren
l_int|NULL
comma
id|envp
)paren
suffix:semicolon
id|current-&gt;mm-&gt;env_end
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
r_return
id|sp
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the functions used to load a.out style executables and shared&n; * libraries.  There is no binary dependent code anywhere else.&n; */
DECL|function|do_load_aout_binary
r_static
r_inline
r_int
id|do_load_aout_binary
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|exec
id|ex
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_int
r_int
id|error
suffix:semicolon
r_int
r_int
id|p
op_assign
id|bprm-&gt;p
suffix:semicolon
r_int
r_int
id|fd_offset
suffix:semicolon
r_int
r_int
id|rlim
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|ex
op_assign
op_star
(paren
(paren
r_struct
id|exec
op_star
)paren
id|bprm-&gt;buf
)paren
suffix:semicolon
multiline_comment|/* exec-header */
r_if
c_cond
(paren
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|ZMAGIC
op_logical_and
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|OMAGIC
op_logical_and
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|QMAGIC
op_logical_and
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|NMAGIC
)paren
op_logical_or
id|N_TRSIZE
c_func
(paren
id|ex
)paren
op_logical_or
id|N_DRSIZE
c_func
(paren
id|ex
)paren
op_logical_or
id|bprm-&gt;dentry-&gt;d_inode-&gt;i_size
OL
id|ex.a_text
op_plus
id|ex.a_data
op_plus
id|N_SYMSIZE
c_func
(paren
id|ex
)paren
op_plus
id|N_TXTOFF
c_func
(paren
id|ex
)paren
)paren
(brace
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
id|current-&gt;personality
op_assign
id|PER_LINUX
suffix:semicolon
id|fd_offset
op_assign
id|N_TXTOFF
c_func
(paren
id|ex
)paren
suffix:semicolon
macro_line|#ifdef __i386__
r_if
c_cond
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_eq
id|ZMAGIC
op_logical_and
id|fd_offset
op_ne
id|BLOCK_SIZE
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;N_TXTOFF != BLOCK_SIZE. See a.out.h.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
r_if
c_cond
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_eq
id|ZMAGIC
op_logical_and
id|ex.a_text
op_logical_and
(paren
id|fd_offset
OL
id|bprm-&gt;dentry-&gt;d_inode-&gt;i_sb-&gt;s_blocksize
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;N_TXTOFF &lt; BLOCK_SIZE. Please convert binary.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Check initial limits. This avoids letting people circumvent&n;&t; * size limits imposed on them by creating programs with large&n;&t; * arrays in the data or bss.&n;&t; */
id|rlim
op_assign
id|current-&gt;rlim
(braket
id|RLIMIT_DATA
)braket
dot
id|rlim_cur
suffix:semicolon
r_if
c_cond
(paren
id|rlim
op_ge
id|RLIM_INFINITY
)paren
id|rlim
op_assign
op_complement
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ex.a_data
op_plus
id|ex.a_bss
OG
id|rlim
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Flush all traces of the currently running executable */
id|retval
op_assign
id|flush_old_exec
c_func
(paren
id|bprm
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
multiline_comment|/* OK, This is the point of no return */
macro_line|#if defined(__sparc__) &amp;&amp; !defined(__sparc_v9__)
id|memcpy
c_func
(paren
op_amp
id|current-&gt;tss.core_exec
comma
op_amp
id|ex
comma
r_sizeof
(paren
r_struct
id|exec
)paren
)paren
suffix:semicolon
macro_line|#endif
id|current-&gt;mm-&gt;end_code
op_assign
id|ex.a_text
op_plus
(paren
id|current-&gt;mm-&gt;start_code
op_assign
id|N_TXTADDR
c_func
(paren
id|ex
)paren
)paren
suffix:semicolon
id|current-&gt;mm-&gt;end_data
op_assign
id|ex.a_data
op_plus
(paren
id|current-&gt;mm-&gt;start_data
op_assign
id|N_DATADDR
c_func
(paren
id|ex
)paren
)paren
suffix:semicolon
id|current-&gt;mm-&gt;brk
op_assign
id|ex.a_bss
op_plus
(paren
id|current-&gt;mm-&gt;start_brk
op_assign
id|N_BSSADDR
c_func
(paren
id|ex
)paren
)paren
suffix:semicolon
id|current-&gt;mm-&gt;rss
op_assign
l_int|0
suffix:semicolon
id|current-&gt;mm-&gt;mmap
op_assign
l_int|NULL
suffix:semicolon
id|compute_creds
c_func
(paren
id|bprm
)paren
suffix:semicolon
id|current-&gt;flags
op_and_assign
op_complement
id|PF_FORKNOEXEC
suffix:semicolon
macro_line|#ifdef __sparc__
r_if
c_cond
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_eq
id|NMAGIC
)paren
(brace
multiline_comment|/* Fuck me plenty... */
id|error
op_assign
id|do_mmap
c_func
(paren
l_int|NULL
comma
id|N_TXTADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_text
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
)paren
suffix:semicolon
id|read_exec
c_func
(paren
id|bprm-&gt;dentry
comma
id|fd_offset
comma
(paren
r_char
op_star
)paren
id|N_TXTADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_text
comma
l_int|0
)paren
suffix:semicolon
id|error
op_assign
id|do_mmap
c_func
(paren
l_int|NULL
comma
id|N_DATADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_data
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
)paren
suffix:semicolon
id|read_exec
c_func
(paren
id|bprm-&gt;dentry
comma
id|fd_offset
op_plus
id|ex.a_text
comma
(paren
r_char
op_star
)paren
id|N_DATADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_data
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|beyond_if
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_eq
id|OMAGIC
)paren
(brace
macro_line|#if defined(__alpha__) || defined(__sparc__)
id|do_mmap
c_func
(paren
l_int|NULL
comma
id|N_TXTADDR
c_func
(paren
id|ex
)paren
op_amp
id|PAGE_MASK
comma
id|ex.a_text
op_plus
id|ex.a_data
op_plus
id|PAGE_SIZE
op_minus
l_int|1
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
)paren
suffix:semicolon
id|read_exec
c_func
(paren
id|bprm-&gt;dentry
comma
id|fd_offset
comma
(paren
r_char
op_star
)paren
id|N_TXTADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_text
op_plus
id|ex.a_data
comma
l_int|0
)paren
suffix:semicolon
macro_line|#else
id|do_mmap
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|ex.a_text
op_plus
id|ex.a_data
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
)paren
suffix:semicolon
id|read_exec
c_func
(paren
id|bprm-&gt;dentry
comma
l_int|32
comma
(paren
r_char
op_star
)paren
l_int|0
comma
id|ex.a_text
op_plus
id|ex.a_data
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|ex.a_text
op_amp
l_int|0xfff
op_logical_or
id|ex.a_data
op_amp
l_int|0xfff
)paren
op_logical_and
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|NMAGIC
)paren
)paren
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;executable not page aligned&bslash;n&quot;
)paren
suffix:semicolon
id|fd
op_assign
id|open_dentry
c_func
(paren
id|bprm-&gt;dentry
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_return
id|fd
suffix:semicolon
id|file
op_assign
id|fcheck
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_op
op_logical_or
op_logical_neg
id|file-&gt;f_op-&gt;mmap
)paren
(brace
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|do_mmap
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|ex.a_text
op_plus
id|ex.a_data
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
)paren
suffix:semicolon
id|read_exec
c_func
(paren
id|bprm-&gt;dentry
comma
id|fd_offset
comma
(paren
r_char
op_star
)paren
id|N_TXTADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_text
op_plus
id|ex.a_data
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|beyond_if
suffix:semicolon
)brace
id|error
op_assign
id|do_mmap
c_func
(paren
id|file
comma
id|N_TXTADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_text
comma
id|PROT_READ
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
op_or
id|MAP_DENYWRITE
op_or
id|MAP_EXECUTABLE
comma
id|fd_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
id|N_TXTADDR
c_func
(paren
id|ex
)paren
)paren
(brace
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGKILL
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|error
op_assign
id|do_mmap
c_func
(paren
id|file
comma
id|N_DATADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_data
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
op_or
id|MAP_DENYWRITE
op_or
id|MAP_EXECUTABLE
comma
id|fd_offset
op_plus
id|ex.a_text
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
id|N_DATADDR
c_func
(paren
id|ex
)paren
)paren
(brace
id|send_sig
c_func
(paren
id|SIGKILL
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
)brace
id|beyond_if
suffix:colon
r_if
c_cond
(paren
id|current-&gt;exec_domain
op_logical_and
id|current-&gt;exec_domain-&gt;module
)paren
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|current-&gt;exec_domain-&gt;module
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;binfmt
op_logical_and
id|current-&gt;binfmt-&gt;module
)paren
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|current-&gt;binfmt-&gt;module
)paren
suffix:semicolon
id|current-&gt;exec_domain
op_assign
id|lookup_exec_domain
c_func
(paren
id|current-&gt;personality
)paren
suffix:semicolon
id|current-&gt;binfmt
op_assign
op_amp
id|aout_format
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;exec_domain
op_logical_and
id|current-&gt;exec_domain-&gt;module
)paren
id|__MOD_INC_USE_COUNT
c_func
(paren
id|current-&gt;exec_domain-&gt;module
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;binfmt
op_logical_and
id|current-&gt;binfmt-&gt;module
)paren
id|__MOD_INC_USE_COUNT
c_func
(paren
id|current-&gt;binfmt-&gt;module
)paren
suffix:semicolon
id|set_brk
c_func
(paren
id|current-&gt;mm-&gt;start_brk
comma
id|current-&gt;mm-&gt;brk
)paren
suffix:semicolon
id|p
op_assign
id|setup_arg_pages
c_func
(paren
id|p
comma
id|bprm
)paren
suffix:semicolon
id|p
op_assign
(paren
r_int
r_int
)paren
id|create_aout_tables
c_func
(paren
(paren
r_char
op_star
)paren
id|p
comma
id|bprm
)paren
suffix:semicolon
id|current-&gt;mm-&gt;start_stack
op_assign
id|p
suffix:semicolon
macro_line|#ifdef __alpha__
id|regs-&gt;gp
op_assign
id|ex.a_gpvalue
suffix:semicolon
macro_line|#endif
id|start_thread
c_func
(paren
id|regs
comma
id|ex.a_entry
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_PTRACED
)paren
id|send_sig
c_func
(paren
id|SIGTRAP
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|load_aout_binary
id|load_aout_binary
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|retval
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|retval
op_assign
id|do_load_aout_binary
c_func
(paren
id|bprm
comma
id|regs
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|do_load_aout_library
id|do_load_aout_library
c_func
(paren
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
id|inode
op_star
id|inode
suffix:semicolon
r_int
r_int
id|bss
comma
id|start_addr
comma
id|len
suffix:semicolon
r_int
r_int
id|error
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|loff_t
id|offset
op_assign
l_int|0
suffix:semicolon
r_struct
id|exec
id|ex
suffix:semicolon
id|retval
op_assign
op_minus
id|EACCES
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_op
)paren
r_goto
id|out_putf
suffix:semicolon
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
multiline_comment|/* N.B. Save current fs? */
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|error
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|read
c_func
(paren
id|file
comma
(paren
r_char
op_star
)paren
op_amp
id|ex
comma
r_sizeof
(paren
id|ex
)paren
comma
op_amp
id|offset
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
r_sizeof
(paren
id|ex
)paren
)paren
r_goto
id|out_putf
suffix:semicolon
multiline_comment|/* We come in here for the regular a.out style of shared libraries */
r_if
c_cond
(paren
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|ZMAGIC
op_logical_and
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|QMAGIC
)paren
op_logical_or
id|N_TRSIZE
c_func
(paren
id|ex
)paren
op_logical_or
id|N_DRSIZE
c_func
(paren
id|ex
)paren
op_logical_or
(paren
(paren
id|ex.a_entry
op_amp
l_int|0xfff
)paren
op_logical_and
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_eq
id|ZMAGIC
)paren
op_logical_or
id|inode-&gt;i_size
OL
id|ex.a_text
op_plus
id|ex.a_data
op_plus
id|N_SYMSIZE
c_func
(paren
id|ex
)paren
op_plus
id|N_TXTOFF
c_func
(paren
id|ex
)paren
)paren
(brace
r_goto
id|out_putf
suffix:semicolon
)brace
r_if
c_cond
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_eq
id|ZMAGIC
op_logical_and
id|N_TXTOFF
c_func
(paren
id|ex
)paren
op_logical_and
(paren
id|N_TXTOFF
c_func
(paren
id|ex
)paren
OL
id|inode-&gt;i_sb-&gt;s_blocksize
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;N_TXTOFF &lt; BLOCK_SIZE. Please convert library&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_putf
suffix:semicolon
)brace
r_if
c_cond
(paren
id|N_FLAGS
c_func
(paren
id|ex
)paren
)paren
r_goto
id|out_putf
suffix:semicolon
multiline_comment|/* For  QMAGIC, the starting address is 0x20 into the page.  We mask&n;&t;   this off to get the starting address for the page */
id|start_addr
op_assign
id|ex.a_entry
op_amp
l_int|0xfffff000
suffix:semicolon
multiline_comment|/* Now use mmap to map the library into memory. */
id|error
op_assign
id|do_mmap
c_func
(paren
id|file
comma
id|start_addr
comma
id|ex.a_text
op_plus
id|ex.a_data
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
op_or
id|MAP_DENYWRITE
comma
id|N_TXTOFF
c_func
(paren
id|ex
)paren
)paren
suffix:semicolon
id|retval
op_assign
id|error
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
id|start_addr
)paren
r_goto
id|out_putf
suffix:semicolon
id|len
op_assign
id|PAGE_ALIGN
c_func
(paren
id|ex.a_text
op_plus
id|ex.a_data
)paren
suffix:semicolon
id|bss
op_assign
id|ex.a_text
op_plus
id|ex.a_data
op_plus
id|ex.a_bss
suffix:semicolon
r_if
c_cond
(paren
id|bss
OG
id|len
)paren
(brace
id|error
op_assign
id|do_mmap
c_func
(paren
l_int|NULL
comma
id|start_addr
op_plus
id|len
comma
id|bss
op_minus
id|len
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_PRIVATE
op_or
id|MAP_FIXED
comma
l_int|0
)paren
suffix:semicolon
id|retval
op_assign
id|error
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
id|start_addr
op_plus
id|len
)paren
r_goto
id|out_putf
suffix:semicolon
)brace
id|retval
op_assign
l_int|0
suffix:semicolon
id|out_putf
suffix:colon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_int
DECL|function|load_aout_library
id|load_aout_library
c_func
(paren
r_int
id|fd
)paren
(brace
r_int
id|retval
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|retval
op_assign
id|do_load_aout_library
c_func
(paren
id|fd
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|init_aout_binfmt
c_func
(paren
r_void
)paren
)paren
(brace
r_return
id|register_binfmt
c_func
(paren
op_amp
id|aout_format
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|init_aout_binfmt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|unregister_binfmt
c_func
(paren
op_amp
id|aout_format
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
