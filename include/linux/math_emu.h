macro_line|#ifndef _LINUX_MATH_EMU_H
DECL|macro|_LINUX_MATH_EMU_H
mdefine_line|#define _LINUX_MATH_EMU_H
macro_line|#include &lt;linux/sched.h&gt;
DECL|struct|info
r_struct
id|info
(brace
DECL|member|___orig_eip
r_int
id|___orig_eip
suffix:semicolon
DECL|member|___ret_from_system_call
r_int
id|___ret_from_system_call
suffix:semicolon
DECL|member|___ebx
r_int
id|___ebx
suffix:semicolon
DECL|member|___ecx
r_int
id|___ecx
suffix:semicolon
DECL|member|___edx
r_int
id|___edx
suffix:semicolon
DECL|member|___esi
r_int
id|___esi
suffix:semicolon
DECL|member|___edi
r_int
id|___edi
suffix:semicolon
DECL|member|___ebp
r_int
id|___ebp
suffix:semicolon
DECL|member|___eax
r_int
id|___eax
suffix:semicolon
DECL|member|___ds
r_int
id|___ds
suffix:semicolon
DECL|member|___es
r_int
id|___es
suffix:semicolon
DECL|member|___fs
r_int
id|___fs
suffix:semicolon
DECL|member|___gs
r_int
id|___gs
suffix:semicolon
DECL|member|___orig_eax
r_int
id|___orig_eax
suffix:semicolon
DECL|member|___eip
r_int
id|___eip
suffix:semicolon
DECL|member|___cs
r_int
id|___cs
suffix:semicolon
DECL|member|___eflags
r_int
id|___eflags
suffix:semicolon
DECL|member|___esp
r_int
id|___esp
suffix:semicolon
DECL|member|___ss
r_int
id|___ss
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EAX
mdefine_line|#define EAX (info-&gt;___eax)
DECL|macro|EBX
mdefine_line|#define EBX (info-&gt;___ebx)
DECL|macro|ECX
mdefine_line|#define ECX (info-&gt;___ecx)
DECL|macro|EDX
mdefine_line|#define EDX (info-&gt;___edx)
DECL|macro|ESI
mdefine_line|#define ESI (info-&gt;___esi)
DECL|macro|EDI
mdefine_line|#define EDI (info-&gt;___edi)
DECL|macro|EBP
mdefine_line|#define EBP (info-&gt;___ebp)
DECL|macro|ESP
mdefine_line|#define ESP (info-&gt;___esp)
DECL|macro|EIP
mdefine_line|#define EIP (info-&gt;___eip)
DECL|macro|ORIG_EIP
mdefine_line|#define ORIG_EIP (info-&gt;___orig_eip)
DECL|macro|EFLAGS
mdefine_line|#define EFLAGS (info-&gt;___eflags)
DECL|macro|DS
mdefine_line|#define DS (*(unsigned short *) &amp;(info-&gt;___ds))
DECL|macro|ES
mdefine_line|#define ES (*(unsigned short *) &amp;(info-&gt;___es))
DECL|macro|FS
mdefine_line|#define FS (*(unsigned short *) &amp;(info-&gt;___fs))
DECL|macro|CS
mdefine_line|#define CS (*(unsigned short *) &amp;(info-&gt;___cs))
DECL|macro|SS
mdefine_line|#define SS (*(unsigned short *) &amp;(info-&gt;___ss))
r_void
id|__math_abort
c_func
(paren
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|math_abort
mdefine_line|#define math_abort(x,y) &bslash;&n;(((volatile void (*)(struct info *,unsigned int)) __math_abort)((x),(y)))
multiline_comment|/*&n; * Gcc forces this stupid alignment problem: I want to use only two longs&n; * for the temporary real 64-bit mantissa, but then gcc aligns out the&n; * structure to 12 bytes which breaks things in math_emulate.c. Shit. I&n; * want some kind of &quot;no-alignt&quot; pragma or something.&n; */
r_typedef
r_struct
(brace
DECL|member|a
DECL|member|b
r_int
id|a
comma
id|b
suffix:semicolon
DECL|member|exponent
r_int
id|exponent
suffix:semicolon
DECL|typedef|temp_real
)brace
id|temp_real
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|m0
DECL|member|m1
DECL|member|m2
DECL|member|m3
r_int
id|m0
comma
id|m1
comma
id|m2
comma
id|m3
suffix:semicolon
DECL|member|exponent
r_int
id|exponent
suffix:semicolon
DECL|typedef|temp_real_unaligned
)brace
id|temp_real_unaligned
suffix:semicolon
DECL|macro|real_to_real
mdefine_line|#define real_to_real(a,b) &bslash;&n;((*(long long *) (b) = *(long long *) (a)),((b)-&gt;exponent = (a)-&gt;exponent))
r_typedef
r_struct
(brace
DECL|member|a
DECL|member|b
r_int
id|a
comma
id|b
suffix:semicolon
DECL|typedef|long_real
)brace
id|long_real
suffix:semicolon
DECL|typedef|short_real
r_typedef
r_int
id|short_real
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|a
DECL|member|b
r_int
id|a
comma
id|b
suffix:semicolon
DECL|member|sign
r_int
id|sign
suffix:semicolon
DECL|typedef|temp_int
)brace
id|temp_int
suffix:semicolon
DECL|struct|swd
r_struct
id|swd
(brace
DECL|member|ie
r_int
id|ie
suffix:colon
l_int|1
suffix:semicolon
DECL|member|de
r_int
id|de
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ze
r_int
id|ze
suffix:colon
l_int|1
suffix:semicolon
DECL|member|oe
r_int
id|oe
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ue
r_int
id|ue
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pe
r_int
id|pe
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sf
r_int
id|sf
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ir
r_int
id|ir
suffix:colon
l_int|1
suffix:semicolon
DECL|member|c0
r_int
id|c0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|c1
r_int
id|c1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|c2
r_int
id|c2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|top
r_int
id|top
suffix:colon
l_int|3
suffix:semicolon
DECL|member|c3
r_int
id|c3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|b
r_int
id|b
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|I387
mdefine_line|#define I387 (current-&gt;tss.i387)
DECL|macro|SWD
mdefine_line|#define SWD (*(struct swd *) &amp;I387.swd)
DECL|macro|ROUNDING
mdefine_line|#define ROUNDING ((I387.cwd &gt;&gt; 10) &amp; 3)
DECL|macro|PRECISION
mdefine_line|#define PRECISION ((I387.cwd &gt;&gt; 8) &amp; 3)
DECL|macro|BITS24
mdefine_line|#define BITS24&t;0
DECL|macro|BITS53
mdefine_line|#define BITS53&t;2
DECL|macro|BITS64
mdefine_line|#define BITS64&t;3
DECL|macro|ROUND_NEAREST
mdefine_line|#define ROUND_NEAREST&t;0
DECL|macro|ROUND_DOWN
mdefine_line|#define ROUND_DOWN&t;1
DECL|macro|ROUND_UP
mdefine_line|#define ROUND_UP&t;2
DECL|macro|ROUND_0
mdefine_line|#define ROUND_0&t;&t;3
DECL|macro|CONSTZ
mdefine_line|#define CONSTZ   (temp_real_unaligned) {0x0000,0x0000,0x0000,0x0000,0x0000}
DECL|macro|CONST1
mdefine_line|#define CONST1   (temp_real_unaligned) {0x0000,0x0000,0x0000,0x8000,0x3FFF}
DECL|macro|CONSTPI
mdefine_line|#define CONSTPI  (temp_real_unaligned) {0xC235,0x2168,0xDAA2,0xC90F,0x4000}
DECL|macro|CONSTLN2
mdefine_line|#define CONSTLN2 (temp_real_unaligned) {0x79AC,0xD1CF,0x17F7,0xB172,0x3FFE}
DECL|macro|CONSTLG2
mdefine_line|#define CONSTLG2 (temp_real_unaligned) {0xF799,0xFBCF,0x9A84,0x9A20,0x3FFD}
DECL|macro|CONSTL2E
mdefine_line|#define CONSTL2E (temp_real_unaligned) {0xF0BC,0x5C17,0x3B29,0xB8AA,0x3FFF}
DECL|macro|CONSTL2T
mdefine_line|#define CONSTL2T (temp_real_unaligned) {0x8AFE,0xCD1B,0x784B,0xD49A,0x4000}
DECL|macro|set_IE
mdefine_line|#define set_IE() (I387.swd |= 1)
DECL|macro|set_DE
mdefine_line|#define set_DE() (I387.swd |= 2)
DECL|macro|set_ZE
mdefine_line|#define set_ZE() (I387.swd |= 4)
DECL|macro|set_OE
mdefine_line|#define set_OE() (I387.swd |= 8)
DECL|macro|set_UE
mdefine_line|#define set_UE() (I387.swd |= 16)
DECL|macro|set_PE
mdefine_line|#define set_PE() (I387.swd |= 32)
DECL|macro|set_C0
mdefine_line|#define set_C0() (I387.swd |= 0x0100)
DECL|macro|set_C1
mdefine_line|#define set_C1() (I387.swd |= 0x0200)
DECL|macro|set_C2
mdefine_line|#define set_C2() (I387.swd |= 0x0400)
DECL|macro|set_C3
mdefine_line|#define set_C3() (I387.swd |= 0x4000)
multiline_comment|/* ea.c */
r_char
op_star
id|ea
c_func
(paren
r_struct
id|info
op_star
id|__info
comma
r_int
r_int
id|__code
)paren
suffix:semicolon
multiline_comment|/* convert.c */
r_void
id|frndint
c_func
(paren
r_const
id|temp_real
op_star
id|__a
comma
id|temp_real
op_star
id|__b
)paren
suffix:semicolon
r_void
id|short_to_temp
c_func
(paren
r_const
id|short_real
op_star
id|__a
comma
id|temp_real
op_star
id|__b
)paren
suffix:semicolon
r_void
id|long_to_temp
c_func
(paren
r_const
id|long_real
op_star
id|__a
comma
id|temp_real
op_star
id|__b
)paren
suffix:semicolon
r_void
id|temp_to_short
c_func
(paren
r_const
id|temp_real
op_star
id|__a
comma
id|short_real
op_star
id|__b
)paren
suffix:semicolon
r_void
id|temp_to_long
c_func
(paren
r_const
id|temp_real
op_star
id|__a
comma
id|long_real
op_star
id|__b
)paren
suffix:semicolon
r_void
id|real_to_int
c_func
(paren
r_const
id|temp_real
op_star
id|__a
comma
id|temp_int
op_star
id|__b
)paren
suffix:semicolon
r_void
id|int_to_real
c_func
(paren
r_const
id|temp_int
op_star
id|__a
comma
id|temp_real
op_star
id|__b
)paren
suffix:semicolon
multiline_comment|/* get_put.c */
r_void
id|get_short_real
c_func
(paren
id|temp_real
op_star
comma
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|get_long_real
c_func
(paren
id|temp_real
op_star
comma
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|get_temp_real
c_func
(paren
id|temp_real
op_star
comma
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|get_short_int
c_func
(paren
id|temp_real
op_star
comma
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|get_long_int
c_func
(paren
id|temp_real
op_star
comma
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|get_longlong_int
c_func
(paren
id|temp_real
op_star
comma
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|get_BCD
c_func
(paren
id|temp_real
op_star
comma
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|put_short_real
c_func
(paren
r_const
id|temp_real
op_star
comma
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|put_long_real
c_func
(paren
r_const
id|temp_real
op_star
comma
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|put_temp_real
c_func
(paren
r_const
id|temp_real
op_star
comma
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|put_short_int
c_func
(paren
r_const
id|temp_real
op_star
comma
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|put_long_int
c_func
(paren
r_const
id|temp_real
op_star
comma
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|put_longlong_int
c_func
(paren
r_const
id|temp_real
op_star
comma
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|put_BCD
c_func
(paren
r_const
id|temp_real
op_star
comma
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* add.c */
r_void
id|fadd
c_func
(paren
r_const
id|temp_real
op_star
comma
r_const
id|temp_real
op_star
comma
id|temp_real
op_star
)paren
suffix:semicolon
multiline_comment|/* mul.c */
r_void
id|fmul
c_func
(paren
r_const
id|temp_real
op_star
comma
r_const
id|temp_real
op_star
comma
id|temp_real
op_star
)paren
suffix:semicolon
multiline_comment|/* div.c */
r_void
id|fdiv
c_func
(paren
r_const
id|temp_real
op_star
comma
r_const
id|temp_real
op_star
comma
id|temp_real
op_star
)paren
suffix:semicolon
multiline_comment|/* sqrt.c */
r_void
id|fsqrt
c_func
(paren
r_const
id|temp_real
op_star
comma
id|temp_real
op_star
)paren
suffix:semicolon
multiline_comment|/* compare.c */
r_void
id|fcom
c_func
(paren
r_const
id|temp_real
op_star
comma
r_const
id|temp_real
op_star
)paren
suffix:semicolon
r_void
id|fucom
c_func
(paren
r_const
id|temp_real
op_star
comma
r_const
id|temp_real
op_star
)paren
suffix:semicolon
r_void
id|ftst
c_func
(paren
r_const
id|temp_real
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
