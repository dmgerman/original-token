macro_line|#ifndef __LINUX_IF_PACKET_H
DECL|macro|__LINUX_IF_PACKET_H
mdefine_line|#define __LINUX_IF_PACKET_H
DECL|struct|sockaddr_pkt
r_struct
id|sockaddr_pkt
(brace
DECL|member|spkt_family
r_int
r_int
id|spkt_family
suffix:semicolon
DECL|member|spkt_device
r_int
r_char
id|spkt_device
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|spkt_protocol
r_int
r_int
id|spkt_protocol
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sockaddr_ll
r_struct
id|sockaddr_ll
(brace
DECL|member|sll_family
r_int
r_int
id|sll_family
suffix:semicolon
DECL|member|sll_protocol
r_int
r_int
id|sll_protocol
suffix:semicolon
DECL|member|sll_ifindex
r_int
id|sll_ifindex
suffix:semicolon
DECL|member|sll_hatype
r_int
r_int
id|sll_hatype
suffix:semicolon
DECL|member|sll_pkttype
r_int
r_char
id|sll_pkttype
suffix:semicolon
DECL|member|sll_halen
r_int
r_char
id|sll_halen
suffix:semicolon
DECL|member|sll_addr
r_int
r_char
id|sll_addr
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Packet types */
DECL|macro|PACKET_HOST
mdefine_line|#define PACKET_HOST&t;&t;0&t;&t;/* To us&t;&t;*/
DECL|macro|PACKET_BROADCAST
mdefine_line|#define PACKET_BROADCAST&t;1&t;&t;/* To all&t;&t;*/
DECL|macro|PACKET_MULTICAST
mdefine_line|#define PACKET_MULTICAST&t;2&t;&t;/* To group&t;&t;*/
DECL|macro|PACKET_OTHERHOST
mdefine_line|#define PACKET_OTHERHOST&t;3&t;&t;/* To someone else &t;*/
DECL|macro|PACKET_OUTGOING
mdefine_line|#define PACKET_OUTGOING&t;&t;4&t;&t;/* Originated by us&t;*/&t;
DECL|macro|PACKET_NDISC
mdefine_line|#define PACKET_NDISC&t;&t;17&t;&t;/* Outgoing NDISC packet*/
multiline_comment|/* Packet socket options */
DECL|macro|PACKET_ADD_MEMBERSHIP
mdefine_line|#define PACKET_ADD_MEMBERSHIP&t;&t;1
DECL|macro|PACKET_DROP_MEMBERSHIP
mdefine_line|#define PACKET_DROP_MEMBERSHIP&t;&t;2
DECL|struct|packet_mreq
r_struct
id|packet_mreq
(brace
DECL|member|mr_ifindex
r_int
id|mr_ifindex
suffix:semicolon
DECL|member|mr_type
r_int
r_int
id|mr_type
suffix:semicolon
DECL|member|mr_alen
r_int
r_int
id|mr_alen
suffix:semicolon
DECL|member|mr_address
r_int
r_char
id|mr_address
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PACKET_MR_MULTICAST
mdefine_line|#define PACKET_MR_MULTICAST&t;0
DECL|macro|PACKET_MR_PROMISC
mdefine_line|#define PACKET_MR_PROMISC&t;1
DECL|macro|PACKET_MR_ALLMULTI
mdefine_line|#define PACKET_MR_ALLMULTI&t;2
macro_line|#endif
eof
