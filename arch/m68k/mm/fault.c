multiline_comment|/*&n; *  linux/arch/m68k/mm/fault.c&n; *&n; *  Copyright (C) 1995  Hamish Macdonald&n; */
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
r_extern
r_void
id|die_if_kernel
c_func
(paren
r_char
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_const
r_int
id|frame_extra_sizes
(braket
)braket
suffix:semicolon
multiline_comment|/* in m68k/kernel/signal.c */
multiline_comment|/*&n; * This routine handles page faults.  It determines the problem, and&n; * then passes it off to one of the appropriate routines.&n; *&n; * error_code:&n; *&t;bit 0 == 0 means no page found, 1 means protection fault&n; *&t;bit 1 == 0 means read, 1 means write&n; *&n; * If this routine detects a bad access, it returns 1, otherwise it&n; * returns 0.&n; */
DECL|function|do_page_fault
id|asmlinkage
r_int
id|do_page_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|address
comma
r_int
r_int
id|error_code
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
r_int
id|fixup
suffix:semicolon
r_int
id|write
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;regs-&gt;sr=%#x, regs-&gt;pc=%#lx, address=%#lx, %ld, %p&bslash;n&quot;
comma
id|regs-&gt;sr
comma
id|regs-&gt;pc
comma
id|address
comma
id|error_code
comma
id|tsk-&gt;mm-&gt;pgd
)paren
suffix:semicolon
macro_line|#endif
id|down
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
)paren
r_goto
id|bad_area
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_start
op_le
id|address
)paren
r_goto
id|good_area
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
r_goto
id|bad_area
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
multiline_comment|/* Accessing the stack below usp is always a bug.  The&n;&t;&t;   &quot;+ 256&quot; is there due to some instructions doing&n;&t;&t;   pre-decrement on the stack and that doesn&squot;t show up&n;&t;&t;   until later.  */
r_if
c_cond
(paren
id|address
op_plus
l_int|256
OL
id|rdusp
c_func
(paren
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
)brace
r_if
c_cond
(paren
id|expand_stack
c_func
(paren
id|vma
comma
id|address
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
multiline_comment|/*&n; * Ok, we have a good vm_area for this memory access, so&n; * we can handle it..&n; */
id|good_area
suffix:colon
id|write
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|error_code
op_amp
l_int|3
)paren
(brace
r_default
suffix:colon
(brace
)brace
multiline_comment|/* 3: write, present */
multiline_comment|/* fall through */
r_case
l_int|2
suffix:colon
multiline_comment|/* write, not present */
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_WRITE
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
id|write
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* read, present */
r_goto
id|bad_area
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/* read, not present */
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
(paren
id|VM_READ
op_or
id|VM_EXEC
)paren
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
)brace
id|handle_mm_fault
c_func
(paren
id|current
comma
id|vma
comma
id|address
comma
id|write
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
multiline_comment|/* There seems to be a missing invalidate somewhere in do_no_page.&n;&t; * Until I found it, this one cures the problem and makes&n;&t; * 1.2 run on the 68040 (Martin Apel).&n;&t; */
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
id|flush_tlb_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Something tried to access memory that isn&squot;t in our memory map..&n; * Fix it, but check if it&squot;s kernel or user first..&n; */
id|bad_area
suffix:colon
id|up
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
multiline_comment|/* Are we prepared to handle this fault?  */
r_if
c_cond
(paren
(paren
id|fixup
op_assign
id|search_exception_table
c_func
(paren
id|regs-&gt;pc
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_struct
id|pt_regs
op_star
id|tregs
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Exception at [&lt;%lx&gt;] (%lx)&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|regs-&gt;pc
comma
id|fixup
)paren
suffix:semicolon
multiline_comment|/* Create a new four word stack frame, discarding the old&n;&t;&t;   one.  */
id|regs-&gt;stkadj
op_assign
id|frame_extra_sizes
(braket
id|regs-&gt;format
)braket
suffix:semicolon
id|tregs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
id|ulong
)paren
id|regs
op_plus
id|regs-&gt;stkadj
)paren
suffix:semicolon
id|tregs-&gt;vector
op_assign
id|regs-&gt;vector
suffix:semicolon
id|tregs-&gt;format
op_assign
l_int|0
suffix:semicolon
id|tregs-&gt;pc
op_assign
id|fixup
suffix:semicolon
id|tregs-&gt;sr
op_assign
id|regs-&gt;sr
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
multiline_comment|/* User memory access */
id|force_sig
(paren
id|SIGSEGV
comma
id|tsk
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Oops. The kernel tried to access some bad page. We&squot;ll have to&n; * terminate things with extreme prejudice.&n; */
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|address
OL
id|PAGE_SIZE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel NULL pointer dereference&quot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel access&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; at virtual address %08lx&bslash;n&quot;
comma
id|address
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
id|error_code
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
