multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Checksumming functions for IP, TCP, UDP and so on&n; *&n; * Authors:&t;Jorge Cwik, &lt;jorge@laser.satlink.net&gt;&n; *&t;&t;Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;&n; *&t;&t;Borrows very liberally from tcp.c and ip.c, see those&n; *&t;&t;files for more names.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
multiline_comment|/*&n; *&t;Fixes:&n; *&n; *&t;Ralf Baechle&t;&t;&t;:&t;generic ipv6 checksum&n; *&t;&lt;ralf@waldorf-gmbh.de&gt;&n; */
macro_line|#ifndef _CHECKSUM_H
DECL|macro|_CHECKSUM_H
mdefine_line|#define _CHECKSUM_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#ifndef _HAVE_ARCH_IPV6_CSUM
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
id|csum
)paren
(brace
r_int
id|carry
suffix:semicolon
id|__u32
id|ulen
suffix:semicolon
id|__u32
id|uproto
suffix:semicolon
id|csum
op_add_assign
id|saddr-&gt;s6_addr32
(braket
l_int|0
)braket
suffix:semicolon
id|carry
op_assign
(paren
id|csum
OL
id|saddr-&gt;s6_addr32
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|csum
op_add_assign
id|carry
suffix:semicolon
id|csum
op_add_assign
id|saddr-&gt;s6_addr32
(braket
l_int|1
)braket
suffix:semicolon
id|carry
op_assign
(paren
id|csum
OL
id|saddr-&gt;s6_addr32
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|csum
op_add_assign
id|carry
suffix:semicolon
id|csum
op_add_assign
id|saddr-&gt;s6_addr32
(braket
l_int|2
)braket
suffix:semicolon
id|carry
op_assign
(paren
id|csum
OL
id|saddr-&gt;s6_addr32
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|csum
op_add_assign
id|carry
suffix:semicolon
id|csum
op_add_assign
id|saddr-&gt;s6_addr32
(braket
l_int|3
)braket
suffix:semicolon
id|carry
op_assign
(paren
id|csum
OL
id|saddr-&gt;s6_addr32
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|csum
op_add_assign
id|carry
suffix:semicolon
id|csum
op_add_assign
id|daddr-&gt;s6_addr32
(braket
l_int|0
)braket
suffix:semicolon
id|carry
op_assign
(paren
id|csum
OL
id|daddr-&gt;s6_addr32
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|csum
op_add_assign
id|carry
suffix:semicolon
id|csum
op_add_assign
id|daddr-&gt;s6_addr32
(braket
l_int|1
)braket
suffix:semicolon
id|carry
op_assign
(paren
id|csum
OL
id|daddr-&gt;s6_addr32
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|csum
op_add_assign
id|carry
suffix:semicolon
id|csum
op_add_assign
id|daddr-&gt;s6_addr32
(braket
l_int|2
)braket
suffix:semicolon
id|carry
op_assign
(paren
id|csum
OL
id|daddr-&gt;s6_addr32
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|csum
op_add_assign
id|carry
suffix:semicolon
id|csum
op_add_assign
id|daddr-&gt;s6_addr32
(braket
l_int|3
)braket
suffix:semicolon
id|carry
op_assign
(paren
id|csum
OL
id|daddr-&gt;s6_addr32
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|csum
op_add_assign
id|carry
suffix:semicolon
id|ulen
op_assign
id|htonl
c_func
(paren
(paren
id|__u32
)paren
id|len
)paren
suffix:semicolon
id|csum
op_add_assign
id|ulen
suffix:semicolon
id|carry
op_assign
(paren
id|csum
OL
id|ulen
)paren
suffix:semicolon
id|csum
op_add_assign
id|carry
suffix:semicolon
id|uproto
op_assign
id|htonl
c_func
(paren
id|proto
)paren
suffix:semicolon
id|csum
op_add_assign
id|uproto
suffix:semicolon
id|carry
op_assign
(paren
id|csum
OL
id|uproto
)paren
suffix:semicolon
id|csum
op_add_assign
id|carry
suffix:semicolon
r_return
id|csum_fold
c_func
(paren
id|csum
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef _HAVE_ARCH_COPY_AND_CSUM_FROM_USER
r_static
r_inline
DECL|function|csum_and_copy_from_user
r_int
r_int
id|csum_and_copy_from_user
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
id|sum
comma
r_int
op_star
id|err_ptr
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|src
comma
id|len
)paren
op_eq
l_int|0
)paren
r_return
id|csum_partial_copy_from_user
c_func
(paren
id|src
comma
id|dst
comma
id|len
comma
id|sum
comma
id|err_ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
op_star
id|err_ptr
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef HAVE_CSUM_COPY_USER
DECL|function|csum_and_copy_to_user
r_static
id|__inline__
r_int
r_int
id|csum_and_copy_to_user
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
id|err_ptr
)paren
(brace
id|sum
op_assign
id|csum_partial
c_func
(paren
id|src
comma
id|len
comma
id|sum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|dst
comma
id|len
)paren
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|dst
comma
id|src
comma
id|len
)paren
op_eq
l_int|0
)paren
r_return
id|sum
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
)paren
op_star
id|err_ptr
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* invalid checksum */
)brace
macro_line|#endif
DECL|function|csum_add
r_static
r_inline
r_int
r_int
id|csum_add
c_func
(paren
r_int
r_int
id|csum
comma
r_int
r_int
id|addend
)paren
(brace
id|csum
op_add_assign
id|addend
suffix:semicolon
r_return
id|csum
op_plus
(paren
id|csum
OL
id|addend
)paren
suffix:semicolon
)brace
DECL|function|csum_sub
r_static
r_inline
r_int
r_int
id|csum_sub
c_func
(paren
r_int
r_int
id|csum
comma
r_int
r_int
id|addend
)paren
(brace
r_return
id|csum_add
c_func
(paren
id|csum
comma
op_complement
id|addend
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|csum_block_add
id|csum_block_add
c_func
(paren
r_int
r_int
id|csum
comma
r_int
r_int
id|csum2
comma
r_int
id|offset
)paren
(brace
r_if
c_cond
(paren
id|offset
op_amp
l_int|1
)paren
id|csum2
op_assign
(paren
(paren
id|csum2
op_amp
l_int|0xFF00FF
)paren
op_lshift
l_int|8
)paren
op_plus
(paren
(paren
id|csum2
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF00FF
)paren
suffix:semicolon
r_return
id|csum_add
c_func
(paren
id|csum
comma
id|csum2
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|csum_block_sub
id|csum_block_sub
c_func
(paren
r_int
r_int
id|csum
comma
r_int
r_int
id|csum2
comma
r_int
id|offset
)paren
(brace
r_if
c_cond
(paren
id|offset
op_amp
l_int|1
)paren
id|csum2
op_assign
(paren
(paren
id|csum2
op_amp
l_int|0xFF00FF
)paren
op_lshift
l_int|8
)paren
op_plus
(paren
(paren
id|csum2
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF00FF
)paren
suffix:semicolon
r_return
id|csum_sub
c_func
(paren
id|csum
comma
id|csum2
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
