macro_line|#ifndef _NET_RAWV6_H
DECL|macro|_NET_RAWV6_H
mdefine_line|#define _NET_RAWV6_H
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|rawv6_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
comma
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
r_struct
id|ipv6_options
op_star
id|opt
comma
r_int
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|rawv6_err
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|type
comma
r_int
id|code
comma
r_int
r_char
op_star
id|buff
comma
r_struct
id|in6_addr
op_star
id|saddr
comma
r_struct
id|in6_addr
op_star
id|daddr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
