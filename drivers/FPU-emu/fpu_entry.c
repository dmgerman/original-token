multiline_comment|/*---------------------------------------------------------------------------+&n; |  fpu_entry.c                                                              |&n; |                                                                           |&n; | The entry function for wm-FPU-emu                                         |&n; |                                                                           |&n; | Copyright (C) 1992,1993,1994                                              |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail   billm@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; | See the files &quot;README&quot; and &quot;COPYING&quot; for further copyright and warranty   |&n; | information.                                                              |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
multiline_comment|/*---------------------------------------------------------------------------+&n; | Note:                                                                     |&n; |    The file contains code which accesses user memory.                     |&n; |    Emulator static data may change when user memory is accessed, due to   |&n; |    other processes using the emulator while swapping is in progress.      |&n; +---------------------------------------------------------------------------*/
multiline_comment|/*---------------------------------------------------------------------------+&n; | math_emulate() is the sole entry point for wm-FPU-emu                     |&n; +---------------------------------------------------------------------------*/
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/segment.h&gt;
macro_line|#include &quot;fpu_system.h&quot;
macro_line|#include &quot;fpu_emu.h&quot;
macro_line|#include &quot;exception.h&quot;
macro_line|#include &quot;control_w.h&quot;
macro_line|#include &quot;status_w.h&quot;
macro_line|#include &lt;asm/segment.h&gt;
DECL|macro|__BAD__
mdefine_line|#define __BAD__ FPU_illegal   /* Illegal on an 80486, causes SIGILL */
macro_line|#ifndef NO_UNDOC_CODE    /* Un-documented FPU op-codes supported by default. */
multiline_comment|/* WARNING: These codes are not documented by Intel in their 80486 manual&n;   and may not work on FPU clones or later Intel FPUs. */
multiline_comment|/* Changes to support the un-doc codes provided by Linus Torvalds. */
DECL|macro|_d9_d8_
mdefine_line|#define _d9_d8_ fstp_i    /* unofficial code (19) */
DECL|macro|_dc_d0_
mdefine_line|#define _dc_d0_ fcom_st   /* unofficial code (14) */
DECL|macro|_dc_d8_
mdefine_line|#define _dc_d8_ fcompst   /* unofficial code (1c) */
DECL|macro|_dd_c8_
mdefine_line|#define _dd_c8_ fxch_i    /* unofficial code (0d) */
DECL|macro|_de_d0_
mdefine_line|#define _de_d0_ fcompst   /* unofficial code (16) */
DECL|macro|_df_c0_
mdefine_line|#define _df_c0_ ffreep    /* unofficial code (07) ffree + pop */
DECL|macro|_df_c8_
mdefine_line|#define _df_c8_ fxch_i    /* unofficial code (0f) */
DECL|macro|_df_d0_
mdefine_line|#define _df_d0_ fstp_i    /* unofficial code (17) */
DECL|macro|_df_d8_
mdefine_line|#define _df_d8_ fstp_i    /* unofficial code (1f) */
DECL|variable|st_instr_table
r_static
id|FUNC
r_const
id|st_instr_table
(braket
l_int|64
)braket
op_assign
(brace
id|fadd__
comma
id|fld_i_
comma
id|__BAD__
comma
id|__BAD__
comma
id|fadd_i
comma
id|ffree_
comma
id|faddp_
comma
id|_df_c0_
comma
id|fmul__
comma
id|fxch_i
comma
id|__BAD__
comma
id|__BAD__
comma
id|fmul_i
comma
id|_dd_c8_
comma
id|fmulp_
comma
id|_df_c8_
comma
id|fcom_st
comma
id|fp_nop
comma
id|__BAD__
comma
id|__BAD__
comma
id|_dc_d0_
comma
id|fst_i_
comma
id|_de_d0_
comma
id|_df_d0_
comma
id|fcompst
comma
id|_d9_d8_
comma
id|__BAD__
comma
id|__BAD__
comma
id|_dc_d8_
comma
id|fstp_i
comma
id|fcompp
comma
id|_df_d8_
comma
id|fsub__
comma
id|fp_etc
comma
id|__BAD__
comma
id|finit_
comma
id|fsubri
comma
id|fucom_
comma
id|fsubrp
comma
id|fstsw_
comma
id|fsubr_
comma
id|fconst
comma
id|fucompp
comma
id|__BAD__
comma
id|fsub_i
comma
id|fucomp
comma
id|fsubp_
comma
id|__BAD__
comma
id|fdiv__
comma
id|trig_a
comma
id|__BAD__
comma
id|__BAD__
comma
id|fdivri
comma
id|__BAD__
comma
id|fdivrp
comma
id|__BAD__
comma
id|fdivr_
comma
id|trig_b
comma
id|__BAD__
comma
id|__BAD__
comma
id|fdiv_i
comma
id|__BAD__
comma
id|fdivp_
comma
id|__BAD__
comma
)brace
suffix:semicolon
macro_line|#else     /* Support only documented FPU op-codes */
DECL|variable|st_instr_table
r_static
id|FUNC
r_const
id|st_instr_table
(braket
l_int|64
)braket
op_assign
(brace
id|fadd__
comma
id|fld_i_
comma
id|__BAD__
comma
id|__BAD__
comma
id|fadd_i
comma
id|ffree_
comma
id|faddp_
comma
id|__BAD__
comma
id|fmul__
comma
id|fxch_i
comma
id|__BAD__
comma
id|__BAD__
comma
id|fmul_i
comma
id|__BAD__
comma
id|fmulp_
comma
id|__BAD__
comma
id|fcom_st
comma
id|fp_nop
comma
id|__BAD__
comma
id|__BAD__
comma
id|__BAD__
comma
id|fst_i_
comma
id|__BAD__
comma
id|__BAD__
comma
id|fcompst
comma
id|__BAD__
comma
id|__BAD__
comma
id|__BAD__
comma
id|__BAD__
comma
id|fstp_i
comma
id|fcompp
comma
id|__BAD__
comma
id|fsub__
comma
id|fp_etc
comma
id|__BAD__
comma
id|finit_
comma
id|fsubri
comma
id|fucom_
comma
id|fsubrp
comma
id|fstsw_
comma
id|fsubr_
comma
id|fconst
comma
id|fucompp
comma
id|__BAD__
comma
id|fsub_i
comma
id|fucomp
comma
id|fsubp_
comma
id|__BAD__
comma
id|fdiv__
comma
id|trig_a
comma
id|__BAD__
comma
id|__BAD__
comma
id|fdivri
comma
id|__BAD__
comma
id|fdivrp
comma
id|__BAD__
comma
id|fdivr_
comma
id|trig_b
comma
id|__BAD__
comma
id|__BAD__
comma
id|fdiv_i
comma
id|__BAD__
comma
id|fdivp_
comma
id|__BAD__
comma
)brace
suffix:semicolon
macro_line|#endif NO_UNDOC_CODE
DECL|macro|_NONE_
mdefine_line|#define _NONE_ 0   /* Take no special action */
DECL|macro|_REG0_
mdefine_line|#define _REG0_ 1   /* Need to check for not empty st(0) */
DECL|macro|_REGI_
mdefine_line|#define _REGI_ 2   /* Need to check for not empty st(0) and st(rm) */
DECL|macro|_REGi_
mdefine_line|#define _REGi_ 0   /* Uses st(rm) */
DECL|macro|_PUSH_
mdefine_line|#define _PUSH_ 3   /* Need to check for space to push onto stack */
DECL|macro|_null_
mdefine_line|#define _null_ 4   /* Function illegal or not implemented */
DECL|macro|_REGIi
mdefine_line|#define _REGIi 5   /* Uses st(0) and st(rm), result to st(rm) */
DECL|macro|_REGIp
mdefine_line|#define _REGIp 6   /* Uses st(0) and st(rm), result to st(rm) then pop */
DECL|macro|_REGIc
mdefine_line|#define _REGIc 0   /* Compare st(0) and st(rm) */
DECL|macro|_REGIn
mdefine_line|#define _REGIn 0   /* Uses st(0) and st(rm), but handle checks later */
macro_line|#ifndef NO_UNDOC_CODE
multiline_comment|/* Un-documented FPU op-codes supported by default. (see above) */
DECL|variable|type_table
r_static
r_int
r_char
r_const
id|type_table
(braket
l_int|64
)braket
op_assign
(brace
id|_REGI_
comma
id|_NONE_
comma
id|_null_
comma
id|_null_
comma
id|_REGIi
comma
id|_REGi_
comma
id|_REGIp
comma
id|_REGi_
comma
id|_REGI_
comma
id|_REGIn
comma
id|_null_
comma
id|_null_
comma
id|_REGIi
comma
id|_REGI_
comma
id|_REGIp
comma
id|_REGI_
comma
id|_REGIc
comma
id|_NONE_
comma
id|_null_
comma
id|_null_
comma
id|_REGIc
comma
id|_REG0_
comma
id|_REGIc
comma
id|_REG0_
comma
id|_REGIc
comma
id|_REG0_
comma
id|_null_
comma
id|_null_
comma
id|_REGIc
comma
id|_REG0_
comma
id|_REGIc
comma
id|_REG0_
comma
id|_REGI_
comma
id|_NONE_
comma
id|_null_
comma
id|_NONE_
comma
id|_REGIi
comma
id|_REGIc
comma
id|_REGIp
comma
id|_NONE_
comma
id|_REGI_
comma
id|_NONE_
comma
id|_REGIc
comma
id|_null_
comma
id|_REGIi
comma
id|_REGIc
comma
id|_REGIp
comma
id|_null_
comma
id|_REGI_
comma
id|_NONE_
comma
id|_null_
comma
id|_null_
comma
id|_REGIi
comma
id|_null_
comma
id|_REGIp
comma
id|_null_
comma
id|_REGI_
comma
id|_NONE_
comma
id|_null_
comma
id|_null_
comma
id|_REGIi
comma
id|_null_
comma
id|_REGIp
comma
id|_null_
)brace
suffix:semicolon
macro_line|#else     /* Support only documented FPU op-codes */
DECL|variable|type_table
r_static
r_int
r_char
r_const
id|type_table
(braket
l_int|64
)braket
op_assign
(brace
id|_REGI_
comma
id|_NONE_
comma
id|_null_
comma
id|_null_
comma
id|_REGIi
comma
id|_REGi_
comma
id|_REGIp
comma
id|_null_
comma
id|_REGI_
comma
id|_REGIn
comma
id|_null_
comma
id|_null_
comma
id|_REGIi
comma
id|_null_
comma
id|_REGIp
comma
id|_null_
comma
id|_REGIc
comma
id|_NONE_
comma
id|_null_
comma
id|_null_
comma
id|_null_
comma
id|_REG0_
comma
id|_null_
comma
id|_null_
comma
id|_REGIc
comma
id|_null_
comma
id|_null_
comma
id|_null_
comma
id|_null_
comma
id|_REG0_
comma
id|_REGIc
comma
id|_null_
comma
id|_REGI_
comma
id|_NONE_
comma
id|_null_
comma
id|_NONE_
comma
id|_REGIi
comma
id|_REGIc
comma
id|_REGIp
comma
id|_NONE_
comma
id|_REGI_
comma
id|_NONE_
comma
id|_REGIc
comma
id|_null_
comma
id|_REGIi
comma
id|_REGIc
comma
id|_REGIp
comma
id|_null_
comma
id|_REGI_
comma
id|_NONE_
comma
id|_null_
comma
id|_null_
comma
id|_REGIi
comma
id|_null_
comma
id|_REGIp
comma
id|_null_
comma
id|_REGI_
comma
id|_NONE_
comma
id|_null_
comma
id|_null_
comma
id|_REGIi
comma
id|_null_
comma
id|_REGIp
comma
id|_null_
)brace
suffix:semicolon
macro_line|#endif NO_UNDOC_CODE
multiline_comment|/* Be careful when using any of these global variables...&n;   they might change if swapping is triggered */
DECL|variable|FPU_rm
r_int
r_char
id|FPU_rm
suffix:semicolon
DECL|variable|FPU_st0_tag
r_char
id|FPU_st0_tag
suffix:semicolon
DECL|variable|FPU_st0_ptr
id|FPU_REG
op_star
id|FPU_st0_ptr
suffix:semicolon
multiline_comment|/* ######## To be shifted */
DECL|variable|FPU_entry_op_cs
r_int
r_int
id|FPU_entry_op_cs
suffix:semicolon
DECL|variable|FPU_data_selector
r_int
r_int
id|FPU_data_selector
suffix:semicolon
macro_line|#ifdef PARANOID
DECL|variable|emulating
r_char
id|emulating
op_assign
l_int|0
suffix:semicolon
macro_line|#endif PARANOID
r_static
r_int
id|valid_prefix
c_func
(paren
r_int
r_char
op_star
id|Byte
comma
r_int
r_char
op_star
op_star
id|fpu_eip
comma
id|overrides
op_star
id|override
)paren
suffix:semicolon
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
r_int
r_char
id|FPU_modrm
comma
id|byte1
suffix:semicolon
id|fpu_addr_modes
id|addr_modes
suffix:semicolon
r_int
id|unmasked
suffix:semicolon
macro_line|#ifdef PARANOID
r_if
c_cond
(paren
id|emulating
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ERROR: wm-FPU-emu is not RE-ENTRANT!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|RE_ENTRANT_CHECK_ON
suffix:semicolon
macro_line|#endif PARANOID
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;used_math
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
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Make sure that the registers are compatible&n;&t;     with the assumptions of the emulator. */
id|regs
(braket
id|i
)braket
dot
id|exp
op_assign
l_int|0
suffix:semicolon
id|regs
(braket
id|i
)braket
dot
id|sigh
op_assign
l_int|0x80000000
suffix:semicolon
)brace
id|finit
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|1
suffix:semicolon
)brace
id|SETUP_DATA_AREA
c_func
(paren
id|arg
)paren
suffix:semicolon
id|addr_modes.vm86
op_assign
(paren
id|FPU_EFLAGS
op_amp
l_int|0x00020000
)paren
op_ne
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|addr_modes.vm86
)paren
id|FPU_EIP
op_add_assign
id|FPU_CS
op_lshift
l_int|4
suffix:semicolon
id|FPU_ORIG_EIP
op_assign
id|FPU_EIP
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr_modes.vm86
)paren
(brace
multiline_comment|/* user code space? */
r_if
c_cond
(paren
id|FPU_CS
op_eq
id|KERNEL_CS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;math_emulate: %04x:%08lx&bslash;n&quot;
comma
id|FPU_CS
comma
id|FPU_EIP
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Math emulation needed in kernel&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* We cannot handle multiple segments yet */
r_if
c_cond
(paren
id|FPU_CS
op_ne
id|USER_CS
op_logical_or
id|FPU_DS
op_ne
id|USER_DS
)paren
(brace
id|math_abort
c_func
(paren
id|FPU_info
comma
id|SIGILL
)paren
suffix:semicolon
)brace
)brace
id|FPU_lookahead
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_PTRACED
)paren
id|FPU_lookahead
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|valid_prefix
c_func
(paren
op_amp
id|byte1
comma
(paren
r_int
r_char
op_star
op_star
)paren
op_amp
id|FPU_EIP
comma
op_amp
id|addr_modes.override
)paren
)paren
(brace
id|RE_ENTRANT_CHECK_OFF
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;FPU emulator: Unknown prefix byte 0x%02x, probably due to&bslash;n&quot;
l_string|&quot;FPU emulator: self-modifying code! (emulation impossible)&bslash;n&quot;
comma
id|byte1
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
suffix:semicolon
id|EXCEPTION
c_func
(paren
id|EX_INTERNAL
op_or
l_int|0x126
)paren
suffix:semicolon
id|math_abort
c_func
(paren
id|FPU_info
comma
id|SIGILL
)paren
suffix:semicolon
)brace
id|do_another_FPU_instruction
suffix:colon
id|FPU_EIP
op_increment
suffix:semicolon
multiline_comment|/* We have fetched the prefix and first code bytes. */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* It would be more logical to do this only in get_address(),&n;     but although it is supposed to be undefined for many fpu&n;     instructions, an 80486 behaves as if this were done here: */
id|FPU_data_selector
op_assign
id|FPU_DS
suffix:semicolon
macro_line|#endif PECULIAR_486
r_if
c_cond
(paren
(paren
id|byte1
op_amp
l_int|0xf8
)paren
op_ne
l_int|0xd8
)paren
(brace
r_if
c_cond
(paren
id|byte1
op_eq
id|FWAIT_OPCODE
)paren
(brace
r_if
c_cond
(paren
id|partial_status
op_amp
id|SW_Summary
)paren
r_goto
id|do_the_FPU_interrupt
suffix:semicolon
r_else
r_goto
id|FPU_fwait_done
suffix:semicolon
)brace
macro_line|#ifdef PARANOID
id|EXCEPTION
c_func
(paren
id|EX_INTERNAL
op_or
l_int|0x128
)paren
suffix:semicolon
id|math_abort
c_func
(paren
id|FPU_info
comma
id|SIGILL
)paren
suffix:semicolon
macro_line|#endif PARANOID
)brace
id|RE_ENTRANT_CHECK_OFF
suffix:semicolon
id|FPU_code_verify_area
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|FPU_modrm
op_assign
id|get_fs_byte
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|FPU_EIP
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
suffix:semicolon
id|FPU_EIP
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|partial_status
op_amp
id|SW_Summary
)paren
(brace
multiline_comment|/* Ignore the error for now if the current instruction is a no-wait&n;&t; control instruction */
multiline_comment|/* The 80486 manual contradicts itself on this topic,&n;&t; but a real 80486 uses the following instructions:&n;&t; fninit, fnstenv, fnsave, fnstsw, fnstenv, fnclex.&n;       */
r_int
r_int
id|code
op_assign
(paren
id|FPU_modrm
op_lshift
l_int|8
)paren
op_or
id|byte1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
(paren
(paren
id|code
op_amp
l_int|0xf803
)paren
op_eq
l_int|0xe003
)paren
op_logical_or
multiline_comment|/* fnclex, fninit, fnstsw */
(paren
(paren
(paren
id|code
op_amp
l_int|0x3003
)paren
op_eq
l_int|0x3001
)paren
op_logical_and
multiline_comment|/* fnsave, fnstcw, fnstenv,&n;&t;&t;&t;&t;&t;&t;     fnstsw */
(paren
(paren
id|code
op_amp
l_int|0xc000
)paren
op_ne
l_int|0xc000
)paren
)paren
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;   *  We need to simulate the action of the kernel to FPU&n;&t;   *  interrupts here.&n;&t;   *  Currently, the &quot;real FPU&quot; part of the kernel (0.99.10)&n;&t;   *  clears the exception flags, sets the registers to empty,&n;&t;   *  and passes information back to the interrupted process&n;&t;   *  via the cs selector and operand selector, so we do the same.&n;&t;   */
id|do_the_FPU_interrupt
suffix:colon
id|cs_selector
op_and_assign
l_int|0xffff0000
suffix:semicolon
id|cs_selector
op_or_assign
id|status_word
c_func
(paren
)paren
suffix:semicolon
id|operand_selector
op_assign
id|tag_word
c_func
(paren
)paren
suffix:semicolon
id|partial_status
op_assign
l_int|0
suffix:semicolon
id|top
op_assign
l_int|0
suffix:semicolon
(brace
r_int
id|r
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
l_int|0
suffix:semicolon
id|r
OL
l_int|8
suffix:semicolon
id|r
op_increment
)paren
(brace
id|regs
(braket
id|r
)braket
dot
id|tag
op_assign
id|TW_Empty
suffix:semicolon
)brace
)brace
id|RE_ENTRANT_CHECK_OFF
suffix:semicolon
id|current-&gt;tss.trap_no
op_assign
l_int|16
suffix:semicolon
id|current-&gt;tss.error_code
op_assign
l_int|0
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
r_return
suffix:semicolon
)brace
)brace
id|FPU_entry_eip
op_assign
id|FPU_ORIG_EIP
suffix:semicolon
id|FPU_entry_op_cs
op_assign
(paren
id|byte1
op_lshift
l_int|24
)paren
op_or
(paren
id|FPU_modrm
op_lshift
l_int|16
)paren
op_or
(paren
id|FPU_CS
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|FPU_rm
op_assign
id|FPU_modrm
op_amp
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|FPU_modrm
OL
l_int|0300
)paren
(brace
multiline_comment|/* All of these instructions use the mod/rm byte to get a data address */
r_if
c_cond
(paren
id|addr_modes.vm86
op_xor
(paren
id|addr_modes.override.address_size
op_eq
id|ADDR_SIZE_PREFIX
)paren
)paren
id|get_address_16
c_func
(paren
id|FPU_modrm
comma
op_amp
id|FPU_EIP
comma
id|addr_modes
)paren
suffix:semicolon
r_else
id|get_address
c_func
(paren
id|FPU_modrm
comma
op_amp
id|FPU_EIP
comma
id|addr_modes
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|byte1
op_amp
l_int|1
)paren
)paren
(brace
r_int
r_int
id|status1
op_assign
id|partial_status
suffix:semicolon
id|FPU_st0_ptr
op_assign
op_amp
id|st
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|FPU_st0_tag
op_assign
id|FPU_st0_ptr-&gt;tag
suffix:semicolon
multiline_comment|/* Stack underflow has priority */
r_if
c_cond
(paren
id|NOT_EMPTY_0
)paren
(brace
id|unmasked
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Do this here to stop compiler warnings. */
r_switch
c_cond
(paren
(paren
id|byte1
op_rshift
l_int|1
)paren
op_amp
l_int|3
)paren
(brace
r_case
l_int|0
suffix:colon
id|unmasked
op_assign
id|reg_load_single
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|reg_load_int32
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|unmasked
op_assign
id|reg_load_double
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|reg_load_int16
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* No more access to user memory, it is safe&n;&t;&t; to use static data now */
id|FPU_st0_ptr
op_assign
op_amp
id|st
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|FPU_st0_tag
op_assign
id|FPU_st0_ptr-&gt;tag
suffix:semicolon
multiline_comment|/* NaN operands have the next priority. */
multiline_comment|/* We have to delay looking at st(0) until after&n;&t;&t; loading the data, because that data might contain an SNaN */
r_if
c_cond
(paren
(paren
id|FPU_st0_tag
op_eq
id|TW_NaN
)paren
op_logical_or
(paren
id|FPU_loaded_data.tag
op_eq
id|TW_NaN
)paren
)paren
(brace
multiline_comment|/* Restore the status word; we might have loaded a&n;&t;&t;     denormal. */
id|partial_status
op_assign
id|status1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|FPU_modrm
op_amp
l_int|0x30
)paren
op_eq
l_int|0x10
)paren
(brace
multiline_comment|/* fcom or fcomp */
id|EXCEPTION
c_func
(paren
id|EX_Invalid
)paren
suffix:semicolon
id|setcc
c_func
(paren
id|SW_C3
op_or
id|SW_C2
op_or
id|SW_C0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|FPU_modrm
op_amp
l_int|0x08
)paren
op_logical_and
(paren
id|control_word
op_amp
id|CW_Invalid
)paren
)paren
id|pop
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* fcomp, masked, so we pop. */
)brace
r_else
(brace
macro_line|#ifdef PECULIAR_486
multiline_comment|/* This is not really needed, but gives behaviour&n;&t;&t;&t; identical to an 80486 */
r_if
c_cond
(paren
(paren
id|FPU_modrm
op_amp
l_int|0x28
)paren
op_eq
l_int|0x20
)paren
multiline_comment|/* fdiv or fsub */
id|real_2op_NaN
c_func
(paren
op_amp
id|FPU_loaded_data
comma
id|FPU_st0_ptr
comma
id|FPU_st0_ptr
)paren
suffix:semicolon
r_else
macro_line|#endif PECULIAR_486
multiline_comment|/* fadd, fdivr, fmul, or fsubr */
id|real_2op_NaN
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|FPU_loaded_data
comma
id|FPU_st0_ptr
)paren
suffix:semicolon
)brace
r_goto
id|reg_mem_instr_done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unmasked
op_logical_and
op_logical_neg
(paren
(paren
id|FPU_modrm
op_amp
l_int|0x30
)paren
op_eq
l_int|0x10
)paren
)paren
(brace
multiline_comment|/* Is not a comparison instruction. */
r_if
c_cond
(paren
(paren
id|FPU_modrm
op_amp
l_int|0x38
)paren
op_eq
l_int|0x38
)paren
(brace
multiline_comment|/* fdivr */
r_if
c_cond
(paren
(paren
id|FPU_st0_tag
op_eq
id|TW_Zero
)paren
op_logical_and
(paren
id|FPU_loaded_data.tag
op_eq
id|TW_Valid
)paren
)paren
(brace
r_if
c_cond
(paren
id|divide_by_zero
c_func
(paren
id|FPU_loaded_data.sign
comma
id|FPU_st0_ptr
)paren
)paren
(brace
multiline_comment|/* We use the fact here that the unmasked&n;&t;&t;&t;&t; exception in the loaded data was for a&n;&t;&t;&t;&t; denormal operand */
multiline_comment|/* Restore the state of the denormal op bit */
id|partial_status
op_and_assign
op_complement
id|SW_Denorm_Op
suffix:semicolon
id|partial_status
op_or_assign
id|status1
op_amp
id|SW_Denorm_Op
suffix:semicolon
)brace
)brace
)brace
r_goto
id|reg_mem_instr_done
suffix:semicolon
)brace
r_switch
c_cond
(paren
(paren
id|FPU_modrm
op_rshift
l_int|3
)paren
op_amp
l_int|7
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* fadd */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|reg_add
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|FPU_loaded_data
comma
id|FPU_st0_ptr
comma
id|control_word
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* fmul */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|reg_mul
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|FPU_loaded_data
comma
id|FPU_st0_ptr
comma
id|control_word
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* fcom */
id|compare_st_data
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* fcomp */
r_if
c_cond
(paren
op_logical_neg
id|compare_st_data
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|unmasked
)paren
id|pop
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* fsub */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|reg_sub
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|FPU_loaded_data
comma
id|FPU_st0_ptr
comma
id|control_word
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* fsubr */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|reg_sub
c_func
(paren
op_amp
id|FPU_loaded_data
comma
id|FPU_st0_ptr
comma
id|FPU_st0_ptr
comma
id|control_word
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
multiline_comment|/* fdiv */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|reg_div
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|FPU_loaded_data
comma
id|FPU_st0_ptr
comma
id|control_word
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/* fdivr */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FPU_st0_tag
op_eq
id|TW_Zero
)paren
id|partial_status
op_assign
id|status1
suffix:semicolon
multiline_comment|/* Undo any denorm tag,&n;&t;&t;&t;&t;&t;       zero-divide has priority. */
id|reg_div
c_func
(paren
op_amp
id|FPU_loaded_data
comma
id|FPU_st0_ptr
comma
id|FPU_st0_ptr
comma
id|control_word
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|FPU_modrm
op_amp
l_int|0x30
)paren
op_eq
l_int|0x10
)paren
(brace
multiline_comment|/* The instruction is fcom or fcomp */
id|EXCEPTION
c_func
(paren
id|EX_StackUnder
)paren
suffix:semicolon
id|setcc
c_func
(paren
id|SW_C3
op_or
id|SW_C2
op_or
id|SW_C0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|FPU_modrm
op_amp
l_int|0x08
)paren
op_logical_and
(paren
id|control_word
op_amp
id|CW_Invalid
)paren
)paren
id|pop
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* fcomp */
)brace
r_else
id|stack_underflow
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|load_store_instr
c_func
(paren
(paren
(paren
id|FPU_modrm
op_amp
l_int|0x38
)paren
op_or
(paren
id|byte1
op_amp
l_int|6
)paren
)paren
op_rshift
l_int|1
comma
id|addr_modes
)paren
suffix:semicolon
)brace
id|reg_mem_instr_done
suffix:colon
macro_line|#ifndef PECULIAR_486
op_star
(paren
r_int
r_int
op_star
)paren
op_amp
id|operand_selector
op_assign
id|FPU_data_selector
suffix:semicolon
macro_line|#endif PECULIAR_486
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* None of these instructions access user memory */
r_int
r_char
id|instr_index
op_assign
(paren
id|FPU_modrm
op_amp
l_int|0x38
)paren
op_or
(paren
id|byte1
op_amp
l_int|7
)paren
suffix:semicolon
macro_line|#ifdef PECULIAR_486
multiline_comment|/* This is supposed to be undefined, but a real 80486 seems&n;&t; to do this: */
id|FPU_data_address
op_assign
l_int|0
suffix:semicolon
macro_line|#endif PECULIAR_486
id|FPU_st0_ptr
op_assign
op_amp
id|st
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|FPU_st0_tag
op_assign
id|FPU_st0_ptr-&gt;tag
suffix:semicolon
r_switch
c_cond
(paren
id|type_table
(braket
(paren
r_int
)paren
id|instr_index
)braket
)paren
(brace
r_case
id|_NONE_
suffix:colon
multiline_comment|/* also _REGIc: _REGIn */
r_break
suffix:semicolon
r_case
id|_REG0_
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|NOT_EMPTY_0
)paren
(brace
id|stack_underflow
c_func
(paren
)paren
suffix:semicolon
r_goto
id|FPU_instruction_done
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|_REGIi
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|NOT_EMPTY_0
op_logical_or
op_logical_neg
id|NOT_EMPTY
c_func
(paren
id|FPU_rm
)paren
)paren
(brace
id|stack_underflow_i
c_func
(paren
id|FPU_rm
)paren
suffix:semicolon
r_goto
id|FPU_instruction_done
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|_REGIp
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|NOT_EMPTY_0
op_logical_or
op_logical_neg
id|NOT_EMPTY
c_func
(paren
id|FPU_rm
)paren
)paren
(brace
id|stack_underflow_pop
c_func
(paren
id|FPU_rm
)paren
suffix:semicolon
r_goto
id|FPU_instruction_done
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|_REGI_
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|NOT_EMPTY_0
op_logical_or
op_logical_neg
id|NOT_EMPTY
c_func
(paren
id|FPU_rm
)paren
)paren
(brace
id|stack_underflow
c_func
(paren
)paren
suffix:semicolon
r_goto
id|FPU_instruction_done
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|_PUSH_
suffix:colon
multiline_comment|/* Only used by the fld st(i) instruction */
r_break
suffix:semicolon
r_case
id|_null_
suffix:colon
id|FPU_illegal
c_func
(paren
)paren
suffix:semicolon
r_goto
id|FPU_instruction_done
suffix:semicolon
r_default
suffix:colon
id|EXCEPTION
c_func
(paren
id|EX_INTERNAL
op_or
l_int|0x111
)paren
suffix:semicolon
r_goto
id|FPU_instruction_done
suffix:semicolon
)brace
(paren
op_star
id|st_instr_table
(braket
(paren
r_int
)paren
id|instr_index
)braket
)paren
(paren
)paren
suffix:semicolon
)brace
id|FPU_instruction_done
suffix:colon
id|ip_offset
op_assign
id|FPU_entry_eip
suffix:semicolon
id|cs_selector
op_assign
id|FPU_entry_op_cs
suffix:semicolon
id|data_operand_offset
op_assign
(paren
r_int
r_int
)paren
id|FPU_data_address
suffix:semicolon
macro_line|#ifdef PECULIAR_486
op_star
(paren
r_int
r_int
op_star
)paren
op_amp
id|operand_selector
op_assign
id|FPU_data_selector
suffix:semicolon
macro_line|#endif PECULIAR_486
id|FPU_fwait_done
suffix:colon
macro_line|#ifdef DEBUG
id|RE_ENTRANT_CHECK_OFF
suffix:semicolon
id|emu_printall
c_func
(paren
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
suffix:semicolon
macro_line|#endif DEBUG
r_if
c_cond
(paren
id|FPU_lookahead
op_logical_and
op_logical_neg
id|need_resched
)paren
(brace
id|FPU_ORIG_EIP
op_assign
id|FPU_EIP
suffix:semicolon
r_if
c_cond
(paren
id|valid_prefix
c_func
(paren
op_amp
id|byte1
comma
(paren
r_int
r_char
op_star
op_star
)paren
op_amp
id|FPU_EIP
comma
op_amp
id|addr_modes.override
)paren
)paren
r_goto
id|do_another_FPU_instruction
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr_modes.vm86
)paren
id|FPU_EIP
op_sub_assign
id|FPU_CS
op_lshift
l_int|4
suffix:semicolon
id|RE_ENTRANT_CHECK_OFF
suffix:semicolon
)brace
multiline_comment|/* Support for prefix bytes is not yet complete. To properly handle&n;   all prefix bytes, further changes are needed in the emulator code&n;   which accesses user address space. Access to separate segments is&n;   important for msdos emulation. */
DECL|function|valid_prefix
r_static
r_int
id|valid_prefix
c_func
(paren
r_int
r_char
op_star
id|Byte
comma
r_int
r_char
op_star
op_star
id|fpu_eip
comma
id|overrides
op_star
id|override
)paren
(brace
r_int
r_char
id|byte
suffix:semicolon
r_int
r_char
op_star
id|ip
op_assign
op_star
id|fpu_eip
suffix:semicolon
op_star
id|override
op_assign
(paren
id|overrides
)paren
(brace
l_int|0
comma
l_int|0
comma
id|PREFIX_DS
)brace
suffix:semicolon
multiline_comment|/* defaults */
id|RE_ENTRANT_CHECK_OFF
suffix:semicolon
id|FPU_code_verify_area
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|byte
op_assign
id|get_fs_byte
c_func
(paren
id|ip
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_switch
c_cond
(paren
id|byte
)paren
(brace
r_case
id|ADDR_SIZE_PREFIX
suffix:colon
id|override-&gt;address_size
op_assign
id|ADDR_SIZE_PREFIX
suffix:semicolon
r_goto
id|do_next_byte
suffix:semicolon
r_case
id|OP_SIZE_PREFIX
suffix:colon
id|override-&gt;operand_size
op_assign
id|OP_SIZE_PREFIX
suffix:semicolon
r_goto
id|do_next_byte
suffix:semicolon
r_case
id|PREFIX_CS
suffix:colon
id|override-&gt;segment
op_assign
id|PREFIX_CS
suffix:semicolon
r_goto
id|do_next_byte
suffix:semicolon
r_case
id|PREFIX_ES
suffix:colon
id|override-&gt;segment
op_assign
id|PREFIX_ES
suffix:semicolon
r_goto
id|do_next_byte
suffix:semicolon
r_case
id|PREFIX_SS
suffix:colon
id|override-&gt;segment
op_assign
id|PREFIX_SS
suffix:semicolon
r_goto
id|do_next_byte
suffix:semicolon
r_case
id|PREFIX_FS
suffix:colon
id|override-&gt;segment
op_assign
id|PREFIX_FS
suffix:semicolon
r_goto
id|do_next_byte
suffix:semicolon
r_case
id|PREFIX_GS
suffix:colon
id|override-&gt;segment
op_assign
id|PREFIX_GS
suffix:semicolon
r_goto
id|do_next_byte
suffix:semicolon
r_case
id|PREFIX_DS
suffix:colon
multiline_comment|/* Redundant unless preceded by another override. */
id|override-&gt;segment
op_assign
id|PREFIX_DS
suffix:semicolon
multiline_comment|/* lock is not a valid prefix for FPU instructions,&n;   let the cpu handle it to generate a SIGILL. */
multiline_comment|/*&t;case PREFIX_LOCK: */
multiline_comment|/* rep.. prefixes have no meaning for FPU instructions */
r_case
id|PREFIX_REPE
suffix:colon
r_case
id|PREFIX_REPNE
suffix:colon
id|do_next_byte
suffix:colon
id|ip
op_increment
suffix:semicolon
id|RE_ENTRANT_CHECK_OFF
suffix:semicolon
id|FPU_code_verify_area
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|byte
op_assign
id|get_fs_byte
c_func
(paren
id|ip
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FWAIT_OPCODE
suffix:colon
op_star
id|Byte
op_assign
id|byte
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
(paren
id|byte
op_amp
l_int|0xf8
)paren
op_eq
l_int|0xd8
)paren
(brace
op_star
id|Byte
op_assign
id|byte
suffix:semicolon
op_star
id|fpu_eip
op_assign
id|ip
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Not a valid sequence of prefix bytes followed by&n;&t;&t; an FPU instruction. */
op_star
id|Byte
op_assign
id|byte
suffix:semicolon
multiline_comment|/* Needed for error message. */
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|__math_abort
r_void
id|__math_abort
c_func
(paren
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|signal
)paren
(brace
id|FPU_EIP
op_assign
id|FPU_ORIG_EIP
suffix:semicolon
id|current-&gt;tss.trap_no
op_assign
l_int|16
suffix:semicolon
id|current-&gt;tss.error_code
op_assign
l_int|0
suffix:semicolon
id|send_sig
c_func
(paren
id|signal
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_OFF
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %0,%%esp ; ret&quot;
suffix:colon
suffix:colon
l_string|&quot;g&quot;
(paren
(paren
(paren
r_int
)paren
id|info
)paren
op_minus
l_int|4
)paren
)paren
suffix:semicolon
macro_line|#ifdef PARANOID
id|printk
c_func
(paren
l_string|&quot;ERROR: wm-FPU-emu math_abort failed!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif PARANOID
)brace
eof
