multiline_comment|/*&n; * include/asm-arm/dec21285.h&n; *&n; * Copyright (C) 1998 Russell King&n; */
DECL|macro|DC21285_PCI_IACK
mdefine_line|#define DC21285_PCI_IACK&t;&t;0x79000000
DECL|macro|DC21285_ARMCSR_BASE
mdefine_line|#define DC21285_ARMCSR_BASE&t;&t;0x42000000
DECL|macro|DC21285_PCI_TYPE_0_CONFIG
mdefine_line|#define DC21285_PCI_TYPE_0_CONFIG&t;0x7b000000
DECL|macro|DC21285_PCI_TYPE_1_CONFIG
mdefine_line|#define DC21285_PCI_TYPE_1_CONFIG&t;0x7a000000
DECL|macro|DC21285_OUTBOUND_WRITE_FLUSH
mdefine_line|#define DC21285_OUTBOUND_WRITE_FLUSH&t;0x78000000
DECL|macro|DC21285_FLASH
mdefine_line|#define DC21285_FLASH&t;&t;&t;0x41000000
DECL|macro|DC21285_PCI_IO
mdefine_line|#define DC21285_PCI_IO&t;&t;&t;0x7c000000
DECL|macro|DC21285_PCI_MEM
mdefine_line|#define DC21285_PCI_MEM&t;&t;&t;0x80000000
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * DEC21285&n; */
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
macro_line|#else
DECL|macro|CSR_SA110_CNTL
mdefine_line|#define CSR_SA110_CNTL&t;&t;0x13c
DECL|macro|CSR_PCIADDR_EXTN
mdefine_line|#define CSR_PCIADDR_EXTN&t;0x140
DECL|macro|CSR_PREFETCHMEMRANGE
mdefine_line|#define CSR_PREFETCHMEMRANGE&t;0x144
DECL|macro|CSR_XBUS_CYCLE
mdefine_line|#define CSR_XBUS_CYCLE&t;&t;0x148
DECL|macro|CSR_XBUS_IOSTROBE
mdefine_line|#define CSR_XBUS_IOSTROBE&t;0x14c
DECL|macro|CSR_DOORBELL_PCI
mdefine_line|#define CSR_DOORBELL_PCI&t;0x150
DECL|macro|CSR_DOORBELL_SA110
mdefine_line|#define CSR_DOORBELL_SA110&t;0x154
DECL|macro|CSR_UARTDR
mdefine_line|#define CSR_UARTDR&t;&t;0x160
DECL|macro|CSR_RXSTAT
mdefine_line|#define CSR_RXSTAT&t;&t;0x164
DECL|macro|CSR_H_UBRLCR
mdefine_line|#define CSR_H_UBRLCR&t;&t;0x168
DECL|macro|CSR_M_UBRLCR
mdefine_line|#define CSR_M_UBRLCR&t;&t;0x16c
DECL|macro|CSR_L_UBRLCR
mdefine_line|#define CSR_L_UBRLCR&t;&t;0x170
DECL|macro|CSR_UARTCON
mdefine_line|#define CSR_UARTCON&t;&t;0x174
DECL|macro|CSR_UARTFLG
mdefine_line|#define CSR_UARTFLG&t;&t;0x178
DECL|macro|CSR_IRQ_STATUS
mdefine_line|#define CSR_IRQ_STATUS&t;&t;0x180
DECL|macro|CSR_IRQ_RAWSTATUS
mdefine_line|#define CSR_IRQ_RAWSTATUS&t;0x184
DECL|macro|CSR_IRQ_ENABLE
mdefine_line|#define CSR_IRQ_ENABLE&t;&t;0x188
DECL|macro|CSR_IRQ_DISABLE
mdefine_line|#define CSR_IRQ_DISABLE&t;&t;0x18c
DECL|macro|CSR_IRQ_SOFT
mdefine_line|#define CSR_IRQ_SOFT&t;&t;0x190
DECL|macro|CSR_FIQ_STATUS
mdefine_line|#define CSR_FIQ_STATUS&t;&t;0x280
DECL|macro|CSR_FIQ_RAWSTATUS
mdefine_line|#define CSR_FIQ_RAWSTATUS&t;0x284
DECL|macro|CSR_FIQ_ENABLE
mdefine_line|#define CSR_FIQ_ENABLE&t;&t;0x288
DECL|macro|CSR_FIQ_DISABLE
mdefine_line|#define CSR_FIQ_DISABLE&t;&t;0x28c
DECL|macro|CSR_FIQ_SOFT
mdefine_line|#define CSR_FIQ_SOFT&t;&t;0x290
DECL|macro|CSR_TIMER1_LOAD
mdefine_line|#define CSR_TIMER1_LOAD&t;&t;0x300
DECL|macro|CSR_TIMER1_VALUE
mdefine_line|#define CSR_TIMER1_VALUE&t;0x304
DECL|macro|CSR_TIMER1_CNTL
mdefine_line|#define CSR_TIMER1_CNTL&t;&t;0x308
DECL|macro|CSR_TIMER1_CLR
mdefine_line|#define CSR_TIMER1_CLR&t;&t;0x30c
DECL|macro|CSR_TIMER2_LOAD
mdefine_line|#define CSR_TIMER2_LOAD&t;&t;0x320
DECL|macro|CSR_TIMER2_VALUE
mdefine_line|#define CSR_TIMER2_VALUE&t;0x324
DECL|macro|CSR_TIMER2_CNTL
mdefine_line|#define CSR_TIMER2_CNTL&t;&t;0x328
DECL|macro|CSR_TIMER2_CLR
mdefine_line|#define CSR_TIMER2_CLR&t;&t;0x32c
DECL|macro|CSR_TIMER3_LOAD
mdefine_line|#define CSR_TIMER3_LOAD&t;&t;0x340
DECL|macro|CSR_TIMER3_VALUE
mdefine_line|#define CSR_TIMER3_VALUE&t;0x344
DECL|macro|CSR_TIMER3_CNTL
mdefine_line|#define CSR_TIMER3_CNTL&t;&t;0x348
DECL|macro|CSR_TIMER3_CLR
mdefine_line|#define CSR_TIMER3_CLR&t;&t;0x34c
DECL|macro|CSR_TIMER4_LOAD
mdefine_line|#define CSR_TIMER4_LOAD&t;&t;0x360
DECL|macro|CSR_TIMER4_VALUE
mdefine_line|#define CSR_TIMER4_VALUE&t;0x364
DECL|macro|CSR_TIMER4_CNTL
mdefine_line|#define CSR_TIMER4_CNTL&t;&t;0x368
DECL|macro|CSR_TIMER4_CLR
mdefine_line|#define CSR_TIMER4_CLR&t;&t;0x36c
macro_line|#endif
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
eof
