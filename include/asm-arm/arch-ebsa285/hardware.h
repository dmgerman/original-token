multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/hardware.h&n; *&n; * Copyright (C) 1998 Russell King.&n; *&n; * This file contains the hardware definitions of the EBSA-285.&n; */
multiline_comment|/*    Logical    Physical&n; * 0xfff00000&t;0x40000000&t;X-Bus&n; * 0xffe00000&t;0x7c000000&t;PCI I/O space&n; *&n; * 0xfe000000&t;0x42000000&t;CSR&n; * 0xfd000000&t;0x78000000&t;Outbound write flush&n; * 0xfc000000&t;0x79000000&t;PCI IACK/special space&n; *&n; * 0xf9030000&t;0x7a080000&t;PCI Config type 1 card 4&n; * 0xf9020000&t;0x7a040000&t;PCI Config type 1 card 3&n; * 0xf9010000&t;0x7a020000&t;PCI Config type 1 card 2&n; * 0xf9000000&t;0x7a010000&t;PCI Config type 1 card 1&n; *&n; * 0xf8030000&t;0x7b080000&t;PCI Config type 0 card 4&n; * 0xf8020000&t;0x7b040000&t;PCI Config type 0 card 3&n; * 0xf8010000&t;0x7b020000&t;PCI Config type 0 card 2&n; * 0xf8000000&t;0x7b010000&t;PCI Config type 0 card 1&n; * &n; */
DECL|macro|IO_END
mdefine_line|#define IO_END&t;&t;&t;0xffffffff
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xe0000000
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;(IO_END - IO_BASE)
DECL|macro|HAS_PCIO
mdefine_line|#define HAS_PCIO
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
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xffe00000
DECL|macro|CSR_SA110_CNTL
mdefine_line|#define CSR_SA110_CNTL&t;&t;((volatile unsigned long *)0xfe00013c)
DECL|macro|CSR_PCIADDR_EXTN
mdefine_line|#define CSR_PCIADDR_EXTN&t;((volatile unsigned long *)0xfe000140)
DECL|macro|CSR_PREFETCHMEMRANGE
mdefine_line|#define CSR_PREFETCHMEMRANGE&t;((volatile unsigned long *)0xfe000144)
DECL|macro|CSR_XBUS_CYCLE
mdefine_line|#define CSR_XBUS_CYCLE&t;&t;((volatile unsigned long *)0xfe000148)
DECL|macro|CSR_XBUS_IOSTROBE
mdefine_line|#define CSR_XBUS_IOSTROBE&t;((volatile unsigned long *)0xfe00014c)
DECL|macro|CSR_DOORBELL_PCI
mdefine_line|#define CSR_DOORBELL_PCI&t;((volatile unsigned long *)0xfe000150)
DECL|macro|CSR_DOORBELL_SA110
mdefine_line|#define CSR_DOORBELL_SA110&t;((volatile unsigned long *)0xfe000154)
DECL|macro|CSR_UARTDR
mdefine_line|#define CSR_UARTDR&t;&t;((volatile unsigned long *)0xfe000160)
DECL|macro|CSR_RXSTAT
mdefine_line|#define CSR_RXSTAT&t;&t;((volatile unsigned long *)0xfe000164)
DECL|macro|CSR_H_UBRLCR
mdefine_line|#define CSR_H_UBRLCR&t;&t;((volatile unsigned long *)0xfe000168)
DECL|macro|CSR_M_UBRLCR
mdefine_line|#define CSR_M_UBRLCR&t;&t;((volatile unsigned long *)0xfe00016c)
DECL|macro|CSR_L_UBRLCR
mdefine_line|#define CSR_L_UBRLCR&t;&t;((volatile unsigned long *)0xfe000170)
DECL|macro|CSR_UARTCON
mdefine_line|#define CSR_UARTCON&t;&t;((volatile unsigned long *)0xfe000174)
DECL|macro|CSR_UARTFLG
mdefine_line|#define CSR_UARTFLG&t;&t;((volatile unsigned long *)0xfe000178)
DECL|macro|CSR_IRQ_STATUS
mdefine_line|#define CSR_IRQ_STATUS&t;&t;((volatile unsigned long *)0xfe000180)
DECL|macro|CSR_IRQ_RAWSTATUS
mdefine_line|#define CSR_IRQ_RAWSTATUS&t;((volatile unsigned long *)0xfe000184)
DECL|macro|CSR_IRQ_ENABLE
mdefine_line|#define CSR_IRQ_ENABLE&t;&t;((volatile unsigned long *)0xfe000188)
DECL|macro|CSR_IRQ_DISABLE
mdefine_line|#define CSR_IRQ_DISABLE&t;&t;((volatile unsigned long *)0xfe00018c)
DECL|macro|CSR_IRQ_SOFT
mdefine_line|#define CSR_IRQ_SOFT&t;&t;((volatile unsigned long *)0xfe000190)
DECL|macro|CSR_FIQ_STATUS
mdefine_line|#define CSR_FIQ_STATUS&t;&t;((volatile unsigned long *)0xfe000280)
DECL|macro|CSR_FIQ_RAWSTATUS
mdefine_line|#define CSR_FIQ_RAWSTATUS&t;((volatile unsigned long *)0xfe000284)
DECL|macro|CSR_FIQ_ENABLE
mdefine_line|#define CSR_FIQ_ENABLE&t;&t;((volatile unsigned long *)0xfe000288)
DECL|macro|CSR_FIQ_DISABLE
mdefine_line|#define CSR_FIQ_DISABLE&t;&t;((volatile unsigned long *)0xfe00028c)
DECL|macro|CSR_FIQ_SOFT
mdefine_line|#define CSR_FIQ_SOFT&t;&t;((volatile unsigned long *)0xfe000290)
DECL|macro|CSR_TIMER1_LOAD
mdefine_line|#define CSR_TIMER1_LOAD&t;&t;((volatile unsigned long *)0xfe000300)
DECL|macro|CSR_TIMER1_VALUE
mdefine_line|#define CSR_TIMER1_VALUE&t;((volatile unsigned long *)0xfe000304)
DECL|macro|CSR_TIMER1_CNTL
mdefine_line|#define CSR_TIMER1_CNTL&t;&t;((volatile unsigned long *)0xfe000308)
DECL|macro|CSR_TIMER1_CLR
mdefine_line|#define CSR_TIMER1_CLR&t;&t;((volatile unsigned long *)0xfe00030c)
DECL|macro|CSR_TIMER2_LOAD
mdefine_line|#define CSR_TIMER2_LOAD&t;&t;((volatile unsigned long *)0xfe000320)
DECL|macro|CSR_TIMER2_VALUE
mdefine_line|#define CSR_TIMER2_VALUE&t;((volatile unsigned long *)0xfe000324)
DECL|macro|CSR_TIMER2_CNTL
mdefine_line|#define CSR_TIMER2_CNTL&t;&t;((volatile unsigned long *)0xfe000328)
DECL|macro|CSR_TIMER2_CLR
mdefine_line|#define CSR_TIMER2_CLR&t;&t;((volatile unsigned long *)0xfe00032c)
DECL|macro|CSR_TIMER3_LOAD
mdefine_line|#define CSR_TIMER3_LOAD&t;&t;((volatile unsigned long *)0xfe000340)
DECL|macro|CSR_TIMER3_VALUE
mdefine_line|#define CSR_TIMER3_VALUE&t;((volatile unsigned long *)0xfe000344)
DECL|macro|CSR_TIMER3_CNTL
mdefine_line|#define CSR_TIMER3_CNTL&t;&t;((volatile unsigned long *)0xfe000348)
DECL|macro|CSR_TIMER3_CLR
mdefine_line|#define CSR_TIMER3_CLR&t;&t;((volatile unsigned long *)0xfe00034c)
DECL|macro|CSR_TIMER4_LOAD
mdefine_line|#define CSR_TIMER4_LOAD&t;&t;((volatile unsigned long *)0xfe000360)
DECL|macro|CSR_TIMER4_VALUE
mdefine_line|#define CSR_TIMER4_VALUE&t;((volatile unsigned long *)0xfe000364)
DECL|macro|CSR_TIMER4_CNTL
mdefine_line|#define CSR_TIMER4_CNTL&t;&t;((volatile unsigned long *)0xfe000368)
DECL|macro|CSR_TIMER4_CLR
mdefine_line|#define CSR_TIMER4_CLR&t;&t;((volatile unsigned long *)0xfe00036c)
DECL|macro|TIMER_CNTL_ENABLE
mdefine_line|#define TIMER_CNTL_ENABLE&t;(1 &lt;&lt; 7)
DECL|macro|TIMER_CNTL_AUTORELOAD
mdefine_line|#define TIMER_CNTL_AUTORELOAD&t;(1 &lt;&lt; 6)
DECL|macro|TIMER_CNTL_DIV1
mdefine_line|#define TIMER_CNTL_DIV1&t;&t;(0)
DECL|macro|TIMER_CNTL_DIV16
mdefine_line|#define TIMER_CNTL_DIV16&t;(1 &lt;&lt; 2)
DECL|macro|TIMER_CNTL_DIV256
mdefine_line|#define TIMER_CNTL_DIV256&t;(2 &lt;&lt; 2)
DECL|macro|TIMER_CNTL_CNTEXT
mdefine_line|#define TIMER_CNTL_CNTEXT&t;(3 &lt;&lt; 2)
DECL|macro|KERNTOPHYS
mdefine_line|#define KERNTOPHYS(a)&t;&t;((unsigned long)(&amp;a))
DECL|macro|PARAMS_OFFSET
mdefine_line|#define PARAMS_OFFSET&t;&t;0x0100
DECL|macro|PARAMS_BASE
mdefine_line|#define PARAMS_BASE&t;&t;(PAGE_OFFSET + PARAMS_OFFSET)
DECL|macro|SAFE_ADDR
mdefine_line|#define SAFE_ADDR&t;&t;0x50000000
eof
