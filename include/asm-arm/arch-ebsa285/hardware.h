multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/hardware.h&n; *&n; * Copyright (C) 1998 Russell King.&n; *&n; * This file contains the hardware definitions of the EBSA-285.&n; */
multiline_comment|/*    Logical    Physical&n; * 0xfff00000&t;0x40000000&t;X-Bus&n; * 0xffe00000&t;0x7c000000&t;PCI I/O space&n; *&n; * 0xfe000000&t;0x42000000&t;CSR&n; * 0xfd000000&t;0x78000000&t;Outbound write flush&n; * 0xfc000000&t;0x79000000&t;PCI IACK/special space&n; *&n; * 0xf9000000&t;0x7a010000&t;PCI Config type 1&n; * 0xf8000000&t;0x7b010000&t;PCI Config type 0&n; * &n; */
macro_line|#include &lt;asm/dec21285.h&gt;
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xe0000000
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xffe00000
DECL|macro|PCI_IACK
mdefine_line|#define PCI_IACK&t;&t;0xfc000000 
DECL|macro|XBUS_LEDS
mdefine_line|#define XBUS_LEDS&t;&t;((volatile unsigned char *)0xfff12000)
DECL|macro|XBUS_LED_AMBER
mdefine_line|#define XBUS_LED_AMBER&t;&t;(1 &lt;&lt; 0)
DECL|macro|XBUS_LED_GREEN
mdefine_line|#define XBUS_LED_GREEN&t;&t;(1 &lt;&lt; 1)
DECL|macro|XBUS_LED_RED
mdefine_line|#define XBUS_LED_RED&t;&t;(1 &lt;&lt; 2)
DECL|macro|XBUS_LED_TOGGLE
mdefine_line|#define XBUS_LED_TOGGLE&t;&t;(1 &lt;&lt; 8)
DECL|macro|XBUS_SWITCH
mdefine_line|#define XBUS_SWITCH&t;&t;((volatile unsigned char *)0xfff12000)
DECL|macro|XBUS_SWITCH_SWITCH
mdefine_line|#define XBUS_SWITCH_SWITCH&t;((*XBUS_SWITCH) &amp; 15)
DECL|macro|XBUS_SWITCH_J17_13
mdefine_line|#define XBUS_SWITCH_J17_13&t;((*XBUS_SWITCH) &amp; (1 &lt;&lt; 4))
DECL|macro|XBUS_SWITCH_J17_11
mdefine_line|#define XBUS_SWITCH_J17_11&t;((*XBUS_SWITCH) &amp; (1 &lt;&lt; 5))
DECL|macro|XBUS_SWITCH_J17_9
mdefine_line|#define XBUS_SWITCH_J17_9&t;((*XBUS_SWITCH) &amp; (1 &lt;&lt; 6))
DECL|macro|KERNTOPHYS
mdefine_line|#define KERNTOPHYS(a)&t;&t;((unsigned long)(&amp;a))
DECL|macro|PARAMS_OFFSET
mdefine_line|#define PARAMS_OFFSET&t;&t;0x0100
DECL|macro|PARAMS_BASE
mdefine_line|#define PARAMS_BASE&t;&t;(PAGE_OFFSET + PARAMS_OFFSET)
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0x50000000
eof
