multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irsysctl.c&n; * Version:       1.0&n; * Description:   Sysctl interface for IrDA&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun May 24 22:12:06 1998&n; * Modified at:   Thu May  6 21:32:46 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1997, 1999 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
DECL|macro|NET_IRDA
mdefine_line|#define NET_IRDA 412 /* Random number */
DECL|enumerator|DISCOVERY
DECL|enumerator|DEVNAME
DECL|enumerator|COMPRESSION
DECL|enumerator|DEBUG
DECL|enumerator|SLOTS
DECL|enumerator|SLOT_TIMEOUT
r_enum
(brace
id|DISCOVERY
op_assign
l_int|1
comma
id|DEVNAME
comma
id|COMPRESSION
comma
id|DEBUG
comma
id|SLOTS
comma
id|SLOT_TIMEOUT
)brace
suffix:semicolon
r_extern
r_int
id|sysctl_discovery
suffix:semicolon
r_extern
r_int
id|sysctl_discovery_slots
suffix:semicolon
r_extern
r_int
id|sysctl_slot_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_fast_poll_increase
suffix:semicolon
DECL|variable|sysctl_compression
r_int
id|sysctl_compression
op_assign
l_int|0
suffix:semicolon
r_extern
r_char
id|sysctl_devname
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_DEBUG
r_extern
r_int
r_int
id|irda_debug
suffix:semicolon
macro_line|#endif
multiline_comment|/* One file */
DECL|variable|irda_table
r_static
id|ctl_table
id|irda_table
(braket
)braket
op_assign
(brace
(brace
id|DISCOVERY
comma
l_string|&quot;discovery&quot;
comma
op_amp
id|sysctl_discovery
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec
)brace
comma
(brace
id|DEVNAME
comma
l_string|&quot;devname&quot;
comma
id|sysctl_devname
comma
l_int|65
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dostring
comma
op_amp
id|sysctl_string
)brace
comma
(brace
id|COMPRESSION
comma
l_string|&quot;compression&quot;
comma
op_amp
id|sysctl_compression
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec
)brace
comma
macro_line|#ifdef CONFIG_IRDA_DEBUG
(brace
id|DEBUG
comma
l_string|&quot;debug&quot;
comma
op_amp
id|irda_debug
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_IRDA_FAST_RR
(brace
id|SLOTS
comma
l_string|&quot;fast_poll_increase&quot;
comma
op_amp
id|sysctl_fast_poll_increase
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec
)brace
comma
macro_line|#endif
(brace
id|SLOTS
comma
l_string|&quot;discovery_slots&quot;
comma
op_amp
id|sysctl_discovery_slots
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec
)brace
comma
(brace
id|SLOT_TIMEOUT
comma
l_string|&quot;slot_timeout&quot;
comma
op_amp
id|sysctl_slot_timeout
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* One directory */
DECL|variable|irda_net_table
r_static
id|ctl_table
id|irda_net_table
(braket
)braket
op_assign
(brace
(brace
id|NET_IRDA
comma
l_string|&quot;irda&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|irda_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The parent directory */
DECL|variable|irda_root_table
r_static
id|ctl_table
id|irda_root_table
(braket
)braket
op_assign
(brace
(brace
id|CTL_NET
comma
l_string|&quot;net&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|irda_net_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|irda_table_header
r_static
r_struct
id|ctl_table_header
op_star
id|irda_table_header
suffix:semicolon
multiline_comment|/*&n; * Function irda_sysctl_register (void)&n; *&n; *    Register our sysctl interface&n; *&n; */
DECL|function|irda_sysctl_register
r_int
id|irda_sysctl_register
c_func
(paren
r_void
)paren
(brace
id|irda_table_header
op_assign
id|register_sysctl_table
c_func
(paren
id|irda_root_table
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irda_table_header
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_sysctl_unregister (void)&n; *&n; *    Unregister our sysctl interface&n; *&n; */
DECL|function|irda_sysctl_unregister
r_void
id|irda_sysctl_unregister
c_func
(paren
r_void
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|irda_table_header
)paren
suffix:semicolon
)brace
eof
