multiline_comment|/*&n; * arch/arm/mm/mm-vnc.c&n; *&n; * Extra MM routines for the Corel VNC architecture&n; *&n; * Copyright (C) 1998 Russell King&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/proc/mm-init.h&gt;
multiline_comment|/* Table describing the MMU translation mapping&n; * mainly used to set up the I/O mappings.&n; */
DECL|macro|MAPPING
mdefine_line|#define MAPPING &bslash;&n;  { 0xe0000000, DC21285_PCI_IO,&t;&t;      0x00100000, DOMAIN_IO, 0, 1 }, /* PCI I/O&t;&t;*/ &bslash;&n;  { 0xe0100000, DC21285_PCI_TYPE_0_CONFIG,    0x00f00000, DOMAIN_IO, 0, 1 }, /* Type 0 Config&t;*/ &bslash;&n;  { 0xe1000000, DC21285_ARMCSR_BASE,&t;      0x00100000, DOMAIN_IO, 0, 1 }, /* ARM CSR&t;&t;*/ &bslash;&n;  { 0xe1100000, DC21285_PCI_IACK,&t;      0x00100000, DOMAIN_IO, 0, 1 }, /* PCI IACK&t;*/ &bslash;&n;  { 0xe1300000, DC21285_OUTBOUND_WRITE_FLUSH, 0x00100000, DOMAIN_IO, 0, 1 }, /* Out wrflsh&t;*/ &bslash;&n;  { 0xe1400000, DC21285_OUTBOUND_WRITE_FLUSH, 0x00100000, DOMAIN_IO, 0, 1 }, /* Out wrflsh&t;*/ &bslash;&n;  { 0xe1500000, DC21285_OUTBOUND_WRITE_FLUSH, 0x00100000, DOMAIN_IO, 0, 1 }, /* Out wrflsh&t;*/ &bslash;&n;  { 0xe1600000, DC21285_OUTBOUND_WRITE_FLUSH, 0x00100000, DOMAIN_IO, 0, 1 }, /* Out wrflsh&t;*/ &bslash;&n;  { 0xe1700000, DC21285_OUTBOUND_WRITE_FLUSH, 0x00100000, DOMAIN_IO, 0, 1 }, /* Out wrflsh&t;*/ &bslash;&n;  { 0xe1800000, DC21285_FLASH,                0x00800000, DOMAIN_IO, 0, 1 }  /* Flash&t;&t;*/
macro_line|#include &quot;mm-armv.c&quot;
eof
