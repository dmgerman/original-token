macro_line|#ifndef _I386_CHECKSUM_H
DECL|macro|_I386_CHECKSUM_H
mdefine_line|#define _I386_CHECKSUM_H
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * computes the checksum of a memory block at buff, length len,&n; * and adds in &quot;sum&quot; (32-bit)&n; *&n; * returns a 32-bit number suitable for feeding into itself&n; * or csum_tcpudp_magic&n; *&n; * this function must be called with even lengths, except&n; * for the last fragment, which may be odd&n; *&n; * it&squot;s best to have buff aligned on a 32-bit boundary&n; */
r_extern
r_int
r_int
id|csum_partial
(paren
r_const
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
multiline_comment|/*&n; * the same as csum_partial, but copies from src while it&n; * checksums, and handles user-space pointer exceptions correctly, when needed.&n; *&n; * here even more important to align src and dst on a 32-bit (or even&n; * better 64-bit) boundary&n; */
r_int
r_int
id|__csum_partial_copy_i386_generic
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
id|sum
comma
r_int
op_star
id|src_err_ptr
comma
r_int
op_star
id|dst_err_ptr
)paren
suffix:semicolon
r_extern
id|__inline__
DECL|function|csum_partial_copy_nocheck
r_int
r_int
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
id|sum
)paren
(brace
r_int
op_star
id|src_err_ptr
op_assign
l_int|NULL
comma
op_star
id|dst_err_ptr
op_assign
l_int|NULL
suffix:semicolon
r_return
id|__csum_partial_copy_i386_generic
(paren
id|src
comma
id|dst
comma
id|len
comma
id|sum
comma
id|src_err_ptr
comma
id|dst_err_ptr
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
DECL|function|csum_partial_copy_from_user
r_int
r_int
id|csum_partial_copy_from_user
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
r_int
op_star
id|dst_err_ptr
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * If the source address is invalid, force an exception via NULL pointer.&n; * The point of this solution is to make the code smaller. The exception path&n; * doesnt have to be fast.&n; */
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|src
comma
id|len
)paren
)paren
id|src
op_assign
l_int|NULL
suffix:semicolon
r_return
id|__csum_partial_copy_i386_generic
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
comma
id|dst_err_ptr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This combination is currently not used, but possible:&n; */
r_extern
id|__inline__
DECL|function|csum_partial_copy_to_user
r_int
r_int
id|csum_partial_copy_to_user
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
r_int
op_star
id|src_err_ptr
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
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
id|dst
op_assign
l_int|NULL
suffix:semicolon
r_return
id|__csum_partial_copy_i386_generic
(paren
id|src
comma
id|dst
comma
id|len
comma
id|sum
comma
id|src_err_ptr
comma
id|err_ptr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the old (and unsafe) way of doing checksums, a warning message will be&n; * printed if they are used and an exeption occurs.&n; *&n; * these functions should go away after some time.&n; */
DECL|macro|csum_partial_copy_fromuser
mdefine_line|#define csum_partial_copy_fromuser csum_partial_copy
r_int
r_int
id|csum_partial_copy
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
id|sum
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;This is a version of ip_compute_csum() optimized for IP headers,&n; *&t;which always checksum on 4 octet boundaries.&n; *&n; *&t;By Jorge Cwik &lt;jorge@laser.satlink.net&gt;, adapted for linux by&n; *&t;Arnt Gulbrandsen.&n; */
DECL|function|ip_fast_csum
r_static
r_inline
r_int
r_int
id|ip_fast_csum
c_func
(paren
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
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|movl
(paren
op_mod
l_int|1
)paren
comma
op_mod
l_int|0
id|subl
"$"
l_int|4
comma
op_mod
l_int|2
id|jbe
l_float|2f
id|addl
l_int|4
(paren
op_mod
l_int|1
)paren
comma
op_mod
l_int|0
id|adcl
l_int|8
(paren
op_mod
l_int|1
)paren
comma
op_mod
l_int|0
id|adcl
l_int|12
(paren
op_mod
l_int|1
)paren
comma
op_mod
l_int|0
l_int|1
suffix:colon
id|adcl
l_int|16
(paren
op_mod
l_int|1
)paren
comma
op_mod
l_int|0
id|lea
l_int|4
(paren
op_mod
l_int|1
)paren
comma
op_mod
l_int|1
id|decl
op_mod
l_int|2
id|jne
l_int|1
id|b
id|adcl
"$"
l_int|0
comma
op_mod
l_int|0
id|movl
op_mod
l_int|0
comma
op_mod
l_int|2
id|shrl
"$"
l_int|16
comma
op_mod
l_int|0
id|addw
op_mod
id|w2
comma
op_mod
id|w0
id|adcl
"$"
l_int|0
comma
op_mod
l_int|0
id|notl
op_mod
l_int|0
l_int|2
suffix:colon
"&quot;"
multiline_comment|/* Since the input registers which are loaded with iph and ipl&n;&t;   are modified, we must also specify them as outputs, or gcc&n;&t;   will assume they contain their original values. */
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=r&quot;
(paren
id|iph
)paren
comma
l_string|&quot;=r&quot;
(paren
id|ihl
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|iph
)paren
comma
l_string|&quot;2&quot;
(paren
id|ihl
)paren
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Fold a partial checksum&n; */
DECL|function|csum_fold
r_static
r_inline
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
id|__asm__
c_func
(paren
"&quot;"
id|addl
op_mod
l_int|1
comma
op_mod
l_int|0
id|adcl
"$"
l_int|0xffff
comma
op_mod
l_int|0
"&quot;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|sum
op_lshift
l_int|16
)paren
comma
l_string|&quot;0&quot;
(paren
id|sum
op_amp
l_int|0xffff0000
)paren
)paren
suffix:semicolon
r_return
(paren
op_complement
id|sum
)paren
op_rshift
l_int|16
suffix:semicolon
)brace
multiline_comment|/*&n; * computes the checksum of the TCP/UDP pseudo-header&n; * returns a 16-bit checksum, already complemented&n; */
DECL|function|csum_tcpudp_magic
r_static
r_inline
r_int
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
c_func
(paren
"&quot;"
id|addl
op_mod
l_int|1
comma
op_mod
l_int|0
id|adcl
op_mod
l_int|2
comma
op_mod
l_int|0
id|adcl
op_mod
l_int|3
comma
op_mod
l_int|0
id|adcl
"$"
l_int|0
comma
op_mod
l_int|0
"&quot;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;g&quot;
(paren
id|daddr
)paren
comma
l_string|&quot;g&quot;
(paren
id|saddr
)paren
comma
l_string|&quot;g&quot;
(paren
(paren
id|ntohs
c_func
(paren
id|len
)paren
op_lshift
l_int|16
)paren
op_plus
id|proto
op_star
l_int|256
)paren
comma
l_string|&quot;0&quot;
(paren
id|sum
)paren
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
multiline_comment|/*&n; * this routine is used for miscellaneous IP-like checksums, mainly&n; * in icmp.c&n; */
DECL|function|ip_compute_csum
r_static
r_inline
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
c_func
(paren
"&quot;"
id|addl
l_int|0
(paren
op_mod
l_int|1
)paren
comma
op_mod
l_int|0
id|adcl
l_int|4
(paren
op_mod
l_int|1
)paren
comma
op_mod
l_int|0
id|adcl
l_int|8
(paren
op_mod
l_int|1
)paren
comma
op_mod
l_int|0
id|adcl
l_int|12
(paren
op_mod
l_int|1
)paren
comma
op_mod
l_int|0
id|adcl
l_int|0
(paren
op_mod
l_int|2
)paren
comma
op_mod
l_int|0
id|adcl
l_int|4
(paren
op_mod
l_int|2
)paren
comma
op_mod
l_int|0
id|adcl
l_int|8
(paren
op_mod
l_int|2
)paren
comma
op_mod
l_int|0
id|adcl
l_int|12
(paren
op_mod
l_int|2
)paren
comma
op_mod
l_int|0
id|adcl
op_mod
l_int|3
comma
op_mod
l_int|0
id|adcl
op_mod
l_int|4
comma
op_mod
l_int|0
id|adcl
"$"
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
l_string|&quot;0&quot;
(paren
id|sum
)paren
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
macro_line|#endif
eof
