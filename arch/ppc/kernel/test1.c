macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*pgd_t *swapper_pg_dir;*/
DECL|variable|BAT0
id|BAT
id|BAT0
op_assign
(brace
(brace
l_int|0x80000000
op_rshift
l_int|17
comma
multiline_comment|/* bepi */
id|BL_256M
comma
multiline_comment|/* bl */
l_int|1
comma
multiline_comment|/* vs */
l_int|1
comma
multiline_comment|/* vp */
)brace
comma
(brace
l_int|0x80000000
op_rshift
l_int|17
comma
multiline_comment|/* brpn */
l_int|1
comma
multiline_comment|/* w */
l_int|1
comma
multiline_comment|/* i (cache disabled) */
l_int|0
comma
multiline_comment|/* m */
l_int|0
comma
multiline_comment|/* g */
id|BPP_RW
multiline_comment|/* pp */
)brace
)brace
suffix:semicolon
DECL|variable|BAT1
id|BAT
id|BAT1
op_assign
(brace
(brace
l_int|0xC0000000
op_rshift
l_int|17
comma
multiline_comment|/* bepi */
id|BL_256M
comma
multiline_comment|/* bl */
l_int|1
comma
multiline_comment|/* vs */
l_int|1
comma
multiline_comment|/* vp */
)brace
comma
(brace
l_int|0xC0000000
op_rshift
l_int|17
comma
multiline_comment|/* brpn */
l_int|1
comma
multiline_comment|/* w */
l_int|1
comma
multiline_comment|/* i (cache disabled) */
l_int|0
comma
multiline_comment|/* m */
l_int|0
comma
multiline_comment|/* g */
id|BPP_RW
multiline_comment|/* pp */
)brace
)brace
suffix:semicolon
DECL|variable|BAT2
id|BAT
id|BAT2
op_assign
(brace
(brace
l_int|0x00000000
op_rshift
l_int|17
comma
multiline_comment|/* bepi */
id|BL_256M
comma
multiline_comment|/* bl */
l_int|0
comma
multiline_comment|/* vs */
l_int|0
comma
multiline_comment|/* vp */
)brace
comma
(brace
l_int|0x00000000
op_rshift
l_int|17
comma
multiline_comment|/* brpn */
l_int|1
comma
multiline_comment|/* w */
l_int|1
comma
multiline_comment|/* i (cache disabled) */
l_int|0
comma
multiline_comment|/* m */
l_int|0
comma
multiline_comment|/* g */
id|BPP_RW
multiline_comment|/* pp */
)brace
)brace
suffix:semicolon
DECL|variable|BAT3
id|BAT
id|BAT3
op_assign
(brace
(brace
l_int|0x00000000
op_rshift
l_int|17
comma
multiline_comment|/* bepi */
id|BL_256M
comma
multiline_comment|/* bl */
l_int|0
comma
multiline_comment|/* vs */
l_int|0
comma
multiline_comment|/* vp */
)brace
comma
(brace
l_int|0x00000000
op_rshift
l_int|17
comma
multiline_comment|/* brpn */
l_int|1
comma
multiline_comment|/* w */
l_int|1
comma
multiline_comment|/* i (cache disabled) */
l_int|0
comma
multiline_comment|/* m */
l_int|0
comma
multiline_comment|/* g */
id|BPP_RW
multiline_comment|/* pp */
)brace
)brace
suffix:semicolon
DECL|variable|TMP_BAT2
id|BAT
id|TMP_BAT2
op_assign
(brace
multiline_comment|/* 0x9XXXXXXX -&gt; 0x0XXXXXXX */
(brace
l_int|0x90000000
op_rshift
l_int|17
comma
multiline_comment|/* bepi */
id|BL_256M
comma
multiline_comment|/* bl */
l_int|1
comma
multiline_comment|/* vs */
l_int|1
comma
multiline_comment|/* vp */
)brace
comma
(brace
l_int|0x00000000
op_rshift
l_int|17
comma
multiline_comment|/* brpn */
l_int|1
comma
multiline_comment|/* w */
l_int|0
comma
multiline_comment|/* i (cache enabled) */
l_int|0
comma
multiline_comment|/* m */
l_int|0
comma
multiline_comment|/* g */
id|BPP_RW
multiline_comment|/* pp */
)brace
)brace
suffix:semicolon
DECL|variable|ZERO_BAT
id|BAT
id|ZERO_BAT
op_assign
(brace
multiline_comment|/* 0x0XXXXXXX -&gt; 0x0XXXXXXX */
(brace
l_int|0x00000000
op_rshift
l_int|17
comma
multiline_comment|/* bepi */
id|BL_256M
comma
multiline_comment|/* bl */
l_int|1
comma
multiline_comment|/* vs */
l_int|1
comma
multiline_comment|/* vp */
)brace
comma
(brace
l_int|0x00000000
op_rshift
l_int|17
comma
multiline_comment|/* brpn */
l_int|1
comma
multiline_comment|/* w */
l_int|0
comma
multiline_comment|/* i (cache enabled) */
l_int|0
comma
multiline_comment|/* m */
l_int|0
comma
multiline_comment|/* g */
id|BPP_RW
multiline_comment|/* pp */
)brace
)brace
suffix:semicolon
DECL|variable|OFF_BAT
id|BAT
id|OFF_BAT
op_assign
(brace
multiline_comment|/* 0x0XXXXXXX -&gt; 0x0XXXXXXX */
(brace
l_int|0x00000000
op_rshift
l_int|17
comma
multiline_comment|/* bepi */
id|BL_256M
comma
multiline_comment|/* bl */
l_int|0
comma
multiline_comment|/* vs */
l_int|0
comma
multiline_comment|/* vp */
)brace
comma
(brace
l_int|0x00000000
op_rshift
l_int|17
comma
multiline_comment|/* brpn */
l_int|1
comma
multiline_comment|/* w */
l_int|0
comma
multiline_comment|/* i (cache enabled) */
l_int|0
comma
multiline_comment|/* m */
l_int|0
comma
multiline_comment|/* g */
id|BPP_RW
multiline_comment|/* pp */
)brace
)brace
suffix:semicolon
eof
