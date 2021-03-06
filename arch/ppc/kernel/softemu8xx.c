multiline_comment|/*&n; * Software emulation of some PPC instructions for the 8xx core.&n; *&n; * Copyright (C) 1998 Dan Malek (dmalek@jlc.net)&n; *&n; * Software floating emuation for the MPC8xx processor.  I did this mostly&n; * because it was easier than trying to get the libraries compiled for&n; * software floating point.  The goal is still to get the libraries done,&n; * but I lost patience and needed some hacks to at least get init and&n; * shells running.  The first problem is the setjmp/longjmp that save&n; * and restore the floating point registers.&n; *&n; * For this emulation, our working registers are found on the register&n; * save area.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/* Eventually we may need a look-up table, but this works for now.&n;*/
DECL|macro|LFS
mdefine_line|#define LFS&t;48
DECL|macro|LFD
mdefine_line|#define LFD&t;50
DECL|macro|LFDU
mdefine_line|#define LFDU&t;51
DECL|macro|STFD
mdefine_line|#define STFD&t;54
DECL|macro|STFDU
mdefine_line|#define STFDU&t;55
DECL|macro|FMR
mdefine_line|#define FMR&t;63
multiline_comment|/*&n; * We return 0 on success, 1 on unimplemented instruction, and EFAULT&n; * if a load/store faulted.&n; */
r_int
DECL|function|Soft_emulate_8xx
id|Soft_emulate_8xx
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|uint
id|inst
comma
id|instword
suffix:semicolon
id|uint
id|flreg
comma
id|idxreg
comma
id|disp
suffix:semicolon
id|uint
id|retval
suffix:semicolon
r_int
r_int
id|sdisp
suffix:semicolon
id|uint
op_star
id|ea
comma
op_star
id|ip
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
id|instword
op_assign
op_star
(paren
(paren
id|uint
op_star
)paren
id|regs-&gt;nip
)paren
suffix:semicolon
id|inst
op_assign
id|instword
op_rshift
l_int|26
suffix:semicolon
id|flreg
op_assign
(paren
id|instword
op_rshift
l_int|21
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|idxreg
op_assign
(paren
id|instword
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|disp
op_assign
id|instword
op_amp
l_int|0xffff
suffix:semicolon
id|ea
op_assign
(paren
id|uint
op_star
)paren
(paren
id|regs-&gt;gpr
(braket
id|idxreg
)braket
op_plus
id|disp
)paren
suffix:semicolon
id|ip
op_assign
(paren
id|uint
op_star
)paren
op_amp
id|current-&gt;thread.fpr
(braket
id|flreg
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|inst
)paren
(brace
r_case
id|LFD
suffix:colon
multiline_comment|/* this is a 16 bit quantity that is sign extended&n;&t;&t; * so use a signed short here -- Cort&n;&t;&t; */
id|sdisp
op_assign
(paren
id|instword
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|ea
op_assign
(paren
id|uint
op_star
)paren
(paren
id|regs-&gt;gpr
(braket
id|idxreg
)braket
op_plus
id|sdisp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|ip
comma
id|ea
comma
r_sizeof
(paren
r_float
)paren
)paren
)paren
id|retval
op_assign
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LFDU
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|ip
comma
id|ea
comma
r_sizeof
(paren
r_float
)paren
)paren
)paren
id|retval
op_assign
id|EFAULT
suffix:semicolon
r_else
id|regs-&gt;gpr
(braket
id|idxreg
)braket
op_assign
(paren
id|uint
)paren
id|ea
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LFS
suffix:colon
id|sdisp
op_assign
(paren
id|instword
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|ea
op_assign
(paren
id|uint
op_star
)paren
(paren
id|regs-&gt;gpr
(braket
id|idxreg
)braket
op_plus
id|sdisp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|ip
comma
id|ea
comma
r_sizeof
(paren
r_float
)paren
)paren
)paren
id|retval
op_assign
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|STFD
suffix:colon
multiline_comment|/* this is a 16 bit quantity that is sign extended&n;&t;&t; * so use a signed short here -- Cort&n;&t;&t; */
id|sdisp
op_assign
(paren
id|instword
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|ea
op_assign
(paren
id|uint
op_star
)paren
(paren
id|regs-&gt;gpr
(braket
id|idxreg
)braket
op_plus
id|sdisp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ea
comma
id|ip
comma
r_sizeof
(paren
r_float
)paren
)paren
)paren
id|retval
op_assign
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|STFDU
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ea
comma
id|ip
comma
r_sizeof
(paren
r_float
)paren
)paren
)paren
id|retval
op_assign
id|EFAULT
suffix:semicolon
r_else
id|regs-&gt;gpr
(braket
id|idxreg
)braket
op_assign
(paren
id|uint
)paren
id|ea
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FMR
suffix:colon
multiline_comment|/* assume this is a fp move -- Cort */
id|memcpy
c_func
(paren
id|ip
comma
op_amp
id|current-&gt;thread.fpr
(braket
(paren
id|instword
op_rshift
l_int|11
)paren
op_amp
l_int|0x1f
)braket
comma
r_sizeof
(paren
r_float
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|retval
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Bad emulation %s/%d&bslash;n&quot;
l_string|&quot; NIP: %08x instruction: %08x opcode: %x &quot;
l_string|&quot;A: %x B: %x C: %x code: %x rc: %x&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|regs-&gt;nip
comma
id|instword
comma
id|inst
comma
(paren
id|instword
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
comma
(paren
id|instword
op_rshift
l_int|11
)paren
op_amp
l_int|0x1f
comma
(paren
id|instword
op_rshift
l_int|6
)paren
op_amp
l_int|0x1f
comma
(paren
id|instword
op_rshift
l_int|1
)paren
op_amp
l_int|0x3ff
comma
id|instword
op_amp
l_int|1
)paren
suffix:semicolon
(brace
r_int
id|pa
suffix:semicolon
id|print_8xx_pte
c_func
(paren
id|current-&gt;mm
comma
id|regs-&gt;nip
)paren
suffix:semicolon
id|pa
op_assign
id|get_8xx_pte
c_func
(paren
id|current-&gt;mm
comma
id|regs-&gt;nip
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
id|pa
op_or_assign
(paren
id|regs-&gt;nip
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
id|pa
op_assign
id|__va
c_func
(paren
id|pa
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Kernel VA for NIP %x &quot;
comma
id|pa
)paren
suffix:semicolon
id|print_8xx_pte
c_func
(paren
id|current-&gt;mm
comma
id|pa
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
id|regs-&gt;nip
op_add_assign
l_int|4
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
