multiline_comment|/* $Id: ptrace.c,v 1.11 1998/10/19 16:26:31 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 Ross Biro&n; * Copyright (C) Linus Torvalds&n; * Copyright (C) 1994, 1995, 1996, 1997, 1998 Ralf Baechle&n; * Copyright (C) 1996 David S. Miller&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;asm/fp.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * This routine gets a long from any process space by following the page&n; * tables. NOTE! You should check that the long isn&squot;t on a page boundary,&n; * and that it is in the task area before calling this: this routine does&n; * no checking.&n; */
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
comma
id|retval
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
multiline_comment|/* This is a hack for non-kernel-mapped video buffers and similar */
r_if
c_cond
(paren
id|MAP_NR
c_func
(paren
id|page
)paren
op_ge
id|MAP_NR
c_func
(paren
id|high_memory
)paren
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
multiline_comment|/* We can&squot;t use flush_page_to_ram() since we&squot;re running in&n;&t; * another context ...&n;&t; */
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|page
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* VCED avoidance  */
r_return
id|retval
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
multiline_comment|/* This is a hack for non-kernel-mapped video buffers and similar */
r_if
c_cond
(paren
id|MAP_NR
c_func
(paren
id|page
)paren
OL
id|MAP_NR
c_func
(paren
id|high_memory
)paren
)paren
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|MAP_NR
c_func
(paren
id|page
)paren
OL
id|MAP_NR
c_func
(paren
id|high_memory
)paren
)paren
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We&squot;re bypassing pagetables, so we have to set the dirty bit&n;&t; * ourselves this should also re-instate whatever read-only mode&n;&t; * there was before&n;&t; */
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
id|flush_tlb_page
c_func
(paren
id|vma
comma
id|addr
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
id|high
op_assign
id|get_long
c_func
(paren
id|tsk
comma
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
id|high
op_assign
id|get_long
c_func
(paren
id|tsk
comma
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
id|res
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;ptrace(r=%d,pid=%d,addr=%08lx,data=%08lx)&bslash;n&quot;
comma
(paren
r_int
)paren
id|request
comma
(paren
r_int
)paren
id|pid
comma
(paren
r_int
r_int
)paren
id|addr
comma
(paren
r_int
r_int
)paren
id|data
)paren
suffix:semicolon
macro_line|#endif
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
(brace
id|res
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* set the ptrace bit in the process flags. */
id|current-&gt;flags
op_or_assign
id|PF_PTRACED
suffix:semicolon
id|res
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
(brace
multiline_comment|/* you may not mess with init */
id|res
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
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
(brace
id|res
op_assign
op_minus
id|ESRCH
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
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
(brace
id|res
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
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
id|capable
c_func
(paren
id|CAP_SYS_PTRACE
)paren
)paren
(brace
id|res
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* the same process cannot be attached many times */
r_if
c_cond
(paren
id|child-&gt;flags
op_amp
id|PF_PTRACED
)paren
(brace
id|res
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
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
id|res
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
op_logical_neg
(paren
id|child-&gt;flags
op_amp
id|PF_PTRACED
)paren
)paren
(brace
id|res
op_assign
op_minus
id|ESRCH
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
r_if
c_cond
(paren
id|request
op_ne
id|PTRACE_KILL
)paren
(brace
id|res
op_assign
op_minus
id|ESRCH
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|child-&gt;p_pptr
op_ne
id|current
)paren
(brace
id|res
op_assign
op_minus
id|ESRCH
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
r_goto
id|out
suffix:semicolon
id|res
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
multiline_comment|/* #define DEBUG_PEEKUSR */
r_case
id|PTRACE_PEEKUSR
suffix:colon
(brace
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|child
op_plus
id|KERNEL_STACK_SIZE
op_minus
l_int|32
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
id|tmp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Default return value. */
r_if
c_cond
(paren
id|addr
OL
l_int|32
op_logical_and
id|addr
op_ge
l_int|0
)paren
id|tmp
op_assign
id|regs-&gt;regs
(braket
id|addr
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|addr
op_ge
l_int|32
op_logical_and
id|addr
OL
l_int|64
)paren
(brace
r_int
r_int
r_int
op_star
id|fregs
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;used_math
)paren
(brace
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|child
)paren
(brace
id|enable_cp1
c_func
(paren
)paren
suffix:semicolon
id|r4xx0_save_fp
c_func
(paren
id|child
)paren
suffix:semicolon
id|disable_cp1
c_func
(paren
)paren
suffix:semicolon
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
)brace
id|fregs
op_assign
(paren
r_int
r_int
r_int
op_star
)paren
op_amp
id|child-&gt;tss.fpu.hard.fp_regs
(braket
l_int|0
)braket
suffix:semicolon
id|tmp
op_assign
(paren
r_int
r_int
)paren
id|fregs
(braket
(paren
id|addr
op_minus
l_int|32
)paren
)braket
suffix:semicolon
)brace
r_else
(brace
id|tmp
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* FP not yet used  */
)brace
)brace
r_else
(brace
id|addr
op_sub_assign
l_int|64
suffix:semicolon
r_switch
c_cond
(paren
id|addr
)paren
(brace
r_case
l_int|0
suffix:colon
id|tmp
op_assign
id|regs-&gt;cp0_epc
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|tmp
op_assign
id|regs-&gt;cp0_cause
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|tmp
op_assign
id|regs-&gt;cp0_badvaddr
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|tmp
op_assign
id|regs-&gt;lo
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|tmp
op_assign
id|regs-&gt;hi
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|tmp
op_assign
id|child-&gt;tss.fpu.hard.control
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
multiline_comment|/* implementation / version register */
id|tmp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX */
r_break
suffix:semicolon
r_default
suffix:colon
id|tmp
op_assign
l_int|0
suffix:semicolon
id|res
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|res
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
r_case
id|PTRACE_POKETEXT
suffix:colon
multiline_comment|/* write the word at location addr. */
r_case
id|PTRACE_POKEDATA
suffix:colon
id|res
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
(brace
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|child
op_plus
id|KERNEL_STACK_SIZE
op_minus
l_int|32
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
l_int|32
op_logical_and
id|addr
op_ge
l_int|0
)paren
id|regs-&gt;regs
(braket
id|addr
)braket
op_assign
id|data
suffix:semicolon
r_else
r_if
c_cond
(paren
id|addr
op_ge
l_int|32
op_logical_and
id|addr
OL
l_int|64
)paren
(brace
r_int
r_int
r_int
op_star
id|fregs
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;used_math
)paren
(brace
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|child
)paren
(brace
id|enable_cp1
c_func
(paren
)paren
suffix:semicolon
id|r4xx0_save_fp
c_func
(paren
id|child
)paren
suffix:semicolon
id|disable_cp1
c_func
(paren
)paren
suffix:semicolon
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* FP not yet used  */
id|memset
c_func
(paren
op_amp
id|child-&gt;tss.fpu.hard
comma
op_complement
l_int|0
comma
r_sizeof
(paren
id|child-&gt;tss.fpu.hard
)paren
)paren
suffix:semicolon
id|child-&gt;tss.fpu.hard.control
op_assign
l_int|0
suffix:semicolon
)brace
id|fregs
op_assign
(paren
r_int
r_int
r_int
op_star
)paren
op_amp
id|child-&gt;tss.fpu.hard.fp_regs
(braket
l_int|0
)braket
suffix:semicolon
id|fregs
(braket
(paren
id|addr
op_minus
l_int|32
)paren
)braket
op_assign
(paren
r_int
r_int
r_int
)paren
id|data
suffix:semicolon
)brace
r_else
(brace
id|addr
op_sub_assign
l_int|64
suffix:semicolon
r_switch
c_cond
(paren
id|addr
)paren
(brace
r_case
l_int|0
suffix:colon
id|regs-&gt;cp0_epc
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|regs-&gt;lo
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|regs-&gt;hi
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|child-&gt;tss.fpu.hard.control
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* The rest are not allowed. */
id|res
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
r_case
id|PTRACE_SYSCALL
suffix:colon
multiline_comment|/* continue and stop at next (return from) syscall */
r_case
id|PTRACE_CONT
suffix:colon
(brace
multiline_comment|/* restart after signal. */
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
(brace
id|res
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
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
id|res
op_assign
id|data
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * make the child exit.  Best I can do is send it a sigkill. &n;&t; * perhaps it should be put in the status that it wants to &n;&t; * exit.&n;&t; */
r_case
id|PTRACE_KILL
suffix:colon
(brace
r_if
c_cond
(paren
id|child-&gt;state
op_ne
id|TASK_ZOMBIE
)paren
(brace
id|child-&gt;exit_code
op_assign
id|SIGKILL
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
id|res
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
(brace
id|res
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|child-&gt;flags
op_and_assign
op_complement
(paren
id|PF_PTRACED
op_or
id|PF_TRACESYS
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
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_default
suffix:colon
id|res
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
id|res
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
multiline_comment|/*&n;&t; * this isn&squot;t the same as continuing with a signal, but it will do&n;&t; * for normal use.  strace only continues with a signal if the&n;&t; * stopping signal is not SIGTRAP.  -brl&n;&t; */
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
