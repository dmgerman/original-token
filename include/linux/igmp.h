multiline_comment|/*&n; *&t;Linux NET3:&t;Internet Gateway Management Protocol  [IGMP]&n; *&n; *&t;Authors:&n; *&t;&t;Alan Cox &lt;Alan.Cox@linux.org&gt;&t;&n; *&n; *&t;Extended to talk the BSD extended IGMP protocol of mrouted 3.6&n; *&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IGMP_H
DECL|macro|_LINUX_IGMP_H
mdefine_line|#define _LINUX_IGMP_H
multiline_comment|/*&n; *&t;IGMP protocol structures&n; */
multiline_comment|/*&n; *&t;Header in on cable format&n; */
DECL|struct|igmphdr
r_struct
id|igmphdr
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|code
id|__u8
id|code
suffix:semicolon
multiline_comment|/* For newer IGMP */
DECL|member|csum
id|__u16
id|csum
suffix:semicolon
DECL|member|group
id|__u32
id|group
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IGMP_HOST_MEMBERSHIP_QUERY
mdefine_line|#define IGMP_HOST_MEMBERSHIP_QUERY&t;0x11&t;/* From RFC1112 */
DECL|macro|IGMP_HOST_MEMBERSHIP_REPORT
mdefine_line|#define IGMP_HOST_MEMBERSHIP_REPORT&t;0x12&t;/* Ditto */
DECL|macro|IGMP_DVMRP
mdefine_line|#define IGMP_DVMRP&t;&t;&t;0x13&t;/* DVMRP routing */
DECL|macro|IGMP_PIM
mdefine_line|#define IGMP_PIM&t;&t;&t;0x14&t;/* PIM routing */
DECL|macro|IGMP_HOST_NEW_MEMBERSHIP_REPORT
mdefine_line|#define IGMP_HOST_NEW_MEMBERSHIP_REPORT&t;0x16&t;/* New version of 0x11 */
DECL|macro|IGMP_HOST_LEAVE_MESSAGE
mdefine_line|#define IGMP_HOST_LEAVE_MESSAGE&t;&t;0x17&t;/* An extra BSD seems to send */
DECL|macro|IGMP_MTRACE_RESP
mdefine_line|#define IGMP_MTRACE_RESP&t;&t;0x1e
DECL|macro|IGMP_MTRACE
mdefine_line|#define IGMP_MTRACE&t;&t;&t;0x1f
multiline_comment|/*&n; *&t;Use the BSD names for these for compatibility&n; */
DECL|macro|IGMP_DELAYING_MEMBER
mdefine_line|#define IGMP_DELAYING_MEMBER&t;&t;0x01
DECL|macro|IGMP_IDLE_MEMBER
mdefine_line|#define IGMP_IDLE_MEMBER&t;&t;0x02
DECL|macro|IGMP_LAZY_MEMBER
mdefine_line|#define IGMP_LAZY_MEMBER&t;&t;0x03
DECL|macro|IGMP_SLEEPING_MEMBER
mdefine_line|#define IGMP_SLEEPING_MEMBER&t;&t;0x04
DECL|macro|IGMP_AWAKENING_MEMBER
mdefine_line|#define IGMP_AWAKENING_MEMBER&t;&t;0x05
DECL|macro|IGMP_OLD_ROUTER
mdefine_line|#define IGMP_OLD_ROUTER&t;&t;&t;0x00
DECL|macro|IGMP_NEW_ROUTER
mdefine_line|#define IGMP_NEW_ROUTER&t;&t;&t;0x01
DECL|macro|IGMP_ALL_HOSTS
mdefine_line|#define IGMP_ALL_HOSTS&t;&t;htonl(0xE0000001L)
multiline_comment|/*&n; * struct for keeping the multicast list in&n; */
macro_line|#ifdef __KERNEL__
DECL|struct|ip_mc_socklist
r_struct
id|ip_mc_socklist
(brace
DECL|member|multiaddr
r_int
r_int
id|multiaddr
(braket
id|IP_MAX_MEMBERSHIPS
)braket
suffix:semicolon
multiline_comment|/* This is a speed trade off */
DECL|member|multidev
r_struct
id|device
op_star
id|multidev
(braket
id|IP_MAX_MEMBERSHIPS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ip_mc_list
r_struct
id|ip_mc_list
(brace
DECL|member|interface
r_struct
id|device
op_star
id|interface
suffix:semicolon
DECL|member|multiaddr
r_int
r_int
id|multiaddr
suffix:semicolon
DECL|member|next
r_struct
id|ip_mc_list
op_star
id|next
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|tm_running
r_int
id|tm_running
suffix:semicolon
DECL|member|users
r_int
id|users
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ip_mc_list
op_star
id|ip_mc_head
suffix:semicolon
r_extern
r_int
id|igmp_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|device
op_star
comma
r_struct
id|options
op_star
comma
id|__u32
comma
r_int
r_int
comma
id|__u32
comma
r_int
comma
r_struct
id|inet_protocol
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ip_mc_drop_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|ip_mc_join_group
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|ip_mc_leave_group
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|ip_mc_drop_socket
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_void
id|ip_mr_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
