multiline_comment|/*&n; * arch/arm/mm/mm-rpc.c&n; *&n; * Extra MM routines for RiscPC architecture&n; *&n; * Copyright (C) 1998-1999 Russell King&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/proc/domain.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &quot;map.h&quot;
DECL|macro|SIZE
mdefine_line|#define SIZE(x) (sizeof(x) / sizeof(x[0]))
DECL|variable|__initdata
r_struct
id|map_desc
id|io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* VRAM&t;&t;*/
(brace
id|SCREEN_BASE
comma
id|SCREEN_START
comma
l_int|2
op_star
l_int|1048576
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IO space&t;*/
(brace
id|IO_BASE
comma
id|IO_START
comma
id|IO_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* EASI space&t;*/
(brace
id|EASI_BASE
comma
id|EASI_START
comma
id|EASI_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|io_desc_size
r_int
r_int
id|__initdata
id|io_desc_size
op_assign
id|SIZE
c_func
(paren
id|io_desc
)paren
suffix:semicolon
eof
