macro_line|#ifndef __SPARC_IPSUM_H
DECL|macro|__SPARC_IPSUM_H
mdefine_line|#define __SPARC_IPSUM_H
multiline_comment|/*  ipsum.h:  IP/UDP/TCP checksum routines on the Sparc.&n; *&n; *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/*&n; *      This routine computes a UDP checksum. &n; */
DECL|function|udp_check
r_extern
r_inline
r_int
r_int
id|udp_check
c_func
(paren
r_struct
id|udphdr
op_star
id|uh
comma
r_int
id|len
comma
id|u32
id|saddr
comma
id|u32
id|daddr
)paren
(brace
multiline_comment|/* uhh.. eventually */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *      This routine computes a TCP checksum. &n; */
DECL|function|tcp_check
r_extern
r_inline
r_int
r_int
id|tcp_check
c_func
(paren
r_struct
id|tcphdr
op_star
id|th
comma
r_int
id|len
comma
id|u32
id|saddr
comma
id|u32
id|daddr
)paren
(brace
multiline_comment|/* uhh.. eventually */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine does all the checksum computations that don&squot;t&n; * require anything special (like copying or special headers).&n; */
DECL|function|ip_compute_csum
r_extern
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
multiline_comment|/* uhh.. eventually */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *      This is a version of ip_compute_csum() optimized for IP headers, which&n; *      always checksum on 4 octet boundaries.&n; */
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
id|buff
comma
r_int
id|wlen
)paren
(brace
multiline_comment|/* uhh.. eventually */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* !(__SPARC_IPSUM_H) */
eof
