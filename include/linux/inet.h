multiline_comment|/*&n; *&t;&t;Swansea University Computer Society NET3&n; *&n; *&t;This work is derived from NET2Debugged, which is in turn derived&n; *&t;from NET2D which was written by:&n; * &t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This work was derived friom Ross Biro&squot;s inspirational work&n; *&t;&t;for the LINUX operating system.  His version numbers were:&n; *&n; *&t;&t;$Id: Space.c,v     0.8.4.5  1992/12/12 19:25:04 bir7 Exp $&n; *&t;&t;$Id: arp.c,v       0.8.4.6  1993/01/28 22:30:00 bir7 Exp $&n; *&t;&t;$Id: arp.h,v       0.8.4.6  1993/01/28 22:30:00 bir7 Exp $&n; *&t;&t;$Id: dev.c,v       0.8.4.13 1993/01/23 18:00:11 bir7 Exp $&n; *&t;&t;$Id: dev.h,v       0.8.4.7  1993/01/23 18:00:11 bir7 Exp $&n; *&t;&t;$Id: eth.c,v       0.8.4.4  1993/01/22 23:21:38 bir7 Exp $&n; *&t;&t;$Id: eth.h,v       0.8.4.1  1992/11/10 00:17:18 bir7 Exp $&n; *&t;&t;$Id: icmp.c,v      0.8.4.9  1993/01/23 18:00:11 bir7 Exp $&n; *&t;&t;$Id: icmp.h,v      0.8.4.2  1992/11/15 14:55:30 bir7 Exp $&n; * &t;&t;$Id: ip.c,v        0.8.4.8  1992/12/12 19:25:04 bir7 Exp $&n; * &t;&t;$Id: ip.h,v        0.8.4.2  1993/01/23 18:00:11 bir7 Exp $&n; * &t;&t;$Id: loopback.c,v  0.8.4.8  1993/01/23 18:00:11 bir7 Exp $&n; * &t;&t;$Id: packet.c,v    0.8.4.7  1993/01/26 22:04:00 bir7 Exp $&n; *&t;&t;$Id: protocols.c,v 0.8.4.3  1992/11/15 14:55:30 bir7 Exp $&n; *&t;&t;$Id: raw.c,v       0.8.4.12 1993/01/26 22:04:00 bir7 Exp $&n; *&t;&t;$Id: sock.c,v      0.8.4.6  1993/01/28 22:30:00 bir7 Exp $&n; *&t;&t;$Id: sock.h,v      0.8.4.7  1993/01/26 22:04:00 bir7 Exp $&n; *&t;&t;$Id: tcp.c,v       0.8.4.16 1993/01/26 22:04:00 bir7 Exp $&n; *&t;&t;$Id: tcp.h,v       0.8.4.7  1993/01/22 22:58:08 bir7 Exp $&n; *&t;&t;$Id: timer.c,v     0.8.4.8  1993/01/23 18:00:11 bir7 Exp $&n; *&t;&t;$Id: timer.h,v     0.8.4.2  1993/01/23 18:00:11 bir7 Exp $&n; *&t;&t;$Id: udp.c,v       0.8.4.12 1993/01/26 22:04:00 bir7 Exp $&n; *&t;&t;$Id: udp.h,v       0.8.4.1  1992/11/10 00:17:18 bir7 Exp $&n; *&t;&t;$Id: we.c,v        0.8.4.10 1993/01/23 18:00:11 bir7 Exp $&n; *&t;&t;$Id: wereg.h,v     0.8.4.1  1992/11/10 00:17:18 bir7 Exp $&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_INET_H
DECL|macro|_LINUX_INET_H
mdefine_line|#define _LINUX_INET_H
macro_line|#include &lt;linux/ddi.h&gt;
DECL|macro|INET_DEBUG
macro_line|#undef&t;INET_DEBUG
macro_line|#ifdef&t;INET_DEBUG
DECL|macro|DPRINTF
macro_line|#  define&t;DPRINTF(x)&t;dprintf x 
macro_line|#else
DECL|macro|DPRINTF
macro_line|#   define&t;DPRINTF(x)&t;do ; while (0)
macro_line|#endif
multiline_comment|/* Debug levels. One per module. */
DECL|macro|DBG_OFF
mdefine_line|#define DBG_OFF&t;&t;0&t;&t;&t;/* no debugging&t;&t;*/
DECL|macro|DBG_INET
mdefine_line|#define DBG_INET&t;1&t;&t;&t;/* sock.c&t;&t;*/
DECL|macro|DBG_RT
mdefine_line|#define DBG_RT&t;&t;2&t;&t;&t;/* route.c&t;&t;*/
DECL|macro|DBG_DEV
mdefine_line|#define DBG_DEV&t;&t;3&t;&t;&t;/* dev.c&t;&t;*/
DECL|macro|DBG_ETH
mdefine_line|#define DBG_ETH&t;&t;4&t;&t;&t;/* eth.c&t;&t;*/
DECL|macro|DBG_PROTO
mdefine_line|#define DBG_PROTO&t;5&t;&t;&t;/* protocol.c&t;&t;*/
DECL|macro|DBG_TMR
mdefine_line|#define DBG_TMR&t;&t;6&t;&t;&t;/* timer.c&t;&t;*/
DECL|macro|DBG_PKT
mdefine_line|#define DBG_PKT&t;&t;7&t;&t;&t;/* packet.c&t;&t;*/
DECL|macro|DBG_RAW
mdefine_line|#define DBG_RAW&t;&t;8&t;&t;&t;/* raw.c&t;&t;*/
DECL|macro|DBG_LOOPB
mdefine_line|#define DBG_LOOPB&t;10&t;&t;&t;/* loopback.c&t;&t;*/
DECL|macro|DBG_SLIP
mdefine_line|#define DBG_SLIP&t;11&t;&t;&t;/* slip.c&t;&t;*/
DECL|macro|DBG_ARP
mdefine_line|#define DBG_ARP&t;&t;20&t;&t;&t;/* arp.c&t;&t;*/
DECL|macro|DBG_IP
mdefine_line|#define DBG_IP&t;&t;21&t;&t;&t;/* ip.c&t;&t;&t;*/
DECL|macro|DBG_ICMP
mdefine_line|#define DBG_ICMP&t;22&t;&t;&t;/* icmp.c&t;&t;*/
DECL|macro|DBG_TCP
mdefine_line|#define DBG_TCP&t;&t;23&t;&t;&t;/* tcp.c&t;&t;*/
DECL|macro|DBG_UDP
mdefine_line|#define DBG_UDP&t;&t;24&t;&t;&t;/* udp.c&t;&t;*/
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|inet_debug
suffix:semicolon
r_extern
r_void
id|inet_proto_init
c_func
(paren
r_struct
id|ddi_proto
op_star
id|pro
)paren
suffix:semicolon
r_extern
r_char
op_star
id|in_ntoa
c_func
(paren
r_int
r_int
id|in
)paren
suffix:semicolon
r_extern
r_int
r_int
id|in_aton
c_func
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
r_extern
r_void
id|dprintf
c_func
(paren
r_int
id|level
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_int
id|dbg_ioctl
c_func
(paren
r_void
op_star
id|arg
comma
r_int
id|level
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* _LINUX_INET_H */
eof
