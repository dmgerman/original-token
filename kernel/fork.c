multiline_comment|/*&n; *  linux/kernel/fork.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; *  &squot;fork.c&squot; contains the help-routines for the &squot;fork&squot; system call&n; * (see also system_call.s).&n; * Fork is rather simple, once you get the hang of it, but the memory&n; * management can be a bitch. See &squot;mm/mm.c&squot;: &squot;copy_page_tables()&squot;&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/segment.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ldt.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
id|asmlinkage
r_void
id|ret_from_sys_call
c_func
(paren
r_void
)paren
id|__asm__
c_func
(paren
l_string|&quot;ret_from_sys_call&quot;
)paren
suffix:semicolon
multiline_comment|/* These should maybe be in &lt;linux/tasks.h&gt; */
DECL|macro|MAX_TASKS_PER_USER
mdefine_line|#define MAX_TASKS_PER_USER (NR_TASKS/2)
DECL|macro|MIN_TASKS_LEFT_FOR_ROOT
mdefine_line|#define MIN_TASKS_LEFT_FOR_ROOT 4
r_extern
r_int
id|shm_fork
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_struct
id|task_struct
op_star
)paren
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
id|MAX_TASKS_PER_USER
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
id|tsk-&gt;mmap
op_assign
l_int|NULL
suffix:semicolon
id|tsk-&gt;stk_vma
op_assign
l_int|NULL
suffix:semicolon
id|p
op_assign
op_amp
id|tsk-&gt;mmap
suffix:semicolon
r_for
c_loop
(paren
id|mpnt
op_assign
id|current-&gt;mmap
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
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
id|tmp-&gt;vm_inode-&gt;i_count
op_increment
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
r_if
c_cond
(paren
id|current-&gt;stk_vma
op_eq
id|mpnt
)paren
id|tsk-&gt;stk_vma
op_assign
id|tmp
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|IS_CLONE
mdefine_line|#define IS_CLONE (regs.orig_eax == __NR_clone)
DECL|macro|copy_vm
mdefine_line|#define copy_vm(p) ((clone_flags &amp; COPYVM)?copy_page_tables(p):clone_page_tables(p))
multiline_comment|/*&n; *  Ok, this is the main fork-routine. It copies the system process&n; * information (task[nr]) and sets up the necessary registers. It&n; * also copies the data segment in its entirety.&n; */
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
r_struct
id|pt_regs
op_star
id|childregs
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|i
comma
id|nr
suffix:semicolon
r_struct
id|file
op_star
id|f
suffix:semicolon
r_int
r_int
id|clone_flags
op_assign
id|COPYVM
op_or
id|SIGCHLD
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
id|task
(braket
id|nr
)braket
op_assign
id|p
suffix:semicolon
op_star
id|p
op_assign
op_star
id|current
suffix:semicolon
id|p-&gt;did_exec
op_assign
l_int|0
suffix:semicolon
id|p-&gt;kernel_stack_page
op_assign
l_int|0
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
id|p-&gt;swappable
op_assign
l_int|1
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
id|SET_LINKS
c_func
(paren
id|p
)paren
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
id|p-&gt;leader
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* process leadership doesn&squot;t inherit */
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
id|p-&gt;min_flt
op_assign
id|p-&gt;maj_flt
op_assign
l_int|0
suffix:semicolon
id|p-&gt;cmin_flt
op_assign
id|p-&gt;cmaj_flt
op_assign
l_int|0
suffix:semicolon
id|p-&gt;start_time
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/*&n; * set up new TSS and kernel stack&n; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|p-&gt;kernel_stack_page
op_assign
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
r_goto
id|bad_fork_cleanup
suffix:semicolon
id|p-&gt;tss.es
op_assign
id|KERNEL_DS
suffix:semicolon
id|p-&gt;tss.cs
op_assign
id|KERNEL_CS
suffix:semicolon
id|p-&gt;tss.ss
op_assign
id|KERNEL_DS
suffix:semicolon
id|p-&gt;tss.ds
op_assign
id|KERNEL_DS
suffix:semicolon
id|p-&gt;tss.fs
op_assign
id|USER_DS
suffix:semicolon
id|p-&gt;tss.gs
op_assign
id|KERNEL_DS
suffix:semicolon
id|p-&gt;tss.ss0
op_assign
id|KERNEL_DS
suffix:semicolon
id|p-&gt;tss.esp0
op_assign
id|p-&gt;kernel_stack_page
op_plus
id|PAGE_SIZE
suffix:semicolon
id|p-&gt;tss.tr
op_assign
id|_TSS
c_func
(paren
id|nr
)paren
suffix:semicolon
id|childregs
op_assign
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|p-&gt;kernel_stack_page
op_plus
id|PAGE_SIZE
)paren
)paren
op_minus
l_int|1
suffix:semicolon
id|p-&gt;tss.esp
op_assign
(paren
r_int
r_int
)paren
id|childregs
suffix:semicolon
id|p-&gt;tss.eip
op_assign
(paren
r_int
r_int
)paren
id|ret_from_sys_call
suffix:semicolon
op_star
id|childregs
op_assign
id|regs
suffix:semicolon
id|childregs-&gt;eax
op_assign
l_int|0
suffix:semicolon
id|p-&gt;tss.back_link
op_assign
l_int|0
suffix:semicolon
id|p-&gt;tss.eflags
op_assign
id|regs.eflags
op_amp
l_int|0xffffcfff
suffix:semicolon
multiline_comment|/* iopl is always 0 for a new process */
r_if
c_cond
(paren
id|IS_CLONE
)paren
(brace
r_if
c_cond
(paren
id|regs.ebx
)paren
id|childregs-&gt;esp
op_assign
id|regs.ebx
suffix:semicolon
id|clone_flags
op_assign
id|regs.ecx
suffix:semicolon
r_if
c_cond
(paren
id|childregs-&gt;esp
op_eq
id|regs.esp
)paren
id|clone_flags
op_or_assign
id|COPYVM
suffix:semicolon
)brace
id|p-&gt;exit_signal
op_assign
id|clone_flags
op_amp
id|CSIGNAL
suffix:semicolon
id|p-&gt;tss.ldt
op_assign
id|_LDT
c_func
(paren
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;ldt
)paren
(brace
id|p-&gt;ldt
op_assign
(paren
r_struct
id|desc_struct
op_star
)paren
id|vmalloc
c_func
(paren
id|LDT_ENTRIES
op_star
id|LDT_ENTRY_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;ldt
op_ne
l_int|NULL
)paren
id|memcpy
c_func
(paren
id|p-&gt;ldt
comma
id|current-&gt;ldt
comma
id|LDT_ENTRIES
op_star
id|LDT_ENTRY_SIZE
)paren
suffix:semicolon
)brace
id|p-&gt;tss.bitmap
op_assign
m_offsetof
(paren
r_struct
id|tss_struct
comma
id|io_bitmap
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
id|IO_BITMAP_SIZE
op_plus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* IO bitmap is actually SIZE+1 */
id|p-&gt;tss.io_bitmap
(braket
id|i
)braket
op_assign
op_complement
l_int|0
suffix:semicolon
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
l_string|&quot;clts ; fnsave %0 ; frstor %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|p-&gt;tss.i387
)paren
)paren
suffix:semicolon
id|p-&gt;semun
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;shm
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|copy_vm
c_func
(paren
id|p
)paren
op_logical_or
id|shm_fork
c_func
(paren
id|current
comma
id|p
)paren
)paren
r_goto
id|bad_fork_cleanup
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
id|p-&gt;filp
(braket
id|i
)braket
)paren
op_ne
l_int|NULL
)paren
id|p-&gt;filp
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
id|p-&gt;filp
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
r_if
c_cond
(paren
id|current-&gt;pwd
)paren
id|current-&gt;pwd-&gt;i_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;root
)paren
id|current-&gt;root-&gt;i_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;executable
)paren
id|current-&gt;executable-&gt;i_count
op_increment
suffix:semicolon
id|dup_mmap
c_func
(paren
id|p
)paren
suffix:semicolon
id|set_tss_desc
c_func
(paren
id|gdt
op_plus
(paren
id|nr
op_lshift
l_int|1
)paren
op_plus
id|FIRST_TSS_ENTRY
comma
op_amp
(paren
id|p-&gt;tss
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;ldt
)paren
id|set_ldt_desc
c_func
(paren
id|gdt
op_plus
(paren
id|nr
op_lshift
l_int|1
)paren
op_plus
id|FIRST_LDT_ENTRY
comma
id|p-&gt;ldt
comma
l_int|512
)paren
suffix:semicolon
r_else
id|set_ldt_desc
c_func
(paren
id|gdt
op_plus
(paren
id|nr
op_lshift
l_int|1
)paren
op_plus
id|FIRST_LDT_ENTRY
comma
op_amp
id|default_ldt
comma
l_int|1
)paren
suffix:semicolon
id|p-&gt;counter
op_assign
id|current-&gt;counter
op_rshift
l_int|1
suffix:semicolon
id|p-&gt;state
op_assign
id|TASK_RUNNING
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
id|free_page
c_func
(paren
id|p-&gt;kernel_stack_page
)paren
suffix:semicolon
id|bad_fork_free
suffix:colon
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
