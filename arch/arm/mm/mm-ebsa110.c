multiline_comment|/*&n; * arch/arm/mm/mm-ebsa110.c&n; *&n; * Extra MM routines for the EBSA-110 architecture&n; *&n; * Copyright (C) 1998 Russell King&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|MAPPING
mdefine_line|#define MAPPING &bslash;&n;&t;{ IO_BASE - PGDIR_SIZE&t;, 0xc0000000&t;, PGDIR_SIZE&t;, DOMAIN_IO, 0, 1 }, &bslash;&n;&t;{ IO_BASE&t;&t;, IO_START&t;, IO_SIZE&t;, DOMAIN_IO, 0, 1 }
macro_line|#include &quot;mm-armv.c&quot;
eof
