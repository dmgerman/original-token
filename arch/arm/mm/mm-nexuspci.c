multiline_comment|/*&n; * arch/arm/mm/mm-nexuspci.c&n; *  from arch/arm/mm/mm-ebsa110.c&n; *&n; * Extra MM routines for the NexusPCI architecture&n; *&n; * Copyright (C) 1998 Phil Blundell&n; * Copyright (C) 1998 Russell King&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/proc/mm-init.h&gt;
DECL|macro|MAPPING
mdefine_line|#define MAPPING&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; &t;{ 0xfff00000, 0x10000000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffe00000, 0x20000000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffc00000, 0x60000000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xfe000000, 0x80000000, 0x00100000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xfd000000, 0x88000000, 0x00100000, DOMAIN_IO, 0, 1 }
macro_line|#include &quot;mm-armv.c&quot;
eof
