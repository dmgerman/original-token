multiline_comment|/* $Id: btfixup.c,v 1.7 1998/03/09 14:03:56 jj Exp $&n; * btfixup.c: Boot time code fixup and relocator, so that&n; * we can get rid of most indirect calls to achieve single&n; * image sun4c and srmmu kernel.&n; *&n; * Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/btfixup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|BTFIXUP_OPTIMIZE_NOP
mdefine_line|#define BTFIXUP_OPTIMIZE_NOP
DECL|macro|BTFIXUP_OPTIMIZE_OTHER
mdefine_line|#define BTFIXUP_OPTIMIZE_OTHER
r_extern
r_char
op_star
id|srmmu_name
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|version
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Boot time fixup v1.6. 4/Mar/98 Jakub Jelinek (jj@ultra.linux.cz). Patching kernel for &quot;
suffix:semicolon
macro_line|#ifdef CONFIG_SUN4
DECL|variable|__initdata
r_static
r_char
id|str_sun4c
(braket
)braket
id|__initdata
op_assign
l_string|&quot;sun4&bslash;n&quot;
suffix:semicolon
macro_line|#else
DECL|variable|__initdata
r_static
r_char
id|str_sun4c
(braket
)braket
id|__initdata
op_assign
l_string|&quot;sun4c&bslash;n&quot;
suffix:semicolon
macro_line|#endif
DECL|variable|__initdata
r_static
r_char
id|str_srmmu
(braket
)braket
id|__initdata
op_assign
l_string|&quot;srmmu[%s]/&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|str_iommu
(braket
)braket
id|__initdata
op_assign
l_string|&quot;iommu&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|str_iounit
(braket
)braket
id|__initdata
op_assign
l_string|&quot;io-unit&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|visited
id|__initdata
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
r_int
id|___btfixup_start
(braket
)braket
comma
id|___btfixup_end
(braket
)braket
comma
id|__init_begin
(braket
)braket
comma
id|__init_end
(braket
)braket
comma
id|__init_text_end
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|_stext
(braket
)braket
comma
id|_end
(braket
)braket
comma
id|__start___ksymtab
(braket
)braket
comma
id|__stop___ksymtab
(braket
)braket
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|wrong_f
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Trying to set f fixup %p to invalid function %08x&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|wrong_b
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Trying to set b fixup %p to invalid function %08x&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|wrong_s
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Trying to set s fixup %p to invalid value %08x&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|wrong_h
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Trying to set h fixup %p to invalid value %08x&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|wrong_a
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Trying to set a fixup %p to invalid value %08x&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|wrong
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Wrong address for %c fixup %p&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|insn_f
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Fixup f %p refers to weird instructions at %p[%08x,%08x]&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|insn_b
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Fixup b %p doesn&squot;t refer to a SETHI at %p[%08x]&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|insn_s
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Fixup s %p doesn&squot;t refer to an OR at %p[%08x]&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|insn_h
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Fixup h %p doesn&squot;t refer to a SETHI at %p[%08x]&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|insn_a
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Fixup a %p doesn&squot;t refer to a SETHI nor OR at %p[%08x]&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|insn_i
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Fixup i %p doesn&squot;t refer to a valid instruction at %p[%08x]&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|fca_und
(braket
)braket
id|__initdata
op_assign
l_string|&quot;flush_cache_all undefined in btfixup()&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|wrong_setaddr
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Garbled CALL/INT patch at %p[%08x,%08x,%08x]=%08x&bslash;n&quot;
suffix:semicolon
macro_line|#ifdef BTFIXUP_OPTIMIZE_OTHER
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_static
r_void
id|set_addr
c_func
(paren
r_int
r_int
op_star
id|addr
comma
r_int
r_int
id|q1
comma
r_int
id|fmangled
comma
r_int
r_int
id|value
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fmangled
)paren
op_star
id|addr
op_assign
id|value
suffix:semicolon
r_else
(brace
r_int
r_int
op_star
id|q
op_assign
(paren
r_int
r_int
op_star
)paren
id|q1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|addr
op_eq
l_int|0x01000000
)paren
(brace
multiline_comment|/* Noped */
op_star
id|q
op_assign
id|value
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|addr
(braket
op_minus
l_int|1
)braket
op_eq
op_star
id|q
)paren
(brace
multiline_comment|/* Moved */
id|addr
(braket
op_minus
l_int|1
)braket
op_assign
id|value
suffix:semicolon
op_star
id|q
op_assign
id|value
suffix:semicolon
)brace
r_else
(brace
id|prom_printf
c_func
(paren
id|wrong_setaddr
comma
id|addr
op_minus
l_int|1
comma
id|addr
(braket
op_minus
l_int|1
)braket
comma
op_star
id|addr
comma
op_star
id|q
comma
id|value
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#else
DECL|function|set_addr
r_static
id|__inline__
r_void
id|set_addr
c_func
(paren
r_int
r_int
op_star
id|addr
comma
r_int
r_int
id|q1
comma
r_int
id|fmangled
comma
r_int
r_int
id|value
)paren
(brace
op_star
id|addr
op_assign
id|value
suffix:semicolon
)brace
macro_line|#endif
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|btfixup
c_func
(paren
r_void
)paren
)paren
(brace
r_int
r_int
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_int
id|type
comma
id|count
suffix:semicolon
r_int
id|insn
suffix:semicolon
r_int
op_star
id|addr
suffix:semicolon
r_int
id|fmangled
op_assign
l_int|0
suffix:semicolon
r_void
(paren
op_star
id|flush_cacheall
)paren
(paren
r_void
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|visited
)paren
(brace
id|visited
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|version
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ARCH_SUN4C_SUN4
)paren
id|printk
c_func
(paren
id|str_sun4c
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
id|str_srmmu
comma
id|srmmu_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4d
)paren
id|printk
c_func
(paren
id|str_iounit
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|str_iommu
)paren
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|p
op_assign
id|___btfixup_start
suffix:semicolon
id|p
OL
id|___btfixup_end
suffix:semicolon
)paren
(brace
id|count
op_assign
id|p
(braket
l_int|2
)braket
suffix:semicolon
id|q
op_assign
id|p
op_plus
l_int|3
suffix:semicolon
r_switch
c_cond
(paren
id|type
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|p
)paren
(brace
r_case
l_char|&squot;f&squot;
suffix:colon
id|count
op_assign
id|p
(braket
l_int|3
)braket
suffix:semicolon
id|q
op_assign
id|p
op_plus
l_int|4
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|p
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
op_logical_or
id|p
(braket
l_int|1
)braket
)paren
op_logical_and
(paren
(paren
id|p
(braket
l_int|1
)braket
op_amp
l_int|3
)paren
op_logical_or
(paren
r_int
op_star
)paren
(paren
id|p
(braket
l_int|1
)braket
)paren
OL
id|_stext
op_logical_or
(paren
r_int
op_star
)paren
(paren
id|p
(braket
l_int|1
)braket
)paren
op_ge
id|_end
)paren
)paren
(brace
id|prom_printf
c_func
(paren
id|wrong_f
comma
id|p
comma
id|p
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;b&squot;
suffix:colon
r_if
c_cond
(paren
id|p
(braket
l_int|1
)braket
OL
(paren
r_int
r_int
)paren
id|__init_begin
op_logical_or
id|p
(braket
l_int|1
)braket
op_ge
(paren
r_int
r_int
)paren
id|__init_text_end
op_logical_or
(paren
id|p
(braket
l_int|1
)braket
op_amp
l_int|3
)paren
)paren
(brace
id|prom_printf
c_func
(paren
id|wrong_b
comma
id|p
comma
id|p
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
r_if
c_cond
(paren
id|p
(braket
l_int|1
)braket
op_plus
l_int|0x1000
op_ge
l_int|0x2000
)paren
(brace
id|prom_printf
c_func
(paren
id|wrong_s
comma
id|p
comma
id|p
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;h&squot;
suffix:colon
r_if
c_cond
(paren
id|p
(braket
l_int|1
)braket
op_amp
l_int|0x3ff
)paren
(brace
id|prom_printf
c_func
(paren
id|wrong_h
comma
id|p
comma
id|p
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;a&squot;
suffix:colon
r_if
c_cond
(paren
id|p
(braket
l_int|1
)braket
op_plus
l_int|0x1000
op_ge
l_int|0x2000
op_logical_and
(paren
id|p
(braket
l_int|1
)braket
op_amp
l_int|0x3ff
)paren
)paren
(brace
id|prom_printf
c_func
(paren
id|wrong_a
comma
id|p
comma
id|p
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
(brace
id|p
(braket
l_int|0
)braket
op_and_assign
op_complement
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|fmangled
op_assign
l_int|0
suffix:semicolon
id|addr
op_assign
(paren
r_int
op_star
)paren
op_star
id|q
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|_stext
op_logical_or
id|addr
op_ge
id|_end
)paren
(brace
id|prom_printf
c_func
(paren
id|wrong
comma
id|type
comma
id|p
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|insn
op_assign
op_star
id|addr
suffix:semicolon
macro_line|#ifdef BTFIXUP_OPTIMIZE_OTHER&t;&t;&t;&t;
r_if
c_cond
(paren
id|type
op_ne
l_char|&squot;f&squot;
op_logical_and
id|q
(braket
l_int|1
)braket
)paren
(brace
id|insn
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|q
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|insn
op_logical_or
id|insn
op_eq
l_int|1
)paren
id|insn
op_assign
op_star
id|addr
suffix:semicolon
r_else
id|fmangled
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
l_char|&squot;f&squot;
suffix:colon
multiline_comment|/* CALL */
r_if
c_cond
(paren
id|addr
op_ge
id|__start___ksymtab
op_logical_and
id|addr
OL
id|__stop___ksymtab
)paren
(brace
op_star
id|addr
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|q
(braket
l_int|1
)braket
)paren
(brace
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc1c00000
)paren
op_eq
l_int|0x01000000
)paren
(brace
multiline_comment|/* SETHI */
op_star
id|addr
op_assign
(paren
id|insn
op_amp
l_int|0xffc00000
)paren
op_or
(paren
id|p
(braket
l_int|1
)braket
op_rshift
l_int|10
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc1f82000
)paren
op_eq
l_int|0x80102000
)paren
(brace
multiline_comment|/* OR X, %LO(i), Y */
op_star
id|addr
op_assign
(paren
id|insn
op_amp
l_int|0xffffe000
)paren
op_or
(paren
id|p
(braket
l_int|1
)braket
op_amp
l_int|0x3ff
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc0000000
)paren
op_ne
l_int|0x40000000
)paren
(brace
multiline_comment|/* !CALL */
id|bad_f
suffix:colon
id|prom_printf
c_func
(paren
id|insn_f
comma
id|p
comma
id|addr
comma
id|insn
comma
id|addr
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|q
(braket
l_int|1
)braket
op_ne
l_int|1
)paren
id|addr
(braket
l_int|1
)braket
op_assign
id|q
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|p
(braket
l_int|2
)braket
op_eq
id|BTFIXUPCALL_NORM
)paren
(brace
id|norm_f
suffix:colon
op_star
id|addr
op_assign
l_int|0x40000000
op_or
(paren
(paren
id|p
(braket
l_int|1
)braket
op_minus
(paren
r_int
)paren
id|addr
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
id|q
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#ifndef BTFIXUP_OPTIMIZE_NOP
r_goto
id|norm_f
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
op_logical_neg
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0x80000000
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0xc1c00000
)paren
op_ne
l_int|0x01000000
)paren
multiline_comment|/* !SETHI */
r_goto
id|bad_f
suffix:semicolon
multiline_comment|/* CALL, Bicc, FBfcc, CBccc are weird in delay slot, aren&squot;t they? */
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0x01800000
)paren
op_eq
l_int|0x01800000
)paren
(brace
r_if
c_cond
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0x01f80000
)paren
op_eq
l_int|0x01e80000
)paren
(brace
multiline_comment|/* RESTORE */
r_goto
id|norm_f
suffix:semicolon
multiline_comment|/* It is dangerous to patch that */
)brace
r_goto
id|bad_f
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0xffffe003
)paren
op_eq
l_int|0x9e03e000
)paren
(brace
multiline_comment|/* ADD %O7, XX, %o7 */
r_int
id|displac
op_assign
(paren
id|addr
(braket
l_int|1
)braket
op_lshift
l_int|19
)paren
suffix:semicolon
id|displac
op_assign
(paren
id|displac
op_rshift
l_int|21
)paren
op_plus
l_int|2
suffix:semicolon
op_star
id|addr
op_assign
(paren
l_int|0x10800000
)paren
op_plus
(paren
id|displac
op_amp
l_int|0x3fffff
)paren
suffix:semicolon
id|q
(braket
l_int|1
)braket
op_assign
id|addr
(braket
l_int|1
)braket
suffix:semicolon
id|addr
(braket
l_int|1
)braket
op_assign
id|p
(braket
l_int|2
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0x201f
)paren
op_eq
l_int|0x200f
op_logical_or
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0x7c000
)paren
op_eq
l_int|0x3c000
)paren
r_goto
id|norm_f
suffix:semicolon
multiline_comment|/* Someone is playing bad tricks with us: rs1 or rs2 is o7 */
r_if
c_cond
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0x3e000000
)paren
op_eq
l_int|0x1e000000
)paren
r_goto
id|norm_f
suffix:semicolon
multiline_comment|/* rd is %o7. We&squot;d better take care. */
)brace
r_if
c_cond
(paren
id|p
(braket
l_int|2
)braket
op_eq
id|BTFIXUPCALL_NOP
)paren
(brace
op_star
id|addr
op_assign
l_int|0x01000000
suffix:semicolon
id|q
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#ifndef BTFIXUP_OPTIMIZE_OTHER
r_goto
id|norm_f
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|addr
(braket
l_int|1
)braket
op_eq
l_int|0x01000000
)paren
(brace
multiline_comment|/* NOP in the delay slot */
id|q
(braket
l_int|1
)braket
op_assign
id|addr
(braket
l_int|1
)braket
suffix:semicolon
op_star
id|addr
op_assign
id|p
(braket
l_int|2
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0xc0000000
)paren
op_ne
l_int|0xc0000000
)paren
(brace
multiline_comment|/* Not a memory operation */
r_if
c_cond
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0x30000000
)paren
op_eq
l_int|0x10000000
)paren
(brace
multiline_comment|/* Ok, non-memory op with rd %oX */
r_if
c_cond
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0x3e000000
)paren
op_eq
l_int|0x1c000000
)paren
r_goto
id|bad_f
suffix:semicolon
multiline_comment|/* Aiee. Someone is playing strange %sp tricks */
r_if
c_cond
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0x3e000000
)paren
OG
l_int|0x12000000
op_logical_or
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0x3e000000
)paren
op_eq
l_int|0x12000000
op_logical_and
id|p
(braket
l_int|2
)braket
op_ne
id|BTFIXUPCALL_STO1O0
op_logical_and
id|p
(braket
l_int|2
)braket
op_ne
id|BTFIXUPCALL_SWAPO0O1
)paren
op_logical_or
(paren
(paren
id|p
(braket
l_int|2
)braket
op_amp
l_int|0xffffe000
)paren
op_eq
id|BTFIXUPCALL_RETINT
c_func
(paren
l_int|0
)paren
)paren
)paren
(brace
multiline_comment|/* Nobody uses the result. We can nop it out. */
op_star
id|addr
op_assign
id|p
(braket
l_int|2
)braket
suffix:semicolon
id|q
(braket
l_int|1
)braket
op_assign
id|addr
(braket
l_int|1
)braket
suffix:semicolon
id|addr
(braket
l_int|1
)braket
op_assign
l_int|0x01000000
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0xf1ffffe0
)paren
op_eq
l_int|0x90100000
)paren
(brace
multiline_comment|/* MOV %reg, %Ox */
r_if
c_cond
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0x3e000000
)paren
op_eq
l_int|0x10000000
op_logical_and
(paren
id|p
(braket
l_int|2
)braket
op_amp
l_int|0x7c000
)paren
op_eq
l_int|0x20000
)paren
(brace
multiline_comment|/* Ok, it is call xx; mov reg, %o0 and call optimizes&n;&t;&t;&t;&t;&t;&t;&t;&t;    &t;   to doing something on %o0. Patch the patch. */
op_star
id|addr
op_assign
(paren
id|p
(braket
l_int|2
)braket
op_amp
op_complement
l_int|0x7c000
)paren
op_or
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0x1f
)paren
op_lshift
l_int|14
)paren
suffix:semicolon
id|q
(braket
l_int|1
)braket
op_assign
id|addr
(braket
l_int|1
)braket
suffix:semicolon
id|addr
(braket
l_int|1
)braket
op_assign
l_int|0x01000000
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0x3e000000
)paren
op_eq
l_int|0x12000000
op_logical_and
id|p
(braket
l_int|2
)braket
op_eq
id|BTFIXUPCALL_STO1O0
)paren
(brace
op_star
id|addr
op_assign
(paren
id|p
(braket
l_int|2
)braket
op_amp
op_complement
l_int|0x3e000000
)paren
op_or
(paren
(paren
id|addr
(braket
l_int|1
)braket
op_amp
l_int|0x1f
)paren
op_lshift
l_int|25
)paren
suffix:semicolon
id|q
(braket
l_int|1
)braket
op_assign
id|addr
(braket
l_int|1
)braket
suffix:semicolon
id|addr
(braket
l_int|1
)braket
op_assign
l_int|0x01000000
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
op_star
id|addr
op_assign
id|addr
(braket
l_int|1
)braket
suffix:semicolon
id|q
(braket
l_int|1
)braket
op_assign
id|addr
(braket
l_int|1
)braket
suffix:semicolon
id|addr
(braket
l_int|1
)braket
op_assign
id|p
(braket
l_int|2
)braket
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* BTFIXUP_OPTIMIZE_OTHER */
macro_line|#endif /* BTFIXUP_OPTIMIZE_NOP */
r_case
l_char|&squot;b&squot;
suffix:colon
multiline_comment|/* BLACKBOX */
multiline_comment|/* Has to be sethi i, xx */
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc1c00000
)paren
op_ne
l_int|0x01000000
)paren
(brace
id|prom_printf
c_func
(paren
id|insn_b
comma
id|p
comma
id|addr
comma
id|insn
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_void
(paren
op_star
id|do_fixup
)paren
(paren
r_int
op_star
)paren
suffix:semicolon
id|do_fixup
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_int
op_star
)paren
)paren
id|p
(braket
l_int|1
)braket
suffix:semicolon
id|do_fixup
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
multiline_comment|/* SIMM13 */
multiline_comment|/* Has to be or %g0, i, xx */
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc1ffe000
)paren
op_ne
l_int|0x80102000
)paren
(brace
id|prom_printf
c_func
(paren
id|insn_s
comma
id|p
comma
id|addr
comma
id|insn
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_addr
c_func
(paren
id|addr
comma
id|q
(braket
l_int|1
)braket
comma
id|fmangled
comma
(paren
id|insn
op_amp
l_int|0xffffe000
)paren
op_or
(paren
id|p
(braket
l_int|1
)braket
op_amp
l_int|0x1fff
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;h&squot;
suffix:colon
multiline_comment|/* SETHI */
multiline_comment|/* Has to be sethi i, xx */
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc1c00000
)paren
op_ne
l_int|0x01000000
)paren
(brace
id|prom_printf
c_func
(paren
id|insn_h
comma
id|p
comma
id|addr
comma
id|insn
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_addr
c_func
(paren
id|addr
comma
id|q
(braket
l_int|1
)braket
comma
id|fmangled
comma
(paren
id|insn
op_amp
l_int|0xffc00000
)paren
op_or
(paren
id|p
(braket
l_int|1
)braket
op_rshift
l_int|10
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;a&squot;
suffix:colon
multiline_comment|/* HALF */
multiline_comment|/* Has to be sethi i, xx or or %g0, i, xx */
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc1c00000
)paren
op_ne
l_int|0x01000000
op_logical_and
(paren
id|insn
op_amp
l_int|0xc1ffe000
)paren
op_ne
l_int|0x80102000
)paren
(brace
id|prom_printf
c_func
(paren
id|insn_a
comma
id|p
comma
id|addr
comma
id|insn
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
(braket
l_int|1
)braket
op_amp
l_int|0x3ff
)paren
id|set_addr
c_func
(paren
id|addr
comma
id|q
(braket
l_int|1
)braket
comma
id|fmangled
comma
(paren
id|insn
op_amp
l_int|0x3e000000
)paren
op_or
l_int|0x80102000
op_or
(paren
id|p
(braket
l_int|1
)braket
op_amp
l_int|0x1fff
)paren
)paren
suffix:semicolon
r_else
id|set_addr
c_func
(paren
id|addr
comma
id|q
(braket
l_int|1
)braket
comma
id|fmangled
comma
(paren
id|insn
op_amp
l_int|0x3e000000
)paren
op_or
l_int|0x01000000
op_or
(paren
id|p
(braket
l_int|1
)braket
op_rshift
l_int|10
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;i&squot;
suffix:colon
multiline_comment|/* INT */
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc1c00000
)paren
op_eq
l_int|0x01000000
)paren
multiline_comment|/* %HI */
id|set_addr
c_func
(paren
id|addr
comma
id|q
(braket
l_int|1
)braket
comma
id|fmangled
comma
(paren
id|insn
op_amp
l_int|0xffc00000
)paren
op_or
(paren
id|p
(braket
l_int|1
)braket
op_rshift
l_int|10
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0x80002000
)paren
op_eq
l_int|0x80002000
op_logical_and
(paren
id|insn
op_amp
l_int|0x01800000
)paren
op_ne
l_int|0x01800000
)paren
multiline_comment|/* %LO */
id|set_addr
c_func
(paren
id|addr
comma
id|q
(braket
l_int|1
)braket
comma
id|fmangled
comma
(paren
id|insn
op_amp
l_int|0xffffe000
)paren
op_or
(paren
id|p
(braket
l_int|1
)braket
op_amp
l_int|0x3ff
)paren
)paren
suffix:semicolon
r_else
(brace
id|prom_printf
c_func
(paren
id|insn_i
comma
id|p
comma
id|addr
comma
id|insn
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|count
op_sub_assign
l_int|2
suffix:semicolon
id|q
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
r_else
id|p
op_assign
id|q
op_plus
id|count
suffix:semicolon
)brace
macro_line|#ifdef __SMP__
id|flush_cacheall
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_void
)paren
)paren
id|BTFIXUPVAL_CALL
c_func
(paren
id|local_flush_cache_all
)paren
suffix:semicolon
macro_line|#else
id|flush_cacheall
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_void
)paren
)paren
id|BTFIXUPVAL_CALL
c_func
(paren
id|flush_cache_all
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|flush_cacheall
)paren
(brace
id|prom_printf
c_func
(paren
id|fca_und
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
(paren
op_star
id|flush_cacheall
)paren
(paren
)paren
suffix:semicolon
)brace
eof