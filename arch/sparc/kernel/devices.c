multiline_comment|/* devices.c: Initial scan of the prom device tree for important&n; *            Sparc device nodes which we need to find.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/mp.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|variable|linux_cpus
r_struct
id|prom_cpuinfo
id|linux_cpus
(braket
id|NCPUS
)braket
suffix:semicolon
DECL|variable|linux_num_cpus
r_int
id|linux_num_cpus
suffix:semicolon
r_extern
r_void
id|cpu_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|auxio_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
DECL|function|device_scan
id|device_scan
c_func
(paren
r_int
r_int
id|mem_start
)paren
(brace
r_char
id|node_str
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|nd
comma
id|prom_node_cpu
comma
id|thismid
suffix:semicolon
r_int
id|cpu_nds
(braket
id|NCPUS
)braket
suffix:semicolon
multiline_comment|/* One node for each cpu */
r_int
id|cpu_ctr
op_assign
l_int|0
suffix:semicolon
id|prom_getstring
c_func
(paren
id|prom_root_node
comma
l_string|&quot;device_type&quot;
comma
id|node_str
comma
r_sizeof
(paren
id|node_str
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|node_str
comma
l_string|&quot;cpu&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|cpu_nds
(braket
l_int|0
)braket
op_assign
id|prom_root_node
suffix:semicolon
id|cpu_ctr
op_increment
suffix:semicolon
)brace
r_else
(brace
r_int
id|scan
suffix:semicolon
id|scan
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|nd
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|scan
op_assign
id|prom_getsibling
c_func
(paren
id|scan
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|prom_getstring
c_func
(paren
id|scan
comma
l_string|&quot;device_type&quot;
comma
id|node_str
comma
r_sizeof
(paren
id|node_str
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|node_str
comma
l_string|&quot;cpu&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|cpu_nds
(braket
id|cpu_ctr
)braket
op_assign
id|scan
suffix:semicolon
id|linux_cpus
(braket
id|cpu_ctr
)braket
dot
id|prom_node
op_assign
id|scan
suffix:semicolon
id|prom_getproperty
c_func
(paren
id|scan
comma
l_string|&quot;mid&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|thismid
comma
r_sizeof
(paren
id|thismid
)paren
)paren
suffix:semicolon
id|linux_cpus
(braket
id|cpu_ctr
)braket
dot
id|mid
op_assign
id|thismid
suffix:semicolon
id|cpu_ctr
op_increment
suffix:semicolon
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
id|cpu_ctr
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No CPU nodes found, cannot continue.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Probably a sun4d or sun4e, Sun is trying to trick us ;-) */
id|halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Found %d CPU prom device tree node(s).&bslash;n&quot;
comma
id|cpu_ctr
)paren
suffix:semicolon
)brace
suffix:semicolon
id|prom_node_cpu
op_assign
id|cpu_nds
(braket
l_int|0
)braket
suffix:semicolon
id|linux_num_cpus
op_assign
id|cpu_ctr
suffix:semicolon
id|cpu_probe
c_func
(paren
)paren
suffix:semicolon
id|auxio_probe
c_func
(paren
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
eof