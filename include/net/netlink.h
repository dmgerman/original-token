DECL|macro|NET_MAJOR
mdefine_line|#define NET_MAJOR 18&t;&t;/* Major 18 is reserved for networking &t;&t;*/
DECL|macro|MAX_LINKS
mdefine_line|#define MAX_LINKS 3&t;&t;/* 18,0 for route updates, 18,1 for SKIP &t;*/
DECL|macro|MAX_QBYTES
mdefine_line|#define MAX_QBYTES 32768&t;/* Maximum bytes in the queue &t;&t;&t;*/
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
r_void
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
eof
