multiline_comment|/* auxio.c: Probing for the Sparc AUXIO register at boot time.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/auxio.h&gt;
multiline_comment|/* Probe and map in the Auxiliary I/O register */
DECL|variable|auxio_register
r_int
r_char
op_star
id|auxio_register
suffix:semicolon
r_void
DECL|function|auxio_probe
id|auxio_probe
c_func
(paren
r_void
)paren
(brace
r_int
id|node
comma
id|auxio_nd
suffix:semicolon
r_struct
id|linux_prom_registers
id|auxregs
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4d
)paren
(brace
id|auxio_register
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|node
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|auxio_nd
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;auxiliary-io&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|auxio_nd
)paren
(brace
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;obio&quot;
)paren
suffix:semicolon
id|node
op_assign
id|prom_getchild
c_func
(paren
id|node
)paren
suffix:semicolon
id|auxio_nd
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;auxio&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|auxio_nd
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Cannot find auxio node, cannot continue...&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|prom_getproperty
c_func
(paren
id|auxio_nd
comma
l_string|&quot;reg&quot;
comma
(paren
r_char
op_star
)paren
id|auxregs
comma
r_sizeof
(paren
id|auxregs
)paren
)paren
suffix:semicolon
id|prom_apply_obio_ranges
c_func
(paren
id|auxregs
comma
l_int|0x1
)paren
suffix:semicolon
multiline_comment|/* Map the register both read and write */
id|auxio_register
op_assign
(paren
r_int
r_char
op_star
)paren
id|sparc_alloc_io
c_func
(paren
id|auxregs
(braket
l_int|0
)braket
dot
id|phys_addr
comma
l_int|0
comma
id|auxregs
(braket
l_int|0
)braket
dot
id|reg_size
comma
l_string|&quot;auxiliaryIO&quot;
comma
id|auxregs
(braket
l_int|0
)braket
dot
id|which_io
comma
l_int|0x0
)paren
suffix:semicolon
multiline_comment|/* Fix the address on sun4m and sun4c. */
r_if
c_cond
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|auxregs
(braket
l_int|0
)braket
dot
id|phys_addr
)paren
op_amp
l_int|3
)paren
op_eq
l_int|3
op_logical_or
id|sparc_cpu_model
op_eq
id|sun4c
)paren
(brace
id|auxio_register
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
(paren
r_int
)paren
id|auxio_register
op_or
l_int|3
)paren
suffix:semicolon
)brace
id|TURN_ON_LED
suffix:semicolon
)brace
eof
