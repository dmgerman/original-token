multiline_comment|/*---------------------------------------------------------------------------+&n; |  load_store.c                                                             |&n; |                                                                           |&n; | This file contains most of the code to interpret the FPU instructions     |&n; | which load and store from user memory.                                    |&n; |                                                                           |&n; | Copyright (C) 1992,1993                                                   |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail apm233m@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
multiline_comment|/*---------------------------------------------------------------------------+&n; | Note:                                                                     |&n; |    The file contains code which accesses user memory.                     |&n; |    Emulator static data may change when user memory is accessed, due to   |&n; |    other processes using the emulator while swapping is in progress.      |&n; +---------------------------------------------------------------------------*/
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &quot;fpu_system.h&quot;
macro_line|#include &quot;exception.h&quot;
macro_line|#include &quot;fpu_emu.h&quot;
macro_line|#include &quot;status_w.h&quot;
macro_line|#include &quot;control_w.h&quot;
DECL|macro|_NONE_
mdefine_line|#define _NONE_ 0   /* FPU_st0_ptr etc not needed */
DECL|macro|_REG0_
mdefine_line|#define _REG0_ 1   /* Will be storing st(0) */
DECL|macro|_PUSH_
mdefine_line|#define _PUSH_ 3   /* Need to check for space to push onto stack */
DECL|macro|_null_
mdefine_line|#define _null_ 4   /* Function illegal or not implemented */
DECL|macro|pop_0
mdefine_line|#define pop_0()&t;{ pop_ptr-&gt;tag = TW_Empty; top++; }
DECL|variable|type_table
r_static
r_int
r_char
id|type_table
(braket
l_int|32
)braket
op_assign
(brace
id|_PUSH_
comma
id|_PUSH_
comma
id|_PUSH_
comma
id|_PUSH_
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
id|_REG0_
comma
id|_REG0_
comma
id|_REG0_
comma
id|_REG0_
comma
id|_REG0_
comma
id|_REG0_
comma
id|_REG0_
comma
id|_NONE_
comma
id|_null_
comma
id|_NONE_
comma
id|_PUSH_
comma
id|_NONE_
comma
id|_PUSH_
comma
id|_null_
comma
id|_PUSH_
comma
id|_NONE_
comma
id|_null_
comma
id|_NONE_
comma
id|_REG0_
comma
id|_NONE_
comma
id|_REG0_
comma
id|_NONE_
comma
id|_REG0_
)brace
suffix:semicolon
DECL|function|load_store_instr
r_void
id|load_store_instr
c_func
(paren
r_char
id|type
)paren
(brace
id|FPU_REG
op_star
id|pop_ptr
suffix:semicolon
multiline_comment|/* We need a version of FPU_st0_ptr which won&squot;t&n;&t;&t;&t;change if the emulator is re-entered. */
id|pop_ptr
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Initialized just to stop compiler warnings. */
r_switch
c_cond
(paren
id|type_table
(braket
(paren
r_int
)paren
(paren
r_int
)paren
id|type
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
id|pop_ptr
op_assign
op_amp
id|st
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Some of these instructions pop after&n;&t;&t;&t;&t; storing */
id|FPU_st0_ptr
op_assign
id|pop_ptr
suffix:semicolon
multiline_comment|/* Set the global variables. */
id|FPU_st0_tag
op_assign
id|FPU_st0_ptr-&gt;tag
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_PUSH_
suffix:colon
(brace
id|pop_ptr
op_assign
op_amp
id|st
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pop_ptr-&gt;tag
op_ne
id|TW_Empty
)paren
(brace
id|stack_overflow
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|top
op_decrement
suffix:semicolon
)brace
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
r_return
suffix:semicolon
macro_line|#ifdef PARANOID
r_default
suffix:colon
id|EXCEPTION
c_func
(paren
id|EX_INTERNAL
)paren
suffix:semicolon
r_return
suffix:semicolon
macro_line|#endif PARANOID
)brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
l_int|000
suffix:colon
multiline_comment|/* fld m32real */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_load_single
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|FPU_loaded_data.tag
op_eq
id|TW_NaN
)paren
op_logical_and
id|real_2op_NaN
c_func
(paren
op_amp
id|FPU_loaded_data
comma
op_amp
id|FPU_loaded_data
comma
op_amp
id|FPU_loaded_data
)paren
)paren
(brace
id|top
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|reg_move
c_func
(paren
op_amp
id|FPU_loaded_data
comma
id|pop_ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|001
suffix:colon
multiline_comment|/* fild m32int */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_load_int32
c_func
(paren
)paren
suffix:semicolon
id|reg_move
c_func
(paren
op_amp
id|FPU_loaded_data
comma
id|pop_ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|002
suffix:colon
multiline_comment|/* fld m64real */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_load_double
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|FPU_loaded_data.tag
op_eq
id|TW_NaN
)paren
op_logical_and
id|real_2op_NaN
c_func
(paren
op_amp
id|FPU_loaded_data
comma
op_amp
id|FPU_loaded_data
comma
op_amp
id|FPU_loaded_data
)paren
)paren
(brace
id|top
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|reg_move
c_func
(paren
op_amp
id|FPU_loaded_data
comma
id|pop_ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|003
suffix:colon
multiline_comment|/* fild m16int */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_load_int16
c_func
(paren
)paren
suffix:semicolon
id|reg_move
c_func
(paren
op_amp
id|FPU_loaded_data
comma
id|pop_ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|010
suffix:colon
multiline_comment|/* fst m32real */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_store_single
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|011
suffix:colon
multiline_comment|/* fist m32int */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_store_int32
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|012
suffix:colon
multiline_comment|/* fst m64real */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_store_double
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|013
suffix:colon
multiline_comment|/* fist m16int */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_store_int16
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|014
suffix:colon
multiline_comment|/* fstp m32real */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
r_if
c_cond
(paren
id|reg_store_single
c_func
(paren
)paren
)paren
id|pop_0
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* pop only if the number was actually stored&n;&t;&t; (see the 80486 manual p16-28) */
r_break
suffix:semicolon
r_case
l_int|015
suffix:colon
multiline_comment|/* fistp m32int */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
r_if
c_cond
(paren
id|reg_store_int32
c_func
(paren
)paren
)paren
id|pop_0
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* pop only if the number was actually stored&n;&t;&t; (see the 80486 manual p16-28) */
r_break
suffix:semicolon
r_case
l_int|016
suffix:colon
multiline_comment|/* fstp m64real */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
r_if
c_cond
(paren
id|reg_store_double
c_func
(paren
)paren
)paren
id|pop_0
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* pop only if the number was actually stored&n;&t;&t; (see the 80486 manual p16-28) */
r_break
suffix:semicolon
r_case
l_int|017
suffix:colon
multiline_comment|/* fistp m16int */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
r_if
c_cond
(paren
id|reg_store_int16
c_func
(paren
)paren
)paren
id|pop_0
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* pop only if the number was actually stored&n;&t;&t; (see the 80486 manual p16-28) */
r_break
suffix:semicolon
r_case
l_int|020
suffix:colon
multiline_comment|/* fldenv  m14/28byte */
id|fldenv
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|022
suffix:colon
multiline_comment|/* frstor m94/108byte */
id|frstor
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|023
suffix:colon
multiline_comment|/* fbld m80dec */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_load_bcd
c_func
(paren
)paren
suffix:semicolon
id|reg_move
c_func
(paren
op_amp
id|FPU_loaded_data
comma
id|pop_ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|024
suffix:colon
multiline_comment|/* fldcw */
id|RE_ENTRANT_CHECK_OFF
suffix:semicolon
id|control_word
op_assign
id|get_fs_word
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|FPU_data_address
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
suffix:semicolon
r_if
c_cond
(paren
id|partial_status
op_amp
op_complement
id|control_word
op_amp
id|CW_Exceptions
)paren
id|partial_status
op_or_assign
(paren
id|SW_Summary
op_or
id|SW_Backward
)paren
suffix:semicolon
r_else
id|partial_status
op_and_assign
op_complement
(paren
id|SW_Summary
op_or
id|SW_Backward
)paren
suffix:semicolon
macro_line|#ifdef PECULIAR_486
id|control_word
op_or_assign
l_int|0x40
suffix:semicolon
multiline_comment|/* An 80486 appears to always set this bit */
macro_line|#endif PECULIAR_486
id|NO_NET_DATA_EFFECT
suffix:semicolon
id|NO_NET_INSTR_EFFECT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|025
suffix:colon
multiline_comment|/* fld m80real */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_load_extended
c_func
(paren
)paren
suffix:semicolon
id|reg_move
c_func
(paren
op_amp
id|FPU_loaded_data
comma
id|pop_ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|027
suffix:colon
multiline_comment|/* fild m64int */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_load_int64
c_func
(paren
)paren
suffix:semicolon
id|reg_move
c_func
(paren
op_amp
id|FPU_loaded_data
comma
id|pop_ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|030
suffix:colon
multiline_comment|/* fstenv  m14/28byte */
id|fstenv
c_func
(paren
)paren
suffix:semicolon
id|NO_NET_DATA_EFFECT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|032
suffix:colon
multiline_comment|/* fsave */
id|fsave
c_func
(paren
)paren
suffix:semicolon
id|NO_NET_DATA_EFFECT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|033
suffix:colon
multiline_comment|/* fbstp m80dec */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
r_if
c_cond
(paren
id|reg_store_bcd
c_func
(paren
)paren
)paren
id|pop_0
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* pop only if the number was actually stored&n;&t;&t; (see the 80486 manual p16-28) */
r_break
suffix:semicolon
r_case
l_int|034
suffix:colon
multiline_comment|/* fstcw m16int */
id|RE_ENTRANT_CHECK_OFF
suffix:semicolon
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|FPU_data_address
comma
l_int|2
)paren
suffix:semicolon
id|put_fs_word
c_func
(paren
id|control_word
comma
(paren
r_int
op_star
)paren
id|FPU_data_address
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
suffix:semicolon
id|NO_NET_DATA_EFFECT
suffix:semicolon
id|NO_NET_INSTR_EFFECT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|035
suffix:colon
multiline_comment|/* fstp m80real */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
r_if
c_cond
(paren
id|reg_store_extended
c_func
(paren
)paren
)paren
id|pop_0
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* pop only if the number was actually stored&n;&t;&t; (see the 80486 manual p16-28) */
r_break
suffix:semicolon
r_case
l_int|036
suffix:colon
multiline_comment|/* fstsw m2byte */
id|RE_ENTRANT_CHECK_OFF
suffix:semicolon
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|FPU_data_address
comma
l_int|2
)paren
suffix:semicolon
id|put_fs_word
c_func
(paren
id|status_word
c_func
(paren
)paren
comma
(paren
r_int
op_star
)paren
id|FPU_data_address
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
suffix:semicolon
id|NO_NET_DATA_EFFECT
suffix:semicolon
id|NO_NET_INSTR_EFFECT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|037
suffix:colon
multiline_comment|/* fistp m64int */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
r_if
c_cond
(paren
id|reg_store_int64
c_func
(paren
)paren
)paren
id|pop_0
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* pop only if the number was actually stored&n;&t;&t; (see the 80486 manual p16-28) */
r_break
suffix:semicolon
)brace
)brace
eof
