multiline_comment|/*&n; *  linux/fs/exec.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
multiline_comment|/*&n; * #!-checking implemented by tytso.&n; */
multiline_comment|/*&n; * Demand-loading implemented 01.12.91 - no need to read anything but&n; * the header into memory. The inode of the executable is put into&n; * &quot;current-&gt;executable&quot;, and page faults do the actual loading. Clean.&n; *&n; * Once more I can proudly say that linux stood up to being changed: it&n; * was less than 2 hours work to get demand-loading completely implemented.&n; */
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;sys/ptrace.h&gt;
macro_line|#include &lt;a.out.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;sys/user.h&gt;
r_extern
r_int
id|sys_exit
c_func
(paren
r_int
id|exit_code
)paren
suffix:semicolon
r_extern
r_int
id|sys_close
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
multiline_comment|/*&n; * MAX_ARG_PAGES defines the number of pages allocated for arguments&n; * and envelope for the new program. 32 should suffice, this gives&n; * a maximum env+arg of 128kB !&n; */
DECL|macro|MAX_ARG_PAGES
mdefine_line|#define MAX_ARG_PAGES 32
multiline_comment|/*&n; * These are the only things you should do on a core-file: use only these&n; * macros to write out all the necessary info.&n; */
DECL|macro|DUMP_WRITE
mdefine_line|#define DUMP_WRITE(addr,nr) &bslash;&n;while (file.f_op-&gt;write(inode,&amp;file,(char *)(addr),(nr)) != (nr)) goto close_coredump
DECL|macro|DUMP_SEEK
mdefine_line|#define DUMP_SEEK(offset) &bslash;&n;if (file.f_op-&gt;lseek) { &bslash;&n;&t;if (file.f_op-&gt;lseek(inode,&amp;file,(offset),0) != (offset)) &bslash;&n; &t;&t;goto close_coredump; &bslash;&n;} else file.f_pos = (offset)&t;&t;
multiline_comment|/*&n; * Routine writes a core dump image in the current directory.&n; * Currently only a stub-function.&n; *&n; * Note that setuid/setgid files won&squot;t make a core-dump if the uid/gid&n; * changed due to the set[u|g]id. It&squot;s enforced by the &quot;current-&gt;dumpable&quot;&n; * field, which also makes sure the core-dumps won&squot;t be recursive if the&n; * dumping of the process results in another error..&n; */
DECL|function|core_dump
r_int
id|core_dump
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
r_int
r_int
id|fs
suffix:semicolon
r_int
id|has_dumped
op_assign
l_int|0
suffix:semicolon
r_register
r_int
id|dump_start
comma
id|dump_size
suffix:semicolon
r_struct
id|user
id|dump
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;dumpable
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
op_div
l_int|1024
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|__asm__
c_func
(paren
l_string|&quot;mov %%fs,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|fs
)paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mov %0,%%fs&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
(paren
r_int
r_int
)paren
l_int|0x10
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|open_namei
c_func
(paren
l_string|&quot;core&quot;
comma
id|O_CREAT
op_or
id|O_WRONLY
op_or
id|O_TRUNC
comma
l_int|0600
comma
op_amp
id|inode
)paren
)paren
r_goto
id|end_coredump
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
id|file.f_mode
op_assign
l_int|3
suffix:semicolon
id|file.f_flags
op_assign
l_int|0
suffix:semicolon
id|file.f_count
op_assign
l_int|1
suffix:semicolon
id|file.f_inode
op_assign
id|inode
suffix:semicolon
id|file.f_pos
op_assign
l_int|0
suffix:semicolon
id|file.f_reada
op_assign
l_int|0
suffix:semicolon
id|file.f_op
op_assign
id|inode-&gt;i_op-&gt;default_file_ops
suffix:semicolon
r_if
c_cond
(paren
id|file.f_op-&gt;open
)paren
r_if
c_cond
(paren
id|file.f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
op_amp
id|file
)paren
)paren
r_goto
id|end_coredump
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
multiline_comment|/* write and seek example: from kernel space */
id|__asm__
c_func
(paren
l_string|&quot;mov %0,%%fs&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
(paren
r_int
r_int
)paren
l_int|0x10
)paren
)paren
suffix:semicolon
id|dump.u_tsize
op_assign
id|current-&gt;end_code
op_div
id|PAGE_SIZE
suffix:semicolon
id|dump.u_dsize
op_assign
(paren
id|current-&gt;brk
op_minus
id|current-&gt;end_code
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
id|dump.u_ssize
op_assign
(paren
(paren
id|current-&gt;start_stack
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_div
id|PAGE_SIZE
)paren
op_minus
(paren
id|regs-&gt;esp
op_div
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* If the size of the dump file exceeds the rlimit, then see what would happen&n;   if we wrote the stack, but not the data area.  */
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
op_div
l_int|1024
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
multiline_comment|/* Make sure we have enough room to write the stack and data areas. */
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
op_div
l_int|1024
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
id|dump.u_comm
op_assign
l_int|0
suffix:semicolon
id|dump.u_ar0
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
(paren
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
)paren
(paren
op_amp
id|dump
)paren
)paren
)paren
suffix:semicolon
id|dump.signal
op_assign
id|signr
suffix:semicolon
id|dump.regs
op_assign
op_star
id|regs
suffix:semicolon
id|dump.start_code
op_assign
l_int|0
suffix:semicolon
id|dump.start_stack
op_assign
id|regs-&gt;esp
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Flag indicating the math stuff is valid. */
r_if
c_cond
(paren
id|dump.u_fpvalid
op_assign
id|current-&gt;used_math
)paren
(brace
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
id|__asm__
c_func
(paren
l_string|&quot;clts ; fnsave %0&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|dump.i387
)paren
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
op_amp
id|dump.i387
comma
op_amp
id|current-&gt;tss.i387
comma
r_sizeof
(paren
id|dump.i387
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
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
id|DUMP_SEEK
c_func
(paren
r_sizeof
(paren
id|dump
)paren
)paren
suffix:semicolon
multiline_comment|/* Dump the task struct.  Not be used by gdb, but could be useful */
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
multiline_comment|/* Now dump all of the user data.  Include malloced stuff as well */
id|DUMP_SEEK
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* now we start writing out the user space info */
id|__asm__
c_func
(paren
l_string|&quot;mov %0,%%fs&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
(paren
r_int
r_int
)paren
l_int|0x17
)paren
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
id|current-&gt;end_code
suffix:semicolon
id|dump_size
op_assign
id|current-&gt;brk
op_minus
id|current-&gt;end_code
suffix:semicolon
id|DUMP_WRITE
c_func
(paren
id|dump_start
comma
id|dump_size
)paren
suffix:semicolon
)brace
suffix:semicolon
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
id|regs-&gt;esp
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|dump_size
op_assign
id|dump.u_ssize
op_star
id|PAGE_SIZE
suffix:semicolon
id|DUMP_WRITE
c_func
(paren
id|dump_start
comma
id|dump_size
)paren
suffix:semicolon
)brace
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
id|end_coredump
suffix:colon
id|__asm__
c_func
(paren
l_string|&quot;mov %0,%%fs&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|fs
)paren
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|has_dumped
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that a shared library must be both readable and executable due to&n; * security reasons.&n; *&n; * Also note that we take the address to load from from the file itself.&n; */
DECL|function|sys_uselib
r_int
id|sys_uselib
c_func
(paren
r_const
r_char
op_star
id|library
)paren
(brace
DECL|macro|libnum
mdefine_line|#define libnum&t;(current-&gt;numlibraries)
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|exec
id|ex
suffix:semicolon
r_if
c_cond
(paren
id|get_limit
c_func
(paren
l_int|0x17
)paren
op_ne
id|TASK_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|libnum
op_ge
id|MAX_SHARED_LIBS
)paren
op_logical_or
(paren
id|libnum
OL
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|library
)paren
id|inode
op_assign
id|namei
c_func
(paren
id|library
)paren
suffix:semicolon
r_else
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|ENOENT
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
op_logical_or
op_logical_neg
id|permission
c_func
(paren
id|inode
comma
id|MAY_READ
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
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|inode-&gt;i_data
(braket
l_int|0
)braket
)paren
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
id|ex
op_assign
op_star
(paren
r_struct
id|exec
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|ZMAGIC
op_logical_or
id|ex.a_trsize
op_logical_or
id|ex.a_drsize
op_logical_or
id|ex.a_text
op_plus
id|ex.a_data
op_plus
id|ex.a_bss
OG
l_int|0x3000000
op_logical_or
id|inode-&gt;i_size
OL
id|ex.a_text
op_plus
id|ex.a_data
op_plus
id|ex.a_syms
op_plus
id|N_TXTOFF
c_func
(paren
id|ex
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
id|ENOEXEC
suffix:semicolon
)brace
id|current-&gt;libraries
(braket
id|libnum
)braket
dot
id|library
op_assign
id|inode
suffix:semicolon
id|current-&gt;libraries
(braket
id|libnum
)braket
dot
id|start
op_assign
id|ex.a_entry
suffix:semicolon
id|current-&gt;libraries
(braket
id|libnum
)braket
dot
id|length
op_assign
(paren
id|ex.a_data
op_plus
id|ex.a_text
op_plus
l_int|0xfff
)paren
op_amp
l_int|0xfffff000
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;Loaded library %d at %08x, length %08x&bslash;n&quot;
comma
id|libnum
comma
id|current-&gt;libraries
(braket
id|libnum
)braket
dot
id|start
comma
id|current-&gt;libraries
(braket
id|libnum
)braket
dot
id|length
)paren
suffix:semicolon
macro_line|#endif
id|libnum
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
DECL|macro|libnum
macro_line|#undef libnum
)brace
multiline_comment|/*&n; * create_tables() parses the env- and arg-strings in new user&n; * memory and creates the pointer tables from them, and puts their&n; * addresses on the &quot;stack&quot;, returning the new stack pointer value.&n; */
DECL|function|create_tables
r_static
r_int
r_int
op_star
id|create_tables
c_func
(paren
r_char
op_star
id|p
comma
r_int
id|argc
comma
r_int
id|envc
)paren
(brace
r_int
r_int
op_star
id|argv
comma
op_star
id|envp
suffix:semicolon
r_int
r_int
op_star
id|sp
suffix:semicolon
id|sp
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
l_int|0xfffffffc
op_amp
(paren
r_int
r_int
)paren
id|p
)paren
suffix:semicolon
id|sp
op_sub_assign
id|envc
op_plus
l_int|1
suffix:semicolon
id|envp
op_assign
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
id|sp
suffix:semicolon
id|put_fs_long
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
id|put_fs_long
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
id|put_fs_long
c_func
(paren
(paren
r_int
r_int
)paren
id|argc
comma
op_decrement
id|sp
)paren
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
id|put_fs_long
c_func
(paren
(paren
r_int
r_int
)paren
id|p
comma
id|argv
op_increment
)paren
suffix:semicolon
r_while
c_loop
(paren
id|get_fs_byte
c_func
(paren
id|p
op_increment
)paren
)paren
multiline_comment|/* nothing */
suffix:semicolon
)brace
id|put_fs_long
c_func
(paren
l_int|0
comma
id|argv
)paren
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
id|put_fs_long
c_func
(paren
(paren
r_int
r_int
)paren
id|p
comma
id|envp
op_increment
)paren
suffix:semicolon
r_while
c_loop
(paren
id|get_fs_byte
c_func
(paren
id|p
op_increment
)paren
)paren
multiline_comment|/* nothing */
suffix:semicolon
)brace
id|put_fs_long
c_func
(paren
l_int|0
comma
id|envp
)paren
suffix:semicolon
r_return
id|sp
suffix:semicolon
)brace
multiline_comment|/*&n; * count() counts the number of arguments/envelopes&n; */
DECL|function|count
r_static
r_int
id|count
c_func
(paren
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_char
op_star
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_assign
id|argv
)paren
r_while
c_loop
(paren
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|tmp
op_increment
)paren
)paren
)paren
id|i
op_increment
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/*&n; * &squot;copy_string()&squot; copies argument/envelope strings from user&n; * memory to free pages in kernel mem. These are in a format ready&n; * to be put directly into the top of new user memory.&n; *&n; * Modified by TYT, 11/24/91 to add the from_kmem argument, which specifies&n; * whether the string and the string array are from user or kernel segments:&n; * &n; * from_kmem     argv *        argv **&n; *    0          user space    user space&n; *    1          kernel space  user space&n; *    2          kernel space  kernel space&n; * &n; * We do this by playing games with the fs segment register.  Since it&n; * it is expensive to load a segment register, we try to avoid calling&n; * set_fs() unless we absolutely have to.&n; */
DECL|function|copy_strings
r_static
r_int
r_int
id|copy_strings
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_int
r_int
op_star
id|page
comma
r_int
r_int
id|p
comma
r_int
id|from_kmem
)paren
(brace
r_char
op_star
id|tmp
comma
op_star
id|pag
suffix:semicolon
r_int
id|len
comma
id|offset
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|old_fs
comma
id|new_fs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* bullet-proofing */
id|new_fs
op_assign
id|get_ds
c_func
(paren
)paren
suffix:semicolon
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from_kmem
op_eq
l_int|2
)paren
id|set_fs
c_func
(paren
id|new_fs
)paren
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
r_if
c_cond
(paren
id|from_kmem
op_eq
l_int|1
)paren
id|set_fs
c_func
(paren
id|new_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|get_fs_long
c_func
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|argv
)paren
op_plus
id|argc
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;argc is wrong&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from_kmem
op_eq
l_int|1
)paren
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* remember zero-padding */
r_do
(brace
id|len
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|get_fs_byte
c_func
(paren
id|tmp
op_increment
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
OL
id|len
)paren
(brace
multiline_comment|/* this shouldn&squot;t happen - 128kB */
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
)paren
(brace
op_decrement
id|p
suffix:semicolon
op_decrement
id|tmp
suffix:semicolon
op_decrement
id|len
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|offset
OL
l_int|0
)paren
(brace
id|offset
op_assign
id|p
op_mod
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|from_kmem
op_eq
l_int|2
)paren
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pag
op_assign
(paren
r_char
op_star
)paren
id|page
(braket
id|p
op_div
id|PAGE_SIZE
)braket
)paren
op_logical_and
op_logical_neg
(paren
id|pag
op_assign
(paren
r_char
op_star
)paren
id|page
(braket
id|p
op_div
id|PAGE_SIZE
)braket
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_free_page
c_func
(paren
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|from_kmem
op_eq
l_int|2
)paren
id|set_fs
c_func
(paren
id|new_fs
)paren
suffix:semicolon
)brace
op_star
(paren
id|pag
op_plus
id|offset
)paren
op_assign
id|get_fs_byte
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|from_kmem
op_eq
l_int|2
)paren
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|change_ldt
r_static
r_int
r_int
id|change_ldt
c_func
(paren
r_int
r_int
id|text_size
comma
r_int
r_int
op_star
id|page
)paren
(brace
r_int
r_int
id|code_limit
comma
id|data_limit
comma
id|code_base
comma
id|data_base
suffix:semicolon
r_int
id|i
suffix:semicolon
id|code_limit
op_assign
id|TASK_SIZE
suffix:semicolon
id|data_limit
op_assign
id|TASK_SIZE
suffix:semicolon
id|code_base
op_assign
id|get_base
c_func
(paren
id|current-&gt;ldt
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|data_base
op_assign
id|code_base
suffix:semicolon
id|set_base
c_func
(paren
id|current-&gt;ldt
(braket
l_int|1
)braket
comma
id|code_base
)paren
suffix:semicolon
id|set_limit
c_func
(paren
id|current-&gt;ldt
(braket
l_int|1
)braket
comma
id|code_limit
)paren
suffix:semicolon
id|set_base
c_func
(paren
id|current-&gt;ldt
(braket
l_int|2
)braket
comma
id|data_base
)paren
suffix:semicolon
id|set_limit
c_func
(paren
id|current-&gt;ldt
(braket
l_int|2
)braket
comma
id|data_limit
)paren
suffix:semicolon
multiline_comment|/* make sure fs points to the NEW data segment */
id|__asm__
c_func
(paren
l_string|&quot;pushl $0x17&bslash;n&bslash;tpop %%fs&quot;
op_scope_resolution
)paren
suffix:semicolon
id|data_base
op_add_assign
id|data_limit
op_minus
id|LIBRARY_SIZE
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|MAX_ARG_PAGES
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|data_base
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|page
(braket
id|i
)braket
)paren
id|put_dirty_page
c_func
(paren
id|page
(braket
id|i
)braket
comma
id|data_base
)paren
suffix:semicolon
)brace
r_return
id|data_limit
suffix:semicolon
)brace
DECL|function|read_omagic
r_static
r_void
id|read_omagic
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|bytes
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|n
comma
id|blkno
comma
id|blk
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|dest
op_assign
(paren
r_char
op_star
)paren
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|bytes
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|blkno
op_assign
id|bmap
c_func
(paren
id|inode
comma
id|blk
)paren
)paren
)paren
id|sys_exit
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|blkno
)paren
)paren
)paren
id|sys_exit
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
id|n
op_assign
(paren
id|blk
ques
c_cond
id|BLOCK_SIZE
suffix:colon
id|BLOCK_SIZE
op_minus
r_sizeof
(paren
r_struct
id|exec
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bytes
OL
id|n
)paren
id|n
op_assign
id|bytes
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|dest
comma
(paren
id|blk
ques
c_cond
id|bh-&gt;b_data
suffix:colon
id|bh-&gt;b_data
op_plus
r_sizeof
(paren
r_struct
id|exec
)paren
)paren
comma
id|n
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
op_increment
id|blk
suffix:semicolon
id|dest
op_add_assign
id|n
suffix:semicolon
id|bytes
op_sub_assign
id|n
suffix:semicolon
)brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|current-&gt;executable
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * &squot;do_execve()&squot; executes a new program.&n; *&n; * NOTE! We leave 4MB free at the top of the data-area for a loadable&n; * library.&n; */
DECL|function|do_execve
r_int
id|do_execve
c_func
(paren
r_int
r_int
op_star
id|eip
comma
r_int
id|tmp
comma
r_char
op_star
id|filename
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|exec
id|ex
suffix:semicolon
r_int
r_int
id|page
(braket
id|MAX_ARG_PAGES
)braket
suffix:semicolon
r_int
id|i
comma
id|argc
comma
id|envc
suffix:semicolon
r_int
id|e_uid
comma
id|e_gid
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
id|sh_bang
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|p
op_assign
id|PAGE_SIZE
op_star
id|MAX_ARG_PAGES
op_minus
l_int|4
suffix:semicolon
r_int
id|ch
suffix:semicolon
r_if
c_cond
(paren
(paren
l_int|0xffff
op_amp
id|eip
(braket
l_int|1
)braket
)paren
op_ne
l_int|0x000f
)paren
id|panic
c_func
(paren
l_string|&quot;execve called from supervisor mode&quot;
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
id|MAX_ARG_PAGES
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* clear page-table */
id|page
(braket
id|i
)braket
op_assign
l_int|0
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
multiline_comment|/* get executables inode */
r_return
op_minus
id|ENOENT
suffix:semicolon
id|argc
op_assign
id|count
c_func
(paren
id|argv
)paren
suffix:semicolon
id|envc
op_assign
id|count
c_func
(paren
id|envp
)paren
suffix:semicolon
id|restart_interp
suffix:colon
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
(brace
multiline_comment|/* must be regular file */
id|retval
op_assign
op_minus
id|EACCES
suffix:semicolon
r_goto
id|exec_error2
suffix:semicolon
)brace
id|i
op_assign
id|inode-&gt;i_mode
suffix:semicolon
multiline_comment|/* make sure we don&squot;t let suid, sgid files be ptraced. */
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_PTRACED
)paren
(brace
id|e_uid
op_assign
id|current-&gt;euid
suffix:semicolon
id|e_gid
op_assign
id|current-&gt;egid
suffix:semicolon
)brace
r_else
(brace
id|e_uid
op_assign
(paren
id|i
op_amp
id|S_ISUID
)paren
ques
c_cond
id|inode-&gt;i_uid
suffix:colon
id|current-&gt;euid
suffix:semicolon
id|e_gid
op_assign
(paren
id|i
op_amp
id|S_ISGID
)paren
ques
c_cond
id|inode-&gt;i_gid
suffix:colon
id|current-&gt;egid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current-&gt;euid
op_eq
id|inode-&gt;i_uid
)paren
id|i
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
id|i
op_rshift_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|i
op_amp
l_int|1
)paren
op_logical_and
op_logical_neg
(paren
(paren
id|inode-&gt;i_mode
op_amp
l_int|0111
)paren
op_logical_and
id|suser
c_func
(paren
)paren
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EACCES
suffix:semicolon
r_goto
id|exec_error2
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|inode-&gt;i_data
(braket
l_int|0
)braket
)paren
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EACCES
suffix:semicolon
r_goto
id|exec_error2
suffix:semicolon
)brace
id|ex
op_assign
op_star
(paren
(paren
r_struct
id|exec
op_star
)paren
id|bh-&gt;b_data
)paren
suffix:semicolon
multiline_comment|/* read exec-header */
r_if
c_cond
(paren
(paren
id|bh-&gt;b_data
(braket
l_int|0
)braket
op_eq
l_char|&squot;#&squot;
)paren
op_logical_and
(paren
id|bh-&gt;b_data
(braket
l_int|1
)braket
op_eq
l_char|&squot;!&squot;
)paren
op_logical_and
(paren
op_logical_neg
id|sh_bang
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * This section does the #! interpretation.&n;&t;&t; * Sorta complicated, but hopefully it will work.  -TYT&n;&t;&t; */
r_char
id|buf
(braket
l_int|128
)braket
comma
op_star
id|cp
comma
op_star
id|interp
comma
op_star
id|i_name
comma
op_star
id|i_arg
suffix:semicolon
r_int
r_int
id|old_fs
suffix:semicolon
id|strncpy
c_func
(paren
id|buf
comma
id|bh-&gt;b_data
op_plus
l_int|2
comma
l_int|127
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|buf
(braket
l_int|127
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|cp
op_assign
id|strchr
c_func
(paren
id|buf
comma
l_char|&squot;&bslash;n&squot;
)paren
)paren
(brace
op_star
id|cp
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|buf
suffix:semicolon
(paren
op_star
id|cp
op_eq
l_char|&squot; &squot;
)paren
op_logical_or
(paren
op_star
id|cp
op_eq
l_char|&squot;&bslash;t&squot;
)paren
suffix:semicolon
id|cp
op_increment
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cp
op_logical_or
op_star
id|cp
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|retval
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
multiline_comment|/* No interpreter name found */
r_goto
id|exec_error1
suffix:semicolon
)brace
id|interp
op_assign
id|i_name
op_assign
id|cp
suffix:semicolon
id|i_arg
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
op_star
id|cp
op_logical_and
(paren
op_star
id|cp
op_ne
l_char|&squot; &squot;
)paren
op_logical_and
(paren
op_star
id|cp
op_ne
l_char|&squot;&bslash;t&squot;
)paren
suffix:semicolon
id|cp
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;/&squot;
)paren
id|i_name
op_assign
id|cp
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|cp
)paren
(brace
op_star
id|cp
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|i_arg
op_assign
id|cp
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * OK, we&squot;ve parsed out the interpreter name and&n;&t;&t; * (optional) argument.&n;&t;&t; */
r_if
c_cond
(paren
id|sh_bang
op_increment
op_eq
l_int|0
)paren
(brace
id|p
op_assign
id|copy_strings
c_func
(paren
id|envc
comma
id|envp
comma
id|page
comma
id|p
comma
l_int|0
)paren
suffix:semicolon
id|p
op_assign
id|copy_strings
c_func
(paren
op_decrement
id|argc
comma
id|argv
op_plus
l_int|1
comma
id|page
comma
id|p
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Splice in (1) the interpreter&squot;s name for argv[0]&n;&t;&t; *           (2) (optional) argument to interpreter&n;&t;&t; *           (3) filename of shell script&n;&t;&t; *&n;&t;&t; * This is done in reverse order, because of how the&n;&t;&t; * user environment and arguments are stored.&n;&t;&t; */
id|p
op_assign
id|copy_strings
c_func
(paren
l_int|1
comma
op_amp
id|filename
comma
id|page
comma
id|p
comma
l_int|1
)paren
suffix:semicolon
id|argc
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i_arg
)paren
(brace
id|p
op_assign
id|copy_strings
c_func
(paren
l_int|1
comma
op_amp
id|i_arg
comma
id|page
comma
id|p
comma
l_int|2
)paren
suffix:semicolon
id|argc
op_increment
suffix:semicolon
)brace
id|p
op_assign
id|copy_strings
c_func
(paren
l_int|1
comma
op_amp
id|i_name
comma
id|page
comma
id|p
comma
l_int|2
)paren
suffix:semicolon
id|argc
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|exec_error1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * OK, now restart the process with the interpreter&squot;s inode.&n;&t;&t; */
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
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
id|interp
)paren
)paren
)paren
(brace
multiline_comment|/* get executables inode */
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|exec_error1
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_goto
id|restart_interp
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
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
)paren
op_logical_or
id|ex.a_trsize
op_logical_or
id|ex.a_drsize
op_logical_or
id|ex.a_text
op_plus
id|ex.a_data
op_plus
id|ex.a_bss
OG
l_int|0x3000000
op_logical_or
id|inode-&gt;i_size
OL
id|ex.a_text
op_plus
id|ex.a_data
op_plus
id|ex.a_syms
op_plus
id|N_TXTOFF
c_func
(paren
id|ex
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
r_goto
id|exec_error2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|N_TXTOFF
c_func
(paren
id|ex
)paren
op_ne
id|BLOCK_SIZE
op_logical_and
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|OMAGIC
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: N_TXTOFF != BLOCK_SIZE. See a.out.h.&quot;
comma
id|filename
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
r_goto
id|exec_error2
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sh_bang
)paren
(brace
id|p
op_assign
id|copy_strings
c_func
(paren
id|envc
comma
id|envp
comma
id|page
comma
id|p
comma
l_int|0
)paren
suffix:semicolon
id|p
op_assign
id|copy_strings
c_func
(paren
id|argc
comma
id|argv
comma
id|page
comma
id|p
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|exec_error2
suffix:semicolon
)brace
)brace
multiline_comment|/* OK, This is the point of no return */
id|current-&gt;dumpable
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|ch
op_assign
id|get_fs_byte
c_func
(paren
id|filename
op_increment
)paren
)paren
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)paren
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;/&squot;
)paren
id|i
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|i
OL
l_int|8
)paren
id|current-&gt;comm
(braket
id|i
op_increment
)braket
op_assign
id|ch
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|8
)paren
id|current-&gt;comm
(braket
id|i
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;executable
)paren
id|iput
c_func
(paren
id|current-&gt;executable
)paren
suffix:semicolon
id|i
op_assign
id|current-&gt;numlibraries
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
(brace
id|iput
c_func
(paren
id|current-&gt;libraries
(braket
id|i
)braket
dot
id|library
)paren
suffix:semicolon
id|current-&gt;libraries
(braket
id|i
)braket
dot
id|library
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|e_uid
op_ne
id|current-&gt;euid
op_logical_or
id|e_gid
op_ne
id|current-&gt;egid
op_logical_or
op_logical_neg
id|permission
c_func
(paren
id|inode
comma
id|MAY_READ
)paren
)paren
id|current-&gt;dumpable
op_assign
l_int|0
suffix:semicolon
id|current-&gt;numlibraries
op_assign
l_int|0
suffix:semicolon
id|current-&gt;executable
op_assign
id|inode
suffix:semicolon
id|current-&gt;signal
op_assign
l_int|0
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
id|current-&gt;sigaction
(braket
id|i
)braket
dot
id|sa_mask
op_assign
l_int|0
suffix:semicolon
id|current-&gt;sigaction
(braket
id|i
)braket
dot
id|sa_flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;sigaction
(braket
id|i
)braket
dot
id|sa_handler
op_ne
id|SIG_IGN
)paren
id|current-&gt;sigaction
(braket
id|i
)braket
dot
id|sa_handler
op_assign
l_int|NULL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_OPEN
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|current-&gt;close_on_exec
op_rshift
id|i
)paren
op_amp
l_int|1
)paren
id|sys_close
c_func
(paren
id|i
)paren
suffix:semicolon
id|current-&gt;close_on_exec
op_assign
l_int|0
suffix:semicolon
id|free_page_tables
c_func
(paren
id|get_base
c_func
(paren
id|current-&gt;ldt
(braket
l_int|1
)braket
)paren
comma
id|get_limit
c_func
(paren
l_int|0x0f
)paren
)paren
suffix:semicolon
id|free_page_tables
c_func
(paren
id|get_base
c_func
(paren
id|current-&gt;ldt
(braket
l_int|2
)braket
)paren
comma
id|get_limit
c_func
(paren
l_int|0x17
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|0
suffix:semicolon
id|p
op_add_assign
id|change_ldt
c_func
(paren
id|ex.a_text
comma
id|page
)paren
suffix:semicolon
id|p
op_sub_assign
id|LIBRARY_SIZE
op_plus
id|MAX_ARG_PAGES
op_star
id|PAGE_SIZE
suffix:semicolon
id|p
op_assign
(paren
r_int
r_int
)paren
id|create_tables
c_func
(paren
(paren
r_char
op_star
)paren
id|p
comma
id|argc
comma
id|envc
)paren
suffix:semicolon
id|current-&gt;brk
op_assign
id|ex.a_bss
op_plus
(paren
id|current-&gt;end_data
op_assign
id|ex.a_data
op_plus
(paren
id|current-&gt;end_code
op_assign
id|ex.a_text
)paren
)paren
suffix:semicolon
id|current-&gt;start_stack
op_assign
id|p
suffix:semicolon
id|current-&gt;rss
op_assign
(paren
id|LIBRARY_OFFSET
op_minus
id|p
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
id|current-&gt;suid
op_assign
id|current-&gt;euid
op_assign
id|e_uid
suffix:semicolon
id|current-&gt;sgid
op_assign
id|current-&gt;egid
op_assign
id|e_gid
suffix:semicolon
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
id|read_omagic
c_func
(paren
id|inode
comma
id|ex.a_text
op_plus
id|ex.a_data
)paren
suffix:semicolon
id|eip
(braket
l_int|0
)braket
op_assign
id|ex.a_entry
suffix:semicolon
multiline_comment|/* eip, magic happens :-) */
id|eip
(braket
l_int|3
)braket
op_assign
id|p
suffix:semicolon
multiline_comment|/* stack pointer */
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
id|exec_error2
suffix:colon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|exec_error1
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_ARG_PAGES
suffix:semicolon
id|i
op_increment
)paren
id|free_page
c_func
(paren
id|page
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
