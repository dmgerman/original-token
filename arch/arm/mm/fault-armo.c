multiline_comment|/*&n; *  linux/arch/arm/mm/fault.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Modifications for ARM processor (c) 1995, 1996 Russell King&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|macro|FAULT_CODE_FORCECOW
mdefine_line|#define FAULT_CODE_FORCECOW&t;0x80
DECL|macro|FAULT_CODE_PREFETCH
mdefine_line|#define FAULT_CODE_PREFETCH&t;0x04
DECL|macro|FAULT_CODE_WRITE
mdefine_line|#define FAULT_CODE_WRITE&t;0x02
DECL|macro|FAULT_CODE_USER
mdefine_line|#define FAULT_CODE_USER&t;&t;0x01
DECL|variable|quicklists
r_struct
id|pgtable_cache_struct
id|quicklists
suffix:semicolon
DECL|function|__bad_pmd
r_void
id|__bad_pmd
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad pmd in pte_alloc: %08lx&bslash;n&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_ERRORS
id|__backtrace
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|set_pmd
c_func
(paren
id|pmd
comma
id|mk_pmd
c_func
(paren
id|BAD_PAGETABLE
)paren
)paren
suffix:semicolon
)brace
DECL|function|__bad_pmd_kernel
r_void
id|__bad_pmd_kernel
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad pmd in pte_alloc_kernel: %08lx&bslash;n&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_ERRORS
id|__backtrace
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|set_pmd
c_func
(paren
id|pmd
comma
id|mk_pmd
c_func
(paren
id|BAD_PAGETABLE
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_pgd_slow
id|pgd_t
op_star
id|get_pgd_slow
c_func
(paren
r_void
)paren
(brace
id|pgd_t
op_star
id|pgd
op_assign
(paren
id|pgd_t
op_star
)paren
id|kmalloc
c_func
(paren
id|PTRS_PER_PGD
op_star
id|BYTES_PER_PTR
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|pgd_t
op_star
id|init
suffix:semicolon
r_if
c_cond
(paren
id|pgd
)paren
(brace
id|init
op_assign
id|pgd_offset
c_func
(paren
op_amp
id|init_mm
comma
l_int|0
)paren
suffix:semicolon
id|memzero
(paren
id|pgd
comma
id|USER_PTRS_PER_PGD
op_star
id|BYTES_PER_PTR
)paren
suffix:semicolon
id|memcpy
(paren
id|pgd
op_plus
id|USER_PTRS_PER_PGD
comma
id|init
op_plus
id|USER_PTRS_PER_PGD
comma
(paren
id|PTRS_PER_PGD
op_minus
id|USER_PTRS_PER_PGD
)paren
op_star
id|BYTES_PER_PTR
)paren
suffix:semicolon
)brace
r_return
id|pgd
suffix:semicolon
)brace
DECL|function|get_pte_slow
id|pte_t
op_star
id|get_pte_slow
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|offset
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|kmalloc
(paren
id|PTRS_PER_PTE
op_star
id|BYTES_PER_PTR
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
r_if
c_cond
(paren
id|pte
)paren
(brace
id|memzero
(paren
id|pte
comma
id|PTRS_PER_PTE
op_star
id|BYTES_PER_PTR
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
id|mk_pmd
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
r_return
id|pte
op_plus
id|offset
suffix:semicolon
)brace
id|set_pmd
c_func
(paren
id|pmd
comma
id|mk_pmd
c_func
(paren
id|BAD_PAGETABLE
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|kfree
(paren
id|pte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|__bad_pmd
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
id|pte_t
op_star
)paren
id|pmd_page
c_func
(paren
op_star
id|pmd
)paren
op_plus
id|offset
suffix:semicolon
)brace
r_extern
r_void
id|die_if_kernel
c_func
(paren
r_char
op_star
id|msg
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|err
comma
r_int
r_int
id|ret
)paren
suffix:semicolon
DECL|function|kernel_page_fault
r_static
r_void
id|kernel_page_fault
(paren
r_int
r_int
id|addr
comma
r_int
id|mode
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
multiline_comment|/*&n;&t; * Oops. The kernel tried to access some bad page. We&squot;ll have to&n;&t; * terminate things with extreme prejudice.&n;&t; */
id|pgd_t
op_star
id|pgd
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|PAGE_SIZE
)paren
id|printk
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel NULL pointer dereference&quot;
)paren
suffix:semicolon
r_else
id|printk
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel paging request&quot;
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot; at virtual address %08lx&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
id|printk
(paren
id|KERN_ALERT
l_string|&quot;current-&gt;tss.memmap = %08lX&bslash;n&quot;
comma
id|tsk-&gt;tss.memmap
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
id|printk
(paren
id|KERN_ALERT
l_string|&quot;*pgd = %08lx&quot;
comma
id|pgd_val
(paren
op_star
id|pgd
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd_none
(paren
op_star
id|pgd
)paren
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
(paren
id|pgd
comma
id|addr
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;, *pmd = %08lx&quot;
comma
id|pmd_val
(paren
op_star
id|pmd
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_none
(paren
op_star
id|pmd
)paren
)paren
id|printk
(paren
l_string|&quot;, *pte = %08lx&quot;
comma
id|pte_val
(paren
op_star
id|pte_offset
(paren
id|pmd
comma
id|addr
)paren
)paren
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|die_if_kernel
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
id|mode
comma
id|SIGKILL
)paren
suffix:semicolon
id|do_exit
(paren
id|SIGKILL
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|handle_dataabort
id|handle_dataabort
(paren
r_int
r_int
id|addr
comma
r_int
id|mode
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
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
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|tsk
op_assign
id|current
suffix:semicolon
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
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
(paren
id|mm
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
r_goto
id|bad_area
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|vma-&gt;vm_start
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
op_logical_or
id|expand_stack
(paren
id|vma
comma
id|addr
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, we have a good vm_area for this memory access, so&n;&t; * we can handle it..&n;&t; */
id|good_area
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode
op_amp
id|FAULT_CODE_WRITE
)paren
)paren
(brace
multiline_comment|/* write? */
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
r_else
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
id|handle_mm_fault
(paren
id|tsk
comma
id|vma
comma
id|addr
comma
id|mode
op_amp
(paren
id|FAULT_CODE_WRITE
op_or
id|FAULT_CODE_FORCECOW
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Something tried to access memory that isn&squot;t in our memory map..&n;&t; * Fix it, but check if it&squot;s kernel or user first..&n;&t; */
id|bad_area
suffix:colon
id|up
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|FAULT_CODE_USER
)paren
(brace
singleline_comment|//extern int console_loglevel;
singleline_comment|//cli();
id|tsk-&gt;tss.error_code
op_assign
id|mode
suffix:semicolon
id|tsk-&gt;tss.trap_no
op_assign
l_int|14
suffix:semicolon
singleline_comment|//console_loglevel = 9;
id|printk
(paren
l_string|&quot;%s: memory violation at pc=0x%08lx, lr=0x%08lx (bad address=0x%08lx, code %d)&bslash;n&quot;
comma
id|tsk-&gt;comm
comma
id|regs-&gt;ARM_pc
comma
id|regs-&gt;ARM_lr
comma
id|addr
comma
id|mode
)paren
suffix:semicolon
singleline_comment|//#ifdef DEBUG
id|show_regs
(paren
id|regs
)paren
suffix:semicolon
id|c_backtrace
(paren
id|regs-&gt;ARM_fp
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|//#endif
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|tsk
)paren
suffix:semicolon
singleline_comment|//while (1);
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Are we prepared to handle this kernel fault?  */
r_if
c_cond
(paren
(paren
id|fixup
op_assign
id|search_exception_table
c_func
(paren
id|regs-&gt;ARM_pc
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Exception at [&lt;%lx&gt;] addr=%lx (fixup: %lx)&bslash;n&quot;
comma
id|tsk-&gt;comm
comma
id|regs-&gt;ARM_pc
comma
id|addr
comma
id|fixup
)paren
suffix:semicolon
id|regs-&gt;ARM_pc
op_assign
id|fixup
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|kernel_page_fault
(paren
id|addr
comma
id|mode
comma
id|regs
comma
id|tsk
comma
id|mm
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle a data abort.  Note that we have to handle a range of addresses&n; * on ARM2/3 for ldm.  If both pages are zero-mapped, then we have to force&n; * a copy-on-write&n; */
id|asmlinkage
r_void
DECL|function|do_DataAbort
id|do_DataAbort
(paren
r_int
r_int
id|min_addr
comma
r_int
r_int
id|max_addr
comma
r_int
id|mode
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|handle_dataabort
(paren
id|min_addr
comma
id|mode
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|min_addr
op_xor
id|max_addr
)paren
op_rshift
id|PAGE_SHIFT
)paren
id|handle_dataabort
(paren
id|max_addr
comma
id|mode
op_or
id|FAULT_CODE_FORCECOW
comma
id|regs
)paren
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|do_PrefetchAbort
id|do_PrefetchAbort
(paren
r_int
r_int
id|addr
comma
r_int
id|mode
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
id|the
id|memc
id|mapping
r_for
id|this
id|page
id|exists
op_minus
id|can
id|check
id|now
dot
dot
dot
)paren
(brace
id|printk
(paren
l_string|&quot;Page in, but got abort (undefined instruction?)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
id|handle_dataabort
(paren
id|addr
comma
id|mode
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
