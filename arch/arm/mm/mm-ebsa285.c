multiline_comment|/*&n; * arch/arm/mm/mm-ebsa285.c&n; *&n; * Extra MM routines for the EBSA285 architecture&n; *&n; * Copyright (C) 1998 Russell King, Dave Gilbert.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/proc/mm-init.h&gt;
multiline_comment|/*&n; * These two functions convert PCI bus addresses to virtual addresses&n; * and back again.&n; */
DECL|function|__virt_to_bus
r_int
r_int
id|__virt_to_bus
c_func
(paren
r_int
r_int
id|res
)paren
(brace
r_if
c_cond
(paren
id|res
OL
id|PAGE_OFFSET
op_logical_or
id|res
op_ge
l_int|0xD0000000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;__virt_to_bus: invalid address 0x%08lx&bslash;n&quot;
comma
id|res
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_ERRORS
id|__backtrace
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
id|res
op_assign
(paren
id|res
op_minus
id|PAGE_OFFSET
)paren
op_plus
l_int|0x10000000
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|__bus_to_virt
r_int
r_int
id|__bus_to_virt
c_func
(paren
r_int
r_int
id|res
)paren
(brace
r_if
c_cond
(paren
id|res
OL
l_int|0x10000000
op_logical_or
id|res
op_ge
l_int|0x20000000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;__bus_to_virt: invalid address 0x%08lx&bslash;n&quot;
comma
id|res
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_ERRORS
id|__backtrace
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
id|res
op_assign
(paren
id|res
op_minus
l_int|0x10000000
)paren
op_plus
id|PAGE_OFFSET
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*    Logical    Physical&n; * 0xfff00000&t;0x40000000&t;X-Bus&n; * 0xffe00000&t;0x7c000000&t;PCI I/O space&n; * 0xfe000000&t;0x42000000&t;CSR&n; * 0xfd000000&t;0x78000000&t;Outbound write flush&n; * 0xfc000000&t;0x79000000&t;PCI IACK/special space&n; * 0xf9000000&t;0x7a000000&t;PCI Config type 1&n; * 0xf8000000&t;0x7b000000&t;PCI Config type 0&n; */
multiline_comment|/*&n; * This is to allow us to fiddle with the EEPROM&n; *  This entry will go away in time, once the fmu&n; *  can mmap() the flash.&n; *&n; * These ones are so that we can fiddle&n; *  with the various cards (eg VGA)&n; *  until we&squot;re happy with them...&n; */
DECL|macro|MAPPING
mdefine_line|#define MAPPING &bslash;&n;&t;{ 0xd8000000, 0x41000000, 0x00400000, DOMAIN_USER, 1, 1 },&t;/* EEPROM */&t;    &bslash;&n;&t;{ 0xdc000000, 0x7c000000, 0x00100000, DOMAIN_USER, 1, 1 },&t;/* VGA */&t;    &bslash;&n;&t;{ 0xe0000000, 0x80000000, 0x10000000, DOMAIN_USER, 1, 1 },&t;/* VGA */&t;    &bslash;&n;&t;{ 0xf8000000, 0x7b000000, 0x01000000, DOMAIN_IO  , 0, 1 },&t;/* Type 0 Config */ &bslash;&n;&t;{ 0xf9000000, 0x7a000000, 0x01000000, DOMAIN_IO  , 0, 1 },&t;/* Type 1 Config */ &bslash;&n;&t;{ 0xfc000000, 0x79000000, 0x01000000, DOMAIN_IO  , 0, 1 },&t;/* PCI IACK&t; */ &bslash;&n;&t;{ 0xfd000000, 0x78000000, 0x01000000, DOMAIN_IO  , 0, 1 },&t;/* Outbound wflsh*/ &bslash;&n;&t;{ 0xfe000000, 0x42000000, 0x01000000, DOMAIN_IO  , 0, 1 },&t;/* CSR&t;&t; */ &bslash;&n;&t;{ 0xffe00000, 0x7c000000, 0x00100000, DOMAIN_IO  , 0, 1 },&t;/* PCI I/O&t; */ &bslash;&n;&t;{ 0xfff00000, 0x40000000, 0x00100000, DOMAIN_IO  , 0, 1 },&t;/* X-Bus&t; */
macro_line|#include &quot;mm-armv.c&quot;
eof
