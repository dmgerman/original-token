multiline_comment|/*&n; *&t;The following information is in its entirety obtained from:&n; *&n; *&t;Novell &squot;IPX Router Specification&squot; Version 1.10 &n; *&t;&t;Part No. 107-000029-001&n; *&n; *&t;Which is available from ftp.novell.com&n; */
macro_line|#ifndef _NET_INET_IPX_H_
DECL|macro|_NET_INET_IPX_H_
mdefine_line|#define _NET_INET_IPX_H_
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/datalink.h&gt;
macro_line|#include &lt;linux/ipx.h&gt;
r_typedef
r_struct
(brace
DECL|member|net
id|__u32
id|net
suffix:semicolon
DECL|member|node
id|__u8
id|node
(braket
id|IPX_NODE_LEN
)braket
suffix:semicolon
DECL|member|sock
id|__u16
id|sock
suffix:semicolon
DECL|typedef|ipx_address
)brace
id|ipx_address
suffix:semicolon
DECL|macro|ipx_broadcast_node
mdefine_line|#define ipx_broadcast_node&t;&quot;&bslash;377&bslash;377&bslash;377&bslash;377&bslash;377&bslash;377&quot;
DECL|macro|ipx_this_node
mdefine_line|#define ipx_this_node           &quot;&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&quot;
DECL|struct|ipxhdr
r_struct
id|ipxhdr
(brace
DECL|member|ipx_checksum
id|__u16
id|ipx_checksum
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|IPX_NO_CHECKSUM
mdefine_line|#define IPX_NO_CHECKSUM&t;0xFFFF
DECL|member|ipx_pktsize
id|__u16
id|ipx_pktsize
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|ipx_tctrl
id|__u8
id|ipx_tctrl
suffix:semicolon
DECL|member|ipx_type
id|__u8
id|ipx_type
suffix:semicolon
DECL|macro|IPX_TYPE_UNKNOWN
mdefine_line|#define IPX_TYPE_UNKNOWN&t;0x00
DECL|macro|IPX_TYPE_RIP
mdefine_line|#define IPX_TYPE_RIP&t;&t;0x01&t;/* may also be 0 */
DECL|macro|IPX_TYPE_SAP
mdefine_line|#define IPX_TYPE_SAP&t;&t;0x04&t;/* may also be 0 */
DECL|macro|IPX_TYPE_SPX
mdefine_line|#define IPX_TYPE_SPX&t;&t;0x05&t;/* Not yet implemented */
DECL|macro|IPX_TYPE_NCP
mdefine_line|#define IPX_TYPE_NCP&t;&t;0x11&t;/* $lots for docs on this (SPIT) */
DECL|macro|IPX_TYPE_PPROP
mdefine_line|#define IPX_TYPE_PPROP&t;&t;0x14&t;/* complicated flood fill brdcast [Not supported] */
DECL|member|ipx_dest
id|ipx_address
id|ipx_dest
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|ipx_source
id|ipx_address
id|ipx_source
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#include &lt;net/ipxcall.h&gt;
DECL|struct|ipx_interface
r_typedef
r_struct
id|ipx_interface
(brace
multiline_comment|/* IPX address */
DECL|member|if_netnum
id|__u32
id|if_netnum
suffix:semicolon
DECL|member|if_node
r_int
r_char
id|if_node
(braket
id|IPX_NODE_LEN
)braket
suffix:semicolon
multiline_comment|/* physical device info */
DECL|member|if_dev
r_struct
id|device
op_star
id|if_dev
suffix:semicolon
DECL|member|if_dlink
r_struct
id|datalink_proto
op_star
id|if_dlink
suffix:semicolon
DECL|member|if_dlink_type
r_int
r_int
id|if_dlink_type
suffix:semicolon
multiline_comment|/* socket support */
DECL|member|if_sknum
r_int
r_int
id|if_sknum
suffix:semicolon
DECL|member|if_sklist
r_struct
id|sock
op_star
id|if_sklist
suffix:semicolon
multiline_comment|/* administrative overhead */
DECL|member|if_ipx_offset
r_int
id|if_ipx_offset
suffix:semicolon
DECL|member|if_internal
r_int
r_char
id|if_internal
suffix:semicolon
DECL|member|if_primary
r_int
r_char
id|if_primary
suffix:semicolon
DECL|member|if_next
r_struct
id|ipx_interface
op_star
id|if_next
suffix:semicolon
DECL|typedef|ipx_interface
)brace
id|ipx_interface
suffix:semicolon
DECL|struct|ipx_route
r_typedef
r_struct
id|ipx_route
(brace
DECL|member|ir_net
id|__u32
id|ir_net
suffix:semicolon
DECL|member|ir_intrfc
id|ipx_interface
op_star
id|ir_intrfc
suffix:semicolon
DECL|member|ir_routed
r_int
r_char
id|ir_routed
suffix:semicolon
DECL|member|ir_router_node
r_int
r_char
id|ir_router_node
(braket
id|IPX_NODE_LEN
)braket
suffix:semicolon
DECL|member|ir_next
r_struct
id|ipx_route
op_star
id|ir_next
suffix:semicolon
DECL|typedef|ipx_route
)brace
id|ipx_route
suffix:semicolon
DECL|macro|IPX_MIN_EPHEMERAL_SOCKET
mdefine_line|#define IPX_MIN_EPHEMERAL_SOCKET&t;0x4000
DECL|macro|IPX_MAX_EPHEMERAL_SOCKET
mdefine_line|#define IPX_MAX_EPHEMERAL_SOCKET&t;0x7fff
macro_line|#endif /* def _NET_INET_IPX_H_ */
eof
