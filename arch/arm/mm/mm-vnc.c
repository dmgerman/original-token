multiline_comment|/*&n; * arch/arm/mm/mm-vnc.c&n; *&n; * Extra MM routines for the Corel VNC architecture&n; *&n; * Copyright (C) 1998 Russell King&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/proc/mm-init.h&gt;
macro_line|#include &lt;asm/dec21285.h&gt;
multiline_comment|/* Table describing the MMU translation mapping&n; * mainly used to set up the I/O mappings.&n; */
DECL|macro|MAPPING
mdefine_line|#define MAPPING &bslash;&n;  { 0xd0000000, DC21285_FLASH,&t;&t;      0x00800000, DOMAIN_IO  , 0, 1 },&t;/* Flash&t; */ &bslash;&n;  { 0xe0000000, DC21285_PCI_MEM,&t;      0x18000000, DOMAIN_IO  , 0, 1 },&t;/* PCI Mem &t; */ &bslash;&n;  { 0xf8000000, DC21285_PCI_TYPE_0_CONFIG,    0x01000000, DOMAIN_IO  , 0, 1 },&t;/* Type 0 Config */ &bslash;&n;  { 0xf9000000, DC21285_PCI_TYPE_1_CONFIG,    0x01000000, DOMAIN_IO  , 0, 1 },&t;/* Type 1 Config */ &bslash;&n;  { PCI_IACK,&t;DC21285_PCI_IACK,&t;      0x01000000, DOMAIN_IO  , 0, 1 },&t;/* PCI IACK&t; */ &bslash;&n;  { 0xfd000000, DC21285_OUTBOUND_WRITE_FLUSH, 0x01000000, DOMAIN_IO  , 0, 1 },&t;/* Out wrflsh&t; */ &bslash;&n;  { 0xfe000000, DC21285_ARMCSR_BASE,&t;      0x01000000, DOMAIN_IO  , 0, 1 },&t;/* CSR&t;&t; */ &bslash;&n;  { 0xffe00000, DC21285_PCI_IO, &t;      0x00100000, DOMAIN_IO  , 0, 1 },&t;/* PCI I/O&t; */ &bslash;&n;
macro_line|#include &quot;mm-armv.c&quot;
eof
