multiline_comment|/* $Id: math.c,v 1.4 1998/04/06 16:09:57 jj Exp $&n; * arch/sparc64/math-emu/math.c&n; *&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *&n; * Emulation routines originate from soft-fp package, which is part&n; * of glibc and has appropriate copyrights in it.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/fpumacro.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|FLOATFUNC
mdefine_line|#define FLOATFUNC(x) extern int x(void *,void *,void *);
DECL|function|FLOATFUNC
id|FLOATFUNC
c_func
(paren
id|FMOVQ
)paren
id|FLOATFUNC
c_func
(paren
id|FNEGQ
)paren
id|FLOATFUNC
c_func
(paren
id|FABSQ
)paren
id|FLOATFUNC
c_func
(paren
id|FSQRTQ
)paren
id|FLOATFUNC
c_func
(paren
id|FADDQ
)paren
id|FLOATFUNC
c_func
(paren
id|FSUBQ
)paren
id|FLOATFUNC
c_func
(paren
id|FMULQ
)paren
id|FLOATFUNC
c_func
(paren
id|FDIVQ
)paren
id|FLOATFUNC
c_func
(paren
id|FDMULQ
)paren
id|FLOATFUNC
c_func
(paren
id|FQTOX
)paren
id|FLOATFUNC
c_func
(paren
id|FXTOQ
)paren
id|FLOATFUNC
c_func
(paren
id|FQTOS
)paren
id|FLOATFUNC
c_func
(paren
id|FQTOD
)paren
id|FLOATFUNC
c_func
(paren
id|FITOQ
)paren
id|FLOATFUNC
c_func
(paren
id|FSTOQ
)paren
id|FLOATFUNC
c_func
(paren
id|FDTOQ
)paren
id|FLOATFUNC
c_func
(paren
id|FQTOI
)paren
id|FLOATFUNC
c_func
(paren
id|FCMPQ
)paren
id|FLOATFUNC
c_func
(paren
id|FCMPEQ
)paren
id|FLOATFUNC
c_func
(paren
id|FSQRTS
)paren
id|FLOATFUNC
c_func
(paren
id|FSQRTD
)paren
id|FLOATFUNC
c_func
(paren
id|FADDS
)paren
id|FLOATFUNC
c_func
(paren
id|FADDD
)paren
id|FLOATFUNC
c_func
(paren
id|FSUBS
)paren
id|FLOATFUNC
c_func
(paren
id|FSUBD
)paren
id|FLOATFUNC
c_func
(paren
id|FMULS
)paren
id|FLOATFUNC
c_func
(paren
id|FMULD
)paren
id|FLOATFUNC
c_func
(paren
id|FDIVS
)paren
id|FLOATFUNC
c_func
(paren
id|FDIVD
)paren
id|FLOATFUNC
c_func
(paren
id|FSMULD
)paren
id|FLOATFUNC
c_func
(paren
id|FSTOX
)paren
id|FLOATFUNC
c_func
(paren
id|FDTOX
)paren
id|FLOATFUNC
c_func
(paren
id|FDTOS
)paren
id|FLOATFUNC
c_func
(paren
id|FSTOD
)paren
id|FLOATFUNC
c_func
(paren
id|FSTOI
)paren
id|FLOATFUNC
c_func
(paren
id|FDTOI
)paren
r_int
id|do_mathemu
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|fpustate
op_star
id|f
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
id|u32
id|insn
op_assign
l_int|0
suffix:semicolon
r_int
id|type
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 01 is single, 10 is double, 11 is quad, &n;&t;&t;&t; 000011 is rs1, 001100 is rs2, 110000 is rd (00 in rd is fcc)&n;&t;&t;&t; 111100000000 tells which ftt may that happen in */
r_int
id|freg
suffix:semicolon
r_static
id|u64
id|zero
(braket
l_int|2
)braket
op_assign
(brace
l_int|0L
comma
l_int|0L
)brace
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_int
(paren
op_star
id|func
)paren
(paren
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
)paren
op_assign
l_int|NULL
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
l_string|&quot;FPQuad from kernel&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current-&gt;tss.flags
op_amp
id|SPARC_FLAG_32BIT
)paren
(brace
id|pc
op_assign
(paren
id|u32
)paren
id|pc
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|insn
comma
(paren
id|u32
op_star
)paren
id|pc
)paren
op_ne
op_minus
id|EFAULT
)paren
(brace
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc1f80000
)paren
op_eq
l_int|0x81a00000
)paren
multiline_comment|/* FPOP1 */
(brace
r_switch
c_cond
(paren
(paren
id|insn
op_rshift
l_int|5
)paren
op_amp
l_int|0x1ff
)paren
(brace
multiline_comment|/* QUAD - ftt == 3 */
r_case
l_int|0x003
suffix:colon
id|type
op_assign
l_int|0x33c
suffix:semicolon
id|func
op_assign
id|FMOVQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x007
suffix:colon
id|type
op_assign
l_int|0x33c
suffix:semicolon
id|func
op_assign
id|FNEGQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00b
suffix:colon
id|type
op_assign
l_int|0x33c
suffix:semicolon
id|func
op_assign
id|FABSQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x02b
suffix:colon
id|type
op_assign
l_int|0x33c
suffix:semicolon
id|func
op_assign
id|FSQRTQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x043
suffix:colon
id|type
op_assign
l_int|0x33f
suffix:semicolon
id|func
op_assign
id|FADDQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x047
suffix:colon
id|type
op_assign
l_int|0x33f
suffix:semicolon
id|func
op_assign
id|FSUBQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x04b
suffix:colon
id|type
op_assign
l_int|0x33f
suffix:semicolon
id|func
op_assign
id|FMULQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x04f
suffix:colon
id|type
op_assign
l_int|0x33f
suffix:semicolon
id|func
op_assign
id|FDIVQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x06e
suffix:colon
id|type
op_assign
l_int|0x33a
suffix:semicolon
id|func
op_assign
id|FDMULQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x083
suffix:colon
id|type
op_assign
l_int|0x32c
suffix:semicolon
id|func
op_assign
id|FQTOX
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x08c
suffix:colon
id|type
op_assign
l_int|0x338
suffix:semicolon
id|func
op_assign
id|FXTOQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0c7
suffix:colon
id|type
op_assign
l_int|0x31c
suffix:semicolon
id|func
op_assign
id|FQTOS
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0cb
suffix:colon
id|type
op_assign
l_int|0x32c
suffix:semicolon
id|func
op_assign
id|FQTOD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0cc
suffix:colon
id|type
op_assign
l_int|0x334
suffix:semicolon
id|func
op_assign
id|FITOQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0cd
suffix:colon
id|type
op_assign
l_int|0x334
suffix:semicolon
id|func
op_assign
id|FSTOQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0ce
suffix:colon
id|type
op_assign
l_int|0x338
suffix:semicolon
id|func
op_assign
id|FDTOQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0d3
suffix:colon
id|type
op_assign
l_int|0x31c
suffix:semicolon
id|func
op_assign
id|FQTOI
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* SUBNORMAL - ftt == 2 */
r_case
l_int|0x029
suffix:colon
id|type
op_assign
l_int|0x214
suffix:semicolon
id|func
op_assign
id|FSQRTS
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x02a
suffix:colon
id|type
op_assign
l_int|0x228
suffix:semicolon
id|func
op_assign
id|FSQRTD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x041
suffix:colon
id|type
op_assign
l_int|0x215
suffix:semicolon
id|func
op_assign
id|FADDS
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x042
suffix:colon
id|type
op_assign
l_int|0x22a
suffix:semicolon
id|func
op_assign
id|FADDD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x045
suffix:colon
id|type
op_assign
l_int|0x215
suffix:semicolon
id|func
op_assign
id|FSUBS
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x046
suffix:colon
id|type
op_assign
l_int|0x22a
suffix:semicolon
id|func
op_assign
id|FSUBD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x049
suffix:colon
id|type
op_assign
l_int|0x215
suffix:semicolon
id|func
op_assign
id|FMULS
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x04a
suffix:colon
id|type
op_assign
l_int|0x22a
suffix:semicolon
id|func
op_assign
id|FMULD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x04d
suffix:colon
id|type
op_assign
l_int|0x215
suffix:semicolon
id|func
op_assign
id|FDIVS
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x04e
suffix:colon
id|type
op_assign
l_int|0x22a
suffix:semicolon
id|func
op_assign
id|FDIVD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x069
suffix:colon
id|type
op_assign
l_int|0x225
suffix:semicolon
id|func
op_assign
id|FSMULD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x081
suffix:colon
id|type
op_assign
l_int|0x224
suffix:semicolon
id|func
op_assign
id|FSTOX
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x082
suffix:colon
id|type
op_assign
l_int|0x228
suffix:semicolon
id|func
op_assign
id|FDTOX
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0c6
suffix:colon
id|type
op_assign
l_int|0x218
suffix:semicolon
id|func
op_assign
id|FDTOS
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0c9
suffix:colon
id|type
op_assign
l_int|0x224
suffix:semicolon
id|func
op_assign
id|FSTOD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0d1
suffix:colon
id|type
op_assign
l_int|0x214
suffix:semicolon
id|func
op_assign
id|FSTOI
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0d2
suffix:colon
id|type
op_assign
l_int|0x218
suffix:semicolon
id|func
op_assign
id|FDTOI
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc1f80000
)paren
op_eq
l_int|0x81a80000
)paren
multiline_comment|/* FPOP2 */
(brace
r_switch
c_cond
(paren
(paren
id|insn
op_rshift
l_int|5
)paren
op_amp
l_int|0x1ff
)paren
(brace
r_case
l_int|0x053
suffix:colon
id|type
op_assign
l_int|0x30f
suffix:semicolon
id|func
op_assign
id|FCMPQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x057
suffix:colon
id|type
op_assign
l_int|0x30f
suffix:semicolon
id|func
op_assign
id|FCMPEQ
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|type
)paren
(brace
r_void
op_star
id|rs1
op_assign
l_int|NULL
comma
op_star
id|rs2
op_assign
l_int|NULL
comma
op_star
id|rd
op_assign
l_int|NULL
suffix:semicolon
id|freg
op_assign
(paren
id|f-&gt;fsr
op_rshift
l_int|14
)paren
op_amp
l_int|0xf
suffix:semicolon
r_if
c_cond
(paren
id|freg
op_ne
(paren
id|type
op_rshift
l_int|8
)paren
)paren
r_goto
id|err
suffix:semicolon
id|f-&gt;fsr
op_and_assign
op_complement
l_int|0x1c000
suffix:semicolon
id|freg
op_assign
(paren
(paren
id|insn
op_rshift
l_int|14
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|type
op_amp
l_int|0x3
)paren
(brace
r_case
l_int|3
suffix:colon
r_if
c_cond
(paren
id|freg
op_amp
l_int|2
)paren
(brace
id|f-&gt;fsr
op_or_assign
(paren
l_int|6
op_lshift
l_int|14
)paren
multiline_comment|/* invalid_fp_register */
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
r_case
l_int|2
suffix:colon
id|freg
op_assign
(paren
(paren
id|freg
op_amp
l_int|1
)paren
op_lshift
l_int|5
)paren
op_or
(paren
id|freg
op_amp
l_int|0x1e
)paren
suffix:semicolon
r_case
l_int|1
suffix:colon
id|rs1
op_assign
(paren
r_void
op_star
)paren
op_amp
id|f-&gt;regs
(braket
id|freg
)braket
suffix:semicolon
id|flags
op_assign
(paren
id|freg
OL
l_int|32
)paren
ques
c_cond
id|SPARC_FLAG_USEDFPUL
suffix:colon
id|SPARC_FLAG_USEDFPUU
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;tss.flags
op_amp
id|flags
)paren
)paren
id|rs1
op_assign
(paren
r_void
op_star
)paren
op_amp
id|zero
suffix:semicolon
r_break
suffix:semicolon
)brace
id|freg
op_assign
(paren
id|insn
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|type
op_rshift
l_int|2
)paren
op_amp
l_int|0x3
)paren
(brace
r_case
l_int|3
suffix:colon
r_if
c_cond
(paren
id|freg
op_amp
l_int|2
)paren
(brace
id|f-&gt;fsr
op_or_assign
(paren
l_int|6
op_lshift
l_int|14
)paren
multiline_comment|/* invalid_fp_register */
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
r_case
l_int|2
suffix:colon
id|freg
op_assign
(paren
(paren
id|freg
op_amp
l_int|1
)paren
op_lshift
l_int|5
)paren
op_or
(paren
id|freg
op_amp
l_int|0x1e
)paren
suffix:semicolon
r_case
l_int|1
suffix:colon
id|rs2
op_assign
(paren
r_void
op_star
)paren
op_amp
id|f-&gt;regs
(braket
id|freg
)braket
suffix:semicolon
id|flags
op_assign
(paren
id|freg
OL
l_int|32
)paren
ques
c_cond
id|SPARC_FLAG_USEDFPUL
suffix:colon
id|SPARC_FLAG_USEDFPUU
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;tss.flags
op_amp
id|flags
)paren
)paren
id|rs2
op_assign
(paren
r_void
op_star
)paren
op_amp
id|zero
suffix:semicolon
r_break
suffix:semicolon
)brace
id|freg
op_assign
(paren
(paren
id|insn
op_rshift
l_int|25
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|type
op_rshift
l_int|4
)paren
op_amp
l_int|0x3
)paren
(brace
r_case
l_int|0
suffix:colon
id|rd
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
(paren
r_int
)paren
op_amp
id|f-&gt;fsr
)paren
op_or
(paren
id|freg
op_amp
l_int|3
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_if
c_cond
(paren
id|freg
op_amp
l_int|2
)paren
(brace
id|f-&gt;fsr
op_or_assign
(paren
l_int|6
op_lshift
l_int|14
)paren
multiline_comment|/* invalid_fp_register */
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
r_case
l_int|2
suffix:colon
id|freg
op_assign
(paren
(paren
id|freg
op_amp
l_int|1
)paren
op_lshift
l_int|5
)paren
op_or
(paren
id|freg
op_amp
l_int|0x1e
)paren
suffix:semicolon
r_case
l_int|1
suffix:colon
id|rd
op_assign
(paren
r_void
op_star
)paren
op_amp
id|f-&gt;regs
(braket
id|freg
)braket
suffix:semicolon
id|flags
op_assign
(paren
id|freg
OL
l_int|32
)paren
ques
c_cond
id|SPARC_FLAG_USEDFPUL
suffix:colon
id|SPARC_FLAG_USEDFPUU
suffix:semicolon
id|regs-&gt;fprs
op_or_assign
id|FPRS_FEF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;tss.flags
op_amp
id|SPARC_FLAG_USEDFPU
)paren
)paren
(brace
id|current-&gt;tss.flags
op_or_assign
id|SPARC_FLAG_USEDFPU
suffix:semicolon
id|f-&gt;fsr
op_assign
l_int|0
suffix:semicolon
id|f-&gt;gsr
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;tss.flags
op_amp
id|flags
)paren
)paren
(brace
r_if
c_cond
(paren
id|freg
OL
l_int|32
)paren
id|memset
c_func
(paren
id|f-&gt;regs
comma
l_int|0
comma
l_int|32
op_star
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
r_else
id|memset
c_func
(paren
id|f-&gt;regs
op_plus
l_int|32
comma
l_int|0
comma
l_int|32
op_star
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
)brace
id|current-&gt;tss.flags
op_or_assign
id|flags
suffix:semicolon
r_break
suffix:semicolon
)brace
id|func
c_func
(paren
id|rd
comma
id|rs2
comma
id|rs1
)paren
suffix:semicolon
id|regs-&gt;tpc
op_assign
id|regs-&gt;tnpc
suffix:semicolon
id|regs-&gt;tnpc
op_add_assign
l_int|4
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|err
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
eof
