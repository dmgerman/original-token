multiline_comment|/*---------------------------------------------------------------------------+&n; |  fpu_system.h                                                             |&n; |                                                                           |&n; | Copyright (C) 1992,1994                                                   |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail   billm@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#ifndef _FPU_SYSTEM_H
DECL|macro|_FPU_SYSTEM_H
mdefine_line|#define _FPU_SYSTEM_H
multiline_comment|/* system dependent definitions */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
multiline_comment|/* This sets the pointer FPU_info to point to the argument part&n;   of the stack frame of math_emulate() */
DECL|macro|SETUP_DATA_AREA
mdefine_line|#define SETUP_DATA_AREA(arg)    FPU_info = (struct info *) &amp;arg
DECL|macro|I387
mdefine_line|#define I387&t;&t;&t;(current-&gt;tss.i387)
DECL|macro|FPU_info
mdefine_line|#define FPU_info&t;&t;(I387.soft.info)
DECL|macro|FPU_CS
mdefine_line|#define FPU_CS&t;&t;&t;(*(unsigned short *) &amp;(FPU_info-&gt;___cs))
DECL|macro|FPU_SS
mdefine_line|#define FPU_SS&t;&t;&t;(*(unsigned short *) &amp;(FPU_info-&gt;___ss))
DECL|macro|FPU_DS
mdefine_line|#define FPU_DS&t;&t;&t;(*(unsigned short *) &amp;(FPU_info-&gt;___ds))
DECL|macro|FPU_EAX
mdefine_line|#define FPU_EAX&t;&t;&t;(FPU_info-&gt;___eax)
DECL|macro|FPU_EFLAGS
mdefine_line|#define FPU_EFLAGS&t;&t;(FPU_info-&gt;___eflags)
DECL|macro|FPU_EIP
mdefine_line|#define FPU_EIP&t;&t;&t;(FPU_info-&gt;___eip)
DECL|macro|FPU_ORIG_EIP
mdefine_line|#define FPU_ORIG_EIP&t;&t;(FPU_info-&gt;___orig_eip)
DECL|macro|FPU_lookahead
mdefine_line|#define FPU_lookahead           (I387.soft.lookahead)
DECL|macro|FPU_entry_eip
mdefine_line|#define FPU_entry_eip           (I387.soft.entry_eip)
DECL|macro|partial_status
mdefine_line|#define partial_status       &t;(I387.soft.swd)
DECL|macro|control_word
mdefine_line|#define control_word&t;&t;(I387.soft.cwd)
DECL|macro|regs
mdefine_line|#define regs&t;&t;&t;(I387.soft.regs)
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
DECL|macro|FPU_verify_area
mdefine_line|#define FPU_verify_area(x,y,z)  if ( verify_area(x,y,z) ) &bslash;&n;                                math_abort(FPU_info,SIGSEGV)
DECL|macro|FPU_IGNORE_CODE_SEGV
macro_line|#undef FPU_IGNORE_CODE_SEGV
macro_line|#ifdef FPU_IGNORE_CODE_SEGV
multiline_comment|/* verify_area() is very expensive, and causes the emulator to run&n;   about 20% slower if applied to the code. Anyway, errors due to bad&n;   code addresses should be much rarer than errors due to bad data&n;   addresses. */
DECL|macro|FPU_code_verify_area
mdefine_line|#define&t;FPU_code_verify_area(z)
macro_line|#else
multiline_comment|/* A simpler test than verify_area() can probably be done for&n;   FPU_code_verify_area() because the only possible error is to step&n;   past the upper boundary of a legal code area. */
DECL|macro|FPU_code_verify_area
mdefine_line|#define&t;FPU_code_verify_area(z) FPU_verify_area(VERIFY_READ,(void *)FPU_EIP,z)
macro_line|#endif
multiline_comment|/* ######## temporary and ugly ;-) */
DECL|macro|FPU_data_address
mdefine_line|#define FPU_data_address        ((void *)(I387.soft.twd))
macro_line|#endif
eof
