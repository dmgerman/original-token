multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlpt_client.h&n; * Version:       0.1&n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sat Feb 21 18:54:38 1998&n; * Modified at:   Mon Jan 11 15:58:16 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998, Thomas Davis, &lt;ratbert@radiks.net&gt;&n; *     Copyright (c) 1998, Dag Brattli, &n; *     All Rights Reserved&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     I, Thomas Davis, provide no warranty for any of this software. This&n; *     material is provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef IRLPT_CLIENT_H
DECL|macro|IRLPT_CLIENT_H
mdefine_line|#define IRLPT_CLIENT_H
multiline_comment|/* Debug function */
multiline_comment|/* int  client_init( struct device *dev); */
multiline_comment|/*&n; * if it&squot;s static, it doesn&squot;t go in here.&n; */
r_void
id|irlpt_client_get_value_confirm
c_func
(paren
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
r_void
id|irlpt_client_connect_indication
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
r_struct
id|qos_info
op_star
id|qos
comma
r_int
id|max_seg_size
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|irlpt_client_connect_request
c_func
(paren
r_struct
id|irlpt_cb
op_star
id|self
)paren
suffix:semicolon
r_extern
id|hashbin_t
op_star
id|irlpt_clients
suffix:semicolon
macro_line|#endif
eof
