multiline_comment|/*&n; * arch/arm/mm/mm-ebsa110.c&n; *&n; * Extra MM routines for the EBSA-110 architecture&n; *&n; * Copyright (C) 1998-1999 Russell King&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &quot;map.h&quot;
DECL|macro|SIZE
mdefine_line|#define SIZE(x) (sizeof(x) / sizeof(x[0]))
DECL|variable|__initdata
r_const
r_struct
id|map_desc
id|io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|IO_BASE
op_minus
id|PGDIR_SIZE
comma
l_int|0xc0000000
comma
id|PGDIR_SIZE
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
