multiline_comment|/*&n; *  linux/kernel/vm86.c&n; *&n; *  Copyright (C) 1994  Linus Torvalds&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * Known problems:&n; *&n; * Interrupt handling is not guaranteed:&n; * - a real x86 will disable all interrupts for one instruction&n; *   after a &quot;mov ss,xx&quot; to make stack handling atomic even without&n; *   the &squot;lss&squot; instruction. We can&squot;t guarantee this in v86 mode,&n; *   as the next instruction might result in a page fault or similar.&n; * - a real x86 will have interrupts disabled for one instruction&n; *   past the &squot;sti&squot; that enables them. We don&squot;t bother with all the&n; *   details yet.&n; *&n; * Let&squot;s hope these problems do not actually matter for anything.&n; */
DECL|macro|KVM86
mdefine_line|#define KVM86&t;((struct kernel_vm86_struct *)regs)
DECL|macro|VMPI
mdefine_line|#define VMPI &t;KVM86-&gt;vm86plus
multiline_comment|/*&n; * 8- and 16-bit register defines..&n; */
DECL|macro|AL
mdefine_line|#define AL(regs)&t;(((unsigned char *)&amp;((regs)-&gt;eax))[0])
DECL|macro|AH
mdefine_line|#define AH(regs)&t;(((unsigned char *)&amp;((regs)-&gt;eax))[1])
DECL|macro|IP
mdefine_line|#define IP(regs)&t;(*(unsigned short *)&amp;((regs)-&gt;eip))
DECL|macro|SP
mdefine_line|#define SP(regs)&t;(*(unsigned short *)&amp;((regs)-&gt;esp))
multiline_comment|/*&n; * virtual flags (16 and 32-bit versions)&n; */
DECL|macro|VFLAGS
mdefine_line|#define VFLAGS&t;(*(unsigned short *)&amp;(current-&gt;thread.v86flags))
DECL|macro|VEFLAGS
mdefine_line|#define VEFLAGS&t;(current-&gt;thread.v86flags)
DECL|macro|set_flags
mdefine_line|#define set_flags(X,new,mask) &bslash;&n;((X) = ((X) &amp; ~(mask)) | ((new) &amp; (mask)))
DECL|macro|SAFE_MASK
mdefine_line|#define SAFE_MASK&t;(0xDD5)
DECL|macro|RETURN_MASK
mdefine_line|#define RETURN_MASK&t;(0xDFF)
DECL|macro|VM86_REGS_PART2
mdefine_line|#define VM86_REGS_PART2 orig_eax
DECL|macro|VM86_REGS_SIZE1
mdefine_line|#define VM86_REGS_SIZE1 &bslash;&n;        ( (unsigned)( &amp; (((struct kernel_vm86_regs *)0)-&gt;VM86_REGS_PART2) ) )
DECL|macro|VM86_REGS_SIZE2
mdefine_line|#define VM86_REGS_SIZE2 (sizeof(struct kernel_vm86_regs) - VM86_REGS_SIZE1)
id|asmlinkage
r_struct
id|pt_regs
op_star
id|FASTCALL
c_func
(paren
id|save_v86_state
c_func
(paren
r_struct
id|kernel_vm86_regs
op_star
id|regs
)paren
)paren
suffix:semicolon
DECL|function|save_v86_state
r_struct
id|pt_regs
op_star
id|save_v86_state
c_func
(paren
r_struct
id|kernel_vm86_regs
op_star
id|regs
)paren
(brace
r_struct
id|tss_struct
op_star
id|tss
suffix:semicolon
r_struct
id|pt_regs
op_star
id|ret
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;thread.vm86_info
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;no vm86_info: BAD&bslash;n&quot;
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
id|set_flags
c_func
(paren
id|regs-&gt;eflags
comma
id|VEFLAGS
comma
id|VIF_MASK
op_or
id|current-&gt;thread.v86mask
)paren
suffix:semicolon
id|tmp
op_assign
id|copy_to_user
c_func
(paren
op_amp
id|current-&gt;thread.vm86_info-&gt;regs
comma
id|regs
comma
id|VM86_REGS_SIZE1
)paren
suffix:semicolon
id|tmp
op_add_assign
id|copy_to_user
c_func
(paren
op_amp
id|current-&gt;thread.vm86_info-&gt;regs.VM86_REGS_PART2
comma
op_amp
id|regs-&gt;VM86_REGS_PART2
comma
id|VM86_REGS_SIZE2
)paren
suffix:semicolon
id|tmp
op_add_assign
id|put_user
c_func
(paren
id|current-&gt;thread.screen_bitmap
comma
op_amp
id|current-&gt;thread.vm86_info-&gt;screen_bitmap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;vm86: could not access userspace vm86_info&bslash;n&quot;
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
id|tss
op_assign
id|init_tss
op_plus
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|tss-&gt;esp0
op_assign
id|current-&gt;thread.esp0
op_assign
id|current-&gt;thread.saved_esp0
suffix:semicolon
id|current-&gt;thread.saved_esp0
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|KVM86-&gt;regs32
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|mark_screen_rdonly
r_static
r_void
id|mark_screen_rdonly
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|tsk-&gt;mm
comma
l_int|0xA0000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|pgd_ERROR
c_func
(paren
op_star
id|pgd
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|pgd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
l_int|0xA0000
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
r_return
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
id|pmd_ERROR
c_func
(paren
op_star
id|pmd
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pte
op_assign
id|pte_offset
c_func
(paren
id|pmd
comma
l_int|0xA0000
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pte_present
c_func
(paren
op_star
id|pte
)paren
)paren
id|set_pte
c_func
(paren
id|pte
comma
id|pte_wrprotect
c_func
(paren
op_star
id|pte
)paren
)paren
suffix:semicolon
id|pte
op_increment
suffix:semicolon
)brace
id|flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
id|do_vm86_irq_handling
c_func
(paren
r_int
id|subfunction
comma
r_int
id|irqnumber
)paren
suffix:semicolon
r_static
r_void
id|do_sys_vm86
c_func
(paren
r_struct
id|kernel_vm86_struct
op_star
id|info
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
DECL|function|sys_vm86old
id|asmlinkage
r_int
id|sys_vm86old
c_func
(paren
r_struct
id|vm86_struct
op_star
id|v86
)paren
(brace
r_struct
id|kernel_vm86_struct
id|info
suffix:semicolon
multiline_comment|/* declare this _on top_,&n;&t;&t;&t;&t;&t; * this avoids wasting of stack space.&n;&t;&t;&t;&t;&t; * This remains on the stack until we&n;&t;&t;&t;&t;&t; * return to 32 bit user space.&n;&t;&t;&t;&t;&t; */
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
r_int
id|tmp
comma
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
id|tsk
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
id|tsk-&gt;thread.saved_esp0
)paren
r_goto
id|out
suffix:semicolon
id|tmp
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|info
comma
id|v86
comma
id|VM86_REGS_SIZE1
)paren
suffix:semicolon
id|tmp
op_add_assign
id|copy_from_user
c_func
(paren
op_amp
id|info.regs.VM86_REGS_PART2
comma
op_amp
id|v86-&gt;regs.VM86_REGS_PART2
comma
(paren
r_int
)paren
op_amp
id|info.vm86plus
op_minus
(paren
r_int
)paren
op_amp
id|info.regs.VM86_REGS_PART2
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
r_goto
id|out
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|info.vm86plus
comma
l_int|0
comma
(paren
r_int
)paren
op_amp
id|info.regs32
op_minus
(paren
r_int
)paren
op_amp
id|info.vm86plus
)paren
suffix:semicolon
id|info.regs32
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|v86
suffix:semicolon
id|tsk-&gt;thread.vm86_info
op_assign
id|v86
suffix:semicolon
id|do_sys_vm86
c_func
(paren
op_amp
id|info
comma
id|tsk
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* we never return here */
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_vm86
id|asmlinkage
r_int
id|sys_vm86
c_func
(paren
r_int
r_int
id|subfunction
comma
r_struct
id|vm86plus_struct
op_star
id|v86
)paren
(brace
r_struct
id|kernel_vm86_struct
id|info
suffix:semicolon
multiline_comment|/* declare this _on top_,&n;&t;&t;&t;&t;&t; * this avoids wasting of stack space.&n;&t;&t;&t;&t;&t; * This remains on the stack until we&n;&t;&t;&t;&t;&t; * return to 32 bit user space.&n;&t;&t;&t;&t;&t; */
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
r_int
id|tmp
comma
id|ret
suffix:semicolon
id|tsk
op_assign
id|current
suffix:semicolon
r_switch
c_cond
(paren
id|subfunction
)paren
(brace
r_case
id|VM86_REQUEST_IRQ
suffix:colon
r_case
id|VM86_FREE_IRQ
suffix:colon
r_case
id|VM86_GET_IRQ_BITS
suffix:colon
r_case
id|VM86_GET_AND_RESET_IRQ
suffix:colon
id|ret
op_assign
id|do_vm86_irq_handling
c_func
(paren
id|subfunction
comma
(paren
r_int
)paren
id|v86
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|VM86_PLUS_INSTALL_CHECK
suffix:colon
multiline_comment|/* NOTE: on old vm86 stuff this will return the error&n;&t;&t;&t;   from verify_area(), because the subfunction is&n;&t;&t;&t;   interpreted as (invalid) address to vm86_struct.&n;&t;&t;&t;   So the installation check works.&n;&t;&t;&t; */
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* we come here only for functions VM86_ENTER, VM86_ENTER_NO_BYPASS */
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|tsk-&gt;thread.saved_esp0
)paren
r_goto
id|out
suffix:semicolon
id|tmp
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|info
comma
id|v86
comma
id|VM86_REGS_SIZE1
)paren
suffix:semicolon
id|tmp
op_add_assign
id|copy_from_user
c_func
(paren
op_amp
id|info.regs.VM86_REGS_PART2
comma
op_amp
id|v86-&gt;regs.VM86_REGS_PART2
comma
(paren
r_int
)paren
op_amp
id|info.regs32
op_minus
(paren
r_int
)paren
op_amp
id|info.regs.VM86_REGS_PART2
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
r_goto
id|out
suffix:semicolon
id|info.regs32
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|subfunction
suffix:semicolon
id|info.vm86plus.is_vm86pus
op_assign
l_int|1
suffix:semicolon
id|tsk-&gt;thread.vm86_info
op_assign
(paren
r_struct
id|vm86_struct
op_star
)paren
id|v86
suffix:semicolon
id|do_sys_vm86
c_func
(paren
op_amp
id|info
comma
id|tsk
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* we never return here */
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|do_sys_vm86
r_static
r_void
id|do_sys_vm86
c_func
(paren
r_struct
id|kernel_vm86_struct
op_star
id|info
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_struct
id|tss_struct
op_star
id|tss
suffix:semicolon
multiline_comment|/*&n; * make sure the vm86() system call doesn&squot;t try to do anything silly&n; */
id|info-&gt;regs.__null_ds
op_assign
l_int|0
suffix:semicolon
id|info-&gt;regs.__null_es
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* we are clearing fs,gs later just before &quot;jmp ret_from_sys_call&quot;,&n; * because starting with Linux 2.1.x they aren&squot;t no longer saved/restored&n; */
multiline_comment|/*&n; * The eflags register is also special: we cannot trust that the user&n; * has set it up safely, so this makes sure interrupt etc flags are&n; * inherited from protected mode.&n; */
id|VEFLAGS
op_assign
id|info-&gt;regs.eflags
suffix:semicolon
id|info-&gt;regs.eflags
op_and_assign
id|SAFE_MASK
suffix:semicolon
id|info-&gt;regs.eflags
op_or_assign
id|info-&gt;regs32-&gt;eflags
op_amp
op_complement
id|SAFE_MASK
suffix:semicolon
id|info-&gt;regs.eflags
op_or_assign
id|VM_MASK
suffix:semicolon
r_switch
c_cond
(paren
id|info-&gt;cpu_type
)paren
(brace
r_case
id|CPU_286
suffix:colon
id|tsk-&gt;thread.v86mask
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_386
suffix:colon
id|tsk-&gt;thread.v86mask
op_assign
id|NT_MASK
op_or
id|IOPL_MASK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_486
suffix:colon
id|tsk-&gt;thread.v86mask
op_assign
id|AC_MASK
op_or
id|NT_MASK
op_or
id|IOPL_MASK
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|tsk-&gt;thread.v86mask
op_assign
id|ID_MASK
op_or
id|AC_MASK
op_or
id|NT_MASK
op_or
id|IOPL_MASK
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n; * Save old state, set default return value (%eax) to 0&n; */
id|info-&gt;regs32-&gt;eax
op_assign
l_int|0
suffix:semicolon
id|tsk-&gt;thread.saved_esp0
op_assign
id|tsk-&gt;thread.esp0
suffix:semicolon
id|tss
op_assign
id|init_tss
op_plus
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|tss-&gt;esp0
op_assign
id|tsk-&gt;thread.esp0
op_assign
(paren
r_int
r_int
)paren
op_amp
id|info-&gt;VM86_TSS_ESP0
suffix:semicolon
id|tsk-&gt;thread.screen_bitmap
op_assign
id|info-&gt;screen_bitmap
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;flags
op_amp
id|VM86_SCREEN_BITMAP
)paren
id|mark_screen_rdonly
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;xorl %%eax,%%eax; movl %%eax,%%fs; movl %%eax,%%gs&bslash;n&bslash;t&quot;
l_string|&quot;movl %0,%%esp&bslash;n&bslash;t&quot;
l_string|&quot;jmp ret_from_sys_call&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|info-&gt;regs
)paren
comma
l_string|&quot;b&quot;
(paren
id|tsk
)paren
suffix:colon
l_string|&quot;ax&quot;
)paren
suffix:semicolon
multiline_comment|/* we never return here */
)brace
DECL|function|return_to_32bit
r_static
r_inline
r_void
id|return_to_32bit
c_func
(paren
r_struct
id|kernel_vm86_regs
op_star
id|regs16
comma
r_int
id|retval
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs32
suffix:semicolon
id|regs32
op_assign
id|save_v86_state
c_func
(paren
id|regs16
)paren
suffix:semicolon
id|regs32-&gt;eax
op_assign
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movl %0,%%esp&bslash;n&bslash;t&quot;
l_string|&quot;jmp ret_from_sys_call&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|regs32
)paren
comma
l_string|&quot;b&quot;
(paren
id|current
)paren
)paren
suffix:semicolon
)brace
DECL|function|set_IF
r_static
r_inline
r_void
id|set_IF
c_func
(paren
r_struct
id|kernel_vm86_regs
op_star
id|regs
)paren
(brace
id|VEFLAGS
op_or_assign
id|VIF_MASK
suffix:semicolon
r_if
c_cond
(paren
id|VEFLAGS
op_amp
id|VIP_MASK
)paren
id|return_to_32bit
c_func
(paren
id|regs
comma
id|VM86_STI
)paren
suffix:semicolon
)brace
DECL|function|clear_IF
r_static
r_inline
r_void
id|clear_IF
c_func
(paren
r_struct
id|kernel_vm86_regs
op_star
id|regs
)paren
(brace
id|VEFLAGS
op_and_assign
op_complement
id|VIF_MASK
suffix:semicolon
)brace
DECL|function|clear_TF
r_static
r_inline
r_void
id|clear_TF
c_func
(paren
r_struct
id|kernel_vm86_regs
op_star
id|regs
)paren
(brace
id|regs-&gt;eflags
op_and_assign
op_complement
id|TF_MASK
suffix:semicolon
)brace
DECL|function|set_vflags_long
r_static
r_inline
r_void
id|set_vflags_long
c_func
(paren
r_int
r_int
id|eflags
comma
r_struct
id|kernel_vm86_regs
op_star
id|regs
)paren
(brace
id|set_flags
c_func
(paren
id|VEFLAGS
comma
id|eflags
comma
id|current-&gt;thread.v86mask
)paren
suffix:semicolon
id|set_flags
c_func
(paren
id|regs-&gt;eflags
comma
id|eflags
comma
id|SAFE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eflags
op_amp
id|IF_MASK
)paren
id|set_IF
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
DECL|function|set_vflags_short
r_static
r_inline
r_void
id|set_vflags_short
c_func
(paren
r_int
r_int
id|flags
comma
r_struct
id|kernel_vm86_regs
op_star
id|regs
)paren
(brace
id|set_flags
c_func
(paren
id|VFLAGS
comma
id|flags
comma
id|current-&gt;thread.v86mask
)paren
suffix:semicolon
id|set_flags
c_func
(paren
id|regs-&gt;eflags
comma
id|flags
comma
id|SAFE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|IF_MASK
)paren
id|set_IF
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
DECL|function|get_vflags
r_static
r_inline
r_int
r_int
id|get_vflags
c_func
(paren
r_struct
id|kernel_vm86_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|flags
op_assign
id|regs-&gt;eflags
op_amp
id|RETURN_MASK
suffix:semicolon
r_if
c_cond
(paren
id|VEFLAGS
op_amp
id|VIF_MASK
)paren
id|flags
op_or_assign
id|IF_MASK
suffix:semicolon
r_return
id|flags
op_or
(paren
id|VEFLAGS
op_amp
id|current-&gt;thread.v86mask
)paren
suffix:semicolon
)brace
DECL|function|is_revectored
r_static
r_inline
r_int
id|is_revectored
c_func
(paren
r_int
id|nr
comma
r_struct
id|revectored_struct
op_star
id|bitmap
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;btl %2,%1&bslash;n&bslash;tsbbl %0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|bitmap
)paren
comma
l_string|&quot;r&quot;
(paren
id|nr
)paren
)paren
suffix:semicolon
r_return
id|nr
suffix:semicolon
)brace
multiline_comment|/*&n; * Boy are these ugly, but we need to do the correct 16-bit arithmetic.&n; * Gcc makes a mess of it, so we do it inline and use non-obvious calling&n; * conventions..&n; */
DECL|macro|pushb
mdefine_line|#define pushb(base, ptr, val) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;decw %w0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %2,0(%1,%0)&quot; &bslash;&n;&t;: &quot;=r&quot; (ptr) &bslash;&n;&t;: &quot;r&quot; (base), &quot;q&quot; (val), &quot;0&quot; (ptr))
DECL|macro|pushw
mdefine_line|#define pushw(base, ptr, val) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;decw %w0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %h2,0(%1,%0)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;decw %w0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %b2,0(%1,%0)&quot; &bslash;&n;&t;: &quot;=r&quot; (ptr) &bslash;&n;&t;: &quot;r&quot; (base), &quot;q&quot; (val), &quot;0&quot; (ptr))
DECL|macro|pushl
mdefine_line|#define pushl(base, ptr, val) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;decw %w0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %h2,0(%1,%0)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;decw %w0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %b2,0(%1,%0)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;decw %w0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %h2,0(%1,%0)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;decw %w0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %b2,0(%1,%0)&quot; &bslash;&n;&t;: &quot;=r&quot; (ptr) &bslash;&n;&t;: &quot;r&quot; (base), &quot;q&quot; (val), &quot;0&quot; (ptr))
DECL|macro|popb
mdefine_line|#define popb(base, ptr) &bslash;&n;({ unsigned long __res; &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;movb 0(%1,%0),%b2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;incw %w0&quot; &bslash;&n;&t;: &quot;=r&quot; (ptr), &quot;=r&quot; (base), &quot;=q&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (ptr), &quot;1&quot; (base), &quot;2&quot; (0)); &bslash;&n;__res; })
DECL|macro|popw
mdefine_line|#define popw(base, ptr) &bslash;&n;({ unsigned long __res; &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;movb 0(%1,%0),%b2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;incw %w0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb 0(%1,%0),%h2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;incw %w0&quot; &bslash;&n;&t;: &quot;=r&quot; (ptr), &quot;=r&quot; (base), &quot;=q&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (ptr), &quot;1&quot; (base), &quot;2&quot; (0)); &bslash;&n;__res; })
DECL|macro|popl
mdefine_line|#define popl(base, ptr) &bslash;&n;({ unsigned long __res; &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;movb 0(%1,%0),%b2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;incw %w0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb 0(%1,%0),%h2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;incw %w0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb 0(%1,%0),%b2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;incw %w0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb 0(%1,%0),%h2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;incw %w0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%2&quot; &bslash;&n;&t;: &quot;=r&quot; (ptr), &quot;=r&quot; (base), &quot;=q&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (ptr), &quot;1&quot; (base)); &bslash;&n;__res; })
DECL|function|do_int
r_static
r_void
id|do_int
c_func
(paren
r_struct
id|kernel_vm86_regs
op_star
id|regs
comma
r_int
id|i
comma
r_int
r_char
op_star
id|ssp
comma
r_int
r_int
id|sp
)paren
(brace
r_int
r_int
op_star
id|intr_ptr
comma
id|segoffs
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;cs
op_eq
id|BIOSSEG
)paren
r_goto
id|cannot_handle
suffix:semicolon
r_if
c_cond
(paren
id|is_revectored
c_func
(paren
id|i
comma
op_amp
id|KVM86-&gt;int_revectored
)paren
)paren
r_goto
id|cannot_handle
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0x21
op_logical_and
id|is_revectored
c_func
(paren
id|AH
c_func
(paren
id|regs
)paren
comma
op_amp
id|KVM86-&gt;int21_revectored
)paren
)paren
r_goto
id|cannot_handle
suffix:semicolon
id|intr_ptr
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|i
op_lshift
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|segoffs
comma
id|intr_ptr
)paren
)paren
r_goto
id|cannot_handle
suffix:semicolon
r_if
c_cond
(paren
(paren
id|segoffs
op_rshift
l_int|16
)paren
op_eq
id|BIOSSEG
)paren
r_goto
id|cannot_handle
suffix:semicolon
id|pushw
c_func
(paren
id|ssp
comma
id|sp
comma
id|get_vflags
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
id|pushw
c_func
(paren
id|ssp
comma
id|sp
comma
id|regs-&gt;cs
)paren
suffix:semicolon
id|pushw
c_func
(paren
id|ssp
comma
id|sp
comma
id|IP
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
id|regs-&gt;cs
op_assign
id|segoffs
op_rshift
l_int|16
suffix:semicolon
id|SP
c_func
(paren
id|regs
)paren
op_sub_assign
l_int|6
suffix:semicolon
id|IP
c_func
(paren
id|regs
)paren
op_assign
id|segoffs
op_amp
l_int|0xffff
suffix:semicolon
id|clear_TF
c_func
(paren
id|regs
)paren
suffix:semicolon
id|clear_IF
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
id|cannot_handle
suffix:colon
id|return_to_32bit
c_func
(paren
id|regs
comma
id|VM86_INTx
op_plus
(paren
id|i
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
)brace
DECL|function|handle_vm86_trap
r_int
id|handle_vm86_trap
c_func
(paren
r_struct
id|kernel_vm86_regs
op_star
id|regs
comma
r_int
id|error_code
comma
r_int
id|trapno
)paren
(brace
r_if
c_cond
(paren
id|VMPI.is_vm86pus
)paren
(brace
r_if
c_cond
(paren
(paren
id|trapno
op_eq
l_int|3
)paren
op_logical_or
(paren
id|trapno
op_eq
l_int|1
)paren
)paren
id|return_to_32bit
c_func
(paren
id|regs
comma
id|VM86_TRAP
op_plus
(paren
id|trapno
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
id|do_int
c_func
(paren
id|regs
comma
id|trapno
comma
(paren
r_int
r_char
op_star
)paren
(paren
id|regs-&gt;ss
op_lshift
l_int|4
)paren
comma
id|SP
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|trapno
op_ne
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* we let this handle by the calling routine */
r_if
c_cond
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|sigdelset
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|SIGTRAP
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|send_sig
c_func
(paren
id|SIGTRAP
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|current-&gt;thread.trap_no
op_assign
id|trapno
suffix:semicolon
id|current-&gt;thread.error_code
op_assign
id|error_code
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|handle_vm86_fault
r_void
id|handle_vm86_fault
c_func
(paren
r_struct
id|kernel_vm86_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
(brace
r_int
r_char
op_star
id|csp
comma
op_star
id|ssp
suffix:semicolon
r_int
r_int
id|ip
comma
id|sp
suffix:semicolon
DECL|macro|CHECK_IF_IN_TRAP
mdefine_line|#define CHECK_IF_IN_TRAP &bslash;&n;&t;if (VMPI.vm86dbg_active &amp;&amp; VMPI.vm86dbg_TFpendig) &bslash;&n;&t;&t;pushw(ssp,sp,popw(ssp,sp) | TF_MASK);
DECL|macro|VM86_FAULT_RETURN
mdefine_line|#define VM86_FAULT_RETURN &bslash;&n;&t;if (VMPI.force_return_for_pic  &amp;&amp; (VEFLAGS &amp; IF_MASK)) &bslash;&n;&t;&t;return_to_32bit(regs, VM86_PICRETURN); &bslash;&n;&t;return;
id|csp
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|regs-&gt;cs
op_lshift
l_int|4
)paren
suffix:semicolon
id|ssp
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|regs-&gt;ss
op_lshift
l_int|4
)paren
suffix:semicolon
id|sp
op_assign
id|SP
c_func
(paren
id|regs
)paren
suffix:semicolon
id|ip
op_assign
id|IP
c_func
(paren
id|regs
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|popb
c_func
(paren
id|csp
comma
id|ip
)paren
)paren
(brace
multiline_comment|/* operand size override */
r_case
l_int|0x66
suffix:colon
r_switch
c_cond
(paren
id|popb
c_func
(paren
id|csp
comma
id|ip
)paren
)paren
(brace
multiline_comment|/* pushfd */
r_case
l_int|0x9c
suffix:colon
id|SP
c_func
(paren
id|regs
)paren
op_sub_assign
l_int|4
suffix:semicolon
id|IP
c_func
(paren
id|regs
)paren
op_add_assign
l_int|2
suffix:semicolon
id|pushl
c_func
(paren
id|ssp
comma
id|sp
comma
id|get_vflags
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
id|VM86_FAULT_RETURN
suffix:semicolon
multiline_comment|/* popfd */
r_case
l_int|0x9d
suffix:colon
id|SP
c_func
(paren
id|regs
)paren
op_add_assign
l_int|4
suffix:semicolon
id|IP
c_func
(paren
id|regs
)paren
op_add_assign
l_int|2
suffix:semicolon
id|CHECK_IF_IN_TRAP
id|set_vflags_long
c_func
(paren
id|popl
c_func
(paren
id|ssp
comma
id|sp
)paren
comma
id|regs
)paren
suffix:semicolon
id|VM86_FAULT_RETURN
suffix:semicolon
multiline_comment|/* iretd */
r_case
l_int|0xcf
suffix:colon
id|SP
c_func
(paren
id|regs
)paren
op_add_assign
l_int|12
suffix:semicolon
id|IP
c_func
(paren
id|regs
)paren
op_assign
(paren
r_int
r_int
)paren
id|popl
c_func
(paren
id|ssp
comma
id|sp
)paren
suffix:semicolon
id|regs-&gt;cs
op_assign
(paren
r_int
r_int
)paren
id|popl
c_func
(paren
id|ssp
comma
id|sp
)paren
suffix:semicolon
id|CHECK_IF_IN_TRAP
id|set_vflags_long
c_func
(paren
id|popl
c_func
(paren
id|ssp
comma
id|sp
)paren
comma
id|regs
)paren
suffix:semicolon
id|VM86_FAULT_RETURN
suffix:semicolon
multiline_comment|/* need this to avoid a fallthrough */
r_default
suffix:colon
id|return_to_32bit
c_func
(paren
id|regs
comma
id|VM86_UNKNOWN
)paren
suffix:semicolon
)brace
multiline_comment|/* pushf */
r_case
l_int|0x9c
suffix:colon
id|SP
c_func
(paren
id|regs
)paren
op_sub_assign
l_int|2
suffix:semicolon
id|IP
c_func
(paren
id|regs
)paren
op_increment
suffix:semicolon
id|pushw
c_func
(paren
id|ssp
comma
id|sp
comma
id|get_vflags
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
id|VM86_FAULT_RETURN
suffix:semicolon
multiline_comment|/* popf */
r_case
l_int|0x9d
suffix:colon
id|SP
c_func
(paren
id|regs
)paren
op_add_assign
l_int|2
suffix:semicolon
id|IP
c_func
(paren
id|regs
)paren
op_increment
suffix:semicolon
id|CHECK_IF_IN_TRAP
id|set_vflags_short
c_func
(paren
id|popw
c_func
(paren
id|ssp
comma
id|sp
)paren
comma
id|regs
)paren
suffix:semicolon
id|VM86_FAULT_RETURN
suffix:semicolon
multiline_comment|/* int xx */
r_case
l_int|0xcd
suffix:colon
(brace
r_int
id|intno
op_assign
id|popb
c_func
(paren
id|csp
comma
id|ip
)paren
suffix:semicolon
id|IP
c_func
(paren
id|regs
)paren
op_add_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|VMPI.vm86dbg_active
)paren
(brace
r_if
c_cond
(paren
(paren
l_int|1
op_lshift
(paren
id|intno
op_amp
l_int|7
)paren
)paren
op_amp
id|VMPI.vm86dbg_intxxtab
(braket
id|intno
op_rshift
l_int|3
)braket
)paren
id|return_to_32bit
c_func
(paren
id|regs
comma
id|VM86_INTx
op_plus
(paren
id|intno
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
)brace
id|do_int
c_func
(paren
id|regs
comma
id|intno
comma
id|ssp
comma
id|sp
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* iret */
r_case
l_int|0xcf
suffix:colon
id|SP
c_func
(paren
id|regs
)paren
op_add_assign
l_int|6
suffix:semicolon
id|IP
c_func
(paren
id|regs
)paren
op_assign
id|popw
c_func
(paren
id|ssp
comma
id|sp
)paren
suffix:semicolon
id|regs-&gt;cs
op_assign
id|popw
c_func
(paren
id|ssp
comma
id|sp
)paren
suffix:semicolon
id|CHECK_IF_IN_TRAP
id|set_vflags_short
c_func
(paren
id|popw
c_func
(paren
id|ssp
comma
id|sp
)paren
comma
id|regs
)paren
suffix:semicolon
id|VM86_FAULT_RETURN
suffix:semicolon
multiline_comment|/* cli */
r_case
l_int|0xfa
suffix:colon
id|IP
c_func
(paren
id|regs
)paren
op_increment
suffix:semicolon
id|clear_IF
c_func
(paren
id|regs
)paren
suffix:semicolon
id|VM86_FAULT_RETURN
suffix:semicolon
multiline_comment|/* sti */
multiline_comment|/*&n;&t; * Damn. This is incorrect: the &squot;sti&squot; instruction should actually&n;&t; * enable interrupts after the /next/ instruction. Not good.&n;&t; *&n;&t; * Probably needs some horsing around with the TF flag. Aiee..&n;&t; */
r_case
l_int|0xfb
suffix:colon
id|IP
c_func
(paren
id|regs
)paren
op_increment
suffix:semicolon
id|set_IF
c_func
(paren
id|regs
)paren
suffix:semicolon
id|VM86_FAULT_RETURN
suffix:semicolon
r_default
suffix:colon
id|return_to_32bit
c_func
(paren
id|regs
comma
id|VM86_UNKNOWN
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* ---------------- vm86 special IRQ passing stuff ----------------- */
DECL|macro|VM86_IRQNAME
mdefine_line|#define VM86_IRQNAME&t;&t;&quot;vm86irq&quot;
DECL|struct|vm86_irqs
r_static
r_struct
id|vm86_irqs
(brace
DECL|member|tsk
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
DECL|member|sig
r_int
id|sig
suffix:semicolon
DECL|variable|vm86_irqs
)brace
id|vm86_irqs
(braket
l_int|16
)braket
op_assign
(brace
(brace
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|variable|irqbits
r_static
r_int
id|irqbits
op_assign
l_int|0
suffix:semicolon
DECL|macro|ALLOWED_SIGS
mdefine_line|#define ALLOWED_SIGS ( 1 /* 0 = don&squot;t send a signal */ &bslash;&n;&t;| (1 &lt;&lt; SIGUSR1) | (1 &lt;&lt; SIGUSR2) | (1 &lt;&lt; SIGIO)  | (1 &lt;&lt; SIGURG) &bslash;&n;&t;| (1 &lt;&lt; SIGUNUSED) )
DECL|function|irq_handler
r_static
r_void
id|irq_handler
c_func
(paren
r_int
id|intno
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irq_bit
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|irq_bit
op_assign
l_int|1
op_lshift
id|intno
suffix:semicolon
r_if
c_cond
(paren
(paren
id|irqbits
op_amp
id|irq_bit
)paren
op_logical_or
op_logical_neg
id|vm86_irqs
(braket
id|intno
)braket
dot
id|tsk
)paren
r_goto
id|out
suffix:semicolon
id|irqbits
op_or_assign
id|irq_bit
suffix:semicolon
r_if
c_cond
(paren
id|vm86_irqs
(braket
id|intno
)braket
dot
id|sig
)paren
id|send_sig
c_func
(paren
id|vm86_irqs
(braket
id|intno
)braket
dot
id|sig
comma
id|vm86_irqs
(braket
id|intno
)braket
dot
id|tsk
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* else user will poll for IRQs */
id|out
suffix:colon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|free_vm86_irq
r_static
r_inline
r_void
id|free_vm86_irq
c_func
(paren
r_int
id|irqnumber
)paren
(brace
id|free_irq
c_func
(paren
id|irqnumber
comma
l_int|0
)paren
suffix:semicolon
id|vm86_irqs
(braket
id|irqnumber
)braket
dot
id|tsk
op_assign
l_int|0
suffix:semicolon
id|irqbits
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irqnumber
)paren
suffix:semicolon
)brace
DECL|function|task_valid
r_static
r_inline
r_int
id|task_valid
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
(paren
id|p
op_eq
id|tsk
)paren
op_logical_and
(paren
id|p-&gt;sig
)paren
)paren
(brace
id|ret
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|handle_irq_zombies
r_static
r_inline
r_void
id|handle_irq_zombies
c_func
(paren
r_void
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
l_int|3
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|vm86_irqs
(braket
id|i
)braket
dot
id|tsk
)paren
(brace
r_if
c_cond
(paren
id|task_valid
c_func
(paren
id|vm86_irqs
(braket
id|i
)braket
dot
id|tsk
)paren
)paren
r_continue
suffix:semicolon
id|free_vm86_irq
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|get_and_reset_irq
r_static
r_inline
r_int
id|get_and_reset_irq
c_func
(paren
r_int
id|irqnumber
)paren
(brace
r_int
id|bit
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|irqnumber
OL
l_int|3
)paren
op_logical_or
(paren
id|irqnumber
OG
l_int|15
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vm86_irqs
(braket
id|irqnumber
)braket
dot
id|tsk
op_ne
id|current
)paren
r_return
l_int|0
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|bit
op_assign
id|irqbits
op_amp
(paren
l_int|1
op_lshift
id|irqnumber
)paren
suffix:semicolon
id|irqbits
op_and_assign
op_complement
id|bit
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|bit
suffix:semicolon
)brace
DECL|function|do_vm86_irq_handling
r_static
r_int
id|do_vm86_irq_handling
c_func
(paren
r_int
id|subfunction
comma
r_int
id|irqnumber
)paren
(brace
r_int
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|subfunction
)paren
(brace
r_case
id|VM86_GET_AND_RESET_IRQ
suffix:colon
(brace
r_return
id|get_and_reset_irq
c_func
(paren
id|irqnumber
)paren
suffix:semicolon
)brace
r_case
id|VM86_GET_IRQ_BITS
suffix:colon
(brace
r_return
id|irqbits
suffix:semicolon
)brace
r_case
id|VM86_REQUEST_IRQ
suffix:colon
(brace
r_int
id|sig
op_assign
id|irqnumber
op_rshift
l_int|8
suffix:semicolon
r_int
id|irq
op_assign
id|irqnumber
op_amp
l_int|255
suffix:semicolon
id|handle_irq_zombies
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
l_int|1
op_lshift
id|sig
)paren
op_amp
id|ALLOWED_SIGS
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|irq
OL
l_int|3
)paren
op_logical_or
(paren
id|irq
OG
l_int|15
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|vm86_irqs
(braket
id|irq
)braket
dot
id|tsk
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|irq
comma
op_amp
id|irq_handler
comma
l_int|0
comma
id|VM86_IRQNAME
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|vm86_irqs
(braket
id|irq
)braket
dot
id|sig
op_assign
id|sig
suffix:semicolon
id|vm86_irqs
(braket
id|irq
)braket
dot
id|tsk
op_assign
id|current
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
r_case
id|VM86_FREE_IRQ
suffix:colon
(brace
id|handle_irq_zombies
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|irqnumber
OL
l_int|3
)paren
op_logical_or
(paren
id|irqnumber
OG
l_int|15
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vm86_irqs
(braket
id|irqnumber
)braket
dot
id|tsk
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vm86_irqs
(braket
id|irqnumber
)braket
dot
id|tsk
op_ne
id|current
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|free_vm86_irq
c_func
(paren
id|irqnumber
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
