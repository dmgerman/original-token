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
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0x50000000
multiline_comment|/* GPIO pins */
DECL|macro|GPIO_CCLK
mdefine_line|#define GPIO_CCLK&t;&t;0x800
DECL|macro|GPIO_DSCLK
mdefine_line|#define GPIO_DSCLK&t;&t;0x400
DECL|macro|GPIO_E2CLK
mdefine_line|#define GPIO_E2CLK&t;&t;0x200
DECL|macro|GPIO_IOLOAD
mdefine_line|#define GPIO_IOLOAD&t;&t;0x100
DECL|macro|GPIO_RED_LED
mdefine_line|#define GPIO_RED_LED&t;&t;0x080
DECL|macro|GPIO_WDTIMER
mdefine_line|#define GPIO_WDTIMER&t;&t;0x040
DECL|macro|GPIO_DATA
mdefine_line|#define GPIO_DATA&t;&t;0x020
DECL|macro|GPIO_IOCLK
mdefine_line|#define GPIO_IOCLK&t;&t;0x010
DECL|macro|GPIO_DONE
mdefine_line|#define GPIO_DONE&t;&t;0x008
DECL|macro|GPIO_FAN
mdefine_line|#define GPIO_FAN&t;&t;0x004
DECL|macro|GPIO_GREEN_LED
mdefine_line|#define GPIO_GREEN_LED&t;&t;0x002
DECL|macro|GPIO_RESET
mdefine_line|#define GPIO_RESET&t;&t;0x001
multiline_comment|/* CPLD pins */
DECL|macro|CPLD_DSRESET
mdefine_line|#define CPLD_DSRESET&t;&t;8
DECL|macro|CPLD_UNMUTE
mdefine_line|#define CPLD_UNMUTE&t;&t;2
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|gpio_modify_op
c_func
(paren
r_int
id|mask
comma
r_int
id|set
)paren
suffix:semicolon
r_extern
r_void
id|gpio_modify_io
c_func
(paren
r_int
id|mask
comma
r_int
id|in
)paren
suffix:semicolon
r_extern
r_int
id|gpio_read
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpld_modify
c_func
(paren
r_int
id|mask
comma
r_int
id|set
)paren
suffix:semicolon
macro_line|#endif
eof
