macro_line|#ifndef __NET_NETLINK_H
DECL|macro|__NET_NETLINK_H
mdefine_line|#define __NET_NETLINK_H
DECL|macro|NET_MAJOR
mdefine_line|#define NET_MAJOR 36&t;&t;/* Major 18 is reserved for networking &t;&t;&t;&t;&t;&t;*/
DECL|macro|MAX_LINKS
mdefine_line|#define MAX_LINKS 12&t;&t;/* 18,0 for route updates, 18,1 for SKIP, 18,2 debug tap 18,3 PPP reserved &t;*/
multiline_comment|/* 4-7 are psi0-psi3  8 is arpd 9 is ppp */
multiline_comment|/* 10 is for IPSEC &lt;John Ioannidis&gt; */
multiline_comment|/* 11 IPv6 route updates&t;&t;*/
DECL|macro|MAX_QBYTES
mdefine_line|#define MAX_QBYTES 32768&t;/* Maximum bytes in the queue &t;&t;&t;&t;&t;&t;&t;*/
macro_line|#include &lt;linux/config.h&gt;
r_extern
r_int
id|netlink_attach
c_func
(paren
r_int
id|unit
comma
r_int
(paren
op_star
id|function
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
)paren
suffix:semicolon
r_extern
r_int
id|netlink_donothing
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|netlink_detach
c_func
(paren
r_int
id|unit
)paren
suffix:semicolon
r_extern
r_int
id|netlink_post
c_func
(paren
r_int
id|unit
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|init_netlink
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|NETLINK_ROUTE
mdefine_line|#define NETLINK_ROUTE&t;&t;0&t;/* Routing/device hook&t;&t;&t;&t;*/
DECL|macro|NETLINK_SKIP
mdefine_line|#define NETLINK_SKIP&t;&t;1&t;/* Reserved for ENskip  &t;&t;&t;*/
DECL|macro|NETLINK_USERSOCK
mdefine_line|#define NETLINK_USERSOCK&t;2&t;/* Reserved for user mode socket protocols &t;*/
DECL|macro|NETLINK_FIREWALL
mdefine_line|#define NETLINK_FIREWALL&t;3&t;/* Firewalling hook&t;&t;&t;&t;*/
DECL|macro|NETLINK_PSI
mdefine_line|#define NETLINK_PSI&t;&t;4&t;/* PSI devices - 4 to 7 */
DECL|macro|NETLINK_ARPD
mdefine_line|#define NETLINK_ARPD&t;&t;8
DECL|macro|NETLINK_NET_PPP
mdefine_line|#define NETLINK_NET_PPP&t;&t;9&t;/* Non tty PPP devices */
DECL|macro|NETLINK_IPSEC
mdefine_line|#define NETLINK_IPSEC&t;&t;10&t;/* IPSEC */
DECL|macro|NETLINK_ROUTE6
mdefine_line|#define NETLINK_ROUTE6&t;&t;11&t;/* af_inet6 route comm channel */
macro_line|#ifdef CONFIG_RTNETLINK
r_extern
r_void
id|ip_netlink_msg
c_func
(paren
r_int
r_int
comma
id|__u32
comma
id|__u32
comma
id|__u32
comma
r_int
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|ip_netlink_msg
mdefine_line|#define ip_netlink_msg(a,b,c,d,e,f,g)
macro_line|#endif
macro_line|#endif
eof
