multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET  is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the Forwarding Information Base.&n; *&n; * Authors:&t;A.N.Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _NET_IP_FIB_H
DECL|macro|_NET_IP_FIB_H
mdefine_line|#define _NET_IP_FIB_H
DECL|struct|fib_node
r_struct
id|fib_node
(brace
DECL|member|fib_next
r_struct
id|fib_node
op_star
id|fib_next
suffix:semicolon
DECL|member|fib_key
id|u32
id|fib_key
suffix:semicolon
DECL|member|fib_info
r_struct
id|fib_info
op_star
id|fib_info
suffix:semicolon
DECL|member|fib_metric
r_int
id|fib_metric
suffix:semicolon
DECL|member|fib_tos
id|u8
id|fib_tos
suffix:semicolon
DECL|member|fib_flag
id|u8
id|fib_flag
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FIBFLG_DOWN
mdefine_line|#define FIBFLG_DOWN&t;&t;1&t;/* Ignore this node&t;*/
DECL|macro|FIBFLG_THROW
mdefine_line|#define FIBFLG_THROW&t;&t;2&t;/* Class lookup failed&t;*/
DECL|macro|FIBFLG_REJECT
mdefine_line|#define FIBFLG_REJECT&t;&t;4&t;/* Route lookup failed&t;*/
DECL|macro|MAGIC_METRIC
mdefine_line|#define MAGIC_METRIC&t;&t;0x7FFF
multiline_comment|/*&n; * This structure contains data shared by many of routes.&n; */
DECL|struct|fib_info
r_struct
id|fib_info
(brace
DECL|member|fib_next
r_struct
id|fib_info
op_star
id|fib_next
suffix:semicolon
DECL|member|fib_prev
r_struct
id|fib_info
op_star
id|fib_prev
suffix:semicolon
DECL|member|fib_gateway
id|u32
id|fib_gateway
suffix:semicolon
DECL|member|fib_dev
r_struct
id|device
op_star
id|fib_dev
suffix:semicolon
DECL|member|fib_refcnt
r_int
id|fib_refcnt
suffix:semicolon
DECL|member|fib_window
r_int
r_int
id|fib_window
suffix:semicolon
DECL|member|fib_flags
r_int
id|fib_flags
suffix:semicolon
DECL|member|fib_mtu
r_int
r_int
id|fib_mtu
suffix:semicolon
DECL|member|fib_irtt
r_int
r_int
id|fib_irtt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fib_zone
r_struct
id|fib_zone
(brace
DECL|member|fz_next
r_struct
id|fib_zone
op_star
id|fz_next
suffix:semicolon
DECL|member|fz_hash
r_struct
id|fib_node
op_star
op_star
id|fz_hash
suffix:semicolon
DECL|member|fz_nent
r_int
id|fz_nent
suffix:semicolon
DECL|member|fz_divisor
r_int
id|fz_divisor
suffix:semicolon
DECL|member|fz_hashmask
id|u32
id|fz_hashmask
suffix:semicolon
DECL|member|fz_logmask
r_int
id|fz_logmask
suffix:semicolon
DECL|member|fz_mask
id|u32
id|fz_mask
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fib_class
r_struct
id|fib_class
(brace
DECL|member|cl_id
r_int
r_char
id|cl_id
suffix:semicolon
DECL|member|cl_auto
r_int
r_char
id|cl_auto
suffix:semicolon
DECL|member|fib_zones
r_struct
id|fib_zone
op_star
id|fib_zones
(braket
l_int|33
)braket
suffix:semicolon
DECL|member|fib_zone_list
r_struct
id|fib_zone
op_star
id|fib_zone_list
suffix:semicolon
DECL|member|cl_users
r_int
id|cl_users
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fib_rule
r_struct
id|fib_rule
(brace
DECL|member|cl_next
r_struct
id|fib_rule
op_star
id|cl_next
suffix:semicolon
DECL|member|cl_class
r_struct
id|fib_class
op_star
id|cl_class
suffix:semicolon
DECL|member|cl_src
id|u32
id|cl_src
suffix:semicolon
DECL|member|cl_srcmask
id|u32
id|cl_srcmask
suffix:semicolon
DECL|member|cl_dst
id|u32
id|cl_dst
suffix:semicolon
DECL|member|cl_dstmask
id|u32
id|cl_dstmask
suffix:semicolon
DECL|member|cl_srcmap
id|u32
id|cl_srcmap
suffix:semicolon
DECL|member|cl_action
id|u8
id|cl_action
suffix:semicolon
DECL|member|cl_flags
id|u8
id|cl_flags
suffix:semicolon
DECL|member|cl_tos
id|u8
id|cl_tos
suffix:semicolon
DECL|member|cl_preference
id|u8
id|cl_preference
suffix:semicolon
DECL|member|cl_dev
r_struct
id|device
op_star
id|cl_dev
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fib_result
r_struct
id|fib_result
(brace
DECL|member|f
r_struct
id|fib_node
op_star
id|f
suffix:semicolon
DECL|member|fr
r_struct
id|fib_rule
op_star
id|fr
suffix:semicolon
DECL|member|fm
r_int
id|fm
suffix:semicolon
)brace
suffix:semicolon
r_void
id|ip_fib_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|ip_fib_chk_addr
c_func
(paren
id|u32
id|addr
)paren
suffix:semicolon
r_int
id|ip_fib_chk_default_gw
c_func
(paren
id|u32
id|addr
comma
r_struct
id|device
op_star
)paren
suffix:semicolon
r_int
id|fib_lookup
c_func
(paren
r_struct
id|fib_result
op_star
comma
id|u32
id|daddr
comma
id|u32
id|src
comma
id|u8
id|tos
comma
r_struct
id|device
op_star
id|devin
comma
r_struct
id|device
op_star
id|devout
)paren
suffix:semicolon
r_static
id|__inline__
r_struct
id|fib_info
op_star
DECL|function|fib_lookup_info
id|fib_lookup_info
c_func
(paren
id|u32
id|dst
comma
id|u32
id|src
comma
id|u8
id|tos
comma
r_struct
id|device
op_star
id|devin
comma
r_struct
id|device
op_star
id|devout
)paren
(brace
r_struct
id|fib_result
id|res
suffix:semicolon
r_if
c_cond
(paren
id|fib_lookup
c_func
(paren
op_amp
id|res
comma
id|dst
comma
id|src
comma
id|tos
comma
id|devin
comma
id|devout
)paren
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|res.f-&gt;fib_info
suffix:semicolon
)brace
DECL|function|get_gw_dev
r_static
id|__inline__
r_struct
id|device
op_star
id|get_gw_dev
c_func
(paren
id|u32
id|gw
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|fib_info
op_star
id|fi
suffix:semicolon
id|fi
op_assign
id|fib_lookup_info
c_func
(paren
id|gw
comma
l_int|0
comma
l_int|1
comma
op_amp
id|loopback_dev
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fi
)paren
r_return
id|fi-&gt;fib_dev
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_extern
r_int
id|ip_rt_event
c_func
(paren
r_int
id|event
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|ip_rt_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|ip_rt_change_broadcast
c_func
(paren
r_struct
id|device
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_void
id|ip_rt_change_dstaddr
c_func
(paren
r_struct
id|device
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_void
id|ip_rt_change_netmask
c_func
(paren
r_struct
id|device
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_void
id|ip_rt_multicast_event
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_struct
id|device
op_star
id|ip_dev_find_tunnel
c_func
(paren
id|u32
id|daddr
comma
id|u32
id|saddr
)paren
suffix:semicolon
macro_line|#endif  _NET_FIB_H
eof