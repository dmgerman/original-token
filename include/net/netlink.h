macro_line|#ifndef __NET_NETLINK_H
DECL|macro|__NET_NETLINK_H
mdefine_line|#define __NET_NETLINK_H
DECL|macro|NET_MAJOR
mdefine_line|#define NET_MAJOR 36&t;&t;/* Major 18 is reserved for networking &t;&t;&t;&t;&t;&t;*/
multiline_comment|/* so....                                ^^ is this 36? */
multiline_comment|/* and the things below... */
DECL|macro|MAX_LINKS
mdefine_line|#define MAX_LINKS 16&t;&t;/* 18,0 for route updates, 18,1 for SKIP, 18,2 debug tap 18,3 PPP reserved &t;*/
multiline_comment|/* 4-7 are psi0-psi3  8 is arpd 9 is ppp */
multiline_comment|/* 10 is for IPSEC &lt;John Ioannidis&gt; */
multiline_comment|/* 11 IPv6 route updates&t;&t;*/
multiline_comment|/* 12 is for firewall trapout&t;*/
DECL|macro|MAX_QBYTES
mdefine_line|#define MAX_QBYTES 32768&t;/* Maximum bytes in the queue &t;&t;&t;&t;&t;&t;&t;*/
macro_line|#include &lt;linux/netlink.h&gt;
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
r_int
comma
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
r_int
comma
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
multiline_comment|/*&n; *&t;skb should fit one page. This choice is good for headerless malloc.&n; */
DECL|macro|NLMSG_GOODSIZE
mdefine_line|#define NLMSG_GOODSIZE (PAGE_SIZE - ((sizeof(struct sk_buff)+0xF)&amp;~0xF))
DECL|macro|NLMSG_RECOVERY_TIMEO
mdefine_line|#define NLMSG_RECOVERY_TIMEO&t;(HZ/2)&t;&t;/* If deleivery was failed,&n;&t;&t;&t;&t;&t;&t;   retry after */
DECL|struct|nlmsg_ctl
r_struct
id|nlmsg_ctl
(brace
DECL|member|nlmsg_timer
r_struct
id|timer_list
id|nlmsg_timer
suffix:semicolon
DECL|member|nlmsg_skb
r_struct
id|sk_buff
op_star
id|nlmsg_skb
suffix:semicolon
multiline_comment|/* Partially built skb&t;*/
DECL|member|nlmsg_unit
r_int
id|nlmsg_unit
suffix:semicolon
DECL|member|nlmsg_delay
r_int
id|nlmsg_delay
suffix:semicolon
multiline_comment|/* Time to delay skb send*/
DECL|member|nlmsg_maxsize
r_int
id|nlmsg_maxsize
suffix:semicolon
multiline_comment|/* Maximal message size  */
DECL|member|nlmsg_force
r_int
id|nlmsg_force
suffix:semicolon
multiline_comment|/* post immediately&t; */
DECL|member|nlmsg_overrun_start
r_int
r_int
id|nlmsg_overrun_start
suffix:semicolon
multiline_comment|/* seqno starting lossage*/
DECL|member|nlmsg_overrun_end
r_int
r_int
id|nlmsg_overrun_end
suffix:semicolon
multiline_comment|/* the last lost message */
DECL|member|nlmsg_overrun
r_char
id|nlmsg_overrun
suffix:semicolon
multiline_comment|/* overrun flag&t;&t; */
)brace
suffix:semicolon
r_void
op_star
id|nlmsg_send
c_func
(paren
r_struct
id|nlmsg_ctl
op_star
comma
r_int
r_int
id|type
comma
r_int
id|len
comma
r_int
r_int
id|seq
comma
r_int
r_int
id|pid
)paren
suffix:semicolon
r_void
id|nlmsg_transmit
c_func
(paren
r_struct
id|nlmsg_ctl
op_star
)paren
suffix:semicolon
DECL|function|nlmsg_ack
r_extern
id|__inline__
r_void
id|nlmsg_ack
c_func
(paren
r_struct
id|nlmsg_ctl
op_star
id|ctl
comma
r_int
r_int
id|seq
comma
r_int
r_int
id|pid
comma
r_int
id|err
)paren
(brace
r_int
op_star
id|r
suffix:semicolon
id|start_bh_atomic
c_func
(paren
)paren
suffix:semicolon
id|r
op_assign
id|nlmsg_send
c_func
(paren
id|ctl
comma
id|NLMSG_ACK
comma
r_sizeof
(paren
id|r
)paren
comma
id|seq
comma
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
op_star
id|r
op_assign
id|err
suffix:semicolon
id|end_bh_atomic
c_func
(paren
)paren
suffix:semicolon
)brace
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
DECL|macro|NETLINK_IPSEC
mdefine_line|#define NETLINK_IPSEC&t;&t;10&t;/* IPSEC */
DECL|macro|NETLINK_ROUTE6
mdefine_line|#define NETLINK_ROUTE6&t;&t;11&t;/* af_inet6 route comm channel */
multiline_comment|/* Wouldn&squot;t this suffice instead of the confusion at the top of&n;   this file?  i.e. 3 is firewall or ppp... */
multiline_comment|/* #define MAX_LINKS&t;&t;16 */
macro_line|#endif
eof
