multiline_comment|/*---------------------------------------------------------------------------+&n; |  fpu_entry.c                                                              |&n; |                                                                           |&n; | The entry function for wm-FPU-emu                                         |&n; |                                                                           |&n; | Copyright (C) 1992    W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail apm233m@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; | See the files &quot;README&quot; and &quot;COPYING&quot; for further copyright and warranty   |&n; | information.                                                              |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
multiline_comment|/*---------------------------------------------------------------------------+&n; | Note:                                                                     |&n; |    The file contains code which accesses user memory.                     |&n; |    Emulator static data may change when user memory is accessed, due to   |&n; |    other processes using the emulator while swapping is in progress.      |&n; +---------------------------------------------------------------------------*/
multiline_comment|/*---------------------------------------------------------------------------+&n; | math_emulate() is the sole entry point for wm-FPU-emu                     |&n; +---------------------------------------------------------------------------*/
macro_line|#ifdef KERNEL_MATH_EMULATION
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &quot;fpu_system.h&quot;
macro_line|#include &quot;fpu_emu.h&quot;
macro_line|#include &quot;exception.h&quot;
macro_line|#include &lt;asm/segment.h&gt;
DECL|macro|__BAD__
mdefine_line|#define __BAD__ Un_impl   /* Not implemented */
DECL|variable|st_instr_table
r_static
id|FUNC
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
DECL|variable|type_table
r_static
r_int
r_char
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
id|_REGI_
comma
id|_REGi_
comma
id|_REGI_
comma
id|_null_
comma
id|_REGI_
comma
id|_REGI_
comma
id|_null_
comma
id|_null_
comma
id|_REGI_
comma
id|_null_
comma
id|_REGI_
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
id|_null_
comma
id|_REG0_
comma
id|_null_
comma
id|_null_
comma
id|_REGI_
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
id|_REGI_
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
id|_REGI_
comma
id|_REGI_
comma
id|_REGI_
comma
id|_NONE_
comma
id|_REGI_
comma
id|_NONE_
comma
id|_REGI_
comma
id|_null_
comma
id|_REGI_
comma
id|_REGI_
comma
id|_REGI_
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
id|_REGI_
comma
id|_null_
comma
id|_REGI_
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
id|_REGI_
comma
id|_null_
comma
id|_REGI_
comma
id|_null_
)brace
suffix:semicolon
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
macro_line|#ifdef PARANOID
DECL|variable|emulating
r_char
id|emulating
op_assign
l_int|0
suffix:semicolon
macro_line|#endif PARANOID
DECL|macro|bswapw
mdefine_line|#define bswapw(x) __asm__(&quot;xchgb %%al,%%ah&quot;:&quot;=a&quot; (x):&quot;0&quot; ((short)x))
DECL|function|math_emulate
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
suffix:semicolon
r_int
r_int
id|code
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
l_string|&quot;ERROR: wm-FPU-emu is not RE-ENTRANT!&bslash;r&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|RE_ENTRANT_CHECK_ON
macro_line|#endif PARANOID
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;used_math
)paren
(brace
id|finit
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|1
suffix:semicolon
id|control_word
op_assign
l_int|0x037f
suffix:semicolon
id|status_word
op_assign
l_int|0x0000
suffix:semicolon
)brace
id|FPU_info
op_assign
(paren
r_struct
id|info
op_star
)paren
op_amp
id|arg
suffix:semicolon
multiline_comment|/* We cannot handle emulation in v86-mode */
r_if
c_cond
(paren
id|FPU_EFLAGS
op_amp
l_int|0x00020000
)paren
id|math_abort
c_func
(paren
id|FPU_info
comma
id|SIGILL
)paren
suffix:semicolon
multiline_comment|/* 0x000f means user code space */
r_if
c_cond
(paren
id|FPU_CS
op_ne
l_int|0x000f
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;math_emulate: %04x:%08x&bslash;n&bslash;r&quot;
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
id|do_another
suffix:colon
id|FPU_entry_eip
op_assign
id|FPU_ORIG_EIP
op_assign
id|FPU_EIP
suffix:semicolon
id|RE_ENTRANT_CHECK_OFF
id|code
op_assign
id|get_fs_word
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
r_if
c_cond
(paren
(paren
id|code
op_amp
l_int|0xff
)paren
op_eq
l_int|0x66
)paren
(brace
id|FPU_EIP
op_increment
suffix:semicolon
id|RE_ENTRANT_CHECK_OFF
id|code
op_assign
id|get_fs_word
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
)brace
id|FPU_EIP
op_add_assign
l_int|2
suffix:semicolon
id|FPU_modrm
op_assign
id|code
op_rshift
l_int|8
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
id|get_address
c_func
(paren
id|FPU_modrm
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|code
op_amp
l_int|1
)paren
)paren
(brace
r_switch
c_cond
(paren
(paren
id|code
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
multiline_comment|/* No more access to user memory, it is safe&n;&t;     to use static data now */
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
r_if
c_cond
(paren
id|NOT_EMPTY_0
)paren
(brace
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
id|reg_add
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
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* fmul */
id|reg_mul
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
id|compare_st_data
c_func
(paren
)paren
suffix:semicolon
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
id|reg_sub
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
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* fsubr */
id|reg_sub
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
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
multiline_comment|/* fdiv */
id|reg_div
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
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/* fdivr */
id|reg_div
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
r_break
suffix:semicolon
)brace
)brace
r_else
id|stack_underflow
c_func
(paren
)paren
suffix:semicolon
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
id|code
op_amp
l_int|6
)paren
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
id|data_operand_offset
op_assign
(paren
r_int
r_int
)paren
id|FPU_data_address
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
id|code
op_amp
l_int|7
)paren
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
id|instruction_done
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
id|instruction_done
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
id|Un_impl
c_func
(paren
)paren
suffix:semicolon
r_goto
id|instruction_done
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
id|instruction_done
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
id|instruction_done
suffix:colon
id|ip_offset
op_assign
id|FPU_entry_eip
suffix:semicolon
id|bswapw
c_func
(paren
id|code
)paren
suffix:semicolon
op_star
(paren
l_int|1
op_plus
(paren
r_int
r_int
op_star
)paren
op_amp
id|cs_selector
)paren
op_assign
id|code
op_amp
l_int|0x7ff
suffix:semicolon
r_if
c_cond
(paren
id|FPU_lookahead
op_logical_and
op_logical_neg
id|need_resched
)paren
(brace
r_int
r_char
id|next
suffix:semicolon
id|skip_fwait
suffix:colon
id|RE_ENTRANT_CHECK_OFF
id|next
op_assign
id|get_fs_byte
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|FPU_EIP
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
id|test_for_fp
suffix:colon
r_if
c_cond
(paren
(paren
id|next
op_amp
l_int|0xf8
)paren
op_eq
l_int|0xd8
)paren
(brace
r_goto
id|do_another
suffix:semicolon
)brace
r_if
c_cond
(paren
id|next
op_eq
l_int|0x9b
)paren
multiline_comment|/* fwait */
(brace
id|FPU_EIP
op_increment
suffix:semicolon
r_goto
id|skip_fwait
suffix:semicolon
)brace
r_if
c_cond
(paren
id|next
op_eq
l_int|0x66
)paren
multiline_comment|/* size prefix */
(brace
id|RE_ENTRANT_CHECK_OFF
id|next
op_assign
id|get_fs_byte
c_func
(paren
(paren
r_int
r_char
op_star
)paren
(paren
id|FPU_EIP
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
r_if
c_cond
(paren
(paren
id|next
op_amp
l_int|0xf8
)paren
op_eq
l_int|0xd8
)paren
r_goto
id|test_for_fp
suffix:semicolon
)brace
)brace
id|RE_ENTRANT_CHECK_OFF
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
id|__asm__
c_func
(paren
l_string|&quot;movl %0,%%esp ; ret&quot;
op_scope_resolution
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
)brace
macro_line|#else /* no math emulation */
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
DECL|function|math_emulate
r_void
id|math_emulate
c_func
(paren
r_int
id|arg
)paren
(brace
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
macro_line|#endif /* KERNEL_MATH_EMULATION */
eof