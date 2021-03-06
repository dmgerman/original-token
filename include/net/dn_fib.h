macro_line|#ifndef _NET_DN_FIB_H
DECL|macro|_NET_DN_FIB_H
mdefine_line|#define _NET_DN_FIB_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DECNET_ROUTER
macro_line|#include &lt;linux/rtnetlink.h&gt;
DECL|struct|dn_kern_rta
r_struct
id|dn_kern_rta
(brace
DECL|member|rta_dst
r_void
op_star
id|rta_dst
suffix:semicolon
DECL|member|rta_src
r_void
op_star
id|rta_src
suffix:semicolon
DECL|member|rta_iif
r_int
op_star
id|rta_iif
suffix:semicolon
DECL|member|rta_oif
r_int
op_star
id|rta_oif
suffix:semicolon
DECL|member|rta_gw
r_void
op_star
id|rta_gw
suffix:semicolon
DECL|member|rta_priority
id|u32
op_star
id|rta_priority
suffix:semicolon
DECL|member|rta_prefsrc
r_void
op_star
id|rta_prefsrc
suffix:semicolon
DECL|member|rta_mx
r_struct
id|rtattr
op_star
id|rta_mx
suffix:semicolon
DECL|member|rta_mp
r_struct
id|rtattr
op_star
id|rta_mp
suffix:semicolon
DECL|member|rta_protoinfo
r_int
r_char
op_star
id|rta_protoinfo
suffix:semicolon
DECL|member|rta_flow
r_int
r_char
op_star
id|rta_flow
suffix:semicolon
DECL|member|rta_ci
r_struct
id|rta_cacheinfo
op_star
id|rta_ci
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dn_fib_key
r_struct
id|dn_fib_key
(brace
DECL|member|src
id|dn_address
id|src
suffix:semicolon
DECL|member|dst
id|dn_address
id|dst
suffix:semicolon
DECL|member|iif
r_int
id|iif
suffix:semicolon
DECL|member|oif
r_int
id|oif
suffix:semicolon
DECL|member|fwmark
id|u32
id|fwmark
suffix:semicolon
DECL|member|scope
r_int
r_char
id|scope
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dn_fib_res
r_struct
id|dn_fib_res
(brace
DECL|member|r
r_struct
id|dn_fib_rule
op_star
id|r
suffix:semicolon
DECL|member|fi
r_struct
id|dn_fib_info
op_star
id|fi
suffix:semicolon
DECL|member|prefixlen
r_int
r_char
id|prefixlen
suffix:semicolon
DECL|member|nh_sel
r_int
r_char
id|nh_sel
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|scope
r_int
r_char
id|scope
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dn_fib_nh
r_struct
id|dn_fib_nh
(brace
DECL|member|nh_dev
r_struct
id|net_device
op_star
id|nh_dev
suffix:semicolon
DECL|member|nh_flags
r_int
id|nh_flags
suffix:semicolon
DECL|member|nh_scope
r_int
r_char
id|nh_scope
suffix:semicolon
DECL|member|nh_weight
r_int
id|nh_weight
suffix:semicolon
DECL|member|nh_power
r_int
id|nh_power
suffix:semicolon
DECL|member|nh_oif
r_int
id|nh_oif
suffix:semicolon
DECL|member|nh_gw
id|u32
id|nh_gw
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dn_fib_info
r_struct
id|dn_fib_info
(brace
DECL|member|fib_next
r_struct
id|dn_fib_info
op_star
id|fib_next
suffix:semicolon
DECL|member|fib_prev
r_struct
id|dn_fib_info
op_star
id|fib_prev
suffix:semicolon
DECL|member|fib_treeref
r_int
id|fib_treeref
suffix:semicolon
DECL|member|fib_clntref
id|atomic_t
id|fib_clntref
suffix:semicolon
DECL|member|fib_dead
r_int
id|fib_dead
suffix:semicolon
DECL|member|fib_flags
r_int
id|fib_flags
suffix:semicolon
DECL|member|fib_protocol
r_int
id|fib_protocol
suffix:semicolon
DECL|member|fib_prefsrc
id|dn_address
id|fib_prefsrc
suffix:semicolon
DECL|member|fib_priority
id|u32
id|fib_priority
suffix:semicolon
DECL|member|fib_nhs
r_int
id|fib_nhs
suffix:semicolon
DECL|member|fib_power
r_int
id|fib_power
suffix:semicolon
DECL|member|fib_nh
r_struct
id|dn_fib_nh
id|fib_nh
(braket
l_int|0
)braket
suffix:semicolon
DECL|macro|fib_dev
mdefine_line|#define fib_dev&t;&t;fib_nh[0].nh_dev
)brace
suffix:semicolon
DECL|macro|DN_FIB_RES_NH
mdefine_line|#define DN_FIB_RES_NH(res)&t;((res).fi-&gt;fib_nh[(res).nh_sel])
DECL|macro|DN_FIB_RES_RESET
mdefine_line|#define DN_FIB_RES_RESET(res)&t;((res).nh_sel = 0)
DECL|macro|DN_FIB_RES_GW
mdefine_line|#define DN_FIB_RES_GW(res)&t;(DN_FIB_RES_NH(res).nh_gw)
DECL|macro|DN_FIB_RES_DEV
mdefine_line|#define DN_FIB_RES_DEV(res)&t;(DN_FIB_RES_NH(res).nh_dev)
DECL|macro|DN_FIB_RES_OIF
mdefine_line|#define DN_FIB_RES_OIF(res)&t;(DN_FIB_RES_NH(res).nh_oif)
r_typedef
r_struct
(brace
DECL|member|datum
id|u16
id|datum
suffix:semicolon
DECL|typedef|dn_fib_key_t
)brace
id|dn_fib_key_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|datum
id|u16
id|datum
suffix:semicolon
DECL|typedef|dn_fib_hash_t
)brace
id|dn_fib_hash_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|datum
id|u16
id|datum
suffix:semicolon
DECL|typedef|dn_fib_idx_t
)brace
id|dn_fib_idx_t
suffix:semicolon
DECL|struct|dn_fib_node
r_struct
id|dn_fib_node
(brace
DECL|member|fn_next
r_struct
id|dn_fib_node
op_star
id|fn_next
suffix:semicolon
DECL|member|fn_info
r_struct
id|dn_fib_info
op_star
id|fn_info
suffix:semicolon
DECL|macro|DN_FIB_INFO
mdefine_line|#define DN_FIB_INFO(f) ((f)-&gt;fn_info)
DECL|member|fn_key
id|dn_fib_key_t
id|fn_key
suffix:semicolon
DECL|member|fn_type
id|u8
id|fn_type
suffix:semicolon
DECL|member|fn_scope
id|u8
id|fn_scope
suffix:semicolon
DECL|member|fn_state
id|u8
id|fn_state
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dn_fib_table
r_struct
id|dn_fib_table
(brace
DECL|member|n
r_int
id|n
suffix:semicolon
DECL|member|insert
r_int
(paren
op_star
id|insert
)paren
(paren
r_struct
id|dn_fib_table
op_star
id|t
comma
r_struct
id|rtmsg
op_star
id|r
comma
r_struct
id|dn_kern_rta
op_star
id|rta
comma
r_struct
id|nlmsghdr
op_star
id|n
comma
r_struct
id|netlink_skb_parms
op_star
id|req
)paren
suffix:semicolon
DECL|member|delete
r_int
(paren
op_star
r_delete
)paren
(paren
r_struct
id|dn_fib_table
op_star
id|t
comma
r_struct
id|rtmsg
op_star
id|r
comma
r_struct
id|dn_kern_rta
op_star
id|rta
comma
r_struct
id|nlmsghdr
op_star
id|n
comma
r_struct
id|netlink_skb_parms
op_star
id|req
)paren
suffix:semicolon
DECL|member|lookup
r_int
(paren
op_star
id|lookup
)paren
(paren
r_struct
id|dn_fib_table
op_star
id|t
comma
r_const
r_struct
id|dn_fib_key
op_star
id|key
comma
r_struct
id|dn_fib_res
op_star
id|res
)paren
suffix:semicolon
DECL|member|flush
r_int
(paren
op_star
id|flush
)paren
(paren
r_struct
id|dn_fib_table
op_star
id|t
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
DECL|member|get_info
r_int
(paren
op_star
id|get_info
)paren
(paren
r_struct
id|dn_fib_table
op_star
id|table
comma
r_char
op_star
id|buf
comma
r_int
id|first
comma
r_int
id|count
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
macro_line|#ifdef CONFIG_RTNETLINK
DECL|member|dump
r_int
(paren
op_star
id|dump
)paren
(paren
r_struct
id|dn_fib_table
op_star
id|t
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_RTNETLINK */
DECL|member|data
r_int
r_char
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * dn_fib.c&n; */
r_extern
r_void
id|dn_fib_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dn_fib_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|dn_fib_rt_message
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|dn_fib_ioctl
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_struct
id|dn_fib_info
op_star
id|dn_fib_create_info
c_func
(paren
r_const
r_struct
id|rtmsg
op_star
id|r
comma
r_struct
id|dn_kern_rta
op_star
id|rta
comma
r_const
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_int
op_star
id|errp
)paren
suffix:semicolon
r_extern
r_int
id|dn_fib_semantic_match
c_func
(paren
r_int
id|type
comma
r_struct
id|dn_fib_info
op_star
id|fi
comma
r_const
r_struct
id|dn_fib_key
op_star
id|key
comma
r_struct
id|dn_fib_res
op_star
id|res
)paren
suffix:semicolon
r_extern
r_void
id|dn_fib_release_info
c_func
(paren
r_struct
id|dn_fib_info
op_star
id|fi
)paren
suffix:semicolon
r_extern
id|u16
id|dn_fib_get_attr16
c_func
(paren
r_struct
id|rtattr
op_star
id|attr
comma
r_int
id|attrlen
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_void
id|dn_fib_flush
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dn_fib_select_multipath
c_func
(paren
r_const
r_struct
id|dn_fib_key
op_star
id|key
comma
r_struct
id|dn_fib_res
op_star
id|res
)paren
suffix:semicolon
r_extern
r_int
id|dn_fib_sync_down
c_func
(paren
id|dn_address
id|local
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|force
)paren
suffix:semicolon
r_extern
r_int
id|dn_fib_sync_up
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n; * dn_tables.c&n; */
r_extern
r_struct
id|dn_fib_table
op_star
id|dn_fib_get_table
c_func
(paren
r_int
id|n
comma
r_int
id|creat
)paren
suffix:semicolon
r_extern
r_struct
id|dn_fib_table
op_star
id|dn_fib_empty_table
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dn_fib_table_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dn_fib_table_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * dn_rules.c&n; */
r_extern
r_void
id|dn_fib_rules_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dn_fib_rules_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dn_fib_rule_put
c_func
(paren
r_struct
id|dn_fib_rule
op_star
)paren
suffix:semicolon
r_extern
r_int
id|dn_fib_lookup
c_func
(paren
r_struct
id|dn_fib_key
op_star
id|key
comma
r_struct
id|dn_fib_res
op_star
id|res
)paren
suffix:semicolon
multiline_comment|/*&n; * rtnetlink interface&n; */
macro_line|#ifdef CONFIG_RTNETLINK
r_extern
r_int
id|dn_fib_rtm_delroute
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|dn_fib_rtm_newroute
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|dn_fib_dump
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
suffix:semicolon
r_extern
r_int
id|dn_fib_rtm_delrule
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|dn_fib_rtm_newrule
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|dn_fib_dump_rules
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_RTNETLINK */
DECL|macro|DN_NUM_TABLES
mdefine_line|#define DN_NUM_TABLES 255
DECL|macro|DN_MIN_TABLE
mdefine_line|#define DN_MIN_TABLE 1
DECL|macro|DN_DEFAULT_TABLE
mdefine_line|#define DN_DEFAULT_TABLE 1
DECL|macro|DN_L1_TABLE
mdefine_line|#define DN_L1_TABLE 1
DECL|macro|DN_L2_TABLE
mdefine_line|#define DN_L2_TABLE 2
r_extern
r_void
id|dn_fib_free_info
c_func
(paren
r_struct
id|dn_fib_info
op_star
id|fi
)paren
suffix:semicolon
DECL|function|dn_fib_info_put
r_static
id|__inline__
r_void
id|dn_fib_info_put
c_func
(paren
r_struct
id|dn_fib_info
op_star
id|fi
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|fi-&gt;fib_clntref
)paren
)paren
id|dn_fib_free_info
c_func
(paren
id|fi
)paren
suffix:semicolon
)brace
DECL|function|dn_fib_res_put
r_static
id|__inline__
r_void
id|dn_fib_res_put
c_func
(paren
r_struct
id|dn_fib_res
op_star
id|res
)paren
(brace
r_if
c_cond
(paren
id|res-&gt;fi
)paren
id|dn_fib_info_put
c_func
(paren
id|res-&gt;fi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;r
)paren
id|dn_fib_rule_put
c_func
(paren
id|res-&gt;r
)paren
suffix:semicolon
)brace
DECL|function|dnet_make_mask
r_static
id|__inline__
id|u16
id|dnet_make_mask
c_func
(paren
r_int
id|n
)paren
(brace
r_if
c_cond
(paren
id|n
)paren
r_return
id|htons
c_func
(paren
op_complement
(paren
(paren
l_int|1
op_lshift
(paren
l_int|16
op_minus
id|n
)paren
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_DECNET_ROUTER */
macro_line|#endif /* _NET_DN_FIB_H */
eof
