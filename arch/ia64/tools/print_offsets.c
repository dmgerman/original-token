multiline_comment|/*&n; * Utility to generate asm-ia64/offsets.h.&n; *&n; * Copyright (C) 1999-2000 Hewlett-Packard Co&n; * Copyright (C) 1999-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * Note that this file has dual use: when building the kernel&n; * natively, the file is translated into a binary and executed.  When&n; * building the kernel in a cross-development environment, this file&n; * gets translated into an assembly file which, in turn, is processed&n; * by awk to generate offsets.h.  So if you make any changes to this&n; * file, be sure to verify that the awk procedure still works (see&n; * prin_offsets.awk).&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm-ia64/processor.h&gt;
macro_line|#include &lt;asm-ia64/ptrace.h&gt;
macro_line|#include &lt;asm-ia64/siginfo.h&gt;
macro_line|#include &lt;asm-ia64/sigcontext.h&gt;
macro_line|#ifdef offsetof
DECL|macro|offsetof
macro_line|# undef offsetof
macro_line|#endif
multiline_comment|/*&n; * We _can&squot;t_ include the host&squot;s standard header file, as those are in&n; *  potential conflict with the what the Linux kernel declares for the&n; *  target system.&n; */
r_extern
r_int
id|printf
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|macro|offsetof
mdefine_line|#define offsetof(type,field)&t;((char *) &amp;((type *) 0)-&gt;field - (char *) 0)
r_struct
(brace
DECL|member|name
r_const
r_char
id|name
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
)brace
DECL|variable|tab
id|tab
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;IA64_TASK_SIZE&quot;
comma
r_sizeof
(paren
r_struct
id|task_struct
)paren
)brace
comma
(brace
l_string|&quot;IA64_PT_REGS_SIZE&quot;
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)brace
comma
(brace
l_string|&quot;IA64_SWITCH_STACK_SIZE&quot;
comma
r_sizeof
(paren
r_struct
id|switch_stack
)paren
)brace
comma
(brace
l_string|&quot;IA64_SIGINFO_SIZE&quot;
comma
r_sizeof
(paren
r_struct
id|siginfo
)paren
)brace
comma
(brace
l_string|&quot;&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* spacer */
(brace
l_string|&quot;IA64_TASK_FLAGS_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|flags
)paren
)brace
comma
(brace
l_string|&quot;IA64_TASK_SIGPENDING_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|sigpending
)paren
)brace
comma
(brace
l_string|&quot;IA64_TASK_NEED_RESCHED_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|need_resched
)paren
)brace
comma
(brace
l_string|&quot;IA64_TASK_THREAD_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread
)paren
)brace
comma
(brace
l_string|&quot;IA64_TASK_THREAD_KSP_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.ksp
)paren
)brace
comma
(brace
l_string|&quot;IA64_TASK_PID_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|pid
)paren
)brace
comma
(brace
l_string|&quot;IA64_TASK_MM_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|mm
)paren
)brace
comma
(brace
l_string|&quot;IA64_PT_REGS_CR_IPSR_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|cr_ipsr
)paren
)brace
comma
(brace
l_string|&quot;IA64_PT_REGS_R12_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|r12
)paren
)brace
comma
(brace
l_string|&quot;IA64_PT_REGS_R8_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|r8
)paren
)brace
comma
(brace
l_string|&quot;IA64_PT_REGS_R16_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|r16
)paren
)brace
comma
(brace
l_string|&quot;IA64_SWITCH_STACK_B0_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|switch_stack
comma
id|b0
)paren
)brace
comma
(brace
l_string|&quot;IA64_SWITCH_STACK_CALLER_UNAT_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|switch_stack
comma
id|caller_unat
)paren
)brace
comma
(brace
l_string|&quot;IA64_SIGCONTEXT_AR_BSP_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|sigcontext
comma
id|sc_ar_bsp
)paren
)brace
comma
(brace
l_string|&quot;IA64_SIGCONTEXT_AR_RNAT_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|sigcontext
comma
id|sc_ar_rnat
)paren
)brace
comma
(brace
l_string|&quot;IA64_SIGCONTEXT_FLAGS_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|sigcontext
comma
id|sc_flags
)paren
)brace
comma
(brace
l_string|&quot;IA64_SIGCONTEXT_CFM_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|sigcontext
comma
id|sc_cfm
)paren
)brace
comma
(brace
l_string|&quot;IA64_SIGCONTEXT_FR6_OFFSET&quot;
comma
m_offsetof
(paren
r_struct
id|sigcontext
comma
id|sc_fr
(braket
l_int|6
)braket
)paren
)brace
comma
)brace
suffix:semicolon
DECL|variable|tabs
r_static
r_const
r_char
op_star
id|tabs
op_assign
l_string|&quot;&bslash;t&bslash;t&bslash;t&bslash;t&bslash;t&bslash;t&bslash;t&bslash;t&bslash;t&bslash;t&quot;
suffix:semicolon
r_int
DECL|function|main
id|main
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_const
r_char
op_star
id|space
suffix:semicolon
r_int
id|i
comma
id|num_tabs
suffix:semicolon
r_int
id|len
suffix:semicolon
id|printf
(paren
l_string|&quot;#ifndef _ASM_IA64_OFFSETS_H&bslash;n&quot;
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;#define _ASM_IA64_OFFSETS_H&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;/*&bslash;n * DO NOT MODIFY&bslash;n *&bslash;n * This file was generated by &quot;
l_string|&quot;arch/ia64/tools/print_offsets.&bslash;n *&bslash;n */&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* This is stretching things a bit, but entry.S needs the bit number&n;     for PF_PTRACED and it can&squot;t include &lt;linux/sched.h&gt; so this seems&n;     like a reasonably solution.  At least the code won&squot;t break shoudl&n;     PF_PTRACED ever change.  */
id|printf
(paren
l_string|&quot;#define PF_PTRACED_BIT&bslash;t&bslash;t&bslash;t%u&bslash;n&bslash;n&quot;
comma
id|ffs
(paren
id|PF_PTRACED
)paren
op_minus
l_int|1
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
r_sizeof
(paren
id|tab
)paren
op_div
r_sizeof
(paren
id|tab
(braket
l_int|0
)braket
)paren
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|tab
(braket
id|i
)braket
dot
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
id|printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|len
op_assign
id|strlen
(paren
id|tab
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|num_tabs
op_assign
(paren
l_int|40
op_minus
id|len
)paren
op_div
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|num_tabs
op_le
l_int|0
)paren
id|space
op_assign
l_string|&quot; &quot;
suffix:semicolon
r_else
id|space
op_assign
id|strchr
c_func
(paren
id|tabs
comma
l_char|&squot;&bslash;0&squot;
)paren
op_minus
(paren
l_int|40
op_minus
id|len
)paren
op_div
l_int|8
suffix:semicolon
id|printf
(paren
l_string|&quot;#define %s%s%lu&bslash;t/* 0x%lx */&bslash;n&quot;
comma
id|tab
(braket
id|i
)braket
dot
id|name
comma
id|space
comma
id|tab
(braket
id|i
)braket
dot
id|value
comma
id|tab
(braket
id|i
)braket
dot
id|value
)paren
suffix:semicolon
)brace
)brace
id|printf
(paren
l_string|&quot;&bslash;n#endif /* _ASM_IA64_OFFSETS_H */&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
