multiline_comment|/* ptrace.c */
multiline_comment|/* By Ross Biro 1/23/92 */
multiline_comment|/* edited by Linus Torvalds */
multiline_comment|/* mangled further by Bob Manson (manson@santafe.edu) */
multiline_comment|/* more mutilation by David Mosberger (davidm@azstarnet.com) */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;proto.h&quot;
DECL|macro|DEBUG
mdefine_line|#define DEBUG&t;DBG_MEM
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
r_enum
(brace
DECL|enumerator|DBG_MEM
id|DBG_MEM
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
DECL|enumerator|DBG_BPT
id|DBG_BPT
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
DECL|enumerator|DBG_MEM_ALL
id|DBG_MEM_ALL
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
)brace
suffix:semicolon
DECL|macro|DBG
mdefine_line|#define DBG(fac,args)&t;{if ((fac) &amp; DEBUG) printk args;}
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(fac,args)
macro_line|#endif
DECL|macro|BREAKINST
mdefine_line|#define BREAKINST&t;0x00000080&t;/* call_pal bpt */
multiline_comment|/*&n; * does not yet catch signals sent when the child dies.&n; * in exit.c or in signal.c.&n; */
multiline_comment|/*&n; * Processes always block with the following stack-layout:&n; *&n; *  +================================+ &lt;---- task + 2*PAGE_SIZE&n; *  | PALcode saved frame (ps, pc,   | ^&n; *  | gp, a0, a1, a2)&t;&t;     | |&n; *  +================================+ | struct pt_regs&n; *  |&t;        &t;&t;     | |&n; *  | frame generated by SAVE_ALL    | |&n; *  |&t;        &t;&t;     | v&n; *  +================================+&n; *  |&t;        &t;&t;     | ^&n; *  | frame saved by do_switch_stack | | struct switch_stack&n; *  |&t;        &t;&t;     | v&n; *  +================================+&n; */
DECL|macro|PT_REG
mdefine_line|#define PT_REG(reg)&t;(PAGE_SIZE*2 - sizeof(struct pt_regs)&t;&t;&bslash;&n;&t;&t;&t; + (long)&amp;((struct pt_regs *)0)-&gt;reg)
DECL|macro|SW_REG
mdefine_line|#define SW_REG(reg)&t;(PAGE_SIZE*2 - sizeof(struct pt_regs)&t;&t;&bslash;&n;&t;&t;&t; - sizeof(struct switch_stack)&t;&t;&t;&bslash;&n;&t;&t;&t; + (long)&amp;((struct switch_stack *)0)-&gt;reg)
multiline_comment|/* &n; * The following table maps a register index into the stack offset at&n; * which the register is saved.  Register indices are 0-31 for integer&n; * regs, 32-63 for fp regs, and 64 for the pc.  Notice that sp and&n; * zero have no stack-slot and need to be treated specially (see&n; * get_reg/put_reg below).&n; */
r_enum
(brace
DECL|enumerator|REG_R0
DECL|enumerator|REG_F0
DECL|enumerator|REG_FPCR
DECL|enumerator|REG_PC
id|REG_R0
op_assign
l_int|0
comma
id|REG_F0
op_assign
l_int|32
comma
id|REG_FPCR
op_assign
l_int|63
comma
id|REG_PC
op_assign
l_int|64
)brace
suffix:semicolon
DECL|variable|regoff
r_static
r_int
id|regoff
(braket
)braket
op_assign
(brace
id|PT_REG
c_func
(paren
id|r0
)paren
comma
id|PT_REG
c_func
(paren
id|r1
)paren
comma
id|PT_REG
c_func
(paren
id|r2
)paren
comma
id|PT_REG
c_func
(paren
id|r3
)paren
comma
id|PT_REG
c_func
(paren
id|r4
)paren
comma
id|PT_REG
c_func
(paren
id|r5
)paren
comma
id|PT_REG
c_func
(paren
id|r6
)paren
comma
id|PT_REG
c_func
(paren
id|r7
)paren
comma
id|PT_REG
c_func
(paren
id|r8
)paren
comma
id|SW_REG
c_func
(paren
id|r9
)paren
comma
id|SW_REG
c_func
(paren
id|r10
)paren
comma
id|SW_REG
c_func
(paren
id|r11
)paren
comma
id|SW_REG
c_func
(paren
id|r12
)paren
comma
id|SW_REG
c_func
(paren
id|r13
)paren
comma
id|SW_REG
c_func
(paren
id|r14
)paren
comma
id|SW_REG
c_func
(paren
id|r15
)paren
comma
id|PT_REG
c_func
(paren
id|r16
)paren
comma
id|PT_REG
c_func
(paren
id|r17
)paren
comma
id|PT_REG
c_func
(paren
id|r18
)paren
comma
id|PT_REG
c_func
(paren
id|r19
)paren
comma
id|PT_REG
c_func
(paren
id|r20
)paren
comma
id|PT_REG
c_func
(paren
id|r21
)paren
comma
id|PT_REG
c_func
(paren
id|r22
)paren
comma
id|PT_REG
c_func
(paren
id|r23
)paren
comma
id|PT_REG
c_func
(paren
id|r24
)paren
comma
id|PT_REG
c_func
(paren
id|r25
)paren
comma
id|PT_REG
c_func
(paren
id|r26
)paren
comma
id|PT_REG
c_func
(paren
id|r27
)paren
comma
id|PT_REG
c_func
(paren
id|r28
)paren
comma
id|PT_REG
c_func
(paren
id|gp
)paren
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|0
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|1
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|2
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|3
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|4
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|5
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|6
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|7
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|8
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|9
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|10
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|11
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|12
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|13
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|14
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|15
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|16
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|17
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|18
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|19
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|20
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|21
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|22
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|23
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|24
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|25
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|26
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|27
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|28
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|29
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|30
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|31
)braket
)paren
comma
id|PT_REG
c_func
(paren
id|pc
)paren
)brace
suffix:semicolon
DECL|variable|zero
r_static
r_int
id|zero
suffix:semicolon
multiline_comment|/*&n; * Get address of register REGNO in task TASK.&n; */
r_static
r_int
op_star
DECL|function|get_reg_addr
id|get_reg_addr
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|regno
)paren
(brace
r_int
op_star
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|regno
op_eq
l_int|30
)paren
(brace
id|addr
op_assign
op_amp
id|task-&gt;tss.usp
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|regno
op_eq
l_int|31
op_logical_or
id|regno
OG
l_int|64
)paren
(brace
id|zero
op_assign
l_int|0
suffix:semicolon
id|addr
op_assign
op_amp
id|zero
suffix:semicolon
)brace
r_else
(brace
id|addr
op_assign
(paren
r_int
op_star
)paren
(paren
(paren
r_int
)paren
id|task
op_plus
id|regoff
(braket
id|regno
)braket
)paren
suffix:semicolon
)brace
r_return
id|addr
suffix:semicolon
)brace
multiline_comment|/*&n; * Get contents of register REGNO in task TASK.&n; */
r_static
r_inline
r_int
DECL|function|get_reg
id|get_reg
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|regno
)paren
(brace
r_return
op_star
id|get_reg_addr
c_func
(paren
id|task
comma
id|regno
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write contents of register REGNO in task TASK.&n; */
r_static
r_inline
r_int
DECL|function|put_reg
id|put_reg
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|regno
comma
r_int
id|data
)paren
(brace
op_star
id|get_reg_addr
c_func
(paren
id|task
comma
id|regno
)paren
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
DECL|function|get_long
id|get_long
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
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
id|pmd_t
op_star
id|pgmiddle
suffix:semicolon
id|pte_t
op_star
id|pgtable
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_MEM_ALL
comma
(paren
l_string|&quot;getting long at 0x%lx&bslash;n&quot;
comma
id|addr
)paren
)paren
suffix:semicolon
id|repeat
suffix:colon
id|pgdir
op_assign
id|pgd_offset
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
id|handle_mm_fault
c_func
(paren
id|tsk
comma
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
id|pgmiddle
op_assign
id|pmd_offset
c_func
(paren
id|pgdir
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pgmiddle
)paren
)paren
(brace
id|handle_mm_fault
c_func
(paren
id|tsk
comma
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
id|pmd_bad
c_func
(paren
op_star
id|pgmiddle
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ptrace: bad page middle %08lx&bslash;n&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|pgmiddle
)paren
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pgmiddle
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pgtable
op_assign
id|pte_offset
c_func
(paren
id|pgmiddle
comma
id|addr
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
id|handle_mm_fault
c_func
(paren
id|tsk
comma
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
id|MAP_NR
c_func
(paren
id|page
)paren
op_ge
id|max_mapnr
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
DECL|function|put_long
id|put_long
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
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
id|pmd_t
op_star
id|pgmiddle
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
id|pgd_offset
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
id|handle_mm_fault
c_func
(paren
id|tsk
comma
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
id|pgmiddle
op_assign
id|pmd_offset
c_func
(paren
id|pgdir
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pgmiddle
)paren
)paren
(brace
id|handle_mm_fault
c_func
(paren
id|tsk
comma
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
id|pmd_bad
c_func
(paren
op_star
id|pgmiddle
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ptrace: bad page middle %08lx&bslash;n&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|pgmiddle
)paren
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pgmiddle
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pgtable
op_assign
id|pte_offset
c_func
(paren
id|pgmiddle
comma
id|addr
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
id|handle_mm_fault
c_func
(paren
id|tsk
comma
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
id|handle_mm_fault
c_func
(paren
id|tsk
comma
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
multiline_comment|/* This is a hack for non-kernel-mapped video buffers and similar.  */
r_if
c_cond
(paren
id|MAP_NR
c_func
(paren
id|page
)paren
OL
id|max_mapnr
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
multiline_comment|/* We&squot;re bypassing pagetables, so we have to set the dirty bit&n;&t;   ourselves.  This should also re-instate whatever read-only&n;&t;   mode there was before.  */
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
id|flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_struct
id|vm_area_struct
op_star
DECL|function|find_extend_vma
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
id|tsk-&gt;mm
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
DECL|function|read_long
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
id|DBG
c_func
(paren
id|DBG_MEM_ALL
comma
(paren
l_string|&quot;in read_long&bslash;n&quot;
)paren
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
(paren
id|PAGE_SIZE
op_minus
r_sizeof
(paren
r_int
)paren
)paren
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma_high
op_assign
id|vma
suffix:semicolon
r_int
r_int
id|low
comma
id|align
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
id|align
op_assign
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
suffix:semicolon
id|addr
op_sub_assign
id|align
suffix:semicolon
id|low
op_assign
id|get_long
c_func
(paren
id|tsk
comma
id|vma
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|align
)paren
(brace
r_int
r_int
id|high
suffix:semicolon
id|high
op_assign
id|get_long
c_func
(paren
id|tsk
comma
id|vma_high
comma
id|addr
op_plus
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|low
op_rshift_assign
id|align
op_star
l_int|8
suffix:semicolon
id|low
op_or_assign
id|high
op_lshift
(paren
l_int|64
op_minus
id|align
op_star
l_int|8
)paren
suffix:semicolon
)brace
op_star
id|result
op_assign
id|low
suffix:semicolon
)brace
r_else
(brace
r_int
id|l
op_assign
id|get_long
c_func
(paren
id|tsk
comma
id|vma
comma
id|addr
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_MEM_ALL
comma
(paren
l_string|&quot;value is 0x%lx&bslash;n&quot;
comma
id|l
)paren
)paren
suffix:semicolon
op_star
id|result
op_assign
id|l
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine checks the page boundaries, and that the offset is&n; * within the task area. It then calls put_long() to write a long.&n; */
r_static
r_int
DECL|function|write_long
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
comma
id|align
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
id|align
op_assign
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
suffix:semicolon
id|addr
op_sub_assign
id|align
suffix:semicolon
id|low
op_assign
id|get_long
c_func
(paren
id|tsk
comma
id|vma
comma
id|addr
)paren
suffix:semicolon
id|high
op_assign
id|get_long
c_func
(paren
id|tsk
comma
id|vma_high
comma
id|addr
op_plus
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|low
op_and_assign
op_complement
l_int|0UL
op_rshift
(paren
l_int|64
op_minus
id|align
op_star
l_int|8
)paren
suffix:semicolon
id|high
op_and_assign
op_complement
l_int|0UL
op_lshift
(paren
id|align
op_star
l_int|8
)paren
suffix:semicolon
id|low
op_or_assign
id|data
op_lshift
(paren
id|align
op_star
l_int|8
)paren
suffix:semicolon
id|high
op_or_assign
id|data
op_rshift
(paren
l_int|64
op_minus
id|align
op_star
l_int|8
)paren
suffix:semicolon
id|put_long
c_func
(paren
id|tsk
comma
id|vma
comma
id|addr
comma
id|low
)paren
suffix:semicolon
id|put_long
c_func
(paren
id|tsk
comma
id|vma_high
comma
id|addr
op_plus
r_sizeof
(paren
r_int
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
id|tsk
comma
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
multiline_comment|/*&n; * Read a 32bit int from address space TSK.&n; */
r_static
r_int
DECL|function|read_int
id|read_int
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
id|data
)paren
(brace
r_int
r_int
id|l
comma
id|align
suffix:semicolon
r_int
id|res
suffix:semicolon
id|align
op_assign
id|addr
op_amp
l_int|0x7
suffix:semicolon
id|addr
op_and_assign
op_complement
l_int|0x7
suffix:semicolon
id|res
op_assign
id|read_long
c_func
(paren
id|tsk
comma
id|addr
comma
op_amp
id|l
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
r_if
c_cond
(paren
id|align
op_eq
l_int|0
)paren
(brace
op_star
id|data
op_assign
id|l
suffix:semicolon
)brace
r_else
(brace
op_star
id|data
op_assign
id|l
op_rshift
l_int|32
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Write a 32bit word to address space TSK.&n; *&n; * For simplicity, do a read-modify-write of the 64bit word that&n; * contains the 32bit word that we are about to write.&n; */
r_static
r_int
DECL|function|write_int
id|write_int
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
id|l
comma
id|align
suffix:semicolon
r_int
id|res
suffix:semicolon
id|align
op_assign
id|addr
op_amp
l_int|0x7
suffix:semicolon
id|addr
op_and_assign
op_complement
l_int|0x7
suffix:semicolon
id|res
op_assign
id|read_long
c_func
(paren
id|tsk
comma
id|addr
comma
op_amp
id|l
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
r_if
c_cond
(paren
id|align
op_eq
l_int|0
)paren
(brace
id|l
op_assign
(paren
id|l
op_amp
l_int|0xffffffff00000000UL
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|data
op_lshift
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|l
op_assign
(paren
id|l
op_amp
l_int|0x00000000ffffffffUL
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|data
op_lshift
l_int|32
)paren
suffix:semicolon
)brace
r_return
id|write_long
c_func
(paren
id|tsk
comma
id|addr
comma
id|l
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set breakpoint.&n; */
r_int
DECL|function|ptrace_set_bpt
id|ptrace_set_bpt
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
(brace
r_int
id|displ
comma
id|i
comma
id|res
comma
id|reg_b
comma
id|nsaved
op_assign
l_int|0
suffix:semicolon
id|u32
id|insn
comma
id|op_code
suffix:semicolon
r_int
r_int
id|pc
suffix:semicolon
id|pc
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|REG_PC
)paren
suffix:semicolon
id|res
op_assign
id|read_int
c_func
(paren
id|child
comma
id|pc
comma
op_amp
id|insn
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
id|op_code
op_assign
id|insn
op_rshift
l_int|26
suffix:semicolon
r_if
c_cond
(paren
id|op_code
op_ge
l_int|0x30
)paren
(brace
multiline_comment|/*&n;&t;&t; * It&squot;s a branch: instead of trying to figure out&n;&t;&t; * whether the branch will be taken or not, we&squot;ll put&n;&t;&t; * a breakpoint at either location.  This is simpler,&n;&t;&t; * more reliable, and probably not a whole lot slower&n;&t;&t; * than the alternative approach of emulating the&n;&t;&t; * branch (emulation can be tricky for fp branches).&n;&t;&t; */
id|displ
op_assign
(paren
(paren
id|s32
)paren
(paren
id|insn
op_lshift
l_int|11
)paren
)paren
op_rshift
l_int|9
suffix:semicolon
id|child-&gt;tss.bpt_addr
(braket
id|nsaved
op_increment
)braket
op_assign
id|pc
op_plus
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|displ
)paren
multiline_comment|/* guard against unoptimized code */
id|child-&gt;tss.bpt_addr
(braket
id|nsaved
op_increment
)braket
op_assign
id|pc
op_plus
l_int|4
op_plus
id|displ
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_BPT
comma
(paren
l_string|&quot;execing branch&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|op_code
op_eq
l_int|0x1a
)paren
(brace
id|reg_b
op_assign
(paren
id|insn
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|child-&gt;tss.bpt_addr
(braket
id|nsaved
op_increment
)braket
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|reg_b
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_BPT
comma
(paren
l_string|&quot;execing jump&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|child-&gt;tss.bpt_addr
(braket
id|nsaved
op_increment
)braket
op_assign
id|pc
op_plus
l_int|4
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_BPT
comma
(paren
l_string|&quot;execing normal insn&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* install breakpoints: */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nsaved
suffix:semicolon
op_increment
id|i
)paren
(brace
id|res
op_assign
id|read_int
c_func
(paren
id|child
comma
id|child-&gt;tss.bpt_addr
(braket
id|i
)braket
comma
op_amp
id|insn
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
id|child-&gt;tss.bpt_insn
(braket
id|i
)braket
op_assign
id|insn
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_BPT
comma
(paren
l_string|&quot;    -&gt; next_pc=%lx&bslash;n&quot;
comma
id|child-&gt;tss.bpt_addr
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
id|res
op_assign
id|write_int
c_func
(paren
id|child
comma
id|child-&gt;tss.bpt_addr
(braket
id|i
)braket
comma
id|BREAKINST
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
)brace
id|child-&gt;tss.bpt_nsaved
op_assign
id|nsaved
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Ensure no single-step breakpoint is pending.  Returns non-zero&n; * value if child was being single-stepped.&n; */
r_int
DECL|function|ptrace_cancel_bpt
id|ptrace_cancel_bpt
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
(brace
r_int
id|i
comma
id|nsaved
op_assign
id|child-&gt;tss.bpt_nsaved
suffix:semicolon
id|child-&gt;tss.bpt_nsaved
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nsaved
OG
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ptrace_cancel_bpt: bogus nsaved: %d!&bslash;n&quot;
comma
id|nsaved
)paren
suffix:semicolon
id|nsaved
op_assign
l_int|2
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
id|nsaved
suffix:semicolon
op_increment
id|i
)paren
(brace
id|write_int
c_func
(paren
id|child
comma
id|child-&gt;tss.bpt_addr
(braket
id|i
)braket
comma
id|child-&gt;tss.bpt_insn
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
(paren
id|nsaved
op_ne
l_int|0
)paren
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_ptrace
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
comma
r_int
id|a4
comma
r_int
id|a5
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_struct
id|task_struct
op_star
id|child
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_MEM
comma
(paren
l_string|&quot;request=%ld pid=%ld addr=0x%lx data=0x%lx&bslash;n&quot;
comma
id|request
comma
id|pid
comma
id|addr
comma
id|data
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
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
r_goto
id|out
suffix:semicolon
multiline_comment|/* set the ptrace bit in the process flags. */
id|current-&gt;flags
op_or_assign
id|PF_PTRACED
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
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
r_goto
id|out
suffix:semicolon
id|ret
op_assign
op_minus
id|ESRCH
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|child
op_assign
id|find_task_by_pid
c_func
(paren
id|pid
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_ATTACH
)paren
(brace
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|child
op_eq
id|current
)paren
r_goto
id|out
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
id|child-&gt;suid
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
id|child-&gt;sgid
)paren
op_logical_or
(paren
id|current-&gt;gid
op_ne
id|child-&gt;gid
)paren
op_logical_or
(paren
op_logical_neg
id|cap_issubset
c_func
(paren
id|child-&gt;cap_permitted
comma
id|current-&gt;cap_permitted
)paren
)paren
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_PTRACE
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* the same process cannot be attached many times */
r_if
c_cond
(paren
id|child-&gt;flags
op_amp
id|PF_PTRACED
)paren
r_goto
id|out
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
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|ESRCH
suffix:semicolon
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
(brace
id|DBG
c_func
(paren
id|DBG_MEM
comma
(paren
l_string|&quot;child not traced&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|child-&gt;state
op_ne
id|TASK_STOPPED
)paren
(brace
id|DBG
c_func
(paren
id|DBG_MEM
comma
(paren
l_string|&quot;child process not stopped&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request
op_ne
id|PTRACE_KILL
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|child-&gt;p_pptr
op_ne
id|current
)paren
(brace
id|DBG
c_func
(paren
id|DBG_MEM
comma
(paren
l_string|&quot;child not parent of this process&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|request
)paren
(brace
multiline_comment|/* When I and D space are separate, these will need to be fixed.  */
r_case
id|PTRACE_PEEKTEXT
suffix:colon
multiline_comment|/* read word at location addr. */
r_case
id|PTRACE_PEEKDATA
suffix:colon
id|down
c_func
(paren
op_amp
id|child-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|ret
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
id|up
c_func
(paren
op_amp
id|child-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_MEM
comma
(paren
l_string|&quot;peek %#lx-&gt;%#lx&bslash;n&quot;
comma
id|addr
comma
id|tmp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|regs.r0
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* special return: no errors */
id|ret
op_assign
id|tmp
suffix:semicolon
r_goto
id|out
suffix:semicolon
multiline_comment|/* Read register number ADDR. */
r_case
id|PTRACE_PEEKUSR
suffix:colon
id|regs.r0
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* special return: no errors */
id|ret
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|addr
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_MEM
comma
(paren
l_string|&quot;peek $%ld-&gt;%#lx&bslash;n&quot;
comma
id|addr
comma
id|ret
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
multiline_comment|/* When I and D space are separate, this will have to be fixed.  */
r_case
id|PTRACE_POKETEXT
suffix:colon
multiline_comment|/* write the word at location addr. */
r_case
id|PTRACE_POKEDATA
suffix:colon
id|DBG
c_func
(paren
id|DBG_MEM
comma
(paren
l_string|&quot;poke %#lx&lt;-%#lx&bslash;n&quot;
comma
id|addr
comma
id|data
)paren
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|child-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|ret
op_assign
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
id|up
c_func
(paren
op_amp
id|child-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|PTRACE_POKEUSR
suffix:colon
multiline_comment|/* write the specified register */
id|DBG
c_func
(paren
id|DBG_MEM
comma
(paren
l_string|&quot;poke $%ld&lt;-%#lx&bslash;n&quot;
comma
id|addr
comma
id|data
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|put_reg
c_func
(paren
id|child
comma
id|addr
comma
id|data
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|PTRACE_SYSCALL
suffix:colon
multiline_comment|/* continue and stop at next&n;&t;&t;&t;&t;(return from) syscall */
r_case
id|PTRACE_CONT
suffix:colon
multiline_comment|/* restart after signal. */
id|ret
op_assign
op_minus
id|EIO
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
id|_NSIG
)paren
r_goto
id|out
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
multiline_comment|/* make sure single-step breakpoint is gone. */
id|ptrace_cancel_bpt
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
id|data
suffix:semicolon
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Make the child exit.  Best I can do is send it a sigkill.&n;&t; * perhaps it should be put in the status that it wants to&n;&t; * exit.&n;&t; */
r_case
id|PTRACE_KILL
suffix:colon
r_if
c_cond
(paren
id|child-&gt;state
op_ne
id|TASK_ZOMBIE
)paren
(brace
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
)brace
multiline_comment|/* make sure single-step breakpoint is gone. */
id|ptrace_cancel_bpt
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|PTRACE_SINGLESTEP
suffix:colon
multiline_comment|/* execute single instruction. */
id|ret
op_assign
op_minus
id|EIO
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
id|_NSIG
)paren
r_goto
id|out
suffix:semicolon
id|child-&gt;tss.bpt_nsaved
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* mark single-stepping */
id|child-&gt;flags
op_and_assign
op_complement
id|PF_TRACESYS
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
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|PTRACE_DETACH
suffix:colon
multiline_comment|/* detach a process that was attached. */
id|ret
op_assign
op_minus
id|EIO
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
id|_NSIG
)paren
r_goto
id|out
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
multiline_comment|/* make sure single-step breakpoint is gone. */
id|ptrace_cancel_bpt
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|asmlinkage
r_void
DECL|function|syscall_trace
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
comma
id|SIGCHLD
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This isn&squot;t the same as continuing with a signal, but it will do&n;&t; * for normal use.  strace only continues with a signal if the&n;&t; * stopping signal is not SIGTRAP.  -brl&n;&t; */
r_if
c_cond
(paren
id|current-&gt;exit_code
)paren
(brace
id|send_sig
c_func
(paren
id|current-&gt;exit_code
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|current-&gt;exit_code
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof
