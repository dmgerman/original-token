multiline_comment|/*&n; *  linux/arch/i386/traps.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; * &squot;Traps.c&squot; handles hardware traps and faults after we have saved some&n; * state in &squot;asm.s&squot;. Currently mostly a debugging-aid, will be extended&n; * to mainly kill the offending process (probably by giving it a signal,&n; * but possibly by killing it outright if necessary).&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
id|asmlinkage
r_int
id|system_call
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|lcall7
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|default_ldt
r_struct
id|desc_struct
id|default_ldt
suffix:semicolon
DECL|function|console_verbose
r_static
r_inline
r_void
id|console_verbose
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|console_loglevel
suffix:semicolon
id|console_loglevel
op_assign
l_int|15
suffix:semicolon
)brace
DECL|macro|DO_ERROR
mdefine_line|#define DO_ERROR(trapnr, signr, str, name, tsk) &bslash;&n;asmlinkage void do_##name(struct pt_regs * regs, long error_code) &bslash;&n;{ &bslash;&n;&t;tsk-&gt;tss.error_code = error_code; &bslash;&n;&t;tsk-&gt;tss.trap_no = trapnr; &bslash;&n;&t;if (signr == SIGTRAP &amp;&amp; current-&gt;flags &amp; PF_PTRACED) &bslash;&n;&t;&t;current-&gt;blocked &amp;= ~(1 &lt;&lt; (SIGTRAP-1)); &bslash;&n;&t;send_sig(signr, tsk, 1); &bslash;&n;&t;die_if_kernel(str,regs,error_code); &bslash;&n;}
DECL|macro|get_seg_byte
mdefine_line|#define get_seg_byte(seg,addr) ({ &bslash;&n;register unsigned char __res; &bslash;&n;__asm__(&quot;push %%fs;mov %%ax,%%fs;movb %%fs:%2,%%al;pop %%fs&quot; &bslash;&n;&t;:&quot;=a&quot; (__res):&quot;0&quot; (seg),&quot;m&quot; (*(addr))); &bslash;&n;__res;})
DECL|macro|get_seg_long
mdefine_line|#define get_seg_long(seg,addr) ({ &bslash;&n;register unsigned long __res; &bslash;&n;__asm__(&quot;push %%fs;mov %%ax,%%fs;movl %%fs:%2,%%eax;pop %%fs&quot; &bslash;&n;&t;:&quot;=a&quot; (__res):&quot;0&quot; (seg),&quot;m&quot; (*(addr))); &bslash;&n;__res;})
DECL|macro|_fs
mdefine_line|#define _fs() ({ &bslash;&n;register unsigned short __res; &bslash;&n;__asm__(&quot;mov %%fs,%%ax&quot;:&quot;=a&quot; (__res):); &bslash;&n;__res;})
r_void
id|page_exception
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|divide_error
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|debug
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|nmi
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|int3
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|overflow
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|bounds
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|invalid_op
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|device_not_available
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|double_fault
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|coprocessor_segment_overrun
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|invalid_TSS
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|segment_not_present
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|stack_segment
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|general_protection
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|page_fault
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|coprocessor_error
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|reserved
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|alignment_check
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|kstack_depth_to_print
r_int
id|kstack_depth_to_print
op_assign
l_int|24
suffix:semicolon
multiline_comment|/*&n; * These constants are for searching for possible module text&n; * segments.  VMALLOC_OFFSET comes from mm/vmalloc.c; MODULE_RANGE is&n; * a guess of how much space is likely to be vmalloced.&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET (8*1024*1024)
DECL|macro|MODULE_RANGE
mdefine_line|#define MODULE_RANGE (8*1024*1024)
DECL|function|die_if_kernel
multiline_comment|/*static*/
r_void
id|die_if_kernel
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|esp
suffix:semicolon
r_int
r_int
id|ss
suffix:semicolon
r_int
r_int
op_star
id|stack
comma
id|addr
comma
id|module_start
comma
id|module_end
suffix:semicolon
r_extern
r_char
id|start_kernel
comma
id|_etext
suffix:semicolon
id|esp
op_assign
(paren
r_int
r_int
)paren
op_amp
id|regs-&gt;esp
suffix:semicolon
id|ss
op_assign
id|KERNEL_DS
suffix:semicolon
r_if
c_cond
(paren
(paren
id|regs-&gt;eflags
op_amp
id|VM_MASK
)paren
op_logical_or
(paren
l_int|3
op_amp
id|regs-&gt;cs
)paren
op_eq
l_int|3
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;cs
op_amp
l_int|3
)paren
(brace
id|esp
op_assign
id|regs-&gt;esp
suffix:semicolon
id|ss
op_assign
id|regs-&gt;ss
suffix:semicolon
)brace
id|console_verbose
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %04lx&bslash;n&quot;
comma
id|str
comma
id|err
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU:    %d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EIP:    %04x:%08lx&bslash;nEFLAGS: %08lx&bslash;n&quot;
comma
l_int|0xffff
op_amp
id|regs-&gt;cs
comma
id|regs-&gt;eip
comma
id|regs-&gt;eflags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;eax: %08lx   ebx: %08lx   ecx: %08lx   edx: %08lx&bslash;n&quot;
comma
id|regs-&gt;eax
comma
id|regs-&gt;ebx
comma
id|regs-&gt;ecx
comma
id|regs-&gt;edx
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;esi: %08lx   edi: %08lx   ebp: %08lx   esp: %08lx&bslash;n&quot;
comma
id|regs-&gt;esi
comma
id|regs-&gt;edi
comma
id|regs-&gt;ebp
comma
id|esp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ds: %04x   es: %04x   fs: %04x   gs: %04x   ss: %04x&bslash;n&quot;
comma
id|regs-&gt;ds
comma
id|regs-&gt;es
comma
id|regs-&gt;fs
comma
id|regs-&gt;gs
comma
id|ss
)paren
suffix:semicolon
id|store_TR
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|STACK_MAGIC
op_ne
op_star
(paren
r_int
r_int
op_star
)paren
id|current-&gt;kernel_stack_page
)paren
id|printk
c_func
(paren
l_string|&quot;Corrupted stack page&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Process %s (pid: %d, process nr: %d, stackpage=%08lx)&bslash;nStack: &quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
l_int|0xffff
op_amp
id|i
comma
id|current-&gt;kernel_stack_page
)paren
suffix:semicolon
id|stack
op_assign
(paren
r_int
r_int
op_star
)paren
id|esp
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
id|kstack_depth_to_print
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
r_int
)paren
id|stack
op_amp
l_int|4095
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_logical_and
(paren
(paren
id|i
op_mod
l_int|8
)paren
op_eq
l_int|0
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n       &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08lx &quot;
comma
id|get_seg_long
c_func
(paren
id|ss
comma
id|stack
op_increment
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nCall Trace: &quot;
)paren
suffix:semicolon
id|stack
op_assign
(paren
r_int
r_int
op_star
)paren
id|esp
suffix:semicolon
id|i
op_assign
l_int|1
suffix:semicolon
id|module_start
op_assign
(paren
(paren
id|high_memory
op_plus
id|VMALLOC_OFFSET
)paren
op_amp
op_complement
(paren
id|VMALLOC_OFFSET
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|module_end
op_assign
id|module_start
op_plus
id|MODULE_RANGE
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
r_int
)paren
id|stack
op_amp
l_int|4095
)paren
op_ne
l_int|0
)paren
(brace
id|addr
op_assign
id|get_seg_long
c_func
(paren
id|ss
comma
id|stack
op_increment
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the address is either in the text segment of the&n;&t;&t; * kernel, or in the region which contains vmalloc&squot;ed&n;&t;&t; * memory, it *may* be the address of a calling&n;&t;&t; * routine; if so, print it so that someone tracing&n;&t;&t; * down the cause of the crash will be able to figure&n;&t;&t; * out the call path that was taken.&n;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
id|addr
op_ge
(paren
r_int
r_int
)paren
op_amp
id|start_kernel
)paren
op_logical_and
(paren
id|addr
op_le
(paren
r_int
r_int
)paren
op_amp
id|_etext
)paren
)paren
op_logical_or
(paren
(paren
id|addr
op_ge
id|module_start
)paren
op_logical_and
(paren
id|addr
op_le
id|module_end
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
op_logical_and
(paren
(paren
id|i
op_mod
l_int|8
)paren
op_eq
l_int|0
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n       &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08lx &quot;
comma
id|addr
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nCode: &quot;
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
l_int|20
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
l_int|0xff
op_amp
id|get_seg_byte
c_func
(paren
id|regs-&gt;cs
comma
(paren
id|i
op_plus
(paren
r_char
op_star
)paren
id|regs-&gt;eip
)paren
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
id|DO_ERROR
c_func
(paren
l_int|0
comma
id|SIGFPE
comma
l_string|&quot;divide error&quot;
comma
id|divide_error
comma
id|current
)paren
id|DO_ERROR
c_func
(paren
l_int|3
comma
id|SIGTRAP
comma
l_string|&quot;int3&quot;
comma
id|int3
comma
id|current
)paren
id|DO_ERROR
c_func
(paren
l_int|4
comma
id|SIGSEGV
comma
l_string|&quot;overflow&quot;
comma
id|overflow
comma
id|current
)paren
id|DO_ERROR
c_func
(paren
l_int|5
comma
id|SIGSEGV
comma
l_string|&quot;bounds&quot;
comma
id|bounds
comma
id|current
)paren
id|DO_ERROR
c_func
(paren
l_int|6
comma
id|SIGILL
comma
l_string|&quot;invalid operand&quot;
comma
id|invalid_op
comma
id|current
)paren
id|DO_ERROR
c_func
(paren
l_int|7
comma
id|SIGSEGV
comma
l_string|&quot;device not available&quot;
comma
id|device_not_available
comma
id|current
)paren
id|DO_ERROR
c_func
(paren
l_int|8
comma
id|SIGSEGV
comma
l_string|&quot;double fault&quot;
comma
id|double_fault
comma
id|current
)paren
id|DO_ERROR
c_func
(paren
l_int|9
comma
id|SIGFPE
comma
l_string|&quot;coprocessor segment overrun&quot;
comma
id|coprocessor_segment_overrun
comma
id|last_task_used_math
)paren
id|DO_ERROR
c_func
(paren
l_int|10
comma
id|SIGSEGV
comma
l_string|&quot;invalid TSS&quot;
comma
id|invalid_TSS
comma
id|current
)paren
id|DO_ERROR
c_func
(paren
l_int|11
comma
id|SIGBUS
comma
l_string|&quot;segment not present&quot;
comma
id|segment_not_present
comma
id|current
)paren
id|DO_ERROR
c_func
(paren
l_int|12
comma
id|SIGBUS
comma
l_string|&quot;stack segment&quot;
comma
id|stack_segment
comma
id|current
)paren
id|DO_ERROR
c_func
(paren
l_int|15
comma
id|SIGSEGV
comma
l_string|&quot;reserved&quot;
comma
id|reserved
comma
id|current
)paren
id|DO_ERROR
c_func
(paren
l_int|17
comma
id|SIGSEGV
comma
l_string|&quot;alignment check&quot;
comma
id|alignment_check
comma
id|current
)paren
DECL|function|do_general_protection
id|asmlinkage
r_void
id|do_general_protection
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
(brace
r_if
c_cond
(paren
id|regs-&gt;eflags
op_amp
id|VM_MASK
)paren
(brace
id|handle_vm86_fault
c_func
(paren
(paren
r_struct
id|vm86_regs
op_star
)paren
id|regs
comma
id|error_code
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|die_if_kernel
c_func
(paren
l_string|&quot;general protection&quot;
comma
id|regs
comma
id|error_code
)paren
suffix:semicolon
id|current-&gt;tss.error_code
op_assign
id|error_code
suffix:semicolon
id|current-&gt;tss.trap_no
op_assign
l_int|13
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGSEGV
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|do_nmi
id|asmlinkage
r_void
id|do_nmi
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
(brace
macro_line|#ifdef CONFIG_SMP_NMI_INVAL
id|smp_invalidate_rcv
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
macro_line|#ifndef CONFIG_IGNORE_NMI
id|printk
c_func
(paren
l_string|&quot;Uhhuh. NMI received. Dazed and confused, but trying to continue&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;You probably have a hardware problem with your RAM chips or a&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;power saving mode enabled.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;
macro_line|#endif
)brace
DECL|function|do_debug
id|asmlinkage
r_void
id|do_debug
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
(brace
r_if
c_cond
(paren
id|regs-&gt;eflags
op_amp
id|VM_MASK
)paren
(brace
id|handle_vm86_debug
c_func
(paren
(paren
r_struct
id|vm86_regs
op_star
)paren
id|regs
comma
id|error_code
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_PTRACED
)paren
id|current-&gt;blocked
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|SIGTRAP
op_minus
l_int|1
)paren
)paren
suffix:semicolon
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
id|current-&gt;tss.trap_no
op_assign
l_int|1
suffix:semicolon
id|current-&gt;tss.error_code
op_assign
id|error_code
suffix:semicolon
r_if
c_cond
(paren
(paren
id|regs-&gt;cs
op_amp
l_int|3
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* If this is a kernel mode trap, then reset db7 and allow us to continue */
id|__asm__
c_func
(paren
l_string|&quot;movl %0,%%db7&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|die_if_kernel
c_func
(paren
l_string|&quot;debug&quot;
comma
id|regs
comma
id|error_code
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Allow the process which triggered the interrupt to recover the error&n; * condition.&n; *  - the status word is saved in the cs selector.&n; *  - the tag word is saved in the operand selector.&n; *  - the status word is then cleared and the tags all set to Empty.&n; *&n; * This will give sufficient information for complete recovery provided that&n; * the affected process knows or can deduce the code and data segments&n; * which were in force when the exception condition arose.&n; *&n; * Note that we play around with the &squot;TS&squot; bit to hopefully get&n; * the correct behaviour even in the presence of the asynchronous&n; * IRQ13 behaviour&n; */
DECL|function|math_error
r_void
id|math_error
c_func
(paren
r_void
)paren
(brace
r_struct
id|i387_hard_struct
op_star
id|env
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|env
op_assign
op_amp
id|current-&gt;tss.i387.hard
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGFPE
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Save the info for the exception handler&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;fnsave %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|env
)paren
)paren
suffix:semicolon
id|current-&gt;flags
op_and_assign
op_complement
id|PF_USEDFPU
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Cause a trap if they use the FPU again.&n;&t; */
id|stts
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
id|clts
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|last_task_used_math
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;fnclex&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|env
op_assign
op_amp
id|last_task_used_math-&gt;tss.i387.hard
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGFPE
comma
id|last_task_used_math
comma
l_int|1
)paren
suffix:semicolon
id|last_task_used_math-&gt;tss.trap_no
op_assign
l_int|16
suffix:semicolon
id|last_task_used_math-&gt;tss.error_code
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;fnsave %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|env
)paren
)paren
suffix:semicolon
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
id|stts
c_func
(paren
)paren
suffix:semicolon
id|env-&gt;fcs
op_assign
(paren
id|env-&gt;swd
op_amp
l_int|0x0000ffff
)paren
op_or
(paren
id|env-&gt;fcs
op_amp
l_int|0xffff0000
)paren
suffix:semicolon
id|env-&gt;fos
op_assign
id|env-&gt;twd
suffix:semicolon
id|env-&gt;swd
op_and_assign
l_int|0xffff3800
suffix:semicolon
id|env-&gt;twd
op_assign
l_int|0xffffffff
suffix:semicolon
macro_line|#endif&t;
)brace
DECL|function|do_coprocessor_error
id|asmlinkage
r_void
id|do_coprocessor_error
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
(brace
id|ignore_irq13
op_assign
l_int|1
suffix:semicolon
id|math_error
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  &squot;math_state_restore()&squot; saves the current math information in the&n; * old math state array, and gets the new ones from the current task&n; *&n; * Careful.. There are problems with IBM-designed IRQ13 behaviour.&n; * Don&squot;t touch unless you *really* know how it works.&n; */
DECL|function|math_state_restore
id|asmlinkage
r_void
id|math_state_restore
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n; *&t;SMP is actually simpler than uniprocessor for once. Because&n; *&t;we can&squot;t pull the delayed FPU switching trick Linus does&n; *&t;we simply have to do the restore each context switch and&n; *&t;set the flag. switch_to() will always save the state in&n; *&t;case we swap processors. We also don&squot;t use the coprocessor&n; *&t;timer - IRQ 13 mode isnt used with SMP machines (thank god).&n; *&n; *&t;If this actually works it will be a miracle however&n; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;clts&quot;
)paren
suffix:semicolon
multiline_comment|/* Allow maths ops (or we recurse) */
r_if
c_cond
(paren
id|current-&gt;used_math
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;frstor %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|current-&gt;tss.i387
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; *&t;Our first FPU usage, clean the chip.&n;&t;&t; */
id|__asm__
c_func
(paren
l_string|&quot;fninit&quot;
)paren
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|1
suffix:semicolon
)brace
id|current-&gt;flags
op_or_assign
id|PF_USEDFPU
suffix:semicolon
multiline_comment|/* So we fnsave on switch_to() */
macro_line|#else
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;clts&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
r_return
suffix:semicolon
id|timer_table
(braket
id|COPRO_TIMER
)braket
dot
id|expires
op_assign
id|jiffies
op_plus
l_int|50
suffix:semicolon
id|timer_active
op_or_assign
l_int|1
op_lshift
id|COPRO_TIMER
suffix:semicolon
r_if
c_cond
(paren
id|last_task_used_math
)paren
id|__asm__
c_func
(paren
l_string|&quot;fnsave %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|last_task_used_math-&gt;tss.i387
)paren
)paren
suffix:semicolon
r_else
id|__asm__
c_func
(paren
l_string|&quot;fnclex&quot;
)paren
suffix:semicolon
id|last_task_used_math
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;used_math
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;frstor %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|current-&gt;tss.i387
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|__asm__
c_func
(paren
l_string|&quot;fninit&quot;
)paren
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|1
suffix:semicolon
)brace
id|timer_active
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|COPRO_TIMER
)paren
suffix:semicolon
macro_line|#endif&t;
)brace
macro_line|#ifndef CONFIG_MATH_EMULATION
DECL|function|math_emulate
id|asmlinkage
r_void
id|math_emulate
c_func
(paren
r_int
id|arg
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;math-emulation not enabled and no coprocessor found.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;killing %s.&bslash;n&quot;
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGFPE
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_MATH_EMULATION */
DECL|function|trap_init
r_void
id|trap_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|desc_struct
op_star
id|p
suffix:semicolon
r_static
r_int
id|smptrap
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|smptrap
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;pushfl ; andl $0xffffbfff,(%esp) ; popfl&quot;
)paren
suffix:semicolon
id|load_ldt
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|smptrap
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
(paren
r_char
op_star
)paren
l_int|0x0FFFD9
comma
l_string|&quot;EISA&quot;
comma
l_int|4
)paren
op_eq
l_int|0
)paren
id|EISA_bus
op_assign
l_int|1
suffix:semicolon
id|set_call_gate
c_func
(paren
op_amp
id|default_ldt
comma
id|lcall7
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|0
comma
op_amp
id|divide_error
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|1
comma
op_amp
id|debug
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|2
comma
op_amp
id|nmi
)paren
suffix:semicolon
id|set_system_gate
c_func
(paren
l_int|3
comma
op_amp
id|int3
)paren
suffix:semicolon
multiline_comment|/* int3-5 can be called from all */
id|set_system_gate
c_func
(paren
l_int|4
comma
op_amp
id|overflow
)paren
suffix:semicolon
id|set_system_gate
c_func
(paren
l_int|5
comma
op_amp
id|bounds
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|6
comma
op_amp
id|invalid_op
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|7
comma
op_amp
id|device_not_available
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|8
comma
op_amp
id|double_fault
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|9
comma
op_amp
id|coprocessor_segment_overrun
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|10
comma
op_amp
id|invalid_TSS
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|11
comma
op_amp
id|segment_not_present
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|12
comma
op_amp
id|stack_segment
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|13
comma
op_amp
id|general_protection
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|14
comma
op_amp
id|page_fault
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|15
comma
op_amp
id|reserved
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|16
comma
op_amp
id|coprocessor_error
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|17
comma
op_amp
id|alignment_check
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|18
suffix:semicolon
id|i
OL
l_int|48
suffix:semicolon
id|i
op_increment
)paren
id|set_trap_gate
c_func
(paren
id|i
comma
op_amp
id|reserved
)paren
suffix:semicolon
id|set_system_gate
c_func
(paren
l_int|0x80
comma
op_amp
id|system_call
)paren
suffix:semicolon
multiline_comment|/* set up GDT task &amp; ldt entries */
id|p
op_assign
id|gdt
op_plus
id|FIRST_TSS_ENTRY
suffix:semicolon
id|set_tss_desc
c_func
(paren
id|p
comma
op_amp
id|init_task.tss
)paren
suffix:semicolon
id|p
op_increment
suffix:semicolon
id|set_ldt_desc
c_func
(paren
id|p
comma
op_amp
id|default_ldt
comma
l_int|1
)paren
suffix:semicolon
id|p
op_increment
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
id|p-&gt;a
op_assign
id|p-&gt;b
op_assign
l_int|0
suffix:semicolon
id|p
op_increment
suffix:semicolon
id|p-&gt;a
op_assign
id|p-&gt;b
op_assign
l_int|0
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/* Clear NT, so that we won&squot;t have troubles with that later on */
id|__asm__
c_func
(paren
l_string|&quot;pushfl ; andl $0xffffbfff,(%esp) ; popfl&quot;
)paren
suffix:semicolon
id|load_TR
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|load_ldt
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
