multiline_comment|/*&n; *  linux/kernel/fork.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; *  &squot;fork.c&squot; contains the help-routines for the &squot;fork&squot; system call&n; * (see also system_call.s).&n; * Fork is rather simple, once you get the hang of it, but the memory&n; * management can be a bitch. See &squot;mm/mm.c&squot;: &squot;copy_page_tables()&squot;&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ldt.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|variable|nr_tasks
r_int
id|nr_tasks
op_assign
l_int|1
suffix:semicolon
DECL|variable|nr_running
r_int
id|nr_running
op_assign
l_int|1
suffix:semicolon
DECL|variable|last_pid
r_int
id|last_pid
op_assign
l_int|0
suffix:semicolon
DECL|function|find_empty_process
r_static
r_int
id|find_empty_process
c_func
(paren
r_void
)paren
(brace
r_int
id|free_task
suffix:semicolon
r_int
id|i
comma
id|tasks_free
suffix:semicolon
r_int
id|this_user_tasks
suffix:semicolon
id|repeat
suffix:colon
r_if
c_cond
(paren
(paren
op_increment
id|last_pid
)paren
op_amp
l_int|0xffff8000
)paren
id|last_pid
op_assign
l_int|1
suffix:semicolon
id|this_user_tasks
op_assign
l_int|0
suffix:semicolon
id|tasks_free
op_assign
l_int|0
suffix:semicolon
id|free_task
op_assign
op_minus
id|EAGAIN
suffix:semicolon
id|i
op_assign
id|NR_TASKS
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|i
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|task
(braket
id|i
)braket
)paren
(brace
id|free_task
op_assign
id|i
suffix:semicolon
id|tasks_free
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|uid
op_eq
id|current-&gt;uid
)paren
id|this_user_tasks
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
op_eq
id|last_pid
op_logical_or
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pgrp
op_eq
id|last_pid
op_logical_or
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|session
op_eq
id|last_pid
)paren
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tasks_free
op_le
id|MIN_TASKS_LEFT_FOR_ROOT
op_logical_or
id|this_user_tasks
OG
id|current-&gt;rlim
(braket
id|RLIMIT_NPROC
)braket
dot
id|rlim_cur
)paren
r_if
c_cond
(paren
id|current-&gt;uid
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_return
id|free_task
suffix:semicolon
)brace
DECL|function|copy_fd
r_static
r_struct
id|file
op_star
id|copy_fd
c_func
(paren
r_struct
id|file
op_star
id|old_file
)paren
(brace
r_struct
id|file
op_star
id|new_file
op_assign
id|get_empty_filp
c_func
(paren
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|new_file
)paren
(brace
id|memcpy
c_func
(paren
id|new_file
comma
id|old_file
comma
r_sizeof
(paren
r_struct
id|file
)paren
)paren
suffix:semicolon
id|new_file-&gt;f_count
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|new_file-&gt;f_inode
)paren
id|new_file-&gt;f_inode-&gt;i_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|new_file-&gt;f_op
op_logical_and
id|new_file-&gt;f_op-&gt;open
)paren
(brace
id|error
op_assign
id|new_file-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|new_file-&gt;f_inode
comma
id|new_file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|iput
c_func
(paren
id|new_file-&gt;f_inode
)paren
suffix:semicolon
id|new_file-&gt;f_count
op_assign
l_int|0
suffix:semicolon
id|new_file
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
r_return
id|new_file
suffix:semicolon
)brace
DECL|function|dup_mmap
r_static
r_int
id|dup_mmap
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|mpnt
comma
op_star
op_star
id|p
comma
op_star
id|tmp
suffix:semicolon
id|tsk-&gt;mm-&gt;mmap
op_assign
l_int|NULL
suffix:semicolon
id|p
op_assign
op_amp
id|tsk-&gt;mm-&gt;mmap
suffix:semicolon
r_for
c_loop
(paren
id|mpnt
op_assign
id|current-&gt;mm-&gt;mmap
suffix:semicolon
id|mpnt
suffix:semicolon
id|mpnt
op_assign
id|mpnt-&gt;vm_next
)paren
(brace
id|tmp
op_assign
(paren
r_struct
id|vm_area_struct
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|vm_area_struct
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
id|exit_mmap
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
op_star
id|tmp
op_assign
op_star
id|mpnt
suffix:semicolon
id|tmp-&gt;vm_task
op_assign
id|tsk
suffix:semicolon
id|tmp-&gt;vm_next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;vm_inode
)paren
(brace
id|tmp-&gt;vm_inode-&gt;i_count
op_increment
suffix:semicolon
multiline_comment|/* insert tmp into the share list, just after mpnt */
id|tmp-&gt;vm_next_share-&gt;vm_prev_share
op_assign
id|tmp
suffix:semicolon
id|mpnt-&gt;vm_next_share
op_assign
id|tmp
suffix:semicolon
id|tmp-&gt;vm_prev_share
op_assign
id|mpnt
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tmp-&gt;vm_ops
op_logical_and
id|tmp-&gt;vm_ops-&gt;open
)paren
id|tmp-&gt;vm_ops
op_member_access_from_pointer
id|open
c_func
(paren
id|tmp
)paren
suffix:semicolon
op_star
id|p
op_assign
id|tmp
suffix:semicolon
id|p
op_assign
op_amp
id|tmp-&gt;vm_next
suffix:semicolon
)brace
id|build_mmap_avl
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * SHAREFD not yet implemented..&n; */
DECL|function|copy_files
r_static
r_void
id|copy_files
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|file
op_star
id|f
suffix:semicolon
r_if
c_cond
(paren
id|clone_flags
op_amp
id|COPYFD
)paren
(brace
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
id|f
op_assign
id|p-&gt;files-&gt;fd
(braket
id|i
)braket
)paren
op_ne
l_int|NULL
)paren
id|p-&gt;files-&gt;fd
(braket
id|i
)braket
op_assign
id|copy_fd
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
r_else
(brace
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
id|f
op_assign
id|p-&gt;files-&gt;fd
(braket
id|i
)braket
)paren
op_ne
l_int|NULL
)paren
id|f-&gt;f_count
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * CLONEVM not yet correctly implemented: needs to clone the mmap&n; * instead of duplicating it..&n; */
DECL|function|copy_mm
r_static
r_int
id|copy_mm
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|clone_flags
op_amp
id|COPYVM
)paren
(brace
id|p-&gt;mm-&gt;min_flt
op_assign
id|p-&gt;mm-&gt;maj_flt
op_assign
l_int|0
suffix:semicolon
id|p-&gt;mm-&gt;cmin_flt
op_assign
id|p-&gt;mm-&gt;cmaj_flt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_page_tables
c_func
(paren
id|p
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|dup_mmap
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|clone_page_tables
c_func
(paren
id|p
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|dup_mmap
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* wrong.. */
)brace
)brace
DECL|function|copy_fs
r_static
r_void
id|copy_fs
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;fs-&gt;pwd
)paren
id|current-&gt;fs-&gt;pwd-&gt;i_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;fs-&gt;root
)paren
id|current-&gt;fs-&gt;root-&gt;i_count
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n; *  Ok, this is the main fork-routine. It copies the system process&n; * information (task[nr]) and sets up the necessary registers. It&n; * also copies the data segment in its entirety.&n; */
DECL|function|do_fork
r_int
id|do_fork
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|usp
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|nr
suffix:semicolon
r_int
r_int
id|new_stack
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
(paren
r_struct
id|task_struct
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
(brace
r_goto
id|bad_fork
suffix:semicolon
)brace
id|new_stack
op_assign
id|get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_stack
)paren
r_goto
id|bad_fork_free
suffix:semicolon
id|nr
op_assign
id|find_empty_process
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
l_int|0
)paren
r_goto
id|bad_fork_free
suffix:semicolon
op_star
id|p
op_assign
op_star
id|current
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;exec_domain
op_logical_and
id|p-&gt;exec_domain-&gt;use_count
)paren
(paren
op_star
id|p-&gt;exec_domain-&gt;use_count
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;binfmt
op_logical_and
id|p-&gt;binfmt-&gt;use_count
)paren
(paren
op_star
id|p-&gt;binfmt-&gt;use_count
)paren
op_increment
suffix:semicolon
id|p-&gt;did_exec
op_assign
l_int|0
suffix:semicolon
id|p-&gt;kernel_stack_page
op_assign
id|new_stack
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|p-&gt;kernel_stack_page
op_assign
id|STACK_MAGIC
suffix:semicolon
id|p-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|p-&gt;flags
op_and_assign
op_complement
(paren
id|PF_PTRACED
op_or
id|PF_TRACESYS
)paren
suffix:semicolon
id|p-&gt;pid
op_assign
id|last_pid
suffix:semicolon
id|p-&gt;next_run
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;prev_run
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;p_pptr
op_assign
id|p-&gt;p_opptr
op_assign
id|current
suffix:semicolon
id|p-&gt;p_cptr
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;signal
op_assign
l_int|0
suffix:semicolon
id|p-&gt;it_real_value
op_assign
id|p-&gt;it_virt_value
op_assign
id|p-&gt;it_prof_value
op_assign
l_int|0
suffix:semicolon
id|p-&gt;it_real_incr
op_assign
id|p-&gt;it_virt_incr
op_assign
id|p-&gt;it_prof_incr
op_assign
l_int|0
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|p-&gt;real_timer
)paren
suffix:semicolon
id|p-&gt;real_timer.data
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|p-&gt;leader
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* process leadership doesn&squot;t inherit */
id|p-&gt;tty_old_pgrp
op_assign
l_int|0
suffix:semicolon
id|p-&gt;utime
op_assign
id|p-&gt;stime
op_assign
l_int|0
suffix:semicolon
id|p-&gt;cutime
op_assign
id|p-&gt;cstime
op_assign
l_int|0
suffix:semicolon
id|p-&gt;start_time
op_assign
id|jiffies
suffix:semicolon
id|p-&gt;mm-&gt;swappable
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* don&squot;t try to swap it out before it&squot;s set up */
id|task
(braket
id|nr
)braket
op_assign
id|p
suffix:semicolon
id|SET_LINKS
c_func
(paren
id|p
)paren
suffix:semicolon
id|nr_tasks
op_increment
suffix:semicolon
multiline_comment|/* copy all the process information */
id|copy_thread
c_func
(paren
id|nr
comma
id|clone_flags
comma
id|usp
comma
id|p
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_mm
c_func
(paren
id|clone_flags
comma
id|p
)paren
)paren
r_goto
id|bad_fork_cleanup
suffix:semicolon
id|p-&gt;semundo
op_assign
l_int|NULL
suffix:semicolon
id|copy_files
c_func
(paren
id|clone_flags
comma
id|p
)paren
suffix:semicolon
id|copy_fs
c_func
(paren
id|clone_flags
comma
id|p
)paren
suffix:semicolon
multiline_comment|/* ok, now we should be set up.. */
id|p-&gt;mm-&gt;swappable
op_assign
l_int|1
suffix:semicolon
id|p-&gt;exit_signal
op_assign
id|clone_flags
op_amp
id|CSIGNAL
suffix:semicolon
id|p-&gt;counter
op_assign
id|current-&gt;counter
op_rshift
l_int|1
suffix:semicolon
id|wake_up_process
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* do this last, just in case */
r_return
id|p-&gt;pid
suffix:semicolon
id|bad_fork_cleanup
suffix:colon
id|task
(braket
id|nr
)braket
op_assign
l_int|NULL
suffix:semicolon
id|REMOVE_LINKS
c_func
(paren
id|p
)paren
suffix:semicolon
id|nr_tasks
op_decrement
suffix:semicolon
id|bad_fork_free
suffix:colon
id|free_page
c_func
(paren
id|new_stack
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
)paren
id|p
)paren
suffix:semicolon
id|bad_fork
suffix:colon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
eof
