macro_line|#ifndef _NET_DN_RAW_H
DECL|macro|_NET_DN_RAW_H
mdefine_line|#define _NET_DN_RAW_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DECNET_RAW
r_extern
r_struct
id|proto_ops
id|dn_raw_proto_ops
suffix:semicolon
r_extern
r_void
id|dn_raw_rx_nsp
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
id|dn_raw_rx_routing
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DECNET_MOP
r_extern
r_void
id|dn_raw_rx_mop
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_DECNET_MOP */
macro_line|#endif /* CONFIG_DECNET_RAW */
macro_line|#endif /* _NET_DN_RAW_H */
eof
