multiline_comment|/*&n; * include/linux/serial.h&n; *&n; * Copyright (C) 1992 by Theodore Ts&squot;o.&n; * &n; * Redistribution of this file is permitted under the terms of the GNU &n; * Public License (GPL)&n; */
multiline_comment|/*&n; * This is our internal structure for each serial port&squot;s state.&n; * &n; * Many fields are paralleled by the structure used by the serial_struct&n; * structure.&n; *&n; * For definitions of the flags field, see tty.h&n; */
DECL|struct|async_struct
r_struct
id|async_struct
(brace
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|timer
r_int
r_int
id|timer
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|xmit_fifo_size
r_int
id|xmit_fifo_size
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|x_char
r_int
id|x_char
suffix:semicolon
multiline_comment|/* xon/xoff characater */
DECL|member|event
r_int
id|event
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|next_port
r_struct
id|async_struct
op_star
id|next_port
suffix:semicolon
multiline_comment|/* For the linked list */
DECL|member|prev_port
r_struct
id|async_struct
op_star
id|prev_port
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Events are used to schedule things to happen at timer-interrupt&n; * time, instead of at rs interrupt time.&n; */
DECL|macro|RS_EVENT_READ_PROCESS
mdefine_line|#define RS_EVENT_READ_PROCESS&t;0
DECL|macro|RS_EVENT_WRITE_WAKEUP
mdefine_line|#define RS_EVENT_WRITE_WAKEUP&t;1
DECL|macro|RS_EVENT_HUP_PGRP
mdefine_line|#define RS_EVENT_HUP_PGRP&t;2
DECL|macro|RS_EVENT_BREAK_INT
mdefine_line|#define RS_EVENT_BREAK_INT&t;3
DECL|macro|RS_EVENT_DO_SAK
mdefine_line|#define RS_EVENT_DO_SAK&t;&t;4
multiline_comment|/*&n; * These are the UART port assignments, expressed as offsets from the base&n; * register.  These assignments should hold for any serial port based on&n; * a 8250, 16450, or 16550(A).&n; */
DECL|macro|UART_RX
mdefine_line|#define UART_RX&t;&t;0&t;/* In:  Receive buffer (DLAB=0) */
DECL|macro|UART_TX
mdefine_line|#define UART_TX&t;&t;0&t;/* Out: Transmit buffer (DLAB=0) */
DECL|macro|UART_DLL
mdefine_line|#define UART_DLL&t;0&t;/* Out: Devisor Latch Low (DLAB=1) */
DECL|macro|UART_DLM
mdefine_line|#define UART_DLM&t;1&t;/* Out: Devisor Latch High (DLAB=1) */
DECL|macro|UART_IER
mdefine_line|#define UART_IER&t;1&t;/* Out: Interrupt Enable Register */
DECL|macro|UART_IIR
mdefine_line|#define UART_IIR&t;2&t;/* In:  Interrupt ID Register */
DECL|macro|UART_FCR
mdefine_line|#define UART_FCR&t;2&t;/* Out: FIFO Control Register */
DECL|macro|UART_LCR
mdefine_line|#define UART_LCR&t;3&t;/* Out: Line Control Register */
DECL|macro|UART_MCR
mdefine_line|#define UART_MCR&t;4&t;/* Out: Modem Control Register */
DECL|macro|UART_LSR
mdefine_line|#define UART_LSR&t;5&t;/* In:  Line Status Register */
DECL|macro|UART_MSR
mdefine_line|#define UART_MSR&t;6&t;/* In:  Modem Status Register */
DECL|macro|UART_SCR
mdefine_line|#define UART_SCR&t;7&t;/* I/O: Scratch Register */
multiline_comment|/*&n; * These are the definitions for the FIFO Control Register&n; */
DECL|macro|UART_FCR_ENABLE_FIFO
mdefine_line|#define UART_FCR_ENABLE_FIFO&t;0x01 /* Enable the FIFO */
DECL|macro|UART_FCR_CLEAR_RCVR
mdefine_line|#define UART_FCR_CLEAR_RCVR&t;0x02 /* Clear the RCVR FIFO */
DECL|macro|UART_FCR_CLEAR_XMIT
mdefine_line|#define UART_FCR_CLEAR_XMIT&t;0x04 /* Clear the XMIT FIFO */
DECL|macro|UART_FCR_DMA_SELECT
mdefine_line|#define UART_FCR_DMA_SELECT&t;0x08 /* For DMA applications */
DECL|macro|UART_FCR_TRIGGER_MASK
mdefine_line|#define UART_FCR_TRIGGER_MASK&t;0xC0 /* Mask for the FIFO trigger range */
DECL|macro|UART_FCR_TRIGGER_1
mdefine_line|#define UART_FCR_TRIGGER_1&t;0x00 /* Mask for trigger set at 1 */
DECL|macro|UART_FCR_TRIGGER_4
mdefine_line|#define UART_FCR_TRIGGER_4&t;0x40 /* Mask for trigger set at 4 */
DECL|macro|UART_FCR_TRIGGER_8
mdefine_line|#define UART_FCR_TRIGGER_8&t;0x80 /* Mask for trigger set at 8 */
DECL|macro|UART_FCR_TRIGGER_14
mdefine_line|#define UART_FCR_TRIGGER_14&t;0xC0 /* Mask for trigger set at 14 */
DECL|macro|UART_FCR_CLEAR_CMD
mdefine_line|#define UART_FCR_CLEAR_CMD&t;(UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT)
DECL|macro|UART_FCR_SETUP_CMD
mdefine_line|#define UART_FCR_SETUP_CMD&t;(UART_FCR_ENABLE_FIFO | UART_FCR_TRIGGER_8)
multiline_comment|/*&n; * These are the definitions for the Line Control Register&n; * &n; * Note: if the word length is 5 bits (UART_LCR_WLEN5), then setting &n; * UART_LCR_STOP will select 1.5 stop bits, not 2 stop bits.&n; */
DECL|macro|UART_LCR_DLAB
mdefine_line|#define UART_LCR_DLAB&t;0x80&t;/* Devisor latch access bit */
DECL|macro|UART_LCR_SBC
mdefine_line|#define UART_LCR_SBC&t;0x40&t;/* Set break control */
DECL|macro|UART_LCR_SPAR
mdefine_line|#define UART_LCR_SPAR&t;0x20&t;/* Stick parity (?) */
DECL|macro|UART_LCR_EPAR
mdefine_line|#define UART_LCR_EPAR&t;0x10&t;/* Even paraity select */
DECL|macro|UART_LCR_PARITY
mdefine_line|#define UART_LCR_PARITY&t;0x08&t;/* Parity Enable */
DECL|macro|UART_LCR_STOP
mdefine_line|#define UART_LCR_STOP&t;0x04&t;/* Stop bits: 0=1 stop bit, 1= 2 stop bits */
DECL|macro|UART_LCR_WLEN5
mdefine_line|#define UART_LCR_WLEN5  0x00&t;/* Wordlength: 5 bits */
DECL|macro|UART_LCR_WLEN6
mdefine_line|#define UART_LCR_WLEN6  0x01&t;/* Wordlength: 6 bits */
DECL|macro|UART_LCR_WLEN7
mdefine_line|#define UART_LCR_WLEN7  0x02&t;/* Wordlength: 7 bits */
DECL|macro|UART_LCR_WLEN8
mdefine_line|#define UART_LCR_WLEN8  0x03&t;/* Wordlength: 8 bits */
multiline_comment|/*&n; * These are the definitions for the Line Status Register&n; */
DECL|macro|UART_LSR_TEMT
mdefine_line|#define UART_LSR_TEMT&t;0x40&t;/* Transmitter empty */
DECL|macro|UART_LSR_THRE
mdefine_line|#define UART_LSR_THRE&t;0x20&t;/* Transmit-hold-register empty */
DECL|macro|UART_LSR_BI
mdefine_line|#define UART_LSR_BI&t;0x10&t;/* Break interrupt indicator */
DECL|macro|UART_LSR_FE
mdefine_line|#define UART_LSR_FE&t;0x08&t;/* Frame error indicator */
DECL|macro|UART_LSR_PE
mdefine_line|#define UART_LSR_PE&t;0x04&t;/* Parity error indicator */
DECL|macro|UART_LSR_OE
mdefine_line|#define UART_LSR_OE&t;0x02&t;/* Overrun error indicator */
DECL|macro|UART_LSR_DR
mdefine_line|#define UART_LSR_DR&t;0x01&t;/* Receiver data ready */
multiline_comment|/*&n; * These are the definitions for the Interrupt Indentification Register&n; */
DECL|macro|UART_IIR_NO_INT
mdefine_line|#define UART_IIR_NO_INT&t;0x01&t;/* No interrupts pending */
DECL|macro|UART_IIR_ID
mdefine_line|#define UART_IIR_ID&t;0x06&t;/* Mask for the interrupt ID */
DECL|macro|UART_IIR_MSI
mdefine_line|#define UART_IIR_MSI&t;0x00&t;/* Modem status interrupt */
DECL|macro|UART_IIR_THRI
mdefine_line|#define UART_IIR_THRI&t;0x02&t;/* Transmitter holding register empty */
DECL|macro|UART_IIR_RDI
mdefine_line|#define UART_IIR_RDI&t;0x04&t;/* Receiver data interrupt */
DECL|macro|UART_IIR_RLSI
mdefine_line|#define UART_IIR_RLSI&t;0x06&t;/* Receiver line status interrupt */
multiline_comment|/*&n; * These are the definitions for the Interrupt Enable Register&n; */
DECL|macro|UART_IER_MSI
mdefine_line|#define UART_IER_MSI&t;0x08&t;/* Enable Modem status interrupt */
DECL|macro|UART_IER_RLSI
mdefine_line|#define UART_IER_RLSI&t;0x04&t;/* Enable receiver line status interrupt */
DECL|macro|UART_IER_THRI
mdefine_line|#define UART_IER_THRI&t;0x02&t;/* Enable Transmitter holding register int. */
DECL|macro|UART_IER_RDI
mdefine_line|#define UART_IER_RDI&t;0x01&t;/* Enable receiver data interrupt */
multiline_comment|/*&n; * These are the definitions for the Modem Control Register&n; */
DECL|macro|UART_MCR_LOOP
mdefine_line|#define UART_MCR_LOOP&t;0x10&t;/* Enable loopback test mode */
DECL|macro|UART_MCR_OUT2
mdefine_line|#define UART_MCR_OUT2&t;0x08&t;/* Out2 complement */
DECL|macro|UART_MCR_OUT1
mdefine_line|#define UART_MCR_OUT1&t;0x04&t;/* Out1 complement */
DECL|macro|UART_MCR_RTS
mdefine_line|#define UART_MCR_RTS&t;0x02&t;/* RTS complement */
DECL|macro|UART_MCR_DTR
mdefine_line|#define UART_MCR_DTR&t;0x01&t;/* DTR complement */
multiline_comment|/*&n; * These are the definitions for the Modem Status Register&n; */
DECL|macro|UART_MSR_DCD
mdefine_line|#define UART_MSR_DCD&t;0x80&t;/* Data Carrier Detect */
DECL|macro|UART_MSR_RI
mdefine_line|#define UART_MSR_RI&t;0x40&t;/* Ring Indicator */
DECL|macro|UART_MSR_DSR
mdefine_line|#define UART_MSR_DSR&t;0x20&t;/* Data Set Ready */
DECL|macro|UART_MSR_CTS
mdefine_line|#define UART_MSR_CTS&t;0x10&t;/* Clear to Send */
DECL|macro|UART_MSR_DDCD
mdefine_line|#define UART_MSR_DDCD&t;0x08&t;/* Delta DCD */
DECL|macro|UART_MSR_TERI
mdefine_line|#define UART_MSR_TERI&t;0x04&t;/* Trailing edge ring indicator */
DECL|macro|UART_MSR_DDSR
mdefine_line|#define UART_MSR_DDSR&t;0x02&t;/* Delta DSR */
DECL|macro|UART_MSR_DCTS
mdefine_line|#define UART_MSR_DCTS&t;0x01&t;/* Delta CTS */
DECL|macro|UART_MSR_ANY_DELTA
mdefine_line|#define UART_MSR_ANY_DELTA 0x0F&t;/* Any of the delta bits! */
eof
