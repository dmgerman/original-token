multiline_comment|/*&n; * linux/include/asm-arm/arch-vnc/hardware.h&n; *&n; * Copyright (C) 1998 Corel Computer/Russell King.&n; *&n; * This file contains the hardware definitions of the VNC.&n; */
multiline_comment|/*    Logical    Physical&n; * 0xffe00000&t;0x7c000000&t;PCI I/O space&n; * 0xfe000000&t;0x42000000&t;CSR&n; * 0xfd000000&t;0x78000000&t;Outbound write flush&n; * 0xfc000000&t;0x79000000&t;PCI IACK/special space&n; * 0xf9000000&t;0x7a000000&t;PCI Config type 1&n; * 0xf8000000&t;0x7b000000&t;PCI Config type 0&n; * &n; */
macro_line|#include &lt;asm/dec21285.h&gt;
DECL|macro|IO_BASE_ARM_CSR
mdefine_line|#define IO_BASE_ARM_CSR&t;&t;0xfe000000
DECL|macro|PCI_IACK
mdefine_line|#define PCI_IACK&t;&t;0xfc000000
multiline_comment|/* LEDs */
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
multiline_comment|/* PIC irq control */
DECL|macro|PIC_LO
mdefine_line|#define PIC_LO&t;&t;&t;0x20
DECL|macro|PIC_MASK_LO
mdefine_line|#define PIC_MASK_LO&t;&t;0x21
DECL|macro|PIC_HI
mdefine_line|#define PIC_HI&t;&t;&t;0xA0
DECL|macro|PIC_MASK_HI
mdefine_line|#define PIC_MASK_HI&t;&t;0xA1
DECL|macro|IO_END
mdefine_line|#define IO_END&t;&t;&t;0xffffffff
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xe0000000
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;(IO_END - IO_BASE)
DECL|macro|HAS_PCIO
mdefine_line|#define HAS_PCIO
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xffe00000
DECL|macro|KERNTOPHYS
mdefine_line|#define KERNTOPHYS(a)&t;&t;((unsigned long)(&amp;a))
singleline_comment|//#define PARAMS_OFFSET&t;&t;0x0100
singleline_comment|//#define PARAMS_BASE&t;&t;(PAGE_OFFSET + PARAMS_OFFSET)
DECL|macro|SAFE_ADDR
mdefine_line|#define SAFE_ADDR&t;&t;0x50000000
eof
