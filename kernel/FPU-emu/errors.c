multiline_comment|/*---------------------------------------------------------------------------+&n; |  errors.c                                                                 |&n; |                                                                           |&n; |  The error handling functions for wm-FPU-emu                              |&n; |                                                                           |&n; | Copyright (C) 1992    W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail apm233m@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
multiline_comment|/*---------------------------------------------------------------------------+&n; | Note:                                                                     |&n; |    The file contains code which accesses user memory.                     |&n; |    Emulator static data may change when user memory is accessed, due to   |&n; |    other processes using the emulator while swapping is in progress.      |&n; +---------------------------------------------------------------------------*/
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &quot;fpu_system.h&quot;
macro_line|#include &quot;exception.h&quot;
macro_line|#include &quot;fpu_emu.h&quot;
macro_line|#include &quot;status_w.h&quot;
macro_line|#include &quot;control_w.h&quot;
macro_line|#include &quot;reg_constant.h&quot;
macro_line|#include &quot;version.h&quot;
multiline_comment|/* */
DECL|macro|PRINT_MESSAGES
macro_line|#undef PRINT_MESSAGES
multiline_comment|/* */
DECL|function|Un_impl
r_void
id|Un_impl
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|byte1
comma
id|FPU_modrm
suffix:semicolon
id|RE_ENTRANT_CHECK_OFF
id|byte1
op_assign
id|get_fs_byte
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|FPU_ORIG_EIP
)paren
suffix:semicolon
id|FPU_modrm
op_assign
id|get_fs_byte
c_func
(paren
l_int|1
op_plus
(paren
r_int
r_char
op_star
)paren
id|FPU_ORIG_EIP
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Unimplemented FPU Opcode at eip=%p : %02x &quot;
comma
id|FPU_ORIG_EIP
comma
id|byte1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FPU_modrm
op_ge
l_int|0300
)paren
id|printk
c_func
(paren
l_string|&quot;%02x (%02x+%d)&bslash;n&quot;
comma
id|FPU_modrm
comma
id|FPU_modrm
op_amp
l_int|0xf8
comma
id|FPU_modrm
op_amp
l_int|7
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;/%d&bslash;n&quot;
comma
(paren
id|FPU_modrm
op_rshift
l_int|3
)paren
op_amp
l_int|7
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
id|EXCEPTION
c_func
(paren
id|EX_Invalid
)paren
suffix:semicolon
)brace
DECL|function|emu_printall
r_void
id|emu_printall
c_func
(paren
)paren
(brace
r_int
id|i
suffix:semicolon
r_static
r_char
op_star
id|tag_desc
(braket
)braket
op_assign
(brace
l_string|&quot;Valid&quot;
comma
l_string|&quot;Zero&quot;
comma
l_string|&quot;ERROR&quot;
comma
l_string|&quot;ERROR&quot;
comma
l_string|&quot;DeNorm&quot;
comma
l_string|&quot;Inf&quot;
comma
l_string|&quot;NaN&quot;
comma
l_string|&quot;Empty&quot;
)brace
suffix:semicolon
r_int
r_char
id|byte1
comma
id|FPU_modrm
suffix:semicolon
id|RE_ENTRANT_CHECK_OFF
id|byte1
op_assign
id|get_fs_byte
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|FPU_ORIG_EIP
)paren
suffix:semicolon
id|FPU_modrm
op_assign
id|get_fs_byte
c_func
(paren
l_int|1
op_plus
(paren
r_int
r_char
op_star
)paren
id|FPU_ORIG_EIP
)paren
suffix:semicolon
macro_line|#ifdef DEBUGGING
r_if
c_cond
(paren
id|status_word
op_amp
id|SW_B
)paren
id|printk
c_func
(paren
l_string|&quot;SW: backward compatibility (=ES)&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_word
op_amp
id|SW_C3
)paren
id|printk
c_func
(paren
l_string|&quot;SW: condition bit 3&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_word
op_amp
id|SW_C2
)paren
id|printk
c_func
(paren
l_string|&quot;SW: condition bit 2&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_word
op_amp
id|SW_C1
)paren
id|printk
c_func
(paren
l_string|&quot;SW: condition bit 1&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_word
op_amp
id|SW_C0
)paren
id|printk
c_func
(paren
l_string|&quot;SW: condition bit 0&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_word
op_amp
id|SW_ES
)paren
id|printk
c_func
(paren
l_string|&quot;SW: exception summary&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_word
op_amp
id|SW_SF
)paren
id|printk
c_func
(paren
l_string|&quot;SW: stack fault&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_word
op_amp
id|SW_PE
)paren
id|printk
c_func
(paren
l_string|&quot;SW: loss of precision&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_word
op_amp
id|SW_UE
)paren
id|printk
c_func
(paren
l_string|&quot;SW: underflow&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_word
op_amp
id|SW_OE
)paren
id|printk
c_func
(paren
l_string|&quot;SW: overflow&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_word
op_amp
id|SW_ZE
)paren
id|printk
c_func
(paren
l_string|&quot;SW: divide by zero&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_word
op_amp
id|SW_DE
)paren
id|printk
c_func
(paren
l_string|&quot;SW: denormalized operand&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_word
op_amp
id|SW_IE
)paren
id|printk
c_func
(paren
l_string|&quot;SW: invalid operation&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif DEBUGGING
id|status_word
op_assign
id|status_word
op_amp
op_complement
id|SW_TOP
suffix:semicolon
id|status_word
op_or_assign
(paren
id|top
op_amp
l_int|7
)paren
op_lshift
id|SW_TOPS
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;At %p: %02x &quot;
comma
id|FPU_ORIG_EIP
comma
id|byte1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FPU_modrm
op_ge
l_int|0300
)paren
id|printk
c_func
(paren
l_string|&quot;%02x (%02x+%d)&bslash;n&quot;
comma
id|FPU_modrm
comma
id|FPU_modrm
op_amp
l_int|0xf8
comma
id|FPU_modrm
op_amp
l_int|7
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;/%d, mod=%d rm=%d&bslash;n&quot;
comma
(paren
id|FPU_modrm
op_rshift
l_int|3
)paren
op_amp
l_int|7
comma
(paren
id|FPU_modrm
op_rshift
l_int|6
)paren
op_amp
l_int|3
comma
id|FPU_modrm
op_amp
l_int|7
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; SW: b=%d st=%d es=%d sf=%d cc=%d%d%d%d ef=%d%d%d%d%d%d&bslash;n&quot;
comma
id|status_word
op_amp
l_int|0x8000
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
multiline_comment|/* busy */
(paren
id|status_word
op_amp
l_int|0x3800
)paren
op_rshift
l_int|11
comma
multiline_comment|/* stack top pointer */
id|status_word
op_amp
l_int|0x80
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
multiline_comment|/* Error summary status */
id|status_word
op_amp
l_int|0x40
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
multiline_comment|/* Stack flag */
id|status_word
op_amp
id|SW_C3
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|status_word
op_amp
id|SW_C2
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
multiline_comment|/* cc */
id|status_word
op_amp
id|SW_C1
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|status_word
op_amp
id|SW_C0
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
multiline_comment|/* cc */
id|status_word
op_amp
id|SW_PE
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|status_word
op_amp
id|SW_UE
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
multiline_comment|/* exception fl */
id|status_word
op_amp
id|SW_OE
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|status_word
op_amp
id|SW_ZE
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
multiline_comment|/* exception fl */
id|status_word
op_amp
id|SW_DE
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|status_word
op_amp
id|SW_IE
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/* exception fl */
id|printk
c_func
(paren
l_string|&quot; CW: ic=%d rc=%d%d pc=%d%d iem=%d     ef=%d%d%d%d%d%d&bslash;n&quot;
comma
id|control_word
op_amp
l_int|0x1000
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
(paren
id|control_word
op_amp
l_int|0x800
)paren
op_rshift
l_int|11
comma
(paren
id|control_word
op_amp
l_int|0x400
)paren
op_rshift
l_int|10
comma
(paren
id|control_word
op_amp
l_int|0x200
)paren
op_rshift
l_int|9
comma
(paren
id|control_word
op_amp
l_int|0x100
)paren
op_rshift
l_int|8
comma
id|control_word
op_amp
l_int|0x80
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|control_word
op_amp
id|SW_PE
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|control_word
op_amp
id|SW_UE
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
multiline_comment|/* exception */
id|control_word
op_amp
id|SW_OE
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|control_word
op_amp
id|SW_ZE
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
multiline_comment|/* exception */
id|control_word
op_amp
id|SW_DE
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|control_word
op_amp
id|SW_IE
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/* exception */
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
id|FPU_REG
op_star
id|r
op_assign
op_amp
id|st
c_func
(paren
id|i
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|r-&gt;tag
)paren
(brace
r_case
id|TW_Empty
suffix:colon
r_continue
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TW_Zero
suffix:colon
id|printk
c_func
(paren
l_string|&quot;st(%d)  %c .0000 0000 0000 0000         &quot;
comma
id|i
comma
id|r-&gt;sign
ques
c_cond
l_char|&squot;-&squot;
suffix:colon
l_char|&squot;+&squot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TW_Valid
suffix:colon
r_case
id|TW_NaN
suffix:colon
r_case
id|TW_Denormal
suffix:colon
r_case
id|TW_Infinity
suffix:colon
id|printk
c_func
(paren
l_string|&quot;st(%d)  %c .%04x %04x %04x %04x e%+-6d &quot;
comma
id|i
comma
id|r-&gt;sign
ques
c_cond
l_char|&squot;-&squot;
suffix:colon
l_char|&squot;+&squot;
comma
(paren
r_int
)paren
(paren
id|r-&gt;sigh
op_rshift
l_int|16
)paren
comma
(paren
r_int
)paren
(paren
id|r-&gt;sigh
op_amp
l_int|0xFFFF
)paren
comma
(paren
r_int
)paren
(paren
id|r-&gt;sigl
op_rshift
l_int|16
)paren
comma
(paren
r_int
)paren
(paren
id|r-&gt;sigl
op_amp
l_int|0xFFFF
)paren
comma
id|r-&gt;exp
op_minus
id|EXP_BIAS
op_plus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Whoops! Error in errors.c      &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|tag_desc
(braket
(paren
r_int
)paren
(paren
r_int
)paren
id|r-&gt;tag
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;[data] %c .%04x %04x %04x %04x e%+-6d &quot;
comma
id|FPU_loaded_data.sign
ques
c_cond
l_char|&squot;-&squot;
suffix:colon
l_char|&squot;+&squot;
comma
(paren
r_int
)paren
(paren
id|FPU_loaded_data.sigh
op_rshift
l_int|16
)paren
comma
(paren
r_int
)paren
(paren
id|FPU_loaded_data.sigh
op_amp
l_int|0xFFFF
)paren
comma
(paren
r_int
)paren
(paren
id|FPU_loaded_data.sigl
op_rshift
l_int|16
)paren
comma
(paren
r_int
)paren
(paren
id|FPU_loaded_data.sigl
op_amp
l_int|0xFFFF
)paren
comma
id|FPU_loaded_data.exp
op_minus
id|EXP_BIAS
op_plus
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|tag_desc
(braket
(paren
r_int
)paren
(paren
r_int
)paren
id|FPU_loaded_data.tag
)braket
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
)brace
r_static
r_struct
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|variable|exception_names
)brace
id|exception_names
(braket
)braket
op_assign
(brace
(brace
id|EX_StackOver
comma
l_string|&quot;stack overflow&quot;
)brace
comma
(brace
id|EX_StackUnder
comma
l_string|&quot;stack underflow&quot;
)brace
comma
(brace
id|EX_Precision
comma
l_string|&quot;loss of precision&quot;
)brace
comma
(brace
id|EX_Underflow
comma
l_string|&quot;underflow&quot;
)brace
comma
(brace
id|EX_Overflow
comma
l_string|&quot;overflow&quot;
)brace
comma
(brace
id|EX_ZeroDiv
comma
l_string|&quot;divide by zero&quot;
)brace
comma
(brace
id|EX_Denormal
comma
l_string|&quot;denormalized operand&quot;
)brace
comma
(brace
id|EX_Invalid
comma
l_string|&quot;invalid operation&quot;
)brace
comma
(brace
id|EX_INTERNAL
comma
l_string|&quot;INTERNAL BUG in &quot;
id|FPU_VERSION
)brace
comma
(brace
l_int|0
comma
l_int|NULL
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; EX_INTERNAL is always given with a code which indicates where the&n; error was detected.&n;&n; Internal error types:&n;       0x14   in e14.c&n;       0x1nn  in a *.c file:&n;              0x101  in reg_add_sub.c&n;              0x102  in reg_mul.c&n;              0x103  in poly_sin.c&n;              0x104  in poly_tan.c&n;              0x105  in reg_mul.c&n;&t;      0x106  in reg_mov.c&n;              0x107  in fpu_trig.c&n;&t;      0x108  in reg_compare.c&n;&t;      0x109  in reg_compare.c&n;&t;      0x110  in reg_add_sub.c&n;&t;      0x111  in interface.c&n;&t;      0x112  in fpu_trig.c&n;&t;      0x113  in reg_add_sub.c&n;&t;      0x114  in reg_ld_str.c&n;&t;      0x115  in fpu_trig.c&n;&t;      0x116  in fpu_trig.c&n;&t;      0x117  in fpu_trig.c&n;&t;      0x118  in fpu_trig.c&n;&t;      0x119  in fpu_trig.c&n;&t;      0x120  in poly_atan.c&n;&t;      0x121  in reg_compare.c&n;&t;      0x122  in reg_compare.c&n;&t;      0x123  in reg_compare.c&n;       0x2nn  in an *.s file:&n;              0x201  in reg_u_add.S&n;              0x202  in reg_u_div.S&n;              0x203  in reg_u_div.S&n;              0x204  in reg_u_div.S&n;              0x205  in reg_u_mul.S&n;              0x206  in reg_u_sub.S&n;              0x207  in wm_sqrt.S&n;&t;      0x208  in reg_div.S&n;              0x209  in reg_u_sub.S&n;              0x210  in reg_u_sub.S&n;              0x211  in reg_u_sub.S&n;              0x212  in reg_u_sub.S&n; */
DECL|function|exception
r_void
id|exception
c_func
(paren
r_int
id|n
)paren
(brace
r_int
id|i
comma
id|int_type
suffix:semicolon
id|int_type
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Needed only to stop compiler warnings */
r_if
c_cond
(paren
id|n
op_amp
id|EX_INTERNAL
)paren
(brace
id|int_type
op_assign
id|n
op_minus
id|EX_INTERNAL
suffix:semicolon
id|n
op_assign
id|EX_INTERNAL
suffix:semicolon
multiline_comment|/* Set lots of exception bits! */
id|status_word
op_or_assign
(paren
l_int|0x3f
op_or
id|EX_ErrorSummary
op_or
id|FPU_BUSY
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Set the corresponding exception bit */
id|status_word
op_or_assign
(paren
id|n
op_or
id|EX_ErrorSummary
op_or
id|FPU_BUSY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
id|EX_StackUnder
)paren
multiline_comment|/* Stack underflow */
multiline_comment|/* This bit distinguishes over- from underflow */
id|status_word
op_and_assign
op_complement
id|SW_C1
suffix:semicolon
)brace
id|RE_ENTRANT_CHECK_OFF
r_if
c_cond
(paren
(paren
op_complement
id|control_word
op_amp
id|n
op_amp
id|CW_EXM
)paren
op_logical_or
(paren
id|n
op_eq
id|EX_INTERNAL
)paren
)paren
(brace
macro_line|#ifdef PRINT_MESSAGES
multiline_comment|/* My message from the sponsor */
id|printk
c_func
(paren
id|FPU_VERSION
l_string|&quot; &quot;
id|__DATE__
l_string|&quot; (C) W. Metzenthen.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif PRINT_MESSAGES
multiline_comment|/* Get a name string for error reporting */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|exception_names
(braket
id|i
)braket
dot
id|type
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|exception_names
(braket
id|i
)braket
dot
id|type
op_eq
id|n
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|exception_names
(braket
id|i
)braket
dot
id|type
)paren
(brace
macro_line|#ifdef PRINT_MESSAGES
id|printk
c_func
(paren
l_string|&quot;FP Exception: %s!&bslash;n&quot;
comma
id|exception_names
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
macro_line|#endif PRINT_MESSAGES
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;FP emulator: Unknown Exception: 0x%04x!&bslash;n&quot;
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
id|EX_INTERNAL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;FP emulator: Internal error type 0x%04x&bslash;n&quot;
comma
id|int_type
)paren
suffix:semicolon
id|emu_printall
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef PRINT_MESSAGES
r_else
id|emu_printall
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PRINT_MESSAGES
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
)brace
id|RE_ENTRANT_CHECK_ON
macro_line|#ifdef __DEBUG__
id|math_abort
c_func
(paren
id|FPU_info
comma
id|SIGFPE
)paren
suffix:semicolon
macro_line|#endif __DEBUG__
multiline_comment|/* Cause the look-ahead mechanism to terminate */
id|FPU_lookahead
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Real operation attempted on two operands, one a NaN */
DECL|function|real_2op_NaN
r_void
id|real_2op_NaN
c_func
(paren
id|FPU_REG
op_star
id|a
comma
id|FPU_REG
op_star
id|b
comma
id|FPU_REG
op_star
id|dest
)paren
(brace
id|FPU_REG
op_star
id|x
suffix:semicolon
id|x
op_assign
id|a
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;tag
op_eq
id|TW_NaN
)paren
(brace
r_if
c_cond
(paren
id|b-&gt;tag
op_eq
id|TW_NaN
)paren
(brace
multiline_comment|/* find the &quot;larger&quot; */
r_if
c_cond
(paren
op_star
(paren
r_int
r_int
op_star
)paren
op_amp
(paren
id|a-&gt;sigl
)paren
OL
op_star
(paren
r_int
r_int
op_star
)paren
op_amp
(paren
id|b-&gt;sigl
)paren
)paren
id|x
op_assign
id|b
suffix:semicolon
)brace
multiline_comment|/* else return the quiet version of the NaN in a */
)brace
r_else
r_if
c_cond
(paren
id|b-&gt;tag
op_eq
id|TW_NaN
)paren
(brace
id|x
op_assign
id|b
suffix:semicolon
)brace
macro_line|#ifdef PARANOID
r_else
(brace
id|EXCEPTION
c_func
(paren
id|EX_INTERNAL
op_or
l_int|0x113
)paren
suffix:semicolon
id|x
op_assign
op_amp
id|CONST_QNaN
suffix:semicolon
)brace
macro_line|#endif PARANOID
r_if
c_cond
(paren
id|control_word
op_amp
id|EX_Invalid
)paren
(brace
multiline_comment|/* The masked response */
id|reg_move
c_func
(paren
id|x
comma
id|dest
)paren
suffix:semicolon
multiline_comment|/* ensure a Quiet NaN */
id|dest-&gt;sigh
op_or_assign
l_int|0x40000000
suffix:semicolon
)brace
id|EXCEPTION
c_func
(paren
id|EX_Invalid
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Invalid arith operation on valid registers */
DECL|function|arith_invalid
r_void
id|arith_invalid
c_func
(paren
id|FPU_REG
op_star
id|dest
)paren
(brace
r_if
c_cond
(paren
id|control_word
op_amp
id|EX_Invalid
)paren
(brace
multiline_comment|/* The masked response */
id|reg_move
c_func
(paren
op_amp
id|CONST_QNaN
comma
id|dest
)paren
suffix:semicolon
)brace
id|EXCEPTION
c_func
(paren
id|EX_Invalid
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Divide a finite number by zero */
DECL|function|divide_by_zero
r_void
id|divide_by_zero
c_func
(paren
r_int
id|sign
comma
id|FPU_REG
op_star
id|dest
)paren
(brace
r_if
c_cond
(paren
id|control_word
op_amp
id|EX_ZeroDiv
)paren
(brace
multiline_comment|/* The masked response */
id|reg_move
c_func
(paren
op_amp
id|CONST_INF
comma
id|dest
)paren
suffix:semicolon
id|dest-&gt;sign
op_assign
(paren
r_int
r_char
)paren
id|sign
suffix:semicolon
)brace
id|EXCEPTION
c_func
(paren
id|EX_ZeroDiv
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|arith_overflow
r_void
id|arith_overflow
c_func
(paren
id|FPU_REG
op_star
id|dest
)paren
(brace
r_if
c_cond
(paren
id|control_word
op_amp
id|EX_Overflow
)paren
(brace
r_char
id|sign
suffix:semicolon
multiline_comment|/* The masked response */
id|sign
op_assign
id|dest-&gt;sign
suffix:semicolon
id|reg_move
c_func
(paren
op_amp
id|CONST_INF
comma
id|dest
)paren
suffix:semicolon
id|dest-&gt;sign
op_assign
id|sign
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Subtract the magic number from the exponent */
id|dest-&gt;exp
op_sub_assign
(paren
l_int|3
op_star
(paren
l_int|1
op_lshift
l_int|13
)paren
)paren
suffix:semicolon
)brace
id|EXCEPTION
c_func
(paren
id|EX_Overflow
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|arith_underflow
r_void
id|arith_underflow
c_func
(paren
id|FPU_REG
op_star
id|dest
)paren
(brace
r_if
c_cond
(paren
id|control_word
op_amp
id|EX_Underflow
)paren
(brace
multiline_comment|/* The masked response */
r_if
c_cond
(paren
id|dest-&gt;exp
op_le
id|EXP_UNDER
op_minus
l_int|63
)paren
id|reg_move
c_func
(paren
op_amp
id|CONST_Z
comma
id|dest
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Add the magic number to the exponent */
id|dest-&gt;exp
op_add_assign
(paren
l_int|3
op_star
(paren
l_int|1
op_lshift
l_int|13
)paren
)paren
suffix:semicolon
)brace
id|EXCEPTION
c_func
(paren
id|EX_Underflow
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|stack_overflow
r_void
id|stack_overflow
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|control_word
op_amp
id|EX_Invalid
)paren
(brace
multiline_comment|/* The masked response */
id|top
op_decrement
suffix:semicolon
id|reg_move
c_func
(paren
op_amp
id|CONST_QNaN
comma
id|FPU_st0_ptr
op_assign
op_amp
id|st
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
id|EXCEPTION
c_func
(paren
id|EX_StackOver
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|stack_underflow
r_void
id|stack_underflow
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|control_word
op_amp
id|EX_Invalid
)paren
(brace
multiline_comment|/* The masked response */
id|reg_move
c_func
(paren
op_amp
id|CONST_QNaN
comma
id|FPU_st0_ptr
)paren
suffix:semicolon
)brace
id|EXCEPTION
c_func
(paren
id|EX_StackUnder
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
