multiline_comment|/*&n; * Acorn specific net device driver probe routine&n; *&n; * Copyright (C) 1998 Russell King&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
r_extern
r_int
id|ether1_probe
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|ether3_probe
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|etherh_probe
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|acorn_ethif_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
)paren
(brace
r_if
c_cond
(paren
l_int|1
macro_line|#ifdef CONFIG_ARM_ETHERH
op_logical_and
id|etherh_probe
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_ARM_ETHER3
op_logical_and
id|ether3_probe
(paren
id|dev
)paren
macro_line|#endif
macro_line|#ifdef CONFIG_ARM_ETHER1
op_logical_and
id|ether1_probe
(paren
id|dev
)paren
macro_line|#endif
op_logical_and
l_int|1
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
