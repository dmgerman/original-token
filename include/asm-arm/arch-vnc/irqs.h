multiline_comment|/*&n; * linux/include/asm-arm/arch-vnc/irqs.h&n; *&n; * Copyright (C) 1998 Russell King&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;32
multiline_comment|/*&n; * This is a list of all interrupts that the 21285&n; * can generate&n; */
DECL|macro|IRQ_SOFTIRQ
mdefine_line|#define IRQ_SOFTIRQ&t;&t;1&t;/* from FB.1 */
DECL|macro|IRQ_CONRX
mdefine_line|#define IRQ_CONRX&t;&t;2&t;/* from FB.2 */
DECL|macro|IRQ_CONTX
mdefine_line|#define IRQ_CONTX&t;&t;3&t;/* from FB.3 */
DECL|macro|IRQ_TIMER0
mdefine_line|#define IRQ_TIMER0&t;&t;4&t;/* from FB.4 */
DECL|macro|IRQ_TIMER1
mdefine_line|#define IRQ_TIMER1&t;&t;5&t;/* from FB.5 */
DECL|macro|IRQ_TIMER2
mdefine_line|#define IRQ_TIMER2&t;&t;6&t;/* from FB.6 */
DECL|macro|IRQ_WATCHDOG
mdefine_line|#define IRQ_WATCHDOG&t;&t;7&t;/* from FB.7 */
DECL|macro|IRQ_ETHER10
mdefine_line|#define IRQ_ETHER10&t;&t;8&t;/* from FB.8 */
DECL|macro|IRQ_ETHER100
mdefine_line|#define IRQ_ETHER100&t;&t;9&t;/* from FB.9 */
DECL|macro|IRQ_VIDCOMP
mdefine_line|#define IRQ_VIDCOMP&t;&t;10&t;/* from FB.10 */
DECL|macro|IRQ_EXTERN_IRQ
mdefine_line|#define IRQ_EXTERN_IRQ&t;&t;11&t;/* from FB.11: chain to IDE irq&squot;s */
DECL|macro|IRQ_DMA1
mdefine_line|#define IRQ_DMA1&t;&t;12&t;/* from future */
DECL|macro|IRQ_PCI_ERR
mdefine_line|#define IRQ_PCI_ERR&t;&t;15&t;/* from FB.[28:31] */
DECL|macro|IRQ_TIMER4
mdefine_line|#define IRQ_TIMER4&t;&t;16&t;/* from 553.0 */
DECL|macro|IRQ_KEYBOARD
mdefine_line|#define IRQ_KEYBOARD&t;&t;17&t;/* from 553.1 */
DECL|macro|IRQ_PIC_HI
mdefine_line|#define IRQ_PIC_HI&t;&t;18&t;/* from 533.2: chained to 553.[8:15] */
DECL|macro|IRQ_UART2
mdefine_line|#define IRQ_UART2&t;&t;19&t;/* from 553.3 */
DECL|macro|IRQ_UART
mdefine_line|#define IRQ_UART&t;&t;20&t;/* from 553.4 */
DECL|macro|IRQ_MOUSE
mdefine_line|#define IRQ_MOUSE&t;&t;21&t;/* from 553.5 */
DECL|macro|IRQ_UART_IR
mdefine_line|#define IRQ_UART_IR&t;&t;22&t;/* from 553.6 */
DECL|macro|IRQ_PRINTER
mdefine_line|#define IRQ_PRINTER&t;&t;23&t;/* from 553.7 */
DECL|macro|IRQ_RTC_ALARM
mdefine_line|#define IRQ_RTC_ALARM&t;&t;24&t;/* from 553.8 */
DECL|macro|IRQ_POWERLOW
mdefine_line|#define IRQ_POWERLOW&t;&t;26&t;/* from 553.10 */
DECL|macro|IRQ_VGA
mdefine_line|#define IRQ_VGA&t;&t;&t;27&t;/* from 553.11 */
DECL|macro|IRQ_SOUND
mdefine_line|#define IRQ_SOUND&t;&t;28&t;/* from 553.12 */
DECL|macro|IRQ_HARDDISK
mdefine_line|#define IRQ_HARDDISK&t;&t;30&t;/* from 553.14 */
multiline_comment|/* These defines handle the translation from the above FB #defines&n; * into physical buts for the FootBridge IRQ registers&n; */
DECL|macro|IRQ_MASK_SOFTIRQ
mdefine_line|#define IRQ_MASK_SOFTIRQ&t;0x00000002
DECL|macro|IRQ_MASK_UART_DEBUG
mdefine_line|#define IRQ_MASK_UART_DEBUG&t;0x0000000C
DECL|macro|IRQ_MASK_TIMER0
mdefine_line|#define IRQ_MASK_TIMER0&t;&t;0x00000010
DECL|macro|IRQ_MASK_TIMER1
mdefine_line|#define IRQ_MASK_TIMER1&t;&t;0x00000020
DECL|macro|IRQ_MASK_TIMER2
mdefine_line|#define IRQ_MASK_TIMER2&t;&t;0x00000040
DECL|macro|IRQ_MASK_WATCHDOG
mdefine_line|#define IRQ_MASK_WATCHDOG&t;0x00000080
DECL|macro|IRQ_MASK_ETHER10
mdefine_line|#define IRQ_MASK_ETHER10&t;0x00000100
DECL|macro|IRQ_MASK_ETHER100
mdefine_line|#define IRQ_MASK_ETHER100&t;0x00000200
DECL|macro|IRQ_MASK_VIDCOMP
mdefine_line|#define IRQ_MASK_VIDCOMP&t;0x00000400
DECL|macro|IRQ_MASK_EXTERN_IRQ
mdefine_line|#define IRQ_MASK_EXTERN_IRQ&t;0x00000800
DECL|macro|IRQ_MASK_DMA1
mdefine_line|#define IRQ_MASK_DMA1&t;&t;0x00030000
DECL|macro|IRQ_MASK_PCI_ERR
mdefine_line|#define IRQ_MASK_PCI_ERR&t;0xf0000000
multiline_comment|/*&n; * Now map them to the Linux interrupts&n; */
DECL|macro|IRQ_TIMER
mdefine_line|#define IRQ_TIMER&t;&t;IRQ_TIMER0
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(i)&t;(i)
eof
