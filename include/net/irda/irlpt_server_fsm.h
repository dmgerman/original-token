multiline_comment|/*********************************************************************&n; *                &n; * Filename:      server_server_fsm.h&n; * Version:       0.1&n; * Sources:       irlan_event.h&n; * &n; *     Copyright (c) 1997 Dag Brattli &lt;dagb@cs.uit.no&gt;, &n; *&t;&t;All Rights Reserved.&n; *     Copyright (c) 1998, Thomas Davis, &lt;ratbert@radiks.net&gt;, &n; *&t;&t;All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     I, Thomas Davis, provide no warranty for any of this software. &n; *     This material is provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRLPT_EVENT_H
DECL|macro|IRLPT_EVENT_H
mdefine_line|#define IRLPT_EVENT_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
r_void
id|irlpt_server_do_event
c_func
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlpt_info
op_star
id|info
)paren
suffix:semicolon
r_void
id|irlpt_server_next_state
c_func
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_SERVER_STATE
id|state
)paren
suffix:semicolon
macro_line|#endif
eof
