multiline_comment|/*&n; *&t;&t;IP_ALIAS (AF_INET) aliasing module.&n; *&n; *&n; * Version:&t;@(#)ip_alias.c&t;0.43   12/20/95&n; *&n; * Author:&t;Juan Jose Ciarlante, &lt;jjciarla@raiz.uncu.edu.ar&gt;&n; *&n; * Fixes:&n; *&t;JJC&t;:&t;ip_alias_dev_select method.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&t;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#ifdef ALIAS_USER_LAND_DEBUG
macro_line|#include &quot;net_alias.h&quot;
macro_line|#include &quot;ip_alias.h&quot;
macro_line|#include &quot;user_stubs.h&quot;
macro_line|#endif
macro_line|#include &lt;linux/net_alias.h&gt;
macro_line|#include &lt;net/ip_alias.h&gt;
multiline_comment|/*&n; *&t;AF_INET alias init&n; */
DECL|function|ip_alias_init_1
r_static
r_int
id|ip_alias_init_1
c_func
(paren
r_struct
id|net_alias_type
op_star
id|this
comma
r_struct
id|net_alias
op_star
id|alias
comma
r_struct
id|sockaddr
op_star
id|sa
)paren
(brace
macro_line|#ifdef ALIAS_USER_LAND_DEBUG
id|printk
c_func
(paren
l_string|&quot;alias_init(%s) called.&bslash;n&quot;
comma
id|alias-&gt;name
)paren
suffix:semicolon
macro_line|#endif
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;AF_INET alias done&n; */
DECL|function|ip_alias_done_1
r_static
r_int
id|ip_alias_done_1
c_func
(paren
r_struct
id|net_alias_type
op_star
id|this
comma
r_struct
id|net_alias
op_star
id|alias
)paren
(brace
macro_line|#ifdef ALIAS_USER_LAND_DEBUG
id|printk
c_func
(paren
l_string|&quot;alias_done(%s) called.&bslash;n&quot;
comma
id|alias-&gt;name
)paren
suffix:semicolon
macro_line|#endif
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Print alias address info&n; */
DECL|function|ip_alias_print_1
r_int
id|ip_alias_print_1
c_func
(paren
r_struct
id|net_alias_type
op_star
id|this
comma
r_struct
id|net_alias
op_star
id|alias
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
op_amp
id|alias-&gt;dev.pa_addr
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d.%d.%d.%d&quot;
comma
(paren
id|p
(braket
l_int|0
)braket
op_amp
l_int|255
)paren
comma
(paren
id|p
(braket
l_int|1
)braket
op_amp
l_int|255
)paren
comma
(paren
id|p
(braket
l_int|2
)braket
op_amp
l_int|255
)paren
comma
(paren
id|p
(braket
l_int|3
)braket
op_amp
l_int|255
)paren
)paren
suffix:semicolon
)brace
DECL|function|ip_alias_dev_select
r_struct
id|device
op_star
id|ip_alias_dev_select
c_func
(paren
r_struct
id|net_alias_type
op_star
id|this
comma
r_struct
id|device
op_star
id|main_dev
comma
r_struct
id|sockaddr
op_star
id|sa
)paren
(brace
id|__u32
id|addr
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Defensive...&t;&n;&t; */
r_if
c_cond
(paren
id|main_dev
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Get u32 address. &n;&t; */
id|addr
op_assign
(paren
id|sa
)paren
ques
c_cond
(paren
r_struct
id|sockaddr_in
op_star
)paren
id|sa.sin_addr.s_addr
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Find &squot;closest&squot; device to address given. any other suggestions? ...&n;&t; *&t;net_alias module will check if returned device is main_dev&squot;s alias&n;&t; */
id|rt
op_assign
id|ip_rt_route
c_func
(paren
id|addr
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rt
)paren
(brace
id|dev
op_assign
id|rt-&gt;rt_dev
suffix:semicolon
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
)brace
r_return
id|dev
suffix:semicolon
)brace
multiline_comment|/*&n; * net_alias AF_INET type defn.&n; */
DECL|variable|ip_alias_type
r_struct
id|net_alias_type
id|ip_alias_type
op_assign
(brace
id|AF_INET
comma
multiline_comment|/* type */
l_int|0
comma
multiline_comment|/* n_attach */
l_string|&quot;ip&quot;
comma
multiline_comment|/* name */
l_int|NULL
comma
multiline_comment|/* get_addr32() */
l_int|NULL
comma
multiline_comment|/* dev_addr_chk() */
id|ip_alias_dev_select
comma
multiline_comment|/* dev_select() */
id|ip_alias_init_1
comma
multiline_comment|/* alias_init_1() */
id|ip_alias_done_1
comma
multiline_comment|/* alias_done_1() */
id|ip_alias_print_1
comma
multiline_comment|/* alias_print_1() */
l_int|NULL
multiline_comment|/* next */
)brace
suffix:semicolon
multiline_comment|/*&n; * ip_alias module initialization&n; */
DECL|function|ip_alias_init
r_int
id|ip_alias_init
c_func
(paren
r_void
)paren
(brace
r_return
id|register_net_alias_type
c_func
(paren
op_amp
id|ip_alias_type
comma
id|AF_INET
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ip_alias module done&n; */
DECL|function|ip_alias_done
r_int
id|ip_alias_done
c_func
(paren
r_void
)paren
(brace
r_return
id|unregister_net_alias_type
c_func
(paren
op_amp
id|ip_alias_type
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ip_alias_init
c_func
(paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ip_alias_done
c_func
(paren
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ip_alias: can&squot;t remove module&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
