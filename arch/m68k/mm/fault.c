multiline_comment|/*&n; *  linux/arch/m68k/mm/fault.c&n; *&n; *  Copyright (C) 1995  Hamish Macdonald&n; */
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
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
id|vm_area_struct
op_star
id|vma
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
id|current-&gt;tss.pagedir_v
)paren
suffix:semicolon
macro_line|#endif
id|vma
op_assign
id|find_vma
c_func
(paren
id|current
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
multiline_comment|/*&n;&t; * was it a write?&n;&t; */
r_if
c_cond
(paren
id|error_code
op_amp
l_int|2
)paren
(brace
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
)brace
r_else
(brace
multiline_comment|/* read with protection fault? */
r_if
c_cond
(paren
id|error_code
op_amp
l_int|1
)paren
r_goto
id|bad_area
suffix:semicolon
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
r_if
c_cond
(paren
id|error_code
op_amp
l_int|1
)paren
(brace
id|do_wp_page
c_func
(paren
id|current
comma
id|vma
comma
id|address
comma
id|error_code
op_amp
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|do_no_page
c_func
(paren
id|current
comma
id|vma
comma
id|address
comma
id|error_code
op_amp
l_int|2
)paren
suffix:semicolon
multiline_comment|/* There seems to be a missing invalidate somewhere in do_no_page.&n;&t; * Until I found it, this one cures the problem and makes&n;&t; * 1.2 run on the 68040 (Martin Apel).&n;&t; */
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Something tried to access memory that isn&squot;t in our memory map..&n; * Fix it, but check if it&squot;s kernel or user first..&n; */
id|bad_area
suffix:colon
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
id|current
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