multiline_comment|/*&n; * arch/arm/mm/mm-nexuspci.c&n; *  from arch/arm/mm/mm-ebsa110.c&n; *&n; * Extra MM routines for the FTV/PCI architecture&n; *&n; * Copyright (C) 1998-1999 Phil Blundell&n; * Copyright (C) 1998-1999 Russell King&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;map.h&quot;
DECL|variable|__initdata
r_struct
id|map_desc
id|io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|INTCONT_BASE
comma
id|INTCONT_START
comma
l_int|0x00001000
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
(brace
id|PLX_BASE
comma
id|PLX_START
comma
l_int|0x00001000
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
(brace
id|PCIO_BASE
comma
id|PLX_IO_START
comma
l_int|0x00100000
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
(brace
id|DUART_BASE
comma
id|DUART_START
comma
l_int|0x00001000
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
(brace
id|STATUS_BASE
comma
id|STATUS_START
comma
l_int|0x00001000
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
DECL|macro|SIZE
mdefine_line|#define SIZE(x) (sizeof(x) / sizeof(x[0]))
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
