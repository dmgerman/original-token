multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions of the Internet Protocol.&n; *&n; * Version:&t;@(#)in.h&t;1.0.1&t;04/21/93&n; *&n; * Authors:&t;Original taken from the GNU Project &lt;netinet/in.h&gt; file.&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IN_H
DECL|macro|_LINUX_IN_H
mdefine_line|#define _LINUX_IN_H
multiline_comment|/* Standard well-defined IP protocols.  */
r_enum
(brace
DECL|enumerator|IPPROTO_IP
id|IPPROTO_IP
op_assign
l_int|0
comma
multiline_comment|/* Dummy protocol for TCP&t;&t;*/
DECL|enumerator|IPPROTO_ICMP
id|IPPROTO_ICMP
op_assign
l_int|1
comma
multiline_comment|/* Internet Control Message Protocol&t;*/
DECL|enumerator|IPPROTO_IGMP
id|IPPROTO_IGMP
op_assign
l_int|2
comma
multiline_comment|/* Internet Gateway Management Protocol */
DECL|enumerator|IPPROTO_TCP
id|IPPROTO_TCP
op_assign
l_int|6
comma
multiline_comment|/* Transmission Control Protocol&t;*/
DECL|enumerator|IPPROTO_EGP
id|IPPROTO_EGP
op_assign
l_int|8
comma
multiline_comment|/* Exterior Gateway Protocol&t;&t;*/
DECL|enumerator|IPPROTO_PUP
id|IPPROTO_PUP
op_assign
l_int|12
comma
multiline_comment|/* PUP protocol&t;&t;&t;&t;*/
DECL|enumerator|IPPROTO_UDP
id|IPPROTO_UDP
op_assign
l_int|17
comma
multiline_comment|/* User Datagram Protocol&t;&t;*/
DECL|enumerator|IPPROTO_IDP
id|IPPROTO_IDP
op_assign
l_int|22
comma
multiline_comment|/* XNS IDP protocol&t;&t;&t;*/
DECL|enumerator|IPPROTO_RAW
id|IPPROTO_RAW
op_assign
l_int|255
comma
multiline_comment|/* Raw IP packets&t;&t;&t;*/
DECL|enumerator|IPPROTO_MAX
id|IPPROTO_MAX
)brace
suffix:semicolon
multiline_comment|/* Internet address. */
DECL|struct|in_addr
r_struct
id|in_addr
(brace
DECL|member|s_addr
r_int
r_int
r_int
id|s_addr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Request struct for multicast socket ops */
DECL|struct|ip_mreq
r_struct
id|ip_mreq
(brace
DECL|member|imr_multiaddr
r_struct
id|in_addr
id|imr_multiaddr
suffix:semicolon
multiline_comment|/* IP multicast address of group */
DECL|member|imr_interface
r_struct
id|in_addr
id|imr_interface
suffix:semicolon
multiline_comment|/* local IP address of interface */
)brace
suffix:semicolon
multiline_comment|/* Structure describing an Internet (IP) socket address. */
DECL|macro|__SOCK_SIZE__
mdefine_line|#define __SOCK_SIZE__&t;16&t;&t;/* sizeof(struct sockaddr)&t;*/
DECL|struct|sockaddr_in
r_struct
id|sockaddr_in
(brace
DECL|member|sin_family
r_int
r_int
id|sin_family
suffix:semicolon
multiline_comment|/* Address family&t;&t;*/
DECL|member|sin_port
r_int
r_int
r_int
id|sin_port
suffix:semicolon
multiline_comment|/* Port number&t;&t;&t;*/
DECL|member|sin_addr
r_struct
id|in_addr
id|sin_addr
suffix:semicolon
multiline_comment|/* Internet address&t;&t;*/
multiline_comment|/* Pad to size of `struct sockaddr&squot;. */
DECL|member|__pad
r_int
r_char
id|__pad
(braket
id|__SOCK_SIZE__
op_minus
r_sizeof
(paren
r_int
r_int
)paren
op_minus
r_sizeof
(paren
r_int
r_int
r_int
)paren
op_minus
r_sizeof
(paren
r_struct
id|in_addr
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|sin_zero
mdefine_line|#define sin_zero&t;__pad&t;&t;/* for BSD UNIX comp. -FvK&t;*/
multiline_comment|/*&n; * Definitions of the bits in an Internet address integer.&n; * On subnets, host and network parts are found according&n; * to the subnet mask, not these masks.&n; */
DECL|macro|IN_CLASSA
mdefine_line|#define&t;IN_CLASSA(a)&t;&t;((((long int) (a)) &amp; 0x80000000) == 0)
DECL|macro|IN_CLASSA_NET
mdefine_line|#define&t;IN_CLASSA_NET&t;&t;0xff000000
DECL|macro|IN_CLASSA_NSHIFT
mdefine_line|#define&t;IN_CLASSA_NSHIFT&t;24
DECL|macro|IN_CLASSA_HOST
mdefine_line|#define&t;IN_CLASSA_HOST&t;&t;(0xffffffff &amp; ~IN_CLASSA_NET)
DECL|macro|IN_CLASSA_MAX
mdefine_line|#define&t;IN_CLASSA_MAX&t;&t;128
DECL|macro|IN_CLASSB
mdefine_line|#define&t;IN_CLASSB(a)&t;&t;((((long int) (a)) &amp; 0xc0000000) == 0x80000000)
DECL|macro|IN_CLASSB_NET
mdefine_line|#define&t;IN_CLASSB_NET&t;&t;0xffff0000
DECL|macro|IN_CLASSB_NSHIFT
mdefine_line|#define&t;IN_CLASSB_NSHIFT&t;16
DECL|macro|IN_CLASSB_HOST
mdefine_line|#define&t;IN_CLASSB_HOST&t;&t;(0xffffffff &amp; ~IN_CLASSB_NET)
DECL|macro|IN_CLASSB_MAX
mdefine_line|#define&t;IN_CLASSB_MAX&t;&t;65536
DECL|macro|IN_CLASSC
mdefine_line|#define&t;IN_CLASSC(a)&t;&t;((((long int) (a)) &amp; 0xc0000000) == 0xc0000000)
DECL|macro|IN_CLASSC_NET
mdefine_line|#define&t;IN_CLASSC_NET&t;&t;0xffffff00
DECL|macro|IN_CLASSC_NSHIFT
mdefine_line|#define&t;IN_CLASSC_NSHIFT&t;8
DECL|macro|IN_CLASSC_HOST
mdefine_line|#define&t;IN_CLASSC_HOST&t;&t;(0xffffffff &amp; ~IN_CLASSC_NET)
DECL|macro|IN_CLASSD
mdefine_line|#define&t;IN_CLASSD(a)&t;&t;((((long int) (a)) &amp; 0xf0000000) == 0xe0000000)
DECL|macro|IN_MULTICAST
mdefine_line|#define&t;IN_MULTICAST(a)&t;&t;IN_CLASSD(a)
DECL|macro|IN_EXPERIMENTAL
mdefine_line|#define&t;IN_EXPERIMENTAL(a)&t;((((long int) (a)) &amp; 0xe0000000) == 0xe0000000)
DECL|macro|IN_BADCLASS
mdefine_line|#define&t;IN_BADCLASS(a)&t;&t;((((long int) (a)) &amp; 0xf0000000) == 0xf0000000)
multiline_comment|/* Address to accept any incoming messages. */
DECL|macro|INADDR_ANY
mdefine_line|#define&t;INADDR_ANY&t;&t;((unsigned long int) 0x00000000)
multiline_comment|/* Address to send to all hosts. */
DECL|macro|INADDR_BROADCAST
mdefine_line|#define&t;INADDR_BROADCAST&t;((unsigned long int) 0xffffffff)
multiline_comment|/* Address indicating an error return. */
DECL|macro|INADDR_NONE
mdefine_line|#define&t;INADDR_NONE&t;&t;0xffffffff
multiline_comment|/* Network number for local host loopback. */
DECL|macro|IN_LOOPBACKNET
mdefine_line|#define&t;IN_LOOPBACKNET&t;&t;127
multiline_comment|/* Address to loopback in software to local host.  */
DECL|macro|INADDR_LOOPBACK
mdefine_line|#define&t;INADDR_LOOPBACK&t;&t;0x7f000001&t;/* 127.0.0.1&t;&t;*/
multiline_comment|/*&n; * Options for use with `getsockopt&squot; and `setsockopt&squot; at&n; * the IP level.  LINUX does not yet have the IP_OPTIONS&n; * option (grin), so we undefine it for now.- HJ &amp;&amp; FvK&n; */
macro_line|#if 0
macro_line|# define IP_OPTIONS&t;1&t;&t;/* IP per-packet options&t;*/
macro_line|#endif
DECL|macro|IP_HDRINCL
mdefine_line|#define IP_HDRINCL&t;2&t;&t;/* raw packet header option&t;*/
multiline_comment|/* Linux Internet number representation function declarations. */
DECL|macro|ntohl
macro_line|#undef ntohl
DECL|macro|ntohs
macro_line|#undef ntohs
DECL|macro|htonl
macro_line|#undef htonl
DECL|macro|htons
macro_line|#undef htons
r_extern
r_int
r_int
r_int
id|ntohl
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
r_int
id|ntohs
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
r_int
id|htonl
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
r_int
id|htons
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
r_extern
id|__inline__
r_int
r_int
r_int
DECL|function|__ntohl
id|__ntohl
c_func
(paren
r_int
r_int
r_int
id|x
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;xchgb %b0,%h0&bslash;n&bslash;t&quot;
multiline_comment|/* swap lower bytes&t;*/
l_string|&quot;rorl $16,%0&bslash;n&bslash;t&quot;
multiline_comment|/* swap words&t;&t;*/
l_string|&quot;xchgb %b0,%h0&quot;
multiline_comment|/* swap higher bytes&t;*/
suffix:colon
l_string|&quot;=q&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
r_int
r_int
DECL|function|__constant_ntohl
id|__constant_ntohl
c_func
(paren
r_int
r_int
r_int
id|x
)paren
(brace
r_return
(paren
(paren
(paren
id|x
op_amp
l_int|0x000000ffU
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0x0000ff00U
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0x00ff0000U
)paren
op_rshift
l_int|8
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0xff000000U
)paren
op_rshift
l_int|24
)paren
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
r_int
r_int
DECL|function|__ntohs
id|__ntohs
c_func
(paren
r_int
r_int
r_int
id|x
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;xchgb %b0,%h0&quot;
multiline_comment|/* swap bytes&t;&t;*/
suffix:colon
l_string|&quot;=q&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
r_int
r_int
DECL|function|__constant_ntohs
id|__constant_ntohs
c_func
(paren
r_int
r_int
r_int
id|x
)paren
(brace
r_return
(paren
(paren
(paren
id|x
op_amp
l_int|0x00ff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
)brace
DECL|macro|__htonl
mdefine_line|#define __htonl(x) __ntohl(x)
DECL|macro|__htons
mdefine_line|#define __htons(x) __ntohs(x)
DECL|macro|__constant_htonl
mdefine_line|#define __constant_htonl(x) __constant_ntohl(x)
DECL|macro|__constant_htons
mdefine_line|#define __constant_htons(x) __constant_ntohs(x)
macro_line|#ifdef  __OPTIMIZE__
DECL|macro|ntohl
macro_line|#  define ntohl(x) &bslash;&n;(__builtin_constant_p((long)(x)) ? &bslash;&n; __constant_ntohl((x)) : &bslash;&n; __ntohl((x)))
DECL|macro|ntohs
macro_line|#  define ntohs(x) &bslash;&n;(__builtin_constant_p((short)(x)) ? &bslash;&n; __constant_ntohs((x)) : &bslash;&n; __ntohs((x)))
DECL|macro|htonl
macro_line|#  define htonl(x) &bslash;&n;(__builtin_constant_p((long)(x)) ? &bslash;&n; __constant_htonl((x)) : &bslash;&n; __htonl((x)))
DECL|macro|htons
macro_line|#  define htons(x) &bslash;&n;(__builtin_constant_p((short)(x)) ? &bslash;&n; __constant_htons((x)) : &bslash;&n; __htons((x)))
macro_line|#endif
macro_line|#endif&t;/* _LINUX_IN_H */
eof
