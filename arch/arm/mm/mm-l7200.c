multiline_comment|/*&n; *  linux/arch/arm/mm/mm-lusl7200.c&n; *&n; *  Copyright (C) 2000 Steve Hill (sjhill@cotw.com)&n; *&n; *  Extra MM routines for L7200 architecture&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/proc/domain.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|l7200_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
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
(brace
id|IO_BASE_2
comma
id|IO_START_2
comma
id|IO_SIZE_2
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
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|l7200_map_io
r_void
id|__init
id|l7200_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|l7200_io_desc
)paren
suffix:semicolon
)brace
eof
