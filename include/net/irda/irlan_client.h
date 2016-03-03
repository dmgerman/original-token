multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlan_client.h&n; * Version:       0.3&n; * Description:   IrDA LAN access layer&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun Aug 31 20:14:37 1997&n; * Modified at:   Thu Apr 22 14:13:34 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998 Dag Brattli &lt;dagb@cs.uit.no&gt;, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRLAN_CLIENT_H
DECL|macro|IRLAN_CLIENT_H
mdefine_line|#define IRLAN_CLIENT_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/irda/irias_object.h&gt;
macro_line|#include &lt;net/irda/irlan_event.h&gt;
r_void
id|irlan_client_start_kick_timer
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
r_int
id|timeout
)paren
suffix:semicolon
r_void
id|irlan_client_discovery_indication
c_func
(paren
id|discovery_t
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_void
id|irlan_client_wakeup
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|__u32
id|saddr
comma
id|__u32
id|daddr
)paren
suffix:semicolon
r_void
id|irlan_client_open_ctrl_tsap
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlan_client_parse_response
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|irlan_client_get_value_confirm
c_func
(paren
r_int
id|result
comma
id|__u16
id|obj_id
comma
r_struct
id|ias_value
op_star
id|value
comma
r_void
op_star
id|priv
)paren
suffix:semicolon
macro_line|#endif
eof
