multiline_comment|/* $Id: traps.c,v 1.10 1997/05/18 08:42:16 davem Exp $&n; * arch/sparc/kernel/traps.c&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
multiline_comment|/*&n; * I hate traps on the sparc, grrr...&n; */
macro_line|#include &lt;linux/sched.h&gt;  /* for jiffies */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* #define TRAP_DEBUG */
DECL|struct|trap_trace_entry
r_struct
id|trap_trace_entry
(brace
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|trap_curbuf
r_int
id|trap_curbuf
op_assign
l_int|0
suffix:semicolon
DECL|variable|trapbuf
r_struct
id|trap_trace_entry
id|trapbuf
(braket
l_int|1024
)braket
suffix:semicolon
DECL|function|syscall_trace_entry
r_void
id|syscall_trace_entry
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s[%d]: &quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;scall&lt;%ld&gt; (could be %ld)&bslash;n&quot;
comma
(paren
r_int
)paren
id|regs-&gt;u_regs
(braket
id|UREG_G1
)braket
comma
(paren
r_int
)paren
id|regs-&gt;u_regs
(braket
id|UREG_I0
)braket
)paren
suffix:semicolon
)brace
DECL|function|syscall_trace_exit
r_void
id|syscall_trace_exit
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Syscall return check, reg dump.&bslash;n&quot;
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
DECL|function|sparc64_dtlb_fault_handler
r_void
id|sparc64_dtlb_fault_handler
(paren
r_void
)paren
(brace
id|printk
(paren
l_string|&quot;sparc64_dtlb_fault_handler&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Die for now... */
)brace
DECL|function|sparc64_dtlb_refbit_handler
r_void
id|sparc64_dtlb_refbit_handler
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
(paren
l_string|&quot;sparc64_dtlb_refbit_handler[%016lx]&bslash;n&quot;
comma
id|regs-&gt;tpc
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Die for now... */
)brace
DECL|function|sparc64_itlb_refbit_handler
r_void
id|sparc64_itlb_refbit_handler
(paren
r_void
)paren
(brace
id|printk
(paren
l_string|&quot;sparc64_itlb_refbit_handler&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Die for now... */
)brace
DECL|function|bad_trap
r_void
id|bad_trap
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|lvl
)paren
(brace
id|printk
(paren
l_string|&quot;Bad trap %d (tstate %016lx tpc %016lx tnpc %016lx)&bslash;n&quot;
comma
id|lvl
comma
id|regs-&gt;tstate
comma
id|regs-&gt;tpc
comma
id|regs-&gt;tnpc
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Die for now... */
)brace
DECL|function|bad_trap_tl1
r_void
id|bad_trap_tl1
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|lvl
)paren
(brace
id|printk
(paren
l_string|&quot;Bad trap %d at tl1+ (tstate %016lx tpc %016lx tnpc %016lx)&bslash;n&quot;
comma
id|lvl
comma
id|regs-&gt;tstate
comma
id|regs-&gt;tpc
comma
id|regs-&gt;tnpc
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Die for now... */
)brace
DECL|function|data_access_exception
r_void
id|data_access_exception
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
(paren
l_string|&quot;Unhandled data access exception sfsr %016lx sfar %016lx&bslash;n&quot;
comma
id|spitfire_get_dsfsr
c_func
(paren
)paren
comma
id|spitfire_get_sfar
c_func
(paren
)paren
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Data access exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|instruction_access_exception
r_void
id|instruction_access_exception
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
(paren
l_string|&quot;Unhandled instruction access exception sfsr %016lx&bslash;n&quot;
comma
id|spitfire_get_isfsr
c_func
(paren
)paren
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Instruction access exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|instruction_dump
r_void
id|instruction_dump
(paren
r_int
r_int
op_star
id|pc
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|pc
)paren
op_amp
l_int|3
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
op_minus
l_int|3
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%c%08x%c&quot;
comma
id|i
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;&lt;&squot;
comma
id|pc
(braket
id|i
)braket
comma
id|i
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|die_if_kernel
r_void
id|die_if_kernel
c_func
(paren
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/* Amuse the user. */
id|printk
c_func
(paren
l_string|&quot;              &bslash;&bslash;|/ ____ &bslash;&bslash;|/&bslash;n&quot;
l_string|&quot;              &bslash;&quot;@&squot;/ .` &bslash;&bslash;`@&bslash;&quot;&bslash;n&quot;
l_string|&quot;              /_| &bslash;&bslash;__/ |_&bslash;&bslash;&bslash;n&quot;
l_string|&quot;                 &bslash;&bslash;__U_/&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s(%d): %s&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|str
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Instruction DUMP:&quot;
)paren
suffix:semicolon
id|instruction_dump
(paren
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;tpc
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
)brace
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
DECL|function|do_illegal_instruction
r_void
id|do_illegal_instruction
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|pc
op_assign
id|regs-&gt;tpc
suffix:semicolon
r_int
r_int
id|tstate
op_assign
id|regs-&gt;tstate
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;Kernel illegal instruction&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#if 1
(brace
r_int
r_int
id|insn
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Ill instr. at pc=%016lx &quot;
comma
id|pc
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|insn
comma
(paren
(paren
r_int
r_int
op_star
)paren
id|pc
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;insn=[%08x]&bslash;n&quot;
comma
id|insn
)paren
suffix:semicolon
)brace
macro_line|#endif
id|current-&gt;tss.sig_address
op_assign
id|pc
suffix:semicolon
id|current-&gt;tss.sig_desc
op_assign
id|SUBSIG_ILLINST
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGILL
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|do_mna
r_void
id|do_mna
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;AIEEE: do_mna at %016lx&bslash;n&quot;
comma
id|regs-&gt;tpc
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|do_priv_instruction
r_void
id|do_priv_instruction
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
comma
r_int
r_int
id|tstate
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
id|tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;Penguin instruction from Penguin mode??!?!&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
id|current-&gt;tss.sig_address
op_assign
id|pc
suffix:semicolon
id|current-&gt;tss.sig_desc
op_assign
id|SUBSIG_PRIVINST
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGILL
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX User may want to be allowed to do this. XXX */
DECL|function|do_memaccess_unaligned
r_void
id|do_memaccess_unaligned
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
comma
r_int
r_int
id|tstate
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
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;KERNEL MNA at pc %016lx npc %016lx called by %016lx&bslash;n&quot;
comma
id|pc
comma
id|npc
comma
id|regs-&gt;u_regs
(braket
id|UREG_RETPC
)braket
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;BOGUS&quot;
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/* die_if_kernel(&quot;Kernel MNA access&quot;, regs); */
)brace
id|current-&gt;tss.sig_address
op_assign
id|pc
suffix:semicolon
id|current-&gt;tss.sig_desc
op_assign
id|SUBSIG_PRIVINST
suffix:semicolon
macro_line|#if 0
id|show_regs
(paren
id|regs
)paren
suffix:semicolon
id|instruction_dump
(paren
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;tpc
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;do_MNA!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|send_sig
c_func
(paren
id|SIGBUS
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|handle_hw_divzero
r_void
id|handle_hw_divzero
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
comma
r_int
r_int
id|psr
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGILL
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|trap_init
r_void
id|trap_init
c_func
(paren
r_void
)paren
(brace
)brace
eof
