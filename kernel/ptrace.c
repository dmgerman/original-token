multiline_comment|/* ptrace.c */
multiline_comment|/* By Ross Biro 1/23/92 */
multiline_comment|/* edited by Linus Torvalds */
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/ptrace.h&gt;
multiline_comment|/*&n; * does not yet catch signals sent when the child dies.&n; * in exit.c or in signal.c.&n; */
multiline_comment|/* determines which flags the user has access to. */
multiline_comment|/* 1 = access 0 = no access */
DECL|macro|FLAG_MASK
mdefine_line|#define FLAG_MASK 0x00000dd9
multiline_comment|/* set&squot;s the trap flag. */
DECL|macro|TRAP_FLAG
mdefine_line|#define TRAP_FLAG 0x100
multiline_comment|/*&n; * this is the number to subtract from the top of the stack. To find&n; * the local frame.&n; */
DECL|macro|MAGICNUMBER
mdefine_line|#define MAGICNUMBER 68
r_void
id|do_no_page
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|task_struct
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|write_verify
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* change a pid into a task struct. */
DECL|function|get_task
r_static
r_inline
r_struct
id|task_struct
op_star
id|get_task
c_func
(paren
r_int
id|pid
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|NR_TASKS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_ne
l_int|NULL
op_logical_and
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
op_eq
id|pid
)paren
)paren
r_return
id|task
(braket
id|i
)braket
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * this routine will get a word off of the processes priviledged stack. &n; * the offset is how far from the base addr as stored in the TSS.  &n; * this routine assumes that all the priviledged stacks are in our&n; * data space.&n; */
DECL|function|get_stack_long
r_static
r_inline
r_int
id|get_stack_long
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|offset
)paren
(brace
r_int
r_char
op_star
id|stack
suffix:semicolon
id|stack
op_assign
(paren
r_int
r_char
op_star
)paren
id|task-&gt;tss.esp0
suffix:semicolon
id|stack
op_add_assign
id|offset
suffix:semicolon
r_return
(paren
op_star
(paren
(paren
r_int
op_star
)paren
id|stack
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * this routine will put a word on the processes priviledged stack. &n; * the offset is how far from the base addr as stored in the TSS.  &n; * this routine assumes that all the priviledged stacks are in our&n; * data space.&n; */
DECL|function|put_stack_long
r_static
r_inline
r_int
id|put_stack_long
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|offset
comma
r_int
r_int
id|data
)paren
(brace
r_int
r_char
op_star
id|stack
suffix:semicolon
id|stack
op_assign
(paren
r_int
r_char
op_star
)paren
id|task-&gt;tss.esp0
suffix:semicolon
id|stack
op_add_assign
id|offset
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|stack
op_assign
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine gets a long from any process space by following the page&n; * tables. NOTE! You should check that the long isn&squot;t on a page boundary,&n; * and that it is in the task area before calling this: this routine does&n; * no checking.&n; *&n; * NOTE2! This uses &quot;tsk-&gt;tss.cr3&quot; even though we know it&squot;s currently always&n; * zero. This routine shouldn&squot;t have to change when we make a better mm.&n; */
DECL|function|get_long
r_static
r_int
r_int
id|get_long
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|page
suffix:semicolon
id|addr
op_add_assign
id|tsk-&gt;start_code
suffix:semicolon
id|repeat
suffix:colon
id|page
op_assign
id|tsk-&gt;tss.cr3
op_plus
(paren
(paren
id|addr
op_rshift
l_int|20
)paren
op_amp
l_int|0xffc
)paren
suffix:semicolon
id|page
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|page
suffix:semicolon
r_if
c_cond
(paren
id|page
op_amp
id|PAGE_PRESENT
)paren
(brace
id|page
op_and_assign
l_int|0xfffff000
suffix:semicolon
id|page
op_add_assign
(paren
id|addr
op_rshift
l_int|10
)paren
op_amp
l_int|0xffc
suffix:semicolon
id|page
op_assign
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|page
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_amp
id|PAGE_PRESENT
)paren
)paren
(brace
id|do_no_page
c_func
(paren
l_int|0
comma
id|addr
comma
id|tsk
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|page
op_and_assign
l_int|0xfffff000
suffix:semicolon
id|page
op_add_assign
id|addr
op_amp
l_int|0xfff
suffix:semicolon
r_return
op_star
(paren
r_int
r_int
op_star
)paren
id|page
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine puts a long into any process space by following the page&n; * tables. NOTE! You should check that the long isn&squot;t on a page boundary,&n; * and that it is in the task area before calling this: this routine does&n; * no checking.&n; */
DECL|function|put_long
r_static
r_void
id|put_long
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|data
)paren
(brace
r_int
r_int
id|page
suffix:semicolon
id|addr
op_add_assign
id|tsk-&gt;start_code
suffix:semicolon
id|repeat
suffix:colon
id|page
op_assign
id|tsk-&gt;tss.cr3
op_plus
(paren
(paren
id|addr
op_rshift
l_int|20
)paren
op_amp
l_int|0xffc
)paren
suffix:semicolon
id|page
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|page
suffix:semicolon
r_if
c_cond
(paren
id|page
op_amp
id|PAGE_PRESENT
)paren
(brace
id|page
op_and_assign
l_int|0xfffff000
suffix:semicolon
id|page
op_add_assign
(paren
id|addr
op_rshift
l_int|10
)paren
op_amp
l_int|0xffc
suffix:semicolon
id|page
op_assign
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|page
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_amp
id|PAGE_PRESENT
)paren
)paren
(brace
id|do_no_page
c_func
(paren
l_int|0
comma
id|addr
comma
id|tsk
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_amp
id|PAGE_RW
)paren
)paren
(brace
id|write_verify
c_func
(paren
id|addr
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|page
op_and_assign
l_int|0xfffff000
suffix:semicolon
id|page
op_add_assign
id|addr
op_amp
l_int|0xfff
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|page
op_assign
id|data
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine checks the page boundaries, and that the offset is&n; * within the task area. It then calls get_long() to read a long.&n; */
DECL|function|read_long
r_static
r_int
id|read_long
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|addr
comma
r_int
r_int
op_star
id|result
)paren
(brace
r_int
r_int
id|low
comma
id|high
suffix:semicolon
r_if
c_cond
(paren
id|addr
OG
id|TASK_SIZE
op_minus
l_int|4
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|0xfff
)paren
OG
id|PAGE_SIZE
op_minus
l_int|4
)paren
(brace
id|low
op_assign
id|get_long
c_func
(paren
id|tsk
comma
id|addr
op_amp
l_int|0xfffffffc
)paren
suffix:semicolon
id|high
op_assign
id|get_long
c_func
(paren
id|tsk
comma
(paren
id|addr
op_plus
l_int|4
)paren
op_amp
l_int|0xfffffffc
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|addr
op_amp
l_int|3
)paren
(brace
r_case
l_int|1
suffix:colon
id|low
op_rshift_assign
l_int|8
suffix:semicolon
id|low
op_or_assign
id|high
op_lshift
l_int|24
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|low
op_rshift_assign
l_int|16
suffix:semicolon
id|low
op_or_assign
id|high
op_lshift
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|low
op_rshift_assign
l_int|24
suffix:semicolon
id|low
op_or_assign
id|high
op_lshift
l_int|8
suffix:semicolon
r_break
suffix:semicolon
)brace
op_star
id|result
op_assign
id|low
suffix:semicolon
)brace
r_else
op_star
id|result
op_assign
id|get_long
c_func
(paren
id|tsk
comma
id|addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine checks the page boundaries, and that the offset is&n; * within the task area. It then calls put_long() to write a long.&n; */
DECL|function|write_long
r_static
r_int
id|write_long
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|data
)paren
(brace
r_int
r_int
id|low
comma
id|high
suffix:semicolon
r_if
c_cond
(paren
id|addr
OG
id|TASK_SIZE
op_minus
l_int|4
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|0xfff
)paren
OG
id|PAGE_SIZE
op_minus
l_int|4
)paren
(brace
id|low
op_assign
id|get_long
c_func
(paren
id|tsk
comma
id|addr
op_amp
l_int|0xfffffffc
)paren
suffix:semicolon
id|high
op_assign
id|get_long
c_func
(paren
id|tsk
comma
(paren
id|addr
op_plus
l_int|4
)paren
op_amp
l_int|0xfffffffc
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|addr
op_amp
l_int|3
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* shouldn&squot;t happen, but safety first */
id|low
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|low
op_and_assign
l_int|0x000000ff
suffix:semicolon
id|low
op_or_assign
id|data
op_lshift
l_int|8
suffix:semicolon
id|high
op_and_assign
l_int|0xffffff00
suffix:semicolon
id|high
op_or_assign
id|data
op_rshift
l_int|24
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|low
op_and_assign
l_int|0x0000ffff
suffix:semicolon
id|low
op_or_assign
id|data
op_lshift
l_int|16
suffix:semicolon
id|high
op_and_assign
l_int|0xffff0000
suffix:semicolon
id|high
op_or_assign
id|data
op_rshift
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|low
op_and_assign
l_int|0x00ffffff
suffix:semicolon
id|low
op_or_assign
id|data
op_lshift
l_int|24
suffix:semicolon
id|high
op_and_assign
l_int|0xff000000
suffix:semicolon
id|high
op_or_assign
id|data
op_rshift
l_int|8
suffix:semicolon
r_break
suffix:semicolon
)brace
id|put_long
c_func
(paren
id|tsk
comma
id|addr
op_amp
l_int|0xfffffffc
comma
id|low
)paren
suffix:semicolon
id|put_long
c_func
(paren
id|tsk
comma
(paren
id|addr
op_plus
l_int|4
)paren
op_amp
l_int|0xfffffffc
comma
id|high
)paren
suffix:semicolon
)brace
r_else
id|put_long
c_func
(paren
id|tsk
comma
id|addr
comma
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_ptrace
r_int
id|sys_ptrace
c_func
(paren
r_int
id|request
comma
r_int
id|pid
comma
r_int
id|addr
comma
r_int
id|data
)paren
(brace
r_struct
id|task_struct
op_star
id|child
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_TRACEME
)paren
(brace
multiline_comment|/* are we already being traced? */
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_PTRACED
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* set the ptrace bit in the proccess flags. */
id|current-&gt;flags
op_or_assign
id|PF_PTRACED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|child
op_assign
id|get_task
c_func
(paren
id|pid
)paren
)paren
)paren
r_return
op_minus
id|ESRCH
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_ATTACH
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|child
op_eq
id|current
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|current-&gt;dumpable
op_logical_or
(paren
id|current-&gt;uid
op_ne
id|child-&gt;euid
)paren
op_logical_or
(paren
id|current-&gt;gid
op_ne
id|child-&gt;egid
)paren
)paren
op_logical_and
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* the same process cannot be attached many times */
r_if
c_cond
(paren
id|child-&gt;flags
op_amp
id|PF_PTRACED
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|child-&gt;flags
op_or_assign
id|PF_PTRACED
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;p_pptr
op_ne
id|current
)paren
(brace
id|REMOVE_LINKS
c_func
(paren
id|child
)paren
suffix:semicolon
id|child-&gt;p_pptr
op_assign
id|current
suffix:semicolon
id|SET_LINKS
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
l_int|4
op_star
id|EFL
op_minus
id|MAGICNUMBER
)paren
op_or
id|TRAP_FLAG
suffix:semicolon
id|put_stack_long
c_func
(paren
id|child
comma
l_int|4
op_star
id|EFL
op_minus
id|MAGICNUMBER
comma
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;state
op_eq
id|TASK_INTERRUPTIBLE
op_logical_or
id|child-&gt;state
op_eq
id|TASK_STOPPED
)paren
id|child-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|child-&gt;signal
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|child-&gt;flags
op_amp
id|PF_PTRACED
)paren
op_logical_or
id|child-&gt;state
op_ne
id|TASK_STOPPED
)paren
r_return
op_minus
id|ESRCH
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;p_pptr
op_ne
id|current
)paren
r_return
op_minus
id|ESRCH
suffix:semicolon
r_switch
c_cond
(paren
id|request
)paren
(brace
multiline_comment|/* when I and D space are seperate, these will need to be fixed. */
r_case
id|PTRACE_PEEKTEXT
suffix:colon
multiline_comment|/* read word at location addr. */
r_case
id|PTRACE_PEEKDATA
suffix:colon
(brace
r_int
id|tmp
comma
id|res
suffix:semicolon
id|res
op_assign
id|read_long
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
r_return
id|res
suffix:semicolon
id|verify_area
c_func
(paren
(paren
r_void
op_star
)paren
id|data
comma
l_int|4
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|tmp
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* read the word at location addr in the USER area. */
r_case
id|PTRACE_PEEKUSR
suffix:colon
(brace
r_int
id|tmp
suffix:semicolon
id|addr
op_assign
id|addr
op_rshift
l_int|2
suffix:semicolon
multiline_comment|/* temporary hack. */
r_if
c_cond
(paren
id|addr
OL
l_int|0
op_logical_or
id|addr
op_ge
l_int|17
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|verify_area
c_func
(paren
(paren
r_void
op_star
)paren
id|data
comma
l_int|4
)paren
suffix:semicolon
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
l_int|4
op_star
id|addr
op_minus
id|MAGICNUMBER
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|tmp
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* when I and D space are seperate, this will have to be fixed. */
r_case
id|PTRACE_POKETEXT
suffix:colon
multiline_comment|/* write the word at location addr. */
r_case
id|PTRACE_POKEDATA
suffix:colon
r_return
id|write_long
c_func
(paren
id|child
comma
id|addr
comma
id|data
)paren
suffix:semicolon
r_case
id|PTRACE_POKEUSR
suffix:colon
multiline_comment|/* write the word at location addr in the USER area */
id|addr
op_assign
id|addr
op_rshift
l_int|2
suffix:semicolon
multiline_comment|/* temproary hack. */
r_if
c_cond
(paren
id|addr
OL
l_int|0
op_logical_or
id|addr
op_ge
l_int|17
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
id|ORIG_EAX
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
id|EFL
)paren
(brace
multiline_comment|/* flags. */
id|data
op_and_assign
id|FLAG_MASK
suffix:semicolon
id|data
op_or_assign
id|get_stack_long
c_func
(paren
id|child
comma
id|EFL
op_star
l_int|4
op_minus
id|MAGICNUMBER
)paren
op_amp
op_complement
id|FLAG_MASK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|put_stack_long
c_func
(paren
id|child
comma
l_int|4
op_star
id|addr
op_minus
id|MAGICNUMBER
comma
id|data
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PTRACE_CONT
suffix:colon
(brace
multiline_comment|/* restart after signal. */
r_int
id|tmp
suffix:semicolon
id|child-&gt;signal
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|data
OG
l_int|0
op_logical_and
id|data
op_le
id|NSIG
)paren
id|child-&gt;signal
op_assign
l_int|1
op_lshift
(paren
id|data
op_minus
l_int|1
)paren
suffix:semicolon
id|child-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
multiline_comment|/* make sure the single step bit is not set. */
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
l_int|4
op_star
id|EFL
op_minus
id|MAGICNUMBER
)paren
op_amp
op_complement
id|TRAP_FLAG
suffix:semicolon
id|put_stack_long
c_func
(paren
id|child
comma
l_int|4
op_star
id|EFL
op_minus
id|MAGICNUMBER
comma
id|tmp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * make the child exit.  Best I can do is send it a sigkill. &n; * perhaps it should be put in the status that it want&squot;s to &n; * exit.&n; */
r_case
id|PTRACE_KILL
suffix:colon
(brace
r_int
id|tmp
suffix:semicolon
id|child-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|child-&gt;signal
op_assign
l_int|1
op_lshift
(paren
id|SIGKILL
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* make sure the single step bit is not set. */
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
l_int|4
op_star
id|EFL
op_minus
id|MAGICNUMBER
)paren
op_amp
op_complement
id|TRAP_FLAG
suffix:semicolon
id|put_stack_long
c_func
(paren
id|child
comma
l_int|4
op_star
id|EFL
op_minus
id|MAGICNUMBER
comma
id|tmp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|PTRACE_SINGLESTEP
suffix:colon
(brace
multiline_comment|/* set the trap flag. */
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
l_int|4
op_star
id|EFL
op_minus
id|MAGICNUMBER
)paren
op_or
id|TRAP_FLAG
suffix:semicolon
id|put_stack_long
c_func
(paren
id|child
comma
l_int|4
op_star
id|EFL
op_minus
id|MAGICNUMBER
comma
id|tmp
)paren
suffix:semicolon
id|child-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|child-&gt;signal
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|data
OG
l_int|0
op_logical_and
id|data
op_le
id|NSIG
)paren
id|child-&gt;signal
op_assign
l_int|1
op_lshift
(paren
id|data
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* give it a chance to run. */
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|PTRACE_DETACH
suffix:colon
(brace
multiline_comment|/* detach a process that was attached. */
r_int
id|tmp
suffix:semicolon
id|child-&gt;flags
op_and_assign
op_complement
id|PF_PTRACED
suffix:semicolon
id|child-&gt;signal
op_assign
l_int|0
suffix:semicolon
id|child-&gt;state
op_assign
l_int|0
suffix:semicolon
id|REMOVE_LINKS
c_func
(paren
id|child
)paren
suffix:semicolon
id|child-&gt;p_pptr
op_assign
id|child-&gt;p_opptr
suffix:semicolon
id|SET_LINKS
c_func
(paren
id|child
)paren
suffix:semicolon
multiline_comment|/* make sure the single step bit is not set. */
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
l_int|4
op_star
id|EFL
op_minus
id|MAGICNUMBER
)paren
op_amp
op_complement
id|TRAP_FLAG
suffix:semicolon
id|put_stack_long
c_func
(paren
id|child
comma
l_int|4
op_star
id|EFL
op_minus
id|MAGICNUMBER
comma
id|tmp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
eof
