multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/irqs.h&n; *&n; * Copyright (C) 1998 Russell King&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;32
multiline_comment|/*&n; * This is a list of all interrupts that the 21285&n; * can generate&n; */
DECL|macro|IRQ_RESERVED
mdefine_line|#define IRQ_RESERVED&t;&t;0
DECL|macro|IRQ_SOFTIRQ
mdefine_line|#define IRQ_SOFTIRQ&t;&t;1
DECL|macro|IRQ_CONRX
mdefine_line|#define IRQ_CONRX&t;&t;2
DECL|macro|IRQ_CONTX
mdefine_line|#define IRQ_CONTX&t;&t;3
DECL|macro|IRQ_TIMER1
mdefine_line|#define IRQ_TIMER1&t;&t;4
DECL|macro|IRQ_TIMER2
mdefine_line|#define IRQ_TIMER2&t;&t;5
DECL|macro|IRQ_TIMER3
mdefine_line|#define IRQ_TIMER3&t;&t;6
DECL|macro|IRQ_TIMER4
mdefine_line|#define IRQ_TIMER4&t;&t;7
DECL|macro|IRQ_IN0
mdefine_line|#define IRQ_IN0&t;&t;&t;8
DECL|macro|IRQ_IN1
mdefine_line|#define IRQ_IN1&t;&t;&t;9
DECL|macro|IRQ_IN2
mdefine_line|#define IRQ_IN2&t;&t;&t;10
DECL|macro|IRQ_IN3
mdefine_line|#define IRQ_IN3&t;&t;&t;11
DECL|macro|IRQ_XCS0
mdefine_line|#define IRQ_XCS0&t;&t;12
DECL|macro|IRQ_XCS1
mdefine_line|#define IRQ_XCS1&t;&t;13
DECL|macro|IRQ_XCS2
mdefine_line|#define IRQ_XCS2&t;&t;14
DECL|macro|IRQ_DOORBELLHOST
mdefine_line|#define IRQ_DOORBELLHOST&t;15
DECL|macro|IRQ_DMA1
mdefine_line|#define IRQ_DMA1&t;&t;16
DECL|macro|IRQ_DMA2
mdefine_line|#define IRQ_DMA2&t;&t;17
DECL|macro|IRQ_PCI
mdefine_line|#define IRQ_PCI&t;&t;&t;18
DECL|macro|IRQ_BIST
mdefine_line|#define IRQ_BIST&t;&t;22
DECL|macro|IRQ_SERR
mdefine_line|#define IRQ_SERR&t;&t;23
DECL|macro|IRQ_SDRAMPARITY
mdefine_line|#define IRQ_SDRAMPARITY&t;&t;24
DECL|macro|IRQ_I2OINPOST
mdefine_line|#define IRQ_I2OINPOST&t;&t;25
DECL|macro|IRQ_DISCARDTIMER
mdefine_line|#define IRQ_DISCARDTIMER&t;27
DECL|macro|IRQ_PCIDATAPARITY
mdefine_line|#define IRQ_PCIDATAPARITY&t;28
DECL|macro|IRQ_PCIMASTERABORT
mdefine_line|#define IRQ_PCIMASTERABORT&t;29
DECL|macro|IRQ_PCITARGETABORT
mdefine_line|#define IRQ_PCITARGETABORT&t;30
DECL|macro|IRQ_PCIPARITY
mdefine_line|#define IRQ_PCIPARITY&t;&t;31
multiline_comment|/*&n; * Now map them to the Linux interrupts&n; */
DECL|macro|IRQ_TIMER
mdefine_line|#define IRQ_TIMER&t;&t;IRQ_TIMER1
eof
