multiline_comment|/* $Id: checksum.h,v 1.26 1997/03/14 07:54:47 davem Exp $ */
macro_line|#ifndef __SPARC_CHECKSUM_H
DECL|macro|__SPARC_CHECKSUM_H
mdefine_line|#define __SPARC_CHECKSUM_H
multiline_comment|/*  checksum.h:  IP/UDP/TCP checksum routines on the Sparc.&n; *&n; *  Copyright(C) 1995 Linus Torvalds&n; *  Copyright(C) 1995 Miguel de Icaza&n; *  Copyright(C) 1996 David S. Miller&n; *  Copyright(C) 1996 Eddie C. Dost&n; *  Copyright(C) 1997 Jakub Jelinek&n; *&n; * derived from:&n; *&t;Alpha checksum c-code&n; *      ix86 inline assembly&n; *      RFC1071 Computing the Internet Checksum&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/cprefix.h&gt;
multiline_comment|/* computes the checksum of a memory block at buff, length len,&n; * and adds in &quot;sum&quot; (32-bit)&n; *&n; * returns a 32-bit number suitable for feeding into itself&n; * or csum_tcpudp_magic&n; *&n; * this function must be called with even lengths, except&n; * for the last fragment, which may be odd&n; *&n; * it&squot;s best to have buff aligned on a 32-bit boundary&n; */
r_extern
r_int
r_int
id|csum_partial
c_func
(paren
r_int
r_char
op_star
id|buff
comma
r_int
id|len
comma
r_int
r_int
id|sum
)paren
suffix:semicolon
multiline_comment|/* the same as csum_partial, but copies from fs:src while it&n; * checksums&n; *&n; * here even more important to align src and dst on a 32-bit (or even&n; * better 64-bit) boundary&n; */
multiline_comment|/* FIXME: Remove these two macros ASAP */
DECL|macro|csum_partial_copy
mdefine_line|#define csum_partial_copy(src, dst, len, sum) &bslash;&n; &t;&t;       csum_partial_copy_nocheck(src,dst,len,sum)
DECL|macro|csum_partial_copy_fromuser
mdefine_line|#define csum_partial_copy_fromuser(s, d, l, w)  &bslash;&n;                         csum_partial_copy((char *) (s), (d), (l), (w))
r_extern
r_int
r_int
id|__csum_partial_copy_sparc_generic
(paren
r_const
r_char
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
id|__inline__
r_int
r_int
DECL|function|csum_partial_copy_nocheck
id|csum_partial_copy_nocheck
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
r_int
id|sum
)paren
(brace
r_register
r_int
r_int
id|ret
id|asm
c_func
(paren
l_string|&quot;o0&quot;
)paren
op_assign
(paren
r_int
r_int
)paren
id|src
suffix:semicolon
r_register
r_char
op_star
id|d
id|asm
c_func
(paren
l_string|&quot;o1&quot;
)paren
op_assign
id|dst
suffix:semicolon
r_register
r_int
id|l
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
op_assign
id|len
suffix:semicolon
id|__asm__
id|__volatile__
(paren
"&quot;"
id|call
l_string|&quot; C_LABEL_STR(__csum_partial_copy_sparc_generic) &quot;
id|mov
op_mod
l_int|4
comma
op_mod
op_mod
id|g7
l_string|&quot; : &quot;
op_assign
id|r
l_string|&quot; (ret) : &quot;
l_int|0
l_string|&quot; (ret), &quot;
id|r
l_string|&quot; (d), &quot;
id|r
l_string|&quot; (l), &quot;
id|r
"&quot;"
(paren
id|sum
)paren
suffix:colon
l_string|&quot;o1&quot;
comma
l_string|&quot;o2&quot;
comma
l_string|&quot;o3&quot;
comma
l_string|&quot;o4&quot;
comma
l_string|&quot;o5&quot;
comma
l_string|&quot;o7&quot;
comma
l_string|&quot;g1&quot;
comma
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
r_int
DECL|function|csum_partial_copy_from_user
id|csum_partial_copy_from_user
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
r_int
id|sum
comma
r_int
op_star
id|err
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|access_ok
(paren
id|VERIFY_READ
comma
id|src
comma
id|len
)paren
)paren
(brace
op_star
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|memset
(paren
id|dst
comma
l_int|0
comma
id|len
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
r_else
(brace
r_register
r_int
r_int
id|ret
id|asm
c_func
(paren
l_string|&quot;o0&quot;
)paren
op_assign
(paren
r_int
r_int
)paren
id|src
suffix:semicolon
r_register
r_char
op_star
id|d
id|asm
c_func
(paren
l_string|&quot;o1&quot;
)paren
op_assign
id|dst
suffix:semicolon
r_register
r_int
id|l
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
op_assign
id|len
suffix:semicolon
r_register
r_int
r_int
id|s
id|asm
c_func
(paren
l_string|&quot;g7&quot;
)paren
op_assign
id|sum
suffix:semicolon
id|__asm__
id|__volatile__
(paren
"&quot;"
dot
id|section
id|__ex_table
comma
macro_line|#alloc
dot
id|align
l_int|4
dot
id|word
l_float|1f
comma
l_int|2
dot
id|previous
l_int|1
suffix:colon
id|call
l_string|&quot; C_LABEL_STR(__csum_partial_copy_sparc_generic) &quot;
id|st
op_mod
l_int|5
comma
(braket
op_mod
op_mod
id|sp
op_plus
l_int|64
)braket
l_string|&quot; : &quot;
op_assign
id|r
l_string|&quot; (ret) : &quot;
l_int|0
l_string|&quot; (ret), &quot;
id|r
l_string|&quot; (d), &quot;
id|r
l_string|&quot; (l), &quot;
id|r
l_string|&quot; (s), &quot;
id|r
"&quot;"
(paren
id|err
)paren
suffix:colon
l_string|&quot;o1&quot;
comma
l_string|&quot;o2&quot;
comma
l_string|&quot;o3&quot;
comma
l_string|&quot;o4&quot;
comma
l_string|&quot;o5&quot;
comma
l_string|&quot;o7&quot;
comma
l_string|&quot;g1&quot;
comma
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
r_extern
id|__inline__
r_int
r_int
DECL|function|csum_partial_copy_to_user
id|csum_partial_copy_to_user
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
r_int
id|sum
comma
r_int
op_star
id|err
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|access_ok
(paren
id|VERIFY_WRITE
comma
id|dst
comma
id|len
)paren
)paren
(brace
op_star
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
r_else
(brace
r_register
r_int
r_int
id|ret
id|asm
c_func
(paren
l_string|&quot;o0&quot;
)paren
op_assign
(paren
r_int
r_int
)paren
id|src
suffix:semicolon
r_register
r_char
op_star
id|d
id|asm
c_func
(paren
l_string|&quot;o1&quot;
)paren
op_assign
id|dst
suffix:semicolon
r_register
r_int
id|l
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
op_assign
id|len
suffix:semicolon
r_register
r_int
r_int
id|s
id|asm
c_func
(paren
l_string|&quot;g7&quot;
)paren
op_assign
id|sum
suffix:semicolon
id|__asm__
id|__volatile__
(paren
"&quot;"
dot
id|section
id|__ex_table
comma
macro_line|#alloc
dot
id|align
l_int|4
dot
id|word
l_float|1f
comma
l_int|1
dot
id|previous
l_int|1
suffix:colon
id|call
l_string|&quot; C_LABEL_STR(__csum_partial_copy_sparc_generic) &quot;
id|st
op_mod
l_int|5
comma
(braket
op_mod
op_mod
id|sp
op_plus
l_int|64
)braket
l_string|&quot; : &quot;
op_assign
id|r
l_string|&quot; (ret) : &quot;
l_int|0
l_string|&quot; (ret), &quot;
id|r
l_string|&quot; (d), &quot;
id|r
l_string|&quot; (l), &quot;
id|r
l_string|&quot; (s), &quot;
id|r
"&quot;"
(paren
id|err
)paren
suffix:colon
l_string|&quot;o1&quot;
comma
l_string|&quot;o2&quot;
comma
l_string|&quot;o3&quot;
comma
l_string|&quot;o4&quot;
comma
l_string|&quot;o5&quot;
comma
l_string|&quot;o7&quot;
comma
l_string|&quot;g1&quot;
comma
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
multiline_comment|/* ihl is always 5 or greater, almost always is 5, and iph is word aligned&n; * the majority of the time.&n; */
DECL|function|ip_fast_csum
r_extern
id|__inline__
r_int
r_int
id|ip_fast_csum
c_func
(paren
id|__const__
r_int
r_char
op_star
id|iph
comma
r_int
r_int
id|ihl
)paren
(brace
r_int
r_int
id|sum
suffix:semicolon
multiline_comment|/* Note: We must read %2 before we touch %0 for the first time,&n;&t; *       because GCC can legitimately use the same register for&n;&t; *       both operands.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sub&bslash;t%2, 4, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t[%1 + 0x00], %0&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t[%1 + 0x04], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t[%1 + 0x08], %%g3&bslash;n&bslash;t&quot;
l_string|&quot;addcc&bslash;t%%g2, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&bslash;t%%g3, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t[%1 + 0x0c], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t[%1 + 0x10], %%g3&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&bslash;t%%g2, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;addx&bslash;t%0, %%g0, %0&bslash;n&quot;
l_string|&quot;1:&bslash;taddcc&bslash;t%%g3, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;add&bslash;t%1, 4, %1&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&bslash;t%0, %%g0, %0&bslash;n&bslash;t&quot;
l_string|&quot;subcc&bslash;t%%g4, 1, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;be,a&bslash;t2f&bslash;n&bslash;t&quot;
l_string|&quot;sll&bslash;t%0, 16, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;b&bslash;t1b&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t[%1 + 0x10], %%g3&bslash;n&quot;
l_string|&quot;2:&bslash;taddcc&bslash;t%0, %%g2, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;srl&bslash;t%%g2, 16, %0&bslash;n&bslash;t&quot;
l_string|&quot;addx&bslash;t%0, %%g0, %0&bslash;n&bslash;t&quot;
l_string|&quot;xnor&bslash;t%%g0, %0, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|iph
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ihl
)paren
comma
l_string|&quot;1&quot;
(paren
id|iph
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/* computes the checksum of the TCP/UDP pseudo-header&n; * returns a 16-bit checksum, already complemented&n; */
DECL|function|csum_tcpudp_magic
r_extern
id|__inline__
r_int
r_int
id|csum_tcpudp_magic
c_func
(paren
r_int
r_int
id|saddr
comma
r_int
r_int
id|daddr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|proto
comma
r_int
r_int
id|sum
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;addcc&bslash;t%1, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&bslash;t%2, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&bslash;t%3, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;addx&bslash;t%0, %%g0, %0&bslash;n&bslash;t&quot;
l_string|&quot;sll&bslash;t%0, 16, %1&bslash;n&bslash;t&quot;
l_string|&quot;addcc&bslash;t%1, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;srl&bslash;t%0, 16, %0&bslash;n&bslash;t&quot;
l_string|&quot;addx&bslash;t%0, %%g0, %0&bslash;n&bslash;t&quot;
l_string|&quot;xnor&bslash;t%%g0, %0, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=r&quot;
(paren
id|saddr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|daddr
)paren
comma
l_string|&quot;r&quot;
(paren
(paren
id|proto
op_lshift
l_int|16
)paren
op_plus
id|len
)paren
comma
l_string|&quot;0&quot;
(paren
id|sum
)paren
comma
l_string|&quot;1&quot;
(paren
id|saddr
)paren
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/* Fold a partial checksum without adding pseudo headers. */
DECL|function|csum_fold
r_extern
id|__inline__
r_int
r_int
id|csum_fold
c_func
(paren
r_int
r_int
id|sum
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;addcc&bslash;t%0, %1, %1&bslash;n&bslash;t&quot;
l_string|&quot;srl&bslash;t%1, 16, %1&bslash;n&bslash;t&quot;
l_string|&quot;addx&bslash;t%1, %%g0, %1&bslash;n&bslash;t&quot;
l_string|&quot;xnor&bslash;t%%g0, %1, %0&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
comma
l_string|&quot;1&quot;
(paren
id|sum
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
DECL|macro|_HAVE_ARCH_IPV6_CSUM
mdefine_line|#define _HAVE_ARCH_IPV6_CSUM
DECL|function|csum_ipv6_magic
r_static
id|__inline__
r_int
r_int
r_int
id|csum_ipv6_magic
c_func
(paren
r_struct
id|in6_addr
op_star
id|saddr
comma
r_struct
id|in6_addr
op_star
id|daddr
comma
id|__u16
id|len
comma
r_int
r_int
id|proto
comma
r_int
r_int
id|sum
)paren
(brace
id|__asm__
id|__volatile__
(paren
"&quot;"
id|addcc
op_mod
l_int|3
comma
op_mod
l_int|4
comma
op_mod
op_mod
id|g4
id|addxcc
op_mod
l_int|5
comma
op_mod
op_mod
id|g4
comma
op_mod
op_mod
id|g4
id|ld
(braket
op_mod
l_int|2
op_plus
l_int|0x0c
)braket
comma
op_mod
op_mod
id|g2
id|ld
(braket
op_mod
l_int|2
op_plus
l_int|0x08
)braket
comma
op_mod
op_mod
id|g3
id|addxcc
op_mod
op_mod
id|g2
comma
op_mod
op_mod
id|g4
comma
op_mod
op_mod
id|g4
id|ld
(braket
op_mod
l_int|2
op_plus
l_int|0x04
)braket
comma
op_mod
op_mod
id|g2
id|addxcc
op_mod
op_mod
id|g3
comma
op_mod
op_mod
id|g4
comma
op_mod
op_mod
id|g4
id|ld
(braket
op_mod
l_int|2
op_plus
l_int|0x00
)braket
comma
op_mod
op_mod
id|g3
id|addxcc
op_mod
op_mod
id|g2
comma
op_mod
op_mod
id|g4
comma
op_mod
op_mod
id|g4
id|ld
(braket
op_mod
l_int|1
op_plus
l_int|0x0c
)braket
comma
op_mod
op_mod
id|g2
id|addxcc
op_mod
op_mod
id|g3
comma
op_mod
op_mod
id|g4
comma
op_mod
op_mod
id|g4
id|ld
(braket
op_mod
l_int|1
op_plus
l_int|0x08
)braket
comma
op_mod
op_mod
id|g3
id|addxcc
op_mod
op_mod
id|g2
comma
op_mod
op_mod
id|g4
comma
op_mod
op_mod
id|g4
id|ld
(braket
op_mod
l_int|1
op_plus
l_int|0x04
)braket
comma
op_mod
op_mod
id|g2
id|addxcc
op_mod
op_mod
id|g3
comma
op_mod
op_mod
id|g4
comma
op_mod
op_mod
id|g4
id|ld
(braket
op_mod
l_int|1
op_plus
l_int|0x00
)braket
comma
op_mod
op_mod
id|g3
id|addxcc
op_mod
op_mod
id|g2
comma
op_mod
op_mod
id|g4
comma
op_mod
op_mod
id|g4
id|addxcc
op_mod
op_mod
id|g3
comma
op_mod
op_mod
id|g4
comma
op_mod
l_int|0
id|addx
l_int|0
comma
op_mod
l_int|0
comma
op_mod
l_int|0
"&quot;"
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|saddr
)paren
comma
l_string|&quot;r&quot;
(paren
id|daddr
)paren
comma
l_string|&quot;r&quot;
(paren
id|htonl
c_func
(paren
(paren
id|__u32
)paren
(paren
id|len
)paren
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|htonl
c_func
(paren
id|proto
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
)paren
suffix:semicolon
r_return
id|csum_fold
c_func
(paren
id|sum
)paren
suffix:semicolon
)brace
multiline_comment|/* this routine is used for miscellaneous IP-like checksums, mainly in icmp.c */
DECL|function|ip_compute_csum
r_extern
id|__inline__
r_int
r_int
id|ip_compute_csum
c_func
(paren
r_int
r_char
op_star
id|buff
comma
r_int
id|len
)paren
(brace
r_return
id|csum_fold
c_func
(paren
id|csum_partial
c_func
(paren
id|buff
comma
id|len
comma
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(__SPARC_CHECKSUM_H) */
eof
