multiline_comment|/*&n; *&t;Device event handling&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_notify.c,v 1.1 2000/02/18 16:47:12 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
macro_line|#include &quot;br_private.h&quot;
r_static
r_int
id|br_device_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|unused
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
suffix:semicolon
DECL|variable|br_device_notifier
r_struct
id|notifier_block
id|br_device_notifier
op_assign
(brace
id|br_device_event
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
DECL|function|br_device_event
r_static
r_int
id|br_device_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|unused
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
id|dev
op_assign
id|ptr
suffix:semicolon
id|p
op_assign
id|dev-&gt;br_port
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
id|NOTIFY_DONE
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|NETDEV_CHANGEADDR
suffix:colon
id|read_lock
c_func
(paren
op_amp
id|p-&gt;br-&gt;lock
)paren
suffix:semicolon
id|br_fdb_changeaddr
c_func
(paren
id|p
comma
id|dev-&gt;dev_addr
)paren
suffix:semicolon
id|br_stp_recalculate_bridge_id
c_func
(paren
id|p-&gt;br
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|p-&gt;br-&gt;lock
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NETDEV_GOING_DOWN
suffix:colon
multiline_comment|/* extend the protocol to send some kind of notification? */
r_break
suffix:semicolon
r_case
id|NETDEV_DOWN
suffix:colon
r_if
c_cond
(paren
id|p-&gt;br-&gt;dev.flags
op_amp
id|IFF_UP
)paren
(brace
id|read_lock
c_func
(paren
op_amp
id|p-&gt;br-&gt;lock
)paren
suffix:semicolon
id|br_stp_disable_port
c_func
(paren
id|dev-&gt;br_port
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|p-&gt;br-&gt;lock
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NETDEV_UP
suffix:colon
r_if
c_cond
(paren
id|p-&gt;br-&gt;dev.flags
op_amp
id|IFF_UP
)paren
(brace
id|read_lock
c_func
(paren
op_amp
id|p-&gt;br-&gt;lock
)paren
suffix:semicolon
id|br_stp_enable_port
c_func
(paren
id|dev-&gt;br_port
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|p-&gt;br-&gt;lock
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NETDEV_UNREGISTER
suffix:colon
id|br_del_if
c_func
(paren
id|dev-&gt;br_port-&gt;br
comma
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
eof
