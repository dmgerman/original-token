multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/irqs.h&n; *&n; * Copyright (C) 1997, 1998 Philip Blundell&n; */
multiline_comment|/* Most of the IRQ sources can generate both FIQs and IRQs.&n;   The exceptions to this are the DUART, which can only generate IRQs,&n;   and the PLX SYSERR output, which can only generate FIQs.  We route&n;   both FIQs and IRQs through the generic IRQ handling system and the&n;   choice by the driver of which to use is basically an arbitrary one.  */
DECL|macro|TREAT_FIQS_AS_IRQS
mdefine_line|#define TREAT_FIQS_AS_IRQS
DECL|macro|FIQ_PLX
mdefine_line|#define FIQ_PLX&t;&t;&t;0
DECL|macro|FIQ_PCI_D
mdefine_line|#define FIQ_PCI_D&t;&t;1
DECL|macro|FIQ_PCI_C
mdefine_line|#define FIQ_PCI_C&t;&t;2
DECL|macro|FIQ_PCI_B
mdefine_line|#define FIQ_PCI_B&t;&t;3
DECL|macro|FIQ_PCI_A
mdefine_line|#define FIQ_PCI_A&t;&t;4
DECL|macro|FIQ_SYSERR
mdefine_line|#define FIQ_SYSERR&t;&t;5
DECL|macro|IRQ_DUART
mdefine_line|#define IRQ_DUART&t;&t;6
DECL|macro|IRQ_PLX
mdefine_line|#define IRQ_PLX &t;&t;7
DECL|macro|IRQ_PCI_D
mdefine_line|#define IRQ_PCI_D&t;&t;8
DECL|macro|IRQ_PCI_C
mdefine_line|#define IRQ_PCI_C&t;&t;9
DECL|macro|IRQ_PCI_B
mdefine_line|#define IRQ_PCI_B&t;&t;10
DECL|macro|IRQ_PCI_A
mdefine_line|#define IRQ_PCI_A&t;        11
multiline_comment|/* timer is part of the DUART */
DECL|macro|IRQ_TIMER
mdefine_line|#define IRQ_TIMER&t;&t;IRQ_DUART
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(i)&t;(i)
eof
