multiline_comment|/*&n; * Tiny Tyne DMA buffer allocator&n; *&n; * Copyright (C) 1995 Ralf Baechle&n; */
macro_line|#include &lt;linux/autoconf.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#ifdef CONFIG_DESKSTATION_TYNE
DECL|variable|allocated
r_static
r_int
r_int
id|allocated
suffix:semicolon
multiline_comment|/*&n; * Not very sophisticated, but should suffice for now...&n; */
DECL|function|deskstation_tyne_dma_alloc
r_int
r_int
id|deskstation_tyne_dma_alloc
c_func
(paren
r_int
id|size
)paren
(brace
r_int
r_int
id|ret
op_assign
id|allocated
suffix:semicolon
id|allocated
op_add_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|allocated
OG
id|boot_info.dma_cache_size
)paren
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|deskstation_tyne_dma_init
r_void
id|deskstation_tyne_dma_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|boot_info.machtype
op_ne
id|MACH_DESKSTATION_TYNE
)paren
r_return
suffix:semicolon
id|allocated
op_assign
l_int|0
suffix:semicolon
id|printk
(paren
l_string|&quot;Deskstation Tyne DMA (%luk) buffer initialized.&bslash;n&quot;
comma
id|boot_info.dma_cache_size
op_rshift
l_int|10
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_DESKSTATION_TYNE */
eof
