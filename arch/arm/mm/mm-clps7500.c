multiline_comment|/*&n; * arch/arm/mm/mm-cl7500.c&n; *&n; * Extra MM routines for CL7500 architecture&n; *&n; * Copyright (C) 1998 Russell King&n; * Copyright (C) 1999 Nexus Electronics Ltd&n; */
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
)brace
comma
multiline_comment|/* IO space&t;*/
(brace
id|ISA_BASE
comma
id|ISA_START
comma
id|ISA_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* ISA space&t;*/
(brace
id|FLASH_BASE
comma
id|FLASH_START
comma
id|FLASH_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* Flash&t;*/
(brace
id|LED_BASE
comma
id|LED_START
comma
id|LED_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
)brace
multiline_comment|/* LED&t;&t;*/
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
