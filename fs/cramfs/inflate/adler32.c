multiline_comment|/* adler32.c -- compute the Adler-32 checksum of a data stream&n; * Copyright (C) 1995-1998 Mark Adler&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
multiline_comment|/* @(#) $Id$ */
macro_line|#include &quot;zlib.h&quot;
DECL|macro|BASE
mdefine_line|#define BASE 65521L /* largest prime smaller than 65536 */
DECL|macro|NMAX
mdefine_line|#define NMAX 5552
multiline_comment|/* NMAX is the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) &lt;= 2^32-1 */
DECL|macro|DO1
mdefine_line|#define DO1(buf,i)  {s1 += buf[i]; s2 += s1;}
DECL|macro|DO2
mdefine_line|#define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
DECL|macro|DO4
mdefine_line|#define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
DECL|macro|DO8
mdefine_line|#define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
DECL|macro|DO16
mdefine_line|#define DO16(buf)   DO8(buf,0); DO8(buf,8);
multiline_comment|/* ========================================================================= */
DECL|function|cramfs_adler32
id|uLong
id|ZEXPORT
id|cramfs_adler32
c_func
(paren
id|adler
comma
id|buf
comma
id|len
)paren
id|uLong
id|adler
suffix:semicolon
r_const
id|Bytef
op_star
id|buf
suffix:semicolon
id|uInt
id|len
suffix:semicolon
(brace
r_int
r_int
id|s1
op_assign
id|adler
op_amp
l_int|0xffff
suffix:semicolon
r_int
r_int
id|s2
op_assign
(paren
id|adler
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
suffix:semicolon
r_int
id|k
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
id|Z_NULL
)paren
r_return
l_int|1L
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
id|k
op_assign
id|len
OL
id|NMAX
ques
c_cond
id|len
suffix:colon
id|NMAX
suffix:semicolon
id|len
op_sub_assign
id|k
suffix:semicolon
r_while
c_loop
(paren
id|k
op_ge
l_int|16
)paren
(brace
id|DO16
c_func
(paren
id|buf
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|16
suffix:semicolon
id|k
op_sub_assign
l_int|16
suffix:semicolon
)brace
r_if
c_cond
(paren
id|k
op_ne
l_int|0
)paren
r_do
(brace
id|s1
op_add_assign
op_star
id|buf
op_increment
suffix:semicolon
id|s2
op_add_assign
id|s1
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|k
)paren
suffix:semicolon
id|s1
op_mod_assign
id|BASE
suffix:semicolon
id|s2
op_mod_assign
id|BASE
suffix:semicolon
)brace
r_return
(paren
id|s2
op_lshift
l_int|16
)paren
op_or
id|s1
suffix:semicolon
)brace
eof
