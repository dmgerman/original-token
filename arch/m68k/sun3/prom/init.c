multiline_comment|/* $Id: init.c,v 1.9 1996/12/18 06:46:55 tridge Exp $&n; * init.c:  Initialize internal variables used by the PROM&n; *          library functions.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
DECL|variable|romvec
r_struct
id|linux_romvec
op_star
id|romvec
suffix:semicolon
DECL|variable|prom_vers
r_enum
id|prom_major_version
id|prom_vers
suffix:semicolon
DECL|variable|prom_rev
DECL|variable|prom_prev
r_int
r_int
id|prom_rev
comma
id|prom_prev
suffix:semicolon
multiline_comment|/* The root node of the prom device tree. */
DECL|variable|prom_root_node
r_int
id|prom_root_node
suffix:semicolon
multiline_comment|/* Pointer to the device tree operations structure. */
DECL|variable|prom_nodeops
r_struct
id|linux_nodeops
op_star
id|prom_nodeops
suffix:semicolon
multiline_comment|/* You must call prom_init() before you attempt to use any of the&n; * routines in the prom library.  It returns 0 on success, 1 on&n; * failure.  It gets passed the pointer to the PROM vector.&n; */
r_extern
r_void
id|prom_meminit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|prom_ranges_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|prom_init
c_func
(paren
r_struct
id|linux_romvec
op_star
id|rp
)paren
)paren
(brace
macro_line|#if CONFIG_AP1000
r_extern
r_struct
id|linux_romvec
op_star
id|ap_prom_init
c_func
(paren
r_void
)paren
suffix:semicolon
id|rp
op_assign
id|ap_prom_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|romvec
op_assign
id|rp
suffix:semicolon
macro_line|#ifndef CONFIG_SUN3
r_switch
c_cond
(paren
id|romvec-&gt;pv_romvers
)paren
(brace
r_case
l_int|0
suffix:colon
id|prom_vers
op_assign
id|PROM_V0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|prom_vers
op_assign
id|PROM_V2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|prom_vers
op_assign
id|PROM_V3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|prom_vers
op_assign
id|PROM_P1275
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;PROMLIB: Sun IEEE Prom not supported yet&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|42
suffix:colon
multiline_comment|/* why not :-) */
id|prom_vers
op_assign
id|PROM_AP1000
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot;PROMLIB: Bad PROM version %d&bslash;n&quot;
comma
id|romvec-&gt;pv_romvers
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|prom_rev
op_assign
id|romvec-&gt;pv_plugin_revision
suffix:semicolon
id|prom_prev
op_assign
id|romvec-&gt;pv_printrev
suffix:semicolon
id|prom_nodeops
op_assign
id|romvec-&gt;pv_nodeops
suffix:semicolon
id|prom_root_node
op_assign
id|prom_getsibling
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|prom_root_node
op_eq
l_int|0
)paren
op_logical_or
(paren
id|prom_root_node
op_eq
op_minus
l_int|1
)paren
)paren
(brace
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|prom_nodeops
)paren
op_eq
l_int|0
)paren
op_logical_or
(paren
(paren
(paren
r_int
r_int
)paren
id|prom_nodeops
)paren
op_eq
op_minus
l_int|1
)paren
)paren
(brace
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|prom_meminit
c_func
(paren
)paren
suffix:semicolon
id|prom_ranges_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
singleline_comment|//&t;printk(&quot;PROMLIB: Sun Boot Prom Version %d Revision %d&bslash;n&quot;,
singleline_comment|//&t;       romvec-&gt;pv_romvers, prom_rev);
multiline_comment|/* Initialization successful. */
r_return
suffix:semicolon
)brace
eof
