multiline_comment|/*&n; * arch/arm/mm/mm-tbox.c&n; *  from arch/arm/mm/mm-ebsa110.c&n; *&n; * Extra MM routines for the Tbox architecture&n; *&n; * Copyright (C) 1998 Phil Blundell&n; * Copyright (C) 1998 Russell King&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/proc/mm-init.h&gt;
multiline_comment|/*    Logical    Physical&n; * 0xffff1000&t;0x00100000&t;DMA registers&n; * 0xffff2000&t;0x00200000&t;MPEG&n; * 0xffff3000&t;0x00300000&t;FPGA1 local control&n; * 0xffff4000&t;0x00400000&t;External serial&n; * 0xffff5000&t;0x00500000&t;Internal serial&n; * 0xffff6000&t;0x00600000&t;Parallel&n; * 0xffff7000&t;0x00700000&t;Interrupt control&n; * 0xffff8000&t;0x00800000&t;Computer video&n; * 0xffff9000&t;0x00900000&t;Control register 0&n; * 0xffffs000&t;0x00a00000&t;Control register 1&n; * 0xffffb000&t;0x00b00000&t;Control register 2&n; * 0xffffc000&t;0x00c00000&t;FPGA2 local control&n; * 0xffffd000&t;0x00d00000&t;Interrupt reset&n; * 0xffffe000&t;0x00e00000&t;MPEG DMA throttle&n; */
DECL|macro|MAPPING
mdefine_line|#define MAPPING&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;{ 0xffff0000, 0x01000000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffff1000, 0x00100000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffff2000, 0x00200000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffff3000, 0x00300000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffff4000, 0x00400000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xfe000000, 0x00400000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffff5000, 0x00500000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffff6000, 0x00600000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffff7000, 0x00700000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffff8000, 0x00800000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffff9000, 0x00900000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffffa000, 0x00a00000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffffb000, 0x00b00000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffffc000, 0x00c00000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffffd000, 0x00d00000, 0x00001000, DOMAIN_IO, 0, 1 },&t;&bslash;&n; &t;{ 0xffffe000, 0x00e00000, 0x00001000, DOMAIN_IO, 0, 1 }
macro_line|#include &quot;mm-armv.c&quot;
eof
