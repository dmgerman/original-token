multiline_comment|/* ptrace.c */
multiline_comment|/* By Ross Biro 1/23/92 */
multiline_comment|/* edited by Linus Torvalds */
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#if 0
multiline_comment|/*&n; * does not yet catch signals sent when the child dies.&n; * in exit.c or in signal.c.&n; */
multiline_comment|/* determines which flags the user has access to. */
multiline_comment|/* 1 = access 0 = no access */
mdefine_line|#define FLAG_MASK 0x00044dd5
multiline_comment|/* set&squot;s the trap flag. */
mdefine_line|#define TRAP_FLAG 0x100
multiline_comment|/*&n; * this is the number to subtract from the top of the stack. To find&n; * the local frame.&n; */
mdefine_line|#define MAGICNUMBER 68
multiline_comment|/* change a pid into a task struct. */
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
multiline_comment|/*&n; * this routine will get a word off of the processes privileged stack. &n; * the offset is how far from the base addr as stored in the TSS.  &n; * this routine assumes that all the privileged stacks are in our&n; * data space.&n; */
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
multiline_comment|/*&n; * this routine will put a word on the processes privileged stack. &n; * the offset is how far from the base addr as stored in the TSS.  &n; * this routine assumes that all the privileged stacks are in our&n; * data space.&n; */
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
multiline_comment|/*&n; * This routine gets a long from any process space by following the page&n; * tables. NOTE! You should check that the long isn&squot;t on a page boundary,&n; * and that it is in the task area before calling this: this routine does&n; * no checking.&n; */
r_static
r_int
r_int
id|get_long
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
)paren
(brace
id|pgd_t
op_star
id|pgdir
suffix:semicolon
id|pte_t
op_star
id|pgtable
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
id|repeat
suffix:colon
id|pgdir
op_assign
id|PAGE_DIR_OFFSET
c_func
(paren
id|vma-&gt;vm_mm
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgdir
)paren
)paren
(brace
id|do_no_page
c_func
(paren
id|vma
comma
id|addr
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
id|pgd_bad
c_func
(paren
op_star
id|pgdir
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ptrace: bad page directory %08lx&bslash;n&quot;
comma
id|pgd_val
c_func
(paren
op_star
id|pgdir
)paren
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|pgdir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pgtable
op_assign
(paren
id|pte_t
op_star
)paren
(paren
id|PAGE_PTR
c_func
(paren
id|addr
)paren
op_plus
id|pgd_page
c_func
(paren
op_star
id|pgdir
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
op_star
id|pgtable
)paren
)paren
(brace
id|do_no_page
c_func
(paren
id|vma
comma
id|addr
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|page
op_assign
id|pte_page
c_func
(paren
op_star
id|pgtable
)paren
suffix:semicolon
multiline_comment|/* this is a hack for non-kernel-mapped video buffers and similar */
r_if
c_cond
(paren
id|page
op_ge
id|high_memory
)paren
r_return
l_int|0
suffix:semicolon
id|page
op_add_assign
id|addr
op_amp
op_complement
id|PAGE_MASK
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
multiline_comment|/*&n; * This routine puts a long into any process space by following the page&n; * tables. NOTE! You should check that the long isn&squot;t on a page boundary,&n; * and that it is in the task area before calling this: this routine does&n; * no checking.&n; *&n; * Now keeps R/W state of page so that a text page stays readonly&n; * even if a debugger scribbles breakpoints into it.  -M.U-&n; */
r_static
r_void
id|put_long
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
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
id|pgd_t
op_star
id|pgdir
suffix:semicolon
id|pte_t
op_star
id|pgtable
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
id|repeat
suffix:colon
id|pgdir
op_assign
id|PAGE_DIR_OFFSET
c_func
(paren
id|vma-&gt;vm_mm
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd_present
c_func
(paren
op_star
id|pgdir
)paren
)paren
(brace
id|do_no_page
c_func
(paren
id|vma
comma
id|addr
comma
l_int|1
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|pgdir
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ptrace: bad page directory %08lx&bslash;n&quot;
comma
id|pgd_val
c_func
(paren
op_star
id|pgdir
)paren
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|pgdir
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pgtable
op_assign
(paren
id|pte_t
op_star
)paren
(paren
id|PAGE_PTR
c_func
(paren
id|addr
)paren
op_plus
id|pgd_page
c_func
(paren
op_star
id|pgdir
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
op_star
id|pgtable
)paren
)paren
(brace
id|do_no_page
c_func
(paren
id|vma
comma
id|addr
comma
l_int|1
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|page
op_assign
id|pte_page
c_func
(paren
op_star
id|pgtable
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_write
c_func
(paren
op_star
id|pgtable
)paren
)paren
(brace
id|do_wp_page
c_func
(paren
id|vma
comma
id|addr
comma
l_int|1
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
multiline_comment|/* this is a hack for non-kernel-mapped video buffers and similar */
r_if
c_cond
(paren
id|page
OL
id|high_memory
)paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|page
op_plus
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
)paren
op_assign
id|data
suffix:semicolon
multiline_comment|/* we&squot;re bypassing pagetables, so we have to set the dirty bit ourselves */
multiline_comment|/* this should also re-instate whatever read-only mode there was before */
id|set_pte
c_func
(paren
id|pgtable
comma
id|pte_mkdirty
c_func
(paren
id|mk_pte
c_func
(paren
id|page
comma
id|vma-&gt;vm_page_prot
)paren
)paren
)paren
suffix:semicolon
id|invalidate
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_struct
id|vm_area_struct
op_star
id|find_extend_vma
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
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
id|addr
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|vma
op_assign
id|find_vma
c_func
(paren
id|tsk
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_start
op_le
id|addr
)paren
r_return
id|vma
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_GROWSDOWN
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_end
op_minus
id|addr
OG
id|tsk-&gt;rlim
(braket
id|RLIMIT_STACK
)braket
dot
id|rlim_cur
)paren
r_return
l_int|NULL
suffix:semicolon
id|vma-&gt;vm_offset
op_sub_assign
id|vma-&gt;vm_start
op_minus
id|addr
suffix:semicolon
id|vma-&gt;vm_start
op_assign
id|addr
suffix:semicolon
r_return
id|vma
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine checks the page boundaries, and that the offset is&n; * within the task area. It then calls get_long() to read a long.&n; */
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
r_struct
id|vm_area_struct
op_star
id|vma
op_assign
id|find_extend_vma
c_func
(paren
id|tsk
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
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
op_complement
id|PAGE_MASK
)paren
OG
id|PAGE_SIZE
op_minus
r_sizeof
(paren
r_int
)paren
)paren
(brace
r_int
r_int
id|low
comma
id|high
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma_high
op_assign
id|vma
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_plus
r_sizeof
(paren
r_int
)paren
op_ge
id|vma-&gt;vm_end
)paren
(brace
id|vma_high
op_assign
id|vma-&gt;vm_next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma_high
op_logical_or
id|vma_high-&gt;vm_start
op_ne
id|vma-&gt;vm_end
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|low
op_assign
id|get_long
c_func
(paren
id|vma
comma
id|addr
op_amp
op_complement
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|high
op_assign
id|get_long
c_func
(paren
id|vma_high
comma
(paren
id|addr
op_plus
r_sizeof
(paren
r_int
)paren
)paren
op_amp
op_complement
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|addr
op_amp
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
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
id|vma
comma
id|addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine checks the page boundaries, and that the offset is&n; * within the task area. It then calls put_long() to write a long.&n; */
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
r_struct
id|vm_area_struct
op_star
id|vma
op_assign
id|find_extend_vma
c_func
(paren
id|tsk
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
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
op_complement
id|PAGE_MASK
)paren
OG
id|PAGE_SIZE
op_minus
r_sizeof
(paren
r_int
)paren
)paren
(brace
r_int
r_int
id|low
comma
id|high
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma_high
op_assign
id|vma
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_plus
r_sizeof
(paren
r_int
)paren
op_ge
id|vma-&gt;vm_end
)paren
(brace
id|vma_high
op_assign
id|vma-&gt;vm_next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma_high
op_logical_or
id|vma_high-&gt;vm_start
op_ne
id|vma-&gt;vm_end
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|low
op_assign
id|get_long
c_func
(paren
id|vma
comma
id|addr
op_amp
op_complement
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|high
op_assign
id|get_long
c_func
(paren
id|vma_high
comma
(paren
id|addr
op_plus
r_sizeof
(paren
r_int
)paren
)paren
op_amp
op_complement
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|addr
op_amp
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
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
op_complement
l_int|0xff
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
op_complement
l_int|0xffff
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
op_complement
l_int|0xffffff
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
id|vma
comma
id|addr
op_amp
op_complement
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
comma
id|low
)paren
suffix:semicolon
id|put_long
c_func
(paren
id|vma_high
comma
(paren
id|addr
op_plus
r_sizeof
(paren
r_int
)paren
)paren
op_amp
op_complement
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
comma
id|high
)paren
suffix:semicolon
)brace
r_else
id|put_long
c_func
(paren
id|vma
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
macro_line|#endif
DECL|function|sys_ptrace
id|asmlinkage
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
macro_line|#if 1
r_return
op_minus
id|ENOSYS
suffix:semicolon
macro_line|#else
r_struct
id|task_struct
op_star
id|child
suffix:semicolon
r_struct
id|user
op_star
id|dummy
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dummy
op_assign
l_int|NULL
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
multiline_comment|/* set the ptrace bit in the process flags. */
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
id|pid
op_eq
l_int|1
)paren
multiline_comment|/* you may not mess with init */
r_return
op_minus
id|EPERM
suffix:semicolon
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
id|child-&gt;dumpable
op_logical_or
(paren
id|current-&gt;uid
op_ne
id|child-&gt;euid
)paren
op_logical_or
(paren
id|current-&gt;uid
op_ne
id|child-&gt;uid
)paren
op_logical_or
(paren
id|current-&gt;gid
op_ne
id|child-&gt;egid
)paren
op_logical_or
(paren
id|current-&gt;gid
op_ne
id|child-&gt;gid
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
id|send_sig
c_func
(paren
id|SIGSTOP
comma
id|child
comma
l_int|1
)paren
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
)paren
r_return
op_minus
id|ESRCH
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;state
op_ne
id|TASK_STOPPED
)paren
(brace
r_if
c_cond
(paren
id|request
op_ne
id|PTRACE_KILL
)paren
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
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
multiline_comment|/* when I and D space are separate, these will need to be fixed. */
r_case
id|PTRACE_PEEKTEXT
suffix:colon
multiline_comment|/* read word at location addr. */
r_case
id|PTRACE_PEEKDATA
suffix:colon
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_int
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
id|res
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|data
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
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
id|res
suffix:semicolon
)brace
multiline_comment|/* read the word at location addr in the USER area. */
r_case
id|PTRACE_PEEKUSR
suffix:colon
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|3
)paren
op_logical_or
id|addr
template_param
r_sizeof
(paren
r_struct
id|user
)paren
op_minus
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|res
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|data
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_return
id|res
suffix:semicolon
id|tmp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Default return condition */
r_if
c_cond
(paren
id|addr
OL
l_int|17
op_star
r_sizeof
(paren
r_int
)paren
)paren
(brace
id|addr
op_assign
id|addr
op_rshift
l_int|2
suffix:semicolon
multiline_comment|/* temporary hack. */
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
r_sizeof
(paren
r_int
)paren
op_star
id|addr
op_minus
id|MAGICNUMBER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
id|DS
op_logical_or
id|addr
op_eq
id|ES
op_logical_or
id|addr
op_eq
id|FS
op_logical_or
id|addr
op_eq
id|GS
op_logical_or
id|addr
op_eq
id|CS
op_logical_or
id|addr
op_eq
id|SS
)paren
id|tmp
op_and_assign
l_int|0xffff
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|0
)braket
op_logical_and
id|addr
op_le
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|7
)braket
)paren
(brace
id|addr
op_sub_assign
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|0
)braket
suffix:semicolon
id|addr
op_assign
id|addr
op_rshift
l_int|2
suffix:semicolon
id|tmp
op_assign
id|child-&gt;debugreg
(braket
id|addr
)braket
suffix:semicolon
)brace
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
multiline_comment|/* when I and D space are separate, this will have to be fixed. */
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
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|3
)paren
op_logical_or
id|addr
template_param
r_sizeof
(paren
r_struct
id|user
)paren
op_minus
l_int|3
)paren
r_return
op_minus
id|EIO
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
id|DS
op_logical_or
id|addr
op_eq
id|ES
op_logical_or
id|addr
op_eq
id|FS
op_logical_or
id|addr
op_eq
id|GS
op_logical_or
id|addr
op_eq
id|CS
op_logical_or
id|addr
op_eq
id|SS
)paren
(brace
id|data
op_and_assign
l_int|0xffff
suffix:semicolon
r_if
c_cond
(paren
id|data
op_logical_and
(paren
id|data
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
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
r_sizeof
(paren
r_int
)paren
op_minus
id|MAGICNUMBER
)paren
op_amp
op_complement
id|FLAG_MASK
suffix:semicolon
)brace
multiline_comment|/* Do not allow the user to set the debug register for kernel&n;&t;&t;     address space */
r_if
c_cond
(paren
id|addr
OL
l_int|17
)paren
(brace
r_if
c_cond
(paren
id|put_stack_long
c_func
(paren
id|child
comma
r_sizeof
(paren
r_int
)paren
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
)brace
suffix:semicolon
multiline_comment|/* We need to be very careful here.  We implicitly&n;&t;&t;     want to modify a portion of the task_struct, and we&n;&t;&t;     have to be selective about what portions we allow someone&n;&t;&t;     to modify. */
id|addr
op_assign
id|addr
op_lshift
l_int|2
suffix:semicolon
multiline_comment|/* Convert back again */
r_if
c_cond
(paren
id|addr
op_ge
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|0
)braket
op_logical_and
id|addr
op_le
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|7
)braket
)paren
(brace
r_if
c_cond
(paren
id|addr
op_eq
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|4
)braket
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr
op_eq
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|5
)braket
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr
OL
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|4
)braket
op_logical_and
(paren
(paren
r_int
r_int
)paren
id|data
)paren
op_ge
l_int|0xbffffffd
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr
op_eq
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|7
)braket
)paren
(brace
id|data
op_and_assign
op_complement
id|DR_CONTROL_RESERVED
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
l_int|0x5f54
op_rshift
(paren
(paren
id|data
op_rshift
(paren
l_int|16
op_plus
l_int|4
op_star
id|i
)paren
)paren
op_amp
l_int|0xf
)paren
)paren
op_amp
l_int|1
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
suffix:semicolon
id|addr
op_sub_assign
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
suffix:semicolon
id|addr
op_assign
id|addr
op_rshift
l_int|2
suffix:semicolon
id|child-&gt;debugreg
(braket
id|addr
)braket
op_assign
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
r_case
id|PTRACE_SYSCALL
suffix:colon
multiline_comment|/* continue and stop at next (return from) syscall */
r_case
id|PTRACE_CONT
suffix:colon
(brace
multiline_comment|/* restart after signal. */
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|NSIG
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_SYSCALL
)paren
id|child-&gt;flags
op_or_assign
id|PF_TRACESYS
suffix:semicolon
r_else
id|child-&gt;flags
op_and_assign
op_complement
id|PF_TRACESYS
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
id|wake_up_process
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
r_sizeof
(paren
r_int
)paren
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
r_sizeof
(paren
r_int
)paren
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
multiline_comment|/*&n; * make the child exit.  Best I can do is send it a sigkill. &n; * perhaps it should be put in the status that it wants to &n; * exit.&n; */
r_case
id|PTRACE_KILL
suffix:colon
(brace
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;state
op_eq
id|TASK_ZOMBIE
)paren
multiline_comment|/* already dead */
r_return
l_int|0
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|SIGKILL
suffix:semicolon
multiline_comment|/* make sure the single step bit is not set. */
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
r_sizeof
(paren
r_int
)paren
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
r_sizeof
(paren
r_int
)paren
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
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|NSIG
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|child-&gt;flags
op_and_assign
op_complement
id|PF_TRACESYS
suffix:semicolon
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
r_sizeof
(paren
r_int
)paren
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
r_sizeof
(paren
r_int
)paren
op_star
id|EFL
op_minus
id|MAGICNUMBER
comma
id|tmp
)paren
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
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
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|NSIG
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|child-&gt;flags
op_and_assign
op_complement
(paren
id|PF_PTRACED
op_or
id|PF_TRACESYS
)paren
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
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
r_sizeof
(paren
r_int
)paren
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
r_sizeof
(paren
r_int
)paren
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
macro_line|#endif
)brace
DECL|function|syscall_trace
id|asmlinkage
r_void
id|syscall_trace
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
id|current-&gt;flags
op_amp
(paren
id|PF_PTRACED
op_or
id|PF_TRACESYS
)paren
)paren
op_ne
(paren
id|PF_PTRACED
op_or
id|PF_TRACESYS
)paren
)paren
r_return
suffix:semicolon
id|current-&gt;exit_code
op_assign
id|SIGTRAP
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_STOPPED
suffix:semicolon
id|notify_parent
c_func
(paren
id|current
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * this isn&squot;t the same as continuing with a signal, but it will do&n;&t; * for normal use.  strace only continues with a signal if the&n;&t; * stopping signal is not SIGTRAP.  -brl&n;&t; */
r_if
c_cond
(paren
id|current-&gt;exit_code
)paren
id|current-&gt;signal
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|current-&gt;exit_code
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|current-&gt;exit_code
op_assign
l_int|0
suffix:semicolon
)brace
eof
