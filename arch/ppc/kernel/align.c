multiline_comment|/*&n; * align.c - handle alignment exceptions for the Power PC.&n; *&n; * Paul Mackerras&t;August 1996.&n; * Copyright (C) 1996 Paul Mackerras&t;(paulus@cs.anu.edu.au).&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|struct|aligninfo
r_struct
id|aligninfo
(brace
DECL|member|len
r_int
r_char
id|len
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INVALID
mdefine_line|#define INVALID&t;{ 0, 0 }
DECL|macro|LD
mdefine_line|#define LD&t;1&t;/* load */
DECL|macro|ST
mdefine_line|#define ST&t;2&t;/* store */
DECL|macro|SE
mdefine_line|#define&t;SE&t;4&t;/* sign-extend value */
DECL|macro|F
mdefine_line|#define F&t;8&t;/* to/from fp regs */
DECL|macro|U
mdefine_line|#define U&t;0x10&t;/* update index register */
DECL|macro|M
mdefine_line|#define M&t;0x20&t;/* multiple load/store */
DECL|macro|S
mdefine_line|#define S&t;0x40&t;/* single-precision fp, or byte-swap value */
DECL|macro|HARD
mdefine_line|#define HARD&t;0x80&t;/* string, stwcx. */
multiline_comment|/*&n; * The PowerPC stores certain bits of the instruction that caused the&n; * alignment exception in the DSISR register.  This array maps those&n; * bits to information about the operand length and what the&n; * instruction would do.&n; */
DECL|variable|aligninfo
r_static
r_struct
id|aligninfo
id|aligninfo
(braket
l_int|128
)braket
op_assign
(brace
(brace
l_int|4
comma
id|LD
)brace
comma
multiline_comment|/* 00 0 0000: lwz / lwarx */
id|INVALID
comma
multiline_comment|/* 00 0 0001 */
(brace
l_int|4
comma
id|ST
)brace
comma
multiline_comment|/* 00 0 0010: stw */
id|INVALID
comma
multiline_comment|/* 00 0 0011 */
(brace
l_int|2
comma
id|LD
)brace
comma
multiline_comment|/* 00 0 0100: lhz */
(brace
l_int|2
comma
id|LD
op_plus
id|SE
)brace
comma
multiline_comment|/* 00 0 0101: lha */
(brace
l_int|2
comma
id|ST
)brace
comma
multiline_comment|/* 00 0 0110: sth */
(brace
l_int|4
comma
id|LD
op_plus
id|M
)brace
comma
multiline_comment|/* 00 0 0111: lmw */
(brace
l_int|4
comma
id|LD
op_plus
id|F
op_plus
id|S
)brace
comma
multiline_comment|/* 00 0 1000: lfs */
(brace
l_int|8
comma
id|LD
op_plus
id|F
)brace
comma
multiline_comment|/* 00 0 1001: lfd */
(brace
l_int|4
comma
id|ST
op_plus
id|F
op_plus
id|S
)brace
comma
multiline_comment|/* 00 0 1010: stfs */
(brace
l_int|8
comma
id|ST
op_plus
id|F
)brace
comma
multiline_comment|/* 00 0 1011: stfd */
id|INVALID
comma
multiline_comment|/* 00 0 1100 */
id|INVALID
comma
multiline_comment|/* 00 0 1101 */
id|INVALID
comma
multiline_comment|/* 00 0 1110 */
id|INVALID
comma
multiline_comment|/* 00 0 1111 */
(brace
l_int|4
comma
id|LD
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 0000: lwzu */
id|INVALID
comma
multiline_comment|/* 00 1 0001 */
(brace
l_int|4
comma
id|ST
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 0010: stwu */
id|INVALID
comma
multiline_comment|/* 00 1 0011 */
(brace
l_int|2
comma
id|LD
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 0100: lhzu */
(brace
l_int|2
comma
id|LD
op_plus
id|SE
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 0101: lhau */
(brace
l_int|2
comma
id|ST
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 0110: sthu */
(brace
l_int|4
comma
id|ST
op_plus
id|M
)brace
comma
multiline_comment|/* 00 1 0111: stmw */
(brace
l_int|4
comma
id|LD
op_plus
id|F
op_plus
id|S
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 1000: lfsu */
(brace
l_int|8
comma
id|LD
op_plus
id|F
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 1001: lfdu */
(brace
l_int|4
comma
id|ST
op_plus
id|F
op_plus
id|S
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 1010: stfsu */
(brace
l_int|8
comma
id|ST
op_plus
id|F
op_plus
id|U
)brace
comma
multiline_comment|/* 00 1 1011: stfdu */
id|INVALID
comma
multiline_comment|/* 00 1 1100 */
id|INVALID
comma
multiline_comment|/* 00 1 1101 */
id|INVALID
comma
multiline_comment|/* 00 1 1110 */
id|INVALID
comma
multiline_comment|/* 00 1 1111 */
id|INVALID
comma
multiline_comment|/* 01 0 0000 */
id|INVALID
comma
multiline_comment|/* 01 0 0001 */
id|INVALID
comma
multiline_comment|/* 01 0 0010 */
id|INVALID
comma
multiline_comment|/* 01 0 0011 */
id|INVALID
comma
multiline_comment|/* 01 0 0100 */
id|INVALID
comma
multiline_comment|/* 01 0 0101: lwax?? */
id|INVALID
comma
multiline_comment|/* 01 0 0110 */
id|INVALID
comma
multiline_comment|/* 01 0 0111 */
(brace
l_int|0
comma
id|LD
op_plus
id|HARD
)brace
comma
multiline_comment|/* 01 0 1000: lswx */
(brace
l_int|0
comma
id|LD
op_plus
id|HARD
)brace
comma
multiline_comment|/* 01 0 1001: lswi */
(brace
l_int|0
comma
id|ST
op_plus
id|HARD
)brace
comma
multiline_comment|/* 01 0 1010: stswx */
(brace
l_int|0
comma
id|ST
op_plus
id|HARD
)brace
comma
multiline_comment|/* 01 0 1011: stswi */
id|INVALID
comma
multiline_comment|/* 01 0 1100 */
id|INVALID
comma
multiline_comment|/* 01 0 1101 */
id|INVALID
comma
multiline_comment|/* 01 0 1110 */
id|INVALID
comma
multiline_comment|/* 01 0 1111 */
id|INVALID
comma
multiline_comment|/* 01 1 0000 */
id|INVALID
comma
multiline_comment|/* 01 1 0001 */
id|INVALID
comma
multiline_comment|/* 01 1 0010 */
id|INVALID
comma
multiline_comment|/* 01 1 0011 */
id|INVALID
comma
multiline_comment|/* 01 1 0100 */
id|INVALID
comma
multiline_comment|/* 01 1 0101: lwaux?? */
id|INVALID
comma
multiline_comment|/* 01 1 0110 */
id|INVALID
comma
multiline_comment|/* 01 1 0111 */
id|INVALID
comma
multiline_comment|/* 01 1 1000 */
id|INVALID
comma
multiline_comment|/* 01 1 1001 */
id|INVALID
comma
multiline_comment|/* 01 1 1010 */
id|INVALID
comma
multiline_comment|/* 01 1 1011 */
id|INVALID
comma
multiline_comment|/* 01 1 1100 */
id|INVALID
comma
multiline_comment|/* 01 1 1101 */
id|INVALID
comma
multiline_comment|/* 01 1 1110 */
id|INVALID
comma
multiline_comment|/* 01 1 1111 */
id|INVALID
comma
multiline_comment|/* 10 0 0000 */
id|INVALID
comma
multiline_comment|/* 10 0 0001 */
(brace
l_int|0
comma
id|ST
op_plus
id|HARD
)brace
comma
multiline_comment|/* 10 0 0010: stwcx. */
id|INVALID
comma
multiline_comment|/* 10 0 0011 */
id|INVALID
comma
multiline_comment|/* 10 0 0100 */
id|INVALID
comma
multiline_comment|/* 10 0 0101 */
id|INVALID
comma
multiline_comment|/* 10 0 0110 */
id|INVALID
comma
multiline_comment|/* 10 0 0111 */
(brace
l_int|4
comma
id|LD
op_plus
id|S
)brace
comma
multiline_comment|/* 10 0 1000: lwbrx */
id|INVALID
comma
multiline_comment|/* 10 0 1001 */
(brace
l_int|4
comma
id|ST
op_plus
id|S
)brace
comma
multiline_comment|/* 10 0 1010: stwbrx */
id|INVALID
comma
multiline_comment|/* 10 0 1011 */
(brace
l_int|2
comma
id|LD
op_plus
id|S
)brace
comma
multiline_comment|/* 10 0 1100: lhbrx */
id|INVALID
comma
multiline_comment|/* 10 0 1101 */
(brace
l_int|2
comma
id|ST
op_plus
id|S
)brace
comma
multiline_comment|/* 10 0 1110: sthbrx */
id|INVALID
comma
multiline_comment|/* 10 0 1111 */
id|INVALID
comma
multiline_comment|/* 10 1 0000 */
id|INVALID
comma
multiline_comment|/* 10 1 0001 */
id|INVALID
comma
multiline_comment|/* 10 1 0010 */
id|INVALID
comma
multiline_comment|/* 10 1 0011 */
id|INVALID
comma
multiline_comment|/* 10 1 0100 */
id|INVALID
comma
multiline_comment|/* 10 1 0101 */
id|INVALID
comma
multiline_comment|/* 10 1 0110 */
id|INVALID
comma
multiline_comment|/* 10 1 0111 */
id|INVALID
comma
multiline_comment|/* 10 1 1000 */
id|INVALID
comma
multiline_comment|/* 10 1 1001 */
id|INVALID
comma
multiline_comment|/* 10 1 1010 */
id|INVALID
comma
multiline_comment|/* 10 1 1011 */
id|INVALID
comma
multiline_comment|/* 10 1 1100 */
id|INVALID
comma
multiline_comment|/* 10 1 1101 */
id|INVALID
comma
multiline_comment|/* 10 1 1110 */
(brace
l_int|0
comma
id|ST
op_plus
id|HARD
)brace
comma
multiline_comment|/* 10 1 1111: dcbz */
(brace
l_int|4
comma
id|LD
)brace
comma
multiline_comment|/* 11 0 0000: lwzx */
id|INVALID
comma
multiline_comment|/* 11 0 0001 */
(brace
l_int|4
comma
id|ST
)brace
comma
multiline_comment|/* 11 0 0010: stwx */
id|INVALID
comma
multiline_comment|/* 11 0 0011 */
(brace
l_int|2
comma
id|LD
)brace
comma
multiline_comment|/* 11 0 0100: lhzx */
(brace
l_int|2
comma
id|LD
op_plus
id|SE
)brace
comma
multiline_comment|/* 11 0 0101: lhax */
(brace
l_int|2
comma
id|ST
)brace
comma
multiline_comment|/* 11 0 0110: sthx */
id|INVALID
comma
multiline_comment|/* 11 0 0111 */
(brace
l_int|4
comma
id|LD
op_plus
id|F
op_plus
id|S
)brace
comma
multiline_comment|/* 11 0 1000: lfsx */
(brace
l_int|8
comma
id|LD
op_plus
id|F
)brace
comma
multiline_comment|/* 11 0 1001: lfdx */
(brace
l_int|4
comma
id|ST
op_plus
id|F
op_plus
id|S
)brace
comma
multiline_comment|/* 11 0 1010: stfsx */
(brace
l_int|8
comma
id|ST
op_plus
id|F
)brace
comma
multiline_comment|/* 11 0 1011: stfdx */
id|INVALID
comma
multiline_comment|/* 11 0 1100 */
id|INVALID
comma
multiline_comment|/* 11 0 1101 */
id|INVALID
comma
multiline_comment|/* 11 0 1110 */
id|INVALID
comma
multiline_comment|/* 11 0 1111 */
(brace
l_int|4
comma
id|LD
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 0000: lwzux */
id|INVALID
comma
multiline_comment|/* 11 1 0001 */
(brace
l_int|4
comma
id|ST
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 0010: stwux */
id|INVALID
comma
multiline_comment|/* 11 1 0011 */
(brace
l_int|2
comma
id|LD
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 0100: lhzux */
(brace
l_int|2
comma
id|LD
op_plus
id|SE
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 0101: lhaux */
(brace
l_int|2
comma
id|ST
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 0110: sthux */
id|INVALID
comma
multiline_comment|/* 11 1 0111 */
(brace
l_int|4
comma
id|LD
op_plus
id|F
op_plus
id|S
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 1000: lfsux */
(brace
l_int|8
comma
id|LD
op_plus
id|F
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 1001: lfdux */
(brace
l_int|4
comma
id|ST
op_plus
id|F
op_plus
id|S
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 1010: stfsux */
(brace
l_int|8
comma
id|ST
op_plus
id|F
op_plus
id|U
)brace
comma
multiline_comment|/* 11 1 1011: stfdux */
id|INVALID
comma
multiline_comment|/* 11 1 1100 */
id|INVALID
comma
multiline_comment|/* 11 1 1101 */
id|INVALID
comma
multiline_comment|/* 11 1 1110 */
id|INVALID
comma
multiline_comment|/* 11 1 1111 */
)brace
suffix:semicolon
DECL|macro|SWAP
mdefine_line|#define SWAP(a, b)&t;(t = (a), (a) = (b), (b) = t)
r_int
DECL|function|fix_alignment
id|fix_alignment
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|instr
comma
id|nb
comma
id|flags
suffix:semicolon
r_int
id|i
comma
id|t
suffix:semicolon
r_int
id|reg
comma
id|areg
suffix:semicolon
r_int
r_char
op_star
id|addr
suffix:semicolon
r_union
(brace
r_int
id|l
suffix:semicolon
r_float
id|f
suffix:semicolon
r_float
id|d
suffix:semicolon
r_int
r_char
id|v
(braket
l_int|8
)braket
suffix:semicolon
)brace
id|data
suffix:semicolon
id|instr
op_assign
(paren
id|regs-&gt;dsisr
op_rshift
l_int|10
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|nb
op_assign
id|aligninfo
(braket
id|instr
)braket
dot
id|len
suffix:semicolon
r_if
c_cond
(paren
id|nb
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* too hard or invalid instruction bits */
id|flags
op_assign
id|aligninfo
(braket
id|instr
)braket
dot
id|flags
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_char
op_star
)paren
id|regs-&gt;dar
suffix:semicolon
id|reg
op_assign
(paren
id|regs-&gt;dsisr
op_rshift
l_int|5
)paren
op_amp
l_int|0x1f
suffix:semicolon
multiline_comment|/* source/dest register */
multiline_comment|/* Verify the address of the operand */
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
r_if
c_cond
(paren
id|verify_area
c_func
(paren
(paren
id|flags
op_amp
id|ST
ques
c_cond
id|VERIFY_WRITE
suffix:colon
id|VERIFY_READ
)paren
comma
id|addr
comma
id|nb
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* bad address */
)brace
macro_line|#ifdef __SMP__
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|F
)paren
op_logical_and
(paren
id|regs-&gt;msr
op_amp
id|MSR_FP
)paren
)paren
id|smp_giveup_fpu
c_func
(paren
id|current
)paren
suffix:semicolon
macro_line|#else&t;
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|F
)paren
op_logical_and
id|last_task_used_math
op_eq
id|current
)paren
id|giveup_fpu
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|flags
op_amp
id|M
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* too hard for now */
multiline_comment|/* If we read the operand, copy it in */
r_if
c_cond
(paren
id|flags
op_amp
id|LD
)paren
(brace
r_if
c_cond
(paren
id|nb
op_eq
l_int|2
)paren
(brace
id|data.v
(braket
l_int|0
)braket
op_assign
id|data.v
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|data.v
(braket
l_int|2
)braket
comma
id|addr
)paren
op_logical_or
id|__get_user
c_func
(paren
id|data.v
(braket
l_int|3
)braket
comma
id|addr
op_plus
l_int|1
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nb
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|data.v
(braket
id|i
)braket
comma
id|addr
op_plus
id|i
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|flags
op_amp
op_complement
id|U
)paren
(brace
r_case
id|LD
op_plus
id|SE
suffix:colon
r_if
c_cond
(paren
id|data.v
(braket
l_int|2
)braket
op_ge
l_int|0x80
)paren
id|data.v
(braket
l_int|0
)braket
op_assign
id|data.v
(braket
l_int|1
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* fall through */
r_case
id|LD
suffix:colon
id|regs-&gt;gpr
(braket
id|reg
)braket
op_assign
id|data.l
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LD
op_plus
id|S
suffix:colon
r_if
c_cond
(paren
id|nb
op_eq
l_int|2
)paren
(brace
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|2
)braket
comma
id|data.v
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|0
)braket
comma
id|data.v
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|1
)braket
comma
id|data.v
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
id|regs-&gt;gpr
(braket
id|reg
)braket
op_assign
id|data.l
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ST
suffix:colon
id|data.l
op_assign
id|regs-&gt;gpr
(braket
id|reg
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ST
op_plus
id|S
suffix:colon
id|data.l
op_assign
id|regs-&gt;gpr
(braket
id|reg
)braket
suffix:semicolon
r_if
c_cond
(paren
id|nb
op_eq
l_int|2
)paren
(brace
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|2
)braket
comma
id|data.v
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|0
)braket
comma
id|data.v
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|SWAP
c_func
(paren
id|data.v
(braket
l_int|1
)braket
comma
id|data.v
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LD
op_plus
id|F
suffix:colon
id|current-&gt;tss.fpr
(braket
id|reg
)braket
op_assign
id|data.d
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ST
op_plus
id|F
suffix:colon
id|data.d
op_assign
id|current-&gt;tss.fpr
(braket
id|reg
)braket
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* these require some floating point conversions... */
multiline_comment|/* note that giveup_fpu enables the FPU for the kernel */
multiline_comment|/* we&squot;d like to use the assignment, but we have to compile&n;&t; * the kernel with -msoft-float so it doesn&squot;t use the&n;&t; * fp regs for copying 8-byte objects. */
r_case
id|LD
op_plus
id|F
op_plus
id|S
suffix:colon
macro_line|#ifdef __SMP__
r_if
c_cond
(paren
id|regs-&gt;msr
op_amp
id|MSR_FP
)paren
id|smp_giveup_fpu
c_func
(paren
id|current
)paren
suffix:semicolon
macro_line|#else&t;
id|giveup_fpu
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;&t;
id|cvt_fd
c_func
(paren
op_amp
id|data.f
comma
op_amp
id|current-&gt;tss.fpr
(braket
id|reg
)braket
)paren
suffix:semicolon
multiline_comment|/* current-&gt;tss.fpr[reg] = data.f; */
r_break
suffix:semicolon
r_case
id|ST
op_plus
id|F
op_plus
id|S
suffix:colon
macro_line|#ifdef __SMP__
r_if
c_cond
(paren
id|regs-&gt;msr
op_amp
id|MSR_FP
)paren
id|smp_giveup_fpu
c_func
(paren
id|current
)paren
suffix:semicolon
macro_line|#else&t;
id|giveup_fpu
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;&t;
id|cvt_df
c_func
(paren
op_amp
id|current-&gt;tss.fpr
(braket
id|reg
)braket
comma
op_amp
id|data.f
)paren
suffix:semicolon
multiline_comment|/* data.f = current-&gt;tss.fpr[reg]; */
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;align: can&squot;t handle flags=%x&bslash;n&quot;
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|ST
)paren
(brace
r_if
c_cond
(paren
id|nb
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|data.v
(braket
l_int|2
)braket
comma
id|addr
)paren
op_logical_or
id|__put_user
c_func
(paren
id|data.v
(braket
l_int|3
)braket
comma
id|addr
op_plus
l_int|1
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nb
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|data.v
(braket
id|i
)braket
comma
id|addr
op_plus
id|i
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|U
)paren
(brace
id|areg
op_assign
id|regs-&gt;dsisr
op_amp
l_int|0x1f
suffix:semicolon
multiline_comment|/* register to update */
id|regs-&gt;gpr
(braket
id|areg
)braket
op_assign
id|regs-&gt;dar
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
eof
