multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlpt_server.h&n; * Version:       0.1&n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sat Feb 21 18:54:38 1998&n; * Modified at:   Tue Sep 22 11:41:42 1998&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998, Thomas Davis, &lt;ratbert@radiks.net&gt;&n; *     Copyright (c) 1998, Dag Brattli, &n; *     All Rights Reserved&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     I, Thomas Davis, provide no warranty for any of this software. This&n; *     material is provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef IRLPT_SERVER_H
DECL|macro|IRLPT_SERVER_H
mdefine_line|#define IRLPT_SERVER_H
macro_line|#include &quot;qos.h&quot;
macro_line|#include &quot;irmod.h&quot;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
multiline_comment|/* int  server_init( struct net_device *dev); */
r_extern
r_struct
id|irlpt_cb
op_star
id|irlpt_server
suffix:semicolon
macro_line|#endif
eof
