multiline_comment|/* tadpole.c: Probing for the tadpole clock stopping h/w at boot time.&n; *&n; * Copyright (C) 1996 David Redman (djhr@tadpole.co.uk)&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|MACIO_SCSI_CSR_ADDR
mdefine_line|#define MACIO_SCSI_CSR_ADDR&t;0x78400000
DECL|macro|MACIO_EN_DMA
mdefine_line|#define MACIO_EN_DMA&t;&t;0x00000200
DECL|macro|CLOCK_INIT_DONE
mdefine_line|#define CLOCK_INIT_DONE&t;&t;1
DECL|variable|clk_state
r_static
r_int
id|clk_state
suffix:semicolon
DECL|variable|clk_ctrl
r_static
r_volatile
r_int
r_char
op_star
id|clk_ctrl
suffix:semicolon
DECL|variable|cpu_pwr_save
r_void
(paren
op_star
id|cpu_pwr_save
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|function|ldphys
r_static
r_inline
r_int
r_int
id|ldphys
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|data
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;tlda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|data
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_BYPASS
)paren
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
DECL|function|clk_init
r_static
r_void
id|clk_init
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov 0x6c, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;mov 0x4c, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;mov 0xdf, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;stb %%g1, [%0+3]&bslash;n&bslash;t&quot;
l_string|&quot;stb %%g2, [%0+3]&bslash;n&bslash;t&quot;
l_string|&quot;stb %%g3, [%0+3]&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|clk_ctrl
)paren
suffix:colon
l_string|&quot;g1&quot;
comma
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
)paren
suffix:semicolon
)brace
DECL|function|clk_slow
r_static
r_void
id|clk_slow
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov 0xcc, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;mov 0x4c, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;mov 0xcf, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;mov 0xdf, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;stb %%g2, [%0+3]&bslash;n&bslash;t&quot;
l_string|&quot;stb %%g3, [%0+3]&bslash;n&bslash;t&quot;
l_string|&quot;stb %%g4, [%0+3]&bslash;n&bslash;t&quot;
l_string|&quot;stb %%g5, [%0+3]&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|clk_ctrl
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
)paren
suffix:semicolon
)brace
DECL|function|tsu_clockstop
r_static
r_void
id|tsu_clockstop
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|mcsr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clk_ctrl
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|clk_state
op_amp
id|CLOCK_INIT_DONE
)paren
)paren
(brace
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|clk_init
c_func
(paren
)paren
suffix:semicolon
id|clk_state
op_or_assign
id|CLOCK_INIT_DONE
suffix:semicolon
multiline_comment|/* all done */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|clk_ctrl
(braket
l_int|2
)braket
op_amp
l_int|1
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* no speed up yet */
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* if SCSI DMA in progress, don&squot;t slow clock */
id|mcsr
op_assign
id|ldphys
c_func
(paren
id|MACIO_SCSI_CSR_ADDR
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mcsr
op_amp
id|MACIO_EN_DMA
)paren
op_ne
l_int|0
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* TODO... the minimum clock setting ought to increase the&n;&t; * memory refresh interval..&n;&t; */
id|clk_slow
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|swift_clockstop
r_static
r_void
id|swift_clockstop
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|clk_ctrl
)paren
r_return
suffix:semicolon
id|clk_ctrl
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|clock_stop_probe
r_void
id|__init
id|clock_stop_probe
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|node
comma
id|clk_nd
suffix:semicolon
r_char
id|name
(braket
l_int|20
)braket
suffix:semicolon
id|prom_getstring
c_func
(paren
id|prom_root_node
comma
l_string|&quot;name&quot;
comma
id|name
comma
r_sizeof
(paren
id|name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|name
comma
l_string|&quot;Tadpole&quot;
comma
l_int|7
)paren
)paren
r_return
suffix:semicolon
id|node
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
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
id|clk_nd
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;clk-ctrl&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clk_nd
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Clock Stopping h/w detected... &quot;
)paren
suffix:semicolon
id|clk_ctrl
op_assign
(paren
r_char
op_star
)paren
id|prom_getint
c_func
(paren
id|clk_nd
comma
l_string|&quot;address&quot;
)paren
suffix:semicolon
id|clk_state
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|name
(braket
l_int|10
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|cpu_pwr_save
op_assign
id|tsu_clockstop
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;enabled (S3)&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|name
(braket
l_int|10
)braket
op_eq
l_char|&squot;X&squot;
)paren
op_logical_or
(paren
id|name
(braket
l_int|10
)braket
op_eq
l_char|&squot;G&squot;
)paren
)paren
(brace
id|cpu_pwr_save
op_assign
id|swift_clockstop
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;enabled (%s)&bslash;n&quot;
comma
id|name
op_plus
l_int|7
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;disabled %s&bslash;n&quot;
comma
id|name
op_plus
l_int|7
)paren
suffix:semicolon
)brace
eof
