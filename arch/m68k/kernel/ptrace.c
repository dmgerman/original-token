multiline_comment|/*&n; *  linux/arch/m68k/kernel/ptrace.c&n; *&n; *  Copyright (C) 1994 by Hamish Macdonald&n; *  Taken from linux/kernel/ptrace.c and modified for M680x0.&n; *  linux/kernel/ptrace.c is by Ross Biro 1/23/92, edited by Linus Torvalds&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of&n; * this archive for more details.&n; */
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * does not yet catch signals sent when the child dies.&n; * in exit.c or in signal.c.&n; */
multiline_comment|/* determines which bits in the SR the user has access to. */
multiline_comment|/* 1 = access 0 = no access */
DECL|macro|SR_MASK
mdefine_line|#define SR_MASK 0x001f
multiline_comment|/* sets the trace bits. */
DECL|macro|TRACE_BITS
mdefine_line|#define TRACE_BITS 0x8000
multiline_comment|/* Find the stack offset for a register, relative to tss.esp0. */
DECL|macro|PT_REG
mdefine_line|#define PT_REG(reg)&t;((long)&amp;((struct pt_regs *)0)-&gt;reg)
DECL|macro|SW_REG
mdefine_line|#define SW_REG(reg)&t;((long)&amp;((struct switch_stack *)0)-&gt;reg &bslash;&n;&t;&t;&t; - sizeof(struct switch_stack))
multiline_comment|/* Mapping from PT_xxx to the stack offset at which the register is&n;   saved.  Notice that usp has no stack-slot and needs to be treated&n;   specially (see get_reg/put_reg below). */
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
id|d1
)paren
comma
id|PT_REG
c_func
(paren
id|d2
)paren
comma
id|PT_REG
c_func
(paren
id|d3
)paren
comma
id|PT_REG
c_func
(paren
id|d4
)paren
comma
id|PT_REG
c_func
(paren
id|d5
)paren
comma
id|SW_REG
c_func
(paren
id|d6
)paren
comma
id|SW_REG
c_func
(paren
id|d7
)paren
comma
id|PT_REG
c_func
(paren
id|a0
)paren
comma
id|PT_REG
c_func
(paren
id|a1
)paren
comma
id|PT_REG
c_func
(paren
id|a2
)paren
comma
id|SW_REG
c_func
(paren
id|a3
)paren
comma
id|SW_REG
c_func
(paren
id|a4
)paren
comma
id|SW_REG
c_func
(paren
id|a5
)paren
comma
id|SW_REG
c_func
(paren
id|a6
)paren
comma
id|PT_REG
c_func
(paren
id|d0
)paren
comma
op_minus
l_int|1
comma
id|PT_REG
c_func
(paren
id|orig_d0
)paren
comma
id|PT_REG
c_func
(paren
id|sr
)paren
comma
id|PT_REG
c_func
(paren
id|pc
)paren
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Get contents of register REGNO in task TASK.&n; */
DECL|function|get_reg
r_static
r_inline
r_int
id|get_reg
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|regno
)paren
(brace
r_int
r_int
op_star
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|regno
op_eq
id|PT_USP
)paren
id|addr
op_assign
op_amp
id|task-&gt;tss.usp
suffix:semicolon
r_else
r_if
c_cond
(paren
id|regno
OL
r_sizeof
(paren
id|regoff
)paren
op_div
r_sizeof
(paren
id|regoff
(braket
l_int|0
)braket
)paren
)paren
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|task-&gt;tss.esp0
op_plus
id|regoff
(braket
id|regno
)braket
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
r_return
op_star
id|addr
suffix:semicolon
)brace
multiline_comment|/*&n; * Write contents of register REGNO in task TASK.&n; */
DECL|function|put_reg
r_static
r_inline
r_int
id|put_reg
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|regno
comma
r_int
r_int
id|data
)paren
(brace
r_int
r_int
op_star
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|regno
op_eq
id|PT_USP
)paren
id|addr
op_assign
op_amp
id|task-&gt;tss.usp
suffix:semicolon
r_else
r_if
c_cond
(paren
id|regno
OL
r_sizeof
(paren
id|regoff
)paren
op_div
r_sizeof
(paren
id|regoff
(braket
l_int|0
)braket
)paren
)paren
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|task-&gt;tss.esp0
op_plus
id|regoff
(braket
id|regno
)braket
)paren
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
op_star
id|addr
op_assign
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine gets a long from any process space by following the page&n; * tables. NOTE! You should check that the long isn&squot;t on a page boundary,&n; * and that it is in the task area before calling this: this routine does&n; * no checking.&n; *&n; */
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
l_string|&quot;ptrace: bad page directory %08lx&bslash;n&quot;
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
l_string|&quot;ptrace: bad page directory %08lx&bslash;n&quot;
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
multiline_comment|/* this is a hack for non-kernel-mapped video buffers and similar */
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
(brace
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
id|flush_page_to_ram
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/* we&squot;re bypassing pagetables, so we have to set the dirty bit ourselves */
multiline_comment|/* this should also re-instate whatever read-only mode there was before */
op_star
id|pgtable
op_assign
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
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|find_extend_vma
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
id|vma_low
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
id|vma_low
op_assign
id|vma-&gt;vm_next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma_low
op_logical_or
id|vma_low-&gt;vm_start
op_ne
id|vma-&gt;vm_end
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|high
op_assign
id|get_long
c_func
(paren
id|tsk
comma
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
id|low
op_assign
id|get_long
c_func
(paren
id|tsk
comma
id|vma_low
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
l_int|3
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
l_int|1
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
id|vma_low
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
id|vma_low
op_assign
id|vma-&gt;vm_next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma_low
op_logical_or
id|vma_low-&gt;vm_start
op_ne
id|vma-&gt;vm_end
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|high
op_assign
id|get_long
c_func
(paren
id|tsk
comma
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
id|low
op_assign
id|get_long
c_func
(paren
id|tsk
comma
id|vma_low
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
id|high
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
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
l_int|1
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
id|tsk
comma
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
id|high
)paren
suffix:semicolon
id|put_long
c_func
(paren
id|tsk
comma
id|vma_low
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
id|low
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
r_struct
id|task_struct
op_star
id|child
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
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
)paren
op_logical_and
op_logical_neg
id|suser
c_func
(paren
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
r_goto
id|out
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
r_goto
id|out
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
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
)paren
id|ret
op_assign
id|put_user
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
r_goto
id|out
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
id|ret
op_assign
op_minus
id|EIO
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
OL
l_int|0
op_logical_or
id|addr
op_ge
r_sizeof
(paren
r_struct
id|user
)paren
)paren
r_goto
id|out
suffix:semicolon
id|tmp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Default return condition */
id|addr
op_assign
id|addr
op_rshift
l_int|2
suffix:semicolon
multiline_comment|/* temporary hack. */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
l_int|19
)paren
(brace
id|tmp
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
id|PT_SR
)paren
id|tmp
op_rshift_assign
l_int|16
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|addr
op_ge
l_int|21
op_logical_and
id|addr
OL
l_int|49
)paren
id|tmp
op_assign
id|child-&gt;tss.fp
(braket
id|addr
op_minus
l_int|21
)braket
suffix:semicolon
r_else
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|put_user
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
r_goto
id|out
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
r_goto
id|out
suffix:semicolon
r_case
id|PTRACE_POKEUSR
suffix:colon
multiline_comment|/* write the word at location addr in the USER area */
id|ret
op_assign
op_minus
id|EIO
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
OL
l_int|0
op_logical_or
id|addr
op_ge
r_sizeof
(paren
r_struct
id|user
)paren
)paren
r_goto
id|out
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
id|PT_ORIG_D0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
id|PT_SR
)paren
(brace
id|data
op_and_assign
id|SR_MASK
suffix:semicolon
id|data
op_lshift_assign
l_int|16
suffix:semicolon
id|data
op_or_assign
id|get_reg
c_func
(paren
id|child
comma
id|PT_SR
)paren
op_amp
op_complement
(paren
id|SR_MASK
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr
OL
l_int|19
)paren
(brace
r_if
c_cond
(paren
id|put_reg
c_func
(paren
id|child
comma
id|addr
comma
id|data
)paren
)paren
r_goto
id|out
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
id|addr
op_ge
l_int|21
op_logical_and
id|addr
OL
l_int|48
)paren
(brace
id|child-&gt;tss.fp
(braket
id|addr
op_minus
l_int|21
)braket
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_goto
id|out
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
op_ge
id|NSIG
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
multiline_comment|/* make sure the single step bit is not set. */
id|tmp
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|PT_SR
)paren
op_amp
op_complement
(paren
id|TRACE_BITS
op_lshift
l_int|16
)paren
suffix:semicolon
id|put_reg
c_func
(paren
id|child
comma
id|PT_SR
comma
id|tmp
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
multiline_comment|/*&n; * make the child exit.  Best I can do is send it a sigkill. &n; * perhaps it should be put in the status that it wants to &n; * exit.&n; */
r_case
id|PTRACE_KILL
suffix:colon
(brace
r_int
id|tmp
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;state
op_eq
id|TASK_ZOMBIE
)paren
multiline_comment|/* already dead */
r_goto
id|out
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
id|get_reg
c_func
(paren
id|child
comma
id|PT_SR
)paren
op_amp
op_complement
(paren
id|TRACE_BITS
op_lshift
l_int|16
)paren
suffix:semicolon
id|put_reg
c_func
(paren
id|child
comma
id|PT_SR
comma
id|tmp
)paren
suffix:semicolon
r_goto
id|out
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
op_ge
id|NSIG
)paren
r_goto
id|out
suffix:semicolon
id|child-&gt;flags
op_and_assign
op_complement
id|PF_TRACESYS
suffix:semicolon
id|tmp
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|PT_SR
)paren
op_or
(paren
id|TRACE_BITS
op_lshift
l_int|16
)paren
suffix:semicolon
id|put_reg
c_func
(paren
id|child
comma
id|PT_SR
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
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
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
op_ge
id|NSIG
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
multiline_comment|/* make sure the single step bit is not set. */
id|tmp
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|PT_SR
)paren
op_amp
op_complement
(paren
id|TRACE_BITS
op_lshift
l_int|16
)paren
suffix:semicolon
id|put_reg
c_func
(paren
id|child
comma
id|PT_SR
comma
id|tmp
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
DECL|function|syscall_trace
id|asmlinkage
r_void
id|syscall_trace
c_func
(paren
r_void
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
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
r_goto
id|out
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
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
eof
