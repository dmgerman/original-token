multiline_comment|/*&n; *&t;AX.25 release 037&n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;AX.25 036&t;Jonathan(G4KLX)&t;Split from ax25_timer.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_AX25) || defined(CONFIG_AX25_MODULE)
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
DECL|struct|protocol_struct
r_static
r_struct
id|protocol_struct
(brace
DECL|member|next
r_struct
id|protocol_struct
op_star
id|next
suffix:semicolon
DECL|member|pid
r_int
r_int
id|pid
suffix:semicolon
DECL|member|func
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|sk_buff
op_star
comma
id|ax25_cb
op_star
)paren
suffix:semicolon
DECL|variable|protocol_list
)brace
op_star
id|protocol_list
op_assign
l_int|NULL
suffix:semicolon
DECL|struct|linkfail_struct
r_static
r_struct
id|linkfail_struct
(brace
DECL|member|next
r_struct
id|linkfail_struct
op_star
id|next
suffix:semicolon
DECL|member|func
r_void
(paren
op_star
id|func
)paren
(paren
id|ax25_cb
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|linkfail_list
)brace
op_star
id|linkfail_list
op_assign
l_int|NULL
suffix:semicolon
DECL|struct|listen_struct
r_static
r_struct
id|listen_struct
(brace
DECL|member|next
r_struct
id|listen_struct
op_star
id|next
suffix:semicolon
DECL|member|callsign
id|ax25_address
id|callsign
suffix:semicolon
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|variable|listen_list
)brace
op_star
id|listen_list
op_assign
l_int|NULL
suffix:semicolon
DECL|function|ax25_protocol_register
r_int
id|ax25_protocol_register
c_func
(paren
r_int
r_int
id|pid
comma
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|sk_buff
op_star
comma
id|ax25_cb
op_star
)paren
)paren
(brace
r_struct
id|protocol_struct
op_star
id|protocol
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_eq
id|AX25_P_TEXT
op_logical_or
id|pid
op_eq
id|AX25_P_SEGMENT
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_INET
r_if
c_cond
(paren
id|pid
op_eq
id|AX25_P_IP
op_logical_or
id|pid
op_eq
id|AX25_P_ARP
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|protocol
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|protocol
)paren
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|protocol-&gt;pid
op_assign
id|pid
suffix:semicolon
id|protocol-&gt;func
op_assign
id|func
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|protocol-&gt;next
op_assign
id|protocol_list
suffix:semicolon
id|protocol_list
op_assign
id|protocol
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ax25_protocol_release
r_void
id|ax25_protocol_release
c_func
(paren
r_int
r_int
id|pid
)paren
(brace
r_struct
id|protocol_struct
op_star
id|s
comma
op_star
id|protocol
op_assign
id|protocol_list
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|protocol
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|protocol-&gt;pid
op_eq
id|pid
)paren
(brace
id|protocol_list
op_assign
id|protocol-&gt;next
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|protocol
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|protocol
op_ne
l_int|NULL
op_logical_and
id|protocol-&gt;next
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|protocol-&gt;next-&gt;pid
op_eq
id|pid
)paren
(brace
id|s
op_assign
id|protocol-&gt;next
suffix:semicolon
id|protocol-&gt;next
op_assign
id|protocol-&gt;next-&gt;next
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|protocol
op_assign
id|protocol-&gt;next
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|ax25_linkfail_register
r_int
id|ax25_linkfail_register
c_func
(paren
r_void
(paren
op_star
id|func
)paren
(paren
id|ax25_cb
op_star
comma
r_int
)paren
)paren
(brace
r_struct
id|linkfail_struct
op_star
id|linkfail
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|linkfail
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|linkfail
)paren
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|linkfail-&gt;func
op_assign
id|func
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|linkfail-&gt;next
op_assign
id|linkfail_list
suffix:semicolon
id|linkfail_list
op_assign
id|linkfail
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ax25_linkfail_release
r_void
id|ax25_linkfail_release
c_func
(paren
r_void
(paren
op_star
id|func
)paren
(paren
id|ax25_cb
op_star
comma
r_int
)paren
)paren
(brace
r_struct
id|linkfail_struct
op_star
id|s
comma
op_star
id|linkfail
op_assign
id|linkfail_list
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|linkfail
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|linkfail-&gt;func
op_eq
id|func
)paren
(brace
id|linkfail_list
op_assign
id|linkfail-&gt;next
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|linkfail
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|linkfail
op_ne
l_int|NULL
op_logical_and
id|linkfail-&gt;next
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|linkfail-&gt;next-&gt;func
op_eq
id|func
)paren
(brace
id|s
op_assign
id|linkfail-&gt;next
suffix:semicolon
id|linkfail-&gt;next
op_assign
id|linkfail-&gt;next-&gt;next
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|linkfail
op_assign
id|linkfail-&gt;next
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|ax25_listen_register
r_int
id|ax25_listen_register
c_func
(paren
id|ax25_address
op_star
id|callsign
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|listen_struct
op_star
id|listen
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|ax25_listen_mine
c_func
(paren
id|callsign
comma
id|dev
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|listen
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|listen
)paren
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|listen-&gt;callsign
op_assign
op_star
id|callsign
suffix:semicolon
id|listen-&gt;dev
op_assign
id|dev
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|listen-&gt;next
op_assign
id|listen_list
suffix:semicolon
id|listen_list
op_assign
id|listen
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ax25_listen_release
r_void
id|ax25_listen_release
c_func
(paren
id|ax25_address
op_star
id|callsign
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|listen_struct
op_star
id|s
comma
op_star
id|listen
op_assign
id|listen_list
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|listen
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|listen-&gt;callsign
comma
id|callsign
)paren
op_eq
l_int|0
op_logical_and
id|listen-&gt;dev
op_eq
id|dev
)paren
(brace
id|listen_list
op_assign
id|listen-&gt;next
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|listen
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|listen
op_ne
l_int|NULL
op_logical_and
id|listen-&gt;next
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|listen-&gt;next-&gt;callsign
comma
id|callsign
)paren
op_eq
l_int|0
op_logical_and
id|listen-&gt;next-&gt;dev
op_eq
id|dev
)paren
(brace
id|s
op_assign
id|listen-&gt;next
suffix:semicolon
id|listen-&gt;next
op_assign
id|listen-&gt;next-&gt;next
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|listen
op_assign
id|listen-&gt;next
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|ax25_protocol_function
r_int
(paren
op_star
id|ax25_protocol_function
c_func
(paren
r_int
r_int
id|pid
)paren
)paren
(paren
r_struct
id|sk_buff
op_star
comma
id|ax25_cb
op_star
)paren
(brace
r_struct
id|protocol_struct
op_star
id|protocol
suffix:semicolon
r_for
c_loop
(paren
id|protocol
op_assign
id|protocol_list
suffix:semicolon
id|protocol
op_ne
l_int|NULL
suffix:semicolon
id|protocol
op_assign
id|protocol-&gt;next
)paren
r_if
c_cond
(paren
id|protocol-&gt;pid
op_eq
id|pid
)paren
r_return
id|protocol-&gt;func
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|ax25_listen_mine
r_int
id|ax25_listen_mine
c_func
(paren
id|ax25_address
op_star
id|callsign
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|listen_struct
op_star
id|listen
suffix:semicolon
r_for
c_loop
(paren
id|listen
op_assign
id|listen_list
suffix:semicolon
id|listen
op_ne
l_int|NULL
suffix:semicolon
id|listen
op_assign
id|listen-&gt;next
)paren
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|listen-&gt;callsign
comma
id|callsign
)paren
op_eq
l_int|0
op_logical_and
(paren
id|listen-&gt;dev
op_eq
id|dev
op_logical_or
id|listen-&gt;dev
op_eq
l_int|NULL
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ax25_link_failed
r_void
id|ax25_link_failed
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
r_int
id|reason
)paren
(brace
r_struct
id|linkfail_struct
op_star
id|linkfail
suffix:semicolon
r_for
c_loop
(paren
id|linkfail
op_assign
id|linkfail_list
suffix:semicolon
id|linkfail
op_ne
l_int|NULL
suffix:semicolon
id|linkfail
op_assign
id|linkfail-&gt;next
)paren
(paren
id|linkfail-&gt;func
)paren
(paren
id|ax25
comma
id|reason
)paren
suffix:semicolon
)brace
DECL|function|ax25_protocol_is_registered
r_int
id|ax25_protocol_is_registered
c_func
(paren
r_int
r_int
id|pid
)paren
(brace
r_struct
id|protocol_struct
op_star
id|protocol
suffix:semicolon
r_for
c_loop
(paren
id|protocol
op_assign
id|protocol_list
suffix:semicolon
id|protocol
op_ne
l_int|NULL
suffix:semicolon
id|protocol
op_assign
id|protocol-&gt;next
)paren
r_if
c_cond
(paren
id|protocol-&gt;pid
op_eq
id|pid
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
