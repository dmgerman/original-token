multiline_comment|/*---------------------------------------------------------------------------+&n; |  fpu_system.h                                                             |&n; |                                                                           |&n; | Copyright (C) 1992    W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail apm233m@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#ifndef _FPU_SYSTEM_H
DECL|macro|_FPU_SYSTEM_H
mdefine_line|#define _FPU_SYSTEM_H
multiline_comment|/* system dependent definitions */
macro_line|#include &lt;linux/math_emu.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
DECL|macro|FPU_CS
mdefine_line|#define FPU_CS&t;&t;&t;(*(unsigned short *) &amp;(FPU_info-&gt;___cs))
DECL|macro|FPU_DS
mdefine_line|#define FPU_DS&t;&t;&t;(*(unsigned short *) &amp;(FPU_info-&gt;___ds))
DECL|macro|FPU_EFLAGS
mdefine_line|#define FPU_EFLAGS&t;&t;(FPU_info-&gt;___eflags)
DECL|macro|FPU_EIP
mdefine_line|#define FPU_EIP&t;&t;&t;(FPU_info-&gt;___eip)
DECL|macro|FPU_ORIG_EIP
mdefine_line|#define FPU_ORIG_EIP&t;&t;(FPU_info-&gt;___orig_eip)
DECL|macro|status_word
mdefine_line|#define status_word&t;&t;(I387.soft.swd)
DECL|macro|control_word
mdefine_line|#define control_word&t;&t;(I387.soft.cwd)
DECL|macro|regs
mdefine_line|#define regs&t;&t;&t;((REG *)(&amp;(I387.soft.regs_space)))
DECL|macro|top
mdefine_line|#define top&t;&t;&t;(I387.soft.top)
DECL|macro|ip_offset
mdefine_line|#define ip_offset&t;&t;(I387.soft.fip)
DECL|macro|cs_selector
mdefine_line|#define cs_selector&t;&t;(I387.soft.fcs)
DECL|macro|data_operand_offset
mdefine_line|#define data_operand_offset&t;(I387.soft.foo)
DECL|macro|operand_selector
mdefine_line|#define operand_selector&t;(I387.soft.fos)
r_extern
r_struct
id|info
op_star
id|FPU_info
suffix:semicolon
macro_line|#endif
eof
