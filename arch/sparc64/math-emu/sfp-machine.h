multiline_comment|/* Machine-dependent software floating-point definitions.  Sparc64 version.&n;   Copyright (C) 1997 Free Software Foundation, Inc.&n;   This file is part of the GNU C Library.&n;&n;   The GNU C Library is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU Library General Public License as&n;   published by the Free Software Foundation; either version 2 of the&n;   License, or (at your option) any later version.&n;&n;   The GNU C Library is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   Library General Public License for more details.&n;&n;   You should have received a copy of the GNU Library General Public&n;   License along with the GNU C Library; see the file COPYING.LIB.  If&n;   not, write to the Free Software Foundation, Inc.,&n;   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
DECL|macro|_FP_W_TYPE_SIZE
mdefine_line|#define _FP_W_TYPE_SIZE&t;&t;64
DECL|macro|_FP_W_TYPE
mdefine_line|#define _FP_W_TYPE&t;&t;unsigned long
DECL|macro|_FP_WS_TYPE
mdefine_line|#define _FP_WS_TYPE&t;&t;signed long
DECL|macro|_FP_I_TYPE
mdefine_line|#define _FP_I_TYPE&t;&t;long
DECL|macro|_FP_MUL_MEAT_S
mdefine_line|#define _FP_MUL_MEAT_S(R,X,Y)&t;_FP_MUL_MEAT_1_imm(S,R,X,Y)
DECL|macro|_FP_MUL_MEAT_D
mdefine_line|#define _FP_MUL_MEAT_D(R,X,Y)&t;_FP_MUL_MEAT_1_wide(D,R,X,Y,umul_ppmm)
DECL|macro|_FP_MUL_MEAT_Q
mdefine_line|#define _FP_MUL_MEAT_Q(R,X,Y)&t;_FP_MUL_MEAT_2_wide(Q,R,X,Y,umul_ppmm)
DECL|macro|_FP_DIV_MEAT_S
mdefine_line|#define _FP_DIV_MEAT_S(R,X,Y)&t;_FP_DIV_MEAT_1_imm(S,R,X,Y,_FP_DIV_HELP_imm)
DECL|macro|_FP_DIV_MEAT_D
mdefine_line|#define _FP_DIV_MEAT_D(R,X,Y)&t;_FP_DIV_MEAT_1_udiv(D,R,X,Y)
DECL|macro|_FP_DIV_MEAT_Q
mdefine_line|#define _FP_DIV_MEAT_Q(R,X,Y)&t;_FP_DIV_MEAT_2_udiv_64(Q,R,X,Y)
DECL|macro|_FP_NANFRAC_S
mdefine_line|#define _FP_NANFRAC_S&t;&t;_FP_QNANBIT_S
DECL|macro|_FP_NANFRAC_D
mdefine_line|#define _FP_NANFRAC_D&t;&t;_FP_QNANBIT_D
DECL|macro|_FP_NANFRAC_Q
mdefine_line|#define _FP_NANFRAC_Q&t;&t;_FP_QNANBIT_Q, 0
DECL|macro|_FP_KEEPNANFRACP
mdefine_line|#define _FP_KEEPNANFRACP 1
DECL|macro|_FP_CHOOSENAN
mdefine_line|#define _FP_CHOOSENAN(fs, wc, R, X, Y)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    R##_s = Y##_s;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_FRAC_COPY_##wc(R,Y);&t;&t;&t;&t;&t;&bslash;&n;    R##_c = FP_CLS_NAN;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|__FP_UNPACK_RAW_1
mdefine_line|#define __FP_UNPACK_RAW_1(fs, X, val)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_##fs *_flo =&t;&t;&t;&t;&bslash;&n;    &t;(union _FP_UNION_##fs *)val;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_f = _flo-&gt;bits.frac;&t;&t;&t;&t;&t;&bslash;&n;    X##_e = _flo-&gt;bits.exp;&t;&t;&t;&t;&t;&bslash;&n;    X##_s = _flo-&gt;bits.sign;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|__FP_UNPACK_RAW_2
mdefine_line|#define __FP_UNPACK_RAW_2(fs, X, val)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_##fs *_flo =&t;&t;&t;&bslash;&n;    &t;(union _FP_UNION_##fs *)val;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_f0 = _flo-&gt;bits.frac0;&t;&t;&t;&t;&bslash;&n;    X##_f1 = _flo-&gt;bits.frac1;&t;&t;&t;&t;&bslash;&n;    X##_e  = _flo-&gt;bits.exp;&t;&t;&t;&t;&bslash;&n;    X##_s  = _flo-&gt;bits.sign;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|__FP_UNPACK_S
mdefine_line|#define __FP_UNPACK_S(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    __FP_UNPACK_RAW_1(S,X,val);&t;&t;&bslash;&n;    _FP_UNPACK_CANONICAL(S,1,X);&t;&bslash;&n;  } while (0)
DECL|macro|__FP_UNPACK_D
mdefine_line|#define __FP_UNPACK_D(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    __FP_UNPACK_RAW_1(D,X,val);&t;&t;&bslash;&n;    _FP_UNPACK_CANONICAL(D,1,X);&t;&bslash;&n;  } while (0)
DECL|macro|__FP_UNPACK_Q
mdefine_line|#define __FP_UNPACK_Q(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    __FP_UNPACK_RAW_2(Q,X,val);&t;&t;&bslash;&n;    _FP_UNPACK_CANONICAL(Q,2,X);&t;&bslash;&n;  } while (0)
DECL|macro|__FP_PACK_RAW_1
mdefine_line|#define __FP_PACK_RAW_1(fs, val, X)&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_##fs *_flo =&t;&t;&t;&t;&bslash;&n;    &t;(union _FP_UNION_##fs *)val;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.frac = X##_f;&t;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.exp  = X##_e;&t;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.sign = X##_s;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|__FP_PACK_RAW_2
mdefine_line|#define __FP_PACK_RAW_2(fs, val, X)&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    union _FP_UNION_##fs *_flo =&t;&t;&t;&bslash;&n;    &t;(union _FP_UNION_##fs *)val;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.frac0 = X##_f0;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.frac1 = X##_f1;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.exp   = X##_e;&t;&t;&t;&t;&bslash;&n;    _flo-&gt;bits.sign  = X##_s;&t;&t;&t;&t;&bslash;&n;  } while (0)
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/* We only actually write to the destination register&n; * if exceptions signalled (if any) will not trap.&n; */
DECL|macro|__FPU_TEM
mdefine_line|#define __FPU_TEM &bslash;&n;&t;(((current-&gt;tss.xfsr[0])&gt;&gt;23)&amp;0x1f)
DECL|macro|__FPU_TRAP_P
mdefine_line|#define __FPU_TRAP_P(bits) &bslash;&n;&t;((__FPU_TEM &amp; (bits)) != 0)
DECL|macro|__FP_PACK_S
mdefine_line|#define __FP_PACK_S(val,X)&t;&t;&t;&bslash;&n;({  int __exc = _FP_PACK_CANONICAL(S,1,X);&t;&bslash;&n;    if(!__exc || !__FPU_TRAP_P(__exc))&t;&t;&bslash;&n;        __FP_PACK_RAW_1(S,val,X);&t;&t;&bslash;&n;    __exc;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__FP_PACK_D
mdefine_line|#define __FP_PACK_D(val,X)&t;&t;&t;&bslash;&n;({  int __exc = _FP_PACK_CANONICAL(D,1,X);&t;&bslash;&n;    if(!__exc || !__FPU_TRAP_P(__exc))&t;&t;&bslash;&n;        __FP_PACK_RAW_1(D,val,X);&t;&t;&bslash;&n;    __exc;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__FP_PACK_Q
mdefine_line|#define __FP_PACK_Q(val,X)&t;&t;&t;&bslash;&n;({  int __exc = _FP_PACK_CANONICAL(Q,2,X);&t;&bslash;&n;    if(!__exc || !__FPU_TRAP_P(__exc))&t;&t;&bslash;&n;        __FP_PACK_RAW_2(Q,val,X);&t;&t;&bslash;&n;    __exc;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* Obtain the current rounding mode. */
DECL|macro|FP_ROUNDMODE
mdefine_line|#define FP_ROUNDMODE&t;((current-&gt;tss.xfsr[0] &gt;&gt; 30) &amp; 0x3)
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|add_ssaaaa
mdefine_line|#define add_ssaaaa(sh, sl, ah, al, bh, bl) &t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ (&quot;addcc %4,%5,%1
id|add
op_mod
l_int|2
comma
op_mod
l_int|3
comma
op_mod
l_int|0
id|bcs
comma
id|a
comma
id|pn
op_mod
op_mod
id|xcc
comma
l_float|1f
id|add
op_mod
l_int|0
comma
l_int|1
comma
op_mod
l_int|0
l_int|1
suffix:colon
l_string|&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_assign
id|r
l_string|&quot; ((UDItype)(sh)),&t;&t;&t;&t;      &t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((UDItype)(sl))&t;&t;&t;&t;      &t;&t;&t;&bslash;&n;&t;   : &quot;
id|r
l_string|&quot; ((UDItype)(ah)),&t;&t;&t;&t;     &t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((UDItype)(bh)),&t;&t;&t;&t;      &t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((UDItype)(al)),&t;&t;&t;&t;     &t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((UDItype)(bl))&t;&t;&t;&t;       &t;&t;&t;&bslash;&n;&t;   : &quot;
id|cc
"&quot;"
)paren
DECL|macro|sub_ddmmss
mdefine_line|#define sub_ddmmss(sh, sl, ah, al, bh, bl) &t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ (&quot;subcc %4,%5,%1
id|sub
op_mod
l_int|2
comma
op_mod
l_int|3
comma
op_mod
l_int|0
id|bcs
comma
id|a
comma
id|pn
op_mod
op_mod
id|xcc
comma
l_float|1f
id|sub
op_mod
l_int|0
comma
l_int|1
comma
op_mod
l_int|0
l_int|1
suffix:colon
l_string|&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_assign
id|r
l_string|&quot; ((UDItype)(sh)),&t;&t;&t;&t;      &t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((UDItype)(sl))&t;&t;&t;&t;      &t;&t;&t;&bslash;&n;&t;   : &quot;
id|r
l_string|&quot; ((UDItype)(ah)),&t;&t;&t;&t;     &t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((UDItype)(bh)),&t;&t;&t;&t;      &t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((UDItype)(al)),&t;&t;&t;&t;     &t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((UDItype)(bl))&t;&t;&t;&t;       &t;&t;&t;&bslash;&n;&t;   : &quot;
id|cc
"&quot;"
)paren
DECL|macro|umul_ppmm
mdefine_line|#define umul_ppmm(wh, wl, u, v) &t;&t;&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  __asm__ (&quot;mulx %2,%3,%1
id|srlx
op_mod
l_int|2
comma
l_int|32
comma
op_mod
op_mod
id|g1
id|srl
op_mod
l_int|3
comma
l_int|0
comma
op_mod
op_mod
id|g2
id|mulx
op_mod
op_mod
id|g1
comma
op_mod
op_mod
id|g2
comma
op_mod
op_mod
id|g3
id|srlx
op_mod
l_int|3
comma
l_int|32
comma
op_mod
op_mod
id|g1
id|srl
op_mod
l_int|2
comma
l_int|0
comma
op_mod
op_mod
id|g2
id|mulx
op_mod
op_mod
id|g1
comma
op_mod
op_mod
id|g2
comma
op_mod
op_mod
id|g2
id|srlx
op_mod
l_int|2
comma
l_int|32
comma
op_mod
op_mod
id|g1
id|add
op_mod
op_mod
id|g2
comma
op_mod
op_mod
id|g3
comma
op_mod
op_mod
id|g3
id|srlx
op_mod
l_int|3
comma
l_int|32
comma
op_mod
op_mod
id|g2
id|mulx
op_mod
op_mod
id|g1
comma
op_mod
op_mod
id|g2
comma
op_mod
op_mod
id|g1
id|srlx
op_mod
op_mod
id|g3
comma
l_int|32
comma
op_mod
op_mod
id|g2
id|add
op_mod
op_mod
id|g1
comma
op_mod
op_mod
id|g2
comma
op_mod
l_int|0
l_string|&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_assign
id|r
l_string|&quot; ((UDItype)(wh)),&t;&t;&t;&t;      &t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((UDItype)(wl))&t;&t;&t;&t;      &t;&t;&t;&bslash;&n;&t;   : &quot;
id|r
l_string|&quot; ((UDItype)(u)),&t;&t;&t;&t;     &t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((UDItype)(v))&t;&t;&t;&t;      &t;&t;&t;&t;&bslash;&n;&t;   : &quot;
id|g1
l_string|&quot;, &quot;
id|g2
l_string|&quot;, &quot;
id|g3
l_string|&quot;, &quot;
id|cc
"&quot;"
)paren
suffix:semicolon
"&bslash;"
)brace
r_while
c_loop
(paren
l_int|0
)paren
DECL|macro|udiv_qrnnd
mdefine_line|#define udiv_qrnnd(q, r, n1, n0, d) &t;&t;&t;&t;&t;&t;&t;&bslash;&n;  do {                                                                  &t;&t;&bslash;&n;    UWtype __d1, __d0, __q1, __q0, __r1, __r0, __m;                     &t;&t;&bslash;&n;    __d1 = (d &gt;&gt; 32);                                           &t;&t;&t;&bslash;&n;    __d0 = (USItype)d;                                            &t;&t;&t;&bslash;&n;                                                                        &t;&t;&bslash;&n;    __r1 = (n1) % __d1;                                                 &t;&t;&bslash;&n;    __q1 = (n1) / __d1;                                                 &t;&t;&bslash;&n;    __m = (UWtype) __q1 * __d0;                                         &t;&t;&bslash;&n;    __r1 = (__r1 &lt;&lt; 32) | (n0 &gt;&gt; 32);                          &t;&t;&t;&t;&bslash;&n;    if (__r1 &lt; __m)                                                     &t;&t;&bslash;&n;      {                                                                 &t;&t;&bslash;&n;        __q1--, __r1 += (d);                                            &t;&t;&bslash;&n;        if (__r1 &gt;= (d)) /* i.e. we didn&squot;t get carry when adding to __r1 */&t;&t;&bslash;&n;          if (__r1 &lt; __m)                                               &t;&t;&bslash;&n;            __q1--, __r1 += (d);                                        &t;&t;&bslash;&n;      }                                                                 &t;&t;&bslash;&n;    __r1 -= __m;                                                        &t;&t;&bslash;&n;                                                                        &t;&t;&bslash;&n;    __r0 = __r1 % __d1;                                                 &t;&t;&bslash;&n;    __q0 = __r1 / __d1;                                                 &t;&t;&bslash;&n;    __m = (UWtype) __q0 * __d0;                                         &t;&t;&bslash;&n;    __r0 = (__r0 &lt;&lt; 32) | ((USItype)n0);                           &t;&t;&t;&bslash;&n;    if (__r0 &lt; __m)                                                     &t;&t;&bslash;&n;      {                                                                 &t;&t;&bslash;&n;        __q0--, __r0 += (d);                                            &t;&t;&bslash;&n;        if (__r0 &gt;= (d))                                                &t;&t;&bslash;&n;          if (__r0 &lt; __m)                                               &t;&t;&bslash;&n;            __q0--, __r0 += (d);                                        &t;&t;&bslash;&n;      }                                                                 &t;&t;&bslash;&n;    __r0 -= __m;                                                        &t;&t;&bslash;&n;                                                                        &t;&t;&bslash;&n;    (q) = (UWtype) (__q1 &lt;&lt; 32)  | __q0;                                &t;&t;&bslash;&n;    (r) = __r0;                                                         &t;&t;&bslash;&n;  } while (0)
DECL|macro|UDIV_NEEDS_NORMALIZATION
mdefine_line|#define UDIV_NEEDS_NORMALIZATION 1  
DECL|macro|abort
mdefine_line|#define abort()&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return 0
macro_line|#ifdef __BIG_ENDIAN
DECL|macro|__BYTE_ORDER
mdefine_line|#define __BYTE_ORDER __BIG_ENDIAN
macro_line|#else
DECL|macro|__BYTE_ORDER
mdefine_line|#define __BYTE_ORDER __LITTLE_ENDIAN
macro_line|#endif
multiline_comment|/* Exception flags. */
DECL|macro|EFLAG_INVALID
mdefine_line|#define EFLAG_INVALID&t;&t;(1 &lt;&lt; 4)
DECL|macro|EFLAG_OVERFLOW
mdefine_line|#define EFLAG_OVERFLOW&t;&t;(1 &lt;&lt; 3)
DECL|macro|EFLAG_UNDERFLOW
mdefine_line|#define EFLAG_UNDERFLOW&t;&t;(1 &lt;&lt; 2)
DECL|macro|EFLAG_DIVZERO
mdefine_line|#define EFLAG_DIVZERO&t;&t;(1 &lt;&lt; 1)
DECL|macro|EFLAG_INEXACT
mdefine_line|#define EFLAG_INEXACT&t;&t;(1 &lt;&lt; 0)
eof
