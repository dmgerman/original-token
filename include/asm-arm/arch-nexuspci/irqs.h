multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/irqs.h&n; *&n; * Copyright (C) 1997 Philip Blundell&n; */
DECL|macro|IRQ_DUART
mdefine_line|#define IRQ_DUART&t;&t;0
DECL|macro|IRQ_TIMER0
mdefine_line|#define IRQ_TIMER0&t;&t;0&t;/* timer is part of the DUART */
DECL|macro|IRQ_PLX
mdefine_line|#define IRQ_PLX &t;&t;1
DECL|macro|IRQ_PCI_D
mdefine_line|#define IRQ_PCI_D&t;&t;2
DECL|macro|IRQ_PCI_C
mdefine_line|#define IRQ_PCI_C&t;&t;3
DECL|macro|IRQ_PCI_B
mdefine_line|#define IRQ_PCI_B&t;&t;4
DECL|macro|IRQ_PCI_A
mdefine_line|#define IRQ_PCI_A&t;&t;5
DECL|macro|IRQ_SYSERR
mdefine_line|#define IRQ_SYSERR&t;&t;6&t;/* must ask JB about this one */
eof
